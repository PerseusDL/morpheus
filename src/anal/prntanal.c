#include <gkstring.h>
static char * pbuf = NULL;
#define NEWLINE "\r"

#include "prntanal.proto.h"

static char prevlemma[MAXWORDSIZE];
static char prevword[MAXWORDSIZE];
static char prevstem[MAXWORDSIZE];
static int curan = 0;

PrntAnalyses(gk_word *Gkword, PrntFlags prntflags, FILE *fout)
{
  int i, nanals;
  gk_analysis * Anal;
  char tmp[LONGSTRING];
	
  if( ! pbuf ) {
    pbuf = (char *)calloc((size_t) MAXANALYSES * 128 , (size_t)sizeof * pbuf );
  }
  *pbuf = 0;
  nanals = totanal_of(Gkword);
  SortAnals(analysis_of(Gkword),nanals);

  if(  prntflags & SHOW_LEMMA ) {
    DumpLemmaInfo(Gkword,prntflags,fout);
    return(nanals);
  }

  if( prntflags & (DBASEFORMAT|SHOW_FULL_INFO|LEXICON_OUTPUT|PARSE_FORMAT|PERSEUS_FORMAT|ENDING_INDEX) ) {
    dump_all_anals(Gkword,prntflags,fout);
    return(nanals);
  }

	

  if( ! (prntflags & SHOW_LEMMA )  ) {
    sprintf(tmp,"$%s&  %s%s", rawword_of(Gkword) ,
	    nanals == 1 ? "is" : "could be" , NEWLINE );
    if( prntflags & KEEP_BETA ) 
      strcat(pbuf,tmp);
    else
      beta2smarta(tmp,pbuf);
  }
	
  prevlemma[0] = 0;
  Xstrncpy(prevword,rawword_of(Gkword),MAXWORDSIZE );
  Xstrncpy(prevstem,stem_of(Gkword),MAXWORDSIZE );
	
  for(i=0,curan=0;i<nanals;i++) {
    Anal = analysis_of(Gkword)+i;
    PrntOneAnalysis(Anal,prntflags,fout);
    Xstrncpy(prevlemma,lemma_of(Anal),MAXWORDSIZE);
  }
	
  if(i ) {
    /*		if(! (prntflags_of(Gkword) & BUFFER_ANALS))
		putchar( '\n' );
		else*/
    if( prntflags & SHOW_LEMMA ) 
      Xstrncat(pbuf,"\n",MAXANALYSES * 128);
    else
      Xstrncat(pbuf,"\r",MAXANALYSES * 128);
  }
  /*	puts(pbuf);*/
}

char *
anal_buf(void)
{
  return(pbuf);
}

GoodAnals(Gkword,lemmflag)
gk_word * Gkword;
int lemmflag;
{
  char curlem[MAXWORDSIZE];
  gk_analysis * Anal;
  int goodanals = 0;
  int difflems = 0;
  int i;
	
  curlem[0] = 0;

  /*
   * grc 6/11/94
   *
   * option to filter out those compounds that are not in a known dictionary --
   * this gets rid of lots of weird analyses
   */
  for(i=0;i<totanal_of(Gkword);i++) {
    Anal = analysis_of(Gkword)+i;
    if( strcmp(curlem,lemma_of(Anal) ) ) {
      difflems ++;
      strcpy(curlem,lemma_of(Anal));
    }
    if( (strchr(lemma_of(Anal),'-') == NULL ) ) {
      goodanals++;
    }
  }
  return(lemmflag? difflems : goodanals );
}

