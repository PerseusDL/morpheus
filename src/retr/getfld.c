#include "srchstate.h"
#define WLIST "/text/tlgdb/bigind.ind"
FILE * fwlist = NULL;
long int curlno = 0;


main()
{
	char line[BUFSIZ];
	
	InitBigind();
	gkcmpinit();
	if( (fwlist = fopen(WLIST,"r")) == NULL ) {
		fprintf(stderr,"could not open [%s]\n", WLIST );
		exit(-1);
	}
	while(gets(line)) {
		checkfld(line);
	}

	fclose(fwlist);
}


checkfld(s)
char *s;
{
	char curl[BUFSIZ];
	char * t;
	int n;
	srch_state * TmpSrch;

        if( ! TmpSrch ) {
                TmpSrch = (srch_state * )Calloc(1,sizeof * TmpSrch);
                if( ! TmpSrch ) {
                        fprintf(stderr,"Dump:Could not allocate TmpSrch \n");
                        return(-1);
                }
        }

	while(fgets(curl,sizeof curl,fwlist)) {
		curlno++;
/*
		if(curl[0] == '*' ) {
			continue;
		}
*/
		t = curl;
		while(*t) t++; t--; *t = 0;
		n = gk_strcmp(s,curl);	
		if( !n && ! strcmp(s,curl) ) {
			strcpy( TmpSrch->key , curl );
			strcpy( TmpSrch->gotstr , curl );
/*
printf("%s = %s at %ld\n", s, curl, curlno );
*/
			thesaur(stdout,TmpSrch,curlno,curl);
			return;
		} else if( n < 0 ) {
			if( char_strcmp(s,curl) < 0 ) {
				fprintf(stderr,"quit %d:  %s = %s at %ld\n", n, s, curl, curlno );
				return;
			}
		}
		
	}
}

char_strcmp(s1,s2)
char *s1, *s2;
{
	char tmp1[BUFSIZ], tmp2[BUFSIZ];
	char *t;

	t = tmp1;
	while(*s1) {
		if(isalpha(*s1) ) *t++ = *s1;
		s1++;
	}
	*t = 0;

	t = tmp2;
	while(*s2) {
		if(isalpha(*s2) ) *t++ = *s2;
		s2++;
	}
	*t = 0;

	return(strcmp(s1,s2));
}
