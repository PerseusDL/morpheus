#include <string.h>

#include <gkstring.h>

#include "preverb2.proto.h"
static exp_prevb2(char *, char *, gk_string *);


/*
 * this routine does two things
 * 	a) it checks to see if sticking a raw preverb could 
 *		actually be attached to a particular stem.
 *	    thus, it catches errors such as "sun+bai/nw" or
 * 		"e)l+poiw=" or "par+ba/llw".
 *	b) it not only checks to make sure that certain letters
 *		are followed by a vowel, but will add a breathing
 *		if the current preverb requires either a rough
 *		or a smooth breathing.
 *	    thus, 
 *		if we have preverb "par", however, and stem "air",
 *		    we end up with stem "air" because "par" can
 *		    be followed by either a rough or a smooth breathing.
 *		if we have preverb "kaq" and stem "air", we
 *		    end up with stem "ai(r", 
 *	        if we have preverb "kat" and stem "air" we end up
 *		    with stem "ai)r"
 *		**UNLESS THE VERB COULD BE IONIC OR AEOLIC!
 *			in which case "kat" does not prejudice the breathing at all.
 */
CombPbStem(char *curpb, char *restofs, Dialect dial, MorphFlags *pbflags)
{
  if( ! * restofs ) return(YES);
  if( cur_lang() == LATIN || cur_lang() == ITALIAN ) 
	return(CombPbStemL(curpb,restofs, dial,pbflags));
  else
	return(CombPbStemG(curpb,restofs, dial,pbflags));
}

CombPbStemL(char *curpb, char *restofs, Dialect dial, MorphFlags *pbflags)
{
	int lastc, lastc2, lastc3, curbreath;
	char workrest[MAXWORDSIZE], noaccpb[MAXWORDSIZE];

	if( !strcmp("circum",curpb) && *restofs == 'i' ) {
		add_morphflag(pbflags,RAW_PREVERB);
		return(YES);
	}

	if( !strcmp("red",curpb) || !strcmp("prod",curpb) ) {
		add_morphflag(pbflags,D_PREVB);
		return(YES);
	}


	lastc = *(curpb + strlen(curpb) - 1);
	

	if( !strcmp("amb",curpb) && !strchr("aeiou",*restofs) ) return(NO);

	if( !strcmp("sub",curpb) || ! strcmp("ob",curpb) ) {
		switch(*restofs) {
			case 'c':
			case 'f':
			case 'g':
			case 'p':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				break;
		}
	}

	if( !strcmp("ex",curpb)) {
		if( ! strchr("aeioucpqtf",*restofs) ) {
			add_morphflag(pbflags,RAW_PREVERB);
		}
		return(YES);
	}

	if( !strcmp("trans",curpb)) {
		switch(*restofs) {
			case 'i':
			case 'j':
			case 'd':
			case 'l':
			case 'm':
			case 'n':
			case 's':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				break;
		}
		return(YES);
	}
	if( !strcmp("dis",curpb)) {

		/* dis-di --> unchanged */
		if( !strncmp("di",restofs,2) ) return(YES);

		switch(*restofs) {
			case 'b':
			case 'd':
			case 'g':
			case 'l':
			case 'm':
			case 'n':
			case 'r':
			case 'v':
			case 'f':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				break;
		}
	}

	if( !strcmp("sub",curpb)) {
		switch(*restofs) {
			case 'm':
			case 'r':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				break;
		}
	}

		
	if( !strcmp("in",curpb)) {
		switch(*restofs) {
			case 'b':
			case 'l':
			case 'p':
			case 'm':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				break;
		}
	}

	if( !strcmp("con",curpb)) {
		switch(*restofs) {
			case 'b':
			case 'p':
			case 'm':
			case 'r':
			case 'l':
			case 'n':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				break;
		}
	}
	if( !strcmp("ad",curpb)) {
		switch(*restofs) {
			case 'c':
			case 'f':
			case 'g':
			case 'l':
			case 'n':
			case 'p':
			case 'r':
			case 's':
			case 't':
				add_morphflag(pbflags,RAW_PREVERB);
				break;
			default:
				
				break;
		}
	}
	
	return(YES);
}

