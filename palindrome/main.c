/**
 * This program receives a word and checks if it's a palindrome or not
 * words can have spaces between them, as long as the letters are a palindrome
 * The maximum number of characters allowed is 80
 * The program can receive both input files or direct input from users.
 */

#include <stdio.h>
#include "palindrome.h"
#include <string.h>
#include <ctype.h>

int main() {
    char str[81];
    int i;
    int valid;

    printf("Enter your string: ");

    while (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';  /* Remove newline */

        if (str[0] == '\0') {
            printf("The string is empty\n");
            printf("Exit code: 1\n");
        } else {
            valid = 1;
            for (i = 0; str[i] != '\0'; i++) {
                if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
                    printf("Your string contains invalid character '%c'\n", str[i]);
                    printf("Exit code: 1\n");
                    valid = 0;
                    break;
                }
            }

            if (valid) {
                if (is_palindrome(str)) {
                    printf("Your string \"%s\" is a palindrome\n", str);
                    printf("Exit code: 0\n");
                } else {
                    printf("Your string \"%s\" isn't a palindrome\n", str);
                    printf("Exit code: 1\n");

                }
            }
        }


        printf("Enter your string: ");
    }

    return 0;
}


