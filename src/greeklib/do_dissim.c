/*
 * gregory crane
 * harvard university
 *
 * 4/17/89
 */
 
#include <gkstring.h>

#include "do_dissim.proto.h"

do_dissim(char *s, Stemtype stype)
{
	register char *p1, *p2, *cp;
	
	/*
	 * added -- grc 5/10/89: a)riqmh/qhn not a)ritmh/qhn
	 */

	if( Is_asp(*(lastn(s,1))) && ((stype & VERBSTEM ) == PP_AP) ) {
		return(0);
	}
	/* end 5/10/89 addition */
	
	p1 = s;
	while(*p1) {
/*
		cp = next_cons(p1);
		if( Is_asp(*p1) && Is_asp(*cp)) {
*/
		if( Is_asp(*p1) && next_cons_rough(p1) ) {
		/*
		 * allow for forms such as "e)qre/fqhn" and "e)qa/fqhn"
		 *
			if(*cp == 'f' && *(cp+1) == 'q' ) return(0);
		 * 
		 * deleted -- grc 5/10/89
		 */
			switch(*p1) {
				case 'q':
					*p1 = 't';
					break;
				case 'x':
					*p1 = 'k';
					break;
				case 'f':
					*p1 = 'p';
					break;
				}
/*
			printf("asp at [%s] of [%s]\n", p1 , s);
*/
			return(1);
		}
		p1++;
	}
	return(0);
}

next_cons_rough(char *s)
{
	char * cp, *next_cons();
	int rval = 0;
	
	cp = next_cons(s);
	rval = Is_asp(*cp);
	if( ! rval ) {
		if( *cp == 's' && Is_asp(*(cp+1) ) )
			rval = 1;
	}
	return( rval );
	
}

char *
next_cons(char *s)
{
	while(Is_cons(*s)||Is_accent(*s)) s++;
	while(Is_vowel(*s)||Is_accent(*s)) s++;
	return(s);
}