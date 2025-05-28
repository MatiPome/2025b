/* test_matcalc.c
 *
 * ISO C90–compliant test harness for the matrix calculator.
 * Compile with:
 *   gcc -std=c90 -Wall -Wextra -pedantic -o test_matcalc mymat.c test_matcalc.c
 */

#include <stdio.h>
#include <string.h>
#include "mymat.h"

/* mats_equal: returns 1 if two matrices have identical elements, 0 otherwise */
static int mats_equal(mat A, mat B)
{
    int i, j;
    for (i = 0; i < MAT_ROWS; i++) {
        for (j = 0; j < MAT_COLS; j++) {
            if (A[i][j] != B[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

/* check: prints PASS or FAIL for a given test name */
static void check(const char *test, int condition)
{
    printf("%-25s : %s\n", test, condition ? "PASS" : "FAIL");
}

int main(void)
{
    mat A;
    mat B;
    mat R;
    mat T;
    float arr[MAT_SIZE];
    int i, j;

    /* Initialize A = 1..16, B = 16..1 */
    for (i = 0; i < MAT_ROWS; i++) {
        for (j = 0; j < MAT_COLS; j++) {
            A[i][j] = (float)(i * MAT_COLS + j + 1);
            B[i][j] = (float)(MAT_SIZE - (i * MAT_COLS + j));
        }
    }

    /* Test read_mat */
    for (i = 0; i < MAT_SIZE; i++) {
        arr[i] = (float)(i + 1);
    }
    read_mat(R, arr);
    check("read_mat sequential", mats_equal(R, A));

    /* Test add_mat */
    add_mat(A, B, R);
    {
        mat E;
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                E[i][j] = A[i][j] + B[i][j];
            }
        }
        check("add_mat A+B", mats_equal(R, E));
    }

    /* Test sub_mat */
    sub_mat(A, B, R);
    {
        mat E;
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                E[i][j] = A[i][j] - B[i][j];
            }
        }
        check("sub_mat A-B", mats_equal(R, E));
    }

    /* Test mul_scalar */
    mul_scalar(A, 2.0f, R);
    {
        mat E;
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                E[i][j] = A[i][j] * 2.0f;
            }
        }
        check("mul_scalar A*2", mats_equal(R, E));
    }

    /* Test mul_mat */
    mul_mat(A, B, R);
    {
        mat E;
        int k;
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                float sum = 0.0f;
                for (k = 0; k < MAT_COLS; k++) {
                    sum += A[i][k] * B[k][j];
                }
                E[i][j] = sum;
            }
        }
        check("mul_mat A*B", mats_equal(R, E));
    }

    /* Test trans_mat */
    trans_mat(A, R);
    {
        mat E;
        for (i = 0; i < MAT_ROWS; i++) {
            for (j = 0; j < MAT_COLS; j++) {
                E[j][i] = A[i][j];
            }
        }
        check("trans_mat A", mats_equal(R, E));
    }

    /* Test aliasing detection */
    memcpy(T, A, sizeof(A));
    check("is_matrix_same(A,A)", is_matrix_same(A, A));
    check("is_matrix_same(A,T)", !is_matrix_same(A, T));

    printf("All tests complete.\n");
    return 0;
}

