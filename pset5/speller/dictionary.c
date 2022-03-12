// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Define backslash zero
#define NUL '\0'

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table, 4100 derived from Z in ASCII is 90 * 45words
const unsigned int N = 4100;

// Hash table
node *table[N];

// Calculate dictionary size
int dic_vocab = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Initialise
    char temp[46] = {'\0'};
    
    // Convert char to uppercase to meet my hash condition
    for (int i = 0; i < strlen(word); i++)
    {
        temp[i] = toupper(word[i]);
    }
    
    // Find hash value
    int hash_value = hash(temp);
    
    // Redirect to the table of specific value
    node *n = table[hash_value];
    
    // Lower every word in the notepad, prevent error
    for (int j = 0; j < strlen(word); j++)
    {
        temp[j] = tolower(word[j]);
    }
    
    // Compare two element with the same value 
    while (n != NULL)
    {
        if (strcasecmp(temp, n->word) == 0)
        {
            return true;
        }
        
        // Continue the link if hash value same but word not
        n = n->next;
    }
    
    // Return typo if cant find any
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialise
    char chac = '\0';
    int sum = 0, i = 0;

    // Create a loop to find total sum of ASCII
    do
    {
        for (int j = 65; j <= 90; j++)
        {
            // If same, break to prevent overloop
            if (word[i] == j)
            {
                sum += j;
                i++;
                break;
            }
            
            // Counter symbol scenario
            else if (word[i] < 65 || word[i] > 90)
            {
                i++;
                break;
            }
        }
    } 
    while (i < strlen(word));

    // Make sure value is within big N
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *files = fopen(dictionary, "r");

    // Return if empty
    if (files == NULL)
    {
        printf("Could not open %s", dictionary);
        return -1;
    }

    // Initialise
    char words[46] = {'\0'};
    char temp = '\0';

    // Read word till the end of the file
    while (fscanf(files, "%s", words) != EOF)
    {
        // Create a node for each word
        node *n = malloc(sizeof(node));
        
        // In case of no memory
        if (n == NULL)
        {
            printf("Insufficient memory\n");
            free(n);
            return false;
        }

        // Copy the word from dictionary to node
        strcpy(n->word, words);

        // Convert uppercase for hash
        for (int i = 0; words[i] != '\0'; i++)
        {
            temp = toupper(words[i]);
            words[i] = temp;
        }
        int hash_value = hash(words);
        
        // Redirect node to the table with same hash value
        n->next = table[hash_value];
        table[hash_value] = n;
        dic_vocab++;
    }

    fclose(files);
    return true;

    // Adapted from https://joseph28robinson.medium.com/cs50-pset-5-speller-f9c89d08237e
    // Bcz I dont understand what a hash is.. After much explanation, still blur. So, I took a glance on the code from the link to get an idea.
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return total count of dictionary vocab
    return dic_vocab;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop is required to free all table memory
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        
        // Clear every vocab in each table node
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        free(n);
        
        // Return if everything is settle, prevent overloop
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    
    return false;
}
