#include "input.h"   /* For status codes */
#include "magic.h"   /* For matrix dimension N */

/*
 * Checks whether the given N×N matrix is a magic square.
 *
 * A magic square is a square matrix in which:
 *  - All rows, columns, and both main diagonals sum to the same value
 *  - The matrix is assumed to contain distinct integers in the range 1..N^2
 *
 * Parameters:
 *   matrix - the N×N matrix to verify
 *
 * Returns:
 *   STATUS_SUCCESS if the matrix is a magic square
 *   STATUS_FAILURE otherwise
 */
int magic(int matrix[N][N]) {
    int target = 0;     /* Target sum: sum of the first row */
    int diag = 0;       /* Sum of the main diagonal (top-left to bottom-right) */
    int rev_diag = 0;   /* Sum of the reverse diagonal (top-right to bottom-left) */
    int row = 0;
    int col = 0;

    /* Calculate the target sum from the first row,
     * and compute both diagonals in the same loop.
     */
    for (col = 0; col < N; col++) {
        target += matrix[0][col];
        diag   += matrix[col][col];
        rev_diag += matrix[col][N - col - 1];
    }

    /* If diagonals don't match the target sum, it's not a magic square */
    if (target != diag || rev_diag != diag) {
        return STATUS_FAILURE;
    }

    /* Check that each row and column sums to the target value */
    for (row = 0; row < N; row++) {
        int rowSum = 0;
        int colSum = 0;
        for (col = 0; col < N; col++) {
            rowSum += matrix[row][col];   /* Sum current row */
            colSum += matrix[col][row];   /* Sum current column */
        }
        if (rowSum != target || colSum != target) {
            return STATUS_FAILURE;
        }
    }

    /* All checks passed — matrix is a magic square */
    return STATUS_SUCCESS;
}

