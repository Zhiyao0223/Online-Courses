#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string names, candidate candidate_info[], int voter_count, int candidate_counts);
int print_winner(string vote_name[], candidate candidates_info[], int voter_count, int candidate_no);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");
    string names[voter_count];
    
    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        // Check for invalid vote
        names[i] = get_string("Vote: ");
            
        if (!vote(names[i], candidates, voter_count, candidate_count))
        {
            printf("Invalid vote.\n");
        }
    }

    // Select and Display winner of election
    print_winner(names, candidates, voter_count, candidate_count);
    return 0;
}





// Check for vote validity
bool vote(string names, candidate candidate_info[], int voter_count, int candidate_counts)
{
    
    for (int i = 0; i < candidate_counts; i++)
    {
        if (strcmp(names, candidate_info[i].name) == 0)
        {
            return true;
        }
    }
    return false;
}





// Determine and Print the winner (or winners) of the election
int print_winner(string vote_name[], candidate candidates_info[], int voter_count, int candidate_no)
{
    string winner[voter_count];
    
    for (int i = 0; i < voter_count; i++)
    {
        bool stoploop = false;
        
        for (int c = 0; c < candidate_no || stoploop == false; c++)
        {
            if (strcmp(vote_name[i], candidates[c].name) == 0)
            {
                candidates_info[c].votes++;
                stoploop = true;
            }
        }
    }
    
    int x = -1;
    int i = 0;
    
    for (int counter = 0; counter < candidate_no; counter++)
    {
        if (candidates[counter].votes > x)
        {
            i = 0;
            x = candidates_info[counter].votes;
            winner[i] = candidates_info[counter].name;
            
        }
        
        else if (candidates[counter].votes == x)
        {
            i++;
            winner[i] = candidates[counter].name;
        }
    }
    
    for (int y = 0; y <= i; y++)
    {
        printf("%s\n", winner[y]);
    }
    
    return 0;
}