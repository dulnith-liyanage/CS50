from cs50 import get_string

def reverse(string):
    return string[::-1]

def checksum(number):
    sum = 0
    reversed_number = reverse(number)

    for i in range(1, len(number), 2):
        digit = str(int(reversed_number[i]) * 2)
        if len(digit) == 1:
            sum += int(digit)
        else:
            sum += int(digit[0])
            sum += int(digit[1])
        
    for j in range(0, len(number), 2):
        digit = int(reversed_number[j])
        sum += digit


    if (sum % 10) == 0:
        return True
    else:
        return False

number_string = get_string("Number: ")

is_valid = checksum(number_string)

if is_valid:
    if len(number_string) == 15 and (number_string[0:2] == "34" or number_string[0:2] == "37"):
        print("AMEX")
    elif len(number_string) == 16 and (number_string[0:2] == "51" or number_string[0:2] == "52" or number_string[0:2] == "53" or number_string[0:2] == "54" or number_string[0:2] == "55"):
        print("MASTERCARD")
    elif (len(number_string) == 13 or len(number_string) == 16) and number_string[0] == "4":
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")