#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int h = get_int("Cahnge Owed: ");
    do
    {
        int sum = h / 25;
        h = h % 25;
        sum += h / 10;
        h = h % 10;
        sum += h / 5;
        h = h % 5;
        sum += h;
        printf("%i\n", sum);
    }
    while (h < 0);
}
