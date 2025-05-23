#include <stdio.h>
#include "output.h"
#include "magic.h"
#include "input.h"

void print_result(int status) {
    if (status == STATUS_SUCCESS)
        printf("The matrix is a magic square.\n");
    else
        printf("The matrix is not a magic square.\n");
}

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

