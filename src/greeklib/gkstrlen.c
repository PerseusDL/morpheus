/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "gkstrlen.proto.h"

int gkstrlen(char *s)
{
	register int n;

	n = Xstrlen(s);
	if (*s == GKPRT_OFF) {
		s++;
		n--;
		}
/*assume for now that you always call this on Greek
	if (grkchars) */
		for (;*s;s++)
			if (Is_diacrit(*s) && !Is_quant(*s))
				n--;
	return (n);
}
