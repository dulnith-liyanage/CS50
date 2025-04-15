from cs50 import get_string

text = get_string("Text: ")

letters = 0
sentences = 0
spaces = 0

for character in text:
    if character.isalpha():
        letters += 1
    if character.isspace():
        spaces += 1
    if character == '.' or character == '!' or character == '?':
        sentences += 1

words = spaces + 1



L = (letters / words) * 100
S = (sentences / words) * 100

index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")