#include <gkstring.h>
#include <modes.h>
#include "endfiles.h" 

#ifdef LIGHTSPEED
char * GetEndString();

#endif

#include "retrends.proto.h"
static gk_string *RetrCompEnds(gk_string *, gk_string *, int *, Dialect);
static ProcEndRecord(char *, gk_string *);
static char *GetEndString(char *, gk_string *);
static NoWantGkEnd(gk_string *, gk_string *, int);
static AddNewEnd(gk_string *, gk_string *, int);

static gk_string  Cur_gkend;

static gk_string WantEnd;
static gk_string AvoidEnd;
static gk_string BlankGkend;
static gk_word BlankGkword;
gk_string * CreatGkString();
static int start_match = 0;

gk_string *
 chckendings(char *endstr, char *restricts, char *stemstr, char *prevbstr, Dialect dial, int *nends)
{
	gk_string * gstring;
	char stemkeys[BUFSIZ];
	Dialect OrDialect;
	gk_string * tmpgstr;
	gk_word  * BlnkGkword;


	Xstrncpy(stemkeys,restricts,(int)sizeof stemkeys);

/*
 * ok, we want to process the restrictions associated with this stem, and then
 * use this information to get appropriate endings (e.g., if the stem
 * is deponent, we don't want to get any active endings ).
 */

	WantEnd = BlankGkend;
	AvoidEnd = BlankGkend;

	tmpgstr = &WantEnd;

	BlnkGkword = CreatGkword(1);
	
	ScanAsciiKeys(stemkeys,BlnkGkword,&WantEnd,&AvoidEnd);
	FreeGkword(BlnkGkword);
	
/*
printf("\nstemkeys [%s]\n", stemkeys );
printf("WantEnd:"); PrntAGstr(&WantEnd,stdout); printf("\n");
printf("AvoidEnd:"); PrntAGstr(&AvoidEnd,stdout); printf("\n");
*/
	if( ! stemtype_of(&WantEnd) ) {
		printf("could not find a stemtype for [%s] with restricts [%s]\n", 
			restricts );
		return(NULL);
	}

	if( endstr )
		set_gkstring(&WantEnd,endstr );
	if( stemstr ) {
		markstem(stemstr,&WantEnd);
	}

	OrDialect = dialect_of(&WantEnd);

	if( dial ) 
		add_dialect(&WantEnd,dial);
	else
		set_dialect(&WantEnd,dial);
		
	if( prevbstr ) {
		if( * prevbstr )
			add_morphflag(morphflags_of(tmpgstr),HAS_PREVERB);
	}

	if( /*Is_geog_name(morphflags_of(&WantEnd)) || */Is_pers_name(morphflags_of(tmpgstr))) {
		if( ! number_of(forminfo_of(&WantEnd)) ) 
			set_number(forminfo_of(&WantEnd),SINGULAR);
	}

/*
	if( !(gstring = RetrCompEnds(&WantEnd,&AvoidEnd,nends,OrDialect))) {
		return(NULL);
	}
*/
	gstring = RetrCompEnds(&WantEnd,&AvoidEnd,nends,OrDialect);
	return(gstring);
}

 CompatKeys(char *keys1, char *keys2, gk_string *gstr)
{
	gk_string  Gstr;
	gk_string  Gstr2;
	gk_word * BlnkGkword;
	int rval = 0;
	int is_deriv = 0;
	
	BlnkGkword = CreatGkword(1);
	
	is_deriv = has_morphflag(morphflags_of(gstr),IS_DERIV);
	Gstr = BlankGkend;
	Gstr2 = BlankGkend;
	*gstr = BlankGkend;
	if( is_deriv ) add_morphflag(morphflags_of(gstr),IS_DERIV);
	ScanAsciiKeys(keys1,BlnkGkword,gstr,NULL);
	ScanAsciiKeys(keys2,BlnkGkword,&Gstr2,NULL);
	FreeGkword(BlnkGkword);

	rval = EndingOk(keys2,gstr,&Gstr,1);
	/*
	 *  grc 3/16/91
	 *
	 *  suppose we match a stem "a):ss:pres" against "ss:aor2_pass".  we don't at this
	 *  point decide whether or not the aor2_pass stem type could be a present.  we just
	 *  make sure that only present forms will be generated -- thus we will generate no
	 *  present forms and filter out the problem later.
	 */
	if( rval ) {
		if( tense_of(forminfo_of(&Gstr2)) ) set_tense(forminfo_of(gstr),tense_of(forminfo_of(&Gstr2)));
		if( mood_of(forminfo_of(&Gstr2)) ) set_mood(forminfo_of(gstr),mood_of(forminfo_of(&Gstr2)));
		if( voice_of(forminfo_of(&Gstr2)) ) set_voice(forminfo_of(gstr),voice_of(forminfo_of(&Gstr2)));
	}

 	return(rval);
}
 
 
 EndingOk(char *keys, gk_string *gstr, gk_string *avoidgstr, int wantderiv)
{
	int good = 0;
	gk_word * BlnkGkword;
	
	Cur_gkend = BlankGkend;
	BlnkGkword = CreatGkword(1);
	ScanAsciiKeys(keys,BlnkGkword,&Cur_gkend,avoidgstr);
	FreeGkword(BlnkGkword);
	
	if( wantderiv ) {
		if( ! derivtype_of(gstr) || derivtype_of(gstr) < 0 ) return(0);
		
		if( derivtype_of(gstr) != derivtype_of(&Cur_gkend)) 
			return(0);
	}
	
	good =  (WantGkEnd(gstr,&Cur_gkend,NO,0) > 0) &&
	  (NoWantGkEnd(avoidgstr,&Cur_gkend,1) == 0 );
/*
if( ! good ) {
printf("gstr [%s] [%s] want %o nowant %o\n",gkstring_of(gstr), gkstring_of(&Cur_gkend), WantGkEnd(gstr,&Cur_gkend,NO,0) ,
NoWantGkEnd(avoidgstr,&Cur_gkend,1)  );
LPrntGstr(gstr,stdout);
LPrntGstr(&Cur_gkend,stdout);

}
*/
	if( good ) {
		int case1, case2;
		int gend1, gend2;
		int num2, pers2;
		int voice1, voice2;
		Dialect dial1, dial2;

		voice1 = voice_of(forminfo_of(&Cur_gkend));
		voice2 = voice_of(forminfo_of(gstr));
		
		if( voice1 ) set_voice(forminfo_of(gstr),voice1);
		
		case1 = case_of(forminfo_of(&Cur_gkend));
		case2 = case_of(forminfo_of(gstr));
		if( case1 & case2 )
			set_case(forminfo_of(gstr), (case1 & case2) );
		else if( case1 && ! case2 )
			set_case(forminfo_of(gstr), case1 );
	
		num2 = number_of(forminfo_of(&Cur_gkend));
		if( num2 )
			set_number(forminfo_of(gstr), number_of(forminfo_of(&Cur_gkend)) );

		pers2 = person_of(forminfo_of(&Cur_gkend));
		if( pers2 )
			set_person(forminfo_of(gstr), person_of(forminfo_of(&Cur_gkend)) );

		gend1 = gender_of(forminfo_of(&Cur_gkend));
		gend2 = gender_of(forminfo_of(gstr));
		if( gend1 & gend2 )
			set_gender(forminfo_of(gstr), (gend1 & gend2) );
		else if( gend1 && ! gend2 )
			set_gender(forminfo_of(gstr), gend1 );

		dial1 = dialect_of(&Cur_gkend);
		dial2 = dialect_of(gstr);
		if( dial1 & dial2 ) 
			set_dialect(gstr,(dial1 & dial2) );
		else if( dial1 && (! dial2) )
			set_dialect(gstr,dial1);
			
		add_morphflags(gstr,morphflags_of(&Cur_gkend));
	}
	return( good );
}

