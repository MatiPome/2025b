#include "input.h"
#include "magic.h"

int magic(int matrix[N][N]) {
    int target = 0;
    int diag = 0;
    int rev_diag = 0;
    int row = 0;
    int col = 0;
    for (col = 0; col < N; col++) {
        target += matrix[0][col];
        diag += matrix[col][col];
        rev_diag += matrix[col][N-col-1];
    }
    if (target != diag || rev_diag != diag) {
        return STATUS_FAILURE;
    }

    for (row = 0; row < N; row++) {
        int rowSum = 0, colSum = 0;
        for (col = 0; col < N; col++) {
            rowSum += matrix[row][col];
            colSum += matrix[col][row];
        }
        if (rowSum != target || colSum != target)
            return STATUS_FAILURE;
    }

    return STATUS_SUCCESS;
}
