#include <gkstring.h>
#define MAXAUGSTEMS 12

#include "checkstem.proto.h"
int comstemtypes(char *, char *, char *);
static wantcurstemtype(char *, char *);
extern verbose;
static int digstem = 0;

char * is_substring();

/*
 * this routine takes a possible verb stem (poss_stem) and tries
 * to figure out whether any such stem exists. 
 *
 * it is smart enough to de-augment a stem, and stores up a 
 * a variety of possible stems in *stemtab[].
 *
 * it also uses the stem types listed in endkeys to get rid of
 * extraneous hits. thus if a previous routine has found an ending
 * that fits onto "ew_pr", "ow_pr" and "ew_fut" stems, we first check to
 * make sure that a stem falls into one of these three categories, and
 * then get rid of extraneous possibilities. thus if the stem is
 * only "ew_fut", we don't have to worry about "ew_pr" or "ow_pr" forms.
 * 
 * the resulting keys for each possible stem are stored in *keytab[]
 */

static	gk_string * tstemtab[MAXAUGSTEMS];
static	gk_string * tqstemtab[MAXAUGSTEMS];
static	char * tkeytab[MAXAUGSTEMS];
static init_stor = 0;

 checkstem(char *poss_stem, char *endkeys, gk_string *stemtab[], char *keytab[], int maxstems)
{
	char *curstemkeys;
	int i;
	int hits = 0;
	int poss_augs = 0;
	int possno = 0;
	int rval = 0;



	curstemkeys = (char *)malloc((size_t)LONGSTRING+1);

	if( ! init_stor ) {
		init_stor = 1;
		for(i=0;i<MAXAUGSTEMS;i++) {
			tstemtab[i] = CreatGkString(1);
			tqstemtab[i] = CreatGkString(1);
			tkeytab[i] = (char *)malloc((size_t)LONGSTRING+1);
		}
	}
	for(i=0;i<MAXAUGSTEMS;i++) {
		ClearGkstring(tstemtab[i]);
		ClearGkstring(tqstemtab[i]);
		*tkeytab[i] = 0;
	}
	
	*curstemkeys = 0;
	rval = stemexists(poss_stem,endkeys,curstemkeys,0);
/*
fprintf(stderr,"rval %d poss stem [%s] endkeys {%s] curstem [%s]\n", rval, poss_stem,endkeys,curstemkeys);
*/

	if( rval ) {

		if( curstemkeys[0] ) {
			set_gkstring(stemtab[possno],poss_stem);
			Xstrncpy((char *)keytab[possno],(char *)curstemkeys,(size_t)LONGSTRING);
			curstemkeys[0] = 0;
			possno++;
			hits++;
		}
	}

/*
 * if it starts with a consonant, forget it.
 * if it starts with a vowel, see if you can find anything by looking
 * for unaugmented forms
 */
	if( Is_cons( *poss_stem ) )
		goto finish;


	poss_augs = unaugment(poss_stem,tstemtab,tqstemtab,MAXAUGSTEMS,ALL_DIAL,1,0);

	for(i=0;i<poss_augs;i++) {

/*
fprintf(stderr,"%d) %s\n", i , gkstring_of(tstemtab[i]) );
*/

		*curstemkeys = 0;
		if( stemexists(gkstring_of(tstemtab[i]),endkeys,curstemkeys,0) ) {
			if( curstemkeys[0] ) {
				*stemtab[hits] = *tstemtab[i];
				Xstrncpy((char *)keytab[hits],(char *)curstemkeys,(size_t)LONGSTRING);
				hits++;
			}
		}

	}

	finish:

	xFree(curstemkeys,"curstemkeys");
	curstemkeys = NULL;
/*
	for(i=0;i<MAXAUGSTEMS;i++) {

		FreeGkString(tstemtab[i]);
		tstemtab[i] = NULL;

		xFree(tkeytab[i],"tkeytab[i]");
		tkeytab[i] = NULL;
	}
*/
	return(hits);
}

stemexists(char *s, char *endkeys, char *stemkeys, int is_nom)
{
	int rval  = 0;
	
/*
fprintf(stderr,"stemexists: s [%s] stemkeys [%s] endkeys [%s]\n", s , stemkeys, endkeys);
*/
	rval = chckstem(s,stemkeys,is_nom);
if( ! rval && digstem ) {
longeststem(s);
}
/*
if( rval ) printf("rval %d for [%s] with keys [%s]\n", rval , s , stemkeys );
*/
	if( ! rval ) return(0);

	rval = comstemtypes(s,stemkeys,endkeys);
/*fprintf(stderr,"endkeys [%s] rval after comstemtypes is %d\n", endkeys, rval );*/
	return(rval);
}