static gk_string *
 RetrCompEnds(gk_string *wantgkend, gk_string *avoidgkend, int *nends, Dialect OrDialect)
{
	gk_string * ListOfEnds;
	gk_string * CurrentList, *GetCurrentEndList();
	int rval, avoidrval;
	int lno = 0;
	int maxend = 0;
	char fname[BUFSIZ];
	int i;

	*nends = 0;
	
	CurrentList = GetCurrentEndList(wantgkend,&lno);

/*
	sprintf(fname,"%s/out/%s.out", ENDTABLEDIR , NameOfStemtype(stemtype_of(wantgkend)) );

	if( (f=MorphFopen(fname,"rb")) == NULL ) {
		fprintf(stderr,"stemtype %o, could not open %s\n", stemtype_of(wantgkend), fname );
		return(NULL);
	}
	

	lno = get_endheader(f,&maxend);
	while((rval=ReadEnding(f,&Cur_gkend,maxend)) > 0 ) {
*/
	ListOfEnds = (gk_string *) CreatGkString( lno + 2 );

	if( ! ListOfEnds ) {
		fprintf(stderr,"Could not find space to store %d greek endings for stem %s\n", lno + 2 , 
		NameOfStemtype(stemtype_of(wantgkend)) );
		return(NULL);
	}

/*
printf("want %s:", gkstring_of(wantgkend) ); PrntGkFlags(wantgkend,stdout); printf("\n");
printf("avoid %s:", gkstring_of(wantgkend) ); PrntGkFlags(avoidgkend,stdout); printf("\n");
*/

	for(i=0;i<lno;i++) {
		Cur_gkend = * (CurrentList+i);
/*

printf("peering at [%s]\n", gkstring_of((&Cur_gkend))); 
PrntAGstr((&Cur_gkend),stdout); printf("\n");
*/
		rval=WantGkEnd(wantgkend,&Cur_gkend,YES,YES);
		avoidrval=NoWantGkEnd(avoidgkend,&Cur_gkend,0);

		if( rval < 0 || avoidrval ) {
/*
fprintf(stdout,"failed on want [%s] and have [%s]\n", gkstring_of(wantgkend) , gkstring_of((&Cur_gkend)) );
fprintf(stdout,"rval %o avoid %o\n", rval ,avoidrval );
*/
			break;
		}
		if( rval && ! avoidrval ) {
/*

printf("want [%s] ", gkstring_of(&Cur_gkend) ); putchar('\n');
PrntAGstr(&Cur_gkend,stdout); putchar('\n');
*/

	    	set_stemtype(&Cur_gkend,stemtype_of(wantgkend) );

		    AddNewEnd(ListOfEnds,&Cur_gkend,*nends);
	            (*nends)++;
		}
/*
else if( !strcmp( gkstring_of(&Cur_gkend),gkstring_of(wantgkend)) ) {

fprintf(stdout,"rval %d avoidrval %d\n", rval  , avoidrval );
printf("avoidgkend:"); PrntGkFlags(avoidgkend,stdout); printf("\n");
printf("wantgkend:"); PrntGkFlags(wantgkend,stdout); printf("\n");
printf("Cur_gkend:"); PrntGkFlags(&Cur_gkend,stdout); printf("\n\n");
		}
*/
	}


	if( ! *nends ) {
		FreeGkString(ListOfEnds);
		ListOfEnds = NULL;
		return(NULL);
	}
	
	return(ListOfEnds);
}

