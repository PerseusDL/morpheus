#include <stdio.h>
#include <stdlib.h>
#include <gkstring.h>

#include <gkdict.h>
#define MAX_END_TABLE 150000

gk_word GkWord;
gk_word BlnkWord;
gk_string Gstr;
gk_string AvoidGstr;
gk_string Blnk;
char ** stems;

int index_stems(int, int, int,char *, char* ,int);
int wantstem, wantirrverb, wantindecl;
char * wlist, *indexlist;
int indfreq;
void * zogalloc(size_t, size_t);


#define BIGSTRING BUFSIZ * 5

static long stemcount = 0;
/*
	int zstrcmp(void *, void *); 
*/
#define DELIMITER " "

#include "indexstems.proto.h"
static do_index(char *file, int indfreq);
long bufsiz =  0;
long bufcount = 0;
char * bufptr;
char * sptr;

/*
FILE * ferrfile;
*/

static long curcomp = 0;

int zstrcmp(const void * s1, const void * s2)
   {
	int rval =0;
	
	char **p1 = (char **)  s1;
	char **p2 = (char **)  s2;
	
	rval = morphstrcmp(*p1,*p2);
/*
	if( ! ( curcomp++ % 4000 ) ) fprintf(stderr,"%d:  [%s] [%s]\n", rval , *p1 , *p2 );
*/

	return(rval);
}


index_hqdict(int wantstem, int wantirrverb, int wantindecl)
{
	index_stems(wantstem,wantirrverb,wantindecl,WORDLIST,STEMLIST,1);
}

index_noms(int wantstem, int wantirrverb, int wantindecl)
{
	index_stems(wantstem,wantirrverb,wantindecl,NOMLIST,NOMINDEX,(int)10);
}

index_vbs(int wantstem, int wantirrverb, int wantindecl)
{
	index_stems(wantstem,wantirrverb,wantindecl,VBLIST,VBINDEX,(int)10);
}

int
index_stems(int wantstem, int wantirrverb, int wantindecl, char *wlist, char *indexlist, int indfreq)
{

	char curlemma[MAXWORDSIZE];
	char curstem[MAXWORDSIZE];
	char basename[BIGSTRING];
	char line[BIGSTRING];
	char tmp[BIGSTRING];
	FILE * finput;
/*
	char errfile[BIGSTRING];
*/
	long i;
	char *s;
	
	stemcount = 0;
	basename[0] = line[0] = 0;


	
	if(! (finput=fopen(wlist,"r"))) {
			fprintf(stderr,"Could not open %s\n", wlist );
			return(-1);
	}
/*	
	sprintf(errfile,"%s.error", wlist );
	if(! (ferrfile=MorphFopen(errfile,"w"))) {
			fprintf(stderr,"Could not open %s\n", errfile );
			return(-1);
	}
*/	
	stems = (char **) calloc((size_t)MAX_END_TABLE,(size_t)sizeof *stems);
	if( ! stems ) {
		fprintf(stderr,"could not allocate %ld stems\n", MAX_END_TABLE );
		exit(-1);
	}

	
/* 
 * make sure we are in the right kind of file!
 */
	while( (s=fgets(line,(int)BIGSTRING,finput))) {
		if( ! strncmp(line,":le:",4) ) {
			nextkey(line+4,curlemma);
			break;
		}
	}
	
	bufsiz = (long)fseek(finput,0L,2);
	bufsiz = ftell(finput) * 2;
	printf("bufsiz %ld bytes\n", bufsiz );
	fseek(finput,0L,0);

	bufptr = (char *)malloc((size_t)bufsiz);
	if( ! bufptr ) {
		printf("could not allocate %ld bytes\n", bufsiz );
		exit(-1);
	}
	printf("allocated %ld bytes successfully!\n", bufsiz );
	sptr = bufptr;
	
	while(fgets(line,(int)BIGSTRING, finput )) {

		if( ! strncmp(line,":le:",4) ) {
		
			nextkey(line+4,curlemma);
			basename[0] = 0;
			continue;
		}
		if( line[0] == '@' ) {
			if( ! basename[0] ) continue;
			strcpy(tmp,basename);
			strcat(tmp," ");
			strcat(tmp,line+1);
			strcpy(line,tmp);
		}
		/*
		 * the stem index does not include compound
		 * verbs. it assumes that the simplex entry will
		 * have all the possible stems, and that morpheus
		 * will be able to find the compound lemma all by itself.
		 *
		if( is_substring("pb:",line) )
			continue;*/

		if( (! strncmp(line,":vs:",4) || 
			! strncmp(line,":aj:",4) ||
			! strncmp(line,":no:",4)) ) {
			char tag[12];
			
			strncpy(tag,line,4);
			if( ! strncmp(line,":aj:",4) || ! strncmp(line,":no:",4) ) {
				char * t = basename;
				strcpy(basename,line);
				while(*t&&!isspace(*t)) t++;
				while(isspace(*t)) t++;
				while(*t&&!isspace(*t)) t++;
				*t = 0;
			} else
				basename[0];
			nextkey(line+4,curstem);
 			if( ! do_curstem(tag,curstem,curlemma,line+4,"") )
 				break;
		} else if( ! strncmp(line,":vb:",4)) {
			char tag[12];
			strncpy(tag,line,4);
			nextkey(line+4,curstem);
 			if( ! do_curstem(tag,curstem,curlemma,line+4,"1") ) 
 				break;

		} else if( ! strncmp(line,":wd:",4) ) {
			char tag[12];
			

			strncpy(tag,line,4);
			nextkey(line+4,curstem);
 			if( ! do_curstem(tag,curstem,curlemma,line+4,"2") ) 
 				break;

		} else if( ! strncmp(line,":de:",4) ) {
			char tag[12];
			strncpy(tag,line,4);
			nextkey(line+4,curstem);
/*
 * grc 7/6/89
 *
 * for an entry such as ":de:b azw pres_redupl", do not even bother 
 * trying to store this as a productive deriv type.
 */
			if( ! is_presredupl(line) )  {
	 			if( ! do_curstem(tag,curstem,curlemma,line+4,"3") ) 
	 				break;
			}
		}	

	}
	fclose(finput);
	printf("stemcount %ld\n", stemcount );
	
	if( wantstem ) {
		do_index(indexlist,indfreq);
	}
}
		
