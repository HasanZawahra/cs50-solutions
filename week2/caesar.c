#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, j = strlen(argv[1]) ; i < j ; i++)
    {
        if (isdigit((argv[1])[i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    int k = atoi(argv[1]);
    while (k >= 26)
    {
        k -= 26;
    }
    for (int i = 0, j = strlen(s) ; i < j ; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            if (s[i] + k > 90)
            {
                printf("%c", '@' + ((s[i] + k) - 90));
            }
            else
            {
                printf("%c", s[i] + k);
            }
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            if (s[i] + k > 122)
            {
                printf("%c", '`' + ((s[i] + k) - 122));
            }
            else
            {
                printf("%c", s[i] + k);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}