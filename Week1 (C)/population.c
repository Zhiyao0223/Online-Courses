#include <stdio.h>
#include <cs50.h>

int main()
{
    // variable for size
    int start, end, counter, year;
    
    // minimum size with condition
    do
    {
        start = get_int("Start size: ");
        
    }
    while (start < 9);
    
    //maximum size with condition
    do 
    {
        end = get_int("End size: ");
    }
    while (end < start);
    

    //initialise counter and
    counter = 0;


    //calculation start ayy
    for (year = start; year < end; counter++)
    {
        year = year + (year / 3) - (year / 4);
    }
    
    //print counter
    printf("Years: %i", counter);
    
}