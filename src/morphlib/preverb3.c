#include <contract.h>

#include "preverb3.proto.h"

static previndex = 0;
static char prevprevb[MAXWORDSIZE];
static gk_string * PrevbTable;
gk_string * load_euph_tab();
static int numprevb = 0;

nextpreverb(char *word, char *oldprevb, char *pblemma, gk_string *gstr)
{
  int i = 0;
  
  if( ! PrevbTable ) {
    PrevbTable = load_euph_tab(RAWPBLIST,&numprevb,NO);
    if( ! PrevbTable ) {
      fprintf(stderr,"Could not create numpreverbs!\n");
      return(0);
    }
  }


  /* 
   * this loop allows you to come back to the list of preverbs
   * and skip over an aborted match.
   *  e.g. skip past "pros" to "pro" if you had unsuccessfully
   * looked for "pros-ai/nw" rather than "pro-sai/nw"
   *
   * grc 7/21/89
   * i replaced this loop with the simpler comparison
   *
   if( ! strcmp(prevprevb,oldprevb) ) i = previndex;
   *
   if(*oldprevb) i = previndex;
   else i = 0;
   */

  for ( i = 0; i < numprevb; i++) {
    if ( !*oldprevb )
      break;
    if ( has_rawpreverb(oldprevb, PrevbTable+i) ) {
      i++;
      break;
    }
  }
  
  
  for (; i < numprevb ; i++) {
    /*
       if (! Xstrncmp(prevbtab[i].rawstring,word,Xstrlen(prevbtab[i].rawstring))) {
       */
    if( has_rawpreverb(word,PrevbTable+i) ) {
      
      char tmp[MAXWORDSIZE];
      
      Xstrncpy(oldprevb,gkstring_of(PrevbTable+i),MAXWORDSIZE);
      Xstrncpy(prevprevb,gkstring_of(PrevbTable+i),MAXWORDSIZE);
      previndex = i+1;
      Xstrncpy(pblemma,gkstring_of(PrevbTable+i)+MAXSUBSTRING,MAXWORDSIZE);
      Xstrncpy(tmp,word+Xstrlen(gkstring_of(PrevbTable+i)) ,MAXWORDSIZE);
      Xstrncpy(word,tmp,MAXWORDSIZE);
      
      /*
       * if no *pbflags set, then accept anything. otherwise, make sure that
       * you have an overlap
       */
      /*
       * grc 6/27/89
       *
       * that will not work--if you have a)podi-, then a)po- with its flag "raw_preverb" will
       * not match "di" which is not a raw_preverb.
       */
      
      if( ! no_morphflag(morphflags_of(gstr)) &&  
	 overlap_morphflags(morphflags_of(gstr) ,morphflags_of(PrevbTable+i))
	 &&  has_morphflag(morphflags_of(gstr),RAW_PREVERB) )
	continue;
      
      add_morphflags(gstr,morphflags_of(PrevbTable+i));
      if( dialect_of(PrevbTable+i) ) {
	dialect_of(gstr) = dialect_of(PrevbTable+i);
      }
      
      /*
	 add_dialect(gstr,dialect_of(PrevbTable+i));
	 if( prevbtab[i].pbflags ) {
	 int j;
	 
	 for(j=0;j<3;j++)
	 add_morphflag(pbflags , (prevbtab[i].pbflags)[j] );
	 }
	 */
      return (1);
    }
  }
  
  return(0);
}

has_rawpreverb(char *curpb, gk_string *pbentry)
{
  return(!Xstrncmp(curpb,gkstring_of(pbentry),Xstrlen(gkstring_of(pbentry))));
}

is_rawpreverb(char *s) 
{
	int i;

	for ( i = 0; i < numprevb; i++) {
		if(!strcmp(s,gkstring_of(PrevbTable+i)))
			return(1);
	}
	return(0);
}
