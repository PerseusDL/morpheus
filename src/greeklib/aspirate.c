/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "aspirate.proto.h"

aspirate(char *p)
{
	if (!Is_unasp(*p))
		return;
	switch (*p) {
	case 't':
	case 'd':
		*p = 'q';
		break;
	case 'p':
	case 'b':
		*p = 'f';
		break;
	case 'k':
	case 'g':
		*p = 'x';
		break;
	}
}
