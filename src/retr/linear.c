/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 *      Linear search routines
 *
 *              look for a string in a file
 *              look for a string in a file looking backwards
 *
 */

/*
 *      Two buffers are maintained so that we always have
 *      at least STORBUF context forwards.
 *
 *      The back search reads a block and then seeks backwards.
 *      This is slow.
 *
 *      The function that looks for the next `targets[0]' in the buffer takes up
 *      most of the time in a linear search. This should be rewritten
 *      in native code, as the routine is short and compact.
 *
 *      for now, the index function is a pointer to a function. the actual
 *      function is determined in the start up. if we are on a VAX (ifdef VAX)
 *      we set the VAX assembly language routine, else a routine in C.
 *
 *      if we are looking through an index and need to keep track of line
 *      numbers, there is a separate index function that checks an array
 *      and looks for any one of a number of different characters. if it sees
 *      a newline, it increments the new line register, otherwise it returns.
 *      this reduces the overhead of returning after every newline (very high
 *      in a one word per line word list).
 *
 *
 *      A '.' stands for a single char wild card.
 *
 *      A '@' stands for a word boundary. "@kai@dh@kai@" will
 *      only match the three separate words "kai" "dh" "kai"
 *      in that order.
 *
 *      Strings may extend over more than one line.
 *
 *      Note also that these routines can find words split by a hyphen,
 *      even when random formatting commands intervene between 
 *      the two halves of the word.
 *
 *      Hyphenization in Textual Databases is an offense against
 *      humanity.
 *
 *      The compare function ignores chars that do not represent greek
 *      letters unless these letters are specifically included as
 *      part of the string to be
 *      searched for. Greek accents are numerous and move around in
 *      a word depending upon the ending. Thus they are most conveniently
 *      ignored.
 */

/*
 *      This routine intentionally does not use code from any of the
 *      greps so that it would not be subject to source license
 *      restrictions.
 */


#include "sec.h"
#define UNCERT_C '!'
#define STORBUF (8 * 1024)
#define WMARKC '\30'
#define WORDBOUND       01
#define LINEBOUND       02
#define CHARACTER       04
#define ACCENT          010
#define CSIZE 128
#define NEXTC( X , DESTB ) if( ! *(++X) ) {  X = DESTB; }

/*
 * return values
 */
    long atol();
    long (*LinFseek)();
    long TxtFseek();
    long IndFseek();

    long (*LinFtell)();
    long TxtFtell();
    long IndFtell();

    int (*LinFread)();
    int TxtFread();
    int IndFread();

    int (*LinClose)();
    int ClTxtFile();
    int ClIndFile();

    int (*LinOpen)();
    int OpTxtFile();
    int OpIndFile();

    long (*LinLength)();
    long TxtLen();
    long IndLen();
    char * strcpy();


    int forw_count = 0;
    long indlnum = 1;
    char ctab[256];
    int tlen;
    char  * scanpoint;
    int eofflag= 0;
    static int rval = 0;
    static wildchars = 0;
    static start_of_word = 0;
    static long end_of_hit = 0; /* pointer to the last character matched */
    int lastout= 0;
    int plusflag = 0;
    static char * buf1 = NULL;
    static char * buf2 = NULL;

    char * curlastline = NULL; /* 
                                * these are buffers for the last line 
                                * cut off by a buffer boundary
                                */
    char * nextlastline = NULL;


/*
 * various variables to keep track of state of the pattern matcher
 */
    char * wbounds = NULL;
    char * boundunits = NULL;
    static long state = WORDBOUND;
    static w1flags = LINEBOUND|WORDBOUND|CHARACTER|ACCENT;
    static w2flags = LINEBOUND|WORDBOUND|CHARACTER|ACCENT;
    int laststate = WORDBOUND|LINEBOUND;
    char AuthName[SHORTS];

    char * curb;
    char * nextb;
    int curlen;
    int nextlen;
    long curoff;
    long nextoff;

    char  word1[MAXWORD];
    char  word2[MAXWORD];

