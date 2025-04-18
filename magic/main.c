#include <stdio.h>
#include "input.h"
#include "magic.h"
#include "output.h"

int main(int argc, char *argv[]) {
    FILE *source = stdin;
    int matrix[N][N];

    if (argc == 2) {
        source = fopen(argv[1], "r");
        if (source == NULL) {
            printf("Error: could not open file %s\n", argv[1]);
            return 1;
        }
    }

    Status result = read_matrix(matrix, source);
    if (result != STATUS_SUCCESS) {
        if (result == STATUS_TOO_FEW)
            printf("❌ Not enough numbers (early EOF).\n");
        else if (result == STATUS_NOT_INTEGER)
            printf("❌ Invalid input: expected an integer.\n");
        else if (result == STATUS_TOO_MANY)
            printf("❌ Too many numbers in input.\n");

        if (source != stdin) fclose(source);
        return 1;
    }

    int is_magic = is_magic_square(matrix);
    print_result(is_magic);

    if (source != stdin) fclose(source);
    return 0;
}