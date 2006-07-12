#include <gkstring.h>
#include "checkstring.proto.h"
static checkstring4(gk_word *);
static add_apostrvowel(char *, char *, char *);
/*
 * a lot of dirty work goes on here. this is where we look for things like apostrophes,
 * crasis, odd preverb forms (e.g. "cun" for "sun"), dialectical things like "tt" vs "ss" etc.
 */
gk_word * CreatGkword(int n);
int 	checkstring1(gk_word * Gkword);
int 	stand_phonetics(gk_word * Gkword);
int 	standword(char * s);
int 	is_blank(char * s);
Dialect WantDialects = ALL_DIAL;

gk_word BlankWord, CheckWord;

int
teststring(char *string)
{
	return(checkstring(string,(PrntFlags)0,stdout));
}

checkstring(char *string, PrntFlags prntflags, FILE *fout)
{
	gk_word * Gkword = NULL;
	FILE * fcurout = fout;
	int nanals = 0;
	int nlems = 0;

	if( is_blank(string) ) return(0);
	if( strlen(string) >= MAXWORDSIZE ) return(0);

	Gkword = (gk_word *) CreatGkword(1 );

	set_dialect(Gkword,WantDialects);
	set_workword(Gkword,string);
	set_prntflags(Gkword,prntflags);
	set_rawword(Gkword,workword_of(Gkword));
	if( cur_lang() != ITALIAN ) standword(workword_of(Gkword));
	stand_phonetics(Gkword);
	
	checkstring1(Gkword);

	if( prntflags & LEMCOUNT ) {
		nlems = cntlems(Gkword);
		FreeGkword( Gkword );
		return(nlems);
	}

	if( prntflags && (nanals=totanal_of(Gkword)) > 0 ) {
		PrntAnalyses(Gkword,prntflags,fcurout);
	}
	FreeGkword( Gkword );
	return(nanals);
}


cntlems(gk_word *Gkword ) 
{
	int i;
	int cnt = 0;
	gk_analysis * Anal;
	char prevlem[BUFSIZ];

	prevlem[0] = 0;
	
	for(i=0;i<totanal_of(Gkword);i++) {
		Anal = analysis_of(Gkword)+i;
		if( strchr(lemma_of(Anal),'-') ) continue;
		if( strcmp(prevlem,lemma_of(Anal))) {
			cnt++;
		}
		strcpy(prevlem,lemma_of(Anal));
	}
	return(cnt);
}

is_article(gk_word * Gkword)
{
	int i;
	gk_analysis * curanal = analysis_of(Gkword);

	for(i=0;i<totanal_of(Gkword);i++) {
		if( !strcmp("article", NameOfStemtype(stemtype_of(curanal+i))))
			return(1);
	}
	return(0);
}

end_phrase(gk_word * checkw,gk_word * Gkword)
{
}
checkstring1(gk_word *Gkword)
{

	if( workword_of(Gkword)[0] == '\'' ) { /* check for prodelision */
		char savework[MAXWORDSIZE];
		int n = 0;
		
		Xstrncpy(savework,workword_of(Gkword),MAXWORDSIZE);
		set_workword(Gkword,"e)");
		Xstrncat(workword_of(Gkword),savework+1,MAXWORDSIZE);
		n = checkstring2(Gkword);

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
			n = checkstring2(Gkword);
			
		}
		
		set_workword(Gkword,"a)");
		Xstrncat(workword_of(Gkword),savework+1,MAXWORDSIZE);
		n = checkstring2(Gkword);

		if( ! n && ! hasaccent(savework) ) {
			set_workword(Gkword,"a)/");
			Xstrncat(workword_of(Gkword),savework+1,MAXWORDSIZE);
			n = checkstring2(Gkword);
			
		}
		
		
	} else
		checkstring2(Gkword);
}

