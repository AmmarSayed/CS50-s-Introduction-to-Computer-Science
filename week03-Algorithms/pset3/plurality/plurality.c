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
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates names
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

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote else record the vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        // if roblem with the name
        if (strcmp(name, candidates[i].name) == 0)
        {
            // increase the vote of the candidate
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // avariable to record the biggest score all over the candidates
    int count_votes = 0;
    string winner_name;

    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate score is bigger, then re assign the value of count_votes
        if (candidates[i].votes > count_votes)
        {
            count_votes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // check who's the winner based on count_votes
        if (candidates[i].votes == count_votes)
        {
            printf("%s", candidates[i].name);
            printf("\n");
        }
    }
    return;

}

