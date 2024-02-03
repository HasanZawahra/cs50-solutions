# TODO
from cs50 import get_string
t = get_string("TEXT: ")
letters = int(0)
words = int(1)
sants = int(0)
for i in (t):
    if i.isalpha() == True:
        letters += 1
    if i == ' ':
        words += 1
    if i in ['.', '!', '?']:
        sants += 1
l = (letters / words) * 100
s = (sants / words) * 100
ind = (0.0588 * l) - (0.296 * s) - 15.8
ind = int(round(ind))
if ind > 16:
    print("Grade 16+")
elif ind <= 1:
    print("Before Grade 1")
else:
    print(f"Grade {ind}")
