#include <stdio.h>
#include <string.h>
#include "input.h"

int read_matrix(int matrix[N][N], FILE *source) {
    char line[80];
    int row = 0, col = 0;
    char *token;
    int count = 0;
    int value = 0;

    printf("Welcome to the magic square analyzer\n\n");
    printf("The magic square consists of %d rows and columns.\n", N);
    printf("Please input a total of %d numbers (space-separated in one line or multiple lines).\n", N * N);

    while (count < N * N && fgets(line, sizeof(line), source)) {
        token = strtok(line, " \t\n");
        while (token != NULL) {
            if (sscanf(token, "%d", &value) != 1) {
                return STATUS_NOT_INTEGER;
            }

            matrix[row][col] = value;
            col++;
            count++;
            if (col == N) {
                col = 0;
                row++;
            }
            if (count > N * N) {
                return STATUS_TOO_MANY;
            }

            token = strtok(NULL, " \t\n");
        }

    }

    if (count < N * N) {
        return STATUS_TOO_FEW;
    }

    return STATUS_SUCCESS;

}



























/*
int read_matrix(int matrix[N][N], FILE *source) {
    char line[256];
    char *token;
    int count = 0;
    int value;
    int row = 0, col = 0;

    printf("Welcome to the magic square analyzer\n\n");
    printf("The magic square consists of %d rows and columns.\n", N);
    printf("Please input a total of %d numbers (space-separated in one line or multiple lines).\n", N * N);

    while (count < N * N && fgets(line, sizeof(line), source) != NULL) {
        token = strtok(line, " \t\n");
        while (token != NULL) {
            if (sscanf(token, "%d", &value) != 1) {
                return STATUS_NOT_INTEGER;
            }

            matrix[row][col] = value;
            count++;
            col++;
            if (col == N) {
                col = 0;
                row++;
            }

            if (count > N * N) {
                return STATUS_TOO_MANY;
            }

            token = strtok(NULL, " \t\n");
        }
    }

    if (count < N * N) {
        return STATUS_TOO_FEW;
    }

    return STATUS_SUCCESS;
}








 int row, col, count = 1;
 int result;
 int extra;

 printf("Welcome to the magic square analyzer\n\n");
 printf("The magic square consists of %d rows and columns.\n", N);
 printf("Please input a total of %d numbers.\n", N * N);

 for (row = 0; row < N; row++) {
     for (col = 0; col < N; col++) {
         printf("Please enter the number for your magic square (%d out of %d):\n", count, N * N);

         result = fscanf(source, "%d", &matrix[row][col]);
         if (result == EOF) {
             return STATUS_TOO_FEW;
         }
         if (result == 0) {
             return STATUS_NOT_INTEGER;
         }

         count++;
     }
 }




     if (fscanf(source, "%d", &extra) == 1) {
         return STATUS_TOO_MANY;
     }

 printf("All numbers entered. Press Ctrl+D (or Ctrl+Z on Windows) to finish.\n");

 return STATUS_SUCCESS;
}
*/
