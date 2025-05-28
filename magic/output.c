#include <stdio.h>      /* For printf */
#include "output.h"     /* Function declarations for output printing */
#include "magic.h"      /* For N (matrix size) */
#include "input.h"      /* For STATUS_* error codes */

/*
 * Prints whether the matrix is a magic square or not,
 * based on the status code returned from magic().
 *
 * Parameters:
 *   status - STATUS_SUCCESS if matrix is magic, STATUS_FAILURE otherwise
 */
void print_result(int status) {
    if (status == STATUS_SUCCESS) {
        printf("The matrix is a magic square.\n");
    } else {
        printf("The matrix is not a magic square.\n");
    }
}

/*
 * Prints a human-readable message for an input error.
 *
 * Parameters:
 *   s - one of the STATUS_* codes returned by read_matrix()
 */
void print_input_error(int s) {
    switch (s) {
        case STATUS_TOO_FEW:
            printf("Input error: not enough numbers (early EOF).\n");
            break;
        case STATUS_NOT_INTEGER:
            printf("Input error: expected an integer.\n");
            break;
        case STATUS_TOO_MANY:
            printf("Input error: too many numbers in input.\n");
            break;
        default:
            printf("Input error: unknown error occurred.\n");
    }
}

/*
 * Prints the contents of the N×N matrix to standard output,
 * formatted in a grid with 4-character-wide fields.
 *
 * Parameters:
 *   matrix - the square matrix to print
 */
void print_matrix(int matrix[N][N]) {
    int row;
    int col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            printf("%4d ", matrix[row][col]);
        }
        printf("\n");
    }
}


