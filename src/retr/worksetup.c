static char  SCCSID[] = "@(#)worksetup.c	2.1  9/26/87";
/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#include "tlg.h"
#include "tlgwind.h"
#define TABSIZE 1024 /* max number of works allowed for now */

#define WORKTAG "wk:"

/*
 * various functions
 */
    char * Calloc();
    char * strcpy();
    char * strncpy();
    char * NextField();

    char oldsname[40];
    static char curauth[SHORTS+1];
    static int first = 1;
    static int tot_works = 0;
    shortw *wtab = NULL;

/* 
 * read the list of works associated with an author and set up a table
 * (wtab) that stores information about the various works
 */


 worksetup( srch )
  srch_state * srch;
{
        char tmpb[BUFSIZ];
        long atol();
        long WorkfOffset();
        char * WorkfFgets();
        int i;

        
        if( ! strcmp( srch->sname , curauth ) ) {
                return( 1 );
        }
        if( ! wtab ) {
            if( (wtab = (shortw *) Calloc(TABSIZE, sizeof * wtab )) == NULL ) {
                prerror("worksetup could not create wtab");
                return( -1 );
            }
        }
        strcpy( curauth , srch->sname );
        if( ! OpWorkfFile(srch->sname) ) {
		fprintf(stderr,"could not find %s.workfile\n", srch->sname);
		return(-1);
	}
        
	srch->wtab = wtab;
        for(i=0;i<TABSIZE;i++) {
                wtab[i].off_in_workfile = WorkfOffset(srch->sname);
                if( !WorkfFgets( tmpb , sizeof tmpb , srch->sname ) )
                        break;
                getshortw( &wtab[i] , tmpb );
        }
        tot_works = srch->nworks = i;
        first = 0;
        ClWorkfFile(srch->sname);
        return( 1 );
}
                

/*
 * given a key, either a number or a string, store other information about
 * work (such as its start and stop points in the author file) in srch
 */

 workbykey( srch , key )
  srch_state * srch;
  char * key;
{
        int n;

        if( !curauth[0] || strcmp( curauth , srch->sname ) || ! srch->nworks )
                worksetup( srch );

	if( isdigit( *key ) ) {
/*
 * assume that any string beginning with a digit describes a reference
 * within a given work, rather than a work number. any reference to a 
 * work as a number, presented as an ASCII string, must have the prefix
 * WORKTAG
 */
                return( -1 );
	} else if( ! strncmp( key , WORKTAG , strlen( WORKTAG ) ) ) {
		n = atoi( key + strlen( WORKTAG ) );
                return( workbynum( srch , n ) );
        } else 
                return( workbyname( srch , key ) );
}



/*
 * assumes a name like "ag" (for the Agamemnon) or "il" (for the Iliad)
 */

 workbyname( srch , name )
  srch_state * srch;
  char * name;
{
        int i;

        if( !curauth[0] || strcmp( curauth , srch->sname ) || ! srch->nworks )
                worksetup( srch );

        for(i=0;i<tot_works;i++) {
                if( ! strcmp( name , wtab[i].wkname)  ) {
                        strncpy( srch->title , wtab[i].wkname , sizeof srch->title );
                        srch->recwkstart = wtab[i].wkoff;
                        if( srch->recwkstart == 0 )
                                srch->recwkstart++;
                        srch->recwkend = wtab[i].wkend;
                        srch->recwknum = wtab[i].wknum;
                        return( wtab[i].wknum );
                }
        }
        return( -1 );
}
        
/*
 * assumes that you have the work number: all TLG works have numbers, but
 * many (such as Plutarch's Moralia) do not have short titles.
 */

 workbynum( srch , wnum )
  srch_state * srch;
  int wnum;
{
        int i;

        if( !curauth[0] || strcmp( curauth , srch->sname ) || ! srch->nworks )
                worksetup( srch );


        for(i=0;i<tot_works;i++) {
                if( wnum == wtab[i].wknum ) {
                        strncpy( srch->title , wtab[i].wkname , sizeof srch->title );
                        srch->recwkstart = wtab[i].wkoff;
                        if( srch->recwkstart == 0 )
                                srch->recwkstart++;
                        srch->recwkend = wtab[i].wkend;
                        srch->recwknum = wtab[i].wknum;
                        return( wtab[i].wknum );
                }
        }
        return( -1 );
}
        
/*
 * the work number does not necessarily corresond to the index of the work in
 * the array wtab[] --> we have this gets the values associated with 
 * wtab[index]
 */

 workbyindex(srch, index)
  srch_state * srch;
  int index;
{
        if( !curauth[0] || strcmp( curauth , srch->sname ) || ! srch->nworks )
                worksetup( srch );

        if( index > tot_works ) {
                return( -1 );
        }
        strncpy( srch->title , wtab[index].wkname , sizeof srch->title - 1);
        srch->recwkstart = wtab[index].wkoff;
        if( srch->recwkstart == 0 )
                srch->recwkstart++;
        srch->recwkend = wtab[index].wkend;
        srch->recwknum = wtab[index].wknum;
        return( wtab[index].wknum );
}

/*
 * given the offset, get rest of info about work and store it in rec
 */
 workbyoff( srch , offset )
  srch_state * srch;
  long offset;
{
        int i;

        if( !curauth[0] || strcmp( curauth , srch->sname ) || ! srch->nworks )
                worksetup( srch );

        for(i=0;i<tot_works;i++) {
                if( offset < wtab[i].wkend ) {
                        strncpy( srch->title , wtab[i].wkname , sizeof srch->title );
                        srch->recwkstart = wtab[i].wkoff;
                        if( srch->recwkstart == 0 )
                                srch->recwkstart++;
                        srch->recwkend = wtab[i].wkend;
                        srch->recwknum = wtab[i].wknum;
                        return( wtab[i].wknum );
                }
        }
        return( -1 );
}

#define isfield( S1 , S2 ) ( !strncmp( S1 , S2 , 2 ) )
#define white( X ) ( X == ' ' || X == '\t' || X == '\n' )


 clearsw( swk )
  shortw * swk;
{
        swk->wkend = 0;
        swk->wknum = 0;
        swk->wkname[0] = 0;

}

 setw( s , wk )
  register char * s;
  register shortw * wk;
{
        long atol();

        if( isfield( s , "ti:" ) ) {
                s += 3;
                strncpy( wk->wkname , s , sizeof wk->wkname - 1);
                return;
        }
        if( isfield( s , "wk:" ) ) {
                s += 3;
                wk->wknum = atoi( s );
                return;
        }


}

 getshortw( swk , source )
  shortw * swk;
  register char * source;
{
        char field[MAXLIN];
        long atol();

        clearsw( swk );

        swk->wkoff = atol( source );
/*
 * the offsets pointed to in the first field or the author.workfile are off
 * by 1 byte. we kludge the fix here, until fixing the problem for all files
 */
/* only exception: if the work starts at 0, it really starts at 0 */
        if( swk->wkoff )
                swk->wkoff++;
        while( isdigit( *source ) )
                source++;
        source++;
        
        swk->wkend = atol( source ) + swk->wkoff;
        while( isdigit( * source ) )
                source++;
        while( white( * source ) )
                source++;

        for(;;) {
                if( (source=NextField( field, source )) == NULL )
                        break;
                setw( field , swk );
        }
/*
 *	Make sure every work has a name -- vjh 9/87
 */
	if ( swk->wkname[0] == '\0' )  {
		strcpy( swk->wkname, "wk" );
		sprintf( swk->wkname+2, "%03d", swk->wknum );
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