CombPbStemG(char *curpb, char *restofs, Dialect dial, MorphFlags *pbflags)
{
  int lastc, lastc2, lastc3, curbreath;
  char workrest[MAXWORDSIZE], noaccpb[MAXWORDSIZE];
  
  
  if( has_morphflag(pbflags,DISSIMILATION) && ! next_cons_rough(restofs) ) 
    return(NO);
  
  
  Xstrncpy(noaccpb,curpb,MAXWORDSIZE);
  stripacc(noaccpb);
  stripbreath(noaccpb);
  /*
   * grc 6/36/89
   *
   * if you have "e)n", lastc2 should == 'e', not ')'
   */
  
  lastc = *(noaccpb+Xstrlen(noaccpb)-1);
  if(Xstrlen(noaccpb) > 1 )
    lastc2 = *(noaccpb+Xstrlen(noaccpb)-2);
  else
    lastc2 = 0;
  if(Xstrlen(noaccpb) > 2 )
    lastc3 = *(noaccpb+Xstrlen(noaccpb)-3);
  else
    lastc3 = 0;
  
  
  /*
   * a)/n-sxeo -- get the apocope
   */
  
  if( Is_cons(lastc) && lastc != 's' && lastc2 != 'e' /* ignore u(pe/r, e)k, e)g, ktl  */ 
     && Is_cons(*restofs)) {
    if( (lastc2 != 'u' && lastc3 != 's' ) ) /* don't mess with su/n */
      add_morphflag(pbflags,APOCOPE);
  }
  /*
   * "u(f", "a)f", "e)f", all must precede a rough breathing.
   *
   * but watch out for "a)mf" !
   */
  
  /*
   * if last char is 'f' and second to last char is 'm'
   * then you have "a)mfi" and all is clear
   */
  /*
   * otherwise, put a rough breathing on the rest of the word
   */
  if( lastc == 'q' || lastc == 'f' ) {
    if( ! Is_vowel( *restofs ) )
      return(NO);
    if( *(lastn(curpb, 2)) == 'm' && lastc == 'f') {
      add_morphflag(pbflags,ELIDE_PREVERB);
      return(YES);
    }
    curbreath = getbreath(restofs);
    /*
     * 2/6/90
     *
     * well, in fixing e)paf-i/hmi (below)
     * we broke the basic function that allowed us to 
     * analyze a)pi/keto, a)paire/w.  what we really need to do is
     * address each preverb separately with its own settings.
     * for now perhaps this will allow us to solve the problem:
     * always let the last preverb win out: we thus privilege the link of
     * of preverb to verb.
     *  in this case, trash the UNASP_PREVERB flag if need be
     */
    if( has_morphflag(pbflags,UNASP_PREVERB) )
      zap_morphflag(pbflags,UNASP_PREVERB);
    if( curbreath == NOBREATH )
      addbreath(restofs,ROUGHBR);
    else if( curbreath == SMOOTHBR )
      return(NO);
  }
  
  /*
   * "met" "a)p" etc.
   */
  else if( (lastc == 't' || lastc == 'p') && Is_vowel(*restofs) ) {
    /*
       if( ! Is_vowel( * restofs ) && has_morphflag(pbflags,APOCOPE) ) 
       return(YES);
       */
    curbreath = getbreath(restofs);
    if(  AndDialect(dial,AEOLIC|IONIC) >= 0 && ( curbreath == ROUGHBR/*
								      * grc
								      * deleted 11/1/89 because we were failing on e)p-af-i/hmi*/
						|| curbreath == NOBREATH)  ) {
      add_morphflag(pbflags,UNASP_PREVERB);
      return( YES );
    } else if( curbreath == NOBREATH ) {
      /*
       * grc 7/17/89
       *
       * can't do this here -- we were failing on a)nt-a/usen because this
       * is assuming that we have a)nt- au)s-
       *
       addbreath(restofs,SMOOTHBR);
       */
      return(YES);
    } else if( curbreath == ROUGHBR )
      return(NO);
  } 
  
  else if( lastc == 'c' ) {
    if( ! Is_vowel( *restofs) )
      return(NO);
  }
  /*
   * su- as in "su + strateu/w" 
   */
  else if( lastc == 'u' ) {
    /*
     * grc 7/1/89
     *
     * 'z' added so that we could pick up on forms such as su-zhte/w
     */
    if( * restofs != 's' && *restofs != 'z' ) 
      return(NO);
  }
  
  /*
   * rules of euphony for nu as in Smyth  91ff.
   */
  
  if( (Is_palatal( *restofs ) || *restofs == 'c' ) ||
     (Is_labial(*restofs) || * restofs == 'y' )  ||
     *restofs == 'l' || *restofs == 'r' || *restofs == 'm' ) {
    if( lastc == 'n' ) {
      /*
       * grc 6/29/89
       * allow for forms such as e)n-re/w
       *
       return(NO);
       */
      add_morphflag(pbflags,RAW_PREVERB);
      add_morphflag(pbflags,POETIC);
      return(YES);
    }
  }
  
  /*
   * di-eipei=n, but not di-di/dwmi
   */
  if( lastc == 'i' && lastc2 == 'd' ) {
    if( (!Is_vowel(*restofs) ) )
      return(NO);
  }
  /*
   * a)g-gra/fw and a)nagra/fw, but not a)g-a/gw
   */
  if( lastc == 'g' && ! Is_palatal(*restofs)) {
    return(NO);
  }
  /*
   * e)n, su/n, but not u(pe/r
   */
  if( lastc2 == 'u' || (lastc2 == 'e' && lastc3 != 'p' )  ) {
    switch(lastc) {
    case 'g':
      if( ! Is_palatal(*restofs) && *restofs != 'c' )
	return(NO);
      return(YES);
    case 'm':
      if( ! Is_labial(*restofs) && *restofs != 'y' &&
	 *restofs != 'm' )
	return(NO);
      return(YES);
    case 'l':
      /*
       * sul-leipw, e)l-lambanw
       * but not sul-nomizw or e)l-feugw
       */
      if( *restofs != 'l' )
	return(NO);
      return(YES);
    case 'r':
      /*
       * sur-re/w not sur-poie/w
       * but accept par-e/rxomai
       */
      if( lastc2 == 'u' && *restofs != 'r' ) 
	return(NO);
      if( *restofs != 'r' && ! Is_vowel(*restofs) )
	return(NO);
      return(YES);
    default:
      return(YES);
    }
  }
  /*
   * make sure that you have doubling of the 'r' after a vowel preverb
   */
  if( Is_vowel(lastc) && Is_vowel(*restofs) && Xstrncmp(lastn(noaccpb,2),"di",2)) {
    add_morphflag(pbflags,RAW_PREVERB);
    if( (lastc3 != 'p' && lastc2 != 'r') ) {
      add_morphflag(pbflags,POETIC);
      return(YES);
    }
  }
  if( Is_vowel(lastc) && *restofs == 'r' ) {
    /* grc 8/25/88 
     * if you see a pattern such as a)na-roibdei=s,
     *  don't just die. Set the flag "RAW_PREVERB" and see what happens
     */
    if( *(restofs+1) != 'r' ) {
      char tbuf[MAXWORDSIZE];
      
      add_morphflag(pbflags,RAW_PREVERB);
      add_morphflag(pbflags,POETIC);
      Xstrncpy(tbuf,"r(",MAXWORDSIZE);
      Xstrncpy(tbuf+2,restofs+1,MAXWORDSIZE);
      Xstrncpy(restofs,tbuf,MAXWORDSIZE);
      /*
	 return(NO);
	 */
    } else
      *(restofs+1) = '(';
    return(YES);
  }
  return(YES);
}

