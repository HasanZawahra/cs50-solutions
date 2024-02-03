# TODO
from cs50 import get_int
Height = get_int("Height: ")
while Height < 1 or Height > 8:
    Height = get_int("Height: ")
for i in range(Height):
    print(" "*(Height - (i + 1)), end="")
    print("#"*(i+1)+"  ", end="")
    print("#"*(i+1))
