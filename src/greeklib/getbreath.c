/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "getbreath.proto.h"

getbreath(char *p)
{
	while (*p) {
		if  (Is_breath(*p)) {
			return (*p);
		}
		p++;
		}
	return (NOBREATH);
}
