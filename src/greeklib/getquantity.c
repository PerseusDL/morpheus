/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "getquantity.proto.h"

int getquantity(char *word, int syll, char *nom, bool is_ending, bool is_oblique)
{
	register char *p;

	p = getsyll(word,syll);
	if (p == P_ERR)
		return (I_ERR);
	p++;
	if (Is_quant(*p)) {
		if ( (*p)==HARDLONG)
			return (LONG);
		else if ( (*p)==HARDSHORT)
			return (SHORT);
		else {		/* the LONGSHORT -- should be for nouns only */
			if (nom == 0) /* ???? */
				return (SHORT);
			else if (getaccent(nom,PENULT)==ACUTE)
				return (LONG);
			else
				return (SHORT);
			}
		}
	else
		return (quantprim(word,syll,is_ending,is_oblique));
}
