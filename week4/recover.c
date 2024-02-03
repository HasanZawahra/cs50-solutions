#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("one CLA only\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open");
        return 1;
    }
    uint8_t b[BLOCK_SIZE];
    int i = 0;
    FILE *img;
    while (fread(&b, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        if (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && (b[3] & 0xf0) == 0xe0)
        {
            if (i == 0)
            {
                char *s = malloc(sizeof(char) * 8);
                if (s == NULL)
                {
                    return 1;
                }
                sprintf(s, "%03i.jpg", i);
                img = fopen(s, "w");
                if (img == NULL)
                {
                    printf("Could not open");
                    return 1;
                }
                fwrite(&b, BLOCK_SIZE, 1, img);
                free(s);
                i += 1;
            }
            else
            {
                fclose(img);
                char *s = malloc(sizeof(char) * 8);
                if (s == NULL)
                {
                    return 1;
                }
                sprintf(s, "%03i.jpg", i);
                img = fopen(s, "w");
                if (img == NULL)
                {
                    printf("Could not open");
                    return 1;
                }
                fwrite(&b, BLOCK_SIZE, 1, img);
                free(s);
                i += 1;
            }
        }
        else
        {
            if (i > 0)
            {
                fwrite(&b, BLOCK_SIZE, 1, img);
            }
        }
    }
    fclose(img);
    fclose(f);
    // slkdjfh s
    // d'r;f
    // df;lkg
}
