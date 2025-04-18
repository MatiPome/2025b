/**
 * This program calculates the number of zero bits in a binary number.
 * It receives a decimal number from the user, converts it to binary,
 * and prints the amount of 0-bits according to the system's int bit width.
 * The program works for 32-bit integers, counting how many '0' bits exist
 * in the binary representation of the given input number.
 */

#include <stdio.h>    /* Standard input/output functions (printf, scanf) */
#include "count_zero_bits.h"   /* Include the module that defines the function count_zero_bits */

/*
 * main:
 *   The entry point of the program. It takes a decimal number input from the user,
 *   validates the input, converts it to binary, counts the zero bits, and prints the result.
 *
 * Parameters: None
 * Returns: int - Return 0 if successful, 1 if input is invalid.
 */
int main(void) {
    unsigned int num;  /* Input number from user, represented as an unsigned integer */

    /* Program banner */
    printf("--------------------------------------------------------------------\n");
    printf("Welcome to the zero counter for decimal to binary program\n");
    printf("--------------------------------------------------------------------\n");

    /* Prompt for user input */
    printf("Please enter a number between 0 and (2^32 -1) in decimal format and press enter: ");

    /* Read and validate input */
    if (scanf("%u", &num) != 1) {    /* Read the user input and check if it is valid */
        return 1;    /* Return an error code if input is invalid (non-numeric input) */
    }

    /* Output result */
    printf("--------------------------------------------------------------------\n");
    printf("The number of zeros in the binary format is: %d\n", count_zero_bits(num));  /* Call count_zero_bits function and display the result */
    printf("--------------------------------------------------------------------\n");
    printf("Thank you for using the program, farewell\n");

    return 0;  /* Return 0 to indicate successful execution of the program */
} /* end of main */