DumpLemmaInfo(gk_word *Gkword, PrntFlags prntflags, FILE *f)
{
  int i = 0;
  gk_analysis * Anal;
  int goodanals = 0;
  int difflems = 0;
  char curlem[MAXWORDSIZE];
	
  curlem[0] = 0;

  goodanals = GoodAnals(Gkword,0);
  difflems =  GoodAnals(Gkword,1);
	
	
  if(! goodanals ) goodanals = totanal_of(Gkword);

  curlem[0] = 0;
  fprintf(f,"form:%s\n", rawword_of(Gkword));
  for(i=0;i<totanal_of(Gkword);i++) {
    Anal = analysis_of(Gkword)+i;

    if( strcmp(curlem,lemma_of(Anal) ) ) {
      if( (strchr(lemma_of(Anal),'-') == NULL ) || (goodanals == totanal_of(Gkword)) ) {
	fprintf(f,"%s\n",  lemma_of(Anal) );
      }
      strcpy(curlem,lemma_of(Anal));
    }
  }
}

PrntOneAnalysis(gk_analysis *Gkanal, PrntFlags prntflags, FILE *f)
{
  PrntFlags showlemma;
  gk_string * TmpGstr;
  char tmp[LONGSTRING];
  char wtmp[LONGSTRING];
  char prntlem[MAXWORDSIZE];
  register char * s;
  int funnyacc = 0;
		

  TmpGstr = (gk_string *)CreatGkString(1);
  tmp[0] = 0;
  curan++;

  Xstrncpy(prntlem,lemma_of(Gkanal),MAXWORDSIZE);
  /*
    if( preverb_of(Gkanal)[0] ) 
    funnyacc = build_lemma(prntlem,preverb_of(Gkanal));
    */				

  if( prntflags & SHOW_LEMMA ) {
    if( strcmp(lemma_of(Gkanal),prevlemma)) {
      if( preverb_of(Gkanal)[0] )
	sprintf(wtmp,"%s\t%s-%s %d\t", rawword_of(Gkanal), preverb_of(Gkanal) , lemma_of(Gkanal) , curan);
      else
	sprintf(wtmp,"%s\t%s %d\t", rawword_of(Gkanal),  lemma_of(Gkanal) ,curan );
      Xstrncat(pbuf,wtmp,MAXANALYSES * 128);
      curan = 0;
      strcpy(wtmp,"\n");
    }
    goto finish;
  }
	
  if( strcmp(lemma_of(Gkanal),prevlemma)) {
				
    sprintf(wtmp,"   &from$  %s", prntlem );
    Xstrncat(tmp,wtmp,LONGSTRING);
    Xstrncpy(prevlemma,lemma_of(Gkanal),MAXWORDSIZE);
	

    if( preverb_of(Gkanal)[0] /* && funnyacc */) {
      char tmp2[128];
		
      sprintf(tmp2," [$%s&+$%s&]", preverb_of(Gkanal) , lemma_of(Gkanal) );
      Xstrncat(tmp,tmp2,LONGSTRING);
    }
    Xstrncat(tmp,NEWLINE,LONGSTRING);
  }
	
	
  if( strcmp(workword_of(Gkanal),prevword ) ) {	
    char tmp1[128];
		
    Xstrncpy(	wtmp,"      ",MAXWORDSIZE);
    if( crasis_of(Gkanal)[0] ) {
		
      sprintf(tmp1,"$%s& + $", crasis_of(Gkanal) );
      Xstrncat(wtmp,tmp1,LONGSTRING);
    }
    sprintf(tmp1,"$%s%s", workword_of(Gkanal), NEWLINE );
    Xstrncat(wtmp,tmp1,LONGSTRING);
    Xstrncat(tmp,wtmp,LONGSTRING);
    Xstrncpy(prevword,workword_of(Gkanal),MAXWORDSIZE);
  }

  odd_morpheme(Gkanal,prvb_gstr_of(Gkanal),"prvb",tmp,0);
  odd_morpheme(Gkanal,aug1_gstr_of(Gkanal),"aug",tmp,0);
  if( strcmp(stem_of(Gkanal),prevstem ) ) {	
    odd_morpheme(Gkanal,stem_gstr_of(Gkanal),"stem",tmp,1);
  } else
    odd_morpheme(Gkanal,stem_gstr_of(Gkanal),"stem",tmp,0);
  odd_morpheme(Gkanal,ends_gstr_of(Gkanal),"end",tmp,0);

  Xstrncat(tmp,"         &",LONGSTRING);
  forminfo_of(TmpGstr) = forminfo_of(Gkanal);
  dialect_of(TmpGstr) = dialect_of(Gkanal);
  set_morphflags(TmpGstr, morphflags_of(Gkanal));
  stemtype_of(TmpGstr) = stemtype_of(Gkanal);
  set_geogregion(TmpGstr,geogregion_of(Gkanal));

  SprintGkFlags(TmpGstr,tmp," ",1);

  Xstrncat(tmp,NEWLINE,LONGSTRING);
  strcat(pbuf,tmp);

finish:
  FreeGkString(TmpGstr);
}

