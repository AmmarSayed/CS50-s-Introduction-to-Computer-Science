import re
from sys import argv
import csv


def main():

    if len(argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        quit()

    # open the CSV file and DNA seuquece , read contents into Memory
    fileName = argv[1]
    mydblist = list()

    # code from : https://docs.python.org/3.7/library/csv.html#reader-objects
    with open(fileName) as fh:
        reader = csv.DictReader(fh)
        for row in reader:
            mydblist.append(row)

    try:
        fhand = open(argv[2], 'r').read()
    except:
        print('File cannot be opened:', fname)
        exit()

    # importing the Dna names from mydblist
    dna_list = []
    for i in mydblist:
        for k, v in i.items():
            if k not in dna_list and k != 'name':
                dna_list.append(k)

    # for each STR, compute the Longest run of consecutive repats in DNA sequence
    dna_dict = {}
    for i in dna_list:
        # making sure that the value is stored as string to match value from CSV
        dna_dict[i] = str(dna_dict.get(i, 0) + int(find_max_repeats(fhand, i)))

    # Compare the STR counts against each row in the CSV file looking for a name to match

    # function by Mr. Felipe Borges
    # https://stackoverflow.com/questions/61037416/python-filter-a-list-of-dictionaries-by-another-dictionary-values/61037585#61037585

    def compare_dicts(a, b):
        # Compare all keys of A with the same key in B
        for key in a.keys():
            if key in b:
                if a[key] != b[key]:
                    return False
        return True

    def compare_cont(mydblist):
        for i in mydblist:
            if compare_dicts(dna_dict, i):
                return i['name']

    if compare_cont(mydblist) == None:
        print('No match')
    else:
        print(compare_cont(mydblist))


# Function from https://www.journaldev.com/23666/python-string-find
# amended by Gabriel L Matinez
# https://stackoverflow.com/questions/61021944/python-counting-consecutive-characters-in-a-string/61022742?noredirect=1#comment107982529_61022742

def find_max_repeats(input_str, search_str):
    max_count = 0
    # regex to find all repeated consicutive
    search_str_regex = f"?:{search_str}"

    # extract all strings I'm searching for
    strungArray = re.findall(f"({search_str_regex})+", input_str)

    for myString in strungArray:
        # loop over each string in the array
        singleString = re.findall(f"({search_str_regex})", myString)
        count = len(singleString)

        if count > max_count:
            max_count = count
    return max_count


main()