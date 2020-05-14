from cs50 import get_string

# define main for execution at end of script


def main():
    # get credit card number from user and check that length is a valid CC number
    ccstr = get_string("Please input your credit card number: ")
    ccnum = int(ccstr)
    cclen = len(ccstr)

    # check if amex
    if cclen == 15 and int(ccstr[0]) == 3 and (int(ccstr[1]) == 4 or int(ccstr[1]) == 7):
        if checksum(ccstr) == True:
            print("AMEX")
        else:
            print("INVALID")

    # check if Mastercard
    elif cclen == 16 and int(ccstr[0]) == 5 and (int(ccstr[1]) < 6 and int(ccstr[1]) > 0):
        if checksum(ccstr) == True:
            print("MASTERCARD")
        else:
            print("INVALID")

        # check if visa
    elif (cclen == 13 or cclen == 16) and int(ccstr[0]) == 4:
        if checksum(ccstr) == True:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


# checksum to determine whether luhns algorithm is valid or invalid for given cc number
def checksum(n):
    sum = 0
    i = len(n) - 2
    while i >= 0:
        if int(n[i]) * 2 >= 10:
            digits = int(n[i]) * 2
            digits = str(digits)
            sum_digits = int(digits[0]) + int(digits[1])
            sum = sum + sum_digits
            sum_digits = 0
        else:
            sum = sum + int(n[i]) * 2
        i = i - 2
    i = len(n) - 1
    while i >= 0:
        sum = sum + int(n[i])
        i = i - 2
    if sum % 10 == 0:

        # returns boolean true if valid
        return True
    else:
        # returns boolean false if checksum is incorrect and cc number is invalid
        return False


main()
