#include <gkstring.h>
#include "endfiles.h"

#include "mkend.proto.h"
static mk_compend(gk_string *, gk_string *, char *, char *);
static update_end(gk_string *, gk_string *, char *, char *, char *);
static join_end(gk_string *, char *, int);

static gk_string WantGstr;
static gk_string AvoidGstr;
static gk_string CurGstr;
static gk_string BlankGstr;

 mk_end(char *havestr, gk_string *Have, gk_string *Avoid)
{
	char * s;
	char savestr[MAXWORDSIZE];
	gk_string * contr_forms;
	gk_string * euph_forms;
	gk_string * poss_contracts();
	gk_string * do_euph();
	gk_string * fix_eta();
	int saw_vowel = 0;
	
	strcpy(savestr,havestr);
	s = savestr;


	while(*s) {
		if( Is_vowel(*s) ) saw_vowel = 1;
		
		if( *s == '@' ) {

			*s = 0;
			mk_compend(Have,Avoid,savestr,s+1);
			return;
		}
		s++;
	}
	
	join_end(Have,gkstring_of(Have),saw_vowel);



	if( (euph_forms = fix_eta((Have)) )) {
		int i;
		for(i=0;gkstring_of(euph_forms+i)[0];i++) {
			mk_end(gkstring_of(euph_forms+i),euph_forms+i,&AvoidGstr);
		}
		FreeGkString(euph_forms);
	}


	if( (euph_forms = do_euph(Have,dialect_of(Avoid)) )) {
		int i;
		for(i=0;gkstring_of(euph_forms+i)[0];i++) {
			mk_end(gkstring_of(euph_forms+i),euph_forms+i,&AvoidGstr);
		}
		FreeGkString(euph_forms);
		return;
	}
/*
 * allow only one contraction per ending for now
 */
	if( ! (Is_contracted(morphflags_of(Have))) && 
		(contr_forms = poss_contracts(Have,dialect_of(Avoid)) )) {
		int i;

		for(i=0;gkstring_of(contr_forms+i)[0];i++) {
			mk_end(gkstring_of(contr_forms+i),contr_forms+i,&AvoidGstr);
		}
		FreeGkString(contr_forms);
		
	} else {
	/*
	 * note that any form that is contracted is assumed to be
	 * contracted. Thus if you want to keep "ee" as "ee", then
	 * "ee" must be stored as the output for "ee" in the appropriate
	 * table.
	 */
/*
printf("no contr in: "); PrntGkStr(Have,stdout);

*/
		if( takes_nu_movable(Have) && cur_lang() != ITALIAN && cur_lang() != LATIN ) {
			gk_string TmpGstr;
			TmpGstr = * Have;
			
			add_numovable(&TmpGstr);

			mk_end(gkstring_of(&TmpGstr),&TmpGstr,&AvoidGstr);
		}

		if( do_dissim(gkstring_of(Have))) {
			add_morphflag(morphflags_of(Have),DISSIMILATION);
		}
		AddNewGstr(Have);

	}
	
}


static 
 mk_compend(gk_string *Have, gk_string *Avoid, char *curstr, char *endtype)
{
	char fname[BUFSIZ];
	FILE * f;
	FILE * MorphFopen();
	int i;
	char line[BUFSIZ];
	char savestem[MAXWORDSIZE];
	gk_string TmpHave;
	gk_string TmpAvoid;

	sprintf(line,"endtables/basics/%s.end",  endtype );

	if( ! (f=MorphFopen(line,"r")) ) {
		fprintf(stderr,"could not open [%s]\n", endtype );
		return(-1);
	}
	while(fgets(line,sizeof line,f)) {
		char curendstr[MAXWORDSIZE];

		strcpy(savestem,curstr);

		if( is_blank(line) )
			continue;
		if( Is_comment(line) )
			continue;

		TmpHave = * Have;
		TmpAvoid = * Avoid;

		nextkey(line,curendstr);

		update_end(&TmpHave,&TmpAvoid,savestem,curendstr,line);
	}
	fclose(f);
}

static 
 update_end(gk_string *Have, gk_string *Avoid, char *stem, char *endstr, char *newkeys)
{
	char savestem[MAXWORDSIZE];

	strcpy(savestem,stem);

	/*
	 * at this point check to see if you want this ending
	 *	if( merge_keys(endkeys,newendline) )
	 *		mk_end() 
	 *	else
	 *		go back
	 */
	if( merge_keys(Have,Avoid,savestem,endstr,newkeys) ) {
		set_gkstring(Have,savestem);
/*
 * this should be put somewhere else ...
 */
 		CompStemEnd(Have,gkstring_of(Have),endstr);

		strcat(gkstring_of(Have),endstr);
		mk_end(gkstring_of(Have),Have,Avoid);
	} 
}

