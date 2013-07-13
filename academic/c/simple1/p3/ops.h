#ifndef LAB5_OPS_H
#define LAB5_OPS_H
/* ops.h written by Homer Simpson */

typedef enum { PLUS, MINUS, STAR, INVALID } op;
enum { NOERROR, INVALID_OP };

/* This figures out which operation to use */
op read_op(const int operation);


/* do_math() does the math based on the parameters  */
/* it puts the result in result */
int do_math(op operator, int first, int second, int* result);

#endif /* ifndef LAB5_OPS_H */
