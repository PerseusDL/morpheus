#include <gkstring.h>
#include "is_thirdmono.h"

#include "is_thirdmono.proto.h"

/*
 * do we have a third declension monosyllabic stem in the genitive or dative?
 * (e.g. ai)go/s, ai)gw=n)
 */
/*
is_thirdmono(stemtype,morphflags,stem,endstring,form_info,is_ending)
Stemtype stemtype;
MorphFlags * morphflags;
*/
is_thirdmono(gk_string *stemgstr, gk_string *endgstr, char *stem, char *endstring, word_form form_info, int is_ending)
{
	char * p;
	Stemtype stemtype = stemtype_of(stemgstr);
	char * getsyll();

	if( is_ending && ! *stem) return(0);
/*
 * fail on anything except nouns
 */

	if( ! (stemtype & NOUNSTEM ) ) {
		return(0);
	}

	if(  (stemtype & DECL3 ) && is_mono_stem(stem,endstring) ) {
/*
	     (getsyll(stem,PENULT) == P_ERR) &&
	     (getsyll(endstring,PENULT) == P_ERR) ) {
*/
/*
 * Smyth 252b
 * e)/aros does not contract to h)ro/s, but to h)=ros
 */
		if( Is_contracted( morphflags_of(stemgstr) ) ||
			Is_contracted( morphflags_of(endgstr) )) {
			 return(0);
		}
		
/*
 * fail in the case of words like ge/nui or de/mai
 */
 		if( diphth_end(stem,endstring) && number_of(form_info) != DUAL ) {
 			return(0);
 		}
		if( ! (case_of(form_info) & GENITIVE ) &&
		    ! (case_of(form_info) & DATIVE)) {
				return(0);
		}
/*
		if( ! right_third_stem(stemtype,stem,endstring) ) {
				return(0);
		}
 */
		return(1);
/* grc 7/15/89
 * this info belongs in the dictionary
		if( is_thirdexception(stem,endstring)) {
				return(0);
		} else {
				return(1);
		}
*/
	}
	return(0);
	
}

is_mono_stem(char *stems, char *ends)
{
	return( (nsylls(stems)+nsylls(ends) == 2) );
}

is_thirdexception(char *stem, char *endstring)
{
	char workword[MAXWORDSIZE];
	int i;
	int len;

	Xstrncpy(workword,stem,MAXWORDSIZE); 
	Xstrncat(workword,endstring,MAXWORDSIZE);
	stripquant(workword);

	len = sizeof( thirdexceptions ) / sizeof ( thirdexceptions[0] );
	for(i=0;i<len;i++) {
		if( ! strcmp( workword , thirdexceptions[i] ) )
			return(1);
	}
	return(0);
}


/*
 * does not regard case information and returns only a possibility
 */
poss_thirdmono(Stemtype stemtype, char *stem, char *endstring)
{
	char * p1;
	char * p2;
	if(  (stemtype & DECL3 ) &&
	     ((p1=getsyll(stem,PENULT)) == P_ERR) &&
	     ((p2=getsyll(endstring,PENULT)) == P_ERR) ) {
			return(1);
	}
	return(0);
	
}
/*
 * this gets us out of having "e(w/|" rather than "e(/w|", but
 * there will be other problems here. perhaps we should flag
 * all the simple consonantal stem endings so that we don't
 * have to mess with this
 *
 * grc 8/27/87 -- this should be superfluous now as all contracted endings
 * should now be marked as such
static 
right_third_stem(stype,stem,ending)
Stemtype stype;
char * stem;
char * ending;
{
	switch(stype) {
		case as_ados:
		case eus_ews:
		case hs_eos:
		case is_ews:
		case is_ios:
/*		case os_eos:*
/*		case u_ews:*
		case us_ews:
/*		case ws_w:*
/*		case ws_wos:*
			return(0);
			
		default:
			return(1);
	}
}
*/

diphth_end(char *stem, char *endstring)
{
	char tmp[MAXWORDSIZE];
	char * s;
	
	strcpy(tmp,stem);
	strcat(tmp,endstring);
	
	s = getsyll(tmp,ULTIMA);
	if( s == P_ERR ) return(0);
	if( Is_vowel(*s) && Is_vowel(*(s-1) ) ) {
		*(s-1) = 0;
		if( nsylls(tmp) != 0 )
			return(1);
	}
	return(0);
}
