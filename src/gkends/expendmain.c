#include <gkstring.h>
char fname[80];
static gk_string Gstr;
#include "compostypes.h"

#include "expendmain.proto.h"

main(argc,argv)
int argc;
char * argv[];
{
	FILE * ffname;
	char * curtable, * NextEndTable();
	int index = 0;
	int formcode = DOEND;
	Stemtype stype = 0;
	int maintable = 0;
	int rval = 0;
	int c, errflg = 0;

	

	while (!errflg && (c = getopt(argc,argv,"IL")) != -1) {
		switch (c) {
			case 'I':
				set_lang(ITALIAN);
				break;
			case 'L':
				set_lang(LATIN);
				break;
			default:
				break;
		}
	}

	if( argc > 3 || argc == 1) {
		fprintf(stderr,"format:%s {ARGS} basename\n", argv[0] );
		exit(-1);
	}
	strcpy(fname,argv[argc-1]);
	rval = strcmp(fname,"formulaX");
	if( rval) 
		maintable = 1;

/*
	printf("about to compile ending type [%s]\n", fname );
*/

	if( ! strcmp("all",fname) )
		stype = NOUNSTEM|ADJSTEM|PPARTMASK; 
	else if( ! strcmp("nom",fname) ) {
		stype = NOUNSTEM|ADJSTEM;
	} else if( ! strcmp("verb", fname ) )
		stype = PPARTMASK;
	else {
		/*
		ScanAsciiKeys(fname,NULL,&Gstr,NULL);
		stype = stemtype_of(&Gstr);
		*/
		expendtables(fname,maintable,formcode);
		exit(1);
	}

	while( (curtable=NextEndTable(&index,stype))) {

/*
		printf("about to compile [%s]\n", curtable );
*/

		expendtables(curtable,maintable,formcode);
	}
}
