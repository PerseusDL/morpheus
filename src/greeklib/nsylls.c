/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "nsylls.proto.h"

nsylls(char *word)
{
	register char *p;
	register int syllcount;

	syllcount = 0;
	for (p = lastn(word,1);p>=word;p--)
		if (Is_vowel(*p)) {
			if (!is_diphth(p,word)) /* count first vowel only */
				syllcount++;
			}
	return (syllcount);
}
