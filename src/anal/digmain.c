#include <stdio.h>
#include <ctype.h>
#include <prntflags.h>
#include <gkdict.h>
FILE * MorphFopen();
#include "stdiomorph.proto.h"
int quickflag = 0;
char * anal_buf();
long prevmemory = 0;

main(void)
{
	FILE * finput, *foutput;
	char line[BUFSIZ*4];
	char fname[BUFSIZ],inpname[BUFSIZ], outname[BUFSIZ];
	
	int rval;
	long freemem = 0;
	long nwords = 0;
	long nhits = 0;
	char * p;


	fprintf(stderr,"use stdout? ");
	gets(line);
	
	if(line[0] == 'y' ) {
		fprintf(stderr,"type in forms\n");
		strcpy(outname,"out.morph");
		finput = stdin;
	} else {
		if((finput=MorphFopen(NOMINDEX,"r")) == NULL) {
			fprintf(stderr,"cannot find [%s]!\n", NOMINDEX);
			exit(-1);
		}
/*
		fprintf(stderr,"word file? ");
		gets(fname);
		
		strcpy(inpname,fname);
		strcat(inpname,".words");
		
		strcpy(outname,fname);
		strcat(outname,".morph");

		if((finput=fopen(inpname,"r")) == NULL) {
			fprintf(stderr,"cannot find [%s]!\n", inpname);
			exit(-1);
		}
	
*/
	
	}

	if( (foutput=fopen("stem.t","w")) == NULL) {
		fprintf(stderr,"cannot find [%s]!\n", outname);
		exit(-1);
	}


	while(fgets(line,(int)sizeof line,finput)) {
if(isdigit(line[0]) || line[0] == '*') continue;
		trimwhite(line);
		trimdigit(line);
		p = line;

/*
		while(*p&&!isspace(*p)) p++;
		if(*p) *p++ = 0;
*/
		checkcmpstem(line,p,foutput);
		nwords++;
		if( rval ) {
			nhits++;
		}
if(! ( nwords % 10) )
	fprintf(stderr,"%ld %ld %0.2f %s %d\n", 
nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval  );
	}
	if( finput != stdin )
		fclose(finput);
	fclose(foutput);
}

trimdigit(char *s)
{
	char * p = s;
	while(*s) s++;
	s--;
	while(isdigit(*s)&&s>p) *s-- = 0;
}
