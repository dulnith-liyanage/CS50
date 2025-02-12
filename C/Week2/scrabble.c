#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word, int score_map[]);

int main(void)
{
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");

    int score1 = compute_score(input1, POINTS);
    int score2 = compute_score(input2, POINTS);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word, int score_map[])
{
    int word_length = strlen(word);
    int total_score = 0;
    for (int i = 0; i < word_length; i++)
    {
        char character = word[i];
        if (isalpha(character))
        {
            int letter = toupper(character);
            total_score += score_map[letter - 'A'];
        }
    }

    return total_score;
}
