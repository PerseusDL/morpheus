/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "quantprim.proto.h"

int quantprim(char *word, int syll, bool is_ending, bool is_oblique)
 /* primitive function -- just greek, no quantifiers */
{
	register char *p;
	register char *s;

	p = getsyll(word,syll);
	if (p == P_ERR)
		return (I_ERR);
	
	s = p;

	while(!Is_cons(*s) && *s) {
		if( *s == HARDLONG )
			return(LONG);
		else if( *s == HARDSHORT )
			return(SHORT);
		s++;
	}

	if( long_by_isub(p) ) {
		return(LONG);
	}
	
	if (is_diphth(p,word))  {
		if ((*p == 'i') && (*(p-1)=='a' || *(p-1)=='o')) {
			if( is_ending == YES && is_oblique == NO &&
		   		(*(p+1)==0 || (Is_accent(*(p+1))&& *(p+2)==0))) /* final -ai or -oi */ {
					return (SHORT);
			} else 
					return(LONG);
		 } else
			return (LONG);
	
	} else if (Is_lvwl(*p)) /*should add: long before double consonants? */
		return (LONG);
	else if (Is_shvwl(*p)) {
		if (*(p+1)==SUBSCR)
			return (LONG);
		else
			return (SHORT);
		}
	else 
		return (I_ERR);
}

long_by_isub(char *s)
{
	if(*(s+1) == '|' || (Is_breath(*(s+1)) && *(s+2) == '|') ) return(1);
	return(0);
}