static
do_index(char *file, int indfreq)
{
	FILE * foutput;
/*
	char curkey[BIGSTRING];
	char prevkey[BIGSTRING];
	char curtag[BIGSTRING];
	char prevtag[BIGSTRING];
*/
	char *curkey;
	char *prevkey;
	char *curtag;
	char *prevtag;
	long i;
	char ** table;
	
	curkey = malloc(BIGSTRING);
	prevkey = malloc(BIGSTRING);
	curtag = malloc(BIGSTRING);
	prevtag = malloc(BIGSTRING);
	
	table = stems;



	qsort(table,(size_t)stemcount,sizeof * table, zstrcmp );
	
/*
 	lqsort((char **)table,stemcount,(int) sizeof * table, xstrcmp );
*/
fprintf(stderr,"out of qsort\n");

	if(! (foutput=MorphFopen(file,"w"))) {
		char tmp[256];
		
		sprintf(tmp,"Could not open %s!", file );
		ErrorMess(tmp);
		return(-1);
	}
	
	prevtag[0] = 0;
	for(i=0;i<stemcount;i++) {

if( ! (i % 5000 ) ) printf("processing %ld: %s\n", i , *(table+i) );

		nextkey(*(table+i),curtag);
		
		/*
		 * if a new keys
		 */
		if( morphstrcmp(curtag,prevtag) ) {
			if( prevtag[0] ) fprintf(foutput,"\n");
			fprintf(foutput,"%s%s%s", curtag, DELIMITER, *(table+i) );
		} else if ( strcmp(prevkey,*(table+i) ) )
			/*
			 * don't include lines such as "uiais perf_act perf_act"
			 * where the same key is repeated
			 */
			fprintf(foutput,"%s%s", DELIMITER, *(table+i) );
		strcpy(prevtag,curtag);
		strcpy(prevkey,*(table+i));
	}
fprintf(stderr,"done with i=%ld, %ld\n", i , stemcount-i);
	fclose(foutput);
fprintf(stderr,"about to index [%s]\n", file);
/*
	free(bufptr);
*/
	index_list(file,"",indfreq);
fprintf(stderr,"have just indexed [%s]\n", file);

/*
	for(i=0;i<stemcount;i++) free(*(table+i));
*/
	free(table);

}




add_newstemkey(char *s)
{
	if( stemcount >= MAX_END_TABLE ) {
		fprintf(stderr,"more than %d endings in table! bye!\n", MAX_END_TABLE );
		return(0);
	}
/*
	*(stems+stemcount) = calloc((size_t)strlen(s)+1,sizeof ** stems );
	if( ! *(stems+stemcount) ) {
*/
	*(stems+stemcount) = sptr;
	if(  bufcount > bufsiz ) {
		fprintf(stderr,"no memory left with %ld stems!\n", stemcount );
		return(0);
	}
	*(sptr) = 0;
	strcpy(*(stems+stemcount),s);
	while(*sptr) {
		sptr++;
		bufcount++;
	}
	if( ! * sptr ) sptr++;
	
	if( ! (stemcount % 1000 ) ) 	fprintf(stderr,"%ld) [%s]\n", stemcount ,s );
	stemcount++;
	return(1);
}

