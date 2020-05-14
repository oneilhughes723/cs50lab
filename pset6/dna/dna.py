import sys
import csv

str_max = []

def main():
    # checks to validate usage
    argv = sys.argv
    argc = len(sys.argv)
    if argc != 3:
        print("Usage: dna.py input/File.csv input/File.txt")
        exit(1)
    # opens data file and saves the headers and number of headers
    with open(argv[1], "r") as df:
        d_read = csv.DictReader(df)
        headers = d_read.fieldnames
        num_head = len(headers)
        df.close()
    # initialize a list to store the length of each header, then loop through to find length of each header
    head_len = []
    for i in range(num_head):
        head_len.append(len(headers[i]))
    # open sequence file and save as a string
    sf = open(argv[2], "r")
    sequence = sf.read()
    sf.close()
    # variable that is number of chars in string sequence
    s_len = len(sequence)
    # initialize lists for number of STRs in a given set of repititions and the max number of STR repetitions in the string
    str_count = []
    str_max = []
    # loop through number of headers, append to STR count and STR max
    for i in range(num_head):
        str_count.append(0)
        str_max.append(0)
        s = 0
        # loops through sequence string to find STRs
        while (s < s_len):
            # enters if the string at that point in the string is equal to the header name it is checking for, then increments by the length of that header
            if sequence[s:(s + head_len[i])] == headers[i]:
                str_count[i] = str_count[i] + 1
                s = s + head_len[i]
                if (str_count[i] > str_max[i]):
                    str_max[i] = str_count[i]
            # enters in all other conditions, increments by 1
            else:
                # checks if the most recent string of STRs is greater than the previous highest string, resets STR count and replaces max if most recent STR count is higher than previous max
                str_count[i] = 0
                s = s + 1
    # re-open datafile
    with open(argv[1], "r") as df:
        d_read = csv.DictReader(df)
        # loops through each row in list of dicts, resets i and max to 0 prior to looping through each value in the row
        for row in d_read:
            i = 0
            match = 0
            # loop through each value in the current dict
            for k, v in row.items():
                # skips first column, still iterates 1 so that str_max[0] is not compared
                if k == 'name':
                    i += 1
                    continue
                # enters if value of a given row equals the number of STRs counted in the sequence, increments match by 1
                if int(v) == str_max[i]:
                    match += 1
                # enters if all values in a given dict are equal to the STR maximums found in the sequence and exits
                if match == num_head - 1:
                    print(row['name'])
                    return
                i += 1
    # prints No match if most recent if statments is not entered
    print("No Match")

main()
