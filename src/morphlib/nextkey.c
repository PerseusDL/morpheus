/*
 * copyright Gregory Crane
 * February 1987
 */
#include <ctype.h>
#include <string.h>

#include "nextkey.proto.h"
nextkey(char *keylist, char *nextkey)
{
	register char * a = keylist;
	register char * b = nextkey;

	while(isspace(*a)) a++;
	if( !*a ) return(0);
	while(*a && !isspace(*a)) *b++ = *a++;
	*b = 0;
	while(isspace(*a)) a++;
	if( *a ) strcpy(keylist,a);
	else  *keylist = 0;
	return(1);
}