static
 ProcEndRecord(char *s, gk_string *gkend)
{
	gk_word * BlnkGkword;
	
	BlnkGkword = CreatGkword(1);
	s=GetEndString(s,gkend);
	ScanAsciiKeys(s,BlnkGkword,gkend,NULL);
	FreeGkword(BlnkGkword);
}

static char * 
 GetEndString(char *s, gk_string *gkend)
{
	char tmp[128];
	char *a;

	a = tmp; 
	while( isspace( *s ) ) s++;
	if( ! *s ) return(NULL);
	while( ! isspace( *s ) && *s ) *a++ = *s++;
	*a = 0;
	while( isspace( *s ) ) s++;
	if( !*s ) return(NULL);
	set_gkstring(gkend,tmp);
	return(s);
}

static
 NoWantGkEnd(gk_string *skipend, gk_string *haveend, int strict)
{

	if( dialect_of(skipend) ) {
		if( ! dialect_of(haveend) ) return(0);
		if( AndDialect(dialect_of(skipend),dialect_of(haveend)) > 0 )
			return(1);
	}
	if( ! gkstring_of(skipend)[0] &&
		! mood_of(forminfo_of(skipend)) &&
		! tense_of(forminfo_of(skipend)) &&
		! voice_of(forminfo_of(skipend)) &&
		! number_of(forminfo_of(skipend)) &&
		! person_of(forminfo_of(skipend)) &&
		! gender_of(forminfo_of(skipend)) &&
		! case_of(forminfo_of(skipend)) &&
/*		! dialect_of(skipend) &&*/
		! stemtype_of(skipend) &&
		 no_morphflags(skipend))
			return(0);

	return( WantGkEnd(skipend,haveend,NO,strict) <= 0 ? 0 : 1 );

}

/*
 * return codes
 *
 *	retcode = 0 -- don't want this ending
 *	retcode = 1 -- do want this ending
 *	retcode < 0 -- you want a string and have seen a string
 *		alphabetically past that string. use this
 *		return value if you are searching a sorted list
 *		
 */
