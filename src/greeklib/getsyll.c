/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "getsyll.proto.h"

char *getsyll(char *word, int syll)
/* return pointer to vowel of corresponding syllable */
{
	register char *p;
	register int syllcount;

	if (syll<0 || syll>2)
		return (P_ERR);
	

	syllcount = 0;
	for (p = lastn(word,1);p>=word;p--) {
		if (Is_vowel(*p)) {
		/*
		 * grc 3/3/89:  we had been returning the second vowel of the dipthong.
		 * we wanted to get the accent "graoi=n" for the dual gen of grau=s, 
		 * but kept getting "graoi/n".  it turned out that this routine was
		 * identifying the final syllable not as "oin" but as "in", and the "in"
		 * was naturally inerpreted as short.
		 *
			if (syllcount == syll) {
				if( is_diphth(p,word) ) 
					return(p-1);
				return(p);
			}
		* nuts--it was right the first time
		*/
			if (syllcount == syll) {
				return(p);
			}
		
			if (!is_diphth(p,word)) /* count first vowel only */
				syllcount++;
			}
	}
	return (P_ERR);
}

/*
 * added by grc: 3/3/89
 *
 * this allows you to get "oin", not "in" as the ultima of "anqrwpoin" or "graoin".
 */
char *getsyll2(char *word, int syll)
{
	char * p;
	
	if( nsylls(word) == 0 ) return(word);
	
	p = getsyll(word,syll);
	if( p == P_ERR ) return(p);
	if( is_diphth(p,word) ) 
		return(p-1);
	else
		return(p);
		
}

