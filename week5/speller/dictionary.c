
// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N * N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // // TODO
    int hash_value = hash(word);
    for (node *t = table[hash_value]; t != NULL; t = t->next)
    {
        if (strcasecmp(word, t->word) == 0)
        {
            return true;
        }
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (strlen(word) > 1)
    {
        if (toupper(word[0]) - 'A' >= N)
        {
            if (toupper(word[1]) - 'A' >= N)
            {
                return (((toupper(word[0]) - 'A') % N) * N) + (toupper(word[1]) - 'A') % N;
            }
            return (((toupper(word[0]) - 'A') % N) * N) + (toupper(word[1]) - 'A');
        }
        return ((toupper(word[0]) - 'A') * N) + (toupper(word[1]) - 'A');
    }
    if (toupper(word[0]) - 'A' >= N)
    {
        return (((toupper(word[0]) - 'A') % N) * N) + (toupper(word[0]) - 'A') % N;
    }
    return ((toupper(word[0]) - 'A') * N) + (toupper(word[0]) - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
int ccc = 0;
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char w[LENGTH + 1];
    while (fscanf(file, "%s", w) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, w);
        int h = hash(w);
        n->next = table[h];
        table[h] = n;
        ccc += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (ccc > 0)
    {
        return ccc;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0, c = N * N; i < c; i++)
    {
        node *p = table[i];

        while (p != NULL)
        {
            node *tmp = p;
            p = p->next;
            free(tmp);
        }

        if (p == NULL && i == c - 1)
        {
            return true;
        }
    }
    return false;
}
