#include <gkstring.h>
#include <morphargs.h>
#include <stdio.h>
#define STEMFILE "gkdict/indices/stindex"
#define WORDLEN 4
#define HASHLEN 10000

#include "testmain.proto.h"
/*
int hashtab[HASHLEN];
*/
static int * hashtab;

main(void)
{
	char sbuf[128];
	char rbuf[128];
	
		
/*
	mySFGetFile(sbuf);
	printf("sbuf [%s]\n", sbuf );
*/
	ErrorMess("num is %d for %s", 1, "fred");

/*	index_list(WORDLIST,":le:",5);*/
/*	index_list(STEMLIST,"",1);*/
/*
	while(gets(sbuf)) {
		beta2smk(sbuf,rbuf);
		printf("rbuf:%s\n", rbuf );
	}
*/
}
