#include <gkstring.h>

#include "fixacc.proto.h"
static fixnacc2(char *, gk_string *, word_form, int, bool);


putsimpleacc(char *s)
{
	gk_word * gkword;
	MorphFlags * mflags;
	char tmpw[MAXWORDSIZE];
	
	if( cur_lang() == LATIN || cur_lang() == ITALIAN ) return;

	gkword = (gk_word *) CreatGkword(1);

	if( ! gkword ) {
		fprintf(stderr,"no memory for gstring in putsimpleacc\n");
		return;
	}
	mflags = (MorphFlags *)calloc(1,sizeof * mflags);
	
	set_workword(gkword,s);
	FixRecAcc(gkword,mflags,workword_of(gkword));
	Xstrncpy(s,workword_of(gkword),MAXWORDSIZE);
	FreeGkword(gkword);
}

FixRecAcc(gk_word *gkform, MorphFlags *mflags, char *word)
  /* add recessive accent */
{
	register char *p;
	word_form form_info;


	if( cur_lang() == LATIN || cur_lang() == ITALIAN ) return;
	form_info = forminfo_of(gkform);

	/* if accent's already there, forget it */
	for (p=word;*p;p++)
		if (Is_accent(*p))
			return;

	if (getsyll(word,ULTIMA,0) == P_ERR)
		return;		/* avoid core dumps */

/*
 * see if this word must be accented on the final syllable of the stem 
 * (which is actually not always the penult: e.g. stratiw/ths, stratiw/taisi)
 */

	
	if (getquantity(word,ULTIMA,NULL_P, YES,NO) == LONG) {
		p = getsyll(word,PENULT,0);

		if (p == P_ERR ) {
			p = getsyll(word,ULTIMA,0);

			if( Accent_optional(mflags) )
				return;
			if( ulttakescirc(ends_gstr_of(gkform),forminfo_of(ends_gstr_of(gkform))) ) {
				addaccent(word,CIRCUMFLEX,p);
			} else {
				addaccent(word,ACUTE,p);
			}
		} else {
			addaccent(word,ACUTE,p);
		}
	} else {		/* short ultima */
		p = getsyll(word,ANTEPENULT,0);
		if (p != P_ERR && ! penult_form(ends_gstr_of(gkform),form_info))
			addaccent(word,ACUTE,p);
		else {		/* no antepenult */
			if( Accent_optional(mflags) )
				return;
			p = getsyll(word,PENULT,0);
			if (p == P_ERR)
				p = getsyll(word,ULTIMA,0);

			/*
			 * note that proclitics are indeclinable, so we don't deal with accenting them
			 * (for now anyway)
			 */
			if (getquantity(word,PENULT,NULL_P,YES,NO) == LONG && ! Is_enclitic(mflags) ) {
				addaccent(word,CIRCUMFLEX,p);
			} else { 	/* short penult or none at all */
				addaccent(word,ACUTE,p);
			}
		}
	}
}

/*
 * grc 2/9/95
 *
 * this wrapper is to clean up forms like "me/li*", where we have a null
 * ending represented by a '*'.
 *
 * Yes, this is a kludge, but reasonable way to catch this, I think.
 */
FixPersAcc(gk_string *gstring, MorphFlags *mflags, gk_string *stemgstr, char *endstring, char *word, word_form form_info, int is_ending)
{
  FixPersAcc2(gstring, mflags, stemgstr, endstring, word, form_info, is_ending);

  if(*(word+strlen(word)-1) == '*' ) *(word+strlen(word)-1) = 0;
}

