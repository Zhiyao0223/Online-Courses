#include <stdio.h>
#include <cs50.c>
#include <math.h>

int main(void)
{
    double input = 0;
    int cent = 0, temp = 0, total = 0, remainding = 0;
    
    do
    {
        input = get_float("Change owed: ");    
    }
    while (input < 0);
    
    cent = round((float) input * 100);
    
    // Prevent 0
    if (cent != 0)
    {
        // Calculate number of 25
        temp = floor(cent / 25);
        total += temp;
        remainding = cent % 25; 
    
        // Calculate number of 10
        if (remainding != 0)
        {
            temp = floor(remainding / 10);
            total += temp;
            remainding %= 10;
        }   
    
        // Calculate number of 5 and 1
        if (remainding != 0)
        {
            temp = floor(remainding / 5);
            total += temp + (remainding % 5);
        }
    }
    
    
    printf("%i %i\n", cent, total);
}