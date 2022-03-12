#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}





// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}





// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Initialise
    int j = 0;
    
    // Count time for eliminate progress
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            j += 1;
        }
    }
    
    // Initialise 2
    bool test = true, test1 = false;
    int ranking[candidate_count];
    int rank;

    // Test for how many tabulate loop
    for (int i = candidate_count - 1; i > -1 && test1 == false; i--)
    {
        if (ranking[i] == 1)
        {
            rank = i;
            test1 = false;
        }
    }
    
    // Start record data one by one
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            for (int k = 0; k < voter_count; k++)
            {
                if (preferences[k][0] == i)
                {
                    candidates[i].votes += 1;
                }
            }
        }
        
        else
        {
            int counter = 0, l = rank;
            test = true;
            
            for (int k = 0; k < voter_count && test == true; k++)
            {
                test = true;
                if (preferences[k][l] == i)
                {
                    for (int b = 0; b < candidate_count && test == true; b++)
                    {
                        if (preferences[k][l + 1] == b && candidates[b].eliminated == false)
                        {
                            candidates[b].votes += 1;
                            test = false;
                        }
                    }
                    if (test == true)
                    {
                        for (int a = 0; a < candidate_count && test == true; a++)
                        {
                            if (preferences[k][l + 2] == a)
                            {
                                candidates[a].votes += 1;
                                test = false;
                            }
                        }
                    }
                }
            }
        }
    }
    bool loop = true;
    ranking[0] = 1;
    for (int i = 0; i < candidate_count && loop == true; i++)
    {
        if (ranking[i] == 1)
        {
            ranking[i + 1] = 1;
            loop = false;
        }
    }
    return;
}





// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Loop to find majority winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > (voter_count / 2))
            {
                printf("%s\n", candidates[i].name);
                return true;
            }
        }
        
    }
    return false;
}





// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialise
    int smallest = MAX_CANDIDATES;

    // Loop find smallest number among uneliminated
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            if (candidates[j].votes < smallest)
            {
                smallest = candidates[j].votes;
            }
        }

    }
    return smallest;
}





// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Initialise
    int counter = 0, same = 0;

    // Check whether is tie
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            counter++;
        }
    }

    for (int i =  0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            same++;
        }
    }
    
    // If tie exist
    if (same == counter)
    {
        return true; 
    }
    
    // Tie dont have
    return false;
}





// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loop find smallest number 
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == min)
        {
            candidates[j].eliminated = true;
        }
    }
    return;
}
