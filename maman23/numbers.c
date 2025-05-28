/* numbers.c - MAMAN 23
 * Converts integers (0–99) into their English word equivalents.
 * Supports input from stdin or "input.txt", and output to stdout or "output.txt".
 * Errors are sent to stderr.
 */

#include <stdio.h>
#include <stdlib.h>

/* Function prototypes */
void print_number_word(int num, FILE *out);
void convert_digits_to_words(FILE *in, FILE *out);

int main(int argc, char *argv[]) {
    FILE *in = NULL;
    FILE *out = NULL;

    if (argc > 3) {
        fprintf(stderr, "Error: Too many arguments\n");
        return 1;
    }

    /* Case 1: No arguments – use default files */
    if (argc == 1) {
        in = fopen("input.txt", "r");
        if (!in) {
            fprintf(stderr, "Error: Cannot open default input file: input.txt\n");
            return 1;
        }
        fprintf(stderr, "[DEBUG] Opened input.txt for reading\n");

        out = fopen("output.txt", "w");
        if (!out) {
            fprintf(stderr, "Error: Cannot open default output file: output.txt\n");
            fclose(in);
            return 1;
        }

    }

    /* Case 2: One argument – use as input, output to stdout */
    else if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            fprintf(stderr, "Error: Cannot open input file: %s\n", argv[1]);
            return 1;
        }
        out = fopen("output.txt", "w");
        if (!out) {
            fprintf(stderr, "Error: Cannot open default output file: output.txt\n");
            fclose(in);
            return 1;
        }
    }

    /* Case 3: Two arguments – input and output files */
    else if (argc == 3) {
        in = fopen(argv[1], "r");
        if (!in) {
            fprintf(stderr, "Error: Cannot open input file: %s\n", argv[1]);
            return 1;
        }


        out = fopen(argv[2], "w");
        if (!out) {
            fprintf(stderr, "Error: Cannot open output file: %s\n", argv[2]);
            fclose(in);
            return 1;
        }

    }

    convert_digits_to_words(in, out);

    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);

    return 0;
}

/* Reads integers from input file and prints their word equivalents */
void convert_digits_to_words(FILE *in, FILE *out) {
    int num;

    while (fscanf(in, "%d", &num) == 1) {
        if (num < 0 || num > 99) {
            fprintf(stderr, "[ERROR] Invalid number %d\n", num);
        } else {
            print_number_word(num, out);
        }
    }
}

/* Converts a single number (0–99) to words and writes it */
void print_number_word(int num, FILE *out) {
    const char *ones[] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };
    const char *teens[] = {
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };
    const char *tens[] = {
        "", "", "twenty", "thirty", "forty", "fifty",
        "sixty", "seventy", "eighty", "ninety"
    };

    if (num < 10) {
        fprintf(out, "%s\n", ones[num]);
    } else if (num < 20) {
        fprintf(out, "%s\n", teens[num - 10]);
    } else {
        int t = num / 10;
        int o = num % 10;
        if (o == 0) {
            fprintf(out, "%s\n", tens[t]);
        } else {
            fprintf(out, "%s %s\n", tens[t], ones[o]);
        }
    }
}


