#include <stdio.h>
#include "magic.h"

int magic(int matrix[N][N]) {
    int target = 0;
    int diag = 0;
    int row = 0;
    int col = 0;
    for (col = 0; col < N; col++) {
        target += matrix[0][i];
        diag += matrix[i][i];
    }
    if (target != diag) {
        return 0;
    }

    for (int row = 0; row < N; row++) {
        int rowSum = 0, colSum = 0;
        for (int col = 0; col < N; col++) {
            rowSum += matrix[row][col];
            colSum += matrix[col][row];
        }
        if (rowSum != target || colSum != target)
            return 0;
    }

    return 1;
}
