/*Caeser.c program to generate encrypted message using Caesar’s cipher
By Ammar Sayed , 19 March 2020
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //testing & Validating the user comand line argument
    if (argc != 2 || argv[1] <= 0)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    else
    {
        //iterate over all chars of argv[1], and check if all digits
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) == false)
            {
                printf("Usage: ./caesar key");
                return 1;
            }

        }
    }

    //converting the key from a string to an integer
    int k = atoi(argv[1]);

    //get the user input
    string p = get_string("plaintext: ");

    //encrypting the user input

    // ci = (pi + k) % 26
    /*
    modulus operator will always result to same number befor % if it's lower,
    for example 2 % 26 = 2, or, 20 % 26 = 20.
    but if it's higher , it returns the remaining
    for exaple 28 % 26 = 2, or 27 % 26 = 1
    */
    printf("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isupper(p[i]))
        {

            printf("%c", ((p[i]) - 'A' + k) % 26 + 'A');
        }

        else if (islower(p[i]))
        {
            printf("%c", ((p[i]) - 'a' + k) % 26 + 'a');
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    //printing a new line
    printf("\n");
}