static
 join_end(gk_string *Have, char *stem, int saw_vowel)
{
	gk_string SaveGstr;
	set_gkstring(Have,stem);
/*
	set_morphflags(&SaveGstr,morphflags_of(Have));
*/
	/* mod 2/21/88 */
/*
	if( Is_penult_accent(morphflags_of(Have)) ) {
		if( saw_vowel) {
/*
printf("saw_vowel on [%s]\n", gkstring_of(Have) );
*
			zap_morphflag(morphflags_of(Have),STEM_ACC);
			add_morphflag(morphflags_of(Have),SUFF_ACC);
		}
	} else */ /* end mod */
	
	
	if( ! Needs_accent(morphflags_of(Have)) 
	&& ! has_morphflag(morphflags_of(Have),SUFF_ACC)
	&& ! has_morphflag(morphflags_of(Have),HAS_AUGMENT)
/*	&& ! has_morphflag(morphflags_of(Have),STEM_ACC)*/
	&& nsylls(gkstring_of(Have)) < 3 ) {
		add_morphflag(morphflags_of(Have),ACCENT_OPTIONAL);
	}
	
	if( ! has_morphflag(morphflags_of(Have),IS_DERIV) && gkstring_of(Have)[0] !='*' ) {
		AccComposForm(Have);
	}
	if( gkstring_of(Have)[0] == '*' )
		zap_morphflag(morphflags_of(Have),ACCENT_OPTIONAL);


	if( has_morphflag(morphflags_of(Have),INDECLFORM) ) {
		CheckForBreathing(Have);
	}
}

 CompStemEnd(gk_string *gstr, char *stem, char *endstr)
{
	int lastc;
	char * ep = endstr;

	lastc = *(stem+strlen(stem)-1);
	
	/*
	 * if you have "e)" + "_mi", then swap the breathing and the long marker
	 * so that we are looking at "e_" + ")mi". Then do the lengthening
	 */
	 

/*
 * ouch -- this should never be hard coded but it will have to stay here for
 * now. I will fix this for latin for now.
 * grc 8/12/96
 */
	 if( Is_breath(lastc) && *ep == HARDLONG && cur_lang() != LATIN && cur_lang() != ITALIAN ) {
	 		*ep = lastc;
	 		lastc = *(stem+strlen(stem)-2);
	 		ep = stem+strlen(stem)-1;
	 		*ep = HARDLONG;
	 }
	 
	 

/*
printf("gks [%s] lastc [%c] stem [%s] endstr [%s]\n", gkstring_of(gstr), lastc , stem, endstr );
*/
	 
/*
 * this side effect should not be in the code!
 * grc 8/12/96
 */

   if( cur_lang() != LATIN && cur_lang() != ITALIAN ) {
	/*
	 * if you have "e" + "_s", convert this to "eis".
	 *
	 * thus, if you have "e" + "_sa" --> "eisa"
	 *		     "e" + "_shs" --> "eishs"
	 *		     "e" + "_sh|" --> "eish|"
	 */
	if( lastc == 'e' && *ep == HARDLONG ) {
		*ep = 'i';
	} else if( lastc == 'o' && *ep == HARDLONG ) {
		/*
		 * "gno" + "-s" --> "gnou/s"
		 */
		*ep = 'u';
	} 
		
   }	

	/* 
	 * '*' is a marker for a null ending, as in the
 	 * athematic endings:
	 *	-n	-men
	 *	-s	-te
	 *	*	-san
	 *
	 * the '*' is a place holder in the ending file, and
	 * is stripped out here so that we don't, for example,
	 * end up storing "h*" as an ending.
	 * 
	 * grc 10/8/88 
	 * this has obviously been changed--find out where the deletion actually takes
	 * place
	 *
	 */
	if( *ep == '*' ) {
	}
	
	zap_extra_lmarks(stem);
	if( Is_lvwl(*(lastn(stem,1))) && *endstr == HARDLONG ) {
		strcpy(endstr,endstr+1);
	}
}

zap_extra_lmarks(char *s)
{
	while(*s) {
		if( Is_lvwl(*s) && *(s+1) == HARDLONG ) {
			strcpy(s+1,s+2);
		}
		s++;
	}
}

