/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

/*
 * grc 2/20/88
 *
 * this does not work on pure beta -- e.g. putting an acute accent on "*)aqw"
 * was producing "*)a/qw" instead of "*)/aqw".
 */

#include <greek.h>


addaccent(char *word, int accent, char *p)
{
	register char * t = p-1;

	if(*word == '*' && Is_breath(*(word+1)) ) {
		if( p == (word+2)) {
			cinsert(accent,word+2);
			return;
		}
		if( p == (word+3) && is_diphth(p,word) == YES) {
			cinsert(accent,word+2);
			return;
		}
	} 

	do p++;
		while (Is_breath(*p) || Is_quant(*p) );
/*
 * grc 5/2/89
 *
 * if i ask for the perfect participle ending "ui=a" i come up with nothing: that is
 * because the ending is being stored as "ui_=a".  here we zap the extraneous long mark.
 *
 */
	if( accent == CIRCUMFLEX && *(p-1) == HARDLONG) {
		strsqz(p-1,1);
		p--;
	}
	cinsert (accent,p);
}
