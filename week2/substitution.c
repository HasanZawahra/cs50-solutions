#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    char ar[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char ar2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int sum = 0;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (ar[i] == (argv[1])[j] || ar2[i] == (argv[1])[j])
            {
                sum += 1;
                i += 1;
                j = -1;
            }
        }
    }
    if (sum != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, o = strlen(s); i < o; i++)
    {
        if (isupper(s[i]) != 0)
        {
            if (islower((argv[1])[s[i] - 65]) != 0)
            {
                printf("%c", (argv[1])[s[i] - 65] - 32);
            }
            else
            {
                printf("%c", (argv[1])[s[i] - 65]);
            }
        }
        else if (islower(s[i]) != 0)
        {
            if (isupper((argv[1])[s[i] - 97]) != 0)
            {
                printf("%c", (argv[1])[s[i] - 97] + 32);
            }
            else
            {
                printf("%c", (argv[1])[s[i] - 97]);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
