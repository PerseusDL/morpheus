/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

#include <greek.h>

#include "addbreath.proto.h"

addbreath(char *w, int c)
{
/*
 * this algorithm gives you breathing "iei(s" for "ieis"
 * grc 2/7/87
 *
	while (Is_vowel(*w))
		w++;
 */

	switch(*w) {
		case 'a':
		case 'e':
		case 'o':
			if( (*(w+2) != DIAERESIS ) && (*(w+1) == 'i' || *(w+1) == 'u')) {
				w +=2;
			} else {
				w++; 
			}
			break;
/*
 * note that you put write "w)i" and "h)i" rather than "wi)" and "hi)"
 */
		case 'w':
		case 'h':
			if( *(w+1) == 'u') {
				w +=2;
			} else {
				w++;
			}
			break;
		default:
			if( Is_vowel(*w) ) 
				w++;
			break;
	}
	
	if (Is_breath(c))
		cinsert(c,w);
}
