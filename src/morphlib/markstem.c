/*
 * Gregory Crane
 * June 1987
 */
/*
 * this routine checks to see if the stem has any special
 * characteristics that would determine what endings it could
 * or could not take. 
 *
 * e.g., is it a noun that ends in 'r', 'i' or 'e'? then you want
 * 	'a_' rather than 'h'
 */

#include <gkstring.h>

#include "markstem.proto.h"
 markstem(char *stemstr, gk_string *gstr)
{
	register char * lastp;

	lastp = stemstr;
	while(*lastp) lastp++;
	
	while(lastp>stemstr&&!isalpha(*lastp)) lastp--;

	if( (Is_nounform(gstr) 
	  || Is_adjform(gstr) 
	  || Is_participle(gstr) 
	  || Is_deriv(morphflags_of(gstr))) &&
		(*lastp == 'r' || *lastp == 'i' || *lastp == 'e') ) {
		if( ! (has_morphflag(morphflags_of(gstr),ENDS_IN_DIGAMMA)) )
			add_morphflag(morphflags_of(gstr),R_E_I_ALPHA);
	}

	/*
	 * check to see quantity of last syllable of stem
	 * so that we can generate dunatw/taos rather than dunato/tatos
	 */
	if( Is_adjform(gstr) ) {
		int quant;

		if((quant=getquantity(stemstr,ULTIMA,0,NO,NO)) != I_ERR ) {
			if( quant == LONG || longbyposition(getsyll(stemstr,ULTIMA)) ||
			/* grc 7/24/89 -- a)ndrhi+o/tatos, not a)ndrhi+wtatos*/
				ends_in(stemstr,"hi") )
				add_morphflag(morphflags_of(gstr),LONG_PEN);
			else
				add_morphflag(morphflags_of(gstr),SHORT_PEN);
		}
	}

}
