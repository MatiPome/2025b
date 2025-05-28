#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>     /* For FILE type */
#include "magic.h"     /* For N (matrix size) constant */

/*=============================================================================
 * Input status codes returned by read_matrix:
 *===========================================================================*/

/* Input was successfully parsed and matrix was filled */
#define STATUS_SUCCESS      0

/* Generic failure (unused in read_matrix, but available) */
#define STATUS_FAILURE      1

/* Encountered a token that is not an integer */
#define STATUS_NOT_INTEGER  2

/* More than N*N numbers were provided in the input */
#define STATUS_TOO_MANY     3

/* Fewer than N*N numbers were provided in the input */
#define STATUS_TOO_FEW      4

/* Maximum number of characters allowed per input line */
#define MAX_LINE_LENGTH     100

/*-----------------------------------------------------------------------------
 * Reads a matrix of size N×N from the given FILE stream.
 *
 * Parameters:
 *   matrix      - 2D array of size N×N to be filled with input values
 *   source      - FILE pointer to input source (stdin or file)
 *   invalidFlag - pointer to int flag; set to 1 if duplicates or out-of-range
 *                 values are found, otherwise set to 0
 *
 * Returns:
 *   One of the STATUS_* codes indicating input success or failure.
 *---------------------------------------------------------------------------*/
int read_matrix(int matrix[N][N], FILE *source, int *invalidFlag);

/*-----------------------------------------------------------------------------
 * Attempts to parse a string into an integer.
 *
 * Parameters:
 *   str  - input string to parse
 *   out  - pointer to int where result will be stored if successful
 *
 * Returns:
 *   1 if conversion was successful, 0 otherwise.
 *---------------------------------------------------------------------------*/
int check_int(const char *str, int *out);

#endif  /* INPUT_H */