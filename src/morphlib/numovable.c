#include <gkstring.h>

#include "numovable.proto.h"

takes_nu_movable(gk_string *gstr)
{
	char tmp[MAXWORDSIZE];
	char * s = tmp;
	strcpy(tmp,gkstring_of(gstr));

/*
 * grc 7/22/89
 * 
 * we were not getting nu movables on forms such as xersi/ and frasi/.
 * hence, we added stripacc()
 */	
 	stripacc(s);
 	
	if(ends_in(s,"si") || ends_in(s,"ci") || ends_in(s,"yi"))  
		return(1);
/*
	if( ends_in(s,"ei") && tense_of(forminfo_of(gstr)) == PLUPERF )
		return(1);
*/
/*
 * grc 11/29/88
 *
 * it is not clear why the pluperfect nu movables have been commented out.
 * they are clearly listed both in Smyth 134 and in the paradigm for w_stem verbs
 * (Smyth 383 where the form lelu/kei(n) is listed).
 */
	if( ends_in(s,"e") && person_of(forminfo_of(gstr)) == PERS3 /* && 
			tense_of(forminfo_of(gstr)) != PLUPERF*/) 
		return(1);
	return(0);
}

add_numovable(gk_string *gstr)
{
	Xstrncat(gkstring_of(gstr), "n",MAXWORDSIZE);
	add_morphflag(morphflags_of(gstr),NU_MOVABLE);
}
