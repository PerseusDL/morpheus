#include <gkstring.h>

#include "penultform.proto.h"

penult_form(gk_string *gstring, word_form form_info)
{
	Stemtype stemtype;

	stemtype = stemtype_of(gstring);

	if( case_of(form_info) == VOCATIVE && 
		number_of(form_info) == SINGULAR &&
		(stemtype & DECL3) &&
		Is_pers_name(morphflags_of(gstring)) ) {
			return(0);
	}

	if( Is_penult_accent(morphflags_of(gstring)) ) {
		return(1);
	}

	/* special case: certain infinitives with acc on penult, not antep. */
	if ( (voice_of(form_info) == ACTIVE && 
			mood_of(form_info) == PARTICIPLE &&
			gender_of(form_info) == NEUTER &&
			number_of(form_info) == SINGULAR &&
			(case_of(form_info) == NOMINATIVE || case_of(form_info)==ACCUSATIVE))
			/* neuter active participles */
	    
	    /*|| (stemtype == AOR1_REG && 
			voice_of(form_info) == ACTIVE && 
			mood_of(form_info) == INFINITIVE) 
		       	/* 1st aorist active inf *
	    || (stemtype == AOR2_REG && 
			voice_of(form_info) == MIDDLE && 
			mood_of(form_info) == INFINITIVE) 
		       	/* 2nd aorist middle inf */
		       	
	    || (voice_of(form_info) & MEDIO_PASS && 
			mood_of(form_info) == INFINITIVE && 
			tense_of(form_info) == PERFECT ) )
			/* perfect m/p inf */ 
				return(1);
	return(0);
}
