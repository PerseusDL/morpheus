#include <gkstring.h>

#include "checkstring.proto.h"
static checkstring4(gk_word *);
static add_apostrvowel(char *, char *, char *);
/*
 * a lot of dirty work goes on here. this is where we look for things like apostrophes,
 * crasis, odd preverb forms (e.g. "cun" for "sun"), dialectical things like "tt" vs "ss" etc.
 */
gk_word * CreatGkword(int n);
int 	digstring1(gk_word * Gkword);
int 	stand_phonetics(gk_word * Gkword);
int 	standword(char * s);
int 	is_blank(char * s);
Dialect WantDialects = ALL_DIAL;

digstring(char *string, PrntFlags prntflags, FILE *fout)
{
	gk_word * Gkword = NULL;
	int nanals = 0;

	if( is_blank(string) ) return(0);
	Gkword = (gk_word *) CreatGkword(1 );

	set_dialect(Gkword,WantDialects);
	set_workword(Gkword,string);
	set_prntflags(Gkword,prntflags);
	standword(workword_of(Gkword));
	set_rawword(Gkword,workword_of(Gkword));
	stand_phonetics(Gkword);
	
	digstring1(Gkword);

	if( (nanals=totanal_of(Gkword)) > 0 ) {
		PrntAnalyses(Gkword,prntflags,fout);
	}
	FreeGkword( Gkword );
	return(nanals);
}


digstring1(gk_word *Gkword)
{
	if( workword_of(Gkword)[0] == '\'' ) { /* check for prodelision */
		char savework[MAXWORDSIZE];
		int n = 0;
		
		Xstrncpy(savework,workword_of(Gkword),MAXWORDSIZE);
		set_workword(Gkword,"e)");
		Xstrncat(workword_of(Gkword),savework+1,MAXWORDSIZE);
		n = digstring2(Gkword);

/*
 * grc 12/16/89
 * kludged so that it would get "e)/qanon" from "'qa/non"
 */
		if( ! n /* && ! hasaccent(savework) */) {
			char tmp[MAXWORDSIZE];
			
			strcpy(tmp,savework);
			if( hasaccent(tmp) ) stripacc(tmp);
			set_workword(Gkword,"e)/");
			Xstrncat(workword_of(Gkword),tmp+1,MAXWORDSIZE);
			n = digstring2(Gkword);
			
		}
		
		set_workword(Gkword,"a)");
		Xstrncat(workword_of(Gkword),savework+1,MAXWORDSIZE);
		n = digstring2(Gkword);

		if( ! n && ! hasaccent(savework) ) {
			set_workword(Gkword,"a)/");
			Xstrncat(workword_of(Gkword),savework+1,MAXWORDSIZE);
			n = digstring2(Gkword);
			
		}
		
		
	} else
		digstring2(Gkword);
}

digstring2(gk_word *Gkword)
{
	int rval;
	Dialect d;
/*
printf("raw [%s] work [%s]\n", rawword_of(Gkword) , workword_of(Gkword) );
*/
	rval = digstring3(Gkword);

	if( ! rval ) {
		rval=checkcrasis(Gkword);
	}

/*
printf("rval %d raw [%s] work [%s]\n", rval , rawword_of(Gkword) , workword_of(Gkword) );
*/	

	if( (d=AndDialect(dialect_of(Gkword),(Dialect)(HOMERIC|IONIC))) >= 0 ||
		! (dialect_of(Gkword) & PROSE) ) {
		Dialect olddial = dialect_of(Gkword);
		gk_string m, m2;

		/*d = dialect_of(Gkword);*/
		set_morphflags(&m, morphflags_of(Gkword));
		set_morphflags(&m2, morphflags_of(Gkword));
		add_morphflag(morphflags_of(Gkword),UNAUGMENTED);
		add_morphflag(morphflags_of(stem_gstr_of(Gkword)),UNAUGMENTED);
		if( ! (dialect_of(Gkword) & (IONIC| PROSE ) )) 
			add_morphflag(morphflags_of(Gkword),POETIC);
/*
		if( d >= 0 ) {
			set_dialect(stem_gstr_of(Gkword),d);
			set_dialect(Gkword,d);
		}
*/
		rval = digstring3(Gkword);
		if( ! rval ) {
			rval=checkcrasis(Gkword);
		}
		set_dialect(Gkword,olddial);
		set_gwmorphflags(Gkword,morphflags_of(&m));
		set_morphflags(stem_gstr_of(Gkword),morphflags_of(&m2));

	}

	return(totanal_of(Gkword));
}

#define Has_apostr(S) (*(S+Xstrlen(S)-1) == '\'')


