#include "helpers.h"
#include <cs50.h>
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialise
    int check = 0;
    double Gx = 0, Gy = 0, total = 0;
    RGBTRIPLE temp[height][width];
    bool border[height][width];
    
    // Initialise array
    for (int i  = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtGreen = 0;
            border[i][j] = false;
        }
    }
    
    // Check for the certain pixel if is at border
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)    
            {
                border[i][j] = true;                
            }
        }
    }
    
    // Loop start
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gx = 0, Gy = 0;
            
            // If is not at border, calculate formula
            if (!border[i][j])
            {
                // Count red
                Gx = (-1 * (image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed)) + (-2 * image[i][j - 1].rgbtRed) + 
                     (image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed);
                Gy = (-1 * (image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed)) + (-2 * image[i - 1][j].rgbtRed) + 
                     (image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) + (2 * image[i + 1][j].rgbtRed);
                
                temp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                
                if (temp[i][j].rgbtRed > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                
                // Count Blue
                Gx = (-1 * (image[i - 1][j - 1].rgbtBlue + image [i + 1][j - 1].rgbtBlue)) + (-2 * image[i][j - 1].rgbtBlue) +
                     (image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue);
                Gy = (-1 * (image[i - 1][j - 1].rgbtBlue + image [i - 1][j + 1].rgbtBlue)) + (-2 * image[i - 1][j].rgbtBlue) + 
                     (image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) + (2 * image[i + 1][j].rgbtBlue);
                
                temp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                
                if (temp[i][j].rgbtBlue > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                
                // Count green
                Gx = (-1 * (image[i - 1][j - 1].rgbtGreen + image [i + 1][j - 1].rgbtGreen)) + (-2 * image[i][j - 1].rgbtGreen) + 
                     (image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen);
                Gy = (-1 * (image[i - 1][j - 1].rgbtGreen + image [i - 1][j + 1].rgbtGreen)) + (-2 * image[i - 1][j].rgbtGreen) + 
                     (image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) + (2 * image[i + 1][j].rgbtGreen);
                
                temp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                
                if (temp[i][j].rgbtGreen > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
            }
            // If the pixel is at border
            else
            {
                // AT THE MOST TOP
                if (i == 0)
                {
                    // TOP LEFT
                    if (j == 0)
                    {
                        // Count red
                        Gx = image[i + 1][j + 1].rgbtRed + (2 * image[i][j + 1].rgbtRed);
                        Gy = image[i + 1][j + 1].rgbtRed + (2 * image[i + 1][j].rgbtRed);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtRed = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtRed = check;
                        }
                        
                        // Count Blue
                        Gx = image[i + 1][j + 1].rgbtBlue + (2 * image[i][j + 1].rgbtBlue);
                        Gy = image[i + 1][j + 1].rgbtBlue + (2 * image[i + 1][j].rgbtBlue);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtBlue = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtBlue = check;
                        }
                        
                        // Count green
                        Gx = image[i + 1][j + 1].rgbtGreen + (2 * image[i][j + 1].rgbtGreen);
                        Gy = image[i + 1][j + 1].rgbtGreen + (2 * image[i + 1][j].rgbtGreen);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtGreen = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtGreen = check;
                        }
                    }
                    // TOP RIGHT
                    else if (j == width - 1)
                    {
                        // Count red
                        Gx = (-1 * image[i + 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed);
                        Gy = image[i + 1][j - 1].rgbtRed + (2 * image[i + 1][j].rgbtRed);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtRed = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtRed = check;
                        }
                        
                        // Count Blue
                        Gx = (-1 * image[i + 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue);
                        Gy = image[i + 1][j - 1].rgbtBlue + (2 * image[i + 1][j].rgbtBlue);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtBlue = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtBlue = check;
                        }
                        
                        // Count green
                        Gx = (-1 * image[i + 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen);
                        Gy = image[i + 1][j - 1].rgbtGreen + (2 * image[i + 1][j].rgbtGreen);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtGreen = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtGreen = check;
                        }
                    }
                    // TOP MIDDLE
                    else
                    {
                        // Count red
                        Gx = (-2 * image[i][j - 1].rgbtRed) + (-1 * image[i + 1][j - 1].rgbtRed) + image[i + 1][j + 1].rgbtRed + 
                             (2 * image[i][j + 1].rgbtRed);
                        Gy = image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed + (2 * image[i + 1][j].rgbtRed);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtRed = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtRed = check;
                        }
                        
                        // Count Blue
                        Gx = (-2 * image[i][j - 1].rgbtBlue) + (-1 * image[i + 1][j - 1].rgbtBlue) + image[i + 1][j + 1].rgbtBlue + 
                             (2 * image[i][j + 1].rgbtBlue);
                        Gy = image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + (2 * image[i + 1][j].rgbtBlue);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtBlue = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtBlue = check;
                        }
                        
                        // Count Green
                        Gx = (-2 * image[i][j - 1].rgbtGreen) + (-1 * image[i + 1][j - 1].rgbtGreen) + image[i + 1][j + 1].rgbtGreen + 
                             (2 * image[i][j + 1].rgbtGreen);
                        Gy = image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + (2 * image[i + 1][j].rgbtGreen);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtGreen = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtGreen = check;
                        }
                    }
                }

                // HEIGHT AT THE MOST BOTTOM
                else if (i == height - 1)
                {
                    // BOTTOM LEFT
                    if (j == 0)
                    {
                        // Count Red
                        Gx = image[i - 1][j + 1].rgbtRed + (2 * image[i][j + 1].rgbtRed);
                        Gy = (-1 * image [i - 1][j + 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtRed = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtRed = check;
                        }
                        
                        // Count Blue
                        Gx = image[i - 1][j + 1].rgbtBlue + (2 * image[i][j + 1].rgbtBlue);
                        Gy = (-1 * image [i - 1][j + 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtBlue = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtBlue = check;
                        }
                        
                        // Count Green
                        Gx = image[i - 1][j + 1].rgbtGreen + (2 * image[i][j + 1].rgbtGreen);
                        Gy = (-1 * image [i - 1][j + 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtGreen = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtGreen = check;
                        }
                    }
                    // BOTTOM RIGHT
                    else if (j == width - 1)
                    {
                        // Count Red
                        Gx = (-1 * image[i - 1][j - 1].rgbtRed) + (-2 * image[i][j - 1].rgbtRed);
                        Gy = (-1 * image [i - 1][j - 1].rgbtRed) + (-2 * image[i - 1][j].rgbtRed);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtRed = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtRed = check;
                        }
                        
                        // Count Green
                        Gx = (-1 * image[i - 1][j - 1].rgbtGreen) + (-2 * image[i][j - 1].rgbtGreen);
                        Gy = (-1 * image [i - 1][j - 1].rgbtGreen) + (-2 * image[i - 1][j].rgbtGreen);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtGreen = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtGreen = check;
                        }
                        
                        // Count Blue
                        Gx = (-1 * image[i - 1][j - 1].rgbtBlue) + (-2 * image[i][j - 1].rgbtBlue);
                        Gy = (-1 * image [i - 1][j - 1].rgbtBlue) + (-2 * image[i - 1][j].rgbtBlue);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtBlue = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtBlue = check;
                        }
                    }
                    // BOTTOM MIDDLE
                    else
                    {
                        // Count Red
                        Gx = (-2 * image[i][j - 1].rgbtRed) + image[i - 1][j + 1].rgbtRed + (-1 * image[i - 1][j - 1].rgbtRed) + 
                             (2 * image[i][j + 1].rgbtRed);
                        Gy = (-1 * (image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed)) + (-2 * image[i - 1][j].rgbtRed);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtRed = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtRed = check;
                        }
                        
                        // Count Blue
                        Gx = (-2 * image[i][j - 1].rgbtBlue) + image[i - 1][j + 1].rgbtBlue + (-1 * image[i - 1][j - 1].rgbtBlue) + 
                             (2 * image[i][j + 1].rgbtBlue);
                        Gy = (-1 * (image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue)) + (-2 * image[i - 1][j].rgbtBlue);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtBlue = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtBlue = check;
                        }
                        
                        // Count Green
                        Gx = (-2 * image[i][j - 1].rgbtGreen) + image[i - 1][j + 1].rgbtGreen + (-1 * image[i - 1][j - 1].rgbtGreen) + 
                             (2 * image[i][j + 1].rgbtGreen);
                        Gy = (-1 * (image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen)) + (-2 * image[i - 1][j].rgbtGreen);
                        check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                        if (check > 255)
                        {
                            temp[i][j].rgbtGreen = 255;
                        }
                        else
                        {
                            temp[i][j].rgbtGreen = check;
                        }
                
                    }    
                }
                // IF IS MIDDLE LEFT
                else if (j == 0 && i != 0 && i != height - 1)
                {
                    // Count Red
                    Gx = (2 * image[i][j + 1].rgbtRed) + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    Gy = (-1 * image[i - 1][j + 1].rgbtRed) + image[i + 1][j + 1].rgbtRed + (-2 * image[i - 1][j].rgbtRed) + 
                         (2 * image[i + 1][j].rgbtRed);
                    check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                    if (check > 255)
                    {
                        temp[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        temp[i][j].rgbtRed = check;
                    }
                        
                    // Count Blue
                    Gx = (2 * image[i][j + 1].rgbtBlue) + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    Gy = (-1 * image[i - 1][j + 1].rgbtBlue) + image[i + 1][j + 1].rgbtBlue + (-2 * image[i - 1][j].rgbtBlue) + 
                         (2 * image[i + 1][j].rgbtBlue);
                    check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                    if (check > 255)
                    {
                        temp[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        temp[i][j].rgbtBlue = check;
                    }
                        
                    // Count Green
                    Gx = (2 * image[i][j + 1].rgbtGreen) + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    Gy = (-1 * image[i - 1][j + 1].rgbtGreen) + image[i + 1][j + 1].rgbtGreen + (-2 * image[i - 1][j].rgbtGreen) + 
                         (2 * image[i + 1][j].rgbtGreen);
                    check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                    if (check > 255)
                    {
                        temp[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        temp[i][j].rgbtGreen = check;
                    }
                }
                // IF IS MIDDLE RIGHT
                else if (j == width - 1 && i != 0 && i != height - 1)
                {
                    // Count Red
                    Gx = (-2 * image[i][j - 1].rgbtRed) + (-1 * (image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed));
                    Gy = (-1 * image[i - 1][j - 1].rgbtRed) + image[i + 1][j - 1].rgbtRed + (-2 * image[i - 1][j].rgbtRed) + 
                         (2 * image[i + 1][j].rgbtRed);
                    check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                    if (check > 255)
                    {
                        temp[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        temp[i][j].rgbtRed = check;
                    }
                        
                    // Count Blue
                    Gx = (-2 * image[i][j - 1].rgbtBlue) + (-1 * (image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue));
                    Gy = (-1 * image[i - 1][j - 1].rgbtBlue) + image[i + 1][j - 1].rgbtBlue + (-2 * image[i - 1][j].rgbtBlue) + 
                         (2 * image[i + 1][j].rgbtBlue);
                    check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                    if (check > 255)
                    {
                        temp[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        temp[i][j].rgbtBlue = check;
                    }
                        
                    // Count Green
                    Gx = (-2 * image[i][j - 1].rgbtGreen) + (-1 * (image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen));
                    Gy = (-1 * image[i - 1][j - 1].rgbtGreen) + image[i + 1][j - 1].rgbtGreen + (-2 * image[i - 1][j].rgbtGreen) + 
                         (2 * image[i + 1][j].rgbtGreen);
                    check = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
                    if (check > 255)
                    {
                        temp[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        temp[i][j].rgbtGreen = check;
                    }
                }
            }
        }
    }
    
    // Put temp color value into image
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = temp[k][l];
        }
    }
    return;
}