#include <greek.h>

/*
 * greg crane
 *
 * february 1987
 */

#define Is_junk(X) (X == ',' || X == '.' || X == ':' || X == ';' || X == '"' || X == '<' || \
	X == '>' || X == '[' || X == ']' || X == '^' || X ==  '-')

#include "standword.proto.h"
	/*
	 * grc 7/6/89
	 *
	 * changed this so that it would only remove the * if it appears in the middle of a 
	 * word
	 */
	  /* || \
	/* grc 6/28/89 -- '*' is long mark in smk  X == '*' )*/
/*
 * 1) strip any white space or garbage at the start of a word
 * 2) standardize some printing conventions: e.g. $ai(/dhn& is converted to $*(/aidhn&.
 * 3) remove any non-characters that may appear in the word: 
 *    e.g., delete '[', ']', '<', '>' etc.
 */
 
standword(char *word)
{
	register char * a;
	register char * b;
	char tmp[MAXWORDSIZE];

/*
 * ignore diaeresis as editors are simply too inconsistent
 * in deciding when and when not to include them 
 */
	stripdiaer(word);
	zap_rr_breath(word);

	a = word; b = tmp;

	while(Is_junk(*a) && *a) a++;

/* deleted 2/14/88 to match up with the standard beta of middle liddel 
	if( *a == '*' ) 
		normucase(a);
*/

/*
 *  *ai(/dhn --> *(/aidhn
 *
 * disabled 8/17/93 grc -- why did we put this in in the first place? it is
 * bad beta code!
 *
	if( *a == '*' && Is_vowel(*(a+1)) && ! Is_breath(*(a+2) ) ) {
		if( is_diphth(a+2,a) && Is_breath(*(a+3)) && Is_accent(*(a+4))) {
			int c;
			
			c = *(a+3);
			*(a+3) = *(a+1);
			*(a+1) = c;
			
			c = *(a+4);
			*(a+4) = *(a+2);
			*(a+2) = c;
		}
	}
 */

	while(*a) {
/*
 * this strips extra accents (e.g. second accents caused by 
 * enclitics
 */
		if( Is_accent(*a) )
			stripacc(a+1);

		if( *a == GRAVE )
			*a = ACUTE;
		if( *a == '*' && a > word ) {
			a++;
			continue;
		}
		if( ! Is_junk(*a) )
			*b++ = *a++;
		else 
			a++;
	}
	*b = 0;
	strcpy(word,tmp);
}

zap2acc(s)
char *s;
{
	int haveacc = 0;
	
	while(*s) {
		if(*s == ACUTE || *s == GRAVE || *s == CIRCUMFLEX ) {
			if( haveacc ) {
				strcpy(s,s+1);
				continue;
			}
			haveacc = 1;				
		}
		s++;
	}
}

striphyph(char *s)
{
	while(*s) {
		if(*s=='-' ) {
			strcpy(s,s+1);
			if( !*s ) break;
		}
		s++;
	}
}
