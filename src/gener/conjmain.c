#include <stdio.h>
#include <gkstring.h>


main(argc,argv)
int argc;
char * argv[];
{
	char filename[80];
	char outfile[80];
	FILE * f;
	FILE * fout;
	int i = 0;
	int fullconj = 0;
	
	
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

	if(!strcmp(argv[argc-1],"full") ) {
		fullconj = 1;
	}
	
	strcpy(filename,"conjfile");
	if( (f=fopen(filename,"r")) == NULL ) {
		fprintf(stdout,"Filename?\n" );
		gets(filename);
		if( (f=fopen(filename,"r")) == NULL ) {
			fprintf(stderr,"Could not open [%s]\n", filename );
			exit(-1);
		}
	}

	if( fullconj )
		sprintf(outfile,"%s.fat", filename );
	else
		sprintf(outfile,"%s.short", filename );
	if( (fout=fopen(outfile,"w")) == NULL) {
		fprintf(stderr,"could not open [%s]\n", outfile );
		exit(-1);
	}

	 GenConjForms(f,fout,fullconj);
	 fclose(fout);
	 
}

