#include <gkstring.h>

#include "addninfix.proto.h"

/*
 * grc 9/17/88
 *
 * maq --> manq
 * a(d --> a(nd
 * etc.
 */
addninfix(char *word)
{
	char * syllp;
	char *getaccp();
	int c = 'n';
	

	if( nsylls(word) > 1 ) 
		return(0);
	syllp = getaccp(word,ULTIMA);
	if( syllp == P_ERR ) return(0);

	if( Is_labial(*syllp) ) 
		c = 'm';
	else if( Is_palatal(*syllp) )
		c = 'g';
		
	cinsert(c,syllp);
	return(1);
}
	