#include <stdio.h>
#include <gkstring.h>

#include "checknom.proto.h"
static gotnom(gk_word *);

checknom(gk_word *Gkword)
{
	int rval;

	if( (prntflags_of(Gkword) & VERBS_ONLY ) ) return(0);

	if(rval=checkregnom(Gkword))
		return(rval);
	return(0);
}

checkregnom(gk_word *Gkword)
{
	register char * wp;
	char workword[MAXWORDSIZE];
	char half1[MAXWORDSIZE];
	int rval = 0;
	Xstrncpy(workword,workword_of(Gkword),(int)sizeof workword);


/*
 * in this loop, you start looking for endings, stripping the
 * word down from left to right, e.g.
 * starting from a)nqrwpou  you look for 
 *	a) nqrwpou
 *	a)n qrwpou
 *	a)nq rwpou
 *	a)nqr wpou
 *	a)nqrw pou
 *	a)nqrwp ou
 * at which point you find ending "ou"
 */

	Xstrncpy(half1,workword,(int)sizeof half1);

/*
 * check first to see if this word works as a noun with a null
 * ending: 
 * 	e.g. voc sg of pai=s, pai=
 */
	set_zeroend(Gkword);
	set_stem(Gkword,workword);
/*
 * grc 7/14/89
 *
 * make this exhaustive -- we failed on o)/pa from o)/y because o)pa/ from o)ph/,
 * o)ph=s got in the way.
 *
	if( rval=gotnom(Gkword) ) {
		return(rval);
	}
 */
 	rval += gotnom(Gkword);

	wp = workword;

	while( *wp ) {

	    set_endstring(Gkword,wp);
	    Xstrncpy(half1,workword,(int)sizeof half1);
	    half1[wp-workword]=0;
	    wp++;

	    set_stem(Gkword,half1);
	  /*
	    if( rval=gotnom(Gkword) ) {
		goto finish;
	     }
	   */
	   	rval += gotnom(Gkword);

	}
	
	finish:
		return(rval);
}

static 
gotnom(gk_word *Gkword)
{
	int is_ending = 0;
	int rval = 0;
	char *endkeys;
	gk_string *curstem;
	char *curend;
	char *stemkeys;
	
	endkeys = stemkeys = curend = NULL;
	curstem = NULL;

	endkeys = (char *)malloc((size_t)LONGSTRING);
	stemkeys = (char *)malloc((size_t)LONGSTRING);
	curstem = CreatGkString(1);
	curend = (char *)malloc((size_t)MAXWORDSIZE);
	
	endkeys[0] = stemkeys[0] = 0;
	stripacc(endstring_of(Gkword));
	Xstrncpy(curend,endstring_of(Gkword),MAXWORDSIZE);
/*
 * note that with nouns we ignore the accents at this point.
 * this is so that we don't have to worry about varying accents such
 * as a)gaqo/s vs. a)/ristos.
 */
	is_ending = chcknend(curend,endkeys);
/*printf("rval %d on curend [%s]\n", is_ending , curend );*/
	if( is_ending ) {
		Xstrncpy(gkstring_of(curstem),stem_of(Gkword),(int)sizeof gkstring_of(curstem));
		stripacc(gkstring_of(curstem));
/*printf("trying stem [%s] with ending [%s] endkeys [%s]\n", gkstring_of(curstem) , curend , endkeys );*/
		*stemkeys = 0;
		if( stemexists(gkstring_of(curstem),endkeys,stemkeys,1) ) {
			rval += StemWorks(Gkword,stemkeys, curstem );
		}
	} 
	if(! rval && 0 ) {
		/*rval=strippreverb(Gkword,endkeys,0);*/
/*printf("rval %d after stripp\n", rval );*/
		if(!rval) checkforcompnoun(gkstring_of(curstem),endkeys,stemkeys);
	}

	xFree(endkeys,"endkeys");
	xFree(stemkeys,"stemkeys");
	FreeGkString(curstem);
	xFree(curend,"curend");
	endkeys = stemkeys = curend = NULL;
	curstem = NULL;
	return(rval);
}
