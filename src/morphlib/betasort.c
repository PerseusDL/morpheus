#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "morphstrcmp.proto.h"
/*
 * grc's brute force beta search routine
 *
 * 6/27/94
 */

char *bufp;
#define TABSIZE 100000
char ** key_table;

int zstrcmp(const void * s1, const void * s2)
   {
        int rval =0;

        char **p1 = (char **)  s1;
        char **p2 = (char **)  s2;

        rval = betastrcmp(*p1,*p2);
/*
        fprintf(stderr,"%d:  [%s] [%s]\n", rval , * p1 , *p2 );
*/
        return(rval);
}


main(argc,argv)
int argc;
char * argv[];
{
	int nblocks;
	int nkeys;
	int pindex;
	FILE * finput;
	char * s, *t;
	int i = 0;
	size_t nlen = 0;
	char line[10240];

	nblocks = 1;
	nkeys = 0;
	if(argc==1) {
		finput = stdin;
	} else if( argc == 2 ) {
		if( !(finput=fopen(argv[2],"r") ) ) {
			fprintf(stderr,"Could not open [%s]!\n", argv[2] );
			exit(-1);
		}
	}


	key_table = (char **)calloc((size_t)TABSIZE,sizeof * key_table);

	while(fgets(line,sizeof line, finput)) {
		nlen = strlen(line);
		line[nlen-1] = 0;
		if( nkeys >= (TABSIZE*nblocks) - 1 ) {
			nblocks ++;
			key_table = (char **) realloc((char **)key_table,(size_t)(TABSIZE*nblocks*(sizeof * key_table)));
		}
		s = (char *) malloc(nlen);
		*(key_table+nkeys) = s;
		strcpy(*(key_table+nkeys),line);
		nkeys++;

	}
	fclose(finput);


	qsort(key_table,(size_t)nkeys,sizeof *key_table,zstrcmp);
	for(i=0;i<nkeys;i++) {
		printf("%s\n", *(key_table+i) );
	}
		
/*

	s = bufp;
	while(*s) {
		putchar(*s++);
	}
*/
}

