/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "naccents.proto.h"

int naccents(char *p)
{
	register int r;

	r = 0;
	while (*p) {
		if (Is_accent(*p))
			r++;
		p++;
		}
	return (r);
}
