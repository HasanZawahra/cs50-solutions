#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asking the user to enter the number.
    long num = get_long("enter the c.n :");
    int f = 0;
    int s = 0;
    int c = 1;
    int l = 0;
    int g = 0;
    int o = 0;
    int y = 0;
    // checking if the number is valid or not.
    while (num > 0)
    {
        if (c == 16 || c == 15)
        {
            g += num % 10;

            l += num % 10;

            if (c == 16)
            {
                y += num % 10;
            }
        }
        if (c == 14)
        {
            g += num % 10;
        }
        if (c == 13)
        {
            o += num % 10;
        }
        if (c % 2 != 0)
        {
            f += (num % 10);
            num /= 10;
        }
        else
        {
            if (num % 10 >= 5)
            {
                s += (num % 10 - 4 + (num % 10 - 5));
            }
            else
            {
                s += (num % 10) * 2;
            }
            num /= 10;
        }
        c += 1;
    }
    c -= 1;
    s += f;
    if (c == 15)
    {
        if (g == 7 || g == 10)
        {
            if (s % 10 == 0)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (c == 13)
    {
        if (o == 4)
        {
            if (s % 10 == 0)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (c == 16)
    {
        if (y == 4)
        {
            if (s % 10 == 0)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (l == 6 || l == 7 || l == 8 || l == 9 || l == 10)
        {
            if (s % 10 == 0)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}