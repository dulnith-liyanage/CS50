#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

int get_number_of_letters(string text, int text_length);
int get_number_of_sentences(string text, int text_length);
int get_number_of_words(string text, int text_length);
int calculate_index(int letters, int sentences, int words);

int main(void)
{
    string input_text = get_string("Text: ");
    int input_text_length = strlen(input_text);

    int number_of_letters = get_number_of_letters(input_text, input_text_length);
    int number_of_sentences = get_number_of_sentences(input_text, input_text_length);
    int number_of_words = get_number_of_words(input_text, input_text_length);

    int grade = calculate_index(number_of_letters, number_of_sentences, number_of_words);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int calculate_index(int letters, int sentences, int words)
{

    float L = (float)letters / (float)words * 100;
    float S = (float)sentences / (float)words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}

int get_number_of_letters(string text, int text_length)
{
    int number_of_letters = 0;
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            number_of_letters++;
        }
    }

    return number_of_letters;
}

int get_number_of_sentences(string text, int text_length)
{
    int number_of_sentences = 0;
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            number_of_sentences++;
        }
    }

    return number_of_sentences;
}

int get_number_of_words(string text, int text_length)
{
    int number_of_spaces = 0;
    int number_of_words;
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == ' ')
        {
            number_of_spaces++;
        }

        number_of_words = number_of_spaces + 1;
    }

    return number_of_words;
}
