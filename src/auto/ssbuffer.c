#include  "ssearch.h"

static char  SCCS_ID[] = "ssbuffer.c  1.1  8/21/85";

static int     sbnext = -1;     /* fd set by ssetfile                   */
static uchar  *sbonebuf;        /* buffer ptr set by ssetbuf            */
static long    sbonesize;       /* buffer count set by ssetbuf          */
static int     sbgotbuf;        /* number of times ssonebuf called      */

#ifdef _NFILE           /* from stdio.h, # of files allowed             */
static int  nextfd = _NFILE;
#else
static int  nextfd = FDBASE;
#endif

ssetfile( fp )
FILE  *fp;
{
        sbnext = fileno( fp );
}


long
ssbuffer( pbufptr, pfd , len )
uchar  **pbufptr;
int    *pfd;
int len;
{
    int  fd;
int readch;
    uchar  *malloc();


    switch ( *pfd )  {

        case  FREEBUF:
            if ( *pbufptr == NULL )
                ssdie( "ssbuffer: FREEBUF called with null buffer ptr\n" );
            free( *pbufptr );
            return( 0 );

        case  NEWFILE:
            if ( sbnext < 0 )  *pfd = nextfd++;
            else  *pfd = sbnext;
            sbnext = -1;
                                                /* FALL THROUGH         */
        default:
            if ( *pbufptr == NULL )
                if (( *pbufptr = malloc( len )) == NULL )
                    return( -1 );
            readch =  read( *pfd, *pbufptr, len );
            return( readch );
    }
}


ssetbuf( bsize , bptr )
long    bsize;
uchar  *bptr;
{
        sbonebuf = bptr;
        sbonesize = bsize;
/**/
        sbgotbuf = 0;
}


long
ssonebuf( pbufptr, pfd , len)
uchar  **pbufptr;
int    *pfd;
int len;
{
    int  fd;

    if( sbgotbuf++ > 0 ) {
        **pbufptr = NULL;
        return( 0 );
    }
    switch ( *pfd )  {

        case  FREEBUF:
            ssdie( "ssonebuf: can not free user buffer\n" );

        case  NEWFILE:
            *pfd = nextfd++;
            sbnext = -1;
                                                /* FALL THROUGH         */
        default:
            if (( *pbufptr = sbonebuf ) == NULL )
                ssdie( "ssonebuf: ssetbuf() not called\n" );
            sbonebuf = NULL;
            return( sbonesize );
    }
}

off_t
ssbuftell(Ssauto)
SSauto Ssauto;
{
/*
 * if just one buffer being read, do not increment the starting offset
 */
/*
        if( Ssauto->ssbufr == ssonebuf ) {
*/
        if( JustOneBuf( Ssauto ) ) {
                return( Ssauto->sscofft );
        } else {
                return( Ssauto->sscofft + Ssauto->sscct );
/*
                return( lseek(Ssauto->ssfd , 0L , 1 ) - Ssauto->sscct );
*/
        }
}
