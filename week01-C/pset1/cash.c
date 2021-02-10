/*pset1 , cash less comfortable ,
Program will print the lease amount of coins given as a change
created by Ammar Sayed , 4th Aug 2019
*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int quarters = 25;
int dimes = 10;
int nickels = 5;
int pennies = 1;
float dollars;
int cents ;
int coins;

int main(void)
{

    // prompting the user for the change in dollars
    do
    {
        dollars = get_float("change: \n");
    }
    while (dollars < 0);

    //Converting the dollars to cents and round the number
    cents = round(dollars * 100);

    //Testing the input
    printf("change is %i cents\n", cents);

    //checking the quarters
    while (cents >= quarters)
    {
        coins++;
        cents = cents - quarters;
    }

    //checking the dimes
    while (cents >= dimes)
    {
        coins++;
        cents = cents - dimes;
    }

    //checking the nickels
    while (cents >= nickels)
    {
        coins++;
        cents = cents - nickels;
    }

    //checking the pennies
    while (cents >= pennies)
    {
        coins++;
        cents = cents - pennies;
    }

    //Print the number of coins calcualted
    printf("coins: %i\n", coins);

}