near_miss(gk_string *gstr, char *checks, int code)
{
/*
fprintf(stdout,"near miss with code %o checks [%s] and [%s]\n", code, checks , gkstring_of(gstr) );
PrntAVerb(gstr,"",stdout);
fputc('\n',stdout);
*/
}


odd_morpheme(gk_analysis *Gkanal, gk_string *gstr, char *tag, char *bufp, int showflg)
{
  char tmp2[128];
  char mflagbuf[256];
	
  tmp2[0] = mflagbuf[0] = 0;
  MorphNames(morphflags_of(gstr),mflagbuf," ",1);

  if( (dialect_of(gstr) /*&& (dialect_of(gstr) != dialect_of(Gkanal))*/) ||
      mflagbuf[0] || showflg ) {
		
    if( ! strcmp(tag,"end") ) 
      sprintf(tmp2,"        [&%s $-%s& ", tag , gkstring_of(gstr));
    else
      sprintf(tmp2,"        [&%s $%s-& ", tag , gkstring_of(gstr));
    Xstrncat(bufp,tmp2,LONGSTRING);
    if (dialect_of(gstr)) {
      DialectNames(dialect_of(gstr),tmp2," ");
      Xstrncat(bufp,tmp2,LONGSTRING);
    }
    if(mflagbuf[0] ) {
      Xstrncat(bufp," ",LONGSTRING);
      Xstrncat(bufp,mflagbuf,LONGSTRING);
    }
    Xstrncat(bufp,"]",LONGSTRING);
    Xstrncat(bufp,NEWLINE,LONGSTRING);
  }
}

dump_all_anals(gk_word *Gkword, PrntFlags prntflags, FILE *fout)
{
  int i = 0;
  int nanals = totanal_of(Gkword);
  int goodanals = 0;
  gk_analysis * Anal;
  char curlem[MAXWORDSIZE];
  int printedwork = 0;
	
  goodanals = GoodAnals(Gkword,0);
  if( (prntflags & PERSEUS_FORMAT ) )
    fprintf(fout,"%s\n", rawword_of(Gkword) );

  for(i=0;i<nanals;i++) {
    Anal = analysis_of(Gkword)+i;
    printedwork = 0;
    /*
      if( ! (prntflags & DBASEFORMAT ) )
      fprintf(fout,":raw\t%s\t%d\n", rawword_of(Anal) , i+1 );
      */
    if( (prntflags & PERSEUS_FORMAT ) ) {
      /*
	if(  strcmp(rawword_of(Anal),workword_of(Anal)) ) {
	char tmp[MAXWORDSIZE];
	
	strcpy(tmp,workword_of(Anal));
	stripquant(tmp);
	
	fprintf(fout,"%s", strcmp(rawword_of(Anal),tmp) ?  tmp : "" );
	if( strcmp(rawword_of(Anal),tmp) ) printedwork = 1;
	}
	*/
      if( !goodanals || (goodanals && (!strchr(lemma_of(Anal),'-'))) ) {
	/*
	  if( strcmp(lemma_of(Anal),curlem) ) 
	  fprintf(fout,"%s\n",printedwork ? "\t" : "", lemma_of(Anal) );
	  */
	DumpPerseusAnalysis(Gkword,prntflags,Anal,fout,i+1);
	strcpy(curlem,lemma_of(Anal));
      }
      continue;
    }
    if( (prntflags & ENDING_INDEX ) ) {
      DumpEndingIndex(Gkword,prntflags,Anal,fout,i+1);
      continue;
    }
    DumpOneAnalysis(Gkword,prntflags,Anal,fout,i+1);
    Xstrncpy(prevlemma,lemma_of(Anal),MAXWORDSIZE);
  }
  if( (prntflags & PERSEUS_FORMAT ) )
    fprintf(fout,"\n");
}

