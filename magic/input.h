#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "magic.h"

/* Input error codes */
#define STATUS_SUCCESS 0
#define STATUS_FAILURE 1
#define STATUS_NOT_INTEGER 2
#define STATUS_TOO_MANY 3
#define STATUS_TOO_FEW 4

int read_matrix(int matrix[N][N], FILE *source);

#endif