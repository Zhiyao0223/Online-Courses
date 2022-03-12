#include <stdio.h>
#include <cs50.h>

// Global
int main(void)
{
    // Formula to check range 
    int n;
    
    do
    {
        n = get_int("Height:");
    }
    while (n > 8 || n < 1);

    // Left pyramid
    // Make a loop 
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (x + y >= n - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        // Middle blank
        for (int space = 0; space < 2; space++)
        {
            printf(" ");
        }

        // Right
        for (int a = n; a >= n - x; a--)
        {
            printf("#");
        }
    
        printf("\n");
    }
}