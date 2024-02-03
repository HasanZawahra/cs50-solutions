#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
        for (int i = 1; i <= h; i += 1)
        {
            for (int j = 0; j < h - i; j += 1)
            {
                printf(" ");
            }
            for (int j = 0; j < i; j += 1)
            {
                printf("#");
            }

            printf("\n");
        }
    }
    while (h < 1);
}
