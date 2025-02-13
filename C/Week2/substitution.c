#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string substiute_characters(string text, string key, int text_length);
bool has_no_duplicates(string key, int key_length);
bool has_valid_characters(string key, int key_length);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string cipher_key = argv[1];
        int cipher_key_length = strlen(cipher_key);

        if (cipher_key_length == 26)
        {
            if (has_valid_characters(cipher_key, cipher_key_length))
            {
                if (has_no_duplicates(cipher_key, cipher_key_length))
                {
                    string plain_text = get_string("plaintext:  ");
                    int plain_text_length = strlen(plain_text);

                    string cipher_text = substiute_characters(plain_text, cipher_key, plain_text_length);

                    printf("ciphertext: %s\n", cipher_text);
                    return 0;
                }
                else
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
            else
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must be 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

string substiute_characters(string text, string key, int text_length)
{
    for (int i = 0; i < text_length; i++)
    {
        char character = text[i];

        int character_position = toupper(character) - 'A';    // Obtains the position of character in the key
        char substituted_character = key[character_position]; // Substitutes the character according to the key

        if (isalpha(character))
        {
            if (islower(character))
            {
                text[i] = tolower(substituted_character); // Returns a lowercase letter
            }
            else
            {
                text[i] = toupper(substituted_character); // Returns an uppercase letter
            }
        }
        else
        {
            text[i] = character; // Ensures that non-alpha characters remain unchanged
        }
    }

    return text;
}

bool has_valid_characters(string key, int key_length)
{
    int non_alpha_character_count = 0;

    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            non_alpha_character_count++;
        }
    }

    if (non_alpha_character_count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_no_duplicates(string key, int key_length)
{
    int duplicate_count = 0;

    for (int i = 0; i < key_length; i++)
    {
        char inspected_letter = toupper(key[i]);
        for (int j = 0; j < i + 1; j++)
        {
            char inspecting_letter = toupper(key[j]);
            if (inspecting_letter == inspected_letter && i != j)
            {
                duplicate_count++;
            }
        }
    }

    if (duplicate_count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}