checkstring2(gk_word *Gkword)
{
	int rval;
	Dialect d;
/*
printf("raw [%s] work [%s]\n", rawword_of(Gkword) , workword_of(Gkword) );
*/
	rval = checkstring3(Gkword);

	if( ! rval && ! totanal_of(Gkword) ) {
		rval=checkcrasis(Gkword);
	}

/*
printf("rval %d raw [%s] work [%s]\n", rval , rawword_of(Gkword) , workword_of(Gkword) );
*/

	if( cur_lang() == LATIN )  return(totanal_of(Gkword));

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
			add_dialect(Gkword,(IONIC|EPIC));
/* grc 7/27/95
 * a)mei/beto in Hdt gets labelled as poetic (!).
			add_morphflag(morphflags_of(Gkword),POETIC);
*/
/*
		if( d >= 0 ) {
			set_dialect(stem_gstr_of(Gkword),d);
			set_dialect(Gkword,d);
		}
*/
		set_dialect(Gkword,(dialect_of(Gkword)|IONIC|EPIC));
		rval = checkstring3(Gkword);
		if( ! rval && ! totanal_of(Gkword) ) {
			rval=checkcrasis(Gkword);
		}
		set_dialect(Gkword,olddial);
		set_gwmorphflags(Gkword,morphflags_of(&m));
		set_morphflags(stem_gstr_of(Gkword),morphflags_of(&m2));
/*
 * grc 8/4/95
 * ah! but how do we deal now with unaugmented poetic forms that are in 
 * doric? by setting the dialect for EPIC|IONIC, we weed out Doric/Aeolic
 * endings.
 *
 * for now, let's see if we came up empty and then run the sucker again if
 * we did.
 */
		if(cur_lang() != LATIN && !rval && ( ! (dialect_of(Gkword) & (IONIC| PROSE ) ))) { 
			add_morphflag(morphflags_of(Gkword),POETIC);

			add_morphflag(morphflags_of(Gkword),UNAUGMENTED);
			add_morphflag(morphflags_of(stem_gstr_of(Gkword)),UNAUGMENTED);
			rval = checkstring3(Gkword);
			if( ! rval && ! totanal_of(Gkword) ) {
				rval=checkcrasis(Gkword);
			}
			set_dialect(Gkword,olddial);
			set_gwmorphflags(Gkword,morphflags_of(&m));
			set_morphflags(stem_gstr_of(Gkword),morphflags_of(&m2));
		}

	}

	return(totanal_of(Gkword));
}

#define Has_apostr(S) (*(S+Xstrlen(S)-1) == '\'')

/* 
   DAS 3 Dec 2001
   These enclitic suffixes should really only work with 
   certain word classes.
   I just can't seem to stop the analyses from showing up.
*/

typedef struct {
  char enclitic[MAXWORDSIZE];
  Stemtype stemtype;
} enclitic_word;

enclitic_word GreekSuff[] = {
  "per", NOUNSTEM|ADJSTEM,
  "", 0				/* sentinel */
};

enclitic_word LatinSuff[] = {
  "que", 0,
  "cumque", 0,
  "cunque", 0,
  "ne", 0,
  "ve", 0,
  "ue", 0,
  "libet", 0,
  "vis", 0, /* quantusvis */
  "piam", 0, /* quempiam */
  "dem", 0,
  "met", PRONOUN|PERS_PRON,
  "", 0				/* sentinel */
};

/* these should only work with verbs, excluding participles */
enclitic_word ItalianSuff[] = {
  "glie", PPARTMASK,
  "gli", PPARTMASK,		/* needs to be before "li" */
  "mi", PPARTMASK,
  "me", PPARTMASK,
  "ci", PPARTMASK,
  "ce", PPARTMASK,
  "ti", PPARTMASK,
  "te", PPARTMASK,
  "vi", PPARTMASK,
  "ve", PPARTMASK,
  "lo", PPARTMASK,
  "li", PPARTMASK,
  "la", PPARTMASK,
  "le", PPARTMASK,
  "loro", PPARTMASK,
  "ne", PPARTMASK,
  "si", PPARTMASK,
  "se", PPARTMASK,
  "", 0				/* sentintel */
};


