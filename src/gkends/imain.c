#include <gkstring.h>
static gk_string Gstr;
char fname[MAXWORDSIZE];
static gk_word Gkword;

main(argc,argv)
int argc;
char * argv[];
{
	FILE * ffname;
	Stemtype stype;
	int is_suffix = 0;
	int c, errflg = 0;
	
/*
	if( (ffname=fopen("do_end_file","r")) ) {
		while(fgets(fname,sizeof fname,ffname)) {
			if( isalpha(fname[0] ) )
					break;
		}
		fclose(ffname);
		unlink("do_end_file");
	} 
	if( ! isalpha(fname[0]) ) {
		printf("ending type? ");
		for(;;) {
			gets(fname);
			if( isalpha(fname[0] ) )
				break;
		}
	}
*/

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

	
	if( argc > 3 ) {
		fprintf(stderr,"format:%s {ARGS} type\n", argv[0] );
		exit(-1);
	}

	strcpy(fname,argv[argc-1]);
/*
	printf("about to compile ending type [%s]\n", fname );
*/
	if( ! strcmp(fname,"nom") ) {
		stype = NOUNSTEM|ADJSTEM;
	} else if( ! strcmp(fname,"verb") ) {
		stype = PPARTMASK;
	} else {
		ScanAsciiKeys(fname,&Gkword,&Gstr,NULL);
		stype = stemtype_of(&Gstr);
		if( stype & (NOUNSTEM|ADJSTEM) ) stype = NOUNSTEM|ADJSTEM;
		else if ( stype & PPARTMASK )  stype = PPARTMASK;
	}
printf("stype %o\n", stype );
	indexendtables(stype,is_suffix);
	return(0);
}

