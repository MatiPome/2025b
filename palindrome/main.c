/**
 * This program receives a word and checks if it's a palindrome or not.
 * Words can have spaces between them, as long as the letters form a palindrome.
 * The maximum number of characters allowed is 80.
 * The program can receive both input from files or direct user input.
 */

#include <stdio.h>
#include "palindrome.h"
#include <string.h>
#include <ctype.h>

int main(void) {
    char str[81];           /* Input string buffer: 80 chars max + null terminator */
    int i;
    int valid;

    printf("\nEnter your string: ");

    /* Read lines from input until EOF */
    while (fgets(str, sizeof(str), stdin) != NULL) {
        /* Display the raw input */
        printf("\nThe word you entered is: %s \n", str);

        /* Remove trailing newline character */
        str[strcspn(str, "\n")] = '\0';

        /* Check if the string is empty */
        if (str[0] == '\0') {
            printf("The string is empty\n");
            printf("\n------------------------------------------------\n");

        } else {
            valid = 1;

            /* Validate that all characters are letters or spaces */
            for (i = 0; str[i] != '\0'; i++) {
                if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
                    printf("Your string contains invalid character '%c'\n", str[i]);
                    printf("------------------------------------------------");

                    valid = 0;
                    break;
                }
            }

            if (valid) {
                /* Call the palindrome function and print the result */
                if (is_palindrome(str)) {
                    printf("The return value is: %d \n", is_palindrome(str));
                    printf("\n------------------------------------------------\n");

                } else {
                    printf("The return value is: %d \n", is_palindrome(str));
                    printf("\n------------------------------------------------\n");
                }
            }
        }

        /* Prompt for next input */
        printf("Enter your string: \n");
    }

    return 0;
}


