# TODO
from cs50 import get_string

number = get_string("NUMBER: ")
x = number.isnumeric()
while x == False:
    number = get_string("NUMBER: ")
    x = number.isnumeric()
sum = int(0)
i = len(number) - 1
o = int(0)
while i >= 0:
    if o % 2 == 0:
        sum += int(number[i])
    else:
        s = int(number[i])*2
        if s > 9:
            s -= 10
            sum += (s+1)
        else:
            sum += s
    i -= 1
    o += 1
if sum % 10 != 0:
    print("INVALID")
else:
    if number[0] == '3' and o == 15:
        if number[1] in ['4', '7']:
            print("AMEX")
        else:
            print("INVALID")
    elif number[0] == '5' and o == 16:
        if number[1] in ['1', '2', '3', '4', '5']:
            print("MASTERCARD")
        else:
            print("INVALID")
    elif number[0] == '4':
        if o == 16 or o == 13:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
