#include  <usual.h>
#include  <token.h>

#define  MAXLINE  80
#define  MAXKEY  100

TKtree  Tree;
short  compiled = 0;
short  sval = 0;
short  ret;

main(argc,argv)
int argc;
char * argv[];
{
    char  cline[MAXLINE];
    char  *keys[MAXKEY+1];
    short  clen;
    FILE * fwords;
    FILE * ftext;
    FILE * fopen();
    char *tline, *cp, *malloc();

	if( argc != 3 ) {
		printf("format:%s wordfile textfile\n", argv[0] );
		exit( -1 );
	}
	if( (fwords=fopen(argv[1] , "r")) == NULL ) {
		fprintf(stderr,"could not open %s\n", argv[1] );
		exit( -1 );
	}
	if( (ftext=fopen(argv[2] , "r")) == NULL ) {
		fprintf(stderr,"could not open %s\n", argv[2] );
		exit( -1 );
	}

	if (( Tree = tkcreate()) == NULL )  {
	    printf("Can't create Tree\n");
	    exit(1);
	}
	printf("Ready\n");
	while ( fgets(cline,sizeof cline , fwords) != NULL )  {
	    sval++;
	    clen = strlen( cline ) -1;
	    tline = malloc( clen + 1);
	    strncpy( tline, cline, clen );
	    tline[ clen ] = NUL;
	    keys[sval] = tline;
	    if ( tkenter( Tree, tline, sval ) == FAILURE )
		printf("Can't enter %s\n", tline);
	    else printf("Entered %s\n", tline);
	}
	if ( tkcompile( Tree ) == FAILURE )  {
	    printf("Can't compile machine\n");
	    exit( -1 );
	}
	fclose( fwords );
	while ( fgets(cline,sizeof cline , ftext) != NULL )  {
		    cp = cline;
		    while ( *cp!=NUL )  {
			if (( ret = tkparse( Tree, *cp )) > 0 )  {
			    printf("%s", cline);
			    cp++;
			}
			else  {
			    cp++;
			    continue;
			}
		    }
	}
fprintf(stderr,"done with text\n" );
	fclose( ftext );

	tkdestroy( Tree );
}
