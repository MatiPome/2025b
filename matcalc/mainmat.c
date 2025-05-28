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
 * Author: [Matias Pomerantz]
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
    puts("Welcome to the Matrix calculator!");
    for (;;) {
        /* Prompt */

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

void parse_command_line(char *line){
    char *p = line;
    char *cmd, *args;

    /* Trim leading whitespace */
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    /* Check if the input is empty */
    if (*p == '\0') {
        return;
    }

    /* Extract command */
    cmd = p;
    while (*p && !isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p) {
        *p++ = '\0';  /* null-terminate cmd */
    }

    /* Skip whitespace before args */
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    /* If p now points to an empty string, there are no args */
    args = (*p == '\0') ? NULL : p;

    /* Special case: stop */
    if (strcmp(cmd, "stop") == 0) {
        if (args == NULL) {
            puts("program terminated");
            exit(0);
        } else {
            puts("argument after stop");
            return;
        }
    }

    /* Other commands */
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
mat *get_matrix_by_name(char *name)
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
    char *end;
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
        puts("[ERROR]Matrix name missing"); return;
    }

    /*  TRIM trailing spaces in `name` */
    end = name + strlen(name) - 1;
    while (end > name && isspace((unsigned char)*end)) {
        *end-- = '\0';
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
        puts("[ERROR] Invalid matrix name");
        return;
    }

    /* 4. main scan: , value , value … ---------------------------- */
    for (;;) {
        while (isspace((unsigned char)*p)) ++p;    /* skip blanks */

        if (*p == '\0') break;                     /* end of line */

        if (expecting_value) {                     /* ---- NEED VALUE ---- */
            if (*p == ',') {                       /* empty value */
                printf("[ERROR] Missing value at position %d\n", count + 1);
                return;
            }
            if (count < MAT_ROWS * MAT_COLS) {
                values[count] = (float)strtod(p, &end);
                if (end == p) {
                    printf("[ERROR] Invalid float at position %d\n", count + 1);
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
                printf("[ERROR] Missing comma before value %d\n", count + 1);
                return;
            }
            ++p;                                   /* consume comma */
            expecting_value = 1;                   /* next we need value */
        }
    }

    if (count == 0)               { puts("[ERROR] Need at least one value"); return; }
    if (expecting_value == 1)     { puts("[ERROR] Trailing comma after last value"); return; }

    read_mat(*m, values);
    puts("Values successfully inserted!");
}

void handle_print_mat(char *args) {
    char *p = args;    /* p will walk through the args string */
    char *name1;       /* name1 will point to the matrix name token */
    mat *m1;           /* m1 will hold the address of the requested matrix */

    /* 1. Skip any leading whitespace characters (spaces, tabs, etc.) */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* Mark the start of the matrix-name token */
    name1 = p;

    /* 2. Scan forward until we hit either:
     *    - end of string ('\0')
     *    - a comma (',')
     *    - any whitespace character
     * This ensures name1..p–1 is the candidate name.
     */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }

    /* 3. If we consumed zero characters, p == name1 ⇒ no name was provided */
    if (p == name1) {
        printf("[ERROR] No matrix name.\n");
        return;
    }

    /* 4. Skip any trailing whitespace after the token */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 5. If there's anything left (comma or extra text), that's an error */
    if (*p != '\0') {
        printf("[ERROR] Unexpected extra input\n");
        return;
    }

    /* 6. Map the extracted token to one of the global matrices */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        /* If the name wasn’t MAT_A…MAT_F, report invalid name */
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 7. All checks passed—invoke the core print function */
    print_mat(*m1);
}

void handle_add_mat(char *line) {
    char *p = line;    /* p will traverse the argument string */
    char *name1, *name2, *name3;  /* pointers to the three matrix-name tokens */
    mat *m1, *m2, *m3; /* pointers to the actual matrix objects */

    /* 1. Skip any leading whitespace (spaces, tabs) */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 2. Mark the start of the first name token */
    name1 = p;

    /* 3. Scan forward until we hit a comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }

    /* 4. If we didn’t move, there was no name at all */
    if (p == name1) {
        printf("[ERROR] No matrix name.\n");
        return;
    }

    /* 5. Skip any whitespace between the name and the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 6. Ensure there is a comma right after name1 */
    if (*p != ',') {
        printf("[ERROR] Missing comma after first name\n");
        return;
    }

    /* 7. Null-terminate name1 and advance past the comma */
    *p++ = '\0';

    /* 8. Lookup the first matrix by its name */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 9. Skip spaces before the second name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    name2 = p;  /* mark start of second name */

    /* 10. Scan until comma, whitespace, or end */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 11. Check that we actually got a name2 */
    if (p == name2) {
        printf("[ERROR] No matrix name.\n");
        return;
    }
    /* 12. Skip any spaces before the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 13. Ensure comma after name2 */
    if (*p != ',') {
        printf("[ERROR] Missing second comma\n");
        return;
    }

    /* 14. Terminate name2 and advance past comma */
    *p++ = '\0';

    /* 15. Lookup the second matrix */
    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("[ERROR] Invalid matrix name\n");
        return;
    }

    /* 16. Skip spaces before the third name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    name3 = p;  /* mark start of third name */

    /* 17. Scan until comma, whitespace, or end */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 18. Ensure there was actually a name3 */
    if (p == name3) {
        printf("[ERROR] Matrix not found\n");
        return;
    }
    /* 19. Skip any trailing spaces */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 20. After the third name, we expect end-of-string (no comma) */
    if (*p != '\0') {
        printf("[ERROR] Unexpected extra input\n");
        return;
    }

    /* 21. Lookup the third matrix */
    m3 = get_matrix_by_name(name3);
    if (!m3) {
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 22. All tokens valid—perform the addition */
    add_mat(*m1, *m2, *m3);
    printf("successfully add_mat\n");
}