checkstring3(gk_word *Gkword)
{
  char saveword[MAXWORDSIZE];
  char workword[MAXWORDSIZE];
  char * string = workword_of(Gkword);
  int rval = 0;
  int workval = 0;
  gk_analysis *oldanal, *newanal;
  int totanal, acount;
  int idx;

  enclitic_word *EnclitArr;
  
  switch (cur_lang()) {
    
  case LATIN:
    EnclitArr = LatinSuff;
    break;
    
  case ITALIAN:
    EnclitArr = ItalianSuff;
    break;
    
  default:
    EnclitArr = GreekSuff;
  }

  Xstrncpy(saveword,workword_of(Gkword),(int)sizeof saveword);
  /*
    if( (rval=checkstring4(Gkword)) > 0 && (prntflags_of(Gkword)&STRICT_CASE) ) 
    return(rval);
  */
  rval=checkstring4(Gkword);


  if(  (isupper(*string) || *string == BETA_UCASE_MARKER) && !(prntflags_of(Gkword)&STRICT_CASE) ) {
    /*
     * check to see if we failed because we 
     * have a word that is upper case
     * because it stands at the beginning of a sentence
     * or paragraph.
     *
     * In Perseus, the only upper case words should be proper nouns -- so you want to
     * be able to set STRICT_CASE
     * grc -- 8/14/93
     */
    if( cur_lang() == LATIN || cur_lang() == ITALIAN ) {
      *string = tolower(*string);
      /*
       * 12/18/97 grc
       * Vbi --> ubi
       * Vt --> ut
       * Vtinam --> utinam etc.
       */

      if(*string == 'v' && isalpha(*(string+1)) /* &&
	* 
	 * 07/12/2006 grc
	 * loosen this up for "vacuus/uacuus"
	 *
	 ! strchr("aeiou",*(string+1))*/ ) {
	*string = 'u';
      }
    } else
      beta_tolower(string);

    if( (rval=checkstring4(Gkword)) > 0 ) {
      set_workword(Gkword,saveword);
      return(rval);
    }

/* If it's all capitals, try all lowercase, then try all except the first letter lowercase */
    if (cur_lang() != GREEK)
    {
	for (idx = 0;  string[idx] != 0;  idx ++)
	{
	    string[idx] = tolower(string[idx]);
	    if (string[idx] == 'v' && strchr("aeiou", string[idx+1]) == 0)
	      string[idx] = 'u';
	}
	if ((rval = checkstring4(Gkword)) > 0 )
	{
	  set_workword(Gkword,saveword);
	  return(rval);
        }
	*string = toupper(*string);
	if ((rval = checkstring4(Gkword)) > 0 )
	{
	  set_workword(Gkword,saveword);
	  return(rval);
        }
    }
    Xstrncpy(string,saveword,MAXWORDSIZE);
  }

  if( Has_apostr(workword_of(Gkword)) ) {
    if( (rval+=checkapostr(Gkword))) {
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

  while ( !totanal_of(Gkword) && (*EnclitArr->enclitic != '\0') ) {
    if ( cmpend(workword_of(Gkword), EnclitArr->enclitic, workword) ) {
      set_workword(Gkword, workword);
      rval += checkstring3(Gkword);

      /* If we need to check for application to a valid stemtype, */
      /* shift the analysis array down. */
      if (EnclitArr->stemtype) {
	oldanal = analysis_of(Gkword);
	totanal = 0;

	newanal = oldanal;

	for (acount = 0; acount < totanal_of(Gkword); acount++, oldanal++) {
	  if ( (stemtype_of(oldanal)) & EnclitArr->stemtype ) {
	    *newanal++ = *oldanal;
	    totanal++;
	  }
	}

	set_totanal(Gkword, totanal);
      }

      if ( rval ) {
	set_workword(Gkword, saveword);
	return rval;
      }
	set_workword(Gkword, saveword);
    }
    EnclitArr++;
  }

  /*
   * 12/8/97 
   */

/* Latin prodelision:  this may be too simplistic */
  if (cur_lang() == LATIN)
  {
    if (cmpend(workword_of(Gkword),"ast",workword) ||
       cmpend(workword_of(Gkword),"est",workword) ||
       cmpend(workword_of(Gkword),"umst",workword) ||
       cmpend(workword_of(Gkword),"amst",workword) ||
       cmpend(workword_of(Gkword),"emst",workword) ||
       cmpend(workword_of(Gkword),"omst",workword))
    {
      strcpy(workword,workword_of(Gkword));
      workword[strlen(workword)-2] = 0;
      set_workword(Gkword,workword);
      rval = checkstring3(Gkword);
      if (rval)
      {
        set_workword(Gkword,saveword);
        return(rval);
      }
    }

/* ...us + est written as ...ust */
    if (cmpend(workword_of(Gkword), "ust", workword))
    {
      strcpy(workword, workword_of(Gkword)); 
      workword[strlen(workword) - 1] = 0;
      set_workword(Gkword,workword);
      rval = checkstring3(Gkword);
      if (rval)
      {
        set_workword(Gkword,saveword);
        return(rval);
      }
    }

/* ...ist could be from either i+est (usual) or is+est (3rd decl genitives esp),
   and ...ost could be from os+est (old nominative) or o+st */
    if (cmpend(workword_of(Gkword), "ist", workword) ||
	cmpend(workword_of(Gkword), "ost", workword))
    {
      strcpy(workword, workword_of(Gkword));
      workword[strlen(workword) - 1] = 0;	/* try -is first */
      set_workword(Gkword,workword);
      workval = checkstring3(Gkword);
      if (workval)
      {
	rval += workval;
      }
      workword[strlen(workword) - 1] = 0;	/* now try -i */
      set_workword(Gkword,workword);
      workval = checkstring3(Gkword);
      if (workval)
      {
	rval += workval;
      }
      if (rval)
      {
        set_workword(Gkword, saveword);
	return(rval);
      }
    }

/* now as for final n, this could be tacked on or could be hiding an s,
   but not if there is an analysis that includes that n  */
    if (! totanal_of(Gkword))
    {
      if (cmpend(workword_of(Gkword), "n", workword))
      {
        strcpy(workword, workword_of(Gkword));
        workword[strlen(workword) - 1] = 's';	/* ...s-ne -> ...n */
        set_workword(Gkword, workword);
        workval = checkstring3(Gkword);
        if (workval)
        {
	  rval += workval;
        }
        workword[strlen(workword) - 1] = 0;	/* ...Vne -> ...Vn */
        set_workword(Gkword,workword);
        workval = checkstring3(Gkword);
        if (workval)
        {
	  rval += workval;
        }
        if (rval)
        {
          set_workword(Gkword, saveword);
	  return(rval);
        }
      }
    }
  }


/* why is this still here?  not obvious */
/*
  if( cur_lang() == LATIN && cmpend(workword_of(Gkword),"ne",workword)) {
    set_workword(Gkword,workword);
    rval = checkstring3(Gkword);
    if( rval ) {
      set_workword(Gkword,saveword);
      return(rval);
    }
  }
*/


  /* grc 8/26/93
   * am going to try to add o(/de at last to clean this up
   if( cmpend(workword_of(Gkword),"de",workword)) {
   set_workword(Gkword,workword);
   rval = checkstring3(Gkword);
   if( rval ) {
   set_workword(Gkword,saveword);
   return(rval);
   }
   }
  */
  /*
   * grc 12/24/90
   * have likewise added o(/sge and o(/ste
 
   if( cmpend(workword_of(Gkword),"ge",workword)) {
   set_workword(Gkword,workword);
   rval = checkstring3(Gkword);
   if( rval ) {
   set_workword(Gkword,saveword);
   return(rval);
   }
   }

   if( cmpend(workword_of(Gkword),"te",workword)) {
   set_workword(Gkword,workword);
   rval = checkstring3(Gkword);
   if( rval ) {
   set_workword(Gkword,saveword);
   return(rval);
   }
   }
  */

  /*
   * uenio and venio
   *
   * grc 12/12/97
   *
   */
  if( cur_lang() == LATIN ) {
    char * a = workword;
    strcpy(workword,saveword);
    if( u2v(workword) ) {
      set_workword(Gkword,workword);
      rval = checkstring3(Gkword);
      if( rval ) {
	set_workword(Gkword,saveword);
	return(rval);
      }
    }
    strcpy(workword,saveword);
  }
  /* If we're out of ideas in Italian, turn all u's to v's. */
  else if ( (cur_lang() == ITALIAN) && !totanal_of(Gkword)) {
    char *a;

    strcpy(workword,saveword);

    for (a = workword, acount = 0; *a != '\0'; a++) {
      if (*a == 'U') {
	*a = 'V';
	acount++;
      }
      else if (*a == 'u') {
	*a = 'v';
	acount++;
      }
    }

    if (acount) {
      set_workword(Gkword,workword);
      rval += checkstring3(Gkword);
      if( rval ) {
	set_workword(Gkword,saveword);
	return(rval);
      }      
    }

    strcpy(workword,saveword);
  }

  /*
   * Lewis and Short stores "jubeo" rather than "iubeo".
   *
   * grc 1/28/97
   *
   * grc 2/7/97
   *
   * also, deal with sub-iectus --> sub-jectus, i.e., 'i'-'j' in middle of word

   */
  if( cur_lang() == LATIN ) {
    char * a = workword;
    strcpy(workword,saveword);

    if( *a == 'I' ) {
      *a = 'J';
      set_workword(Gkword,workword);
      rval = checkstring3(Gkword);
      if( rval ) {
	set_workword(Gkword,saveword);
	return(rval);
      }
    }

    while(*a) {
      /*
       * don't look for "cupjo"
       */
      if( *a == 'i' && *(a+2) && strchr("aeiou",*(a+1)) ) {
	*a = 'j';

	set_workword(Gkword,workword);
	rval = checkstring3(Gkword);
	if( rval ) {
	  set_workword(Gkword,saveword);
	  return(rval);
	}
	else
	{
	  *a = 'i';
	}
      }
      a++;
    }
  }

/* Latin exsT as alternate spelling for exT, T an unvoiced stop;
   our dictionary has the exsT forms, so if we find one without,
   try putting in an 's' */
  if (cur_lang() == LATIN)
  {
    if (strncmp(workword_of(Gkword), "ex", 2) == 0)
    {
      char* p_word = NULL;
      char* p_tail = NULL;
      char* p_start = NULL;
      strcpy(workword, workword_of(Gkword));
      p_word = workword;
      p_word += 2;
      switch (*p_word)
      {
	case 'c': case 'p': case 't':
	  p_start = p_word;
	  p_tail = p_word + 1;
	  memmove(p_tail, p_word, strlen(p_word));
	  *p_start = 's';
	  set_workword(Gkword, workword);
	  rval = checkstring3(Gkword);
	  if (rval)
	  {
	    set_workword(Gkword, saveword);
	    return(rval);
	  }
        default:
	  break;
      }
    }
  }

  set_workword(Gkword,saveword);
  return(rval);
}

static
checkstring4(gk_word *Gkword)
{
	char saveword[MAXWORDSIZE];
	char wordnoacc[MAXWORDSIZE];
	char workword[MAXWORDSIZE];
	register char * a;
	char * string = workword_of(Gkword);
	int rval = 0; 

	rval=checkword(Gkword);

	if( rval > 0 ) {
		return(rval);
	}
	
	Xstrncpy(workword,string,MAXWORDSIZE);
	Xstrncpy(saveword,workword,MAXWORDSIZE);
	Xstrncpy(wordnoacc,workword,MAXWORDSIZE);
	stripacc(wordnoacc);

/* A handful of Greek orthographic variations */
	if (cur_lang() == GREEK)
	{
	
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
		rval=checkstring4(Gkword);
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
		rval=checkstring4(Gkword);
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
			rval=checkstring4(Gkword);
			Xstrncpy(string,saveword,MAXWORDSIZE);
			if( rval > 0 )
				return(rval);
		}
	  }
*/

	}

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
	int	num_sylls = 0;
	
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

/* Monosyllables don't drop their last vowel unless it's epsilon (Smyth 70).  
   Note, though, that the apparent number of syllables will be one less than 
   it should be, if there really is a vowel missing.  For example, a)ll' will 
   appear to be one syllable -- it's an elided disyllable.  But d' will appear 
   to have no syllables at all -- it is therefore an elided monosyllable and
   must be de.  */
/*
 * try an 'a'
 */
	num_sylls = nsylls(workword_of(Gkword));
	if (num_sylls >= 1)
	{
 		add_apostrvowel(workword_of(Gkword),p,"a");
		curval = checkstring3(Gkword);
		set_workword(Gkword,saveword);
		rval += curval;
	}

/*
 * try an 'i'
 */

	if (num_sylls >= 1)
	{
 		add_apostrvowel(workword_of(Gkword),p,"i");
		curval = checkstring3(Gkword);
		set_workword(Gkword,saveword);
		rval += curval;
	}

/*
 * try an 'o'
 */
	if (num_sylls >= 1)
	{
 		add_apostrvowel(workword_of(Gkword),p,"o");
		curval = checkstring3(Gkword);
		set_workword(Gkword,saveword);
		rval += curval;
	}

/*
 * try an 'e' -- even if it's a monosyllable
 */
 	add_apostrvowel(workword_of(Gkword),p,"e");
	curval = checkstring3(Gkword);
	set_workword(Gkword,saveword);
	rval += curval;

/*
 * try an 'ai'
 * grc 7/11/89 -- to analyze gene/sq', which appears in pindar
 *
 */
	if (num_sylls >= 1)
	{
 		add_apostrvowel(workword_of(Gkword),p,"ai");
 		set_morphflags(&TmpGstr,morphflags_of(Gkword));
 		add_morphflag(morphflags_of(Gkword),POETIC);
		curval = checkstring3(Gkword);
		set_workword(Gkword,saveword);
		rval += curval;
 		set_gwmorphflags(Gkword,morphflags_of(&TmpGstr));
	}
 	
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

setepic()
{

AddWantDialect((Dialect )( EPIC));	
}	

setatticprose()
{
SetWantDialect((Dialect )( ATTIC|PROSE));	
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

#define LatVow(X) (strchr("aeiouAEIOU",X))

u2v(char *s) {
	int nchanges = 0;
	char half1[BUFSIZ], *t;

	half1[0] = 0;
	t = half1;
	
	if( (*s == 'U' || *s =='u' ) && LatVow(*(s+1)) ) {
		if(*s=='U') *s='V';	
		if(*s=='u') *s='v';	
		nchanges++;
	}
	*t++ = *s++;
	*t = 0;
	
	while(*s) {

		if(LatVow(*(s-1))&&LatVow(*(s+1))&&*s=='u') {
			*s = 'v';
			nchanges++;
		}
		
		if( is_rawpreverb(half1) && *s == 'u' && LatVow(*(s+1)) ) {
			*s = 'v';
			nchanges++;
		}

		if( *s=='u' && chckend(s+1) && LatVow(*(s+1)) ) {
			*s = 'v';
			nchanges++;
		}

		*t++ = *s++;
		*t = 0;
	}

	return(nchanges);
}
