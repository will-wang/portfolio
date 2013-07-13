#include "io.h"

/* Main this is the entry point of our little program*/
int main(void)
{
	const char* str = "Imma kill you fool!";
	printMessage(str);	/* Call Print Message and pass it a message (preferably something funny)*/
	printNumber(42);	/* Call print int with the number 42 */
	printHex(0xDEADBEEF);	/* Call print hex with the hex DEADBEEF */
	hi();			/* Call hi here */
	return 0;
}
