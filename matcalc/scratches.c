// matrix_calc.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define N 3
#define MAT_ROWS N
#define MAT_COLS N

typedef float mat[N][N];

mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;

// === Function declarations ===
void stop(void);
void parse_command_line(char *line);
void handle_add_mat(char *args);
void handle_read_mat(char *args);
void handle_print_mat(char *args);
mat *get_matrix_by_name(const char *name);
void add_mat(mat MAT1, mat MAT2, mat MAT_RESULT);
void read_mat(mat m, float values[]);
void print_mat(mat MATRIX);
int is_matrix_same(mat a, mat b);
void copy_mat(mat src, mat dest);

// === Main Loop ===
int main(void) {
    char line[MAX_LINE_LENGTH];
    while (1) {
        printf("Insert your command:\n");
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = '\0';
        if (strspn(line, " \t") == strlen(line)) continue; // Skip empty lines
        parse_command_line(line);
    }
    return 0;
}

// === Command Parser ===
void parse_command_line(char *line) {
    char *cmd = strtok(line, " \t");
    if (!cmd) return;

    char *args = strtok(NULL, "");

    if (strcmp(cmd, "stop") == 0) {
        stop();
        return;
    }

     else if (strcmp(cmd, "add_mat") == 0) {
        handle_add_mat(args);
    } else if (strcmp(cmd, "read_mat") == 0) {
        handle_read_mat(args);
    } else if (strcmp(cmd, "print_mat") == 0) {
        handle_print_mat(args);
    } else {
        printf("Unknown command: %s\n", cmd);
    }
}

// === Matrix Name Resolver ===
mat *get_matrix_by_name(const char *name) {
    if (strcmp(name, "MAT_A") == 0) return &MAT_A;
    if (strcmp(name, "MAT_B") == 0) return &MAT_B;
    if (strcmp(name, "MAT_C") == 0) return &MAT_C;
    if (strcmp(name, "MAT_D") == 0) return &MAT_D;
    if (strcmp(name, "MAT_E") == 0) return &MAT_E;
    if (strcmp(name, "MAT_F") == 0) return &MAT_F;
    return NULL;
}

// === Matrix Operations ===
void add_mat(mat MAT1, mat MAT2, mat MAT_RESULT) {
    if (is_matrix_same(MAT1, MAT_RESULT)) {
        mat TEMP;
        copy_mat(MAT1, TEMP);
        for (int i = 0; i < MAT_ROWS; i++) {
            for (int j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = TEMP[i][j] + MAT2[i][j];
            }
        }
    } else if (is_matrix_same(MAT2, MAT_RESULT)) {
        mat TEMP;
        copy_mat(MAT2, TEMP);
        for (int i = 0; i < MAT_ROWS; i++) {
            for (int j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = TEMP[i][j] + MAT1[i][j];
            }
        }
    } else {
        for (int i = 0; i < MAT_ROWS; i++) {
            for (int j = 0; j < MAT_COLS; j++) {
                MAT_RESULT[i][j] = MAT1[i][j] + MAT2[i][j];
            }
        }
    }
}

void read_mat(mat m, float values[]) {
    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = values[k++];
        }
    }
}

void print_mat(mat MATRIX) {
    for (int i = 0; i < MAT_ROWS; i++) {
        for (int j = 0; j < MAT_COLS; j++) {
            printf("%10.2f", MATRIX[i][j]);
        }
        printf("\n");
    }
}

int is_matrix_same(mat a, mat b) {
    return a == b;
}

void copy_mat(mat src, mat dest) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

/*
* mainmat.c - Matrix calculator command-line interface
 *
 * Implements a REPL (Read-Eval-Print Loop) that accepts textual commands
 * to manipulate fixed-size matrices (MAT_A through MAT_F).
 * Conforms to ISO C90: all declarations appear before code in blocks.
 *
 * Supported commands:
 *   stop                         - Exit the program
 *   read_mat <M>,<v1>,<v2>,...   - Load values into matrix M
 *   print_mat <M>                - Print matrix M's contents
 *   add_mat <M1>,<M2>,<M3>       - Compute M3 = M1 + M2
 *   sub_mat <M1>,<M2>,<M3>       - Compute M3 = M1 - M2
 *   mul_scalar <M1>,<s>,<M2>     - Compute M2 = M1 * scalar s
 *   mul_mat <M1>,<M2>,<M3>       - Compute M3 = M1 * M2
 *   trans_mat <M1>,<M2>          - Compute M2 = transpose(M1)
 *
 * Author: [Your Name]
 */