digstring3(gk_word *Gkword)
{
	char saveword[MAXWORDSIZE];
	char workword[MAXWORDSIZE];
	char * string = workword_of(Gkword);
	int rval = 0;

	Xstrncpy(saveword,workword_of(Gkword),(int)sizeof saveword);
	if( (rval=digstring4(Gkword)) > 0 )
		return(rval);

	if(  *string == BETA_UCASE_MARKER ) {
/*
 * check to see if we failed because we 
 * have a word that is upper case
 * because it stands at the beginning of a sentence
 * or paragraph.
 */
 		beta_tolower(string);

		if( (rval=digstring4(Gkword)) > 0 ) {
			set_workword(Gkword,saveword);
			return(rval);
		}
		Xstrncpy(string,saveword,MAXWORDSIZE);
 	}

	if( Has_apostr(workword_of(Gkword)) ) {
		if( (rval=checkapostr(Gkword))) {
			set_workword(Gkword,saveword);
			return(rval);
		}
	}
	 
/*
 * try strippping a "per" off of it, as in "oi(=o/sper"
 *
 * grc 7/10/89 -- commented this out. this really belongs in the dictionary
 * rather than in the parser
 *
 * grc 7/15/89 -- put it back in for now.  i am not at all sure anymore that this
 * doesn't belong in the parser.  
 */
/*
 * grc 12/24/90
 * have added o(/sper to the dictionary and will use the dictionary for any other
 * problems that come up
 *
 * grc 5/9/92
 * have put this back in yet again -- there are just too many damn words that have
 * per attached to them for now.
 */
	if( cmpend(workword_of(Gkword),"per",workword)) {
		set_workword(Gkword,workword);
		rval = digstring3(Gkword);
		if( rval ) {
			set_workword(Gkword,saveword);
			return(rval);
		}
	}
 
	if( cmpend(workword_of(Gkword),"de",workword)) {
		set_workword(Gkword,workword);
		rval = digstring3(Gkword);
		if( rval ) {
			set_workword(Gkword,saveword);
			return(rval);
		}
	}
/*
 * grc 12/24/90
 * have likewise added o(/sge and o(/ste
 
	if( cmpend(workword_of(Gkword),"ge",workword)) {
		set_workword(Gkword,workword);
		rval = digstring3(Gkword);
		if( rval ) {
			set_workword(Gkword,saveword);
			return(rval);
		}
	}

	if( cmpend(workword_of(Gkword),"te",workword)) {
		set_workword(Gkword,workword);
		rval = digstring3(Gkword);
		if( rval ) {
			set_workword(Gkword,saveword);
			return(rval);
		}
	}
*/
	set_workword(Gkword,saveword);
	return(0);
}

static
digstring4(gk_word *Gkword)
{
	char saveword[MAXWORDSIZE];
	char wordnoacc[MAXWORDSIZE];
	char workword[MAXWORDSIZE];
	register char * a;
	char * string = workword_of(Gkword);
	int rval = 0; 

	if( (rval=checkword(Gkword)) > 0 ) {
		return(rval);
	}
	
	Xstrncpy(workword,string,MAXWORDSIZE);
	Xstrncpy(saveword,workword,MAXWORDSIZE);
	Xstrncpy(wordnoacc,workword,MAXWORDSIZE);
	stripacc(wordnoacc);
	
/*
 * look for "cun" instead of "sun"
 *
 * grc 6/26/89
 *
 * make this handle only nominals.  such a test is a blunt instrument:
 * it caused me to get a)pocu/rw as a form of a)po-su/rw.
 *
 * only use this in the case of nominals (in which preverbs have not been 
 * consistently coded in middle liddell). let the preverb routines handle this for
 * verbs.
 */
	if( has_cun(workword) ) {
		Xstrncpy(string,workword,MAXWORDSIZE);
/*
		rval=digstring4(Gkword);
*/
		rval+=checkindecl(Gkword);
		rval+=checknom(Gkword);
		Xstrncpy(string,saveword,MAXWORDSIZE);
		if( rval > 0 )
			return(rval);
	}
	Xstrncpy(workword,saveword,MAXWORDSIZE);

/*
 * look for "tt" and change it to "ss"
 */
	if( has_tt(workword) ) {
		Xstrncpy(string,workword,MAXWORDSIZE);
		rval=digstring4(Gkword);
		Xstrncpy(string,saveword,MAXWORDSIZE);
		if( rval > 0 )
			return(rval);
	}
	Xstrncpy(workword,saveword,MAXWORDSIZE);
	

/*
 * ok, try zapping a possible "nu" movable
 */
/*
 * grc 2/22/87
 * put this in greek.h at some point
 */
 /*
  * grc 10/3/87
  * this function removed to the ending tables. the ending generator has to be
  * smart enough to know which endings could take nu movables. we should not make the
  * search here (otherwise we have to do a post check to make sure that we don't
  * accept forms such as "pe/mpeten".
  */
/*
#define Is_sigmatic(X) (X =='s' || X == 'y' || X == 'c' )
	a = wordnoacc;
	while( *a ) a++; a--;
	if( a - wordnoacc > 2 ) {
		if( ( *a == 'n' ) &&
		   ( (*(a-1) == 'i' && Is_sigmatic( *(a-2))) ||
		     (*(a-1) == 'e' )))   {
			workword[ Xstrlen(workword) - 1] = 0;
			Xstrncpy(string,workword,MAXWORDSIZE);
			rval=digstring4(Gkword);
			Xstrncpy(string,saveword,MAXWORDSIZE);
			if( rval > 0 )
				return(rval);
		}
	}
*/
	return(0);
}

