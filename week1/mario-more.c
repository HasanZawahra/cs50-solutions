#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asking the user to input an integer.
    int h = get_int("enter the height of the pyramid :");
    // makeing the user reinput the ineger if the recent input was invalid.
    while (h < 1 || h > 8)
    {
        h = get_int("invalid input, enter again :");
    }
    //a nested (for loop) to make the pyramid.
    for (int j = 1; j <= h; j++)
    {
        // msking the left side of the pyramid.
        for (int i = 1; i <= h; i++)
        {
            if (i > h - j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int i = 1; i <= j; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
