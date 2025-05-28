#ifndef MYMAT_H
#define MYMAT_H

/* Dimensions of every matrix */
#define MAT_ROWS 4    /* Number of rows per matrix */
#define MAT_COLS 4    /* Number of columns per matrix */
#define MAT_SIZE (MAT_ROWS * MAT_COLS)  /* Total elements in a matrix */

/* Maximum length of an input line in the REPL */
#define MAX_LINE_LENGTH 1000

/*
 * mat
 * A 4×4 matrix type, stored in row-major order.
 */
typedef float mat[MAT_ROWS][MAT_COLS];

/*
 * stop
 * Terminates the program immediately (called by the "stop" command).
 */
void stop();

/*
 * read_mat
 * Loads up to MAT_SIZE floats from arr[] into MATRIX.
 * Unfilled elements (if arr has fewer than MAT_SIZE entries) remain unchanged.
 *
 * Parameters:
 *   MATRIX – target matrix to populate
 *   arr    – array of floats (length MAT_SIZE) containing the values
 */
void read_mat(mat MATRIX, float arr[MAT_SIZE]);

/*
 * print_mat
 * Prints the contents of MATRIX in a 4×4 grid format to stdout.
 *
 * Parameters:
 *   MATRIX – the matrix to display
 */
void print_mat(mat MATRIX);

/*
 * add_mat
 * Computes the element-wise sum of MAT1 and MAT2, storing the result in MAT_RESULT.
 *
 * Parameters:
 *   MAT1, MAT2     – input matrices to add
 *   MAT_RESULT     – output matrix for the sum
 */
void add_mat(mat MAT1, mat MAT2, mat MAT_RESULT);

/*
 * mul_mat
 * Performs matrix multiplication: MAT_RESULT = MAT1 × MAT2.
 *
 * Parameters:
 *   MAT1, MAT2     – input matrices (both 4×4)
 *   MAT_RESULT     – output matrix (4×4 product)
 */
void mul_mat(mat MAT1, mat MAT2, mat MAT_RESULT);

/*
 * sub_mat
 * Computes the element-wise difference: MAT_RESULT = MAT1 − MAT2.
 *
 * Parameters:
 *   MAT1, MAT2     – input matrices
 *   MAT_RESULT     – output matrix for the difference
 */
void sub_mat(mat MAT1, mat MAT2, mat MAT_RESULT);

/*
 * trans_mat
 * Transposes MAT1, storing the result in MAT_RESULT.
 *
 * Parameters:
 *   MAT1           – input matrix to transpose
 *   MAT_RESULT     – output matrix (transpose of MAT1)
 */
void trans_mat(mat MAT1, mat MAT_RESULT);

/*
 * mul_scalar
 * Multiplies every element of MAT1 by scalar, storing in MAT_RESULT.
 *
 * Parameters:
 *   MAT1           – input matrix
 *   scalar         – floating-point factor
 *   MAT_RESULT     – output matrix for the scaled values
 */
void mul_scalar(mat MAT1, float scalar, mat MAT_RESULT);

/*
 * is_matrix_same
 * Compares two matrices for equality.
 *
 * Returns:
 *   1 if all corresponding entries in mat1 and mat2 are equal, 0 otherwise.
 */
int is_matrix_same(mat mat1, mat mat2);

/*
 * copy_mat
 * Copies the contents of MAT1 into temp.
 *
 * Parameters:
 *   MAT1  – source matrix
 *   temp  – destination matrix buffer
 */
void copy_mat(mat MAT1, mat temp);

/*
 * parse_command_line
 * Parses a user‐entered command line, splits into command and arguments,
 * and dispatches to the appropriate handler (read_mat, add_mat, etc.).
 *
 * Parameters:
 *   line – modifiable string containing the full user input
 */
void parse_command_line(char *line);

/*
 * get_matrix_by_name
 * Maps a string like "MAT_A" … "MAT_F" to its corresponding global mat*.
 *
 * Returns:
 *   pointer to the matching matrix, or NULL if the name is invalid.
 */
mat *get_matrix_by_name(char *name);

/*
 * Handlers for each REPL command.
 * Each takes the argument substring (after the command name),
 * parses tokens and commas, validates input, and invokes the core operation.
 */

void handle_add_mat(char *args);       /* for "add_mat" command */
void handle_read_mat(char *args);      /* for "read_mat" command */
void handle_print_mat(char *args);     /* for "print_mat" command */
void handle_trans_mat(char *args);     /* for "trans_mat" command */
void handle_mul_scalar(char *args);    /* for "mul_scalar" command */
void handle_mul_mat(char *args);       /* for "mul_mat" command */
void handle_sub_mat(char *args);       /* for "sub_mat" command */

#endif /* MYMAT_H */

