#include <gkstring.h>
#define MAXAUG 8
#define TEMP_AUGMENT SYLL_AUGMENT * 2

#include "augment.proto.h"
static augmentit(gk_word *, bool, int);
typedef struct {
	char noaug[MAXAUG];
	char withaug[MAXAUG];
	Dialect augdial;
	char uniqueflag;
} augtable;

/*
 * Smyth 435
 */
augtable TempAugments[] = {

	"ai)",	"h)|",	(Dialect)ALL_DIAL,   0,
	"ai(",	"h(|",	(Dialect)ALL_DIAL,   0,
	"ei)",	"h)|",	(Dialect)ALL_DIAL,   0,
	"ei(",	"h(|",	(Dialect)ALL_DIAL,   0,

	"oi)",	"w)|",	(Dialect)ALL_DIAL,   0,
	"oi(",	"w(|",	(Dialect)ALL_DIAL,   0,

/*
 * commented out 8/24/88 grc
 * if you use these, you end up with forms like 
 *     "e)chi/thsa" rather than "e)ch/ithsa"
 
	iota addscripts vs. subscripts are the underlying problem--not sure what the best
	way to deal with them is at this point. this is yet another loose end.
	"ai)",	"h)i",	(Dialect)ALL_DIAL,   0,
	"ai(",	"h(i",	(Dialect)ALL_DIAL,   0,
	"ei)",	"h)i",	(Dialect)ALL_DIAL,   0,
	"ei(",	"h(i",	(Dialect)ALL_DIAL,   0,
*/	
	"oi)",	"w)|",	(Dialect)ALL_DIAL,   0,
	"oi(",	"w(|",	(Dialect)ALL_DIAL,   0,


	"au)",	"hu)",	(Dialect)ALL_DIAL,   0,
	"au(",	"hu(",	(Dialect)ALL_DIAL,   0,

	"au)",	"au)",	(Dialect)DORIC,   0,
	"au(",	"au(",	(Dialect)DORIC,   0,

	"eu)",	"hu)",	(Dialect)ALL_DIAL,   0,
	"eu(",	"hu(",	(Dialect)ALL_DIAL,   0,

	"e)e",	"e)e",	(Dialect)EPIC,   1,
	"e(e",	"e(e",	(Dialect)EPIC,   1,

	"a)",	"h)",	(Dialect)(ATTIC|IONIC|EPIC),   0,
	"a(",	"h(",	(Dialect)(ATTIC|IONIC|EPIC),   0,
/*
 * grc 6/23/89
 *
 * all these dialects were screwing up the sort weight of this augment and
 * making the doric form precede the attic!
 *
	"a)",	"h)",	(Dialect)ALL_DIAL,   0,
	"a(",	"h(",	(Dialect)ALL_DIAL,   0,
*/
	"a)",	"a_)",	(Dialect)(DORIC|AEOLIC),   0,
	"a(",	"a_(",	(Dialect)(DORIC|AEOLIC),   0,

	"e)",	"h)",	(Dialect)ALL_DIAL,   0,
	"e(",	"h(",	(Dialect)ALL_DIAL,   0,

	"h(",	"h(",	(Dialect)ALL_DIAL,   0,
	"h)",	"h)",	(Dialect)ALL_DIAL,   0,

	"i(",	"i_(",	(Dialect)ALL_DIAL,   0,
	"i)",	"i_)",	(Dialect)ALL_DIAL,   0,

	"o)",	"w)",	(Dialect)ALL_DIAL,   0,
	"o(",	"w(",	(Dialect)ALL_DIAL,   0,

	"w)",	"w)",	(Dialect)ALL_DIAL,   0,
	"w(",	"w(",	(Dialect)ALL_DIAL,   0,

	"u)",	"u_)",	(Dialect)ALL_DIAL,   0,
	"u(",	"u_(",	(Dialect)ALL_DIAL,   0,

	"ou)",	"ou)",	(Dialect)ALL_DIAL,   0,
	"ou(",	"ou(",	(Dialect)ALL_DIAL,   0,
	0,
};

/*
 * Smyth 431 
 */
