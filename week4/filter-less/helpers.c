#include "helpers.h"
#include <math.h>

// Convert image to grayscale
int less(int i, int l);
void swap(BYTE *i, BYTE *j);

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j ++)
        {
            int av = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = av;
            image[i][j].rgbtRed = av;
            image[i][j].rgbtGreen = av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE imag[height][width])
{
    RGBTRIPLE image[height][width];
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j ++)
        {
            image[i][j].rgbtBlue = imag[i][j].rgbtBlue;
            image[i][j].rgbtRed = imag[i][j].rgbtRed;
            image[i][j].rgbtGreen = imag[i][j].rgbtGreen;
        }
    }
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j ++)
        {
            imag[i][j].rgbtBlue = less(255, ((int) round((0.272 * (double)image[i][j].rgbtRed) + (0.534 * (double)image[i][j].rgbtGreen) +
                                             (0.131 * (double)image[i][j].rgbtBlue))));
            imag[i][j].rgbtRed = less(255, ((int) round((0.393 * (double)image[i][j].rgbtRed) + (0.769 * (double)image[i][j].rgbtGreen) +
                                            (0.189 * (double)image[i][j].rgbtBlue))));
            imag[i][j].rgbtGreen = less(255, ((int) round((0.349 * (double)image[i][j].rgbtRed) + (0.686 * (double)image[i][j].rgbtGreen) +
                                              (0.168 * (double)image[i][j].rgbtBlue))));
        }
    }
    return;
}
int less(int i, int l)
{
    if (i < l)
    {
        return i;
    }
    return l;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0, k = width - 1 ; j < width / 2 && k >= width / 2 ; j ++, k--)
        {
            swap(&image[i][k].rgbtBlue, &image[i][j].rgbtBlue);
            swap(&image[i][k].rgbtRed, &image[i][j].rgbtRed);
            swap(&image[i][k].rgbtGreen, &image[i][j].rgbtGreen);
        }
    }
    return;
}
void swap(BYTE *i, BYTE *j)
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE imag[height][width])
{
    RGBTRIPLE image[height][width];
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j ++)
        {
            image[i][j].rgbtBlue = imag[i][j].rgbtBlue;
            image[i][j].rgbtRed = imag[i][j].rgbtRed;
            image[i][j].rgbtGreen = imag[i][j].rgbtGreen;
        }
    }
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j ++)
        {
            if (i == 0 && j == 0)
            {
                imag[i][j].rgbtRed = (int) round((image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                                  image[i][j].rgbtRed) / 4.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                   image[i][j].rgbtBlue) / 4.0);
                imag[i][j].rgbtGreen = (int) round((image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                    image[i][j].rgbtGreen) / 4.0);
            }
            else if (i == 0 && j > 0 && j < width - 1)
            {
                imag[i][j].rgbtRed = (int) round((image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i][j -
                                                  1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j -
                                                   1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                imag[i][j].rgbtGreen = (int) round((image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                    image[i][j -
                                                            1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
            }
            else if (i == 0 && j == width - 1)
            {
                imag[i][j].rgbtRed = (int) round((image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                                  image[i][j].rgbtRed) / 4.0);
                imag[i][j].rgbtBlue = (int) round((image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                   image[i][j].rgbtBlue) / 4.0);
                imag[i][j].rgbtGreen = (int) round((image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                    image[i][j].rgbtGreen) / 4.0);
            }
            else if (i > 0 && i < height - 1 && j == 0)
            {
                imag[i][j].rgbtRed = (int) round((image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i -
                                                  1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i -
                                                   1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                imag[i][j].rgbtGreen = (int) round((image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i
                                                    -
                                                    1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
            }
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                imag[i][j].rgbtRed = (int) round((image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i -
                                                  1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i -
                                                   1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                imag[i][j].rgbtGreen = (int) round((image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i -
                                                    1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
            }
            else if (i == height - 1 && j == 0)
            {
                imag[i][j].rgbtRed = (int) round((image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                                  image[i][j].rgbtRed) / 4.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                   image[i][j].rgbtBlue) / 4.0);
                imag[i][j].rgbtGreen = (int) round((image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                    image[i][j].rgbtGreen) / 4.0);
            }
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                imag[i][j].rgbtRed = (int) round((image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j -
                                                  1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j -
                                                   1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);
                imag[i][j].rgbtGreen = (int) round((image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                    image[i][j -
                                                            1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
            }
            else if (i == height - 1 && j == width - 1)
            {
                imag[i][j].rgbtRed = (int) round((image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                                  image[i][j].rgbtRed) / 4.0);
                imag[i][j].rgbtBlue = (int) round((image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                                   image[i][j].rgbtBlue) / 4.0);
                imag[i][j].rgbtGreen = (int) round((image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                                    image[i][j].rgbtGreen) / 4.0);
            }
            else
            {
                imag[i][j].rgbtRed = (int) round((image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j -
                                                  1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                                  image[i][j].rgbtRed) / 9.0);
                imag[i][j].rgbtBlue = (int) round((image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j -
                                                   1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue
                                                   +
                                                   image[i][j].rgbtBlue) / 9.0);

                imag[i][j].rgbtGreen = (int) round((image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                    image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i +
                                                            1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 9.0);

            }
        }
    }
    return;
}
// rftgyhdfghfghdh