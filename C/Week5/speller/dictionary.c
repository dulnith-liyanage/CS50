// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Used by the size function to count the size of the dictionary
int size_of_dictionary = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// To free the nodes in the hashmap
void free_nodes(node *first_node);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    for (int i = 0; i < N; i++)
    {

        for (node *p = table[i]; p != NULL; p = p->next)
        {
            if (strcasecmp(p->word, word) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_file = fopen(dictionary, "r");
    if (!dictionary_file)
    {
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(dictionary_file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, buffer); // Copies the word in to the node

        int index = hash(n->word); // Finds the index corresponding to the table

        // Adds the node to the hashmap
        node *tmp = table[index];
        n->next = tmp;
        table[index] = n;

        // Increase the size count
        size_of_dictionary++;
    }

    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_of_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    int free_count = 0;

    for (int i = 0; i < N; i++)
    {
        free_nodes(table[i]);
    }

    return true;
}

void free_nodes(node *first_node)
{
    // Base condition
    if (first_node == NULL)
    {
        return;
    }

    free_nodes(first_node->next);
    free(first_node);
}