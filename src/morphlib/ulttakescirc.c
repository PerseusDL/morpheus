#include <gkstring.h>

#include "ulttakescirc.proto.h"

ulttakescirc(gk_string *gstring, word_form form_info)
{
	Stemtype stemtype;

	stemtype = stemtype_of(gstring);

	if( has_morphflag(morphflags_of(gstring),NO_CIRCUMFLEX) )
		return(0);
		
	if( Is_contracted(morphflags_of(gstring)) /* || 
		has_morphflag(morphflags_of(gstring),LOST_ACC) */) {
		return(1);
	}
	
	if( Is_enclitic(morphflags_of(gstring)) ) return(0);
	
	if( case_of(form_info)  & ACCUSATIVE ) {
		return(0);
	}
	if( case_of(form_info) &  NOMINATIVE) {
		return(0);
	}

	return(1);
}
