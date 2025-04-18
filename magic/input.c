#include <stdio.h>
#include "input.h"

Status read_matrix(int matrix[N][N], FILE *source) {
    int row, col, count = 1;

    printf("Welcome to the magic square analyzer\n\n");
    printf("The magic square consists of %d rows and columns.\n", N);
    printf("Please input a total of %d numbers.\n", N * N);

    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            printf("Please enter the number for your magic square (%d out of %d):\n", count, N * N);
            int result = fscanf(source, "%d", &matrix[row][col]);

            if (result == EOF)
                return STATUS_TOO_FEW;
            if (result == 0)
                return STATUS_NOT_INTEGER;

            count++;
        }
    }

    int extra;
    if (fscanf(source, "%d", &extra) == 1) {
        return STATUS_TOO_MANY;
    }

    return STATUS_SUCCESS;
}