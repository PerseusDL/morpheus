#include <gkstring.h>

static gk_string * StoreGstr;
#define MAXENDINGS 	10000

#include "stor.proto.h"
static cur_endcnt = 0;
static int maxstring = 0;
gk_string * CreatGkString();
int dictstrcmp();
int CompByDictStr(const void *gstr1, const void *gstr2);
 int
 CompGkString(const void *gstr1, const void *gstr2);

InitGstrMem(void)
{
	if( ! StoreGstr ) {
		if( (StoreGstr = (gk_string *) 	CreatGkString(MAXENDINGS+1)) == NULL ) {
			return(0);
		}
	}
	cur_endcnt = 0;
	return(1);
}

 AddNewGstr(gk_string *gstr)
{
	char * news;
	Dialect d;
	
	news = gkstring_of(gstr);


/*
	if( (d=AndDialect((Dialect)(ATTIC),dialect_of(gstr))) < 0) {
			return;
	}
*/
	if( cur_endcnt >= MAXENDINGS ) {
		fprintf(stderr,"Hey! you only have space for %d endings!\n", MAXENDINGS );
		fprintf(stderr,"Change to variable MAXENDINGS to reflect the actual number you want!\n");
		return(-1);
	}
	if( strlen(news) + 1 >= maxstring )
		maxstring = strlen(news) + 1;
	if( *news != '*' )
		stripzeroend(news);

	hyphtodiaer(news);
/*
	stripchar(news,'-');
*/
	stripchar(news,'!');

	*(StoreGstr+cur_endcnt) = *gstr;
	cur_endcnt++;


}

ResetGstrBuf()
{

	cur_endcnt = 0;
}

 PrntNewGstrings(FILE *f, int compiled_flag)
{
	int rval, i;
	char tmp[LONGSTRING];
	char line[LONGSTRING*2];
	char res[LONGSTRING*2];
	int deriv, indeclform;
	
	indeclform = has_morphflag(morphflags_of(StoreGstr),INDECLFORM);
	
	deriv = has_morphflag(morphflags_of(StoreGstr),IS_DERIV);

	if( compiled_flag ) {
		set_endheader(f,maxstring);
		/*
		 * do not resort forms if you are processing suffixes. leave them in the
		 * order in which they naturally appear
		 */
		 	if( ! deriv )
				qsort(StoreGstr,(size_t)cur_endcnt,(size_t)(sizeof * StoreGstr),CompByDictStr);
	} else if( ! deriv ) {
		qsort(StoreGstr,(size_t)cur_endcnt,(size_t)(sizeof * StoreGstr),CompGkString);
	}
	
		
	for(i=0;i<cur_endcnt;i++) {
		line[0] = tmp[0] = 0;
		if( compiled_flag ) {
			if( deriv )
				zap_morphflag(morphflags_of(StoreGstr+i),IS_DERIV);

			rval =  WriteEnding(f,StoreGstr+i , maxstring );
			if( deriv )
				add_morphflag(morphflags_of(StoreGstr+i),IS_DERIV);
		} else {
/* 
 * grc 1/11/96
 * handle this in the postprocessing stage
			if( i > 0 && new_parad(StoreGstr+i-1,StoreGstr+i) && ! deriv) {
				fprintf(f,"\n");
			}
 */
			LPrntGstr(StoreGstr+i,f);
		}
	}
}

LPrntGstr(gk_string *gstr, FILE *f)
{
	char tmp[256], res[256], line[256];
	int indecl;
	
	tmp[0] = line[0] = res[0] = 0;
	indecl = has_morphflag(morphflags_of(gstr),INDECLFORM);
	if( has_morphflag(morphflags_of(gstr),IS_DERIV) || indecl ) {
		zap_morphflag(morphflags_of(gstr),IS_DERIV);
		zap_morphflag(morphflags_of(gstr),INDECLFORM);
		SprintGkFlags(gstr,tmp," ",0);
		sprintf(line,"%s  %s\n", gkstring_of(gstr), tmp );
	
		if( indecl ) {
			if( Is_verbform(gstr) ) fprintf(f,":vb:");
			else fprintf(f,":wd:");
		}
		fprintf(f,"%s", line );
	} else {
		SprintGkFlags(gstr,tmp," ",0);
		if( cur_lang() == LATIN  || cur_lang() == ITALIAN )
			sprintf(line,"%s%s\n", gkstring_of(gstr), tmp );
		else
			sprintf(line,"<G>%s</G>%s\n", gkstring_of(gstr), tmp );
/*	
		beta2smarta(line,res);
		fprintf(f,"%s", res );
 */
		fprintf(f,"%s", line );
	}
}

new_parad(gk_string *gstr1, gk_string *gstr2)
{
	word_form wf1, wf2;
	
	wf1 = forminfo_of(gstr1);
	wf2 = forminfo_of(gstr2);
	
	if( tense_of(wf1) != tense_of(wf2) ||
		mood_of(wf1) != mood_of(wf2) ||
		voice_of(wf1) != voice_of(wf2) )
			return(1);
			
	if( gender_of( wf1 ) != gender_of(wf2) && dialect_of(gstr1) != dialect_of(gstr2) )
			return(1);
	return(0);
}

/*
 * grc 7/19/89
 *
 * this lets us turn "a-i" into "ai+".
 *
 * added so that we would be able to analyze "gh/rai+".
 */
hyphtodiaer(char *news)
{
	register char * s= news;
		
	while(*s) {
		if(*s=='-' ) {
			strcpy(s,s+1);
			if( is_diphth(s,news) ) {
				cinsert(DIAERESIS,s+1);
			}
		}
		s++;
	}
}
