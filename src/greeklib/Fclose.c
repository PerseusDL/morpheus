#include <stdio.h>

#include "Fclose.proto.h"

xFclose(FILE *f)
{
	if( ! f ) {
		fprintf(stderr,"hey! trying to close a NULL pointer!\n");
		return;
	}
	fclose(f);
}

xFree(char *p, char *errmess)
{
	if( ! p ) {
		fprintf(stderr,"asked to free a null pointer for %s!\n", errmess);
		return(-1);
	}
/*  ANSI C does not seem to return an error message!
 *  grc 3/14/91
 *XstrlenXstrlen
	if(  free(p) < 0 ) {
		fprintf(stderr,"could not free pointer for %s!\n", errmess);
		return(-1);
	}
*/
	free(p);
	return(0);
}