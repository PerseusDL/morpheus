/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "stripacc.proto.h"

stripacc(char *word)
{
	register char *p;
	int rval = 0;

	for (p = lastn(word,1);p >= word;p--)
		if (Is_accent(*p)) {
		/*
		 * return the number of the first syllable with an accent on it
		 * (note that for this function, you are not interested in any
		 * subsequent accents caused by enclitics
		 */
			if( ! rval ) {
			/*
			 * add 1 here because the accent follows the syllable on which it falls,
			 * e.g. with pe/mpomen, p would point to "/mpomen" here and the number of 
			 * syllables would be 2, but the accent is on the antepenult (syll number 3)
			 * hence we add the 1
			 */
				rval = nsylls(p) + 1;
			}
			strsqz(p,1);
		}
	return(rval);
}
