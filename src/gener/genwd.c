#include <gkstring.h>
#include <stdlib.h>
#include <string.h>
#include <modes.h>
#define SKIPLINE  100
static  AddWdEndings( gk_word * , gk_string * , gk_word * , int );

#define NextStem(f,stem,stemkeys) NextDictLine(f,stem,stemkeys,":")
#define NextLemma(f,lemma,lemmakeys) NextDictLine(f,lemma,lemmakeys,":le:")

gk_string * chckendings();
gk_word * GenStemForms(gk_word *, char *, int);
gk_word * GenIrregForm(gk_word *, char *, int);

Dialect AndDialect();
int CompGkForms(gk_word *gkform1, gk_word *gkform2);

gk_string BlankGstr;
gk_word TmpGkword;

GenDictEntry(Gkword,dentry)
 gk_word *Gkword;
 char * dentry;
{
	
	gk_word * gkforms;
	int formcnt;
	Stemtype stype;
	char keys[LONGSTRING*4];

	TmpGkword = * Gkword;
	
	keys[0] = 0;
	stype = stemtype_of(stem_gstr_of(&TmpGkword));
	/**(stem_gstr_of(&TmpGkword)) = BlankGstr;*/
	stemtype_of(stem_gstr_of(&TmpGkword)) = stype;
	set_morphflag(morphflags_of(stem_gstr_of(&TmpGkword)),0);
	set_morphflag(morphflags_of(&TmpGkword),0);

	SprintGkFlags(stem_gstr_of(&TmpGkword),keys,"\t",1);
	*(ends_gstr_of(&TmpGkword)) = BlankGstr;
/*printf("endstring: [%s] keys:%s\n", endstring_of(&TmpGkword), keys );*/

	gkforms = GenStemForms(&TmpGkword,keys,0);
	if( ! gkforms ) return;

	for(formcnt=0;workword_of((gkforms+formcnt))[0];formcnt++) ;

        qsort(gkforms,formcnt,sizeof * gkforms,CompGkForms);	

	stripmetachars(workword_of(gkforms));
/*	printf("workword:%s\n", workword_of(gkforms) );*/
	strcpy(dentry,workword_of(gkforms));
	FreeGkword(gkforms);
}

 GenNxtWord(f,mode,fout)
  FILE * f;
  int mode;
  FILE * fout;
{
	
	int rval, i;
	gk_word * Rvals = NULL;
	char lemmakeys[256];
	char stemkeys[256];
	gk_word * Gkword = NULL;


	stemkeys[0] = 0;
	Gkword = CreatGkword(1 );
	if( ! Gkword ) {
		fprintf(stderr,"could not allocate memory for Gkword in GenNxtWord\n");
		return;
	}

	for(;;) {
		if( NextLemma(f,lemma_of(Gkword),lemmakeys) != SKIPLINE)
			break;
	}
	

	while( (rval=NextStem(f,stem_of(Gkword),stemkeys)) > 0 )  {
		if( rval == SKIPLINE )
			goto finish;
	
		if( rval == IRREG_VERB || rval == IRREG_INDECL ) {
			Rvals = GenIrregForm(Gkword,stemkeys,mode);
			if( ! Rvals ) {
				continue;
			}
		} else {
			Rvals = GenStemForms(Gkword,stemkeys,mode);
			if( ! Rvals ) {
				continue;
			}
			fprintf(fout,"\n");
		}
/*
		PrntGkWord(Gkword,Rvals,fout);
*/
/*printf("continue? "); getchar();*/
		FreeGkword(Rvals);
		Rvals = NULL;
		set_workword(Gkword,"");
		set_stem(Gkword,"");
		set_endstring(Gkword,"");
	}
	finish:
		FreeGkword( Gkword ); 
		Gkword = NULL;
		return(rval? 1 : 0);
}

