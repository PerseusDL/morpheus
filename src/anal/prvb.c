#include <stdio.h>
#include <gkstring.h>

#include "prvb.proto.h"

strippreverb(gk_word *Gkword, char *endkeys, int rval)
{
	register char * a;
	register char * b;
	char curstem[MAXWORDSIZE];
	int foo;
	
	gk_word WorkGkword;
/*
 * let's see if the stem by itself flies without a preverb
 */
	if( checkhalf1(Gkword,endkeys) ) {
		rval++;
	}

	WorkGkword = * Gkword;
	Xstrncpy(curstem,stem_of(&WorkGkword),MAXWORDSIZE);
/*	fprintf(stderr, "entered strippreverb with word %s\n", curstem); */

/*
fprintf(stderr,"start with ending [%s]\n", endstring_of(Gkword) );
*/
	for(a=curstem,b=rawprvb_of(Gkword);;) {
		set_morphflag(morphflags_of(prvb_gstr_of(&WorkGkword)),0);
		if( ! * a )
			return(rval);
		*b++ = *a++;
		*b = 0;
		set_stem(Gkword,a);
		
		/*
		 * grc 6/26/89
		 *
		 * we were failiing on a)nti/fhmi
		 * because the stem was seen as "/fhmi" -- the initial accent confused
		 * the subsequent checks (does the stem begin with a vowel?  with a consonant?)
		 * and this seemed the best place to fix it.
		 */
		if( Is_accent(*a) ) 
			continue;
		WorkGkword = *Gkword;

/* fprintf(stderr, "trying raw preverb %s, preverb %s\n", rawprvb_of(&WorkGkword), preverb_of(&WorkGkword)); */
		if( is_preverb(rawprvb_of(&WorkGkword),preverb_of(&WorkGkword),
			prvb_gstr_of(&WorkGkword)) ) {
					
			/*
			 * don't try out possibilities where the preverb reduces the stem to nothing 
			 */
			if( ! stem_of(&WorkGkword)[0] ) 
				continue;


/* fprintf(stderr, "rawpb [%s] pb [%s] stem %s\n", rawprvb_of(&WorkGkword), preverb_of(&WorkGkword), stem_of(&WorkGkword)); */

			if( ! CombPbStem(rawprvb_of(&WorkGkword),stem_of(&WorkGkword),dialect_of(&WorkGkword),morphflags_of(prvb_gstr_of(&WorkGkword))) ) {
				continue;
			}

			if( has_morphflag(morphflags_of(prvb_gstr_of(&WorkGkword)) , APOCOPE ) && (dialect_of(&WorkGkword) & PROSE) ) 
				continue;
			if( doubled_cons(stem_of(&WorkGkword) ) )  {
				if( AndDialect(dialect_of(&WorkGkword),EPIC) < 0 ) 
					continue;
				if( (dialect_of(&WorkGkword) & PROSE) ) 
					continue;
					
				strcpy(stem_of(&WorkGkword),stem_of(&WorkGkword)+1);
				add_morphflag(morphflags_of(prvb_gstr_of(&WorkGkword)),DOUBLED_CONS);
				add_dialect(stem_gstr_of(&WorkGkword),(EPIC|POETIC));
			}
/*
fprintf(stderr,"\t pb [%s] stem [%s] end [%s]\n", rawprvb_of(&WorkGkword), 
stem_of(&WorkGkword), endstring_of(&WorkGkword) );
*/
			if( checkhalf1(&WorkGkword,endkeys) ) {
/* fprintf(stderr, "\t* found one!\n"); */
				CpGkAnal(Gkword,&WorkGkword);
      				rval++;
			}

		}
	}
}

/*
 * check for stems such as a)na-ssei/sas
 */
doubled_cons(char *s)
{
	if( *s == 'r' ) 
		return(0);
	if( ! Is_cons(*s) ) return(0);
/*
 * grc 5/29/92
 *
 * avoid forms such as prossth=nai being analyzed as from pro-i/sthmi
 */
	if( Is_cons(*(s+2))) return(0);
	if(*s==*(s+1) ) return(1);
	return(0);
}
