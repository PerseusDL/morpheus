/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "shortanalog.proto.h"

shortanalog(char *p)
/* change long vowel in syll pointed to by p to its short analog */
{
	switch (*p) {
		case 'h':
			*p = 'e';
			break;
		case 'w':
			*p = 'o';
			break;
		default:
			/*if (debug)
				printf("Syll already has short vowel\n");*/
			break;
		}
}
