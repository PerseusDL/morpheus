#include <stdio.h>
#include <ctype.h>
#include <prntflags.h>

#include "stdiomorph.proto.h"
int quickflag = 0;
char * anal_buf();
long prevmemory = 0;

main(void)
{
char fname[BUFSIZ];
fprintf(stdout,"hello world!\n");
		while(1) {
			fprintf(stderr,"fname? ");
			if( ! gets(fname) ) break;
			crunchfile(fname);
		}
	
}

crunchfile(s)
char *s;
{
	FILE * finput, *foutput;
	char line[BUFSIZ*4];
	char inpname[BUFSIZ], outname[BUFSIZ];
	
	int rval;
	long freemem = 0;
	long nwords = 0;
	long nhits = 0;
	char * p;
		
		strcpy(inpname,s);
		strcat(inpname,".words");
		
		strcpy(outname,s);
		strcat(outname,".morph");

		if((finput=fopen(inpname,"r")) == NULL) {
			fprintf(stderr,"cannot find [%s]!\n", inpname);
			exit(-1);
		}
	

	
	
	if( (foutput=fopen(outname,"w")) == NULL) {
		fprintf(stderr,"cannot find [%s]!\n", outname);
		exit(-1);
	}

	while(fgets(line,(int)sizeof line,finput)) {
/*
		printf("%s %s %d\n", line, prevl , dictstrcmp(line,prevl) );
		strcpy(prevl,line);
		continue;
*/		
		trimwhite(line);
		trimdigit(line);
		p = line;
		while(*p&&!isspace(*p)) p++;
		if(*p) *p = 0;

		rval = checkstring(line,(PrntFlags)SHOW_LEMMA,foutput);
/*
		rval = checkstring(line,(PrntFlags)DBASEFORMAT,foutput);
		rval = checkstring(line,(PrntFlags)SHOW_FULL_INFO);
*/
		nwords++;
		if( rval ) {
			nhits++;
			fprintf(foutput,"%s",anal_buf() );
		} else {
			printf(":failed %s\n", line );
			fprintf(foutput,":failed %s\n", line );
		}
/*
freemem = (long) FreeMem();
fprintf(stderr,"%ld %ld %0.2f %s %d %ld %ld \n", 
nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval , freemem , prevmemory - freemem );
		prevmemory = freemem;
*/
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
