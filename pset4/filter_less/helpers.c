#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Prevent overloop
    if (height < 0)
    {
        return;
    }

    // Initialise
    BYTE average[width];
    for (int x = 0; x < width; x++)
    {
        average[x] = 0;
    }

    // Copy input
    for (int i = 0; i < width; i++)
    {
        average[i] = round((image[height][i].rgbtRed + image[height][i].rgbtBlue + image[height][i].rgbtGreen) / 3.0);


    }

    for (int j = 0; j < width; j++)
    {
        image[height][j].rgbtRed = average[j];
        image[height][j].rgbtBlue = average[j];
        image[height][j].rgbtGreen = average[j];
    }
    grayscale(height - 1, width, image);

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    if (height < 0)
    {
        return;
    }
    
    // Initialise
    RGBTRIPLE copy[width];
    int temp[3] = {0};
    
    for (int x = 0; x < width; x++)
    {
        copy[x].rgbtRed = 0;
        copy[x].rgbtGreen = 0;
        copy[x].rgbtBlue = 0;
    }

    // Sepia process
    for (int i = 0; i < width; i++)
    {
        
        temp[0] = round(0.393 * image[height][i].rgbtRed + 0.769 * image[height][i].rgbtGreen + 0.189 * image[height][i].rgbtBlue);
        temp[1] = round(0.349 * image[height][i].rgbtRed + 0.686 * image[height][i].rgbtGreen + 0.168 * image[height][i].rgbtBlue);
        temp[2] = round(0.272 * image[height][i].rgbtRed + 0.534 * image[height][i].rgbtGreen + 0.131 * image[height][i].rgbtBlue);
        
        if (temp[0] > 255)
        {
            temp[0] = 255;
        }
        if (temp[1] > 255)
        {
            temp[1] = 255;
        }
        if (temp[2] > 255)
        {
            temp[2] = 255;
        }
        
        copy[i].rgbtRed = temp[0];
        copy[i].rgbtGreen = temp[1];
        copy[i].rgbtBlue = temp[2];
    }
    
    for (int j  = 0; j < width; j++)
    {
        image[height][j] = copy[j];
    }
    
    sepia(height - 1, width, image);
        
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Base criteria to prevent overloop
    if (height < 0)
    {
        return;
    }

    // Initialise
    RGBTRIPLE temp[width / 2];


    for (int j = 0; j < width / 2; j++)
    {
        temp[j].rgbtRed = 0;
        temp[j].rgbtBlue = 0;
        temp[j].rgbtGreen = 0;
    }

    for (int i = 0; i < width / 2; i++)
    {
        int j = width - i - 1;
        // Copy input into
        temp[i] = image[height][i];

        // Swap
        image[height][i] = image[height][j];
        image[height][j] = temp[i];
    }
    // Recursion
    reflect(height - 1, width, image);
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialise
    int total_red;
    int total_blue;
    int total_green;
    char cases;
    RGBTRIPLE temp[height][width];

    // Initialise array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtGreen = 0;
        }
    }

    // Start
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise everytime to make sure value renew
            total_red = 0;
            total_blue = 0;
            total_green = 0;
            cases = ' ';

            // Non edge block
            if (i - 1 >= 0 && i < height - 1 && j - 1 >= 0 && j < width - 1)
            {
                cases = 'a';
                for (int x = i - 1; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 2; y++)
                    {
                        total_red += image[x][y].rgbtRed;
                        total_blue += image[x][y].rgbtBlue;
                        total_green += image[x][y].rgbtGreen;
                    }
                }
            }

            // HEIGHT IS 0
            else if (i - 1 < 0)
            {
                cases = 'b';

                // Width is at most left
                if (j == 0)
                {
                    for (int x = i; x < i + 2; x++)
                    {
                        for (int y = j ; y < j + 2; y++)
                        {
                            total_red += image[x][y].rgbtRed;
                            total_blue += image[x][y].rgbtBlue;
                            total_green += image[x][y].rgbtGreen;
                        }
                    }
                }

                // Width at most right
                else if (j + 1 == width)
                {
                    for (int x = i; x < i + 2; x++)
                    {
                        for (int y = j - 1; y < j + 1; y++)
                        {
                            total_red += image[x][y].rgbtRed;
                            total_blue += image[x][y].rgbtBlue;
                            total_green += image[x][y].rgbtGreen;
                        }
                    }
                }
                else
                {
                    cases = 'c';
                    for (int x = i; x < i + 2; x++)
                    {
                        for (int y = j - 1; y < j + 2; y++)
                        {
                            total_red += image[x][y].rgbtRed;
                            total_blue += image[x][y].rgbtBlue;
                            total_green += image[x][y].rgbtGreen;
                        }
                    }
                }
            }

            // HEIGHT IS THE BOTTOM
            else if (i + 1 == height)
            {
                cases = 'b';

                // Width at most left
                if (j - 1 < 0)
                {
                    for (int x = i - 1; x < i + 1; x++)
                    {
                        for (int y = j; y < j + 2; y++)
                        {
                            total_red += image[x][y].rgbtRed;
                            total_blue += image[x][y].rgbtBlue;
                            total_green += image[x][y].rgbtGreen;
                        }
                    }
                }

                // Width most right
                else if (j + 1 == width)
                {
                    for (int x = i - 1; x < i + 1; x++)
                    {
                        for (int y = j - 1; y < j + 1; y++)
                        {
                            total_red += image[x][y].rgbtRed;
                            total_blue += image[x][y].rgbtBlue;
                            total_green += image[x][y].rgbtGreen;
                        }
                    }
                }
                else
                {
                    cases = 'c';
                    for (int x = i - 1; x <= i; x++)
                    {
                        for (int y = j - 1; y < j + 2; y++)
                        {
                            total_red += image[x][y].rgbtRed;
                            total_blue += image[x][y].rgbtBlue;
                            total_green += image[x][y].rgbtGreen;
                        }
                    }
                }

            }

            // WIDTH IS THE MOST LEFT
            else if (j == 0)
            {
                cases = 'c';
                for (int x = i - 1 ; x < i + 2; x++)
                {
                    for (int y = j; y < j + 2; y++)
                    {
                        total_red += image[x][y].rgbtRed;
                        total_blue += image[x][y].rgbtBlue;
                        total_green += image[x][y].rgbtGreen;
                    }
                }
            }

            // WIDTH IS THE MOST RIGHT
            else if (j + 1 == width)
            {
                cases = 'c';
                for (int x = i - 1 ; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 1; y++)
                    {
                        total_red += image[x][y].rgbtRed;
                        total_blue += image[x][y].rgbtBlue;
                        total_green += image[x][y].rgbtGreen;
                    }
                }
            }

            // Blur colour according to assigned letter
            if (cases == ' ')
            {
                printf("Error\n");
                return;
            }
            // 'a' is for non-edge pixel
            else if (cases == 'a')
            {
                temp[i][j].rgbtRed = round(total_red / 9.0);
                temp[i][j].rgbtBlue = round(total_blue / 9.0);
                temp[i][j].rgbtGreen = round(total_green / 9.0);
            }
            // 'b' and 'c' is edge pixel
            else if (cases == 'b')
            {
                temp[i][j].rgbtRed = round(total_red / 4.0);
                temp[i][j].rgbtBlue = round(total_blue / 4.0);
                temp[i][j].rgbtGreen = round(total_green / 4.0);
            }

            else if (cases == 'c')
            {
                temp[i][j].rgbtRed = round(total_red / 6.0);
                temp[i][j].rgbtBlue = round(total_blue / 6.0);
                temp[i][j].rgbtGreen = round(total_green / 6.0);
            }
        }
    }

    // Put temp value of colour into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}
