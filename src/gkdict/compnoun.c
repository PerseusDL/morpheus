#include <stdio.h>
#include <gkdict.h>
#include <gkstring.h>

int is_nomhead(char * heads,char * headkeys);

checkforcompnoun(char * curstem,char * endkeys,char * stemkeys)
{
	char *s = curstem;
	char headkeys[BUFSIZ];
	int n = 0;
	char firsth[BUFSIZ];

	if(*s) s++;

	while(*s) {
		if( strlen(s) < 3 ) break;
		if( (Is_vowel(*(s-1))||Is_vowel(*s) ||Is_breath(*(s-1)) ) && is_nomhead(s,headkeys) ) {
			printf("[%s] [%s] [%s]\n", curstem, headkeys , endkeys);
			n = comstemtypes(curstem,headkeys,endkeys);
			strcpy(firsth,curstem);
			firsth[strlen(curstem)-strlen(s)] = 0;
			if(n) {
				char * p;
				p = headkeys;
				while(*p) {
					while(isspace(*p)) p++;
					if(!*p) break;
					printf("%s-", firsth);
					if(*p==':') p++;
					while(*p&&!isspace(*p)) putchar(*p++);
					putchar('\n');
				}
			}
		}
		s++;
	}
}

#define MAXTAILS 10000
char *headtab[MAXTAILS];
static int init_headtab = 0;
static int nheads = 0;

setup_headtab()
{
	FILE * fheads;
	char line[1000];

	if( init_headtab ) return(1);
	if(!(fheads=fopen(COMPHEADS,"r"))) {
		fprintf(stderr,"could not open [%s]\n", COMPHEADS ); 
		return(0);
	}
	while(fgets(line,sizeof line,fheads) ) {
		if( line[0] != '#' ) continue;
		headtab[nheads] = malloc(strlen(line));
		line[strlen(line)-1] = 0;
		strcpy(headtab[nheads],line+1);
		nheads++;
	}
	fclose(fheads);
	init_headtab = 1;
	return(1);
}

is_nomhead(char * heads,char * headkeys)
{
	int rval = 0;
	char tmphead[BUFSIZ];
	char tmptab[BUFSIZ];
	int i;
	char *s;

	if( ! init_headtab ) setup_headtab();
	strcpy(tmphead,heads);
	stripacc(tmphead);
	strcat(tmphead,"\t");

	headkeys[0] = 0;
	for(i=0;i<nheads;i++) {
		strcpy(tmptab,headtab[i]);
		stripquant(tmptab);
		if( !strncmp(tmptab,tmphead,strlen(tmphead)) ) {
			s = headtab[i]+strlen(tmphead)-1;
			while(isspace(*s)) *s++ = ':';	
			while(*s&&!isspace(*s)) s++;
			while(isspace(*s)) *s++ = ':';	
			strcat(headkeys,headtab[i]);
			strcat(headkeys," ");
			rval = 1;
		} 
	}
	return(rval);
}
