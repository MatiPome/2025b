#include <stdio.h>     /* For FILE, fgets, fprintf, sscanf */
#include <string.h>    /* For strtok */
#include "input.h"     /* For constants like N and status codes */
#include <stdlib.h>    /* For strtol, malloc, free */
#include <limits.h>    /* For INT_MAX, INT_MIN */
#include <errno.h>     /* For errno, ERANGE */


/*
 * Reads a square matrix of integers from the given input source.
 * Returns a status code based on input validity:
 *  - STATUS_SUCCESS if input was correctly formatted
 *  - STATUS_TOO_FEW if fewer than N*N numbers are provided
 *  - STATUS_TOO_MANY if more than N*N numbers are parsed
 *  - STATUS_NOT_INTEGER if a non-integer token is encountered
 *
 * Also sets *invalidFlag to 1 if any duplicate or out-of-range values are found.
 */
int read_matrix(int matrix[N][N], FILE *source, int *invalidFlag) {
    char line[MAX_LINE_LENGTH];        /* Buffer for each input line */
    int seen[N * N] = {0};             /* Flags to detect duplicates (1..N^2) */
    int row = 0, col = 0;              /* Matrix position trackers */
    char *token;                       /* Pointer to current token from line */
    int count = 0;                     /* Total numbers successfully read */
    int value = 0;                     /* Holds integer value of current token */
    int invalid = 0;                   /* Flag for duplicates or out-of-range */

    /* Introductory messages written to stderr */
    fprintf(stderr, "Welcome to the magic square analyzer\n\n");
    fprintf(stderr, "The magic square consists of %d rows and columns.\n", N);
    fprintf(stderr, "Please input a total of %d numbers (space-separated in one line or multiple lines).\n", N * N);

    /* Read input until we have N*N values or reach EOF */
    while (count < N * N && fgets(line, sizeof(line), source)) {

        /* Tokenize the line using standard whitespace delimiters */
        token = strtok(line, " \t\n\v\f\r");

        while (token != NULL) {

            /* Convert token to integer; fail if not a valid number */

            if (!check_int(token, &value)) {
                return STATUS_NOT_INTEGER;
            }

            /* Check for overflow — we already reached N*N values */
            if (count >= N * N) {
                return STATUS_TOO_MANY;
            }

            /* Check if value is out of range or already seen */
            if (value < 1 || value > N * N || seen[value - 1]) {
                invalid = 1;
            } else {
                seen[value - 1] = 1;  /* Mark value as seen */
            }

            /* Store the value in the matrix */
            matrix[row][col] = value;
            col++;
            count++;

            /* Move to the next row if current row is filled */
            if (col == N) {
                col = 0;
                row++;
            }

            /* Advance to next token in the same line */
            token = strtok(NULL, " \t\n\v\f\r");
        }
    }

    /* If fewer values were read than required, report error */
    if (count < N * N) {
        return STATUS_TOO_FEW;
    }

    /* Set the output flag to indicate if any input was invalid */
    *invalidFlag = invalid;

    /* If everything else was fine, return success */
    return STATUS_SUCCESS;
}


/*
 * check_int:
 *  Attempts to parse a string into an integer.
 *  Returns 1 if successful, 0 otherwise.
 *  The result is stored in *out if valid.
 */
int check_int(const char *str, int *out) {
    char *end;
    long val;

    errno = 0;  /* Reset errno before conversion */
    val = strtol(str, &end, 10);  /* Convert string to long */

    /* Check if nothing was parsed */
    if (end == str)
        return 0;

    /* Check for trailing non-digit characters */
    if (*end != '\0')
        return 0;

    /* Check for overflow or underflow */
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN)
        return 0;

    /* All checks passed, assign value */
    *out = (int)val;
    return 1;
}

























