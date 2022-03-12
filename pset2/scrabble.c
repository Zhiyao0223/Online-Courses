#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Assign points to alphabet
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string text);
char lowercase(char w);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    
    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    
    // Print the winner
    if (score1 != score2)
    {
        if (score1 > score2)
        {
            printf("Player 1 wins!\n");
        }
        else
        {
            printf("Player 2 wins!\n");
        }
    }    
    else
    {
        printf("Tie!\n");
    }
}





int compute_score(string text)
{
    // Initialise sum
    int sum = 0;
    
    // Change every different char
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Initialise array and Assign value to z
        int arr = 0;
        char z = lowercase(text[i]);
    
        // Check for suitable char
        for (char alpha = 'a'; alpha <= 'z'; alpha++, arr++)
        {
            if (z == alpha)
            {
                sum = sum + points[arr];
            } 
        }
    }
    return sum;
}




// Make vocab lowercase
char lowercase(char w)
{
    if (w >= 'A' && w <= 'z')
    {
        char c = tolower(w);
        return c;
    }
    return w;
}
