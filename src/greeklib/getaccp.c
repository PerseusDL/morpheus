/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "getaccp.proto.h"

char *getaccp(char *word, int syll)
{
	register char *p;

	p = getsyll(word,syll);
	if (p == P_ERR)
		return (P_ERR);
	p++;
	while (Is_breath(*p) || Is_quant(*p) )
		p++;
	return (p);
}
