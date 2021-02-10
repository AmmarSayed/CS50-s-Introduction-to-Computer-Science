# to do
import csv
from sys import argv
import cs50
# check if no comandline argument
if len(argv) < 2:
    print("Usage: python import.py characters.csv")
    quit()

# Create database by opening and closing an empty file first
open(f"students.db", "a").close()
# open student file for SQLite
db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as file:

    # Create a Dictreader
    reader = csv.DictReader(file)

    for row in reader:
        # split the name field using spaces
        x = row['name'].split()
        # check if we have 3 names
        if len(x) == 3:
            first = x[0]
            middle = x[1]
            last = x[2]
            db.execute(
                "INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, row['house'], row['birth'])
        elif len(x) == 2:
            first = x[0]
            middle = None
            last = x[1]
            db.execute(
                "INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, row['house'], row['birth'])
