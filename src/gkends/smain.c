#include <gkstring.h>

static gk_string Gstr;
char fname[MAXWORDSIZE];

main(argc,argv)
int argc;
char * argv[];
{
	FILE * ffname;
	Stemtype stype = 0;
	int is_deriv = 1;
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

	
	if( argc > 3 ) {
		fprintf(stderr,"format:%s {ARGS} type\n", argv[0] );
		exit(-1);
	}
	indexendtables(stype,is_deriv);
	return(0);
}
