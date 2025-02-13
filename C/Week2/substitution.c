#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string substiute_characters(string text, string key, int text_length);

int main(int argc, string argv[])
{

    if (argc == 2)
    {
        string cipher_key = argv[1];
        int cipher_key_length = strlen(cipher_key);

        if (cipher_key_length == 26)
        {
            string plain_text = get_string("plaintext:  ");
            int plain_text_length = strlen(plain_text);

            string cipher_text = substiute_characters(plain_text, cipher_key, plain_text_length);

            printf("ciphertext: %s\n", cipher_text);
            return 0;
        }
        else
        {
            printf("Usage: ./substitution key\n");
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
                text[i] = tolower(substituted_character);
            }
            else
            {
                text[i] = toupper(substituted_character);
            }
        }
        else
        {
            text[i] = character;
        }
    }

    return text;
}