void handle_mul_mat(char *args) {
    char *p = args;      /* p will traverse the input string */
    char *name1, *name2, *name3;  /* pointers to hold the three matrix-name substrings */
    mat *m1, *m2, *m3;   /* pointers to the actual matrix objects */

    /* 1. Skip any leading whitespace before the first name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 2. Mark start of first name token */
    name1 = p;

    /* 3. Scan until comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }

    /* 4. If we consumed no characters, there was no name */
    if (p == name1) {
        printf("[ERROR] No matrix name.\n");
        return;
    }

    /* 5. Skip any whitespace between name1 and the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 6. Expect a comma here; otherwise error */
    if (*p != ',') {
        printf("[ERROR] Missing comma after first name\n");
        return;
    }

    /* 7. Null-terminate name1 and advance past the comma */
    *p++ = '\0';

    /* 8. Lookup the first matrix by its name */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 9. Skip whitespace before the second name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    name2 = p;  /* mark start of second name */

    /* 10. Scan until comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 11. Ensure we actually got a second name */
    if (p == name2) {
        printf("[ERROR] No matrix name.\n");
        return;
    }
    /* 12. Skip whitespace before the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 13. Expect a comma after name2 */
    if (*p != ',') {
        printf("[ERROR] Missing second comma\n");
        return;
    }

    /* 14. Null-terminate name2 and advance past comma */
    *p++ = '\0';

    /* 15. Lookup the second matrix */
    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("[ERROR] Invalid matrix name\n");
        return;
    }

    /* 16. Skip whitespace before the third name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    name3 = p;  /* mark start of third name */

    /* 17. Scan until comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 18. Ensure we consumed at least one character for name3 */
    if (p == name3) {
        printf("[ERROR] Matrix not found\n");
        return;
    }
    /* 19. Skip any trailing whitespace */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 20. After the third name, there must be no comma or extra text */
    if (*p != '\0') {
        printf("[ERROR]Unexpected extra input\n");
        return;
    }

    /* 21. Lookup the third matrix */
    m3 = get_matrix_by_name(name3);
    if (!m3) {
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 22. All names valid—perform the matrix multiplication */
    mul_mat(*m1, *m2, *m3);
    printf("successfully mul_mat\n");
}

void handle_sub_mat(char *args) {
    char *p = args;       /* p will walk through the input string */
    char *name1, *name2, *name3;  /* pointers to hold each matrix-name token */
    mat *m1, *m2, *m3;    /* pointers to the actual matrix objects */

    /* 1. Skip leading whitespace (spaces, tabs) */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 2. Mark the start of the first matrix name */
    name1 = p;

    /* 3. Scan until we hit a comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }

    /* 4. If no characters were consumed, no name was provided */
    if (p == name1) {
        printf("[ERROR] No matrix name.\n");
        return;
    }

    /* 5. Skip any whitespace between the name and the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 6. Expect a comma here; if not, report missing comma */
    if (*p != ',') {
        printf("[ERROR] Missing comma after first name\n");
        return;
    }

    /* 7. Null-terminate name1 and advance past the comma */
    *p++ = '\0';

    /* 8. Lookup the first matrix pointer */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 9. Skip whitespace before the second name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    name2 = p;  /* mark start of second matrix name */

    /* 10. Scan until comma, whitespace, or end */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 11. If no characters consumed, second name is missing */
    if (p == name2) {
        printf("[ERROR] No matrix name.\n");
        return;
    }
    /* 12. Skip whitespace before comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 13. Expect the second comma here */
    if (*p != ',') {
        printf("[ERROR] Missing second comma\n");
        return;
    }

    /* 14. Null-terminate name2 and advance past comma */
    *p++ = '\0';

    /* 15. Lookup the second matrix pointer */
    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("[ERROR] Invalid matrix name\n");
        return;
    }

    /* 16. Skip whitespace before the third name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    name3 = p;  /* mark start of third matrix name */

    /* 17. Scan until comma, whitespace, or end */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 18. If no characters consumed, third name is missing */
    if (p == name3) {
        printf("[ERROR] Matrix not found\n");
        return;
    }
    /* 19. Skip trailing whitespace */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 20. After the third name, there must be no comma or extra text */
    if (*p != '\0') {
        printf("[ERROR] Unexpected extra input\n");
        return;
    }

    /* 21. Lookup the third matrix pointer */
    m3 = get_matrix_by_name(name3);
    if (!m3) {
        printf("[ERROR] Invalid matrix name.\n");
        return;
    }

    /* 22. Perform the subtraction and report success */
    sub_mat(*m1, *m2, *m3);
    printf("successfully sub_mat\n");
}

