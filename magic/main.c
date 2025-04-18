#include <stdio.h>
#include "input.h"
#include "magic.h"
#include "output.h"

int main(int argc, char *argv[]) {
    int result;
    int magic_square;
    FILE *source = stdin;
    int matrix[N][N];

    if (argc == 2) {
        source = fopen(argv[1], "r");
        if (source == NULL) {
            print_error_file(argv[1]);
            return 1;
        }
    }

    result = read_matrix(matrix, source);
    if (result != STATUS_SUCCESS) {
        print_input_error(result);
        if (source != stdin) fclose(source);
        return 1;
    }

    magic_square = magic(matrix);
    print_result(magic_square);

    if (source != stdin) fclose(source);
    return 0;
}