gk_word *
 GenStemForms(Gkword,keys,mode)
  gk_word * Gkword;
  char * keys;
  int mode;
{
	gk_string * stem_gstring;
	gk_string * gstring;
	gk_word *gkforms;
	gk_word tmpGkword;
	char stemkeys[LONGSTRING];
	Dialect dial;
	int nends = 0;
	int maxforms = 0;
	
	stemkeys[0] = 0;
/*
	Xstrncpy(stemkeys,keys,LONGSTRING);
*/
	strcpy(stemkeys,keys);

/*
 * ok, we want to process the keys associated with this stem, and then
 * use this information to get appropriate endings (e.g., if the stem
 * is deponent, we don't want to get any active endings ).
 */

	tmpGkword = *Gkword;
	stem_gstring = stem_gstr_of(&tmpGkword);
/*
printf("stem [%s] stemkeys [%s]\n", stem_of(Gkword), stemkeys);
*/
	if( ! ScanAsciiKeys(stemkeys,&tmpGkword,stem_gstring,(gk_string *)NULL) ) {
		fprintf(stderr,"stem [%s] lemma [%s]: Something wrong with stemkeys [%s]\n",gkstring_of(stem_gstring), lemma_of(&tmpGkword), stemkeys );
		fprintf(stderr,"stemtype:%d\n", stemtype_of(&tmpGkword) );
		return(NULL);
	}

/*
 * grc 8/4/89
 */
 	if( has_morphflag(morphflags_of(Gkword),SYLL_AUGMENT) && 
 		!  has_morphflag(morphflags_of(stem_gstring),SYLL_AUGMENT) )
 			return(NULL);
 			
	/*
	 * don't bother checking for a)n-ei/xomen if the preverb for the current stem is
	 * a)mfi/ or the like.
	 */


	if( preverb_of(Gkword)[0] && strcmp(preverb_of(Gkword) , preverb_of(&tmpGkword) ) ) {
		return(NULL);
	}
	set_stemtype(&tmpGkword,stemtype_of(stem_gstring));
	set_derivtype(&tmpGkword,derivtype_of(stem_gstring));

	if( (dial=AndDialect(dialect_of(&tmpGkword),dialect_of(stem_gstring))) < 0) {
/*
printf("failing on dialect with stem d [%o] and dial [%o]\n", dialect_of(stem_gstring), dial);
*/
		return(NULL);
	} /*else{
		set_dialect(stem_gstring,dial);
	}*/

/*
printf("endstring %s stemkeys [%s]\n", endstring_of(&tmpGkword),stemkeys );
*/
	if( !(gstring = chckendings(endstring_of(&tmpGkword),stemkeys,stem_of(&tmpGkword),
	           preverb_of(&tmpGkword),dialect_of(&tmpGkword),&nends))) {
/*
printf("gstring null with stem [%s] stemkeys [%s]  ending [%s] &tmpGkword dial %o\n",stem_of(&tmpGkword) , stemkeys,endstring_of(&tmpGkword), dialect_of(&tmpGkword));
*/
		return(NULL);
	}

	maxforms = (nends * 2) + 2;
	gkforms = CreatGkword(maxforms);
/*
if( maxforms > 12 ) {
printf("stemkeys [%s]\n", stemkeys );
printf("maxforms %d stem %s\n", maxforms, NameOfStemtype(stemtype_of(gstring)) );
}
*/
	if( ! gkforms ) {
		fprintf(stderr,"no memory for %d gkforms of %s in genwd\n", 
		maxforms, lemma_of(Gkword) );
		FreeGkString(gstring);
		gstring = NULL;
		return(NULL);
	}
	set_stemtype(&tmpGkword,stemtype_of(gstring));

	AddWdEndings(&tmpGkword,gstring,gkforms,maxforms);
	
	FreeGkString(gstring);
	gstring = NULL;
	return(gkforms);
}