int CompAnals(const void*, const void*);

SortAnals(gk_analysis *Anal, int nanals)
{
  /*
    lqsort(Anal,(long)nanals,(int)sizeof * Anal,CompAnals);
    */
  qsort(Anal,(long)nanals,(int)sizeof * Anal,CompAnals);

}

int CompAnals(const void* Anal1, const void* Anal2)
{
  return(strcmp(lemma_of((gk_analysis*)Anal1),lemma_of((gk_analysis*)Anal2)));
}

static gk_string EndGstr;
static word_form forminfo;

DumpPerseusAnalysis(
		    gk_word *Gkword,
		    PrntFlags prntflags,
		    gk_analysis *anal,
		    FILE *fout,
		    int cura
		    )
{
  char tmp[LONGSTRING];
  char tmp2[LONGSTRING];
  char workw[LONGSTRING];

  tmp[0] = workw[0] = 0;
	
  fprintf(fout,"<NL>");
  if( Is_participle(anal )) {
    fprintf(fout,"P ");
  }	else if( Is_nounform(anal) || Is_adjform(anal) ) {
    /*
     * grc 11/5/94
     * look for ENGLISH lemmas -- words not in the dict, for which we use the
     * English equivalent.
     * 
     * all Greek is in beta-code and hence lower case or marked with '*'
     *
     * only english words are upper case
     */
    if( isupper(lemma_of(anal)[0]) && cur_lang() == GREEK )
      fprintf(fout,"E ");
    else
      fprintf(fout,"N ");
  }
  else if( Is_verbform(anal) ) {
    fprintf(fout,"V ");
  } else
    fprintf(fout,"I ");

  if(  strcmp(rawword_of(anal),workword_of(anal)) ) {
    char tmp[MAXWORDSIZE];

    strcpy(tmp,workword_of(anal));
    /* grc 2/7/97 -- don't punt the quantity
       stripquant(tmp);
       */
		
    if( strcmp(rawword_of(anal),tmp) )
      fprintf(fout,"%s,",   tmp );
  } 

  fprintf(fout,"%s ", lemma_of(anal) );

  if (prntflags & ENDING_INDEX) {
    fprintf(fout,"\t%d</NL>",forminfo_of(anal));
  }
  else {
    GregSprintGkFlags(anal,tmp," "," ",1);
    fprintf(fout,"%s</NL>", tmp );
  }

}

DumpEndingIndex(gk_word *Gkword, PrntFlags prntflags, gk_analysis *anal, FILE *fout, int cura)
{
  
  char tmp[BUFSIZ];
  
  tmp[0] = 0;
  PrntStemtype(stemtype_of(anal),fout);
  fprintf(fout,"%s ", endstring_of(anal) );
  AddParadigmInfo(tmp,forminfo_of(anal),".");
  AddPersNumInfo(tmp,forminfo_of(anal),".");
  AddAdjInfo(tmp,forminfo_of(anal),".");
  fprintf(fout,"%s %s %d", tmp+1, workword_of(anal), totanal_of(Gkword) );
  if( strcmp(workword_of(anal),rawword_of(anal)))
    fprintf(fout," %s", rawword_of(anal) );
  
  fprintf(fout,"\n");
}