/*static*/
 WantGkEnd(gk_string *wantend, gk_string *haveend, bool writeflag, int strict)
{
	int compval;

	word_form wform, hform;
/*
	Dialect wdial = dialect_of(wantend);
	Dialect hdial = dialect_of(haveend);
*/
	Dialect wdial;
	Dialect hdial;

	Dialect d/*, AndDialect()*/;

	int wmood = mood_of( forminfo_of(wantend) );
	int hmood = mood_of( forminfo_of(haveend) );

	int wvoice = voice_of( forminfo_of(wantend) );
	int hvoice = voice_of( forminfo_of(haveend) );

	int wtense = tense_of( forminfo_of(wantend) );
	int htense = tense_of( forminfo_of(haveend) );

	int wgender = gender_of( forminfo_of(wantend) );
	int hgender = gender_of( forminfo_of(haveend) );

	int wdegree = degree_of( forminfo_of(wantend) );
	int hdegree = degree_of( forminfo_of(haveend) );

	int wcase = case_of( forminfo_of(wantend) );
	int hcase = case_of( forminfo_of(haveend) );

	int wperson = person_of( forminfo_of(wantend) );
	int hperson = person_of( forminfo_of(haveend) );

	int wnumber = number_of( forminfo_of(wantend) );
	int hnumber = number_of( forminfo_of(haveend) );

	char wendstr[MAXWORDSIZE];
	char * hendstr = gkstring_of(haveend);

	wform = forminfo_of(wantend);
	hform = forminfo_of(haveend);
	
/*
 * basically, we check to see if any particular form has been requested
 * and check each ending against this. if nothing is asked for (e.g. no
 * mood or voice is specified) then we just take the ending (i.e. we take
 * subjunctive, optative, indicative etc. rather than just the optatives or
 * subjunctives or whatever...
 */
	setwendstr(wendstr,gkstring_of(wantend));
	if( wmood && hmood != wmood ) {
		if( hmood || (!hmood && strict) ) {
#ifdef SHOWFAIL
printf("failing on wmood %o hmood %o\n", wmood, hmood );
#endif
			return(0);
		}
	}

/*
 *
 *  perfect actives are, by definition, always active in form
 */


   	if( (stemtype_of(wantend) & PPARTMASK ) == PP_PF ) {
   		wvoice = ACTIVE;
   		voice_of(wform) = ACTIVE;
   	}

   	if( (stemtype_of(wantend) & PPARTMASK ) == PP_SU && 
	     cur_lang() == LATIN && wvoice == DEPONENT ) {
			set_voice(forminfo_of(haveend), wvoice);
   	}

	if( cur_lang() == LATIN && wvoice == DEPONENT ) {
		if( hvoice == ACTIVE && hmood != PARTICIPLE && hmood != GERUNDIVE ) return(0);
	} else if( wvoice ) {
		if( ! Want_Voice( wform , hform )) {
		   if( hvoice || (!hvoice && strict)) {
#ifdef SHOWFAIL
printf("have [%s] failing on wvoice %o hvoice %o\n",hendstr, wvoice, hvoice );
#endif
				return(0);
			}
		} else {
/*
 * note that an ending may generally be either middle or passive, but
 * if the stem in hand is strictly middle or strictly passive,
 * then the ending inherits that limitation.
 */

			if( writeflag == YES )
			   set_voice(forminfo_of(haveend), wvoice);
		}
	}

	if( wtense && htense != wtense )
		if( htense || (!htense && strict) ) {
#ifdef SHOWFAIL
printf("failing on wtense %o htense %o\n", wtense, htense );
#endif
			return(0);
		}

/*
 * note that here you only fail if the gender is set in the
 * ending as well as in the stem.
 * 
 * if we follow the normal algorithm, a masculine stem would 
 * not match a set of endings that had no gender specified.
 *
 * likewise, we need to match either masculine or feminine against
 * an ending that is common to both (but not, for example, to a neuter
 * stem, e.g. -es in nom pl for masc and fem, but -a for neuter)
 */
/*

/*
 * only fail if gender set for both.
 * 	e.g., dwr- from dw=ron will want to find 
 * endings such as -on, or -a that are specifically flagged
 * as neuter, but will also want to find other endings
 * that can attach themselves to any gender
 */
	if( wgender ) {
		if( hgender ) {
			if( ! Want_Gender(wform, hform)) {
#ifdef SHOWFAIL
printf("failing with hgender %o and wgender %o\n", hgender , wgender );
#endif
				return(0);
			}
		}
		if( writeflag )
			if( Want_Gender(wform,hform) )
				set_gender(forminfo_of(haveend), Want_Gender(wform, hform));
			else
			   	set_gender(forminfo_of(haveend), wgender );
	}

	if( wcase ) {
		if( ! Want_Case(wform, hform))
			if( hcase || (!hcase && strict) ) {
#ifdef SHOWFAIL
printf("failing with hcase %o wcase %o\n", hcase , wcase );
#endif
				return(0);
			}
if( writeflag ) {
#ifdef SHOWFAIL
printf("[%s] hcase %o wcase %o anded %o\n", gkstring_of(haveend), hcase, wcase, hcase & wcase );
#endif
		set_case(forminfo_of(haveend) , wcase&hcase );
}
	}

	if( wperson && hperson != wperson ) {
		if( hperson || (!hperson && strict) ) {
#ifdef SHOWFAIL
printf("failing with hperson %o wperson %o\n", hperson , wperson );
#endif
			return(0);
		}
	}

	if( wnumber && hnumber != wnumber )
		if( hnumber || (!hnumber && strict) ) {
#ifdef SHOWFAIL
printf("failing on wnumber %o hnumber %o\n", wnumber , hnumber );
#endif
			return(0);
		}

	if( *wendstr && strict ) {
	
		if( (compval=endstrcmp(wendstr,hendstr))){
	/*
	 * this expects that you have a sorted list of endings and that you
	 * don't want to look for endings that are alphabetically larger
	 * than the ending that you want 
	 */
			if( compval < 0 && noaccstrcmp(wendstr,hendstr) ) {

#ifdef SHOWFAIL
#endif

				return(compval);
			}
#ifdef SHOWFAIL
printf("failing on wendsrr\n");
#endif
		/*
		 * don't fail if you did not specifically ask for a long vowel.
		 *
		 * do fail if you specifically ask for a long vowel and this ending is not 
		 * marked as long.
		 */
		if( has_quantacc(hendstr) != has_quantacc(wendstr) ) {
			char tmp[MAXWORDSIZE];
			
			Xstrncpy(tmp,hendstr,MAXWORDSIZE);
			stripquantacc(tmp);
			compval=endstrcmp(wendstr,tmp);
/*
			compval=dictstrcmp(wendstr,tmp);
*/
			if( compval  ) 				
						return(0);
		}  else
						return(0);
		} else {
			/*
			 * if you ask for "w=", then match only "w=" and not "w".
			 *
			 * if you ask for "w", however, then match both "w=" and "w".
			 */

			if( hasaccent(wendstr)  ) {
				char tmp1[MAXWORDSIZE];
				char tmp2[MAXWORDSIZE];
				
				Xstrncpy(tmp1,wendstr,(int)sizeof tmp1);
				stripquant(tmp1);
				
				Xstrncpy(tmp2,hendstr,(int)sizeof tmp2);
				stripquant(tmp2);
				if( strcmp(tmp1,tmp2) )
						return(0);
			}
		}
	}

	if(  ! EuphEnd(wantend,haveend,strict) ) {
#ifdef SHOWFAIL
printf("[%s] failing on euph end\n", gkstring_of(haveend) );
#endif
		return(0);
	}
	wdial = dialect_of(wantend);
	hdial = dialect_of(haveend);

/*
 * note that we are checking not for equality, but to see if
 * we want any of the dialect bits set for the current ending
 */
	if( (d=AndDialect(hdial,wdial)) < 0 )
		return(0);
/*
	else if( writeflag ) {
		set_dialect(haveend,d);
	}
*/
/*
 * we currently mark a)/ristos as "os_h_on superl". 
 * we thus want a)rist- to have all the normal endings (-os,-h,-on,-ou,-hs,-ou)
 * but not to have endings such as "-o/tatos" or "-w/teros" tacked onto it.
 */
 
/*
 * grc 6/5/89
 *
 * this system prevents morphology formulas from generating any actual endings.  the
 * formula has the flag "comp" or "superl", but none of the endings in the basic
 * paradigms are so marked, so they are all skipped.  i added the requirement that this
 * rule only be active if strict is non zero to get around this (this is much the same
 * strategy that we took with iteratives.
 */
	if( wdegree ) {
		if(  hdegree && wdegree != hdegree /* grc 6/5/89 */ && strict /* end mod*/) {
			if( hdegree || (!hdegree && strict) )
				return(0);
		}
		if( wdegree && writeflag ) set_degree(forminfo_of(haveend),wdegree);
	}

	if( ! RightMorphflags(wantend,haveend)) {
#ifdef SHOWFAIL
printf("[%s] failing on rightmorphflags\n", gkstring_of(haveend) );
#endif
		return(0);
	}
	return(1);
}

 RightMorphflags(gk_string *wantend, gk_string *haveend)
{
/*
 * this kludge checks to make sure that you don't yank create weird
 * comparatives or superlatives such as "a)gaqw/teros" or "a)risto/tatos"
 */
	if( (Is_irregcomp(morphflags_of(wantend)) || Is_irregsuperl(morphflags_of(wantend)) ||
		 Has_nocomp(morphflags_of(wantend)))
		&& ((Is_superlative(forminfo_of(haveend)) || Is_comparative(forminfo_of(haveend))))) {
			return(0);
		}

	/*
	 * o.k., suppose you have "gno/n" as neut nom sg part of "e)/gnwn"
	 * when you have the simplex, but "gnou/s" in compounds such as
	 * "diagnou/s". this matches up endings that can only go in
	 * composition with stems that have preverbs
	 */

	if( Comp_only(morphflags_of(haveend)) && ! Has_preverb(morphflags_of(wantend)) ) {
		if( ! has_morphflag(morphflags_of(wantend),IS_DERIV) )
			return(0);
	}
	if( Not_in_compos(morphflags_of(haveend)) && Has_preverb(morphflags_of(wantend)) ) {
		if( ! has_morphflag(morphflags_of(wantend),IS_DERIV) )
			return(0);
	}
	
	return(1);
}