gk_word *
 GenIrregForm(Gkword,keys,mode)
  gk_word * Gkword;
  char * keys;
  int mode;
{
	gk_string * gstring;
	gk_word * gkforms;
	char stemkeys[LONGSTRING];
	char * preverb;
	Dialect dial;

	Xstrncpy(stemkeys,keys,LONGSTRING);
/*
 * note that we allocate an array of at least two members long 
 * -- the calling routine expects a "null-terminated" array
 */
	gstring = (gk_string *) CreatGkString(2);
	if( ! gstring  ) {
		fprintf(stderr,"could not allocate memory for gstring  in GenIrregForm\n");
		return(NULL);
	}
	gkforms = (gk_word *) CreatGkword(4);
	if(  ! gkforms ) {
		fprintf(stderr,"could not allocate memory for  gkforms in GenIrregForm\n");
		FreeGkString(gstring);
		gstring = NULL;
		return(NULL);
	}

	if( ! ScanAsciiKeys(stemkeys,Gkword,gstring,NULL) ) {
		char errmess[LONGSTRING];
		FreeGkString(gstring);
		sprintf(errmess,"GenIrregForm Error: no stemtype seen in [%s:%s]",workword_of(Gkword),
		 stemkeys );
		ErrorMess(errmess);	
		return(NULL);
	}

	add_morphflags(stem_gstr_of(Gkword),morphflags_of(gstring));
	
	if( mode & INDECL )	{
		add_morphflag(morphflags_of(Gkword),INDECLFORM);
		add_morphflag(morphflags_of(gstring),INDECLFORM);
	}
	add_morphflag(morphflags_of(Gkword),IRREGFORM);
	add_morphflag(morphflags_of(gstring),IRREGFORM);

	if( mode & INDECL && preverb_of(Gkword)[0] ) {
/*
		fprintf(stderr,"Hey! preverb [%s] with indeclinable form [%s]!\n", preverb_of(Gkword),
			stem_of(Gkword) );
*/
		preverb = NULL;
	} else {
		preverb = preverb_of(Gkword);
	}

	if( ! stemtype_of(gstring) ) {
		printf("GenIrregForm: could not find a stemtype for [%s] with keys [%s]\n", 
			workword_of(Gkword) , keys );
		FreeGkString(gstring);
		gstring = NULL;
		FreeGkword(gkforms);
		gkforms = NULL;
		return(NULL);
	}
	set_endstring(Gkword,"");
	set_stemtype(Gkword,stemtype_of(gstring));

	if( (dial=AndDialect(dialect_of(gstring),dialect_of(Gkword))) >= 0 ) {
		if( dialect_of(gstring) ) /* if we are looking for attic forms, and a given
								   * form could be either attic or ionic, we ignore
								   * the ionic possibility.
								   */
			set_dialect( gstring, dial );
	} else {
		FreeGkString(gstring);
		gstring = NULL;
		FreeGkword(gkforms);
		gkforms = NULL;
		return(NULL);
	}

/*
	add_morphflags(gstring,morphflags_of(Gkword));
*/
	forminfo_of(Gkword) = forminfo_of(gstring);

	if( skip_augment(morphflags_of(stem_gstr_of(Gkword)))  &&  ! needs_augment(gstring)) {
		FreeGkString(gstring);
		gstring = NULL;
		FreeGkword(gkforms);
		gkforms = NULL;
		return(NULL);
	}

	BuildAWord(Gkword,gstring,gkforms);
	set_morphflag(morphflags_of(stem_gstr_of(Gkword)),0);
	zap_morphflag(morphflags_of(Gkword),INDECLFORM);
	FreeGkString(gstring);
	gstring = NULL;
	
	return(gkforms);
}

 NextDictLine(f,word,wordkeys,starts)
  FILE * f;
  char * word;
  char * wordkeys;
  char * starts;
{
	char tmp[LONGSTRING];
	register char * s;

	while(1) {
		if( ! fgets(tmp,(int)sizeof tmp,f) ) 
			return(EOF);
	
		if( is_blank(tmp) ) {
			return(SKIPLINE);
		}
		if( Is_comment(tmp) )
			continue;

		s = tmp;

		if( ! Xstrncmp(tmp,starts,Xstrlen(starts)) ) {
			char tagged[MAXWORDSIZE];

			s++;
/*
 * s now point to something like
 *	"vs:pau	w_stem active"
 */

/*
 * s now points to "w_stem active" 
 * while tagged contains "vs:pau"
 */
			nextkey(s,tagged);
			Xstrncpy(wordkeys,s,LONGSTRING);
			
			Xstrncpy(word,tagged+3,LONGSTRING);
			*(tagged+3) = 0;

			if( ! strcmp(starts,":le:") ) return(1);
			if( ! strcmp(tagged,"vb:") ) {
				return(IRREG_VERB);
			} else if( ! strcmp(tagged,"wd:") ) {
				return(IRREG_INDECL);
			}
			if( strcmp(tagged,"vs:") && strcmp(tagged,"no:") && 
				strcmp(tagged,"aj:") )
					return(SKIPLINE);

			return(LEMMA);
		}
/*
 * check for blank line 
 */
		while(isspace(*s)) *s++;
		if( ! *s ) return(0);
		
	}
}

