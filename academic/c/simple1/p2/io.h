#ifndef IO_H
#define IO_H
/*
 *  Welcome to this .h file
 *  This is called a header file
 *  which gets included into the .c file
 *  and other files that need to use the stuff
 *  defined here. Since main.c uses the functions
 *  defined here it needs to #include the .h file
 *	
 *  Function prototypes 
 *  These exist to let the files who #include
 *  this file that the functions below exist.
 */
 
 
/* Prints "Message: <<string>>" where <<string>> is 
   the string passed to this function */
void printMessage(const char*);

/* Prints "Number: <<number>>" where <<number>> is 
   the number passed to this function */
void printNumber(int);

/* Prints "Number: <<number>>" where <<number>> is 
   the number passed to this function and it 
   prints out number in hexadecimal*/
void printHex(int);

/* Just prints HI THERE */
void hi(void);

#endif