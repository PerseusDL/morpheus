/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>


cinsert (int c, char *p)
/* insert char c before point p */
{
	register char *enid;

	for (enid = lastn(p,1) + 2; enid > p; enid--)
		*enid = *(enid-1);
	*enid = c;
}
