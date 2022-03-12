#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int validcheck(int integer, string key);
char encrypt(char word, char key[], char key1[]);

int main(int argc, string argv[])
{
    // Initialise
    char key[26] = {' '};
    char key1[26] = {' '};
    int word = 0;
    
    // Check input validity
    int test = validcheck(argc, argv[1]);
    
    // Error: Exisiting of char other than alphabet
    if (test == 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // Error: Insufficient char
    if (test == 1)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    // Encryption key (Both lower and uppercase)
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(argv[1][i]);
        key1[i] = tolower(argv[1][i]);
    }


    // Prompt plain text
    string plain = get_string("plaintext: ");


    // Encryption Process
    word = strlen(plain);
    char cipher[word];
    
    for (int i = 0; i < word; i++)
    {
        cipher[i] = encrypt(plain[i], key, key1);
    }
    

    // Print ciphertext (Output)
    printf("ciphertext: ");
 
    // Print char one by one
    for (int i = 0; i < word; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");

    return 0;
}





// Check validity of input insert
int validcheck(int integer, string key)
{
    // Initialise
    int sum = 0;
    int c1 = 0;
    char character[26] = {' '};
    
    // Check for input. No input inserted result 'interger' == 1
    if (integer == 2)
    {
        int length = strlen(key);
        
        for (int c = 0; c < length; c++)
        {
            if (c1 < 1)
            {
                bool test = isalpha(key[c]);
                
                // Check for first char if is alphabet
                if (test == false)
                {
                    return 1;
                }
                c1++;
            }
            
            bool test1 = isalpha(key[c]);
        
            // Check for remaining input as an alphabet
            if (test1 == false)
            {
                return 1;
            }
            
            sum += 1;
        }
        
        // Check for duplicate char. TRUE: return 'Insufficient char'
        for (int i = 0; i < length; i++)
        {
            for (int length1 = length - 1; length1 != i; length1--)
            {
                if (key[i] == key[length1])
                {
                    return 1;
                }
                if (i != 0)
                {
                    for (int length2 = 0; length2 != i; length2++)
                    {
                        if (key[i] == key[length1])
                        {
                            return 1;
                        } 
                    }
                }
            }
        }
    
    
        // Insufficient char
        if (sum > 0 && sum < 25)
        {
            return 1;
        }
        
        // Sufficient char and meet requirement
        if (sum == 26)
        {
            return 0;
        }
    }
    // Invalid input
    return 2;
}





// Encrypt process
char encrypt(char word, char key[], char key1[])
{
    // Initialise
    char cipher1 = ' ';
    char start = 'a';
    char start1 = 'A';
    
    // Test for alphabet. Ignore char if 'false'
    bool test = isalpha(word);

    if (test == true)
    {
        for (int c = 0; c < 26; c++, start++, start1++)
        {
            if (word == start)
            {
                cipher1 = key1[c];
                return cipher1;
            }
                    
            if (word == start1)
            {
                cipher1 = key[c];
                return cipher1;
            }
        }
    }
    
    // Return non-alphabet
    return word;
}
