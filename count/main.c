/**
 * This program calculates the number of zero bits in a binary number.
 * It receives a decimal number from the user, converts it to binary,
 * and prints the amount of 0-bits according to the system's int bit width.
 */

#include <stdio.h>
#include "module.h"

int main(void) {
    unsigned num;  /* Input number from user */

    /* Program banner */
    printf("--------------------------------------------------------------------\n");
    printf("Welcome to the zero counter for decimal to binary program\n");
    printf("--------------------------------------------------------------------\n");

    /* Prompt for user input */
    printf("Please enter a number in decimal format and press enter: ");

    /* Read and validate input */
    if (scanf("%u", &num) != 1)
        return 1;

    /* Output result */
    printf("--------------------------------------------------------------------\n");
    printf("The number of zeros in the binary format is: %d\n", count_zero_bits(num));
    printf("--------------------------------------------------------------------\n");
    printf("Thank you for using the program, farewell\n");

    return 0;
} /* end of main */

