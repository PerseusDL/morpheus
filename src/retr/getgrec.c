/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#define isfield( S1 , S2 ) ( !strncmp( S1 , S2 , 2 ) )
    static srch_state BlankSrchState;
    char * strncpy();

 getgrec( rec , f )
  srch_state * rec;
  FILE * f;
{
        register char * s;
        char * getgfield();
        char tmp[LONGS];
        long atol();

        rec->recpoint = ftell( f );
        rec->p2 = rec->pword = rec->pw2 = 0;

        for(;;) {
                if( !fgets( tmp , sizeof tmp , f ) )
                        return( 0 );
                if( tmp[0] == ':' )
                        break;
                }
        
        clearf( rec );
        
        s = tmp+1;
        while( (s=getgfield(rec,s) ) )
                ;
        return( 1 );
        
}

char  *
 getgfield( rec , source )
  srch_state * rec;
  register char * source;
{
        char * getf();
        char field[LONGS];

        for(;;) {
                setf( source , rec );
                if( (source=getf(  source )) == NULL )
                        return(NULL);
        }

}

char *
 getf( s )
  register char * s;
{

/*
 * skip fields of three formats:
 *      --sn:name
 *      --re:"arg1 arg2 arg3" (ie. ignore whitespace within quotes )
 *      --a random flag like "poetry" or "imperat"
 *
 * end up with s pointing to beginning of next field
 */

        while( *s != ':' && ! WHITE( *s ) ) {
                if( !*s || *s == '\n' )
                        return( NULL );
                s++;
        }
        if( WHITE( *s ) ) {
                while( WHITE( *s ) )
                        s++;
                return( s );
        }
        s++;

/* if '"' follows ':', skip to next '"' */
        if( *s == '"' ) {
                s++;
                while( *s != '"' ) {
                        if( !*s || *s == '\n' ) {
                                printf("getf:\" not matched\n");
                                return( NULL );
                        }
                        s++;
                }
                s++;
        } else {
/* skip until next white space if not already pointing to whitespace */
                while( ! WHITE( *s ) ) {
                        if( !*s || *s == '\n' ) 
                                return( NULL );
                        s++;
                }
        }

/* now skip the white space */
        while( WHITE( *s ) ) 
                s++;
        if( ! *s )
                return( NULL );
        return( s );
        
}

 clearf( srch )
  srch_state * srch;
{

/*
        * srch = BlankSrchState;
*/
        srch->sname[0] = NULL;
        srch->key[0] = NULL;
        srch->Print_ref[0] = NULL;
        srch->title[0] = NULL;
        srch->freq = 0;
        srch->p2 = 0;
        srch->pnull = 0;
}

 setf( s , rec )
  register char * s;
  register srch_state * rec;
{
        long atol();
        
        if( isfield( s , "sn" ) ) {
                s += 3;
                wstrncpy( rec->sname , s , sizeof rec->sname );
                return;
        }

        if( isfield( s , "wd" ) ) {
                s += 3;
                wstrncpy( rec->gotstr , s , sizeof rec->gotstr );
                return;
        }

        if( isfield( s , "w1" ) ) {
                s += 3;
                wstrncpy( rec->gotstr , s , sizeof rec->gotstr );
                return;
        }
        if( isfield( s , "w2" ) ) {
                s += 3;
                wstrncpy( rec->gotstr2 , s , sizeof rec->gotstr2 );
                return;
        }
        if( isfield( s , "ti" ) ) {
                s += 3;
                wstrncpy( rec->title , s , sizeof rec->title );
                return;
        }
        if( isfield( s , "fq" ) || isfield( s , "af" ) ) {
                s += 3;
                rec->freq = atol( s );
                return;
        }
        if( isfield( s , "re" ) ) {
                s += 3;
                wstrncpy( rec->Print_ref , s , sizeof rec->Print_ref );
                return;
        }
        if( isfield( s , "pN" ) ) {
                rec->pnull = 1;
                return;
        }
        if( isfield( s , "pA" ) ) {
                s += 3;
                rec->p2 = atol( s );
        return;
        }
        if( isfield(s , "r2" ) ) {
                char * a = rec->endref;

                s+= 3;
                if( *s == '"' )
                        s++;
                while( *s != '"' ) {
                        *a++ = *s++;
                }
                *a = 0;
        return;
        }
        if( isfield(s , "r1" ) ) {
                char * a = rec->Print_ref;

                s+= 3;
                if( *s == '"' )
                        s++;
                while( *s != '"' ) {
                        *a++ = *s++;
                }
                *a = 0;
        return;
        }

        if( isfield( s , "pS" ) ) {
                s += 3;
                rec->pword = atol( s );
                return;
        }
        if( isfield( s , "pW" ) ) {
                s += 3;
                rec->pword = atol( s );
                return;
        }
        if( isfield( s , "wk" ) ) {
                s += 3;
                rec->recwknum = atoi( s );
                return;
        }
        if( isfield( s , "ti" ) ) {
                s += 3;
                strncpy( rec->title , s , sizeof rec->title );
                return;
        }
        if( isfield( s , "p1" ) ) {
                s += 3;
                rec->pword = atol( s );
                return;
        }
        if( isfield( s , "p2" ) ) {
                s += 3; 
                rec->pw2 = atol( s );
                return;
        }
}

 wstrncpy( s1 , s2 , lim )
  char *s1;
  char *s2;
  int lim;
{
        int i;

        if( *s2 == '"' ) {
                s2++;
                for(i=0;i<lim;i++) {
                        if( *s2 == '"' ) {
                                *s1 = 0;
                                return;
                        }
                        *s1++ = *s2++;
                }
        } else {
                for(i=0;i<lim;i++) {
                        if( WHITE( *s2 ) ) {
                                *s1 = 0;
                                return;
                        }
                        *s1++ = *s2++;
                }
        }
        *s1 = 0;
}