FixPersAcc2(gk_string *gstring, MorphFlags *mflags, gk_string *stemgstr, char *endstring, char *word, word_form form_info, int is_ending)
{
	register char *p;
	char tmp[MAXWORDSIZE];
	char workstem[MAXWORDSIZE];
	char * stem = gkstring_of(stemgstr);
	bool is_oblique;

	*word = 0;

	if( cur_lang() == LATIN || cur_lang() == ITALIAN ) {
		Xstrncpy(word,stem,MAXWORDSIZE);
		Xstrncat(word,endstring,MAXWORDSIZE);
		return;
	}

/*
 * e.g., if you have something like "g'" (for "ge/")
 */
	if( ! nsylls(stem)  && ! nsylls(endstring) ) {
		Xstrncpy(word,stem,MAXWORDSIZE);
		Xstrncat(word,endstring,MAXWORDSIZE);
		return;
	}

	if( has_morphflag(mflags,PROCLITIC) ) {
		Xstrncpy(word,stem,MAXWORDSIZE);
		return;
	}
	if( case_of(form_info) == GENITIVE || case_of(form_info) == DATIVE ) 
		is_oblique = YES;
	else 
		is_oblique = NO;

	Xstrncpy(workstem,stem,MAXWORDSIZE);
	/* if accent's already there, forget it */
	for (p=endstring;*p;p++)
		if (Is_accent(*p)) {
			Xstrncpy(word,stem,MAXWORDSIZE);
			Xstrncat(word,endstring,MAXWORDSIZE);
			return;
	}


	for (p=stem;*p;p++)
		if (Is_accent(*p)) {
			Xstrncpy(word,stem,MAXWORDSIZE);
			Xstrncat(word,endstring,MAXWORDSIZE);
			return;
	}
/*
 * grc 7/15/89
 *
 * we were generating endings such as -podwn and accepting forms like
 * tri/podwn rather than tri-po/dwn
 */
 	if( Accent_optional(mflags) && has_morphflag(mflags,ENCLITIC) ) {
			Xstrncpy(word,stem,MAXWORDSIZE);
			Xstrncat(word,endstring,MAXWORDSIZE);
			return;
	}
	
 
/*
 * accent the ultima really means accent the first syllable of
 * the ending (unless of course the ending already has an
 * accent
 */
 /*
  * grc 7/5/89
  *
  * no! in the case of kt-enos where the ending is -enos, you want to 
  * generate kteno/s, not kte/nos.
  */
	if( is_thirdmono(stemgstr,gstring, stem,endstring,form_info,is_ending) && nsylls(endstring) == 2 ) {
			char * ep;
			
		 	if( Accent_optional(mflags) ) {
					Xstrncpy(word,stem,MAXWORDSIZE);
					Xstrncat(word,endstring,MAXWORDSIZE);
					return;
			}
			ep = getsyll(endstring,ULTIMA,0);
			if( is_diphth(ep,endstring)) {
				ep--;
			}
			fixnacc2(ep,gstring,form_info,is_ending,is_oblique);
			Xstrncpy(tmp,workstem,MAXWORDSIZE);
			Xstrncat(tmp,endstring,MAXWORDSIZE);
/*			stripmetachars(tmp);*/
			Xstrncpy(word,tmp,MAXWORDSIZE);
			return;
	} else if( has_morphflag(morphflags_of(stemgstr),SUFF_ACC) || 
	   is_thirdmono(stemgstr,gstring, stem,endstring,form_info,is_ending) ||
	   nsylls(stem) == 0 ) {
/*
 * note that the last case, where you have 0 syllables in the stem, crops up
 * if you segment Trw/s as Tr-ws and get a stem "Tr" with endings "ws" wos"
 */
/*
	 	if( Accent_optional(mflags) ) {
				Xstrncpy(word,stem,MAXWORDSIZE);
				Xstrncat(word,endstring,MAXWORDSIZE);
				return;
		}
*/
		if( nsylls(endstring) >= 1 ) {
			if( ! naccents(endstring) ) 
				fixnacc2(endstring,gstring,form_info,is_ending,is_oblique);
			Xstrncpy(tmp,workstem,MAXWORDSIZE);
			Xstrncat(tmp,endstring,MAXWORDSIZE);
/*			stripmetachars(tmp);*/
			Xstrncpy(word,tmp,MAXWORDSIZE);
			return;
		} else if(nsylls(endstring) == 0 ) {
			char * p;
			
			
			Xstrncpy(tmp,stem,MAXWORDSIZE);
			Xstrncat(tmp,endstring,MAXWORDSIZE);
			
			p = getsyll2(tmp,ULTIMA,0);

			if( p != P_ERR ) {
				fixnacc2(p,gstring,form_info,is_ending,is_oblique);			
				Xstrncpy(word,tmp,MAXWORDSIZE);
			}
			return;
		}
	}

/*
 * "a penult accent" really means that accent cannot recede past the final
 * syllable of the stem.
 *
 * see if this word must be accented on the final syllable of the stem 
 * (which is actually not always the penult: e.g. stratiw/ths, stratiw/taisi)
 */
	else if( penult_form(stemgstr,form_info)  || 
		has_morphflag(morphflags_of(gstring),STEM_ACC) || nsylls(stem) == 1  )  {
		
		p = getsyll(workstem,ULTIMA,0);
		if( nsylls(endstring) == 1 && 
/*
 * "poli-t + ai" becomes "poli=tai"
 */
			(quantprim(workstem,ULTIMA,NO,is_oblique)==LONG) &&
			(quantprim(endstring,ULTIMA,YES,is_oblique)==SHORT) && ! Is_enclitic(mflags) ) {
			 	if( Accent_optional(mflags) ) {
						Xstrncpy(word,stem,MAXWORDSIZE);
						Xstrncat(word,endstring,MAXWORDSIZE);
						return;
				}
				addaccent(workstem,CIRCUMFLEX,p);
		} else if((quantprim(endstring,ULTIMA,YES,is_oblique)==LONG) ||
			(nsylls(endstring) == 2 )) {
/*
 * loxmwd + h becomes loxmw/dh
 */
				addaccent(workstem,ACUTE,p);
		} else if((quantprim(workstem,ULTIMA,NO,is_oblique)==LONG) &&
			(has_morphflag(morphflags_of(stemgstr),CONTRACTED)) ) {
/*
 * "pu- + r" --> "pu=r", "fw + s" --> "fw=s"
 * where "pu=r" represents a pseudo-contraction and "fw=s" represents "fa/os"
 */
				addaccent(workstem,CIRCUMFLEX,p);
		} else {
			addaccent(workstem,ACUTE,p);
		}
		Xstrncpy(tmp,workstem,MAXWORDSIZE);
		Xstrncat(tmp,endstring,MAXWORDSIZE);
		Xstrncpy(word,tmp,MAXWORDSIZE);
		return;
	} 
/*
 * this final, odd case is for words such as "diw=ruc, diw/ruxos", where we
 * create a stem "diwru". if we call this a "penult accent" then we end up
 * sticking the accent on the 'u' rather than on the 'w'.
 *
 * see also ai)go/-nuc (from middle liddel -- 2/6/88 
 * :no:ai)gonu c_xos ant_acc masc fem
 */
	else if( antepen_form(stemgstr,form_info) ) {
		p = getsyll(workstem,PENULT,0);

		if( nsylls(endstring) == 0 && 
			(getquantity(workstem,PENULT,NULL_P,NO,is_oblique)==LONG) &&
			(getquantity(workstem,ULTIMA,NULL_P,NO,is_oblique)==SHORT) && ! Is_enclitic(mflags) )
/* 
 * diwru + c --> diw=ruc
 */
				addaccent(workstem,CIRCUMFLEX,p);
		else if( nsylls(endstring) > 1 || 
			 (getquantity(endstring,ULTIMA,NULL_P,YES,is_oblique)==LONG)) {
/*
 * diwru + xwn   --> diwru/xwn
 * diwru + xessi --> diwru/xessi
 */
				p = getsyll(workstem,ULTIMA,0);
			 	addaccent(workstem,ACUTE,p);
		} else
/* 
 * diwru + xos	--> diw/ruxos
 */
			addaccent(workstem,ACUTE,p);
		Xstrncpy(tmp,workstem,MAXWORDSIZE);
		Xstrncat(tmp,endstring,MAXWORDSIZE);
		Xstrncpy(word,tmp,MAXWORDSIZE);
		return;
	}

	Xstrncpy(tmp,workstem,MAXWORDSIZE);
	Xstrncat(tmp,endstring,MAXWORDSIZE);

	fixnacc2(tmp,gstring,form_info,is_ending,is_oblique);
	Xstrncpy(word,tmp,MAXWORDSIZE);

}