augtable SyllAugments[] = {
/*
 *	i)dw/n, ei)=don
 */
	"i)",	"ei)",	(Dialect)ALL_DIAL,   0,
	"i(",	"ei(",	(Dialect)ALL_DIAL,   0,

	"i)",	"e)i",	(Dialect)ALL_DIAL,   0,
	"i(",	"e(i",	(Dialect)ALL_DIAL,   0,

/*
 * oi)wni/zomai --> oi)wni/zonto
 */
	"oi)w",	"oi)w",	(Dialect)ALL_DIAL,   0,

	"e)oi",	"e)w|",	(Dialect)ALL_DIAL,   1,
	"e(oi",	"e(w|",	(Dialect)ALL_DIAL,   1,

	"oi)",	"e)w|",	(Dialect)ALL_DIAL,   0,
	"oi(",	"e(w|",	(Dialect)ALL_DIAL,   0,

/*
 * if you already have "ei", don't do anything to the stem.
 *	e.g., "ei)p" stays "ei)p".
 * but if you are analyzing "ei", try "e" 
 *	e.g. get "e(l" from "ei(l"
 */
	"ei(",	"ei(", 	(Dialect)ALL_DIAL,   0,
	"ei)",	"ei)", 	(Dialect)ALL_DIAL,   0,

	"e)",	"ei)",	(Dialect)ALL_DIAL,   0,
	"e(",	"ei(",	(Dialect)ALL_DIAL,   0,
/*
 * grc 9/8/88
 *
 * the long alpha may not be right here -- it is taken from the example of 
 * $e(a_/lwn& vs. $a(/lw=&.  The length may be due to the influence of "Attic 
 * reduplication", but we will make it the rule for now.
 *
 * grc 9/17/88
 *
 * well, so much for that: remember forms such as $e(/a^de&.
 */
	"a)",	"e)a",	(Dialect)ALL_DIAL,   0,
	"a(",	"e(a",	(Dialect)ALL_DIAL,   0,

	"h)",	"e)h",	(Dialect)ALL_DIAL,   0,
	"h(",	"e(h",	(Dialect)ALL_DIAL,   0,

	"w)",	"e)w",	(Dialect)ALL_DIAL,   0,
	"w(",	"e(w",	(Dialect)ALL_DIAL,   0,

	"o)",	"e)w",	(Dialect)ALL_DIAL,   0,
	"o(",	"e(w",	(Dialect)ALL_DIAL,   0,

	"e)",	"ei)",	(Dialect)ALL_DIAL,   0,
	"e(",	"ei(",	(Dialect)ALL_DIAL,   0,
	
	"eu)",	"eu)",	(Dialect)ALL_DIAL,   0,
	"eu(",	"eu(",	(Dialect)ALL_DIAL,   0,


	"ou)",	"e)ou",	(Dialect)ALL_DIAL,   0,
	"ou(",	"e(ou",	(Dialect)ALL_DIAL,   0,
	0,
};

do_syllaug(gk_word *gkform, int maxaugs)
{
	int i;
	int naugs = 0;
	Dialect d;
	int compval;
	int wstart;
	char tmpstem[MAXWORDSIZE];
	gk_word TmpGkword;
	
	TmpGkword = *gkform;

	Xstrncpy(tmpstem,workword_of(gkform),MAXWORDSIZE);
	striphyph(tmpstem);
	
	for(i=0;SyllAugments[i].noaug[0];i++) {
		compval = Xstrncmp( SyllAugments[i].noaug , tmpstem , Xstrlen(SyllAugments[i].noaug ));
		if( ! compval ) {
			char tmp[MAXWORDSIZE];
			*(gkform+naugs) = TmpGkword;
			
			if((d=AndDialect(dialect_of(gkform+naugs),SyllAugments[i].augdial))<0) {
				continue;
			}
if( d ) set_dialect((gkform+naugs),d);
			Xstrncpy(tmp,SyllAugments[i].withaug,MAXWORDSIZE);
			wstart = Xstrlen(SyllAugments[i].noaug);
			if( tmpstem[wstart] == HARDSHORT ) wstart++;
			
			Xstrncat(tmp,tmpstem+wstart ,MAXWORDSIZE);
			sprintf(aug1_of(gkform+naugs),"%s>%s", SyllAugments[i].noaug,SyllAugments[i].withaug);

/*
			if(d) set_dialect(aug1_gstr_of((gkform+naugs)),d);
			else 
*/
			set_dialect(aug1_gstr_of((gkform+naugs)),SyllAugments[i].augdial);
			add_morphflag(morphflags_of(aug1_gstr_of(gkform+naugs)),SYLL_AUG);
			zap_morphflag(morphflags_of(stem_gstr_of(gkform+naugs)),SYLL_AUG);
			
			set_workword((gkform+naugs),tmp);
			naugs++;
			if( naugs >= maxaugs ) {
fprintf(stderr,"temp: got naugs %d with max %d\n", naugs , maxaugs );
				break;
			}
			
			if( SyllAugments[i].uniqueflag ) break;
		}
	}
	return(naugs);
}

