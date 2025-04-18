#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "magic.h"

typedef enum {
    STATUS_SUCCESS = 0,
    STATUS_NOT_INTEGER,
    STATUS_TOO_MANY,
    STATUS_TOO_FEW
} Status;

Status read_matrix(int matrix[N][N], FILE *source);

#endif