#include <gkstring.h>
#include <libfiles.h>
#include "compostypes.h"

#include "expsuffmain.proto.h"

char fname[80];
static gk_string Gstr;

main(int argc, char * argv[])
{
	FILE * ffname;
	char * curtable, * NextEndTable();
	int index = 0;
	Stemtype stype = 0;
	int maintable = 1;
	int formcode = DODERIV;
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
	if( !strcmp(fname,"all") ) {
		do_all_derivs(maintable,formcode);
	} else

/*
	printf("about to compile ending type [%s]\n", fname );
*/
		expendtables(fname,maintable,formcode);
}

do_all_derivs(int maintable, int formcode)
{
	FILE * finput;
	char inpfname[MAXPATHNAME];
	char tmp[LONGSTRING];
	char derivname[LONGSTRING];

/*
	sprintf(inpfname,"rule_files%c%s",  DIRCHAR, "derivtypes.table" );
*/
	strcpy(inpfname,DERIVTYPES);
	if(! (finput=MorphFopen(inpfname,"r"))) {
		printf("could not open [%s]\n",  inpfname );
		return(-1);
	}
	
	while(fgets(tmp,sizeof tmp,finput)) {
		if( ! isalpha( tmp[0] ) ) continue;
		nextkey(tmp,derivname);
		printf("compiling deriv [%s]\n", derivname );
		
		expendtables(derivname,maintable,formcode);

	}
}