/*
 * various functions
 */
    int forw_search();
    int (* execute)();
    int simpind();
    int nscan();
    int lindex();
    int lcntlines();
    int (*as_ind)();

    int forw_reset();
    int (*buf_reset)();

    long fend; /* offset to stop reading file */
    long more; /* number of bytes left to read in file */
/*    static int f; /* input file number */
    long hits = 0; /* number of matches so far */
    long tries = 0; /* number of tries (e.g. for context search) */
    static long sl_flags = 0; /* various flags */
    static long lowbound;


 InitLinLookup(srch)
  srch_state * srch;
{
        lowbound = 0;
        hits = 0;

/* BUG FIX -- if less than 0, fail */
        if( linsetup( srch ) < 0 )
                return( -1 );

        init();

        scanpoint = curb;
        tlen = curlen;
        return(1);
}

 NextLinPhrase(srch)
  srch_state * srch;
{
        if( forw_search(srch) ) {
                gotphrase( srch , scanpoint );
                scanpoint++;
                tlen--;
                return(1);
        } else {
                return(0);
        }
}


 forw_search(srch)
  srch_state * srch;
{
        for(;;) {
                (*as_ind)(word1[0]);
                if( !tlen ) {
                        if( !(*buf_reset)() ) {
                                rval = 0;
                                break;
                        }
                } else {
                        if(compare(scanpoint,word1,w1flags)) {
                                return(1);
                        }
                        scanpoint++;
                        tlen--;
                }
        }
        bdump( srch , (long)((*LinFtell)(AuthName) - srch->l_start) );
        (*LinClose)(AuthName);
        return(0);
}


 compare( lp , wp , flags )
  register char *lp ;
  register char *wp ;
  int flags;
{
        char * jump();
        char * sp = lp;

        wp++;
        NEXTC( lp , nextb );
        for( ;; ) {
                if( !*wp ) {
                        if( wildchars ) {
                                if( ! enough_chars( sp , wildchars ) )
                                        return( 0 );
                        }
                        set_match_end( lp );
                        if( sp > curb )
                                state = getstate( sp - 1 );
                        else
                                state = laststate;
                        if( !(state & flags ) ) {
                                return( 0 );
                        }
                        end_of_hit = curoff + (lp - curb) - 1;

                        return(1);
                }
                                        

/* if search skips non-alphabetic chars, step over them here */
                if( sl_flags & ONLY_VIEW_CHARS ) {
                        while( !( wbounds[ *lp ] & (CHARACTER|ACCENT) ) )  {
                                NEXTC( lp , nextb );
        }
                }

        /*
         * in damaged texts, where a letter is missing, match this ellipsis
         * against any character in the query
         */
                if( *lp == UNCERT_C ) {
                        NEXTC( lp , nextb );
                        wp++;
                        continue;
                }

                if( *wp == WILDC ) {
                        if( isalpha( *lp ) ) {
                                NEXTC( lp , nextb );
                                wp++;
                                continue;
                        /*
                         * fail on word boundary 
                         */
                        } else if( wbounds[ *lp ] & WORDBOUND ) {
                                return(0);
                        } else {
                                NEXTC( lp , nextb );
                                continue;
                        }
                                        
                }
                                        
                if( *wp == WMARKC ) {
                        wp++;

                        /* look for next CHARACTER or WORDBOUND */
                        while( !( wbounds[ *lp ] & (WORDBOUND|CHARACTER) ) ) {
                                NEXTC( lp , nextb );
                        }

/* if CHARACTER, fail */
                        if( ! (wbounds[ * lp ] & WORDBOUND ) ) {
                                return( 0 );
                        }

/* else skip to next ACCENT or CHARACTER and proceed */
                        while( !( wbounds[ *lp ] & (CHARACTER|ACCENT) ) ) {
                                NEXTC( lp , nextb );
                        }
                        continue;
                        
                }
                if( *wp == *lp  ) {
                        wp++;
                } else 
        /*
         * if chars do not match and *lp is either a word boundary or an
         * alphabetic character, fail. thus, "pemp" will not fail if it
         * sees "pe]mp" or "pe/mp"
         * 
         * OR
         *
         * if you really want an ACCENT and you didn't get a match,
         * fail. thus you can ask for "@fu/gh|@" and not get "@fugh=|@".
         */
                        if( (wbounds[ *lp ] & (WORDBOUND|CHARACTER) ) ||
                                (wbounds[ * wp ] & ACCENT) )
                                return( 0 );

                if( *lp == '-' ) {
                        lp = jump( lp , nextb );
                        continue;
                }
                if( *lp == '\n' ) {
                        lp = jump( lp , nextb );
                        continue;
                }
                NEXTC( lp , nextb );
        }
}

 enough_chars( s ) 
  char * s;
{
        int i;

        if( s == curb ) {
                s = curlastline;
                while( *s ) s++;
        }
        s--;

        for(i=0;;) {
                if( isalpha( *s ) )
                        i++;
                if( wbounds[ *s ] & WORDBOUND )
                        break;
                if( s == curb ) {
                        s = curlastline;
                        while( *s ) s++;
                        s--;
                }
                if( s == curlastline )
                        break;
                s--;
        }
        if( start_of_word ) {
                if( i == wildchars )
                        return( 1 );
                else
                        return( 0 );
        }
        if( i >= wildchars )
                return( 1 );
        else
                return( 0 );
}


 forw_reset( )
{
        char * tmp = 0;
        long x;


        if( eofflag ) {
                return( 0 );
        }
        if( lastout ) {
                eofflag++;
        }

        laststate = getstate( &curb[curlen-1] );

        curoff = nextoff;
        nextoff = (*LinFtell)(AuthName);

        curlen = nextlen;

        strcpy( curlastline , nextlastline );
        if( *nextb )
                getlastline( &nextb[nextlen-1] , nextlastline );


        tmp = curb;
        curb = nextb;
        nextb = tmp;

        tlen = curlen;
        scanpoint = curb;

        if( (x=(*LinFtell)(AuthName)) + STORBUF > fend ) {
                nextlen = (*LinFread)( AuthName, nextb , (int)(fend-x) );
                if( nextlen >= 0 )
                        nextb[nextlen] = 0;
                else
                        nextb[0] = 0;
                lastout++;

                return( 1 );
        }

        if( (nextlen= (*LinFread)(AuthName,  nextb ,  STORBUF )) < 0 )
                prerror("input error");
        nextb[nextlen] = 0;

        return( 1 );
}

 init()
{
        int i;
        long x;

        lastout = eofflag = 0;
        nextoff = 0;
        curlen = 0;
        hits = 0;
        tries = 0;
        rval = 0;

        curoff = (*LinFtell)();
        wbounds[' '] = WORDBOUND;
        wbounds['\t'] = WORDBOUND;
        wbounds['\n'] = WORDBOUND;
        wbounds['.'] = WORDBOUND;
        wbounds[','] = WORDBOUND;
        wbounds['`'] = WORDBOUND;
/*      wbounds['\''] = WORDBOUND;*/
        wbounds[';'] = WORDBOUND;
        wbounds[':'] = WORDBOUND;
        wbounds['_'] = WORDBOUND;
        wbounds[ '\\' ] = ACCENT;
        wbounds[ '/' ] = ACCENT;
        wbounds[ '+' ] = ACCENT;
        wbounds[ '=' ] = ACCENT;
        wbounds[ '?' ] = ACCENT;
        wbounds[ ')' ] = ACCENT;
        wbounds[ '(' ] = ACCENT;
        wbounds[ '|' ] = ACCENT;
        wbounds[ '*' ] = ACCENT;
        for(i='a';i<='z';i++)
                wbounds[i] = CHARACTER;
        for(i='A';i<='Z';i++)
                wbounds[i] = CHARACTER;
        
        if( fend - lowbound < STORBUF ) {
                curlen = (*LinFread)(AuthName, curb , (int)(fend-lowbound) );
                curb[curlen] = 0;
                eofflag++;
                return;
        } 

/* set input buffer to STORBUF chars before end of file */

        if( (curlen=(*LinFread)(AuthName, curb ,  STORBUF )) < 0 )
                prerror("input error");

        getlastline( &curb[curlen-1] , nextlastline );

/* subtract no of chars read from no of chars to be read */
        more -= (long)curlen;
        curb[curlen] = 0;
        nextoff = (*LinFtell)(AuthName);

        if( (x=fend-(*LinFtell)(AuthName)) < STORBUF ) {
                nextlen = (*LinFread)( AuthName, nextb , (int)x );
                nextb[(int)nextlen] = 0;
                lastout++;
                return;
        }

        if( (nextlen=(*LinFread)(AuthName,  nextb ,  (STORBUF) )) < 0 )
                prerror("input error");

        nextb[nextlen] = 0;

}

