#include <stdio.h>
#include <gkstring.h>

#include "checkverb.proto.h"

checkverb(gk_word *Gkword)
{
	register char * wp;
	register char * a1;
	char workword[MAXWORDSIZE];
	char half1[MAXWORDSIZE];
	int rval = 0;

	Xstrncpy(workword,workword_of(Gkword),MAXWORDSIZE);
/*
 * ignore accents entirely at this point. you will look for accent errors 
 * later when you actually conjugate the word and see if things work out.
 */
/*	stripacc(workword);*/
	wp = workword;

	a1 = half1;
	*a1 = 0;

/*
 * in this loop, you start looking for endings, stripping the
 * word down from left to right, e.g.
 * starting from e)pe/pempon  you look for 
 *	pepempon
 *	epempon
 *	pempon
 *	empon
 *	mpon
 *	pon
 *	on
 * at which point you find an ending
 */

	while(*wp) {
/*
 * let's see if we have an irregular verb such as "o)/ntes" or "i(/w" or
 * a compound of some irregular verb 
 * (e.g. "a)fi/eis" or "a)fiei=s")
 */
 	
	    set_stem(Gkword,wp);
	    
	    set_rawprvb(Gkword,half1);

/*
fprintf(stderr,"trying irregvb stem [%s] preverb [%s] \n", stem_of(Gkword), rawprvb_of(Gkword) );
*/
	    rval+=try_irregvb(Gkword);


/*
 * ok, now let's see if wp is pointing to a conventional
 * ending and half1 is either a stem or  a preverb+stem
 */


	    set_preverb(Gkword,"");
	    set_rawprvb(Gkword,"");
	    set_stem(Gkword,half1);
	    set_endstring(Gkword,wp);
/*
fprintf(stderr,"trying reg stem [%s] [%s] preverb [%s] rval %d\n", stem_of(Gkword), half1, rawprvb_of(Gkword) , rval );
*/
	    rval += analyzed_verb(Gkword);

/*
	    if( rval ) {
			goto finish;
	    }
*/
	   	*a1++ = *wp++;
	    *a1 = 0;
/*
 * grc 3/24/91
 *
 * if you ask for an analysis of a(/, this thing checks for "(/"!
 *
 * i guess this is a long overlooked side effect of commenting out the 
 * stripacc(workword) above.
 *
 * this loop is to get past that little bug
 */
 		while(*wp&&!isalpha(*wp)&&*wp!='|'&&*wp!='('&&*wp!=')') wp++;


	}

/*
 * grc 7/24/89
 *
 * in a form such as e)/fh, the ending is "null", i.e. we feel that the
 * stem is fh-. check for that
 */
	if( ! rval ) {

	    set_preverb(Gkword,"");
		set_endstring(Gkword,"*");
	    set_stem(Gkword,workword);
	    rval += analyzed_verb(Gkword);

	}

	finish:

		return(rval);
}

analyzed_verb(gk_word *Gkword)
{
	char tmpendstring[MAXWORDSIZE];
	char endkeys[LONGSTRING];
	
	int rval;

	*endkeys = 0;

	Xstrncpy(tmpendstring,endstring_of(Gkword),MAXWORDSIZE);
	stripacc(tmpendstring);
	stripquant(tmpendstring);
/*
printf("rval %d tmpend %s endkeys %s\n", chckvend(tmpendstring,endkeys),tmpendstring, endkeys );
*/

	if( (rval=chckvend(tmpendstring,endkeys)) ) {
	    gk_word TmpGkword;
	    char preverbs[MAXWORDSIZE];

	    TmpGkword = * Gkword;
	    stripacc(stem_of(&TmpGkword));

	    if(rval=strippreverb(&TmpGkword,endkeys,0)) {
		CpGkAnal(Gkword,&TmpGkword);
	    }
	} 

	return(rval);
}