#include <stdio.h>    /* printf, puts, fgets */
#include <string.h>   /* strcmp, strlen, strspn, strcspn */
#include <stdlib.h>   /* strtod, exit */
#include <ctype.h>    /* isspace, isspace */
#include "mymat.h"   /* matrix type, dimensions, core operations */

/*
 * File-scope matrices with internal linkage.
 * These are zero-initialized before main() and exist for program duration.
 */

static mat MAT_A;
static mat MAT_B;
static mat MAT_C;
static mat MAT_D;
static mat MAT_E;
static mat MAT_F;


/*
 * main - entry point: continually prompt user and dispatch commands
 */
int main(void) {
    char line[MAX_LINE_LENGTH];
    for (;;) {
        /* Prompt */
        puts("Welcome to the Matrix calculator!");
        puts("Please insert your command (type 'stop' to exit):");

        /* Read a full line, exit on EOF */
        if (!fgets(line, sizeof line, stdin)) {
            puts("EOF reached, exiting.");
            break;
        }
        /* Strip trailing newline */
        line[strcspn(line, "\n")] = '\0';
        /* Ignore lines containing only whitespace */
        if (strspn(line, " \t") == strlen(line)) {
            continue;
        }
        /* Parse and execute */
        parse_command_line(line);
    }
    return 0;
}

void parse_command_line(char *line)
{
    char *p = line;
    char *cmd;
    char *args;
    /* Skip leading whitespace */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* Empty input? */
    if (*p == '\0') {
        return;
    }
    /* Extract command token */
    cmd = p;
    while (*p && !isspace((unsigned char)*p)) {
        ++p;
    }
    if (p == cmd) {
        return;
    }
    *p++ = '\0';  /* Terminate cmd and advance pointer */
    /* Skip spaces to arguments */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    args = (*p ? p : NULL);

    /* Dispatch to specific handlers */
    if (strcmp(cmd, "stop") == 0) {
        exit(0);
    }
    if (strcmp(cmd, "read_mat") == 0 && args) {
        handle_read_mat(args);
    } else if (strcmp(cmd, "print_mat") == 0 && args) {
        handle_print_mat(args);
    } else if (strcmp(cmd, "add_mat") == 0 && args) {
        handle_add_mat(args);
    } else if (strcmp(cmd, "sub_mat") == 0 && args) {
        handle_sub_mat(args);
    } else if (strcmp(cmd, "mul_scalar") == 0 && args) {
        handle_mul_scalar(args);
    } else if (strcmp(cmd, "mul_mat") == 0 && args) {
        handle_mul_mat(args);
    } else if (strcmp(cmd, "trans_mat") == 0 && args) {
        handle_trans_mat(args);
    } else {
        printf("Undefined command or missing args: '%s'\n", cmd);
    }
}

/*
 * get_matrix_by_name - map "MAT_X" strings to corresponding matrix pointers.
 * Returns NULL if the name is invalid.
 */
mat *get_matrix_by_name(const char *name)
{
    if (!name) return NULL;
    if (strcmp(name, "MAT_A") == 0) return &MAT_A;
    if (strcmp(name, "MAT_B") == 0) return &MAT_B;
    if (strcmp(name, "MAT_C") == 0) return &MAT_C;
    if (strcmp(name, "MAT_D") == 0) return &MAT_D;
    if (strcmp(name, "MAT_E") == 0) return &MAT_E;
    if (strcmp(name, "MAT_F") == 0) return &MAT_F;
    return NULL;
}


