/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"

srch_state * srch;
srch_state Srch;

#define MAXCNT 200

main(argc,argv)
int argc;
char * argv[];
{
	FILE * finput;
	char curword[256];

        if( argc != 3 ) {
                fprintf(ERRFILE, "usage:%s string author\n", argv[0] );
                exit( -1 );
        }

	if( (finput=fopen(argv[1],"r")) == NULL ) {
		fprintf(ERRFILE,"could not open [%s]\n", argv[1] );
		exit(-1);
	}

	srch = &Srch;

	srch->rflags |= SPELL_CHECK;
	strcpy(srch->sname,argv[2]);
	
	while(fgets(curword,sizeof curword,finput) ) {
		trimnl(curword);
		printf("%s", curword );
		addwdbound(curword);
		strncpy( srch->key , curword, sizeof srch->key );
		if( ! has_accent(srch->key) ) 
			printf("\tNOACC");
		if( lacks_breathing(srch->key) )
			printf("\tNOBREATH");
		if( ! PickSearch(srch) ) {
			printf("\tMISS");
			stripaccent(srch->key);
		/* for little words, strip the breathing right away,
		 * otherwise we end up with forms such as "h)=de" (from 
		 * "h(/de") being interpreted as "h)de/".
		 */
			if( strlen(srch->key) >= 5 ) {
					
				stripbreathing(srch->key);
			}
			if( ! PickSearch(srch) ) {
				stripbreathing(srch->key);
				if( ! PickSearch(srch) )
					zap_p(srch->key);
					if( ! PickSearch(srch) )
						printf("\tCLUELESS");
			} 
				
		} 
		printf("\n");
		fflush(stdout);
	}
}

trimnl(s)
register char *s;
{
	while(*s) s++;
	s--;
	if(*s=='\n') *s = 0;
}

addwdbound(s)
register char * s;
{
	char tmp[256];

	strcpy(tmp,"@");
	strcat(tmp,s);
	strcat(tmp,"@");
	strcpy(s,tmp) ;
}

/*
 * in kurzweil data entry, 'p' often covers a multitude of errors:
 * e.g. "ei)sopa=|s", "*)amfitpi/tas"
 */
zap_p(s)
char *s;
{
	if( strlen(s) < 4 )
		return;
	while(*s) {
		if( *s == 'p' ) *s = '.';
		s++;
	}
}
