/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "isdiphth.proto.h"

bool is_diphth(char *p, char *word)
/* is *p the second, i.e., significant, vowel in a diphthong? */
/* acceptable diphthongs taken from Smyth 5. Subscripts are NOT diphthongs
	for this purpose */
{
	int c1, c2;

	if (p - 1 < word)
		return(NO);
	if( Is_diaeresis(*(p+1)) )
		return(NO);

	c2 = *p; 
	if( isupper(c2) ) c2 = tolower(c2);
	if (c2 != 'i' && c2 != 'u')
		return (NO);

	c1 = *(p-1);
	if( isupper(c1) ) c1 = tolower(c1);

	if (!Is_vowel(c1))
		return (NO);

/* so c1 is a vowel */
	if ((c1 == 'a')||(c1 == 'e')||(c1 == 'o'))
		return (YES);
	if (c2 == 'i')
		return (c1 == 'u');
	if (c2 == 'u')
		return (c1 == 'h');
	return (NO);
}

starts_w_diphth(char *stem)
{
	return(is_diphth(stem+1,stem));
}