/*
 * ok, here we are with a list of stems to which the current ending
 * could be appended, and a list of stemtypes (and lemmas) to which 
 * our current stem could belong. the two lists look like
 *   endkeys = "ew_pr  ew_fut ow_pr"
 *   stemkeys = "ew_fut:ba/llw aor2:ba/llw"
 *
 * now we want to get those stem types common to both lists  and
 * return with only "ew_fut:ba/llw" in the above example.
 */

int
comstemtypes(char *stem, char *stemkeys, char *endkeys)
{
	register char * s, *p;
	char tmp[LONGSTRING];
	char cstemtype[LONGSTRING];
	char cstem[MAXWORDSIZE];
	char clemma[MAXWORDSIZE];
	char stembuf[LONGSTRING];
	
	s = stemkeys;
	p = tmp;
	
	stembuf[0] = tmp[0] = 0;
	while(*s) {
		setstemvars(s,cstem,clemma,cstemtype,stembuf);

		if( wantcurstemtype(cstemtype,endkeys) ) {
			if( tmp[0] ) Xstrncat(tmp," ",(int)LONGSTRING);
			Xstrncat(tmp,clemma,(int)LONGSTRING);
			Xstrncat(tmp,":",(int)LONGSTRING);
			if( cstem[0] ) Xstrncat(tmp,cstem,(int)LONGSTRING);
			else Xstrncat(tmp,stem,(int)LONGSTRING);
			Xstrncat(tmp,":",(int)LONGSTRING);
			Xstrncat(tmp,cstemtype,(int)LONGSTRING);
			Xstrncat(tmp,":",(int)LONGSTRING);
			if(*stembuf)
				Xstrncat(tmp,stembuf,(int)LONGSTRING);
		}
		while(! isspace(*s) && *s ) s++;
		while( isspace(*s) ) s++;
	}
	Xstrncpy((char *)stemkeys,(char *)p,(size_t)LONGSTRING);

	if( *stemkeys )
		return(1);
	else
		return(0);
}

static
wantcurstemtype(char *curst, char *stlist)
{
	char * is_substring(), *s;
	int rval = 0;
	
	s = is_substring(curst,stlist);
	if( s != NULL ) rval = 1;
	
	return( rval );
}


setstemvars(char *s, char *cstem, char *clemma, char *cstemtype, char *cstemkeys)
{
	char * parsefield();
	*cstemkeys = *cstem = *clemma = *cstemtype = 0;
	
	s = parsefield(s,cstem,':',MAXWORDSIZE);
	s = parsefield(s,clemma,':',MAXWORDSIZE);
	s = parsefield(s,cstemtype,':',MAXWORDSIZE);
	s = parsefield(s,cstemkeys,' ',LONGSTRING);
}

char *
parsefield(char *s, char *buf, int c, int len)
{
	int i;
	
	*buf = 0;
/*
	while(*s&&*s!=c&&!isspace(*s)) *buf++ = *s++;
*/
	for(i=0;*s&&*s!=c&&!isspace(*s);i++) {
		*buf++ = *s++;
		if( i >= len ) {
			fprintf(stderr,"Hey %d chars; %d s [%s] left!\n", len , Xstrlen(s) ,s );
			*buf = 0;
			while(*s&&!isspace(*s)) s++;
			break;
		}
	}
	
	*buf = 0;
	if( isspace(*s) ) return("");
	if(*s) s++;
	return(s);
}

longeststem(s)
char * s;
{
	char * p = s;
	char tmp[256],tmp2[256];
	char stemkeys[1024];
	int rval = 0;
	
	strcpy(tmp,s);
	stemkeys[0] = 0;
	p = tmp;
	
	while(*p) p++; p--;
	while(p>=tmp) {
		strcpy(tmp2,p);
		*p = 0;
		if( (rval += chckstem(tmp,stemkeys,1)) ) {
			printf("%s-%s\tn\t%s\n", tmp, tmp2, stemkeys );
		}
		if( chckstem(tmp,stemkeys,0) )  {
			printf("%s-%s\tv\t%s\n", tmp, tmp2, stemkeys );
			break;
		}
		if( rval ) break;
		p--;

	}
	
}
