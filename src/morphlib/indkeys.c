#include <gkstring.h>
#include <endfiles.h>
#include <endtags.h>
#define DECALPHA 1

#include "indkeys.proto.h"


char curkey[LONGSTRING];
char prevkey[LONGSTRING];
int nkeys = MODULUS + 1;

index_list(char *listname, char *tagstring, int modulus)
{
	FILE * finput;
	FILE * foutput;
	char outfile[BUFSIZ];
	char line[LONGSTRING*4];
	char curlemma[LONGSTRING];
	char field[LONGSTRING];
#ifdef DECALPHA
	int curoff;
#else
	long curoff;
#endif
	int i;
	int taglen;
	
	if( modulus > MODULUS ) modulus = MODULUS;
	finput = MorphFopen(listname,"r");
	if( ! finput ) {
		fprintf(stderr,"Could not open input %s\n", listname );
		return(-1);
	}
	sprintf(outfile,"%s.lindex",listname);
	
	foutput = MorphFopen(outfile,"wb");
	if( ! finput ) {
		fprintf(stderr,"Could not open output  %s\n", outfile );
		return(-1);
	}
	if( tagstring ) taglen = Xstrlen(tagstring);
	for(i=0;;i++) {
#ifdef DECALPHA
		curoff = (int)ftell(finput);
#else
		curoff = ftell(finput);
#endif
		if( ! fgets(line,sizeof line,finput) )
			break;
		if( Xstrlen(line) >= LONGSTRING ) {
			FILE * f;
			
			if( (f=fopen("inderr","a")) ) {
				fprintf(f,"fat line %d bytes:%s\n", Xstrlen(line) , line );
				fclose(f);
			}
			printf("fat line %d bytes:%s\n", Xstrlen(line) , line );
		}
		if( is_blank(line) ) continue;
		if( line[0] == '#' ) continue;
		if( tagstring ) {
			if( ! Xstrncmp(line,tagstring,taglen) ) 
			prockeyline(line+taglen,modulus,curoff,foutput);
		} else
			prockeyline(line,modulus,curoff,foutput);
	}
	fclose(finput);
	fclose(foutput);
}


static int count = 0;

#ifdef DECALPHA
prockeyline(char *s, int modulus, int curoff, FILE *f)
#else
prockeyline(char *s, int modulus, long curoff, FILE *f)
#endif
{
	char curlemma[LONGSTRING];
	char * p;
	int i;
	int prntflag = 0;

	p = s;
	
	for(i=0;i<KEYLEN;i++) {
		curkey[i] = *p++;
		curkey[i+1] = 0;
		if( (! *p) || isspace( * p ) )
			break;
	}
	
	if( ++nkeys >= modulus && morphstrcmp(curkey,prevkey) ) {
		if( prntflag )
			fprintf(stdout,"%s\t%ld\n", curkey , curoff );

		WriteKey(curkey,&curoff,f);
		nkeys = 0;
	} else {
		if( prntflag )
			printf("not writing key [%s]:nkeys %d modulus %d prev %s curkey [%s] curoff %ld\n",s,nkeys, modulus, prevkey, curkey , curoff );
	}
	Xstrncpy(prevkey,curkey,LONGSTRING);

	count++;
}
