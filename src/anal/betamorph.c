#include <gkstring.h>

#include "betamorph.proto.h"

int quickflag;
extern char * anal_buf();

_main(void)
{
	char line[BUFSIZ];
	PrntFlags prntflags  = KEEP_BETA;
	char * s;
	int nverbs = 0;
	int rval;
	
	while(gets(line)) {
		if(  strncmp(line,":le:",4)) {
			continue;
		}
		s = line+4;
		rval = checkstring(s,prntflags);
		printf("%s\t%d\n", s , rval );
		if( ++nverbs > 10 ) break;
		
	}
}