char * 
 jump( s , destb  )
  register char * s;
  register char * destb;
{
        loop:
        for(;;) {
                if(*s == '\n' )
                        break;
                NEXTC( s , destb );
        }

        NEXTC( s , destb );
        if( *s == '~' )
                goto loop;
        return( s );
}
        
 wordset( obj , source , flags )
  char * obj;
  char * source;
  int *flags;
{

        if( source[0] == '@'  ) {
                if( source[1] != WILDC ) 
                        *flags =  WORDBOUND ;
                else
                        start_of_word++;
                wrdcpy( obj , &(source[1]) );
        } else {
                wrdcpy( obj , source );
        }
/* BUG FIX -- make sure you otherwise return 1 */
        return( 1 );
}

 wrdcpy( s , a )
  register char *s;
  register char *a;
{
        static int first;

        for(first=1; *a; ) {
                if( *a == '@' ) {
                        *s++ = WMARKC;
                        while( *a == '@' )
                                a++;
                        continue;
                }
                /*
                 * if the query starts with a '.' (Wild card char), look
                 * forward till you get your first real char and count
                 * the number of wildchars that you see.
                 *
                 * only wildchars and no alphabetic chars may be in query,
                 * (ie. the user wants all words N letters long).
                 */
                if( first ) {
                        first = 0;
                        if( has_chars( a ) ) {
                                while( *a == WILDC && *a )  {
                                        wildchars++;
                                        a++;
                                }
                                continue;
                        }
                                
                }
                if( *a == 'j' || *a == 'v' )
                        *s++ = 's';
                if( isupper( *a ) ) {
                        *s++ = '*';
                        if( *a == 'J' || *a == 'V' )
                                *s++ = 's';
                        else
                                *s++ = tolower( *a );
			a++;
                        continue;
                }
                        
                *s++ = *a++;
                first = 0;
        }
        *s = 0;
}

 has_chars( s )
  char * s;
{
        while( *s ) {
                if( ISTLGC( *s ) )
                        return( 1 );
                s++;
        }       
        return( 0 );
}


 gotphrase(srch,pp)
  srch_state * srch;
  char * pp;
{
        long hitoffset;
        
        hits++;

        hitoffset = curoff + (pp - curb);
        if( ! (srch->rflags & INDEX ) )
                srch->pword = hitoffset;
        srch->pend = end_of_hit;
        getpword( pp , srch->gotstr , word1 );
/*
        srch->l_start = srch->pword + 1;
*/
        srch->l_start = hitoffset + 1;
        srch->l_len = fend - srch->l_start;

        if( srch->rflags & INDEX ) {
                srch->p2 = indlnum;
                srch->l_lno = indlnum;
        } else {
                srch->p2 = srch->pw2 = 0;
        }
        return( hits );
}

 getstate( s ) 
  register char * s;
{
        int n;

        for(;;) {
                if( s == curb )
                        return( laststate );
                if( ! ((n=wbounds[ *s ]) & (WORDBOUND|CHARACTER) ) ) 
                        s--;
                else
                        return( n );
        }
}

