#include <stdio.h>
#include <ctype.h>
#include <string.h>
void *malloc( size_t size);
void *calloc( size_t size, size_t nelems);
static got_match(char * key,char * listmemb);


static char ** commonwords;

static int inited = 0;
static int ncommon = 0;

char * check_clist();

char *
is_common(s)
char *s;
{
	char curkey[64];
	register char *p;
	
	p = curkey;
	if(*s=='@') strcpy(p,s+1);
	while(*p) p++; p--;
	if(*p == '@' ) *p = 0;

	if( ! inited ) {
		init_common();
	}
/*
	p=check_clist(curkey);
	printf("curkey [%s] p == NULL %d\n", curkey , p == NULL );
	return(p);
*/
	return(check_clist(curkey));
}

init_common()
{
	FILE * f;
	int i;
	char * getenv();
	char curword[128];
	char libdir[BUFSIZ];

	strcpy(libdir,getenv("LIBDIR"));
	if( ! libdir[0] ) {
		fprintf(stderr,"could not initialize LIBDIR!\n");
		exit(-1);
	}
	strcat(libdir,"/irreg.spell");
	if( ! (f=fopen(libdir,"r")) ) {
		fprintf(stderr,"could not open [%s]\n", libdir );
		exit(-1);
	}
	
	while(fgets(curword,sizeof curword,f)) {
		if( isalpha(curword[0]) )
			ncommon++;
	}
	
	commonwords = (char **) calloc((size_t)(ncommon+1),sizeof * commonwords );

	fseek(f,0L,0);
	for(i=0;;i++) {
		if( ! fgets(curword,sizeof curword,f) )
			break;
		if( isalpha(curword[0]) ) {
			int n;

			n = strlen(curword);
			curword[n-1] = 0; /* zap '\n' */
			n--;
			*(commonwords+i) = (char *) malloc((size_t)(n+1));
			strcpy(*(commonwords+i),curword);
		}
	}
	fclose(f);

	inited++;
}

char *
check_clist(s)
char *s;
{
	int i;

	for(i=0;i<ncommon;i++) {
		if( got_match(s,*(commonwords+i)))
			return(*(commonwords+i));
		
	}
	return(NULL);
}


static 
got_match(char * key,char * listmemb)
{
	while(*key) {
		if( ! * listmemb )
			return(0);
		if( *key == *listmemb ) {
			key++; listmemb++;
			continue;
		}
		if(!isalpha(*listmemb)) {
			while(*listmemb&&!isalpha(*listmemb))
				listmemb++;
			continue;
		}
		return(0);
	}
	while(*listmemb&&!isalpha(*listmemb)) listmemb++;
	if( !*listmemb)
		return(1);
	return(0);
}
