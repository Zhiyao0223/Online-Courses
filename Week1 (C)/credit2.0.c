#include <ctype.h>
#include <stdio.h>
#include <string.h>

char validitycheck(long num);

int main(void)
{
    /*
    This system can help in differenciate counterfeit credit card with the name of Visa, Mastercard and American Express(AMEX)
    Two steps need to be taken for checking
    
    1.  (Harkness, 2020)
        The first digit is different for each card network: Visa cards – Begin with a 4 and have 13 or 16 digits
                                                            Mastercard cards – Begin with a 5 and has 16 digits
                                                            American Express cards – Begin with a 3, followed by a 4 or a 7  has 15 digits
        
    2.      Most credit card ultilize Luhn algorithm
    
    Card type will be displayed if is valid
    */
    
    // Initialise variable
    long number = 0;

    // Input credit card number
    printf("Please inset your credit card number (exclude hypen) :");
    scanf("%ld", &number);

    // Checkc validity of card   
    char card_type = validitycheck(number);
    
    // Print card name (Visa, Mastercard, AMEX)
    if (card_type == 'v')
    {
        printf("Card type: Visa\n");
    }    
    else if(card_type == 'm')
    {
        printf("Card type: Mastercard\n");
    }
    else if (card_type == 'a')
    {
        printf("Card type: AMEX\n");
    }
    else
    {
        printf("INVALID CARD\n");
    }
    
    return 0;
}





char validitycheck(long num)
{
    // Initialise 
    int sum = 0, sum1 = 0, i = 0;
    int remaining[17] = {0};
    long temp = num;
    
    // Count total sum for whole credit card digit
    do 
    {
        remaining[i] = temp % 10;
        temp /= 10;
        
        if (i % 2 != 0)
        {
            int x = 0, y = 0;
            
            if (remaining[i] * 2 > 9)
            {
                x = (remaining[i] * 2) % 10;
                y = (remaining[i] * 2) / 10;
                
                sum = sum + x + y;
            }
            
            else
            {
                sum = sum + (remaining[i] * 2);
            }
        }
        else 
        {
            sum1 += remaining[i];
        }
        i++;

    } while (temp > 0);
    
    sum += sum1;
    
    // Check if sum divisible by 10, else return
    if (sum % 10 != 0)
    {
        return i;
    }

    // For Visa and Mastercard
    if (i == 13 || i == 16)
    {
        long remain = 0;
        remain = num;

        for (int c = 0; remain > 100; c++)
        {
            remain /= 10;
        }

        if (remain >= 51 && remain <= 55)
        {
            return 'm';
        }

        remain /= 10;

        if (remain == 4)
        {
            return 'v';
        }
    }

    // For AMEX
    else if(i == 15)
    {
        long remain1 = 0;
        remain1 = num;

        for (int c = 0; remain1 > 100; c++)
        {
            remain1 = remain1 / 10;
        }

        if (remain1 == 34 || remain1 == 37)
        {
            return 'a';
        }
    }

    // Do not meet requirement
    return 'i';
}
