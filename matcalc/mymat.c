#include "mymat.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * read_mat
 *
 * Populates a NxN matrix with values from a flat float array.
 * Conforms to ISO C90: loop indices declared at top of each block.
 *
 * Parameters:
 *   MATRIX – the target matrix (mat type, NxN)
 *   arr    – an array of MAT_SIZE floats (MAT_ROWS × MAT_COLS)
 *
 * Behavior:
 *   - Iterates row by row (i = 0 … MAT_ROWS-1)
 *   - Within each row, iterates column by column (j = 0 … MAT_COLS-1)
 *   - Computes the flat-array index as (i * MAT_COLS + j)
 *   - Writes arr[index] into MATRIX[i][j]
 *   - Prints a confirmation message for each written element
 */
void read_mat(mat MATRIX, float arr[MAT_SIZE]) {
    int i, j;  /* loop counters for rows (i) and columns (j) */

    /* Outer loop: iterate over each row */
    for (i = 0; i < MAT_ROWS; i++) {
        /* Inner loop: iterate over each column in the current row */
        for (j = 0; j < MAT_COLS; j++) {
            /* Calculate flat index into arr[] and assign to MATRIX */
            MATRIX[i][j] = arr[i * MAT_COLS + j];
        }
    }
}
/*
 * print_mat
 *
 * Prints the contents of a NxN matrix to stdout in a neatly formatted grid.
 *
 * Parameters:
 *   MATRIX – the matrix (mat type) whose values will be displayed
 *
 * Behavior:
 *   - Uses two nested loops (i for rows, j for columns)
 *   - For each element, prints a field width of 10 characters with 2 decimal places
 *   - After each row, outputs a newline to start the next row
 */
void print_mat(mat MATRIX) {
    int i, j;  /* loop indices for rows and columns */

    for (i = 0; i < MAT_ROWS; i++) {
        for (j = 0; j < MAT_COLS; j++) {
            /* Print each element in fixed-width, two-decimal format */
            printf("%10.2f", MATRIX[i][j]);
        }
        /* End of row: move to next line */
        printf("\n");
    }
}


/*
 * add_mat
 *
 * Performs element-wise addition of two NxN matrices, storing the result
 * in MAT_RESULT. Correctly handles the case where MAT_RESULT aliases
 * one of the source matrices by first copying the aliased input.
 *
 * Parameters:
 *   MAT1       – first input matrix
 *   MAT2       – second input matrix
 *   MAT_RESULT – destination matrix for the sum
 */
void add_mat(mat MAT1, mat MAT2, mat MAT_RESULT) {
    int i, j;  /* loop counters for rows (i) and columns (j) */

    /* Case 1: MAT_RESULT aliases MAT1 */
    if (is_matrix_same(MAT1, MAT_RESULT)) {
        mat TEMP;                 /* temporary buffer to hold original MAT1 */
        copy_mat(MAT1, TEMP);     /* copy MAT1 into TEMP */

        /* Perform addition using TEMP to avoid clobbering MAT1 */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = TEMP[i][j] + MAT2[i][j];
            }
        }
    }
    /* Case 2: MAT_RESULT aliases MAT2 */
    else if (is_matrix_same(MAT2, MAT_RESULT)) {
        mat TEMP;                 /* temporary buffer to hold original MAT2 */
        copy_mat(MAT2, TEMP);     /* copy MAT2 into TEMP */

        /* Perform addition using TEMP to avoid clobbering MAT2 */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = TEMP[i][j] + MAT1[i][j];
            }
        }
    }
    /* Case 3: no aliasing */
    else {
        /* Direct element-wise addition */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = MAT1[i][j] + MAT2[i][j];
            }
        }
    }
}

/*
 * sub_mat
 *
 * Performs element-wise subtraction of two NxN matrices, storing the result
 * in MAT_RESULT. Correctly handles the case where MAT_RESULT aliases
 * one of the source matrices by first copying the aliased input.
 *
 * Parameters:
 *   MAT1       – minuend matrix (from which MAT2 is subtracted)
 *   MAT2       – subtrahend matrix
 *   MAT_RESULT – destination matrix for the difference
 */
void sub_mat(mat MAT1, mat MAT2, mat MAT_RESULT) {
    int i, j;  /* loop counters for rows (i) and columns (j) */

    /* Case 1: MAT_RESULT aliases MAT1 */
    if (is_matrix_same(MAT1, MAT_RESULT)) {
        mat TEMP;                 /* temporary buffer to hold original MAT1 */
        copy_mat(MAT1, TEMP);     /* copy MAT1 into TEMP */

        /* Perform subtraction using TEMP to avoid clobbering MAT1 */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = TEMP[i][j] - MAT2[i][j];
            }
        }
    }
    /* Case 2: MAT_RESULT aliases MAT2 */
    else if (is_matrix_same(MAT2, MAT_RESULT)) {
        mat TEMP;                 /* temporary buffer to hold original MAT2 */
        copy_mat(MAT2, TEMP);     /* copy MAT2 into TEMP */

        /* Perform subtraction using TEMP to avoid clobbering MAT2 */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = MAT1[i][j] - TEMP[i][j];
            }
        }
    }
    /* Case 3: no aliasing */
    else {
        /* Direct element-wise subtraction */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = MAT1[i][j] - MAT2[i][j];
            }
        }
    }
}


