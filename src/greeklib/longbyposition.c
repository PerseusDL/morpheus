/*
 * grc 2/13/88
 * this is not fully developed -- no real attempt to deal with stops and liquids
 */
#include <greek.h> 

#include "longbyposition.proto.h"
/*
 * return values
 * 		0 if the vowel not long by position
 *		1 if the vowel definitely long by position
 *		2 if the vowel could be long by position
 */
 
longbyposition(char *s)
{
	while(Is_vowel(*s)||(*s && ! isalpha(*s))) s++;

/* 'z', 'c', and 'y' make position */
	if(Is_dblcons(*s)) return(1);
	
	if(! Is_cons(*(s+1))) return(0);
	
	if( Is_labial(*(s+1) && Is_stop(*s))) return(2);

	if( Is_cons(*s) ) return(1);
	return(0);
}