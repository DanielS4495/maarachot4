#include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -c file.txt OR %s -d file.bin\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-c") == 0) {
        char *filename_with_bin_extension = malloc(strlen(argv[2]) + 5); // Allocate memory for the new filename
        strcpy(filename_with_bin_extension, argv[2]); // Copy the original filename to the new string

        // Remove the ".txt" extension if it exists
        char *dot_ptr = strrchr(filename_with_bin_extension, '.'); // Find the last occurrence of '.'
        if (dot_ptr != NULL && strcmp(dot_ptr, ".txt") == 0) {
            *dot_ptr = '\0'; // Null-terminate the string at the position of '.'
        }

        // Append ".bin" extension to the filename
        strcat(filename_with_bin_extension, ".bin");

        // Pass the modified filename to the function
        compress_text_file(argv[2], filename_with_bin_extension);

    } else if (strcmp(argv[1], "-d") == 0) {
        // Create output text file
        FILE *output_file = fopen("output.txt", "w");
        if (!output_file) {
            fprintf(stderr, "Error creating output file.\n");
            exit(EXIT_FAILURE);
        }
        fclose(output_file);

        // Pass filenames to the function
        decompress_binary_file(argv[2], "output.txt");
    } else {
        fprintf(stderr, "Invalid option.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

