/**
 * This program receives a word and checks if it's a palindrome or not.
 * Words can have spaces between them, as long as the letters form a palindrome.
 * The maximum number of characters allowed is 80.
 * The program can receive both input from files or direct user input.
 * It performs input validation and checks that only letters and spaces are allowed.
 * The program displays if the string is a palindrome or not after validation.
 */

#include <stdio.h>          /* Standard input/output functions (printf, fgets) */
#include "palindrome.h"     /* Header file for palindrome checking (assuming it defines is_palindrome) */
#include <string.h>         /* String handling functions like strcspn */
#include <ctype.h>          /* Functions for character classification (isalpha, isspace) */
#include <stdlib.h>         /* Standard library functions (exit) */

int main(void) {
    char str[MAX_STRING_LENGTH + 1];           /* Input string buffer: 80 chars max + null terminator */
    int i;                  /* Loop index for validation of each character */
    int valid;              /* Flag to track if the input is valid (only letters or spaces) */

    printf("\nEnter your string: ");  /* Prompt the user for input */

    /* Read lines from input until EOF */
    while (fgets(str, sizeof(str), stdin) != NULL) {

        /* Display the raw input */
        printf("\nThe word you entered is: %s \n", str);

        /* Remove trailing newline character from fgets */
        str[strcspn(str, "\n")] = '\0';  /* Replace the newline with null terminator */

        /* Check if the string is empty */
        if (str[0] == '\0') {
            printf("The string is empty\n");
            exit(1);  /* Exit the program if the input is empty */
        } else {
            valid = 1;  /* Assume the string is valid initially */

            /* Validate that all characters are letters or spaces */
            for (i = 0; str[i] != '\0'; i++) {
                /* Loop through each character in the string to validate it
                   Only letters and spaces are allowed */
                if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
                    printf("Your string contains invalid character '%c'\n", str[i]);
                    printf("------------------------------------------------");

                    valid = 0;  /* Set valid flag to 0 if an invalid character is found */
                    break;  /* Exit the loop if an invalid character is found */
                }
            }

            if (valid) {
                /* Call the palindrome function and print the result */
                if (is_palindrome(str)) {
                    printf("The return value is: 1 (Palindrome)\n");  /* 1 means it's a palindrome */
                    printf("\n------------------------------------------------\n");

                } else {
                    printf("The return value is: 0 (Not a palindrome)\n");  /* 0 means it's not a palindrome */
                    printf("\n------------------------------------------------\n");
                }
            }
        }

        /* Prompt for next input */
        printf("Enter your string: \n");
    }

    return 0;  /* Exit successfully */
}



