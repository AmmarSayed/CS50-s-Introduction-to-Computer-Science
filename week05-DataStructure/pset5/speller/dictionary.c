// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"

unsigned int count_word = 0; // to be used in size function
const unsigned int N = 100000; // Number of buckets in hash table

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table
node *Hash_table[N] = {NULL};


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file, read only mode,and check if NULL
    FILE *file_ptr = fopen(dictionary, "r");
    if (file_ptr == NULL)
    {
        return false;
    }

    // Create a buffer array to store words from the dictionary
    char dictWord [LENGTH + 1];

    // read strings from file one at , and load words into the hash table
    while (fscanf(file_ptr, "%s", dictWord) != EOF)
    {
        for (int i = 0, n = strlen(dictWord); i < n; i++)
        {
            dictWord[i] = tolower(dictWord[i]);
        }

        count_word ++; // counting number of words we've scanned

        // create a new node for each word we found in dictWord
        node *n_word = malloc(sizeof(node));

        if (n_word != NULL)
        {
            strcpy(n_word->word, dictWord); // store the dictWord in n_word
        }


        // Hash word to obtain a hash value for dictWord
        int i = hash(dictWord);

        // store the n_word into the table
        if (Hash_table[i] == NULL) // Is this the first word?
        {
            Hash_table[i] = n_word;
            n_word->next = NULL;
        }
        else
        {
            // insert node into hash table at that location by hash function, change where the head of the list is
            n_word->next = Hash_table[i];
            // then make the list equal to the new word, so it's now added to the begining of the chain
            Hash_table[i] = n_word;
        }
    }
    fclose(file_ptr);
    return true;
}

// Hashes word to a number
// https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (count_word > 0)
    {
        return count_word;
    }
    return false;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char tmp [LENGTH + 1];
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        strcpy(tmp, word);
    }

    for (int i = 0, n = strlen(tmp); i < n; i++)
    {
        tmp[i] = tolower(tmp[i]);
    }

    // hash the word to obtain a hash value
    int h = hash(tmp);

    // Access linked list at the index in the hash table
    if (Hash_table[h] == NULL)
    {
        return false;
    }

    // cursor to compare words
    node *cursor = Hash_table[h];// cursor = to the first element of the array

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, tmp) == 0)
        {
            return true; // if you find the word, return true
        }
        cursor = cursor->next; // move cursor to the next node
    }

    return false; // return false because nothing found above
    free(cursor);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // curser
    node *cursor = Hash_table[0];

    //loop thourgh the hash table
    for (int i = 0; i < N; i++)
    {
        while (Hash_table[i] != NULL)
        {
            cursor = Hash_table[i] ;
            Hash_table[i] = cursor->next;
            free(cursor);
        }
    }
    return true;
}