DumpOneAnalysis(gk_word *Gkword, PrntFlags prntflags, gk_analysis *anal, FILE *fout, int cura)
{
  char tmp[LONGSTRING];
  char tmp2[LONGSTRING];
  char workw[LONGSTRING];
  
  tmp[0] = workw[0] = 0;
  
  if( prntflags & LEXICON_OUTPUT ) {
    sprintf(tmp,"%s",  rawword_of(anal));
    if( strcmp( rawword_of(anal), workword_of(anal)) ) {
      strcat(tmp," ");
      strcat(tmp, workword_of(anal) );
    }
    strcat(tmp," ");
    if(  preverb_of(anal)[0] ) {
      strcat(tmp,preverb_of(anal) );
      strcat(tmp,"-");
    }
    strcat(tmp,lemma_of(anal));
    strcat(tmp,"\t");
    /*
      beta2smarta(tmp,tmp2);
      */
    fprintf(fout,"%s", tmp );
    tmp[0] = 0;	
    /*
      if( ! strcmp(rawword_of(anal),workword_of(anal)) ) 
      fprintf(fout,"\t");
      else
      fprintf(fout,"%s\t", workword_of(anal) );
      */
    /*
      fprintf(fout,"%s\t", part_of_speech(stemtype_of(anal)) );
      */
		
    /*
      Delimiter changed to '\t' by jjake on 04.24.92 in order to turn the
      Parse elements from a set into an (ordered) vector.
      */

    JakeSprintGkFlags(anal,tmp," "," ",1);
    
    fprintf(fout,"%s\t", tmp );
    
    fprintf(fout,"%s\t", crasis_of(anal) );
    /*
      if( prntflags != DBASESHORT ) {
      DumpDbGkString(prvb_gstr_of(anal),fout);
      DumpDbGkString(aug1_gstr_of(anal),fout);
      DumpDbGkString(stem_gstr_of(anal),fout);
      DumpDbGkString(suffix_gstr_of(anal),fout);
      DumpDbGkString(ends_gstr_of(anal),fout);
      }
      */
    fprintf(fout,"\n");
    return;
  }
  if( prntflags & DBASEFORMAT ) {
    char tmp[BUFSIZ];
    
    tmp[0] = 0;
    
    
    fprintf(fout,"\n:raw %s\n", rawword_of(anal) );
    fprintf(fout,"\n:workw %s\n", workword_of(anal) );
    fprintf(fout,":lem %s\n", lemma_of(anal) );
    
    fprintf(fout,":prvb "); 
    GregSprintGkFlags(prvb_gstr_of(anal),tmp," ", " ", 1);
    fprintf(fout,"%s\t%s\n", gkstring_of(prvb_gstr_of(anal)),tmp );
    tmp[0] = 0;

    fprintf(fout,":aug1 "); 
    GregSprintGkFlags(aug1_gstr_of(anal),tmp," ", " ", 1);
    fprintf(fout,"%s\t%s\n", gkstring_of(aug1_gstr_of(anal)),tmp );
    tmp[0] = 0;

    fprintf(fout,":stem "); 
    GregSprintGkFlags(stem_gstr_of(anal),tmp," ", " ", 1);
    fprintf(fout,"%s\t%s\n", gkstring_of(stem_gstr_of(anal)),tmp );
    tmp[0] = 0;

    fprintf(fout,":suff "); 
    GregSprintGkFlags(suffix_gstr_of(anal),tmp," ", " ", 1);
    fprintf(fout,"%s\t%s\n", gkstring_of(suffix_gstr_of(anal)),tmp );
    tmp[0] = 0;

    fprintf(fout,":end "); 
    GregSprintGkFlags(ends_gstr_of(anal),tmp," ", " ", 1);
    fprintf(fout,"%s\t%s\n", gkstring_of(ends_gstr_of(anal)),tmp );
    tmp[0] = 0;

    return;

    fprintf(fout,"%s\t", lemma_of(anal) );
    fprintf(fout,"%s\t", rawword_of(anal) );
    if( ! strcmp(rawword_of(anal),workword_of(anal)) ) 
      fprintf(fout,"\t");
    else
      fprintf(fout,"%s\t", workword_of(anal) );
    /*
      fprintf(fout,"%s\t", part_of_speech(stemtype_of(anal)) );
      */
		
    /*
      Delimiter changed to '\t' by jjake on 04.24.92 in order to turn the
      Parse elements from a set into an (ordered) vector.
      */

    JakeSprintGkFlags(anal,tmp,"\t"," ",1);
    fprintf(fout,"%s\t", tmp );
    fprintf(fout,"%s\t", crasis_of(anal) );
    if( (prntflags) != DBASESHORT ) {
      DumpDbGkString(prvb_gstr_of(anal),fout);
      DumpDbGkString(aug1_gstr_of(anal),fout);
      DumpDbGkString(stem_gstr_of(anal),fout);
      DumpDbGkString(suffix_gstr_of(anal),fout);
      DumpDbGkString(ends_gstr_of(anal),fout);
    }
    fprintf(fout,"\n");
    return;
  }
	
  /*
    SprintGkFlags(anal,tmp,"\t",1);
    */
  JakeSprintGkFlags(anal,tmp," "," ",1);

  if(preverb_of(anal)[0] )	{
    strcpy(workw,preverb_of(anal) );
    strcat(workw,"-");
  }
  if(aug1_of(anal)[0] )	{
    strcat(workw,aug1_of(anal) );
    strcat(workw,"-");
  }
  fprintf(fout,":summ %d %s %s%s-%s %s %s\n",cura, rawword_of(anal) , workw,
	  stem_of(anal), endstring_of(anal) , lemma_of(anal) , tmp );
  /*
    fprintf(fout,":lemm %s\n", lemma_of(anal) );
    */
  if( preverb_of(anal)[0] ) {
    DumpGstr(":pvb",prvb_gstr_of(anal),fout,(int)(prntflags & PARSE_FORMAT ));
  }
  if(  aug1_of(anal)[0] ) {
    DumpGstr(":aug",aug1_gstr_of(anal),fout,(int)(prntflags & PARSE_FORMAT ));
  }
  if( stem_of(anal)[0] ) {
    DumpGstr(":stem",stem_gstr_of(anal),fout,(int)(prntflags & PARSE_FORMAT ));
  }
  if( endstring_of(anal)[0] ) {
    EndGstr = *(ends_gstr_of(anal));
    forminfo_of(&EndGstr) = forminfo;
	
    DumpGstr(":end",&EndGstr,fout,(int)(prntflags & PARSE_FORMAT ));
  }
  if( crasis_of(anal)[0] ) {
    fprintf(fout,":crasis %s\n", crasis_of(anal) );
  }
  fprintf(fout,"\n");
}

DumpGstr(char *tags, gk_string *gstr, FILE *fout, int fullrec)
{
  char tmp[LONGSTRING];
	
  tmp[0] = 0;
	
  fprintf(fout,"%s\t%s\t", tags , gkstring_of(gstr) );
  SprintGkFlags(gstr,tmp,"\t",1);
  if( fullrec ) {
    char *s = tmp;
    while(*s) {
      if(isspace(*s)) {
	fprintf(fout," ");
	while(isspace(*s)) s++;
	continue;
      } else
	fprintf(fout,"%c", *s++);
    }
    fprintf(fout,"\n");
  } else
    fprintf(fout,"%s\n", tmp );
}

DumpDbGkString(gk_string *gstr, FILE *fout)
{
	char tmp[LONGSTRING];
	tmp[0] = 0;
	fprintf(fout,"%s", gkstring_of(gstr) );
	SprintGkFlags(gstr,tmp,"\t",1);
	fprintf(fout,"%s\t", tmp );
}