/*
 * mul_mat
 *
 * Performs standard matrix multiplication of two NxN matrices:
 *   MAT_RESULT = MAT1 × MAT2
 * Correctly handles aliasing when MAT_RESULT is also one of the inputs
 * by first copying both inputs if necessary.
 *
 * Parameters:
 *   MAT1       – first input matrix (rows of MAT1)
 *   MAT2       – second input matrix (columns of MAT2)
 *   MAT_RESULT – destination matrix for the product
 */
void mul_mat(mat MAT1, mat MAT2, mat MAT_RESULT) {
    int i, j, k;  /* loop counters: i=row index, j=column index, k=inner sum index */

    /* Case: MAT_RESULT aliases either input matrix */
    if (is_matrix_same(MAT1, MAT_RESULT) || is_matrix_same(MAT2, MAT_RESULT)) {
        mat TEMP1, TEMP2;          /* temporaries to hold originals */
        copy_mat(MAT1, TEMP1);     /* copy MAT1 to TEMP1 */
        copy_mat(MAT2, TEMP2);     /* copy MAT2 to TEMP2 */

        /* Multiply using TEMP1 and TEMP2 to avoid overwriting inputs */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                float sum = 0;      /* accumulator for dot product */
                for (k = 0; k < MAT_COLS; k++) {
                    sum += TEMP1[i][k] * TEMP2[k][j];
                }
                MAT_RESULT[i][j] = sum;
            }
        }
    }
    /* No aliasing: safe to multiply directly */
    else {
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                float sum = 0;      /* accumulator for dot product */
                for (k = 0; k < MAT_COLS; k++) {
                    sum += MAT1[i][k] * MAT2[k][j];
                }
                MAT_RESULT[i][j] = sum;
            }
        }
    }
}



/*
 * mul_scalar
 *
 * Multiplies every element of a NxN matrix by a scalar value,
 * storing the result in MAT_RESULT. Handles aliasing by using
 * a temporary copy if MAT_RESULT is the same as MAT1.
 *
 * Parameters:
 *   MAT1       – input matrix to scale
 *   scalar     – floating-point factor to multiply each element by
 *   MAT_RESULT – destination matrix for the scaled result
 */
void mul_scalar(mat MAT1, float scalar, mat MAT_RESULT) {
    int i, j;  /* loop counters for rows (i) and columns (j) */

    /* Case: MAT_RESULT aliases the input MAT1 */
    if (is_matrix_same(MAT1, MAT_RESULT)) {
        mat TEMP;                 /* temporary buffer to hold original MAT1 */
        copy_mat(MAT1, TEMP);     /* copy MAT1 into TEMP */

        /* Multiply each element in TEMP by scalar to avoid overwriting MAT1 */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = TEMP[i][j] * scalar;
            }
        }
    }
    /* No aliasing: safe to multiply directly */
    else {
        /* Direct element-wise multiplication */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = MAT1[i][j] * scalar;
            }
        }
    }
}



/*
 * trans_mat
 *
 * Computes the transpose of a NxN matrix:
 *   MAT_RESULT[j][i] = MAT1[i][j]
 * Handles aliasing by first copying MAT1 if MAT_RESULT == MAT1.
 *
 * Parameters:
 *   MAT1       – input matrix to transpose
 *   MAT_RESULT – destination matrix to receive the transpose
 */
void trans_mat(mat MAT1, mat MAT_RESULT) {
    int i, j;  /* loop counters for original rows (i) and columns (j) */

    /* Case: MAT_RESULT aliases the source MAT1 */
    if (is_matrix_same(MAT1, MAT_RESULT)) {
        mat TEMP;                 /* temporary buffer for original data */
        copy_mat(MAT1, TEMP);     /* copy MAT1 into TEMP */

        /* Write transposed values from TEMP to MAT_RESULT */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[j][i] = TEMP[i][j];
            }
        }
    }
    /* No aliasing: safe to read directly from MAT1 */
    else {
        /* Write transposed values directly from MAT1 */
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[j][i] = MAT1[i][j];
            }
        }
    }
}



/*
 * copy_mat
 *
 * Copies all elements from a N×N source matrix into a destination buffer.
 * Uses two nested loops over rows and columns.
 *
 * Parameters:
 *   MAT1 – source matrix to copy
 *   temp – destination matrix buffer (must be same dimensions)
 */
void copy_mat(mat MAT1, mat temp) {
    int i, j;  /* loop counters for rows (i) and columns (j) */
    for (i = 0; i < MAT_ROWS; i++) {
        for (j = 0; j < MAT_COLS; j++) {
            temp[i][j] = MAT1[i][j];
        }
    }
}

/*
 * is_matrix_same
 *
 * Checks if two matrix variables refer to the exact same memory location.
 * This tests pointer identity, not content equality.
 *
 * Parameters:
 *   mat1 – first matrix
 *   mat2 – second matrix
 *
 * Returns:
 *   1 if both matrix pointers are identical (aliasing), 0 otherwise.
 */
int is_matrix_same(mat mat1, mat mat2) {
    return mat1 == mat2;
}

/*
 * stop
 *
 * Terminates the program immediately.
 * Called when the user enters the "stop" command.
 */
void stop() {
    exit(0);
}
