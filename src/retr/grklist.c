/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 * this module handles all IO between the user and TLG files.
 * it should isolate programs from details such as file system
 * specifics, so that we can use the standard unix file or CDFS
 * or raw compact disk or whatever.
 */

/*
 * include statements
 */

#include "defcons.h"
#include "tlgfile.h"


/*
 * define statements
 */

/*#define WHITE( X ) ( X == '\t' || X == ' ' || X == '\n' )*/
#define isfield( S1 , S2 ) ( !strncmp( S1 , S2 , 2 ) )


/*
 * declarations
 */
    static Thesaurus = 0;
    static tlgauthor TlgAuthor;
    static char grklist[MAXPATHNAME];
    static char dbasdir[MAXPATHNAME];
    static char dbasname[SHORTS];

    char * NextField();
    FILE * OpenGrklist();
    char * GetAuthRec();
    char * AuthInGrklist();
    char * strcpy();
    char * strncpy();
    char * getenv();

/*
 * given an author's name, scan through the list of authors on line,
 * find the appropriate record and read the information into a data
 * structure TlgAuthor
 */
 TlgAuthInit(authname)
  char * authname;
{
        if( AuthIsOpen(authname) )
                return(1);
        strncpy(TlgAuthor.tlgsname,authname,sizeof TlgAuthor.tlgsname );

        return(GetAuthInfo(&TlgAuthor));
}

char *
 TlgAuthDirectory(authname)
  char * authname;
{
        if( ! strcmp(authname,BIGINDNAME ) ) return( dbasdir );
        if( !strcmp( authname , TlgAuthor.tlgsname ) ) 
                return( TlgAuthor.tlgauthdir );
        TlgAuthInit(authname);
        return(TlgAuthor.tlgauthdir);
}

 TxtIsOnCD(authname)
  char * authname;
{
        if( strcmp( authname , TlgAuthor.tlgsname ) ) {
		TlgAuthInit(authname);
	}
/*
 * goddamn file shouldn't be marked as being both on CD and 
 * and hard disk (even though it may be on both).
 */
	if( (TlgAuthor.tlgflags & USE_CD ) && (TlgAuthor.tlgflags & USE_HD) ) {
		fprintf(stderr,"ERROR:author %s both on CD and HD!\n", authname);
		return(0);
	}
	return(TlgAuthor.tlgflags & USE_CD );
}

 TxtIsOnHD(authname)
  char * authname;
{
        if( strcmp( authname , TlgAuthor.tlgsname ) ) 
		TlgAuthInit(authname);
/*
 * goddamn file shouldn't be marked as being both on CD and 
 * and hard disk (even though it may be on both).
 */
	if( (TlgAuthor.tlgflags & USE_CD ) && (TlgAuthor.tlgflags & USE_HD) )
		return(-1);
/*
 * note -- the default is hardwired here to look at the Hard Disk!
 */
	if( TlgAuthor.tlgflags & USE_CD )
		return(0);
	return(1);
}
 InitBigind()
{
        Thesaurus++;
        SetBigind();
}

 CloseBigind()
{
        Thesaurus = 0;
}


/*
 * routines local to this module
 */

static 
 AuthIsOpen(authname)
  char * authname;
{
        if( !strcmp(authname,TlgAuthor.tlgsname) )
                return(1);
        else
                return(0);
}

static 
 GetAuthInfo( tauth )
  tlgauthor * tauth;
{
        char getauthtmp[BUFSIZ];


        if( (AuthInGrklist( tauth->tlgsname , getauthtmp )) == NULL ) {
                return( 0 );
        }
        GetAuthRec( tauth , getauthtmp );

        return( 1 );
}

static char  *
 GetAuthRec( tauth , source )
  tlgauthor * tauth;
  register char * source;
{
        register char * s;
        char field[MAXLIN];

        ClearTlgAuthor( tauth );
        s = tauth->tlgsname;

        while( !WHITE( *source ) )
                *s++ = *source++;
        *s = 0 ;
        source++;

        for(;;) {
                if( (source=NextField( field, source )) == NULL )
                        break;
                SetTlgAuthor( field , tauth );
                }
        sprintf(tauth->tlgbasename,"%s/%s", tauth->tlgauthdir , tauth->tlgsname );
}


static
 ClearTlgAuthor( tauth )
  tlgauthor * tauth;
{
        tauth->tlgsname[0] = 0;
        tauth->tlgauthdir[0] = 0;
        tauth->tlgbasename[0] = 0;
}

static 
 SetTlgAuthor( s , tauth )
  register char * s;
  register tlgauthor * tauth;
{
        long atol();

        if( isfield( s , "sn" ) ) {
                s += 3;
                strncpy( tauth->tlgsname , s , sizeof tauth->tlgsname );
                return;
        }
        if( isfield( s , "Wc" ) ) {
                s += 3;
                tauth->tlgnworks = atoi( s );
                return;
        }

        if( isfield( s , "ln" ) ) {
                s += 3;
                tauth->tlgfilelen = atol( s );
                return;
        }


	if( isfield( s , "cdfile" ) ) {
		tauth->tlgflags |= USE_CD;
		return;
	}

	if( isfield( s , "hdfile" ) ) {
		tauth->tlgflags |= USE_HD;
		return;
	}

        if( isfield( s , "di" ) ) {
                s += 3;
                strncpy( tauth->tlgauthdir , s , sizeof tauth->tlgauthdir );
                return;
        }
}


static char *
 NextField( s1, s2 )
  register char * s1;
  register char * s2;
{
        while( WHITE( *s2 ) && *s2 )
                s2++;
        if( !*s2 )
                return( NULL );
        while( !WHITE( *s2 ) && *s2 )
                *s1++ = *s2++;
        *s1 = 0;
                return( s2 );
}



static
 SetGrklist()
{

#if MACINTOSH
        strncpy(grklist, "grklist" , sizeof grklist );
#else
        strncpy(grklist, getenv( "GRKLIST" ) , sizeof grklist );
#endif
        if( grklist[0] )
                return(OK);
        else {
                fprintf(stderr,"Error: GRKLIST not defined\n");
                return(NULL);
        }
}

static 
 SetBigind()
{
#if  MACINTOSH
#else
        sprintf(dbasdir,"%s", getenv( "DBASDIR" ) );
#endif

}

static char *
 AuthInGrklist( s , abuf )
  register char * s;
  char * abuf;
{
        FILE * fgrklist;
        char tmp[128];
        char * fgets();
        
        
        if( (fgrklist=OpenGrklist()) == NULL ) {
                fprintf(stderr,"could not open grklist, looking for %s\n", s );
                return( NULL );
        }
        strcpy( tmp , s );
        strcat( tmp , "\t" );
        

        while( fgets( abuf , BUFSIZ, fgrklist ) ) {
                if( Empty( abuf ) )
                        continue;
                if( CheckAuth( tmp , abuf ) ) {
                        fclose( fgrklist );
                        fgrklist = NULL;
                        return( abuf );
                }
        }

        fclose( fgrklist );

        fgrklist = NULL;
        return( NULL );
}

static
 Empty( s )
  register char * s;
{
        while( *s ) {
                if( ! WHITE( *s ) )
                        return( 0 );
                s++;
        }
        return( 1 );
}

static
 CheckAuth( patt , lbuf )
  char * patt;
  char * lbuf;
{
        if(! strncmp( patt , lbuf , strlen( patt ) ) )
                return(  1 );
        return( 0 );
}

static FILE *
 OpenGrklist()
{
        if( grklist[0] == 0 ) {
                if(SetGrklist()<0)
                        return(NULL);
        }
        return(fopen(grklist,"r"));
}
