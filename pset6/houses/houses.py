import sys
import csv
from cs50 import SQL


db = SQL("sqlite:///students.db")


def main():
    # initialize variables to None for later use
    first, middle, last, house, year = None, None, None, None, None
    # check validity of command line arguments
    argv = sys.argv
    argc = len(sys.argv)
    if argc != 2:
        print("Usage: import.py inputfile.csv")
        exit(1)
    # opens csv file from command line and reads it into lists
    with open(argv[1], "r") as df:
        d_read = csv.reader(df)
        # iterate over each row from csv file
        for row in d_read:
            count = 0
            # iterates over each value in the row and saves variables
            for col in row:
                if count == 0:
                    name = col.split()
                    if len(name) == 2:
                        first = name[0]
                        middle = None
                        last = name[1]
                    if len(name) == 3:
                        first = name[0]
                        middle = name[1]
                        last = name[2]
                if count == 1:
                    house = col
                if count == 2:
                    birth = col
                # count is to determine what column is being saved
                count += 1
            # executes sql query to insert data into students database
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       (first, middle, last, house, birth))
            db.execute("DELETE FROM students WHERE house = 'house'")


main()


