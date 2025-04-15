#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Opens and reads the contents of the memory card
    FILE *memory_card = fopen(argv[1], "r");

    // Creates a buffer to store the bytes of data
    __uint8_t buffer[BLOCK_SIZE];

    // Counts the number of encountered jpegs
    int jpeg_counter = 0;

    // Initializes the current jpeg file and file name
    char *file_name_format = "###.jpg";
    char current_file_name[sizeof(file_name_format)];

    FILE *current_file = NULL;

    if (memory_card == NULL)
    {
        printf("The file could not be opened.");
        return 1;
    }

    while (fread(buffer, 1, BLOCK_SIZE, memory_card) == BLOCK_SIZE)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (jpeg_counter != 0)
            {
                fclose(current_file);
            }

            // Names a file, creates the file
            sprintf(current_file_name, "%03i.jpg", jpeg_counter);

            // Creates the file from the file name
            current_file = fopen(current_file_name, "w");

            // Writes data in to the current file
            fwrite(buffer, 1, BLOCK_SIZE, current_file);

            jpeg_counter++;
        }
        else if (jpeg_counter != 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, current_file);
        }
    }

    fclose(current_file);
    fclose(memory_card);
}