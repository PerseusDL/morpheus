/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "stripbreath.proto.h"

stripbreath(char *word)
{
	register char *p;
	for (p=lastn(word,1);p>=word;p--)
		if (Is_breath(*p))
			strsqz(p,1);
}
