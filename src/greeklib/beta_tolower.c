#include <greek.h>

#include "beta_tolower.proto.h"
/*
 * convert from beta code capital letters
 *
 * greg crane
 * may 1988
 */

/*
 * start with something like "*)/andra"
 * and end with "a)/ndra"
 */
beta_tolower(char *word)
{
	register char * s;
	register char * t;

	if( *word != BETA_UCASE_MARKER ) return(0);

	s = word;
	while(!isalpha(*s)&&*s) s++;
	*word = *s;
	strcpy(s,s+1);

}
