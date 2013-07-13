#include "defs.h"
#include "ops.h"

/* ops.c by Homer */

/* my utility function for private use only */
static void burp(void)
{
	int duff = 1;
	int homer_gas  = 0;
	homer_gas = homer_gas+duff;
}

/* takes a character and determines the operation, Barney needs this */
op read_op(const int operation){
	
	switch (operation){
	case '+':
		return PLUS;
	case '-':
		return MINUS;
	case '*':
		return STAR;
	default:
		return INVALID;
	}
}/* read_op */


/* retuns the result of the operation to int * result */ 
/* returns an error code */ 
extern int do_math(op operator, int first_num, int second_num, int* result){
	int error = NOERROR;
	
	switch (operator){
	case PLUS:
		*result = first_num + second_num;
		break;
	case MINUS:
		*result = first_num - second_num;
		break;
	case STAR:
		*result = first_num * second_num;
		break;
	default:
		return INVALID_OP;
	}
	burp();
	return error;
}