#define MAX_FORM_VARIANTS 12
static 
 AddWdEndings(Gkword,Endings,Forms,maxforms)
  gk_word * Gkword;
  gk_string * Endings;
  gk_word * Forms;
  int maxforms;
{
	int i,j,k;
	gk_word SaveGkWord;
	Dialect d;
	int formvars;
	gk_word * CurBuf;
	gk_string CurEnd;
	
	CurBuf = CreatGkword(MAX_FORM_VARIANTS+1);
	if( ! CurBuf) {
		fprintf(stderr,"no memory for CurBuf in AddWdEndings: raww [%s]\n", rawword_of(Gkword) );
		return;
	}

	SaveGkWord = * Gkword;
	j = 0;
	for(i=0;gkstring_of((Endings+i))[0];i++) {

		CurEnd = *(Endings+i);

/* 
 * grc 4/22/95
 * we were allowing e)nhntiw/meqa as:
 * e)n,a)na/-ti/w  pres subj mp 1st pl attic epic apocope prevb_aug w_stem
 *
 * we needed to make sure augmented preverbs don't get attached to subjunctives
 * etc.
 */
	if( has_morphflag(morphflags_of(prvb_gstr_of(Gkword)),PREVB_AUGMENT)  &&  ! needs_augment(Endings+i)) {
		continue;
	}

	/*
	 * if you are hunting for unaugmented epic forms, don't bother looking at things
	 * like present indicatives or futures. only look at words that normally would
	 * take an augment..
	 */

		if( (skip_augment(morphflags_of(stem_gstr_of(Gkword))) 
		  || skip_augment(morphflags_of(Gkword))
		  || skip_augment(morphflags_of(Endings+i))) && ! needs_augment(Endings+i)) {
			continue;
		}
		
	/*
	 * grc 3/21/91
	 *
	 * this check is added so that we don't get "unaugmented" stems attached to
	 * non-augmenting forms, such as subjunctives.
	 *
	 * currently, a)kolouqh/seis is getting analyzed as a doric epic short subj, because
	 * the -eis is a short subj, but the a)kolouqhs- could be from a)_kolouqhs-
	 */
		if( mood_of(forminfo_of(stem_gstr_of(Gkword))) ) {
			if( mood_of(forminfo_of(stem_gstr_of(Gkword))) != mood_of(forminfo_of(Endings+i)))
				continue;
		}


		set_stemtype(&CurEnd,stemtype_of(Gkword) );
		set_endstring(Gkword,gkstring_of(Endings+i));
		forminfo_of (Gkword) = forminfo_of(&CurEnd);
/*
		add_morphflags(Endings+i,morphflags_of(Gkword));
*/

		if((formvars=BuildAWord(Gkword,&CurEnd,CurBuf )) ) {
			for(k=0;k<formvars;k++) {
				*(Forms+j) = *(CurBuf+k);
				j++;
			}

		}

		*Gkword = SaveGkWord;
	}
	workword_of(Forms+j)[0] = 0;
	if( j > maxforms ) {
		fprintf(stderr,"%d > %d for %s\n", j, maxforms,lemma_of(Gkword));
		exit(1);
	}
	
/*
	for(k=0;workword_of(Forms+k)[0];k++) {
		fprintf(stderr,"generated [%s] [%lo]\n", workword_of(Forms+k) ,forminfo_of(Forms+k));
	}
*/

	analysis_of(CurBuf) = NULL;
	FreeGkword(CurBuf);
	CurBuf = NULL;
}

 BuildAWord(Gkword,CurEnding,CurForms)
  gk_word * Gkword;
  gk_string * CurEnding;
  gk_word * CurForms;
{
	Dialect dial;

	*CurForms = *Gkword;
	
	*(ends_gstr_of(CurForms)) = *CurEnding;
	add_morphflags(stem_gstr_of(CurForms),morphflags_of(Gkword));

	
	if( (dial=AndDialect(dialect_of(CurEnding),dialect_of(Gkword))) < 0) {
/*
printf("failing on stem [%s] end [%s] [%o] [%o]\n", stem_of(Gkword) ,gkstring_of(CurEnding), dialect_of(CurEnding) , dialect_of(Gkword) );
*/
		return(0);
	}

	if(Is_verbform(Gkword)) {
		return( BuildAVerb(Gkword,CurEnding,CurForms) );
	} else {
		return( BuildANoun(Gkword,CurEnding,CurForms) );
	}
}

 BuildANoun(Gkword,CurEnding,CurForms)
  gk_word * Gkword;
  gk_string * CurEnding;
  gk_word * CurForms;
{
	char tmp[MAXWORDSIZE];

/*
 * don't bother accenting things like articles or adverbs
 * as these already have accents on them (they are stored as
 * indeclinables
 */
 	*(ends_gstr_of(CurForms)) = *CurEnding;
/*
	if( preverb_of(Gkword)[0] ) rstprevb(stem_of(CurForms),preverb_of(Gkword),prvb_gstr_of(Gkword));
*/
	if( Is_nounform(Gkword) || Is_adjform(Gkword) || 
			mood_of(forminfo_of(CurEnding)) == PARTICIPLE  ||
			mood_of(forminfo_of(CurEnding)) == INFINITIVE ) {

		FixPersAcc(CurEnding,
			morphflags_of(CurEnding),stem_gstr_of(CurForms),gkstring_of(CurEnding),tmp,
			forminfo_of(CurEnding),YES);
		Xstrncpy(gkstring_of(CurEnding),tmp,MAXWORDSIZE);
	} else {
		Xstrncpy(gkstring_of(CurEnding),stem_of(Gkword),MAXWORDSIZE );
	}
	if( has_morphflag(morphflags_of(stem_gstr_of(Gkword)),ENCLITIC) ) 
		stripacute(gkstring_of(CurEnding));
	set_workword(CurForms,gkstring_of(CurEnding));
/*
printf("stem: "); 	PrntAWord(stem_gstr_of(CurForms),Gkword,"",stdout);
printf("end: "); 	PrntAWord(ends_gstr_of(CurForms),Gkword,"",stdout);
printf("result [%s]\n", workword_of(CurForms) );
*/
	return(1);
}


 BuildAVerb(Gkword,CurEnding,CurForms)
  gk_word * Gkword;
  gk_string * CurEnding;
  gk_word * CurForms;
{
	char tmpstem[MAXWORDSIZE+1];
	char preverb[MAXWORDSIZE+1];
	gk_string * prvb_gstr = prvb_gstr_of(CurForms);
	char * stem = stem_of(Gkword);
	char * endstring = endstring_of(CurForms);
	int i;
	int augs = 0;
	int nforms = 0;

 	*(ends_gstr_of(CurForms)) = *CurEnding;

	Xstrncpy(tmpstem,stem,MAXWORDSIZE);
/*
 * if you have an accent on the preverb, get rid of
 * it so that you do not confuse the accentuation
 * routines. (otherwise, you get forms like "a)po/bainomen"
 * because the accentuation routine, seeing the '/' on the
 * preverb, figures that the job has been done...
 */
	if( Has_preverb(morphflags_of(stem_gstr_of(Gkword))) /* preverb_of(Gkword)[0] */ ) {
		Xstrncpy( preverb , preverb_of(Gkword) ,MAXWORDSIZE);
		stripacc(preverb);
	} else
		preverb[0] = 0;

	if( mood_of(forminfo_of(CurForms)) == PARTICIPLE || 
		mood_of(forminfo_of(CurForms)) == INFINITIVE  ) {
		/*
		 * participles never take augments, so punt this flag if it
		 * is present 
		 */
		zap_morphflag(morphflags_of(stem_gstr_of(CurForms)),SYLL_AUGMENT);
		nforms = BuildANoun(Gkword,CurEnding,CurForms);

		if( preverb[0] ) {
			for(i=0;i<nforms;i++)
				rstprevb(workword_of((CurForms+i)),preverb,prvb_gstr_of(CurForms+i));
		}

		return(nforms);
	}

	if( *endstring && *endstring != '*' ) {
  		Xstrncat(tmpstem,"-",MAXWORDSIZE);
 		Xstrncat(tmpstem,endstring,(int)sizeof tmpstem);
	}
/*
 * grc 9/3/88
 * 
 * conjstem() commented out because it does too much. When combining "a)l" and "so" (to make
 * the athematic aorist form $a)=lso& from $a(/llomai&), it truncates the "l" and produces 
 * $a)=so&.  
 * 
 * Nowadays Morpheus assumes that endings and stems are simply appended. Thus, the stem of
 * $le/leimmai" is not "leleip" but "lelei" as far as Morpheus is concerned.
 *
		conjstem(tmpstem, endstring );
 */
	set_workword(CurForms,tmpstem);
	if( *endstring && Is_enclitic(morphflags_of(stem_gstr_of(CurForms))))
		return(1);
		

	if( ! *endstring ) { /* check to see if you have a conjugated form */
			     /* if so, you don't want to augment it again 
			      * (e.g. you don't want to see h)/dwka, rather than
			      *  e)/dwka
			      */

	 	add_morphflags(stem_gstr_of(CurForms),morphflags_of(CurEnding));
	 	set_morphflag(morphflags_of(CurEnding),0);
	 	set_morphflag(morphflags_of(ends_gstr_of(CurForms)),0);
	 	set_morphflag(morphflags_of(CurForms),0);
		
		if( preverb[0]) {
			if( nsylls(workword_of(CurForms)) == 1  ) {
				
				MonoSyllVb(CurForms,forminfo_of(CurEnding),preverb);
					stripstemsep(workword_of(CurForms));
		} else {
				if( has_morphflag(morphflags_of(prvb_gstr_of(CurForms)),PREVB_AUGMENT) )
					add_morphflag(morphflags_of(stem_gstr_of(CurForms)),PREVB_AUGMENT);
				rstprevb(workword_of(CurForms),preverb,stem_gstr_of(CurForms));
				zap_morphflag(morphflags_of(stem_gstr_of(CurForms)),PREVB_AUGMENT);
/*
				check_double_augment(CurForms);
 */
			}
		}
	/*
	 * don't accent enclitics unless they have preverbs
	 */
	 	
		if( ! Is_enclitic(morphflags_of(stem_gstr_of(CurForms))) || 
			(Is_enclitic(morphflags_of(stem_gstr_of(CurForms))) && preverb[0]) ){ 
			gk_string TmpGstr;
			
/*
			set_morphflags(morphflags_of(&TmpGstr),morphflags_of(ends_gstr_of(CurForms)));
*/
			set_morphflag(morphflags_of(&TmpGstr),0);
			if( has_morphflag(morphflags_of(stem_gstr_of(CurForms)) ,NO_CIRCUMFLEX))
				add_morphflag(morphflags_of(ends_gstr_of(CurForms)),NO_CIRCUMFLEX);
			add_morphflags(&TmpGstr,morphflags_of(stem_gstr_of(CurForms)));
			FixRecAcc(CurForms,morphflags_of(&TmpGstr),workword_of(CurForms));
			stripstemsep(workword_of(CurForms));
		} else {

			stripacc(workword_of(CurForms));
		}

/*
 * modified 6/5/88
 * morphflags_of(Gkword) does not contain the relevant flag (NO_AUGMENT)
 * 
 	 else if( (augs=add_augment(CurForms,morphflags_of(stem_gstr_of(Gkword)))) ||
 */
	} else if( (augs=add_augment(CurForms,morphflags_of(stem_gstr_of(CurForms)),MAX_FORM_VARIANTS)) ||
	 (Is_vowel(workword_of(CurForms)[0]) && 
	 (tense_of(forminfo_of(CurForms)) == PLUPERF || 
/*
 * grc 3/20/91
 *
 * added FUTPERF
 */
	  tense_of(forminfo_of(CurForms)) == FUTPERF || 
	 		tense_of(forminfo_of(CurForms)) == PERFECT))  ) {
	 	 if( ! augs ) augs = 1; /* if you have a perfect form, augs will be 0 */
		 for(i=0;i<augs;i++) {

		 /*
		  * grc 6/5/88
		  
		  * note that the accent never precedes the augment *unless* you have a double
		  * augment. thus, you get 
		  *   
		  *   a)mpe/sxon
		  *
		  * but also
		  *
		  *   h)/mpesxon
		  */

			if( has_prevb_augment(morphflags_of(prvb_gstr_of(CurForms+i))) ) {
				rstprevb(workword_of(CurForms+i),preverb,prvb_gstr_of(CurForms+i));
/*
				check_double_augment(CurForms+i);
*/
				FixRecAcc(CurForms+i,morphflags_of(ends_gstr_of(CurForms+i)),workword_of(CurForms+i));
				stripstemsep(workword_of(CurForms+i));
			} else {

				FixRecAcc(CurForms+i,morphflags_of(ends_gstr_of(CurForms+i)),workword_of(CurForms+i));

				stripstemsep(workword_of(CurForms));
/*
 * note this check for the perfect allows us to generate e)ph=rtai rather than e)/phrtai
 */

				if( preverb[0] ) {
					rstprevb(workword_of(CurForms+i),preverb,prvb_gstr_of(CurForms+i));
				}
			}

		}
		return(augs);
	} else if( nsylls(workword_of(CurForms)) == 1 && preverb[0] ) {
		MonoSyllVb(CurForms,forminfo_of(CurForms),preverb);
	} else {
		if( preverb[0] ) {
			rstprevb(workword_of(CurForms),preverb,prvb_gstr_of(CurForms));
		}
/*
 grc 7/24/95
 
 this was not accenting forms such as fh=, because the 
 ending (for some reason) had the accent optional flag set...
		FixRecAcc(CurForms,morphflags_of(ends_gstr_of(CurForms)),workword_of(CurForms));
*/
		FixRecAcc(CurForms,morphflags_of(stem_gstr_of(CurForms)),workword_of(CurForms));
		stripstemsep(workword_of(CurForms));

	}
	stripstemsep(workword_of(CurForms));

/*	stripmetachars(gkstring_of(CurForms));*/
	return(1);
}


