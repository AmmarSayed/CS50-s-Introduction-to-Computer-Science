#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
float index_func(int w_t, int l_t, int s_t);
int count_letters(string u_t);
int count_sentences(string u_t);
int count_words(string u_t);


int main(void)
{
    // Receieve the text from the user
    string text = get_string("Text: ");


// run the test on the text
    int letters = count_letters(text);

    int sentences = count_sentences(text);

    int words = count_words(text);


    // grade formula will run here
    int x = index_func(words, letters,  sentences);

    if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (x > 16)
    {
        printf("Grade 16+\n");

    }
    else
    {
        printf("Grade %i\n", x);
    }


}

int count_letters(string u_t)  // function to count number of letters
{
    //u_t is the user input text
    int count = 0;

    //looping through characters
    for (int i = 0, n = strlen(u_t); i < n; i++)
    {
        //checking if a character a to z or A to Z
        if (u_t[i] >= 'a' && u_t[i] <= 'z')
        {
            count ++;
        }
        else if (u_t[i] >= 'A' && u_t[i] <= 'Z')
        {
            count ++;
        }
    }

    return count;
}

int count_sentences(string u_t)  // function to count number of sentences
{
    //u_t is the user input text
    int count = 0;

    //looping through characters
    for (int i = 0, n = strlen(u_t); i < n; i++)
    {
        //checking if a character a to z or A to Z
        if (u_t[i] == '.' || u_t[i] == '?' || u_t[i] == '!')
        {
            count ++;
        }
    }
    return count;
}

int count_words(string u_t)  // function to count number of words
{
    //u_t is the user input text
    int count = 0;

    //looping through characters
    for (int i = 0, n = strlen(u_t); i < n; i++)
    {
        //checking if a character a to z or A to Z
        if (u_t[i] == ' ')
        {
            count ++;
        }
    }
    return count + 1;

}


float index_func(int w_t, int l_t, int s_t)
{
    // w_t is number of words in the text
    // l_t is number of letters in the text
    // s_t is number of sentences in the text

    //L is the average number of letters per 100 words in the text.
    float L = 100.00 / w_t * l_t;

    //S is the average number of sentences per 100 words in the text.
    float S = 100.00 / w_t * s_t;
    //Coleman-Liau index of the text
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return round(index);
}

