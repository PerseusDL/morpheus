/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "strsqz.proto.h"

strsqz(char *p, int n)
/* squeeze out n chars beginning with *p  */
{
	register char *enid;

	for (enid = p+n;*enid && *p; enid++, p++)
		*p = *enid;
	*p = *enid;	/* move the null too */
}
