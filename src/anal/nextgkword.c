#include <gkstring.h>
#define RETURN '\r'
#define NEWLINE '\n'
#define VERTICAL_TAB 013 /* used by MS WORD */
#define IS_RETURN(X) (X == RETURN || X == NEWLINE || X == VERTICAL_TAB )
#define HYPHEN '-'
#define INSCR_LINE '|'

#include "nextgkword.proto.h"

char *
NextGkWord(char *bufp, char *word)
{
	char tmpword[MAXWORDSIZE];
	char * wp = tmpword;
	
startover:
	for(;;) {
		while(*bufp && isspace(*bufp) ) bufp++;
		if( ! *bufp )
			return(NULL);
		if( !isdigit(*bufp) && *bufp != '~' ) /* remember that smk greek
											   * uses more than a-zA-Z to
											   * represent alphabetic chars
											   */
			break;
		while(*bufp && ! isspace(*bufp) ) bufp++;
	}
	
	while(*bufp && ! isspace(*bufp) ) {
		if( * bufp == INSCR_LINE ) {
			bufp++; continue;
		}
		if( isdigit(*bufp) || *bufp == '[' || *bufp == ']') {
			bufp++;
			continue;
		}
		
		if( *bufp == HYPHEN && isspace(*(bufp+1)) ) {
		  skipline:
			while(*bufp && ! IS_RETURN(*bufp) ) bufp++;
			/* *bufp != NEWLINE && *bufp != RETURN ) bufp++;*/
			while(IS_RETURN(*bufp)) bufp++;
			/*
			if( *bufp == RETURN ) bufp++;
			if( *bufp == NEWLINE ) bufp++;
			*/
			if( ! *bufp ) break;
			if( *bufp == '~' ) goto skipline;
			
			while(*bufp && isspace(*bufp)) bufp++;
			if( ! *bufp ) break;
		}
		 *wp++ = *bufp++;
	}
	*wp = 0;
	if( wp == tmpword )
		goto startover;
		
	smk2beta(tmpword,word);
	return(bufp);
}

/*		smk2beta(locbuf,betastring);
			curp = locbuf;
			while(curp=NextGkWord(curp,betastring)) {*/


FILE * fdumpout;

printdump(char *s)
{
	if( ! fdumpout ) {
		fdumpout = fopen("dumpfile","w");
	}
	if( ! fdumpout ) return;
	fprintf(fdumpout,"%s\r", s );
}