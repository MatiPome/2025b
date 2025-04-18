#ifndef OUTPUT_H
#define OUTPUT_H

#include "input.h"  // for Status enum

void print_result(int status);
void print_input_error(int s);
void print_error_file(const char *filename);

#endif