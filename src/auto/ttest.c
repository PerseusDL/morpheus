#include  <usual.h>
#include  <token.h>

#define  MAXLINE  80
#define  MAXKEY  100

TKtree  Tree;
short  compiled = 0;
short  sval = 0;
short  ret;

main()
{
    char  cline[MAXLINE];
    char  *keys[MAXKEY+1];
    char *tline, *cp, *malloc();

	if (( Tree = tkcreate()) == NULL )  {
	    printf("Can't create Tree\n");
	    exit(1);
	}
	printf("Ready\n");
	while ( gets(cline) != NULL )  {
	    if ( !strcmp( cline, "compile" ))  {
		if ( tkcompile( Tree ) == FAILURE )  {
		    printf("Can't compile machine\n");
		    continue;
		}
		else  {
		    printf("Compiled machine\n", tline);
		    compiled++;
		}
	    }
	    else  {
		if ( !compiled )  {
		    sval++;
		    tline = malloc( strlen(cline) + 1);
		    strcpy( tline, cline);
		    keys[sval] = tline;
		    if ( tkenter( Tree, tline, sval ) == FAILURE )
			printf("Can't enter %s\n", tline);
		    else printf("Entered %s\n", tline);
		}
		else  {
		    cp = cline;
		    while ( *cp!=NUL )  {
			if (( ret = tkmatch( Tree, *cp )) > 0 )  {
			    printf("Recognized %s\n", keys[ret]);
			    while (( ret = tknext( Tree )) > 0 )
				printf("Recognized %s\n", keys[ret]);
			    cp++;
			}
			else  {
			    cp++;
			    continue;
			}
		    }
		}
	    }
	}

	tkdestroy( Tree );
}
