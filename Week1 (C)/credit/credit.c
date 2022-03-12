#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checksum(long num);
string checklength(long num1);

int main(void)
{
    // Initialise boolean 
    bool boolean = false;
    
    // Input credit card number
    long number = get_long("Please inset your credit card number (exclude hypen) :");

    // Formula calculate valid for sum   
    boolean = checksum(number);
    
    // Formula to count long length
    if (boolean == true)
    {
        string test = checklength(number);
        
        printf("%s\n", test);
    }
    
    else
    {
        printf("INVALID\n");
    }
}




// Used to count sum every 2 digits
bool checksum(long num)
{
    // Initialise 
    int sum = 0;
    int sum1 = 0;
    int remain[17] = {0};
    
    // Count total sum for whole length
    for (int i = 0; num > 0 ; i++)
    {
        remain[i] = num % 10;
        num /= 10;
        
        if (i % 2 != 0)
        {
            int x, y = 0;
            
            if (remain[i] * 2 > 9)
            {
                x = (remain[i] * 2) % 10;
                y = (remain[i] * 2) / 10;
                
                sum = sum + x + y;
            }
            
            else
            {
                sum = sum + (remain[i] * 2);
            }
        }
        else 
        {
            sum1 += remain[i];
        }
        
    }
    sum = sum + sum1;
    
    // Check if sum divisible by 10
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}




// Used to check long length
string checklength(long num1)
{
    // Initialise
    int i = 0;
    long num_ori = num1;
    
    // Calculate word length
    do
    {
        num_ori /= 10;
        i++;
    }
    while (num_ori > 0);    
    
    // For Visa and Mastercard
    if (i == 13 || i == 16) 
    {
        long remain = 0;
        remain = num1;
        
        for (int c = 0; remain > 100; c++)
        {
            remain /= 10;
        }
        
        if (remain == 51 || remain == 52 || remain == 53 || remain == 54 || remain == 55)
        {
            return "MASTERCARD";
        }
        
        remain /= 10;
        
        if (remain == 4)
        {
            return "VISA";
        }
    }
    
    // For AMEX
    if (i == 15)
    {
        long remain1 = 0;
        remain1 = num1;
        
        for (int c = 0; remain1 > 100; c++)
        {
            remain1 = remain1 / 10;
        }
        
        if (remain1 == 34 || remain1 == 37)
        {
            return "AMEX";
        }
    }
    
    // Do not meet requirement
    return "INVALID";
}
