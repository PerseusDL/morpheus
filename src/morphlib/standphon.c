#include <gkstring.h>

#include "standphon.proto.h"

/*
 * this module looks for fairly simple graphic variations.
 * It is more complex than standword() insofar as this deals with some changes that
 * are associated with particular dialects.
 *
 * Changes made in this routine are recorded.  Thus, if you see "a(rpa/sdw", the -sd- 
 * is changed to a 'z' here, but the form "a(rpa/sdw" is still stored in
 * rawword_of(Gkword). The changes that were made in standword() are of sufficiently 
 * trivial nature so that they are forgotten.
 *
 * e.g., if it sees a rough breathing between two vowels, it assumes that an intervocalic
 * sigma has been replaced by the 'h'. It replaces the 's' and marks this word as 
 * "Laconian".
 */
stand_phonetics(gk_word *Gkword)
{
	register char * s = workword_of(Gkword);
	int lastc = 0;
	
	while(*s) {
		
		if( *s == h_AS_ROUGH  ) {
			if( Is_vowel(lastc) && Is_vowel(*(s+1))) {
				*s = 's';
				add_morphflag(morphflags_of(Gkword),INTERV_S_TO_H);
				add_geogregion(Gkword,LACONIA);
			}
			else {
				strcpy(s,s+1);
				addbreath(s,ROUGHBR);
			}
			s++;
			continue;
		}
		
		if( *s == H_AS_ROUGH ) {
				strcpy(s,s+1);
				addbreath(s,ROUGHBR);
				if( islower(*s) ) *s = toupper(*s);
				continue;
		}
		
		/*
		 * grc 6/29/89
		 * this causes ei)s-de/xomai, ei)s-de/rkomai etc. to fail
		 *
		if( *s == 's' && *(s+1) == 'd' ) { /* "sd" --> "z" *
			*s = 'z';
			s++;
			strcpy(s,s+1);
		}
		*/
		/*
		 * grc 6/29/89
		 * this causes e)k-ste/llw, e)kste/fw etc. to fail
		 *
		if( *s == 'k' && *(s+1) == 's' ) { /* "ks" --> "c" *
			*s = 'c';
			s++;
			strcpy(s,s+1);
		}
		*/
		if( isalpha(*s) ) lastc = *s;
		s++;
	}
	
}