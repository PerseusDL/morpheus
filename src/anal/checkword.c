#include <gkstring.h>

#include "checkword.proto.h"

extern quickflag;

long prevmem, curmem;
static int meminit = 0;
long startmem;
checkword(gk_word *Gkword)
{
	int rval = 0;

	/*
	 * if NO_AUGMENT is set, then we are fishing for an epic verb form,
	 * so we don't need to check for indeclinables and nominal forms.
	 */

	if( ! (has_morphflag(morphflags_of(stem_gstr_of(Gkword)) , UNAUGMENTED ) ) )
		rval += checkindecl(Gkword);

	/*
	 * assume (no doubt wrongly) that if a word is in the indeclinable
	 * list, it does not show up anywhere else
	 *
	 * oops: "nw/" can be a form of "e)gw/", but can also be the 
	 *	nom/voc/acc dual of nou=s.
	 * 
	 * 
	 */
	if( rval && quickflag ) {
		return(rval);
	}
	if( ! (has_morphflag(morphflags_of(stem_gstr_of(Gkword)) , UNAUGMENTED) ) )
		rval += checknom(Gkword);		


	if( rval && quickflag ) {
		return(rval);
	}
/*
 * grc 3/25/91
 *
 * this is probably a mistake, but for now we will just head home if we see
 * that the original word was capitalized.  only proper nouns should be capitalized
 * so avoid bizarre verbal analyses -- a.g., *)apo/llwn as from a)po-la/w !
 */
/*
 * grc 6/1/92
 *
 * put this back so that i could see how many upper case words we actually could analyze
 * in the tlg.
 *
 	if( rawword_of(Gkword)[0] != BETA_UCASE_MARKER ) {
 */
 		rval += checkverb(Gkword);
 /*
	}
  */

	return(rval);
}
