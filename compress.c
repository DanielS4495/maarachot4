#include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress_text_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error opening input file1.\n");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fclose(input_file);
        fprintf(stderr, "Error opening output file2.\n");
        exit(EXIT_FAILURE);
    }

    int num;
    while (fscanf(input_file, "%d", &num) == 1) {
        // Convert each digit to a compressed 4-bit representation
        while (num != 0) {
            int digit = num % 10;
            int compressed_digit = 0;
            for (int i = 0; i < 4; i++) {
                int bit = digit % 2;
                compressed_digit |= ((bit ^ 1) << i); // Invert each bit and set it in the compressed digit
                digit /= 2;
            }
            fwrite(&compressed_digit, sizeof(char), 1, output_file); // Write the compressed digit to the output file
            num /= 10;
        }
    }

    // If there is an odd number of digits, add 4 zeros to the end of the file
    if (ftell(input_file) % 2 != 0) {
        for (int i = 0; i < 4; i++) {
            int compressed_digit = 0;
            fwrite(&compressed_digit, sizeof(char), 1, output_file); // Write zero digit to the output file
        }
    }
    fclose(input_file);
    fclose(output_file);
}

void decompress_binary_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Error opening input file3.\n");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        fclose(input_file);
        fprintf(stderr, "Error opening output file4.\n");
        exit(EXIT_FAILURE);
    }

    int digit;
    char number[256] = "";
     while (fread(&digit, sizeof(char), 1, input_file) == 1) {
        
        digit = ~digit & 0xF; // Invert and take only 4 bits
        printf("d %d\n",digit);
        if (digit == -1) {
            break; // Stop reading if it is the last character
        }
        if(digit ==  15){
            digit = 0;
        }
         char digit_str[2]; // Temporary string to hold the digit
        sprintf(digit_str, "%d", digit); // Convert digit to string
        strcat(number, digit_str); // Concatenate digit_str to number
        
        printf("n %s\n",number);
    
    }
     int length = strlen(number);
    for (int i = 0; i < length / 2; i++) {
        char temp = number[i];
        number[i] = number[length - i - 1];
        number[length - i - 1] = temp;
    }
    fprintf(output_file, "%s", number);
    // int temp_number = number;
    // int reversed_number = 0;
    // while (temp_number > 0) {
    //     int last_digit = temp_number % 10;
    //     reversed_number = reversed_number * 10 + last_digit;
    //     temp_number /= 10;
    // }

    // // Handle leading zeroes
    // if (number == 0) {
    //     fprintf(output_file, "0");
    // } else {
    //     // Print the reconstructed number
    //     while (reversed_number > 0) {
    //         int last_digit = reversed_number % 10;
    //         fprintf(output_file, "%d", last_digit);
    //         reversed_number /= 10;
    //     }
    // }

    fclose(input_file);
    fclose(output_file);
}