is_preverb(char *rawpb, char *fullpb, gk_string *gstr)
{
  int rval;
  
  /*	char tmpfullpb[MAXWORDSIZE];*/
  
  if( ! * rawpb ) return(0);
  *fullpb = 0;
  
  set_morphflag(morphflags_of(gstr),0);
  rval=exp_preverb(rawpb,fullpb,gstr);
  return(rval);
}


/*
 * break the raw preverbs in rawpb into their dictionary parts.
 * e.g., "parasummeta" is stored as "para/,su/n,meta/" in fullpb.
 *
 * returns 0 if rawpb does not break up into preverbs.
 * returns 1 if successful
 */
exp_preverb(char *rawpb, char *fullpb, gk_string *gstr)
{
  char savepb[MAXWORDSIZE];
  char tmppb[MAXWORDSIZE];
  int rval = 0;
  
  if( ! * rawpb ) return(0);
  if( strchr(rawpb,',')  ) {
    Xstrncpy(fullpb,rawpb,MAXWORDSIZE);
    return(1);
  }
  if( fullpb == NULL ) 
    fullpb = tmppb;
  /*
     set_morphflag(morphflags_of(gstr),0);
     */
  Xstrncpy(savepb,rawpb,MAXWORDSIZE);
  stripacc(savepb);

  rval = exp_prevb2(savepb,fullpb,gstr);
  return(rval);
}


