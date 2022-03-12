#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Initialise
    int ban = -1;

    // Start record
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // Initialise
        int reverse = candidate_count - 1;
        bool loop = true;

        // Update preferences[winner][loser] if candidate(winner) get one vote
        for (int number = 0; loop == true; number++)
        {
            if (ranks[i] == number)
            {
                do
                {
                    if (reverse != number && reverse != ban)
                    {
                        preferences[number][reverse] += 1;
                    }
                    reverse--;
                }
                while (reverse > -1);
                loop = false;
            }
            ban = ranks[0];
        }

    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Initialise
    int x = 0, y = 1;
    pair_count = candidate_count * (candidate_count - 1) / 2;
    bool test = true;
    int k = 1, counter = 0;

    // Record total pair, ignore tie
    for (int i = 0; i < pair_count; i++)
    {
        if (pair_count == counter)
        {
            pair_count = i;
            return;
        }

        // Initialise
        test = true;

        // Update winner and loser according to total vote get
        do
        {
            if (preferences[x][y] > 0)
            {
                if (preferences[x][y] > preferences[y][x])
                {
                    pairs[i].winner = x;
                    pairs[i].loser = y;
                    test = false;
                    counter++;
                }
                else if (preferences[x][y] < preferences[y][x])
                {
                    pairs[i].winner = y;
                    pairs[i].loser = x;
                    test = false;
                    counter++;
                }
                // Tie, ignore specific_pair
                else if (preferences[x][y] == preferences[y][x])
                {
                    if (i < 0)
                    {
                        i = -1;
                    }
                    else
                    {
                        i--;
                    }
                    test = false;
                    counter++;
                }
            }

            // Increment of x and y
            if (x < candidate_count)
            {
                if (y + 1 < candidate_count)
                {
                    y++;
                }
                else
                {
                    x++, k++;
                    y = k;
                }
            }
            else
            {
                test = false;
            }
        }
        while (test == true);
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Initialise
    int pair_power[pair_count];
    int descending[pair_count];
    pair strength[pair_count];
    int x = 0, y = 0, counter = 0, temp = 0;

    // Initialise array
    for (int r = 0; r < pair_count - 1; r++)
    {
        pair_power[r] = 0;
        descending[r] = 0;
        strength[r].winner = 0;
        strength[r].loser = 0;
    }

    // Set array with pair_winner and loser
    for (int i = 0; i < pair_count; i++)
    {
        x = pairs[i].winner, y = pairs[i].loser;

        pair_power[i] = preferences[x][y];
        strength[i].winner = x;
        strength[i].loser = y;
    }

    // Sorting Process
    for (int many = 0; many < pair_count; many++)
    {
        descending[many] = pair_power[many];
    }

    // Bubble sort is used
    do
    {
        for (int i = 0; i < pair_count; i++)
        {
            counter = 0;

            if (i == pair_count - 1)
            {
                int smallest = MAX;
                for (int j = 0; j < pair_count; j++)
                {
                    if (pair_power[j] < smallest)
                    {
                        smallest = pair_power[j];
                        descending[i] = pair_power[j];
                    }
                }
            }
            else
            {
                if (descending[i] < descending[i + 1])
                {
                    temp = descending[i];
                    descending[i] = descending[i + 1];
                    descending[i + 1] = temp;
                    counter++;
                }
            }
        }
    }
    // Sort until no more changes in number
    while (counter != 0);

    // Replace sorted number into pair_winner and loser
    bool test;
    for (int i = 0; i < pair_count; i++)
    {
        test = true;
        for (int j = 0; test == true; j++)
        {
            if (descending[i] == pair_power[j])
            {
                pairs[i].winner = strength[j].winner;
                pairs[i].loser = strength[j].loser;
                pair_power[j] = -1;
                test = false;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Initialise
    int x = 0, y = 0;
    int digit[candidate_count];
    int record[pair_count];
    int record1[pair_count];
    bool loop = true, test = false;

    for (int i = 0; i < candidate_count; i++)
    {
        digit[i] = 0;
    }

    // Check if middle loop
    for (int i = 0; i < pair_count; i++)
    {
        x = pairs[i].winner;
        y = record[i] =  pairs[i].loser;
        record1[i] = pairs[i + 1].winner;
        test = false;
        loop = true;

        if (record[i] == record1[i])
        {
            for (int k = i - 1; k > -1 && test == false; k--)
            {
                if (y == pairs[k].winner)
                {
                    test = true;
                }
            }
        }

        // If no loop, locked pair
        if (test == false)
        {
            locked[x][y] = true;
            digit[y] = 1;
        }

        // Step drop final pair if no single majority
        if (i + 1 != pair_count && test == false)
        {
            for (int j = pairs[i + 1].loser; j < candidate_count && loop == true; j++)
            {
                if (digit[y] == digit[j])
                {
                    return;
                }
                loop = false;
            }
        }
        else if (test == false)
        {
            locked[x][y] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Initialise
    int x = 0, y = 0, counter = 0;
    bool loop;

    // Determine winner if is single majority
    for (int i = 0; i < pair_count; i++)
    {
        loop = true;
        counter = 0;
        x = pairs[i].winner;
        y = pairs[i].loser;

        for (int j = y; (j < pair_count) && (loop == true); j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (locked[k][j] == true)
                {
                    counter++;
                }
            }
            if (counter == 0)
            {
                loop = false;
            }
        }

        // Print single majority winner
        if (counter == 0)
        {
            printf("%s\n", candidates[y]);
            sleep(1);
            return;
        }
    }

    // Print winner that ignore pair
    for (int i = 0; i < candidate_count; i++)
    {
        counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                counter++;
            }
        }

        if (counter == 0)
        {
            printf("%s\n", candidates[i]);
            sleep(1);
            return;
        }
    }
    return;
}