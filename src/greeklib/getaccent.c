/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "getaccent.proto.h"

int getaccent(char *word, int syll)
{
	register char *p;

	p = getaccp(word,syll);
	if (p == P_ERR)
		return (C_ERR);
	if Is_accent(*p)
		return (*p);
	return (NOACCENT);
}
