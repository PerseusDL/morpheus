#include <gkstring.h>
#include <gkdict.h>

#include "dictstems.proto.h"

char * is_substring();

dictstems(char *lemma, int *nstems, bool wantacc, char *orgstem, char *stemtype, char *pparttab[], int maxpparts)
{
	FILE * f;
	FILE * getlemmstart();
	char *line = NULL;
	char *lemmfile = NULL;
	char *tmp = NULL;
	char cstem[MAXWORDSIZE];
	char wantstem[MAXWORDSIZE];
	char curtarget[MAXWORDSIZE * 2];
	register char * cp;
	int slen;
	long startoff;
	int gotpparts = 0;

	int anystem = 0;
	
	line = (char *)malloc((size_t)(BUFSIZ*4)+1);
	lemmfile = (char *)malloc((size_t)LONGSTRING+1);
	tmp = (char *)malloc((size_t)(BUFSIZ*4)+1);
	line[(BUFSIZ*4)+1] = lemmfile[LONGSTRING+1] = tmp[(BUFSIZ*4)+1] = 0;
	
	lemmfile[0] = 0;
	startoff = 0;

	if( stemtype == NULL || ! * stemtype )
		anystem++;

/* 
 * see if the stem that you are asking for has an accent.
 * if not, ignore any accents on stems in the dictionary.
 * 	e.g. match "i(/eis" only against "i(/eis" and not "i(ei=s",
 *	     but match "i(eis" against both "i(/eis" and "i(ei=s".
 *
	if( naccents(orgstem) ) {
		wantacc = YES;
	}
 *
 * grc 2/4/87
 * well, that complicates the search for things like enclitics.
 * if you have "e)/sti" and you want to match "e)sti" in a dictionary,
 * do you really want to have to process the flags for "e)sti" to 
 * determine it is an enclitic? better get all stems, ignoring accents,
 * and leave it to a later stage of the process to distinguish between
 * "i(/eis" and "i(ei=s".
 *
 * but wait a second
 * grc 2/12/87 
 * aha, even that won't do terribly well. suppose we want to use this
 * routine to search for things like "a)/ndres" where we damn well know
 * what the accent should be.
 *   the option "wantacc" is now an argument passed to this routine
 * telling whether or not you should pay attention to the accent.
 */
	Xstrncpy(wantstem,orgstem,(BUFSIZ*4));
	stripquant(wantstem);
	if( wantacc == NO ) 
		stripacc(wantstem);

	if( (f=getlemmstart(lemma,lemmfile,&startoff)) == NULL ) {
/*
		sprintf(tmp,"dictstems: could not find %s\n", lemma );
		ErrorMess(tmp);
*/
		gotpparts = -1;
		goto finish;
	}	

	fseek(f,startoff,0);
	/*
	 * now look for stems
	 */
	slen = Xstrlen(wantstem);
	for(gotpparts=0;fgets(line,BUFSIZ*4 , f) && gotpparts <maxpparts;) {
		if( is_blank(line) ) break;
		if( Is_comment(line) ) continue;
		if( ! morphstrncmp(line,LEMMTAG,strlen(LEMMTAG))) continue;
			

		Xstrncpy(tmp, line + 4,(BUFSIZ*4));
		nextkey(tmp,cstem);

		if( wantacc == NO )
			stripacc(cstem);
		stripquant(cstem);
/*
 * to make sure that you don't match "bal" against "ball", check to see that
 * there is whitespace after the matched string
 */
/*
fprintf(stderr,"cstem [%s] wantstem [%s] morphstrcmp() %d\n", cstem, wantstem,
morphstrcmp(cstem,wantstem) );
*/
		(*nstems)++;

		if(!morphstrcmp(cstem,wantstem) ) {

			if( anystem ) {
				Xstrncpy(pparttab[gotpparts++],line+4,MAXWORDSIZE);
			} else if( is_substring(stemtype,tmp) )  {
				Xstrncpy(pparttab[gotpparts++],line+4,MAXWORDSIZE);
			}
		}
	}

	finish:
		if(f) {
			xFclose(f);
			f = NULL;
		}
		xFree(line,"dicts line");
		xFree(lemmfile,"dicts lemmfile");
		xFree(tmp,"dicts tmp");
		line = lemmfile = tmp = NULL;
		
		return(gotpparts);
}
