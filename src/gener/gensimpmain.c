#include <stdio.h>


main()
/*
main(argc,argv)
int argc;
char * argv[];
*/
{
	char filename[80];
	char outfile[80];
	FILE * f;
	FILE * fout;
	FILE * fneed;
	int i = 0;
	

	strcpy(filename,"morphfile");
	if( (f=fopen(filename,"r")) == NULL ) {
		fprintf(stdout,"Filename?\n" );
		gets(filename);
		if( (f=fopen(filename,"r")) == NULL ) {
			fprintf(stderr,"Could not open [%s]\n", filename );
			exit(-1);
		}
	}
/*
	if(argc == 1 )
		strcpy(filename,"morphfile");
	else
		strcpy(filename,argv[2] );
	if( (f=fopen(filename,"r")) == NULL ) {
		fprintf(stderr,"Could not open [%s]\n", filename );
		exit(-1);
	}
*/	
	sprintf(outfile,"%s.out", filename );
	if( (fout=fopen(outfile,"w")) == NULL) {
		fprintf(stderr,"could not open [%s]\n", outfile );
		exit(-1);
	}

	sprintf(outfile,"%s.needs", filename );
	if( (fneed=fopen(outfile,"w")) == NULL) {
		fprintf(stderr,"could not open [%s]\n", outfile );
		exit(-1);
	}

	 GenSimplex(f,fout,fneed);
	 if (fout != stdout) fclose(fout);
	 fclose(fneed);
/*while( GenNxtWord(f,0,fout) );*/
}

