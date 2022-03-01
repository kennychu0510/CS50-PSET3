#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
            
            /*test
            printf("passed in rank: %i\n", rank);
            printf("rank: ");
            for (int k = 0; k < candidate_count; k++)
            {
                printf("%i ", ranks[k]);
            }
            printf("\n");
            */
            
            return true;
        }
    }
    

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; 
            
            /*testing
            printf("i: %i\n", i);
            printf("rank[i]: %i\n", ranks[i]);
            printf("j: %i\n", j); 
            printf("preference: \n");
            for (int k = 0; k < candidate_count; k++)
            {
                for (int l = 0; l < candidate_count; l++)
                {
                    printf("%i ", preferences[k][l]);
                }
                printf("\n");
            }
            printf("\n\n"); */
        }
    }
    
    /*test
    printf("rank: ");
    for (int k = 0; k < candidate_count; k++)
    {
        printf("%i ", ranks[k]);
    }
    
    
    
    printf("candidate count: %i\n", candidate_count);
    printf("pair count: %i\n", pair_count);
    */
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
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
    int swaps = 1;
    int n = 1;
    
    while (swaps != 0)
    {
        swaps = 0;
        
        for (int i = 0; i < pair_count - n; i++)
        {
            int j = i + 1;
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                swaps++;
                pair temp_pair = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp_pair;
            }
            
        }
        n++;
    }
    
    /*
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair %i\n", i+1);
        printf("Winner: %i\n", pairs[i].winner);
        printf("Loser: %i\n", pairs[i].loser);
    }*/
    
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        
        int start_i = pairs[i].winner;
        int start_j = pairs[i].loser;
        int current_i = pairs[i].winner;
        int current_j = pairs[i].loser;
        
        do
        {
             if (locked[current_i][current_j] == true)
             {
                 current_i = 
             }
        }while (locked[pairs[j].winner][pairs[j].loser] != false);
        
        
        
        
    }
    
    int last_winner = pairs[pair_count-1].winner;
    int last_loser = pairs[pair_count-1].loser;
    
    
    printf("locked graph before last: \n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    
    int true_count = 0;
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[i][last_loser] == true || locked[last_winner][i] == true)
        {
            true_count++;
        }
    }
    if (true_count > 0)
    {
        locked[pairs[pair_count-1].winner][pairs[pair_count-1].loser] = true;
    }
    
    
    printf("locked graph after last: \n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    
    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            false_count++;
        }
        if (false_count == candidate_count)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}