has_cun(char *s)
{
	while(*s) {
		if( *s == 'c' && *(s+1) == 'u' ) {
			*s = 's';
			return(1);
		}
		s++;
	}
	return(0);
}


checkapostr(gk_word *Gkword)
{
	char saveword[MAXWORDSIZE];
	gk_string TmpGstr;
	int rval = 0;
	int curval = 0;
	char * p;

	
	Xstrncpy(saveword,workword_of(Gkword),MAXWORDSIZE );
	p = workword_of(Gkword);
	while(*p) p++; p--;
	if(  *p != '\'' ) return(0);
	if( p>workword_of(Gkword) && (*(p-1) == 'q' || *(p-1) == 'x' || *(p-1) == 'f' ) ) {
	/*
	 * note that this should set a flag that indicates that the
	 * next word in the input stream *must* begin with a rough
	 * breathing.
	 */
	 	if( *(p-1) == 'q' ) {
			*(p-1) = 't';
		/*
		 * 9/7/89
		 *
		 * neoxa/raxq' comes from neoxa/rakta
		 */
		 	if(*(p-2) == 'x' ) *(p-2) = 'k';
		} else if( *(p-1) == 'x' )
			*(p-1) = 'k';
		else
			*(p-1) = 'p';
		rval += checkapostr(Gkword);
/*
		if( rval ) return(rval);
 */
		/* make sure that you don't miss forms such as "o)/rniq'" */
		Xstrncpy(workword_of(Gkword),saveword,MAXWORDSIZE);
	}

/*
 * try an 'a'
 */
 	add_apostrvowel(workword_of(Gkword),p,"a");
	curval = digstring3(Gkword);
	set_workword(Gkword,saveword);
	rval += curval;

/*
 * try an 'i'
 */

 	add_apostrvowel(workword_of(Gkword),p,"i");
	curval = digstring3(Gkword);
	set_workword(Gkword,saveword);
	rval += curval;

/*
 * try an 'o'
 */
 	add_apostrvowel(workword_of(Gkword),p,"o");
	curval = digstring3(Gkword);
	set_workword(Gkword,saveword);
	rval += curval;

/*
 * try an 'e'
 */
 	add_apostrvowel(workword_of(Gkword),p,"e");
	curval = digstring3(Gkword);
	set_workword(Gkword,saveword);
	rval += curval;

/*
 * try an 'ai'
 * grc 7/11/89 -- to analyze gene/sq', which appears in pindar
 *
 */
 	add_apostrvowel(workword_of(Gkword),p,"ai");
 	set_morphflags(&TmpGstr,morphflags_of(Gkword));
 	add_morphflag(morphflags_of(Gkword),POETIC);
	curval = digstring3(Gkword);
	set_workword(Gkword,saveword);
	rval += curval;
 	set_gwmorphflags(Gkword,morphflags_of(&TmpGstr));
 	
 	if( ! rval ) {
 		int syllno = 0;
 		int accnum = 0;
 		
 		set_workword(Gkword,saveword);
 		checkaccent(workword_of(Gkword),&syllno,&accnum);
 		if( syllno == ULTIMA && accnum != C_ERR ) {
 			stripacc(workword_of(Gkword));
 			rval = checkapostr(Gkword);
 		}
 		Xstrncpy(workword_of(Gkword),saveword,MAXWORDSIZE);
 	}
	return(rval);
}

static
add_apostrvowel(char *word, char *end, char *vow)
{
/*
 * if it has no accents (like a)ll' from a)lla/) stick one on
 */
 	Xstrncpy(end,vow,MAXWORDSIZE);
	if( naccents(word) == 0 ) {
		Xstrncat(word,"/",MAXWORDSIZE);
	}

	if( *end == 'u' || * end == 'i' || *end == 'a' )
		Xstrncat(word,"^",MAXWORDSIZE);

}

has_tt(char *s)
{
	while(*s) {
		if( *s == 't' && *(s+1) == 't' ) {
			*s = *(s+1) = 's';
			return(1);
		}
		s++;
	}
	return(0);
}

SetWantDialect(Dialect dial)
{
	WantDialects = dial;
}

AddWantDialect(Dialect dial)
{
	WantDialects |= dial;
}

ZapWantDialect(Dialect dial)
{
	WantDialects &= (~dial);
}

Dialect
GetWantDialect(void)
{
	return(WantDialects);
}

updateDialect(Dialect dial)
{
	Dialect GetWantDialect();
	Dialect curdial;
	
	curdial = GetWantDialect();
	if( dial == 0 ) {
		SetWantDialect(dial);
		return(0);
	} else if( dial & curdial ) {
		ZapWantDialect(dial);
		return(-1);
	} else {
		AddWantDialect(dial);
		return(1);
	}
}

