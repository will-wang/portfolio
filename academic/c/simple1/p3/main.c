#include "defs.h"
#include <stdio.h>
#include "io.h"

/* main.c written by Barney Gumbel */

static int barney_gas;

/* this is only useful to me, in this file  -- Barney*/
static int burp(int duff)
{
	return barney_gas += duff;
}


int main(int argc, char* argv[])
{
	int noise = burp(argc);
	FILE *fp;
	char line[256];
	s_expr exp;

	if (argc < 2) {
		PRINTF(("Usage: %s [filename]\n", argv[0]));
		return EXIT_FAILURE;
	}
	
	if ((fp = fopen(argv[1], "r")) == NULL){
		FPRINTF((stderr,"Unable to open file %s!\n", argv[1]));
		return EXIT_FAILURE;
	}

	while(read_input(fp, line, 256) != FAILURE){
		if( FAILURE == parse_line(line,&exp)){
			FPRINTF((stderr,"Parsing Error\n"));
			if (fclose(fp) < 0) {
				FPRINTF((stderr,"Doh!\n"));
			}
			return EXIT_FAILURE;
		}
		if(NOERROR != do_math(exp.operation,exp.first,exp.second,&(exp.result))){
			FPRINTF((stderr,"DOh! Error in math operations\n"));
			return EXIT_FAILURE;
		}
		print_output(exp.result);
		noise += burp(noise);
	}

	
	if (fclose(fp) < 0) {
		PRINTF(("I think I need to go to Moe's Tavern\n"));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
