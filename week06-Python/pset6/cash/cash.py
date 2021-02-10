from cs50 import get_float


def main():
    # define variables
    quarters = 25
    dimes = 10
    nickels = 5
    pennies = 1
    cents = 0  # to be used in converting the entry of the user to cents
    coins = 0  # Counter for coins

    dollars = get_positive_get_float()

    cents = int(dollars * 100)

    # loop through the cents and calculate the remaining 
    while cents >= quarters:
        cents -= quarters
        coins += 1
    while cents >= dimes:
        cents -= dimes
        coins += 1
    while cents >= nickels:
        cents -= nickels
        coins += 1
    while cents >= pennies:
        cents -= pennies
        coins += 1

    print(coins)


# function to get a float from the user
def get_positive_get_float():
    while True:
        n = get_float("Change owed: ")
        if n > 0:
            break
    return n


main()