static 
 AddNewEnd(gk_string *gstrings, gk_string *newgstr, int sofar)
{
	int i, rval;

	
	set_gkstring( gstrings + sofar + 1 , "" );

	if( sofar == 0 ) {
		*gstrings = *newgstr;
		return;
	}

/* 
 * this is computationally inefficient as you are copying whole data
 * structures rather than just pointers, but for now it will do.
 *
 */
/*
printf("starting with: "); PrntGkFlags(newgstr,stdout); printf("\n", rval );
*/
	for(i=sofar;i>=1;i--) {

		rval = CompGkString( gstrings+i-1 , newgstr );

		if( rval > 0 ) {
			*(gstrings+i) = *newgstr;
			return;
		}
		*(gstrings+i) = *(gstrings+i-1);
	}
	*gstrings = *newgstr;

}


setwendstr(char *wendstr, char *str)
{
	char * p = str;
	char * s = wendstr;
	
	*wendstr = 0;
	while(*p) {
		*s++ = *p++;
	}

	if(*(s-1) == HARDSHORT ) *--s = 0;
	if( *(s-1) == '-' && p > str) {
		start_match = 1;
		s--;
	} else
		start_match = 0;
	*s = 0;
	stripacc(wendstr);
}

endstrcmp(char *wendstr, char *haveendstr)
{
	char tmp[MAXWORDSIZE];
	char *hp, *sp;
	int i = 0;
	int wlen, j;
	
	
	if( start_match) {
		wlen = Xstrlen(wendstr);
		hp = haveendstr;
		sp = tmp;
		for(i=0;i<wlen;) {
			if( ! isalpha(*hp) && *(wendstr+i) != *hp ) {
				hp++;
				continue;
			}
			*sp++ = *hp++;
			i++;
		}
		*sp = 0;
/*
printf("%s --> %s\n", haveendstr, tmp );
*/
/*			
		strncpy(tmp,haveendstr,Xstrlen(wendstr));
*/
		haveendstr = tmp;
	}
	return(dictstrcmp(wendstr,haveendstr));
}

noaccstrcmp(char *wendstr, char *hendstr)
{
	char tmp1[BUFSIZ];
	char tmp2[BUFSIZ];
	
	strcpy(tmp1,wendstr);
	stripquantacc(tmp1);
	
	strcpy(tmp2,hendstr);
	stripquantacc(tmp2);
	
	return(strcmp(tmp1,tmp2));
}

has_quantacc(char *s)
{
	int rval = 0;
	if( has_quant(s) ) rval += 010;
	if( hasaccent(s) ) rval += 020;
	return(rval);
}

stripquantacc(char *s)
{
	stripquant(s);
	stripacc(s);
}
