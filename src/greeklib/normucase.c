#include <greek.h>

#include "normucase.proto.h"
/*
 * convert from beta code capital letters
 *
 * greg crane
 * february 1987
 */

/*
 * start with something like "*(/ellhn"
 * and end with "E(/llhn"
 */
normucase(char *word)
{
	register char * s;
	register char * t;

	if( *word != BETA_UCASE_MARKER ) return(0);

	s = word;
	while(!isalpha(*s)&&*s) s++;

	/*
	 * in case of "*(/ellhn", s points now to "ellhn"
 	 */
	if( ! islower(*s) )
		return(0);
	*word = toupper(*s);
	/*
 	 * word now "E(/ellhn"
	 */
	t = s+1;
	strcpy(s,t);
	/*
 	 * word now "E(/llhn"
	 */
}