do_tempaug(gk_word *gkform, int maxaugs)
{
	int i, wstart;
	int naugs = 0;
	char tmpstem[MAXWORDSIZE];
	Dialect d;
	gk_word TmpGkword;
	
	TmpGkword = *gkform;

	Xstrncpy(tmpstem,workword_of(gkform),MAXWORDSIZE);
	striphyph(tmpstem);

	for(i=0;TempAugments[i].noaug[0];i++) {
		if( !Xstrncmp( TempAugments[i].noaug , tmpstem , Xstrlen(TempAugments[i].noaug ))) {
			char tmp[MAXWORDSIZE];
			*(gkform+naugs) = TmpGkword;

			if((d=AndDialect(dialect_of(gkform+naugs),TempAugments[i].augdial))<0) {
				continue;
			}

			if( d ) set_dialect((gkform+naugs),d);

			Xstrncpy(tmp,TempAugments[i].withaug,MAXWORDSIZE);

			wstart = Xstrlen(TempAugments[i].noaug);
			if( tmpstem[wstart] == HARDSHORT ) wstart++;
			Xstrncat(tmp,tmpstem+wstart ,MAXWORDSIZE);

/*			
			Xstrncat(tmp,tmpstem+wstart ,MAXWORDSIZE);
*/
			sprintf(aug1_of(gkform+naugs),"%s>%s", TempAugments[i].noaug,TempAugments[i].withaug);

/*
			if(d) set_dialect(aug1_gstr_of((gkform+naugs)),d);
			else 
*/
			set_dialect(aug1_gstr_of((gkform+naugs)),TempAugments[i].augdial);

			set_workword((gkform+naugs),tmp);
			naugs++;
			if( naugs >= maxaugs ) {
fprintf(stderr,"temp: got naugs %d with max %d\n", naugs , maxaugs );
				break;
			}
			if( TempAugments[i].uniqueflag ) break;
		}
	}
	return(naugs);
}

/*
 * this has to do a better job with dialects at some point 
 *
 * grc 3/21/91
 *
 * this thing checks for whether you are undoing an reduplication
 *
 * if not, then these stems should only be attached to indicatives
 */