/*
 * this routine initiliazes the search.
 * it looks at the various flags set in srch->rflags and determines
 * what type of search is called for
 */
 linsetup( srch )
  srch_state * srch;
{
        char * Malloc();
        char file[MAXPATHNAME];

        start_of_word = wildchars = 0;

        if( buf1 == NULL ) 
                buf1 = Malloc(  STORBUF + 2 );
        if( buf2 == NULL ) 
                buf2 = Malloc(  STORBUF + 2 );


        curb  = buf1;
        nextb = buf2;

        if( curlastline == NULL )
                curlastline = Malloc( CSIZE );
        if( nextlastline == NULL )
                nextlastline = Malloc( CSIZE );

        if( wbounds == NULL )
                wbounds = Malloc( CSIZE );
        if( boundunits == NULL )
                boundunits = Malloc( CSIZE );

        sl_flags = srch->rflags;
        indlnum = 1;
        curb  = buf1;
        nextb = buf2;
        nextlen = curlen = 0;
        buf1[0] = 0;
        buf2[0] = 0;

        w1flags = LINEBOUND|WORDBOUND|CHARACTER|ACCENT;
        w2flags = LINEBOUND|WORDBOUND|CHARACTER|ACCENT;

    strncpy(AuthName,srch->sname,sizeof AuthName);
    if( srch->rflags & INDEX ) {
                LinFseek = IndFseek;
                LinFtell = IndFtell;
                LinFread = IndFread;
                LinClose = ClIndFile;
                LinOpen = OpIndFile;
                LinLength = IndLen;
        } else {
                LinFseek = TxtFseek;
                LinFtell = TxtFtell;
                LinFread = TxtFread;
                LinClose = ClTxtFile;
                LinOpen = OpTxtFile;
                LinLength = TxtLen;
        }
        if( (*LinOpen)(AuthName) < 0 ) {
                fprintf(stderr,"linear could not open %s\n", AuthName );
                return(-1);
        }

        if( srch->l_len == 0 ) {
                more = fend = (*LinLength)(AuthName);
        } else {
                more = fend = srch->l_start + srch->l_len;
        }

/* BUG FIX -- check for wordset() rval. if < 0 , return -1 */
        if( wordset( word1 , srch->key , &w1flags ) < 0 )
                return( -1 );

        if( srch->l_lno )
                indlnum = srch->l_lno;

        curoff = (*LinFseek)( AuthName , srch->l_start );


        lowbound = curoff;


        if( srch->rflags & INDEX ) {
		int i;

                execute = forw_search;
                buf_reset = forw_reset;
		for(i='a';i<='z';i++) 
			ctab[i] = 0;
                if( word1[0]  == WILDC ) {

                        for(i='a';i<='z';i++) 
                                ctab[i]++;
                } else
                        ctab[ word1[0] ] = 1;

                ctab[ '\n' ] = 1;
#if AUTOMATON == 0
        as_ind = lcntlines;
#else
#if VAX 
                as_ind = nscan;
#else
                as_ind = lcntlines;
#endif
#endif
        } else {
                buf_reset = forw_reset;
                execute = forw_search;
#if AUTOMATON == 0
                as_ind = lindex;
#else
#if VAX
                as_ind = simpind;
#else
                as_ind = lindex;
#endif
#endif
        }

/* BUG FIX -- makesure you return a useful value */
        return( 1 );

}

 getlastline( source , obj )
  register char * source;
  register char * obj;
{
        char * start = source;
        while( *source != '\n' && *source) {
                source--;
        }
        if( *source == '\n' && source != start )
                source++;
        
        while( *source && (source != start )) {
                *obj++ = *source++;
        }
        *obj = 0;
}

