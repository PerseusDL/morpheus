/*
 * Copyright Gregory Crane
 * April 1987
 */

#include  <ssearch.h>
#include "srchstate.h"

#define  MAXKEY  100

long tlgbuffer();
extern Centry  betatab[];
extern uchar  *betaesc();
char Authname[SHORTS];

main(argc,argv)
int argc;
char * argv[];
{
    static srch_state Srch;
    uchar   cline[MAXLINE];
    uchar  *keys[MAXKEY+1];
    char   sname[MAXKEY+1];
    char buf[2049];
    long len;
    short  clen;
    short  svalue;
    FILE * fwords;
    FILE * fopen();
    SSauto   Query;
    SSmatch  Pmatch;
    uchar *tline, *cp, *Malloc();

        if( argc != 3 ) {
                printf("format:%s wordfile textfile\n", argv[0] );
                exit( -1 );
        }
        if( (fwords=fopen(argv[1] , "r")) == NULL ) {
                fprintf(stderr,"could not open %s\n", argv[1] );
                exit( -1 );
        }

        strcpy( Srch.sname , argv[2] );
        strcpy( Authname , Srch.sname );

        if( ! TlgOnline( Srch.sname ) ) {
                fprintf(stderr,"%s not found\n", Srch.sname );
                exit( -1 );
   *pfd;
int len;
{

    int readch;
    uchar  *Malloc();


    switch ( *pfd )  {

        case  FREEBUF:
            free( *pbufptr );
            return( 0 );

        case  NEWFILE:
                                                /* FALL THROUGH         */
        default:
            if ( *pbufptr == NULL )
                if (( *pbufptr = Malloc( len )) == NULL )
                    return( -1 );
            readch =  TxtFread(Authname, *pbufptr, len );
            return( readch );
    }
}
