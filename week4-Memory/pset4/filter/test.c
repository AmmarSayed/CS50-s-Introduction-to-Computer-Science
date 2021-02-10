#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main (void)
{
    char *s = "Ammar";
    char *c = malloc(strlen(s) + 1);

    //copy the string
    for (int i = 0, n = strlen(s); i < n + 1; i++)
    {
        c[i] = toupper(s[i]);
    }
    printf("%s\n", c);

    free (c);
}