static
fixnacc2(char *targstring, gk_string *gstring, word_form form_info, int is_ending, bool is_oblique)
{
	register char *p;
	MorphFlags * mflags = morphflags_of(gstring);
	bool is_contr;
	
	is_contr = has_morphflag(mflags,CONTRACTED);


	if( cur_lang() == LATIN || cur_lang() == ITALIAN ) return;
	/* if accent's already there, forget it */
	for (p=targstring;*p;p++)
		if (Is_accent(*p))
			return;
/*
 * grc 7/27/89
 *
 * assume that this is an ending
 */
 	is_ending = YES;

/*
 * grc 8/23/94
 *
 * why is this here? it screws up situations such as the 
 * epsilon contract nom pl ending ousai which should be ou=sai but
 * because of this becomes "ou/sai".
 *
 	if( has_morphflag(morphflags_of(gstring),CONTRACTED) ) is_oblique = YES;
 * for now, i comment it out and we will see what else breaks
 */

	if (getquantity(targstring,ULTIMA,NULL_P,is_ending,is_oblique) == LONG||
			((nsylls(targstring) ==1 ) && (is_ending&&is_contr))) {
		p = getsyll(targstring,PENULT,is_ending);
		if (p == P_ERR) {
			if( Accent_optional(mflags) ) {
				return;
			}
			p = getsyll(targstring,ULTIMA,is_ending);
			if( ulttakescirc(gstring,form_info) ) {
				addaccent(targstring,CIRCUMFLEX,p);
			} else {
				addaccent(targstring,ACUTE,p);
			}
		} else {
			addaccent(targstring,ACUTE,p);
		}
	}  else {		/* short ultima */
		p = getsyll(targstring,ANTEPENULT,is_ending);
		if (p != P_ERR) /* if it has an antepenult */
			addaccent(targstring,ACUTE,p);
		else {		/* no antepenult */
			if( Accent_optional(mflags) ) {
				return;
			}
			p = getsyll(targstring,PENULT,is_ending);
			if (p == P_ERR)
				p = getsyll(targstring,ULTIMA,is_ending);
			if (getquantity(targstring,PENULT,NULL_P,is_ending,is_oblique&&!is_contr) == LONG && ! Is_enclitic(mflags) ) {
				addaccent(targstring,CIRCUMFLEX,p);
			} else { 	/* short penult or none at all */
				addaccent(targstring,ACUTE,p);
			}
		}
	}
}
