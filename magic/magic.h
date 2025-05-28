#ifndef MAGIC_H
#define MAGIC_H

/*===========================================================================
 * Defines the size of the square matrix used in the magic square project.
 * Change this value to switch between 3×3, 5×5, etc.
 *===========================================================================*/
#define N 3

/*
 * Checks whether the given N×N matrix is a magic square.
 *
 * Parameters:
 *   matrix - a 2D array of size N×N to be tested
 *
 * Returns:
 *   STATUS_SUCCESS (0) if the matrix is a valid magic square
 *   STATUS_FAILURE (1) otherwise
 */
int magic(int matrix[N][N]);

#endif  /* MAGIC_H */