static recursion_level = 0;
/*
 * this does the real work of exp_preverb()
 *
 * it performs a depth first search of the possible parses of any
 * particular cluster of preverbs.
 * 
 * thus it segments "prosummeta" as "pros-ummeta" and recurses
 * with "ummeta". when this fails, it pops back up
 * and tries "pro-summeta", from which it recursively calls itself to
 * examine "summeta", and "meta" 
 */
static 
exp_prevb2(char *str, char *fullpb, gk_string *gstr)
{
  int i;
  char startpb[MAXWORDSIZE];
  char startfpb[MAXWORDSIZE];
  char preverb[MAXWORDSIZE]; /* actual preverb, e.g. "a)f" or "par" */
  char pblemma[MAXWORDSIZE]; /* this is where you put the cannonical
			      * form of the preverb, e.g. "a)po/"
			      */
  gk_string Gstr, SaveGstr;
  
  set_morphflag(morphflags_of(&Gstr),0);
  
  strncpy(startpb,str,MAXWORDSIZE);
  strncpy(startfpb,fullpb,MAXWORDSIZE);
  SaveGstr = * gstr;
  preverb[0] = 0;
  
  if( ! *str ) {
    return(1);
  }
  
  for(i = 0;;i++) {
    int rval;

    rval = nextpreverb(str,preverb,pblemma,gstr); 

    if( ! rval ) return(0);
    
    if( *fullpb )
      strncat(fullpb,",",MAXWORDSIZE);
    strncat(fullpb,pblemma,MAXWORDSIZE);
    
    if( ! CombPbStem(preverb,str,(Dialect)0,morphflags_of(&Gstr))) {
      return(0);
    }
    
    ++recursion_level;
    rval = exp_prevb2(str,fullpb,gstr);
    if(rval) {
      if( has_morphflag(morphflags_of(&Gstr),UNASP_PREVERB ) ) 
	add_morphflag(morphflags_of(gstr),UNASP_PREVERB );
      return(rval);
    } 
    /*
     * ok, trying that preverb must not have worked, so let's reset preverblist
     * to what it was when we first entered this routine
     */
    strncpy(str,startpb,MAXWORDSIZE);
    strncpy(fullpb,startfpb,MAXWORDSIZE);
    *gstr = SaveGstr;
  }
  printf("broke out of loop\n");
  return(0);
}
