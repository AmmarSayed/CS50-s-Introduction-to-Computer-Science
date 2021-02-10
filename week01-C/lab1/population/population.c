#include <cs50.h>
#include <stdio.h>
int get_positive_int(string st, int num);

int main(void)
{
    // TODO: Prompt for start size
    int startSize = get_positive_int("Enter starting population >", 9);

    // TODO: Prompt for end size
    int endSize = get_positive_int("Enter end population >", startSize);

    // TODO: Calculate number of years until we reach threshold

    int years = 0;

    while (startSize < endSize)
    {
        int gain = startSize / 3;
        int lose = startSize / 4;

        startSize = startSize + gain - lose;

        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);

}


// Prompt user for positive integer
int get_positive_int(string st, int num)
{
    int n;
    do
    {
        n = get_int("%s %d: ", st, num);
    }
    while (n < num);
    return n;
}
