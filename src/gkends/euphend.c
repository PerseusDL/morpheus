#include <gkstring.h>

#include "euphend.proto.h"

 EuphEnd(gk_string *want, gk_string *have, int strict)
{
	Dialect d;
	char * curs = gkstring_of(have);

	if( strict && has_morphflag(morphflags_of(want),ITERATIVE) && 
		! has_morphflag(morphflags_of(have),ITERATIVE)  ) {
			return(0);
	}
			
	if( has_morphflag(morphflags_of(want),UNCONTR_END) && 
		has_morphflag(morphflags_of(have),CONTRACTED)  )
			return(0);
			
	if( Has_numovable(morphflags_of(want)) && ! Has_numovable(morphflags_of(have)) ) {
	  	if ( ! Is_deriv(morphflags_of(want)))  
			return(0);
	}

	if( *curs == 'h' && ! (has_morphflag(morphflags_of(want),ENDS_IN_DIGAMMA)) &&
	  ((stemtype_of(have) & (DECL1|DECL2)) || mood_of(forminfo_of(have)) == PARTICIPLE || 
	  	Is_deriv(morphflags_of(want))) ) {
		/*
		 * if the stem ended in 'r', 'i' or 'e', ...
		 */

		if( Is_rho_eta_form(morphflags_of(want)) ) {
			Dialect dial1;
/*
printf("dial %lo anded %lo have %lo\n", dialect_of(want), AndDialect(dialect_of(want) , (Dialect) RHO_ALPHA_DIAL),
dialect_of(have) );
*/
			if( (d=AndDialect(dialect_of(want) , (Dialect) RHO_ETA_DIAL)) < 0 )  {
				if(! Is_verbform(want) || Is_deriv(morphflags_of(want)) ) {
			/*
			 * avoid clash or 'r', 'i', 'e' with 'h' if Attic
			 * nominal form.
			 */
					return(0);
				} else {
					return(1);
				}

			}
			/*
			 * note that this ending can only appear after
			 * 'r', 'e' or 'i' in certain dialects
			 */
			set_dialect(have,RHO_ETA_DIAL);
			zap_morphflag(morphflags_of(want),R_E_I_ALPHA);
		}
	} else if( *curs == 'a' && *(curs+1) == HARDLONG ) {
		/*
		 * if you have a  long 'a' and this 'a' is flagged
		 * to be attached only to stems ending in 'r', 'i',
		 * or 'e', check to see if the stem really does end
		 * in 'r', 'i' or 'e'.
		 *
		 * if not, fail
		 */

		if( Is_rho_eta_form(morphflags_of(have)) ) {
			if( ! Is_rho_eta_form(morphflags_of(want) ) ) 
				return(0);
				
			if( (has_morphflag(morphflags_of(want),ENDS_IN_DIGAMMA)) ||
				!Is_rho_eta_form(morphflags_of(want)) ) {

				return(0);
			}
		} 
	}


	if( Is_comparative(forminfo_of(want)) && ! Is_comparative(forminfo_of(have)) ) {
		if( strict ) 
			return(0);
	}
	
	if( Is_superlative(forminfo_of(want)) && ! Is_superlative(forminfo_of(have)) ) {
		if( strict )
			return(0);
	}
/*
 * This is commented out for now: until we have carefully marked
 * long and short vowels in our dictionary, this will be unreliable.
 *
 * e.g. we would assume i)/sxuros had a short 'u' rather than a long
 * 'u' and would thus allow forms such as "i)sxurw/teros" rather than
 * "i)sxuro/teros"
 *
 * reinserted for Hansen and Quinn vocab: GRC 9/9/87
 */
/*	  ((morphflags_of(have)&LONG_PEN) && 
	    ((morphflags_of(want)&LONG_PEN) != (morphflags_of(have)&LONG_PEN)) ||
		((morphflags_of(have)&SHORT_PEN)) &&
		((morphflags_of(want)&SHORT_PEN) != (morphflags_of(have)&SHORT_PEN))) ) {
*/
	if(
	  (has_long_pen(morphflags_of(have)) && 
	    has_long_pen(morphflags_of(want)) != has_long_pen(morphflags_of(have))) ||
		(has_short_pen(morphflags_of(have)) &&
		has_short_pen(morphflags_of(want)) != has_short_pen(morphflags_of(have))) ) {

			return(0);
	}

	return(1);
}
