#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count ; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //sort_count is how many elements are swapped in the bubble sort algorithm
    int sort_count = 1;
    //swap variables are placeholders for the bubble sort swap values
    int swap_winner = 0;
    int swap_loser = 0;
    //loop continues until no swaps are made in bubble sort
    while (sort_count != 0)
    {
        //resets sort_count after each iteration
        sort_count = 0;
        for (int i = 0; i < candidate_count - 1; i++)
        {
            //finds the strength of victory for two pairs and swaps them as needed
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                swap_winner = pairs[i].winner;
                swap_loser = pairs[i].loser;
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = swap_winner;
                pairs[i + 1].loser = swap_loser;
                sort_count++;
            }
        }
        int i = 0;
    }
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int k = 0;
        for (int j = i; j >= 0; j--)
        {
            if (pairs[i].loser != pairs[i - j].winner)
            {
                k++;
            }
            if (k == i + 1)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int losercount[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        losercount[i] = 0;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == true)
        {
            losercount[pairs[i].loser]++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (losercount[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;

}


