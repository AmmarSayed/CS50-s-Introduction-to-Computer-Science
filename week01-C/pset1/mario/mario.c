/*pset1 , mario less comfortable ,
Program to print a pyramid based on user input for number of rows
created by Ammar Sayed , 15th July 2019
*/
#include <stdio.h>
#include <cs50.h>
int get_positive_integer(string u_input);

int main(void)
{
    int hight = get_positive_integer("Please enter the number of columns needed !\n");
    //set the number of lines using "\n"
    for (int i = 0; i < hight; i++)
    {
        //set the number of spaces
        for (int spaces = hight - i; spaces > 1; spaces--)
        {
            printf(" ");
        }
        //set the number of hasges
        for (int hashes = 0; hashes <= i; hashes++)
        {
            printf("#");
        }
        printf("\n");
    }
}

//prompt the user for positive number between 1 and 8
int get_positive_integer(string user_input)
{
    int n;
    do
    {
        n = get_int("%s", user_input);
    }
    while (n < 1 || n > 8);
    return n;
}
