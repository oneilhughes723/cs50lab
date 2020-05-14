from cs50 import SQL
import sys

db = SQL("sqlite:///students.db")


def main():
    # checks validity of command line input
    argv = sys.argv
    argc = len(sys.argv)
    if argc != 2:
        print("Usage: roster.py house")
        exit(1)
    # saves command line input for house as a variables for later use
    house = argv[1]
    # saves lists of dictionaries from database
    splist = db.execute("Select first, middle, last, birth from students where house = (?) order by last, first", (house))
    # iterates over each dictionary
    for row in splist:
        # saves values from keys in each dictionary as variables named after the key
        first = row.get('first')
        middle = row.get('middle')
        last = row.get('last')
        birth = row.get('birth')
        # if statement that prints lines according to formatting and based on presence of middle name
        if middle == None:
            print(first, last + ',', "born", birth)
        else:
            print(first, middle, last + ',', "born", birth)


main()