/* now that you have a match, look in buffer and get the actual string */
/* copy from last word boundary before match, then copy at least */
/* strlen( searchpattern ) chars, then go till next word break: */
/* this takes care of multi-word strings, e.g. @kai@dh@kai@, where you */
/* want more than just the chars between two word bounds */

 getpword( s , p , word )
  register char * s;
  register char * p;
  char * word;
{
        char * a;
        char * towordbegin( );

        a = towordbegin( s , curb  );

/* if you found a pattern, but the word in which the pattern rests is
/* partially in the last block read, you can still reconstruct the beginning
/* of the word by looking at curlastline which contains the last line of
/* the previous buffer */

        if( a == curb && curlastline[0] ) {
                a =towordbegin(&curlastline[strlen(curlastline)-1],curlastline);
                txtcpy( p , a , curb , word , MAXWORD );
                return;
        }

        txtcpy( p , a , nextb , word , MAXWORD );
}

 txtcpy( p , a , destb , word, maxs )
  register char *p;
  register char * a;
  register char * destb;
  char * word;
  int maxs;
{
        int i;
        char * jump();

        for(i=0;i<maxs;i++) {
                
        /* if hyphenated word, skip to second half of word */
                if( *a == '-' ) {
                        a = jump( a , curb );
                        continue;
                }

        /* if word boundary */
                if( wbounds[ *a ] & WORDBOUND ) {

                        if( sl_flags & INDEX )
                                break;
                        /* if copied as many chars as in string requested */

                        /* AND */

                        /* if copied up to the point where the matching
                                process concluded */
                        /* break */
                

                        if( i >= (strlen( word ) - 1) && up_to_match_end( a ) )
                                break;

                        /* otherwise mark the wordboundary  */
                        /* in the string with a '@' */

                        *p++ = '@';

                        /* skip over chars till you get to next printing char */
                        while( ! (wbounds[ *a ] & (CHARACTER|ACCENT)) )
                                NEXTC( a , destb );
                        continue;
                }

                /* skip over chars until you find something worth looking at */
                if( ( ! (wbounds[ *a ] & (WORDBOUND|CHARACTER|ACCENT)) )
                                && *a != '\'' && *a != UNCERT_C ) {
                        NEXTC( a , destb );
                        continue;
                }

                if( !*a )
                        break;
                /* set all grave accents to acute */
                if( *a == '\\' )
                        *p++ = '/';
                else
                        *p++ = *a;
                NEXTC( a , destb );
        }
        *p = 0;
}

