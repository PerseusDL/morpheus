#include <stdio.h>
#include <ctype.h>
#include <prntflags.h>
#include "stdiomorph.proto.h"

#include <time.h>
int quickflag = 0;
char * anal_buf();
long prevmemory = 0;
time_t start_time = 0;
time_t prev_time = 0;
time_t end_time = 0;
double avg_time = 0;
double long_time = 0;
double string_time = 0;
char long_string[BUFSIZ];
int timeit = 1;

main(argc,argv)
int argc;
char *argv[];
{
	FILE * finput, *foutput, *ffailed;
	char line[BUFSIZ*4];
	char fname[BUFSIZ],inpname[BUFSIZ], outname[BUFSIZ], failedname[BUFSIZ];
	char destPath[BUFSIZ];
	
	int rval;
	long freemem = 0;
	long nwords = 0;
	long nhits = 0;
	char * p;
/*
for(;;) {
gets(line);
		rval = chckcmpvb(line,destPath);
printf("%d:[%s] [%s]\n", rval, line ,destPath );
}
*/
	if( argc == 1)  {
		finput = stdin;
		foutput = stdout;
		ffailed = stdout;
	} else {
		strcpy(fname,argv[1]);
		strcpy(inpname,fname);
		strcat(inpname,".words");
		
/*
		fprintf(stderr,"destination directory? (press return for same as source)");
*/
		if (argc == 3) {
			strcpy(destPath,argv[2]);
			strcpy(outname,destPath);
			strcat(outname,":");
			strcat(outname,fname);
			strcat(outname,".morph");
		} else {
			strcpy(outname,fname);
			strcat(outname,".morph");
			strcpy(failedname,fname);
			strcat(failedname,".failed");
		}
		 
		fprintf(stderr,"Input: %s\nOutput: %s\n",inpname,outname);
	
		if((finput=fopen(inpname,"r")) == NULL) {
			fprintf(stderr,"cannot find [%s]!\n", inpname);
			exit(-1);
		}
	

	
	}
	if( foutput != stdout && ((foutput=fopen(outname,"w")) == NULL)) {
		fprintf(stderr,"cannot find [%s]!\n", outname);
		exit(-1);
	}
	
	if( ffailed != stdout && ((ffailed=fopen(failedname,"w")) == NULL)) {
		fprintf(stderr,"cannot open [%s]!\n", failedname);
		exit(-1);
	}
	
	while(fgets(line,(int)sizeof line,finput)) {

/*
		char * t;
		t = line;
		while(*t&&!isspace(*t)) t++;
		*t = 0;
		rval = chckcmpvb(line,destPath);
		if( ! rval ) {
			printf("failed on [%s]\n", line );
		}
*/
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

		if( timeit) {
			prev_time = clock();
			if( start_time == 0 ) start_time = prev_time;
		}
/*setatticprose();*/
/*set_nocrasis();*/
/*		rval = checkstring(line,(PrntFlags)(SHOW_LEMMA|STRICT_CASE),foutput);*/

/*		rval = checkstring(line,(PrntFlags)LEXICON_OUTPUT,foutput);*/
/*		rval = checkstring(line,(PrntFlags)SHOW_LEMMA|STRICT_CASE,foutput);*/
/*		rval = checkstring(line,(PrntFlags)(SHOW_FULL_INFO|STRICT_CASE),stdout);*/
/*		rval = checkstring(line,(PrntFlags)DBASEFORMAT,foutput);*/
		rval = checkstring(line,(PrntFlags)(PERSEUS_FORMAT/*|STRICT_CASE*/),foutput);
/*		rval = checkstring(line,(PrntFlags)(DBASESHORT|STRICT_CASE),foutput);*/
/*		rval = checkstring(line,(PrntFlags)DBASEFORMAT,foutput);*/
/*		rval = checkstring(line,(PrntFlags)SHOW_FULL_INFO,foutput);*/

/*		rval = checkstring(line,(PrntFlags)SHOW_LEMMA|STRICT_CASE,foutput);*/
		

		if( timeit ) {
			end_time = clock();
			string_time = (double) (end_time - prev_time)/ CLOCKS_PER_SEC ;
			if( string_time >= long_time && nwords > 0 && rval ) {
			
				long_time = string_time;
				strcpy(long_string,line);
				fprintf(stderr,":longtime\t%.2f\t%s\n", long_time, long_string );
			}
		}

		nwords++;
		if( rval ) {
			nhits++;
			fprintf(foutput,"%s",anal_buf() );
		} else {
		/*	printf("%s\t:failed\n", line );*/
			fprintf(ffailed,"%s\n", line );
		}

if(! ( nwords % 100) ) {
	if( timeit ) {
		avg_time = (double)(end_time - start_time)/(CLOCKS_PER_SEC * (double)nwords) ;

		fprintf(stderr,":time %.2f %.2f\n", avg_time , string_time );
	}
	fprintf(stderr,"%ld %ld %0.2f %s %d\n", 
nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval  );
}
	}
	if( finput != stdin )
		fclose(finput);
	fclose(foutput);
	fclose(ffailed);
	fprintf(stderr,"FINAL:  %ld %ld %0.2f %s %d\n", 
nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval  );
	if( timeit )
		fprintf(stderr,":avg time %.2f; long time [%.2f] for [%s]\n", avg_time , long_time, long_string );

}

trimdigit(char *s)
{
	char * p = s;
	while(*s) s++;
	s--;
	while(isdigit(*s)&&s>p) *s-- = 0;
}
