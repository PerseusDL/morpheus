#include <gkstring.h>
#include <modes.h>
#define MAXSTEMS 10

#include "checkindecl.proto.h"
static IndeclWorks(gk_word *, char *);
long matchendtag();


checkindecl(gk_word *Gkword)
{
	int rval;
	int hits = 0;
	int nstems = 0;
	int i;
	int sawstems = 0;
	char *keys;
	char keybuf[LONGSTRING];
	char workword[MAXWORDSIZE];
	char * parsefield();
	char stemkeys[LONGSTRING];
	char tmpword[MAXWORDSIZE];
	register char * sp;
	
/*
	keybuf = (char *)malloc((size_t)LONGSTRING);
	workword = (char *)malloc((size_t)MAXWORDSIZE);
*/
	if( (prntflags_of(Gkword) & VERBS_ONLY ) ) return(0);
	Xstrncpy(tmpword,workword_of(Gkword),MAXWORDSIZE);

	keys = keybuf;
	rval = chckindecl(tmpword,keys);
/*
printf("rval %d workword [%s] keys [%s]\n", rval, workword, keys );
*/
	if( ! rval ) {
		goto finish;
	}
	while(*keys) {	
	sp = keys;
		
/*
		sp = parsefield(sp,tmpword,':');
*/
		sp = parsefield(sp,workword,':',MAXWORDSIZE);
		if( ! workword[0] ) Xstrncpy(workword,tmpword,MAXWORDSIZE);

/*
		if( tmpword[0] ) set_workword(Gkword,tmpword);
*/
		sp = parsefield(sp,lemma_of(Gkword),':',MAXWORDSIZE);
		sp = parsefield(sp,stemkeys,' ',LONGSTRING);
		subchar(stemkeys,':',' ');

/*	
		Xstrncpy(workword,workword_of(Gkword),MAXWORDSIZE);
*/
		set_stem(Gkword,workword );
		hits += IndeclWorks(Gkword,stemkeys);
		while(*keys && ! isspace(*keys) ) keys++;
		while(isspace(*keys)) keys++;

	}
	finish:

/*
		xFree(keybuf,"keybuf");
		xFree(workword,"workword");
		keybuf = workword = NULL;
*/

	return(hits);
}

static
IndeclWorks(gk_word *Gkword, char *keys)
{
	int i;
	int rval = 0;
	gk_word * GenIrregForm();
	gk_word * Forms;

/*
printf("keys [%s] workword [%s]\n", keys, workword ); getchar();
*/
	Forms = GenIrregForm(Gkword,keys,INDECL);

	if( Forms ) {
		rval += CheckGenWords(Gkword,Forms);
		FreeGkString(Forms);
	} /* else
		ErrorMess("Forms was null!"); 
	*/
	return(rval);
}
