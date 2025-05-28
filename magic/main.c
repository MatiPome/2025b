#include <stdio.h>       /* For FILE, stdin, fopen, fclose */
#include "input.h"       /* For read_matrix and input status codes */
#include "magic.h"       /* For matrix size N and magic() function */
#include "output.h"      /* For output-related print functions */

/*
 * Entry point of the magic square analyzer.
 *
 * Accepts optional command-line argument for input file.
 * Reads a matrix of integers, validates structure and values,
 * and checks if the matrix is a valid magic square.
 */
int main(int argc, char *argv[]) {
    int result;                  /* Result code from read_matrix */
    int magic_square;            /* Result from magic() or STATUS_FAILURE */
    int invalid = 0;             /* Flag set by read_matrix if input is invalid */
    FILE *source = stdin;        /* Input source: stdin by default */
    int matrix[N][N];            /* Storage for the input matrix */

    /* If a filename is passed as argument, open it for reading */
    if (argc == 2) {
        source = fopen(argv[1], "r");
    }

    /* Read the matrix and check for structural input errors */
    result = read_matrix(matrix, source, &invalid);
    if (result != STATUS_SUCCESS) {
        print_input_error(result);       /* Report specific input error */
        if (source != stdin) fclose(source);
        return STATUS_FAILURE;          /* Exit with failure code */
    }

    /* Print the matrix regardless of whether it's valid or not */
    print_matrix(matrix);

    /* If the input had invalid values (duplicates/out-of-range), skip logic check */
    if (invalid) {
        magic_square = STATUS_FAILURE;
    } else {
        magic_square = magic(matrix);   /* Check if the matrix is a magic square */
    }

    /* Print the result: magic or not */
    print_result(magic_square);

    /* Close the input file if not reading from stdin */
    if (source != stdin) fclose(source);

    return STATUS_SUCCESS;
}

