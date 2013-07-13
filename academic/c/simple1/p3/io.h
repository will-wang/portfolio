#ifndef LAB5_IO_H
#define LAB5_IO_H

#include "ops.h"

/* io.h written by Moe Szyslak  */

/* This is an internal structure, don't worry about it */
typedef struct simple_expression {
	op operation;
	int first;
	int second;
	int result;
} s_expr;

/* reads one line from a file, Barney needs this */
int read_input(FILE *input, char *buffer, int size);

/* parses an expression from a line */
static int parse_line(char* line, s_expr *se);

/* prints out the result of an operation */
void print_output(int result);

#endif /* ifndef LAB5_IO_H */