/* return a pointer to last word boundary in current string */

char * 
 towordbegin( s , startp )
  register char * s;
  register char * startp;
{
        for(;;) {
                if( s == startp ) {
                        return( s );
                }
                if( wbounds[ *s ] & WORDBOUND ) {
                        return( s+1 );
                }
                s--;
        }
}

    static char * match_end_p;
    static char * match_buffer;

 set_match_end( s )
  char *s;
{
/* keep track of where you were pointing when match ended */
        match_end_p = s;
/* also keep track of which buffer you were in */
        match_buffer = curb;
}

 up_to_match_end( s )
  char *s;
{
        /* current buffer was not the match buffer */
        if( curb != match_buffer ) {
                /* if s is closer to the end of curb than the start,
                        then match_end is in the other buffer */
                /*if( s - curb > BUFSIZ/2 )*/
                if( s - curb > STORBUF/2 )
                        return( 0 );
                else
                        return( 1 );
        }
        if( s > match_end_p )
                return( 1 );
        return( 0 );
}


 bdump(srch, bytes)
  srch_state * srch;
  long bytes;
{
        char mess[MAXMESS];

        if( ! (srch->rflags&BYTEFLAG) )
                return;

        sprintf(mess,"bytes:%ld ", bytes );
}

 lindex(c)
  register char c;
{
        register char *sp = scanpoint;
        do {
                if (*sp == c) {
                        tlen -= sp - scanpoint;
                        scanpoint = sp;
                        return;
                }
                        
        } while (*sp++);
        tlen = 0;
}

 lcntlines()
{
        register char *sp = scanpoint;
        do {
                if( *sp == '\n' ) {
                        indlnum++;
                        continue;
                }
                if (ctab[ *sp ] ) {
                        tlen -= sp - scanpoint;
                        scanpoint = sp;
                        return;
                }
                        
        } while (*sp++);
        tlen = 0;
        
}

/* note that this routine assumes a string beginning with a null */
char *
 lrindex(sp, c)
  register char *sp;
  register c;
{
        do {
                if (*sp == c)
                        return( sp );
        } while (*--sp);
        return(sp);
}