void handle_read_mat(char *line)
{
    char  *p = line, *name;
    float  values[MAT_ROWS * MAT_COLS] = {0};
    int    count = 0;                     /* floats stored      */
    int    expecting_value;               /* 1 = need value, 0 = need comma */
    mat   *m;


    /* 1. skip leading spaces ------------------------------------- */
    while (isspace((unsigned char)*p)) ++p;

    /* 2. extract matrix name ------------------------------------- */
    name = p;
    while (*p && !isspace((unsigned char)*p) && *p != ',') {
        ++p;
    }
    if (p == name) {
        puts("Matrix name missing"); return;
    }

    /* did the name end with a comma? */
    if (*p == ',') {                 /* comma stuck to name */
        *p++ = '\0';
        expecting_value = 1;         /* next token must be a value */
    } else {
        *p++ = '\0';
        expecting_value = 0;         /* we still need a comma */
    }

    /* 3. validate matrix name ------------------------------------ */
    m = get_matrix_by_name(name);
    if (!m) {
        puts("Invalid matrix name");
        return;
    }

    /* 4. main scan: , value , value … ---------------------------- */
    for (;;) {
        while (isspace((unsigned char)*p)) ++p;    /* skip blanks */

        if (*p == '\0') break;                     /* end of line */

        if (expecting_value) {                     /* ---- NEED VALUE ---- */
            char *end;
            if (*p == ',') {                       /* empty value */
                printf("Missing value at position %d\n", count + 1);
                return;
            }
            if (count < MAT_ROWS * MAT_COLS) {
                values[count] = (float)strtod(p, &end);
                if (end == p) {
                    printf("Invalid float at position %d\n", count + 1);
                    return;
                }
                ++count;

                                  /* next we need comma */
            } else {                               /* skip extra numbers */
                expecting_value = 0;
                break;
            }
            p = end;
            expecting_value = 0;

        } else {                                   /* ---- NEED COMMA ---- */
            if (*p != ',') {
                printf("Missing comma before value %d\n", count + 1);
                return;
            }
            ++p;                                   /* consume comma */
            expecting_value = 1;                   /* next we need value */
        }
    }

    if (count == 0)               { puts("Need at least one value"); return; }
    if (expecting_value == 1)     { puts("Trailing comma after last value"); return; }

    read_mat(*m, values);
    puts("Values successfully inserted!");
}

void handle_print_mat(char *args) {
    char *name;
    char *extra;
    mat *m;

    name = strtok(args, " \t,");
    if (!name) {
        printf("Missing argument value to print\n");
        return;
    }

    m = get_matrix_by_name(name);
    if (!m) {
        printf("Invalid Matrix name\n");
        return;
    }

    extra = strtok(NULL, " \t,");
    if (extra && *extra != '\0' && strspn(extra, " \t") != strlen(extra)) {
        printf("Error: Unexpected input after last parameter.\n");
        return;
    }

    print_mat(*m);
}



void handle_add_mat(char *line) {
    char *p = line, *name1, *name2, *name3;
    mat *m1;
    mat *m2;
    mat *m3;

    /* skip leading spaces */
    while (isspace((unsigned char)*p)) ++p;
    name1 = p;

    /* scan to comma or whitespace */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;

    /* no name? */
    if (p == name1) {
        printf("No matrix name.\n");
        return;
    }
    /* read until comma or whitespace */
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma after first name\n");
        return;
    }

    /* terminate name1 and advance */
    *p++ = '\0';


    /* now lookup just "MAT_A" */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("Invalid matrix name.\n");
        return;
    }

              /* terminate name1 */

    /* skip spaces, expect name2 */
    while (isspace((unsigned char)*p)) ++p;
    name2 = p;

    /* scan to comma or whitespace */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;    /* no name? */
    if (p == name2) {
        printf("No matrix name.\n");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    if (*p !=',') {
        printf("Missing second comma\n");
        return;
    }

    *p++ = '\0';

    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("Invalid matrix name\n");
        return;
    }

        /* terminate name2 */

    /* skip spaces, expect name3 */
    while (isspace((unsigned char)*p)) ++p;
    name3 = p;
    /* consume until end or stray comma */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name3) {
        printf("Matrix not found\n");
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma\n");
        return;
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != '\0') {
        printf("Unexpected extra input\n");
        return;
    }

    /* now lookup and dispatch */

    m3 = get_matrix_by_name(name3);
    if (!m3) {
        printf("Invalid matrix name.\n");
        return;
    }
    add_mat(*m1, *m2, *m3);
    printf("successfully add_mat");
}



void handle_trans_mat(char *args) {
    char *p = args;
    char *name1, *name2;
    mat *m1, *m2;

    while (isspace((unsigned char)*p)) ++p;
    name1 = p;

    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name1) {
        printf("Missing matrix name\n");
        return;
    }


    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma after first matrix\n");
        return;
    }

    *p++ ='\0';

    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("Invalid Matrix name\n");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    name2 = p;

    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name1) {
        printf("Missing matrix name\n");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    if (*p != '\0') {
        printf("Unexpected input after last parameter\n");
        return;
    }
    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("invalid matrix name\n");
        return;
    }


    trans_mat(*m1, *m2);
}







