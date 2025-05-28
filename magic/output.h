#ifndef OUTPUT_H
#define OUTPUT_H

#include "magic.h"  /* For matrix size N */

/*
 * Prints whether the matrix is a magic square based on the given status.
 *
 * Parameters:
 *   status - STATUS_SUCCESS if magic, STATUS_FAILURE otherwise
 */
void print_result(int status);

/*
 * Prints a specific error message based on the input status code.
 *
 * Parameters:
 *   s - one of the STATUS_* codes from read_matrix()
 */
void print_input_error(int s);

/*
 * Prints the N×N matrix to standard output in a formatted grid.
 *
 * Parameters:
 *   matrix - a 2D array of size N×N containing the input values
 */
void print_matrix(int matrix[N][N]);

#endif  /* OUTPUT_H */