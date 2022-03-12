#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Initialise
    int n;
    
    // Prompt input
    do
    {
        n = get_int("Height: "); 
    }
    while (n < 1 || n > 8);
    
    // Loop to display # and ' '
    for (int i = 1; i <= n; i++)
    {
        int y;
        int x;
        
        for (y = 0; y < n - i ; y++)
        {
            printf(" ");
        }
        
        for (x = 0; x < i; x++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}