void handle_trans_mat(char *args) {
    char *p = args;      /* p will traverse the args string */
    char *name1, *name2; /* pointers to hold the source and destination names */
    mat *m1, *m2;        /* will point to the actual matrices */

    /* 1. Skip any leading whitespace before name1 */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 2. Mark start of first token (source matrix name) */
    name1 = p;

    /* 3. Scan until comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 4. If no characters were consumed, name1 is missing */
    if (p == name1) {
        printf("[ERROR] Missing matrix name\n");
        return;
    }

    /* 5. Skip whitespace between name1 and the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 6. Expect a comma here to separate the two names */
    if (*p != ',') {
        printf("[ERROR] Missing comma after first matrix\n");
        return;
    }

    /* 7. Null-terminate name1 and advance past the comma */
    *p++ = '\0';

    /* 8. Lookup the first matrix pointer */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        printf("[ERROR] Invalid Matrix name\n");
        return;
    }

    /* 9. Skip whitespace before the second name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 10. Mark start of second token (destination matrix name) */
    name2 = p;

    /* 11. Scan until comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 12. If we consumed none, the second name is missing */
    if (p == name2) {
        printf("[ERROR] Missing matrix name\n");
        return;
    }

    /* 13. Skip any trailing whitespace after name2 */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 14. After name2, we should be at end-of-string (no comma allowed) */
    if (*p != '\0') {
        printf("[ERROR] Unexpected input after last parameter\n");
        return;
    }

    /* 15. Lookup the second matrix pointer */
    m2 = get_matrix_by_name(name2);
    if (!m2) {
        printf("[ERROR] invalid matrix name\n");
        return;
    }

    /* 16. All validation passed—perform the transpose operation */
    trans_mat(*m1, *m2);
    puts("successfully trans_mat");
}

void handle_mul_scalar(char *args) {
    char *p = args;      /* p traverses the input string */
    char *name1, *name2; /* pointers to hold the two matrix-name tokens */
    char *end;           /* pointer used by strtod to mark end of parse */
    float scalar;        /* the parsed floating-point scalar value */
    mat *m1, *m2;        /* pointers to the actual matrix objects */

    /* 1. Skip leading whitespace before the first matrix name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 2. Mark the start of the first matrix-name token */
    name1 = p;

    /* 3. Scan until we hit a comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 4. If no characters were consumed, the first name is missing */
    if (p == name1) {
        puts("[ERROR] Missing matrix name 1");
        return;
    }

    /* 5. Skip any whitespace before the comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 6. Expect a comma here separating name1 and the scalar */
    if (*p != ',') {
        puts("[ERROR] missing comma after first value");
        return;
    }

    /* 7. Null-terminate name1 and advance past the comma */
    *p++ = '\0';

    /* 8. Lookup the first matrix pointer by name */
    m1 = get_matrix_by_name(name1);
    if (!m1) {
        puts("[ERROR] Invalid matrix name 1");
        return;
    }

    /* 9. Skip whitespace before the scalar token */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 10. Parse the scalar value from the string */
    scalar = strtod(p, &end);
    /* 11. If strtod did not consume any characters, error */
    if (end == p) {
        puts("[ERROR] no scalar found in input");
        return;
    }
    /* 12. Advance p past the parsed number */
    p = end;

    /* 13. Skip whitespace before the next comma */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 14. Expect a comma separating scalar and second matrix name */
    if (*p != ',') {
        puts("[ERROR] missing comma after second value");
        return;
    }

    /* 15. Null-terminate the scalar token and advance past comma */
    *p++ = '\0';

    /* 16. Skip whitespace before the second matrix name */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 17. Mark the start of the second matrix-name token */
    name2 = p;

    /* 18. Scan until comma, whitespace, or end-of-string */
    while (*p && *p != ',' && !isspace((unsigned char)*p)) {
        ++p;
    }
    /* 19. If no characters consumed, second matrix name is missing */
    if (p == name2) {
        puts("[ERROR] Missing matrix name 2");
        return;
    }

    /* 20. Skip any trailing whitespace after name2 */
    while (isspace((unsigned char)*p)) {
        ++p;
    }
    /* 21. After name2, we should be at end-of-string (no extra input) */
    if (*p != '\0') {
        puts("[ERROR] Unexpected value after last argument");
        return;
    }

    /* 22. Lookup the second matrix pointer by name */
    m2 = get_matrix_by_name(name2);
    if (!m2) {
        puts("[ERROR] Invalid matrix name 2");
        return;
    }

    /* 23. All validations passed—perform scalar multiplication */
    mul_scalar(*m1, scalar, *m2);
    puts("successfully mul_scalar");

    /* 24. Completed handle_mul_scalar */
}