do_curstem(char *tag, char *curstem, char *curlemma, char *curline, char *prefix)
{

	char markedstem[BIGSTRING];
	int rval = 0;

	
	GkWord = BlnkWord;

	Gstr = Blnk;
	AvoidGstr = Blnk;	
	
	clear_globs(curline);
	rval = ScanAsciiKeys((char *)curline,&GkWord,&Gstr,&AvoidGstr);
/*
	if( ! stemtype_of(&Gstr) ) {
		fprintf(stderr,"no stemtype in:%s\n", curline );
		fprintf(ferrfile,"no stemtype in:%s\n", curline );
	}
*/	
	if( has_morphflag(morphflags_of(prvb_gstr_of(&GkWord)),ROOT_PREVERB) ) 
		add_morphflag(morphflags_of(&Gstr),ROOT_PREVERB);
/*
if(preverb_of(&GkWord)[0] )
	printf("if preverb_of(Gkword)[0] [%s]\n", preverb_of(&GkWord) );
*/
	
	stripstemsep(curstem);
	stripshortmark(curstem);
	if( has_quant(curstem) || has_diaeresis(curstem) || hasaccent(curstem)) {
		strcpy(markedstem,curstem);
		stripquant(curstem);
		stripacc(curstem);
	} else
		markedstem[0] = 0;
	stripdiaer(curstem);

	if( ! dump_curstem(prefix,curstem,markedstem,curlemma,&Gstr,&AvoidGstr,preverb_of(&GkWord)) )
			return(0);
	
	if( Is_proclitic(morphflags_of(&Gstr))) {
		int rval;

	
		rval=dumpaccstem(prefix,curstem,markedstem,curlemma,&Gstr,&AvoidGstr,PENULT,preverb_of(&GkWord));
		if( rval < 0 ) 
			return(0);
		if(! rval && Is_proclitic(morphflags_of(&Gstr)))
			rval=dumpaccstem(prefix,curstem,markedstem,curlemma,&Gstr,&AvoidGstr,ULTIMA,preverb_of(&GkWord));
		if( rval < 0 ) return(0);
	}
	return(1);
}

dumpaccstem(char *prefix, char *curstem, char *markedstem, char *curlemma, gk_string *gstr, gk_string *avoidgstr, int syllnum, char *preverb)
{
	char * p, * getsyll();
	char tmpmarked[MAXWORDSIZE];
	char tmpstem[MAXWORDSIZE];

	if( * markedstem ) 
		strcpy(tmpstem,markedstem);
	else 
		strcpy(tmpstem,curstem);

	
	if((p=getsyll(tmpstem,syllnum)) == P_ERR)
		return(0);

	 addaccent(tmpstem,ACUTE,p);
/*	
	if( * markedstem ) {
		strcpy(tmpmarked,tmpstem);
		stripquant(tmpstem);
	} else {
		tmpmarked[0] = 0;
	}
*/
	strcpy(tmpmarked,tmpstem);
	stripquant(tmpstem);
	stripdiaer(tmpstem);
	stripacc(tmpstem);
	if( ! dump_curstem(prefix,tmpstem,tmpmarked,curlemma,gstr,avoidgstr,preverb) )
		return(-1);
		
	return(1);
}
	
dump_curstem(char *prefix, char *curstem, char *markedstem, char *curlemma, gk_string *gstr, gk_string *avoidgstr, char *preverb)
{	
	char tmp[BIGSTRING];
	char notbuf[BIGSTRING];

	set_gkstring(gstr,*markedstem ? markedstem : curstem );
	if( takes_nu_movable(gstr) && (! strcmp(prefix,"1") || ! strcmp(prefix,"2") ) ) {
			gk_string TmpGstr;
			char unmarked[MAXWORDSIZE];
			char tmpmarked[MAXWORDSIZE];
			
			TmpGstr = *gstr;
			if( * markedstem ) {
				set_gkstring(&TmpGstr,markedstem);
				add_numovable(&TmpGstr);
				strcpy(unmarked,gkstring_of(&TmpGstr));
				strcpy(tmpmarked,gkstring_of(&TmpGstr));
				stripquant(unmarked);
				stripacc(unmarked);
				stripdiaer(unmarked);
			} else {
				tmpmarked[0] = 0;
				set_gkstring(&TmpGstr,curstem);
				add_numovable(&TmpGstr);
				strcpy(unmarked,gkstring_of(&TmpGstr));
				stripquant(unmarked);
				stripacc(unmarked);
				stripdiaer(unmarked);
			}
/*
printf("numovable is [%s]\n", gkstring_of(&TmpGstr));
*/
			dump_curstem(prefix,unmarked,gkstring_of(&TmpGstr),curlemma,&TmpGstr,avoidgstr,preverb);
	}


	sprintf(tmp,"%s%s %s:%s", prefix , curstem, markedstem , curlemma );
	SprintGkFlags(gstr,tmp,":",0);
	if( *preverb ) {
		char tmp2[128];
		if( has_morphflag(morphflags_of(gstr),ROOT_PREVERB ) ) 
			sprintf(tmp2,":rpb:%s:", preverb);
		else
			sprintf(tmp2,":pb:%s:", preverb);
		
		strcat(tmp,tmp2);
	}
	notbuf[0] = 0;
	SprintGkFlags(avoidgstr,notbuf,":",0);
	if( notbuf[0] ) {
		strcat(tmp,":not");
		strcat(tmp,notbuf);
	}

	return (add_newstemkey(tmp));
}

clear_globs(char *s)
{
	while(*s) {
		if( *s == ',' )
			*s = ' ';
		s++;
	}
}

is_presredupl(char *s)
{
	if( is_substring("pres_redupl",s) )
		return(1);
	return(0);
}

huh(void)
{
	getchar();
}

