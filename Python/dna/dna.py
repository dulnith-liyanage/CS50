import csv
import sys

def main():

    # TODO: Check for command-line usage
    if not len(sys.argv) == 3:
        print("Usage python dna.py csv_file text_file")

    # TODO: Read database file into a variable
    people = []
    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            people.append(row)

    # TODO: Read DNA sequence file into a variable
    dna_sequence = ""
    with open(sys.argv[2]) as txtfile:
        dna_sequence = txtfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR_array = []

    # Adds the STRs to an array
    for key in people[0]:
        if not key == 'name':
            STR_matches = {}
            STR_matches["STR_name"] = key
            STR_matches["longest_match"] = longest_match(dna_sequence, key)
            STR_array.append(STR_matches)

    # TODO: Check database for matching profiles
    for person in people:
        person["match_count"] = 0

    for person in people:
        for STR in STR_array:
            if int(person[STR["STR_name"]]) == STR["longest_match"]:
                person["match_count"] += 1
                    
    for person in people:
        if person["match_count"] == len(STR_array):
            print(person["name"])
            break
    else:
            print("No match")   

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()