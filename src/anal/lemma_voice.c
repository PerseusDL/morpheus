#include <gkstring.h>

#include "lemma_voice.proto.h"

has_act_lemma(gk_word *Gkword)
{
	char * lp = lemma_of(Gkword);
		
	if( *(lp+Xstrlen(lp)-1) == 'w' )
		return(1);
	return(0);
}


set_pass_lemma(gk_word *Gkword)
{
	char * lp = lemma_of(Gkword);
	
	if( has_act_lemma(Gkword)) {	
		*(lp+Xstrlen(lp)-1) = 0;
		Xstrncat(lp,"omai",(int)sizeof lemma_of(Gkword));
	}
}

/*
build_lemma(lemma,preverb)
char * lemma;
char * preverb;
{
	if( * preverb ) {
			int startsyll, startaccent;
			int ressyll, resaccent;
			/*
			 *if you adding the preverb changes the accent, notice this.
			 * this allows us to flag forms such as para/+ei)=si (--> pa/reisi)
			 * so that we see that they are different from forms such as
			 * para/+ei)si/ (which also goes to pa/reisi). by marking accent
			 * changes, we know when also to print the simple roots (e.g. ei)=mi, vs. ei)mi/)
			 * as well as the compounded verbs (e.g. pa/reimi for both cases)
			 *
			
			checkaccent(lemma,&startsyll,&startaccent);
			rstprevb(lemma,preverb);
			stripacc(lemma);
			putsimpleacc(lemma,(PrntFlags)0);
			checkaccent(lemma,&ressyll,&resaccent);
			return( ressyll != startsyll || resaccent != startaccent );
	}
	return(0);
}
*/
