/*
  This is a header file that helps with printf-like calls, wrapping them to
  deal with return values.  You are not expected to understand the contents
  for this lab, but you are allowed to use this header file in any future
  submissions you make in this course (you must include defs.h in your turnin
  if you use it!)
*/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


/*
 * STRINGIZE macro - see Weiss, pages 108-109
 */

#define STRINGIZE( s )		#s

/*
 * This defines compiler values for FAILURE and SUCCESS, as well as
 * convenience macros for testing the return values of functions that
 * return a "boolean" type. Since C does not have true booleans, it 
 * is best to do explicit comparisons to predefined values to 
 * determine the success or failure of a function.
 *
 * These macros simplify that task, while at the same time abstracting
 * away specific details of how the return value is tested.
 */

enum { FAILURE, SUCCESS };

#define SUCCEEDS( m )		( ( m ) != FAILURE )
#define FAILS( m )		( ( m ) == FAILURE )

/*
 * Ditto for UNSET and SET, which can be used for "flag" variables
 */

enum { UNSET, SET };

#define IS_SET( m )		( ( m ) != UNSET )
#define NOT_SET( m )		( ( m ) == UNSET )

/*
 * The ERR_MSG macro prints a message on stderr describing where an
 * error occured and what its cause was (if known)
 */

#define ERR_MSG( func )						\
    { 								\
	( void )fflush( stderr );				\
	( void )fprintf( stderr, __FILE__ ":%d:" #func ": %s\n",\
		__LINE__, strerror( errno ) );			\
    }

/*
 * PRINTF_LIKE macro
 *
 * This macro is a wrapper for functions (like printf(3s))
 * that people tend to want to ignore the return value of.
 * Since printf(3s) can have a variable number of arguments, we
 * must rely on a "trick" to get the macro properly expanded.
 *
 * To use this macro, substitute PRINTF(( ... )) everywhere you
 * would normally use printf( ... ). Note the use of the double
 * parentheses (that is the "trick").
 */

#define PRINTF_LIKE( fn, args, test )	if( fn args test ) ERR_MSG( fn )

/*
 * PRINTF_LIKE functions - these require the (( ... )) "trick"
 * because they take a variable number of arguments
 */

#define PRINTF( args )		PRINTF_LIKE( printf, args, < 0 )
#define FPRINTF( args )		PRINTF_LIKE( fprintf, args, < 0 )
#define SPRINTF( args )		PRINTF_LIKE( sprintf, args, < 0 )

#define SCANF( args )		PRINTF_LIKE( scanf, args, < 0 )
#define FSCANF( args )		PRINTF_LIKE( fscanf, args, < 0 )
#define SSCANF( args )		PRINTF_LIKE( sscanf, args, < 0 )

/*
 * fflush doesn't "technically" need the (( ... )) trick, but it is
 * included for the sake of consistency with the above stdio functions
 */

#define FFLUSH( args )		PRINTF_LIKE( fflush, args, < 0 )

/*
 * The STR_LIKE macro is a wrapper for functions (like strcat(3c))
 * that people tend to want to ignore the return value of. Its main
 * purpose is to check the return value, which keeps lint happy.
 */

#define STR_LIKE( fn, s1, s2 )		if( fn( s1, s2 ) != s1 ) ERR_MSG( fn )

/*
 * The STRN_LIKE macro is a wrapper for functions (like strncat(3c))
 * that people tend to want to ignore the return value of. Its main
 * purpose is to check the return value, which keeps lint happy.
 */

#define STRN_LIKE( fn, s1, s2, n )	if( fn( s1, s2, n ) != s1 ) ERR_MSG( fn )

/*
 * STR_LIKE and STRN_LIKE functions - single parens work fine here
 */

#define STRCAT( s1, s2 )	STR_LIKE( strcat, (s1), (s2) )
#define STRCPY( s1, s2 )	STR_LIKE( strcpy, (s1), (s2) )

#define STRNCAT( s1, s2, n )	STRN_LIKE( strncat, (s1), (s2), (n) )
#define STRNCPY( s1, s2, n )	STRN_LIKE( strncpy, (s1), (s2), (n) )

