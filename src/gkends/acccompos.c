#include <string.h>

#include <gkstring.h> 

#include "acccompos.proto.h"
char * skip_to_syll();

AccComposForm(gk_string *gstr)
{
	gk_word * gkform;
	char * p = gkstring_of(gstr);
	char *s;
	char word[MAXWORDSIZE];
	char prefword[MAXWORDSIZE];
	char saveword[MAXWORDSIZE];
	int had_stem_acc = 0;
	int had_suff_acc = 0;
	gkform = (gk_word *) CreatGkword(1);
	word[0] = prefword[0] = saveword[0] = 0;

/*
 * grc 6/16/89
 *
 * the ath_primary infinitive ending -men has the key stem_acc, but we
 * want to put the accent on the stem: e.g. a)rh/men, not a)rhme/n
 *
	if( has_morphflag(morphflags_of(gstr),STEM_ACC) && 
		! has_morphflag(morphflags_of(gstr),INDECLFORM) ) {
			return;
	}
 * grc 7/28/89
 * this should be unnecessary and leaving it in causes us to fail with
 * @wn_ousa_on w_stem pres part act stem_acc
 */

	if( has_morphflag(morphflags_of(gstr),ENCLITIC) ) goto finish;
	
/*
printf("start with p [%s]\n", p );
*/
	s = strchr(p,'!');
	/*
	 *grc 7/12/89
	 *
	 * if there is an '!' in the word, then the accent cannot precede that 
	 * point and everything else should, for the purposes of accentuation, be
	 * ignored.  save what precedes as  aprefix, then add it later.
	 */

	if( s ) {
		
		strcpy(prefword,p);
		p = s+1;
		set_gkstring(gstr,"");
		add_morphflag(morphflags_of(gstr),NEEDS_ACCENT);
		zap_morphflag(morphflags_of(gstr),ACCENT_OPTIONAL);
		set_workword(gkform,"");
		s = strchr(prefword,'!');
		*(s+1) = 0;
	} else {
		strcpy(saveword,p);
		set_gkstring(gstr,"");
		p = saveword;
	}
	
	*ends_gstr_of(gkform) = * gstr;
	set_morphflags((gk_string *)gkform,morphflags_of(gstr));

/*
 * if the ending is accented or if it is more than one syllable long,
 * then this flag is unnecessary.
 */
	if( hasaccent(gkstring_of(gstr)) || nsylls(gkstring_of(gstr)) > 1 ) {
		zap_morphflag(morphflags_of(gstr),STEM_ACC);
		goto finish;
	}

	if( has_morphflag(morphflags_of(gstr),STEM_ACC)   && 
		! has_morphflag(morphflags_of(gstr),INDECLFORM)) {
		had_stem_acc = 1;
		zap_morphflag(morphflags_of(gstr),STEM_ACC);
	}

	if( has_morphflag(morphflags_of(gstr),SUFF_ACC) && 
		! has_morphflag(morphflags_of(gstr),INDECLFORM) ) {
		had_suff_acc = 1;
		zap_morphflag(morphflags_of(gstr),SUFF_ACC);
	}

	if( Is_adjform(gstr) || Is_nounform(gstr) || Is_participle(gstr) || (stemtype_of(gstr)|INDECL) ||  has_morphflag(morphflags_of(gstr),INDECLFORM) ) {

		FixPersAcc(gstr,morphflags_of(gstr),gstr,p,word,forminfo_of(gstr), 
		has_morphflag(morphflags_of(gstr),INDECLFORM) ? 0 : 1 );
		if(word[0] ) {
			if( prefword[0] ) {
				strcat(prefword,word);
				strcpy(word,prefword);
			}
			strcpy(gkstring_of(gstr),word);
		}


	} else if( Is_verbform(gstr) || had_suff_acc ) {
		FixRecAcc(gkform,morphflags_of(gstr),p);
		if( prefword[0] ) {
			strcat(prefword,p);
			strcpy(p,prefword);
		}
	}  

finish:
	if( had_suff_acc ) 
		add_morphflag(morphflags_of(gstr),SUFF_ACC);
	if( had_stem_acc ) 
		add_morphflag(morphflags_of(gstr),STEM_ACC);
	zap_morphflag(morphflags_of(gstr),ACCENT_OPTIONAL);
	/*
	 * once you have put the ending on the accent, you should
	 * get rid of this flag, as this flag would only be confusing
	 * at a later stage of the process
	 */
	zap_morphflag(morphflags_of(gstr),NEEDS_ACCENT);

	if( (hasaccent(gkstring_of(gstr))  || nsylls(gkstring_of(gstr)) > 1)
		&& has_morphflag(morphflags_of(gstr),STEM_ACC)) {
		zap_morphflag(morphflags_of(gstr),STEM_ACC);
	}

	FreeGkword(gkform);
	
}

char *
skip_to_syll(char *s, int nsyll)
{
	if( nsylls(s) > 3 || nsylls(s) == 1) {
		return(s);
	} else if( nsylls(s) == 3 ) {
		return(getsyll2(s,PENULT));
	}
	else if( nsylls(s) == 2 ) {
		return(getsyll2(s,ULTIMA));
	} else
		return(s);
	
}
