import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from time import strftime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    dic = db.execute("SELECT symbol, name, shares, price FROM stocks WHERE user_id =?", session["user_id"])
    cash = float(0)
    for s in dic:
        cash += int(s["shares"])*float(s["price"])
    tot = db.execute("SELECT cash FROM users WHERE id =?", session["user_id"])
    return render_template("index.html", dic=dic, cash=usd(tot[0]["cash"]), tot=usd(tot[0]["cash"]+cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide Symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide number of shares!!!!", 400)

        nn = lookup(request.form.get("symbol"))
        if not nn:
            return apology("This stock's symbol doesn't exist!", 400)

        elif not str.isdigit(request.form.get("shares")):
            return apology("invalid input", 400)

        if int(request.form.get("shares")) <= 0:
            return apology("Invalid number of shares!", 400)

        dict = lookup(str.upper(request.form.get("symbol")))
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        total_price = float(dict["price"])*int(request.form.get("shares"))

        if float(rows[0]["cash"]) < total_price:
            return apology("Can't afford!", 400)

        else:
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=rows[0]["cash"] - total_price, id=session["user_id"])

        datetime = strftime('%Y-%m-%d %H:%M:%S')
        flash("Congratulations! Transaction is successful!")

        db.execute("""INSERT INTO transactions (
                        user_id, symbol, name, shares, price_per_share, total_price, transacted)
                        VALUES(:user_id, :symbol, :name, :shares, :price_per_share, :total_price, :transacted)""",
                   user_id=session["user_id"], symbol=str.upper(request.form.get("symbol")),
                   name=dict["name"], shares=int(request.form.get("shares")), price_per_share=dict["price"],
                   total_price=total_price, transacted=datetime)

        instock = db.execute("SELECT symbol FROM stocks WHERE user_id = :user_id and symbol = :symbol",
                             user_id=session["user_id"], symbol=str.upper(request.form.get("symbol")))
        if not instock:
            db.execute("INSERT INTO stocks(user_id,symbol,name,shares,price)VALUES(?,?,?,?,?)", session["user_id"], str.upper(
                request.form.get("symbol")), dict["name"], int(request.form.get("shares")), dict["price"])

        else:
            rows = db.execute("SELECT shares FROM stocks WHERE user_id = :user_id and symbol = :symbol",
                              user_id=session["user_id"], symbol=str.upper(request.form.get("symbol")))

            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? and symbol = ? ", int(
                rows[0]["shares"]) + int(request.form.get("shares")), ession["user_id"], str.upper(request.form.get("symbol")))

        return redirect(url_for("index"))

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol,shares,price_per_share,transacted FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect(url_for("index"))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect(url_for("login"))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        nn = lookup(request.form.get("symbol"))
        if not nn:
            return apology("This stock's symbol doesn't exist!", 400)
        elif not request.form.get("symbol"):
            return apology("missing symbol", 400)

        else:
            dic = lookup(request.form.get("symbol"))
            return render_template("quoted.html", name=dic["name"], price=usd(dic["price"]), symbol=dic["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username!", 400)

        if not request.form.get("password"):
            return apology("must provide password", 400)

        if not request.form.get("confirmation"):
            return apology("must provide password!", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("fuck you!", 400)

        rows = db.execute("SELECT username FROM users")
        if request.form.get("username") in rows[0]["username"]:
            return apology("The username you typed in is already taken", 400)

        else:
            pas = generate_password_hash(request.form.get("password"))
            user = request.form.get("username")
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", user, pas)
            flash("Congratulations!You were successfully registered!")
            rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
            session["user_id"] = rows[0]["id"]
            return redirect(url_for("index"))
    else:
        return render_template("registration.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        num = db.execute("SELECT shares,price FROM stocks WHERE user_id =?", session["user_id"])
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)
        if not request.form.get("shares") or int(request.form.get("shares")) <= 0 or int(request.form.get("shares")) > num[0]["shares"]:
            return apology("Invalid number of shares!!!!", 400)

        else:
            flash("SOLD!")
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? and symbol = ? ", int(
                num[0]["shares"])-int(request.form.get("shares")), session["user_id"], request.form.get("symbol"))
            c = db.execute("SELECT cash FROM users WHERE id =?", session["user_id"])
            ca = (int(request.form.get("shares"))*float(num[0]["price"]))
            db.execute("UPDATE users SET cash = ? WHERE id = ?", float(c[0]["cash"]) + ca, session["user_id"])
            um = db.execute("SELECT shares FROM stocks WHERE user_id =?", session["user_id"])
            if int(um[0]["shares"]) == 0:
                db.execute("DELETE FROM stocks WHERE symbol=? AND user_id =?", request.form.get("symbol"), session["user_id"])
            return redirect(url_for("index"))

    else:
        rows = db.execute("SELECT symbol FROM stocks WHERE user_id =?", session["user_id"])
        return render_template("sell.html", rows=rows)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    if request.method == "POST":
        if not request.form.get("amount"):
            return apology("Must insert the amount!!!!", 400)

        else:
            flash("CHASH ADDED successfully!!")
            c = db.execute("SELECT cash FROM users WHERE id =?", session["user_id"])
            db.execute("UPDATE users SET cash = ? WHERE id = ?", float(
                c[0]["cash"])+float(request.form.get("amount")), session["user_id"])
            return redirect(url_for("index"))

    else:
        return render_template("addcash.html")
