/* These are preprocessor directives*/
/* We need to include stdio.h to get printf 
     stdio.h is in the compilers directory so we
     have to enclose it in <>'s*/
#include <stdio.h>
/* io.h has our prototypes for the functions below
   since we have the file right here we use ""'s to
   include it */
#include "io.h"

/* Strings in C are defined as const char* 
    (A pointer to a char) We will talk about
    pointers later.
*/

/* 
 * In all of these functions you will just
 * be making a call to printf to print out something
 * For more information on printf see 
 * http://en.wikipedia.org/wiki/Printf#printf_format_placeholders
 */
void printMessage(const char* string)
{	
	printf("%s\n", string);
}

void printNumber(int a)
{
	printf("%d\n", a);
}

void printHex(int hex)
{
	printf("%x\n", hex);
}

void hi(void)
{	
	printf("%s\n", "Hi There");
}