unaugment(char *s, gk_string *possibs[], gk_string *qpossibs[], int maxstems, Dialect dial, int wantsyllaugs, int wantredupl)
{
	int rval = 0;
	int compval;
	int i;
	char augnoquant[MAXWORDSIZE];
	Dialect d;


	if( ! Xstrncmp(s,"e)rr",4) ) {
		rval = 1;
		Xstrncpy(gkstring_of(possibs[0]),"r(",MAXWORDSIZE);
		Xstrncat(gkstring_of(possibs[0]),s+4,MAXWORDSIZE);
		if( ! wantredupl ) {
			set_mood(forminfo_of(possibs[0]),INDICATIVE);
		}
		return(rval);
	}
	
	if( ! Xstrncmp(s,"e)r",3) ) {
		rval = 1;
		Xstrncpy(gkstring_of(possibs[0]),"r(",MAXWORDSIZE);
		Xstrncat(gkstring_of(possibs[0]),s+3,MAXWORDSIZE);
		add_morphflag(morphflags_of(possibs[0]),RAW_SONANT);
		if( ! wantredupl ) {
			set_mood(forminfo_of(possibs[0]),INDICATIVE);
		}
		return(rval);
	}
	
	if( ! Xstrncmp(s,"e)",2) && Is_cons(*(s+2)) ) {
		rval = 1;
		Xstrncpy(gkstring_of(possibs[0]),s+2,MAXWORDSIZE);
		if(*(s+2) == *(s+3) ) { /* e)/llabe, e)ssei/onto 429 a. D */
			rval = 2;
			Xstrncpy(gkstring_of(possibs[1]),s+3,MAXWORDSIZE);
			add_morphflag(morphflags_of(possibs[1]),SYLL_AUGMENT);
		}
		if( ! wantredupl ) {
			set_mood(forminfo_of(possibs[0]),INDICATIVE);
		}
		return(rval);
	}
	
	for(i=0;TempAugments[i].noaug[0] && rval<maxstems;i++) {
		Xstrncpy(augnoquant,TempAugments[i].withaug,MAXWORDSIZE);
		stripquant(augnoquant);
		compval = morphstrncmp( augnoquant , s , strlen(augnoquant) );
		if( ! compval ) {
			char tmp[128];

			Xstrncpy(tmp,TempAugments[i].noaug,MAXWORDSIZE);

/*
			Xstrncat(tmp,s+Xstrlen(TempAugments[i].withaug),MAXWORDSIZE );
*/
			Xstrncat(tmp,s+Xstrlen(augnoquant) ,MAXWORDSIZE);
			Xstrncpy(gkstring_of(possibs[rval]),tmp,MAXWORDSIZE);

			if( strcmp(augnoquant,TempAugments[i].withaug) ) {
				Xstrncpy(tmp,TempAugments[i].withaug,MAXWORDSIZE);
				Xstrncat(tmp,s+Xstrlen(augnoquant) ,MAXWORDSIZE);
				Xstrncpy(gkstring_of(qpossibs[rval]),tmp,MAXWORDSIZE);
				set_dialect(possibs[rval],TempAugments[i].augdial );
			}
			if( ! wantredupl ) {
				set_mood(forminfo_of(possibs[rval]),INDICATIVE);
			}
			rval++;
		}
	}

	if( ! wantsyllaugs ) return(rval);
	
	for(i=0;SyllAugments[i].noaug[0] && rval<maxstems;i++) {
		Xstrncpy(augnoquant,SyllAugments[i].withaug,MAXWORDSIZE);
		stripquant(augnoquant);
		compval = morphstrncmp( augnoquant , s , strlen(augnoquant) );

		if( ! compval ) {
			char tmp[128];
			
			Xstrncpy(tmp,SyllAugments[i].noaug,MAXWORDSIZE);
/*
			Xstrncat(tmp,s+Xstrlen(SyllAugments[i].withaug) ,MAXWORDSIZE);
*/
			Xstrncat(tmp,s+Xstrlen(augnoquant) ,MAXWORDSIZE);
			Xstrncpy(gkstring_of(possibs[rval]),tmp,MAXWORDSIZE);
			set_dialect(possibs[rval],SyllAugments[i].augdial);
			add_morphflag(morphflags_of(possibs[rval]),SYLL_AUGMENT);
			if( ! wantredupl ) {
				set_mood(forminfo_of(possibs[rval]),INDICATIVE);
			}
			rval++;
		}
	}
	return(rval);
}


unaugfromlemma(char *stem, char *lemma)
{
	char tmp[MAXWORDSIZE];
	int i, withlen, noauglen;
	int compval;
/*
 * normal augment on consonantal stem, e.g. "e)ball" and "ba/llw"
 */
	if( !Xstrncmp(stem,"e)",2) ) {
	/*
 	 * if you have "e)" as an augment, but your lemma does not
	 * start with a consonant, you got something funny ...
	 *
 	 * yeah--you might have e)ws- as in w)qe/w, let it ride 
	 * 	grc 2/18/87
 	 */
		if( Is_cons(*lemma) ) {
			Xstrncpy(tmp,stem+2,MAXWORDSIZE);
			Xstrncpy(stem,tmp,MAXWORDSIZE);
			return(TEMP_AUGMENT);
		}
/* grc 2/18/87
		return(-1);
*/
	}

	for(i=0;TempAugments[i].noaug[0];i++) {
		withlen = Xstrlen(TempAugments[i].withaug);
		if( !Xstrncmp( TempAugments[i].withaug , stem , withlen)) {
			
			noauglen = Xstrlen(TempAugments[i].noaug);
/*
 * ok, so the you have a match between the augmented stem, and the
 * unaugmented lemma. make the current stem start the same way as
 * the lemma
 */
			if(!Xstrncmp( TempAugments[i].noaug, lemma ,noauglen)){

				Xstrncpy(tmp,TempAugments[i].noaug,MAXWORDSIZE);
				Xstrncat(tmp,stem+Xstrlen(TempAugments[i].withaug) ,MAXWORDSIZE);
				Xstrncpy(stem,tmp,MAXWORDSIZE);
				return(TEMP_AUGMENT);
			}
		}
	}
	for(i=0;SyllAugments[i].noaug[0];i++) {
		withlen = Xstrlen(SyllAugments[i].withaug);
		compval = Xstrncmp( SyllAugments[i].withaug , stem , withlen);
		if( ! compval ) {	
			noauglen = Xstrlen(SyllAugments[i].noaug);
/*
 * ok, so the you have a match between the augmented stem, and the
 * unaugmented lemma. make the current stem start the same way as
 * the lemma
 */
			if(!Xstrncmp( SyllAugments[i].noaug, lemma ,noauglen)){

				Xstrncpy(tmp,SyllAugments[i].noaug,MAXWORDSIZE);
				Xstrncat(tmp,stem+Xstrlen(SyllAugments[i].withaug),MAXWORDSIZE );
				Xstrncpy(stem,tmp,MAXWORDSIZE);
				return(SYLL_AUGMENT);
			}
		}
	}
	return(-1);
}

