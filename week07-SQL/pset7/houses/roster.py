# to do
import csv
from sys import argv
import cs50


# check if no comandline argument
if len(argv) < 2:
    print("Usage: python import.py characters.csv")
    quit()

# open student file for SQLite
housename = argv[1]

db = cs50.SQL("sqlite:///students.db")

query = db.execute(
    "SELECT DISTINCT s.first,s.middle,s.last, s.birth FROM students s WHERE s.house = ? ORDER BY s.last ASC , s.first ASC ;", housename)

for i in query:
    if i['middle'] == None:
        print(i['first'], ' ', i['last'], ', born ', i['birth'], sep='')
    else:
        print(i['first'], ' ', i['middle'], ' ', i['last'], ', born ', i['birth'], sep='')
