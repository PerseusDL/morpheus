/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 * for a given string, figure out the best way to search locate it in
 * an author
 */

#include "srchstate.h"

 PickSearch(srch)
  srch_state * srch;
{
        if( srch->rflags & THESAURUS )
                return( ScanThesaur( srch ) );
	if( TxtIsOnCD(srch->sname) ) 
		printf("will use CD to search %s\n", srch->sname );
        if( StringIsPhrase( srch->key ) || (srch->rflags&LINEAR) ) {
                return( ScanAuthor(srch) );
        }
        return( ScanIndex(srch) );
}

/* 
 * check to see if string s is a single word or a phrase (ie., more than
 * one word: e.g.
 *      @kai@dh  or kai@dh 
 */
 StringIsPhrase( s )
  char * s;
{
/*
 * basically we look for a '@' somewhere after the first char of the
 * string
 */
        if( *s == '@' )
                s++;
        while( *s && *s != '@') 
                s++;
/* 
 * returns either the value following the second '@' 
 */
        if( *s == '@' )
                return( *++s );
/* 
 * or simply 0, if no other '@' in string 
 */
        return( *s );
}

 WildString(s)
  char * s;
{
        while(*s) {
                if( *s == '.' )
                        return( 1 );
                s++;
        }
        return(0);
}