add_augment(gk_word *gkform, MorphFlags *mf, int maxaugs)
{
	bool syllabic;
	char * res;
	int rval = 0;
	gk_string SaveGstr;
	gk_string * tmpgstr;
	
	tmpgstr = &SaveGstr;

	syllabic = syll_augment(morphflags_of(stem_gstr_of(gkform))) ? YES : NO;
	res = workword_of(gkform);
	set_morphflags(&SaveGstr,mf);
/*
	if( skip_augment(morphflags_of(tmpgstr)) ) {
*
* grc 1/11/96
* added the following to deal with iteratives, which should never be augmented
*
*/
	if( skip_augment(morphflags_of(tmpgstr)) || skip_augment(morphflags_of(ends_gstr_of(gkform))) ) {
		add_morphflag(morphflags_of(stem_gstr_of(gkform)),UNAUGMENTED);
		return(0);
	}

	if( cur_lang() == LATIN || cur_lang() == ITALIAN ) return(0);

	if( ! needs_augment2(gkform,res) ) {
		zap_morphflag(morphflags_of(stem_gstr_of(gkform)),SYLL_AUGMENT);
		if( Has_augment(morphflags_of(stem_gstr_of(gkform))))
			return(1);
		return(0);
	}
	
	/*
	if( mf & UNAUGMENTED ) {
		add_morphflag(morphflags_of(stem_gstr_of(gkform)),UNAUGMENTED);
		return(0);
	}	
	*/

	rval = augmentit(gkform,syllabic,maxaugs);

	add_morphflag(morphflags_of(stem_gstr_of(gkform)),HAS_AUGMENT);

	return(rval);
}

needs_augment(gk_string *gstr)
{
	gk_word * TmpGkword;
	int rval;
	
	TmpGkword = CreatGkword(2);
	if( ! TmpGkword ) {
		fprintf(stderr,"no memory for TmpGkword in needs_augment\n");
		return(0);
	}
	*(stem_gstr_of(TmpGkword)) = * gstr;

	forminfo_of(TmpGkword) = forminfo_of(gstr);
	rval = needs_augment2(TmpGkword,"");
	FreeGkword(TmpGkword);
	return(rval);
}

needs_augment2(gk_word *gkform, char *stem)
{
	word_form v_form;
	
	v_form = forminfo_of(gkform);
	
	if( Has_augment(morphflags_of(stem_gstr_of(gkform))) ) 
		return(0);
		
	if(mood_of(v_form) != INDICATIVE) {
		return(0);
	}

	switch (tense_of(v_form)) {
	case IMPERF:
		return(1);
	case AORIST:		
		return(1);
	case PLUPERF:
		/*
		 * grc 6/25/89
		 *
		 * Smyth 444a
		 *  if you have the attic_redupl, then you almost always augment the pluperf
		 */
		if( has_morphflag(morphflags_of(stem_gstr_of(gkform)),ATTIC_REDUPL)) 
		 	return(1);
		/*
		 * Smyth 444
		 *
		 * e)/stalka, e)/stalkh
		 * h)go/reuka, h)goreu/kh
		 */
		if( *stem == 'e' || * stem == 'h' )
			return(0);
		return(1);
	default:
		return(0);
	}	/* switch */
}


 
simpleaugment(char *s, bool syllabic)
{
	gk_word * gkform;

	gkform = CreatGkword(6);
	if( ! gkform ) {
		fprintf(stderr,"no memory for gkform in simpleaugment of [%s]\n",s);
		return;
	}
		
	set_workword(gkform,s);
	augmentit(gkform,syllabic,5);
	Xstrncpy(s,workword_of(gkform),MAXWORDSIZE);
	FreeGkword(gkform);
}

