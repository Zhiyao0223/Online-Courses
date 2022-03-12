#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int countletter(string texts);
int countword(string text0);
int countsentence(string text1);
int formula(int l, int w, int s);

int main(void)
{
    // Initialise
    int letters = 0;
    int words = 0;
    int sentences = 0;
    
    // Prompt for string
    string text = get_string("Text: ");
    
    // Prepare for calculate formula
    letters = countletter(text);
    words = countword(text);
    sentences = countsentence(text);

    // Formula count grade
    int formula1 = formula(letters, words, sentences);
    
    // Output
    if (formula1 > 16)
    {
        printf("Grade 16+\n");
    }
    
    if (formula1 < 1)
    {
        printf("Before Grade 1\n");
    }
    
    if (formula1 >= 1 && formula1 <= 16)
    {
        printf("Grade %i\n", formula1);
    }
}




// Count all letters in string
int countletter(string texts)
{
    int lettersum = 0;
    
    for (int i = 0; texts[i] != '\0'; i++)
    {
        bool test0 = isalpha(texts[i]);
        
        if (test0 == true)
        {
            lettersum += 1;
        }
    }
    return lettersum;
}




// Count all words in string
int countword(string text0)
{
    int wordsum = 0;
    
    for (int i = 0; text0[i] != '\0'; i++)
    {
        if (text0[i] == ' ')
        {
            wordsum += 1;
        }
    }
    return wordsum + 1;
}




// Count all sentences in string
int countsentence(string text1)
{
    int stringsum = 0;
    
    for (int i = 0; text1[i] != '\0'; i++)
    {
        if (text1[i] == '.' || text1[i] == '!' || text1[i] == '?')
        {
            stringsum += 1;
        }
    }
    return stringsum;
}




// Count grade
int formula(int l, int w, int s)
{
    double index = 0;
    double L = 0;
    double S = 0;
    
    L = (double)l /  w * 100.0;
    S = (double)s /  w * 100.0;
    
    index = 0.0588 * L - (0.296 * S) - 15.8;
    
    int index1 = round(index);
    
    return index1;
}