void handle_mul_scalar(char *args) {
    char *name1;
    char *name2;
    char *p = args;
    char *end;
    float scalar;
    mat *m1;
    mat *m2;

    while (isspace((unsigned char)*p)) ++p;
    name1 = p;

    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name1) {
        puts("Missing matrix name 1");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        puts("missing comma after first value");
        return;
    }

    *p++ = '\0';

    m1= get_matrix_by_name(name1);
    if (!m1) {
        puts("Invalid matrix name 1");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    scalar = strtod(p, &end);
    if (end == p) {
        puts("no scalar found in input");
        return;
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        puts("missing comma after second value");
        return;
    }

    *p++ = '\0';

    while (isspace((unsigned char)*p)) ++p;
    name2 = p;
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name2) {
        puts("Missing matrix name 2");
        return;
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != '\0') {
        puts("Unexpected value after last argument");
        return;
    }


    m2= get_matrix_by_name(name2);
    if (!m2) {
        puts("Invalid matrix name 2");
        return;
    }

    mul_scalar(*m1, scalar, *m2);

    /* terminate mul_scalar */

}

void handle_mul_mat (char *args) {
    char *p = args, *name1, *name2, *name3;
    mat *m1;
    mat *m2;
    mat *m3;

    /* skip leading spaces */
    while (isspace((unsigned char)*p)) ++p;
    name1 = p;

    /* scan to comma or whitespace */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;

    /* no name? */
    if (p == name1) {
        printf("No matrix name.\n");
        return;
    }
    /* read until comma or whitespace */
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma after first name\n");
        return;
    }

    /* terminate name1 and advance */
    *p++ = '\0';


    /* now lookup just "MAT_A" */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("Invalid matrix name.\n");
        return;
    }

              /* terminate name1 */

    /* skip spaces, expect name2 */
    while (isspace((unsigned char)*p)) ++p;
    name2 = p;

    /* scan to comma or whitespace */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;    /* no name? */
    if (p == name2) {
        printf("No matrix name.\n");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    if (*p !=',') {
        printf("Missing second comma\n");
        return;
    }

    *p++ = '\0';

    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("Invalid matrix name\n");
        return;
    }

        /* terminate name2 */

    /* skip spaces, expect name3 */
    while (isspace((unsigned char)*p)) ++p;
    name3 = p;
    /* consume until end or stray comma */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name3) {
        printf("Matrix not found\n");
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma\n");
        return;
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != '\0') {
        printf("Unexpected extra input\n");
        return;
    }

    /* now lookup and dispatch */

    m3 = get_matrix_by_name(name3);
    if (!m3) {
        printf("Invalid matrix name.\n");
        return;
    }
    mul_mat(*m1, *m2, *m3);
    printf("successfully mul_mat");
}

void handle_sub_mat(char *args) {
    char *p = args, *name1, *name2, *name3;
    mat *m1;
    mat *m2;
    mat *m3;

    /* skip leading spaces */
    while (isspace((unsigned char)*p)) ++p;
    name1 = p;

    /* scan to comma or whitespace */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;

    /* no name? */
    if (p == name1) {
        printf("No matrix name.\n");
        return;
    }
    /* read until comma or whitespace */
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma after first name\n");
        return;
    }

    /* terminate name1 and advance */
    *p++ = '\0';


    /* now lookup just "MAT_A" */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("Invalid matrix name.\n");
        return;
    }

              /* terminate name1 */

    /* skip spaces, expect name2 */
    while (isspace((unsigned char)*p)) ++p;
    name2 = p;

    /* scan to comma or whitespace */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;    /* no name? */
    if (p == name2) {
        printf("No matrix name.\n");
        return;
    }

    while (isspace((unsigned char)*p)) ++p;
    if (*p !=',') {
        printf("Missing second comma\n");
        return;
    }

    *p++ = '\0';

    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("Invalid matrix name\n");
        return;
    }

        /* terminate name2 */

    /* skip spaces, expect name3 */
    while (isspace((unsigned char)*p)) ++p;
    name3 = p;
    /* consume until end or stray comma */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) ++p;
    if (p == name3) {
        printf("Matrix not found\n");
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != ',') {
        printf("Missing comma\n");
        return;
    }
    while (isspace((unsigned char)*p)) ++p;
    if (*p != '\0') {
        printf("Unexpected extra input\n");
        return;
    }

    /* now lookup and dispatch */

    m3 = get_matrix_by_name(name3);
    if (!m3) {
        printf("Invalid matrix name.\n");
        return;
    }

    sub_mat(*m1, *m2, *m3);
    printf("successfully sub_mat");
}