static
augmentit(gk_word *gkform, bool syllabic, int maxaugs)
{
	char * s = workword_of(gkform);
	gk_string * stem_gstr = stem_gstr_of(gkform);
	
	if( Is_cons(*s) ) {
		if (0==Xstrncmp("r(",s,2)) {
			if(has_morphflag(morphflags_of(stem_gstr),RAW_SONANT))
				stripbreath(s);
			else
				s[1] = 'r';	/* replace breathing with 'r' */
			strcpy(aug1_of(gkform),"r(>e)rr");
				
		} else if( has_morphflag(morphflags_of(stem_gstr),SYLL_AUGMENT)) {
			cinsert(*s,s);
			sprintf(aug1_of(gkform),"%c>e)%c%c", *s, *s , *s );
		}
		cinsert (SMOOTHBR,s);
		cinsert ('e',s);
		if( ! aug1_of(gkform)[0] ) strcpy(aug1_of(gkform),"e)");
		return(1);
	}

	if( syllabic )
		return(do_syllaug(gkform,maxaugs));
	else
		return(do_tempaug(gkform,maxaugs));
}

simpleredupit(char *s, int syllabic, int redupc)
{
	gk_word * gkform;

	gkform = CreatGkword(6);
	if( ! gkform ) {
		fprintf(stderr,"no memory for gkform in simpleaugment of [%s]\n",s);
		return;
	}
		
	set_workword(gkform,s);
	redupit2(gkform,syllabic,redupc,5);
	Xstrncpy(s,workword_of(gkform),MAXWORDSIZE);
	FreeGkword(gkform);
}

redupit2(gk_word *gkform, int syllabic, int redupc, int nredups)
{
/* Smyth 440-442 */
	register char c;
	register char * s = workword_of(gkform);

	if( Is_cons(*s) && Is_cons(*(s+1)) && ! Is_liquid(*(s+1)) && redupc != 'i' )
		return(augmentit(gkform,syllabic,nredups));
	else if( *s == 'z' || *s == 'c' /* grc 7/6/89 -- added 'y' */ || *s == 'y' )
		return(augmentit(gkform,syllabic,nredups));
	else if (Is_vowel(*s) ||  *s ==  'r'  )
		return(augmentit(gkform,syllabic,nredups));
	else if ( (! Xstrncmp("gn",s,2) || ! Xstrncmp("gl",s,2)) && redupc != 'i' )
	/*
	 * this exception leads to e)-gnwk-a but gi-gnw/skw 
	 *  grc 4/27/89
	 */
		return(augmentit(gkform,syllabic,nredups));
/*
simpleaugment(s,syllabic);
*/
	 else {
		c = *s;
		if (c == 'q')
			c = 't';
		if (c == 'x')
			c = 'k';
		if (c == 'f')
			c = 'p';
		cinsert (redupc,s);
		cinsert (c,s);
		}
	return(1);
}

un_redupl(char *src, char *res, int redupc)
{
	char sbuf[MAXWORDSIZE+1], * p;
	
	*res = 0;
	Xstrncpy(sbuf,src,MAXWORDSIZE);
	stripacc(sbuf);
	
/*
 * grc 6/11/89
 *
 * do not accept kukl- as a valid reduplicated form
 */
	if( *(sbuf+1) != redupc ) return(0);
	
	p = sbuf+2;
	if( *p == 'q' ) *p = 't';
	else if( *p == 'x' ) *p = 'k';
	else if( *p == 'f' ) *p = 'p';
	if( sbuf[0] == sbuf[2] ) {
		Xstrncpy(res,src+2,MAXWORDSIZE);
		return(1);
	}
	return(0);
	
}

/*
 * this is a simple routine, as it assumes that all double augments will
 * be  
 *    a --> h  [e.g., a)mfi/, a)na/]
 * or
 *    e --> h [e.g., e)n]
 */
add_double_augment(char *s, MorphFlags *oddpb)
{
	
	simpleaugment(s,NO);
/*
	if(*s == 'a' || *s == 'e' ) {
		*s = 'h';
*/
/*
		add_morphflag(morphflags_of(prvb_gstr_of(gkform)),HAS_AUGMENT);
*/
		add_morphflag(oddpb,HAS_AUGMENT);
	
/*
	}
*/
}
