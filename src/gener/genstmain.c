#include <stdio.h>
int quickflag = 0;

main(argc,argv)
int argc;
char * argv[];
{
	char filename[80];
	char outfile[80];
	FILE * f = NULL;
	FILE * fout = NULL;
	int i = 0;
	

	if( argc == 1 ) {
		f = stdin;
		fout = stdout;
	} else {
		if( (f=fopen(argv[1],"r")) == NULL ) {
			fprintf(stderr,"could not open [%s]\n", argv[1] );
			exit(-1);
		} 

		sprintf(outfile,"%s.out", argv[1] );
		if( (fout=fopen(outfile,"w")) == NULL) {
			fprintf(stderr,"could not open [%s]\n", outfile );
			exit(-1);
		}
	}

	 GenStemLink(f,fout);
	 if (fout != stdout) xFclose(fout);

	 
}

