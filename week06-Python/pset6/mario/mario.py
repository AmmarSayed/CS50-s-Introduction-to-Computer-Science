def main():
    height = get_positive_int()

    for line in range(height):
        # print the spaces
        for spa in range(height - line - 1):
            print(" ", end="")
        # print the hashes
        for ha in range(line+1):
            print("#", end="")
        # print a new line
        print()


def get_positive_int():
    # function to get a positive integer

    # forever check for a number equal to or between 1 and 8
    while True:
        try:
            n = int(input("Height: "))
            if 1 <= n <= 8:
                break
            else:
                print("Sorry Please input a number between 1 and 8!")

        except ValueError:
            print("Sorry Please input a number between 1 and 8!")

    return n


main()
