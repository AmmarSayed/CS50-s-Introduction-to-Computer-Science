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
    //Looping through the name to check if matching a candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0) //check if given name is existing candidate
        {
            //store the index of the candidate who is the jth ranked preference for the ith voter.
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Update votes for non-eliminated candidates
void tabulate(void)
{
    //iterate through voter count
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        //check the candidate in the rank if eliminated
        while (candidates [preferences[i][j]].eliminated == true)
        {
            j++; // if eliminated move to the next rank
        }
        candidates [preferences[i][j]].votes++; // add vote to the candidate
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int total_votes = 0; //intiate the total_votes with 0
    //iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        total_votes = candidates [i].votes + total_votes; // Adding votes to the total votes
    }
    int half_votes = total_votes / 2; // finding half of the votes

    for (int i = 0; i < voter_count; i ++)
    {
        // checking if the vote of candidate is more than half votes
        if (candidates [i].votes > half_votes)
        {
            printf("%s\n", candidates [i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = candidates [0].votes; // Set the fist vote as minmum
    // Loop through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the vote is less than the mi_vote & greater than 0
        if (min_votes > candidates [i].votes && candidates [i].eliminated == false)
        {
            min_votes = candidates [i].votes; // Then store the value in votes inside the min_votes
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int can_in_election = 0; // counter of candidates still in the election
    int can_min_votes = 0; // counter of candidates has the fewest number of votes

    // loop through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates [i].eliminated) // check if a candidate is not eliminated
        {
            can_in_election ++; // if not , update  in election
        }
        if (candidates [i].votes == min) // check if candidate votes equal to minimum votes
        {
            can_min_votes ++; // if yes, update the counter of min votes with 1
        }
    }
    // compare both counter of min votes with candidates in the election
    if (can_in_election == can_min_votes)
    {
        return true; // if they're equal, so return true
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // loop through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates [i].eliminated && candidates [i].votes == min)
        {
            candidates [i].eliminated = true;
        }
    }
    return;
}
