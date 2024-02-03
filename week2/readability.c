#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sants(string text);
int main(void)
{
    string text = get_string("Tsxt :");
    int let = count_letters(text);
    int words = count_words(text);
    int sants = count_sants(text);
    double L = ((double) let / words) * 100;
    double S = ((double) sants / words) * 100;
    double res = (0.0588 * L) - (0.296 * S) - 15.8;
    int an = round(res);
    if (an >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (an < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", an);
    }
}
int count_letters(string text)
{
    int let = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            let++;
        }
    }
    return let;
}
int count_words(string text)
{
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}
int count_sants(string text)
{
    int sants = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sants++;
        }
    }
    return sants;
}