MonoSyllVb(CurForms,winfo,preverb)
gk_word * CurForms;
word_form winfo;
char * preverb;
{
	/*
	 * Smyth 426 
	 *
	 *  b) sune/kdos, sugka/qes not su/nekdos, su/gkaqes, e)pi/qes, not e)/piqes
 	 *  c) prodou=, e)nqou=, but kata/qou
	 */
		if( mood_of( winfo ) == IMPERATIVE  && 
			tense_of( (winfo ) ) == AORIST &&
			(voice_of( (winfo) ) & MIDDLE) &&
			(nsylls(preverb) == 1 || Is_vowel(workword_of(CurForms)[0]) )) {
			/*
			 * this makes sure that "pro" + "qou" --> "proqou="
			 */
				FixRecAcc(CurForms,morphflags_of(ends_gstr_of(CurForms)),workword_of(CurForms));
				rstprevb(workword_of(CurForms),preverb,prvb_gstr_of(CurForms));
		}
		/*
		 * otherwise, the accent goes on the last syllable of
		 * the preverb, which will be the penult of the overall
		 * verb form.
		 */
		else { 
			rstprevb(workword_of(CurForms),preverb,prvb_gstr_of(CurForms));
			add_morphflag(morphflags_of(ends_gstr_of(CurForms)),STEM_ACC);
			FixRecAcc(CurForms,morphflags_of(ends_gstr_of(CurForms)),workword_of(CurForms));
		}
}
