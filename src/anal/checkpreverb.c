#include <gkstring.h>

#include "checkpreverb.proto.h"
/*
 * check to see if a compound  of this type exists
 */
 
/*
 * more trouble than it is worth--no longer called as of 6/7/88, grc
 */
Check_preverb(gk_word *Gkword, gk_string *gstr)
{
	char savelemma[MAXWORDSIZE];
	int rval = 0;
	int sawstems = 0;
	int voice;
	
	voice = voice_of(forminfo_of(gstr));
return(1);
/*
	if( ! Should_check_preverb(Gkword) )
		return(1);

	if(lemma_exists(lemma_of(Gkword))) {
		return(1);
	}
		
	if( preverb_of(Gkword)[0] ) {
		Xstrncpy(savelemma,lemma_of(Gkword),(int)sizeof savelemma);
		build_lemma(lemma_of(Gkword),preverb_of(Gkword));

		if(lemma_exists(lemma_of(Gkword))) {
			Xstrncpy(lemma_of(Gkword),savelemma,(int)sizeof lemma_of(Gkword));
			return(1);
		}
	}

	if(preverb_of(Gkword)[0] && has_act_lemma(Gkword) && voice != ACTIVE ) {
		Xstrncpy(lemma_of(Gkword),savelemma,(int)sizeof lemma_of(Gkword));
		set_pass_lemma(Gkword);
		build_lemma(lemma_of(Gkword),preverb_of(Gkword));
		if(lemma_exists(lemma_of(Gkword))) {
			Xstrncpy(lemma_of(Gkword),savelemma,(int)sizeof lemma_of(Gkword));
			set_pass_lemma(Gkword);
			return(1);
		}
	} 
	
	return(0);
*/
}
