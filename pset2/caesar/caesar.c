#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int validcheck(int integer, string number[]);
char encrypt(char character, int keys, int wordcount);
int findkey(string digit[], int length);

int main(int argc, string argv[])
{
    // Initialise
    int word = 0;
    int key = 0;
    
    // Check input validity
    int test = validcheck(argc, argv);
    
    // Error 1: Invalid input
    if (test == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Variable for input length
    int length = strlen(argv[1]);

    // Change input string to int
    key = findkey(argv, length);

    // Prompt text
    string plain = get_string("plaintext: ");

    // Text length
    word = strlen(plain);
    
    // Create variable based on word length
    char cipher[word];


    // Seperate text char one by one
    for (int i = 0; i < word; i++)
    {
        cipher[i] = encrypt(plain[i], key, word);
    }

    // Output
    printf("ciphertext: ");

    // Print encrypted word one by one
    for (int i = 0; i < word; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");

    return 0;
}





// To check for input validity
int validcheck(int integer, string number[])
{
    // Normally input will be 2 int
    if (integer != 2)
    {
        return 1;
    }

    // Initialise
    int n = 0;

    n = strlen(number[1]);

    // Loop check for any invalid input
    for (int i = 0; i < n; i++)
    {
        bool test = isdigit(number[1][i]);

        if (test == false || number[1][i] < 0)
        {
            return 1;
        }
    }
    return 0;
}





// Encryption start 
char encrypt(char character, int key, int wordcount)
{
    // Initialise
    char alpha = 'a';
    char alpha2 = 'A';
    char protect = ' ';
    
    // Test if required convert
    bool test = isalpha(character);

    if (test == true)
    {
        // Check for similarity 
        for (int i = 0; i < 26; i++, alpha++, alpha2++)
        {
            if (character == alpha || character == alpha2)
            {
                bool test1 = islower(character);
                int temp = (int) character + key;
                char temp1 = ' ';

                if (temp > 90 && temp < 97)
                {
                    temp1 =  'A' + ((temp - 65) % 26);
                    return temp1;
                }

                if (temp > 122)
                {
                    temp1 = 'a' + ((temp - 97) % 26);
                    return temp1;
                }

                if (test1 == false && temp > 97)
                {
                    temp1 = 'A' + ((temp - 65)  % 26);
                    return temp1;
                }

                protect = (int) character + key;
                return protect;
            }
        }
    }

    return character;
}





// Formula to convert string input to int
int findkey(string digit[], int length)
{
    // Initialise
    int counter = 1;
    int sum = 0;
    int multi = 0;

    // In case input is 2 digit or more
    for (int c = 0, x = 1; c < length; c++, x *= 10)
    {
        bool test = isdigit(digit[1][c]);

        if (test == true)
        {
            counter *= x ;
        }
    }
    
    // Convert string to int manually
    for (int i = 0; counter > 0; i++, counter /= 10)
    {
        int c = 0;
        bool condition = false;

        for (char w = '0'; condition == false && w <= '9'; w++)
        {
            if (digit[1][i] == w)
            {
                sum += (c * counter);
                condition = true;
            }
            c++;
        }

    }

    return sum;
}