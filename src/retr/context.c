/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#if MACINTOSH
#include  "godzilla_1:lightspeed:automaton:ssearch.h"
#else
#include "../auto/ssearch.h"
#endif
#include "gksel.h"
#define CHARSET 128

static InitUnits();
static char * ssbackup(char * startp,long center,int separation,int units);
static get_wlen_in_text(char * bufp,int buflen);
static ssjump(char * startp, int slen,int separation,int units);

    static char * sbuf;
    static char * tlgch;
    static char * wordbound;
    static char * sentbound;
    static InitRun = 0;

    char * ssbackup();
        
/*
 * get a slab of context around a given offset 
 */
 GkselByOff(gksel)
  GkSelection * gksel;
{
        long start;
        long firsthalf;
        long radius;
        int len;
        int maxbuf;
        char * startp;

        maxbuf = gksel->gkselunits * gksel->gkselnunits ;
        if( maxbuf <= 0 ) {
                fprintf(stderr,"GkselByOff error: maxbuf %d!\n", maxbuf );
                return(-1);
        }

        sbuf = (char *)calloc(maxbuf+2, sizeof * sbuf );
        if( ! sbuf ) {
                fprintf(stderr,"no space for  sbuf in set_sspace())\n");
                return(-1);
        }

        if( ! tlgch ) {
                tlgch = calloc(CHARSET,sizeof * tlgch );
        }
        if( ! wordbound ) {
                wordbound = calloc(CHARSET,sizeof * wordbound );
        }
        if( ! sentbound ) {
                sentbound = calloc(CHARSET,sizeof * sentbound );
        }
        if( ! InitRun ) 
                InitUnits();

        radius = (long)maxbuf/2;
        if( radius > gksel->gkselcenter ) {
                TxtFseek(gksel->gkselauth,0L);
        } else {
                TxtFseek(gksel->gkselauth,(gksel->gkselcenter-radius));
        }
        start = TxtFtell(gksel->gkselauth);
        len  = TxtFread(gksel->gkselauth,sbuf,maxbuf);
        sbuf[len] = 0;
        startp = ssbackup(sbuf,gksel->gkselcenter-start,gksel->gkselnunits,gksel->gkselunits);
        

        /*gksel->gkselbufp = startp;*/
        firsthalf = (gksel->gkselcenter-start) - (startp - sbuf );
        gksel->gkselstart = start + (startp - sbuf);
        
        gksel->gkselcEnd = gksel->gkselcenter +
          get_wlen_in_text( sbuf + (gksel->gkselcenter-start), len - (int)(gksel->gkselcenter-start) );

        len = ssjump( sbuf + (gksel->gkselcenter-start),
                        len - (int)(gksel->gkselcenter-start),
                        gksel->gkselnunits,
                        gksel->gkselunits)
                                + firsthalf;

/*
 * this kludge makes sure that the buffer ends in a blank space--otherwise
 * the automaton does not recognize a match. ie. the
 * checking the context for "qumw=|", missed those places where "qumw=|"
 * was the last word in the text searched.
 */
        startp[len++] = ' ';
        startp[len] = 0;
	strcpy(gksel->gkselbufp, startp );


        gksel->gksellen = len;
        

/*
printf("skipped %ld, len %d buf:%s\n\n", startp - sbuf , len , startp );
*/
        free(sbuf);
        return(len);

}

 
static
 InitUnits()
{
        int i = 0;
        InitRun++;


/*
 * you only want to count line/sentence/word boundaries up to beginning
 * of second word/phrase, but you want second word/phrase fully in core
 * so that you can dump both word/phrase + intervening text.
 */


        wordbound[ '.' ] ++;
        wordbound[ ',' ] ++;
        wordbound[ ' ' ] ++;
        wordbound[ ';' ] ++;
        wordbound[ ':' ] ++;
        wordbound[ '_' ] ++;
        wordbound[ '\n' ] ++;

        sentbound[ '.' ] ++;
        sentbound[ ';' ] ++;
        sentbound[ ':' ] ++;

        tlgch[ ')' ]++;
        tlgch[ '(' ]++;
        tlgch[ '/' ]++;
        tlgch[ '\\' ]++;
        tlgch[ '=' ]++;
        tlgch[ '+' ]++;
        tlgch[ '|' ]++;
        tlgch[ '*' ]++;
        tlgch[ '!' ]++;
        tlgch[ '\'' ]++;
        
        for(i='A';i<='Z';i++)
                tlgch[ i ] ++ ;
        for(i='a';i<='z';i++)
                tlgch[ i ] ++ ;

}

static char *
 ssbackup(char * startp,long center,int separation,int units)
{
        register char * s;
        char * lastw;
        char * lastch;
        int cursep = 0;
        int sawchar = 0;

        s = startp + center;
        
#define DROPS()  if( --s <= startp)  return(s) 
        while(s>startp) {
            if( tlgch[ *s ] ) { sawchar++; lastch = s; }
            if( *s == '}' ) {
                while( *s != '{' )
                        DROPS();
            }

            switch(units) {
                case LINE:
                        if( *s == '\n' ) {
        /*
         * check to make sure you aren't looking at a citation reference
         * and make sure there were some textual characters in the previous
         * line
         */
                                if( *(s+1) != '~' && sawchar ) {
                                        if( cursep++ >= separation )
                                                return( lastch );
                                }
                                while( *s == '\n' )
                                        DROPS();
                                sawchar = 0;
                        }
                        break;
                case SENTENCE:
                        if( sentbound[ *s ] ) {
                                if( ++cursep >= separation )
                                        return( lastch );
                        }
                        break;
                case WORD:
                        /*
                         * if you back over a "\n~" then decrement
                         * cursep--you have seen a reference record, not
                         * a valid word.
                         *
                         * assumes that a reference record will appear
                         * as a single word (e.g. string of tlgch's with
                         * no wordbreaks). this seems to be valid except
                         * in the case of reference records that set a title
                         * with two words separated by a blank.
                         * that is not a problem since a context search should
                         * not step over work boundaries anyway.
                         */
                        if( *s == '\n' && *(s+1) == '~' ) {
                                sawchar = 0;
                                cursep--;
                        }
                        if( wordbound[ *s ] ) {
                                lastw = s+1;
                                while( wordbound[ *s ] )
                                        DROPS();
                                while( ! tlgch[ *s ] ) {
                                        /* skip marginalia */
                                        if( *s == '}' ) {
                                                DROPS();
                                                while( *s != '{' )
                                                        DROPS();
                                        }
                                        DROPS();
                                }
                                if( *(s+1) != '-' )  {
                                        if( cursep++ >= separation )
                                                return( lastw );
                                }
                        }
                        break;
                default:
                        break;
            }
            DROPS();
        }
        return(startp);
}

/*
 * returns the number of bytes that a word, starting at bufp takes up.
 * deals with things like hyphenation.
 */
#define ADV_S( ) if(s>=bufp+buflen) return(buflen); else s++; 

static 
 get_wlen_in_text(char * bufp,int buflen)
{
        register char * s = bufp;

        while(bufp<=bufp+buflen) {
                /* deal with hyphenated words */
                if( *s == '-' ) {
                    while( ! tlgch[ *s ] ) {
                        if( *s == '{' ) {
                            while(*s != '}' )
                                ADV_S()
                        }
                        if( *s == '\n' ) {
                            ADV_S()
                            if( *s == '~' ) {
                                while(*s != '\n' ) {
                                     ADV_S()
                                }
                            }
                        }
                        ADV_S()
                    }
                }
                if( wordbound[ *s ] )
                        return(s - bufp );
                else 
                        s++;
        }
}


static
 ssjump(char * startp, int slen,int separation,int units)
{
        char * s = startp;
        char * end = startp + slen;
        int cursep = 0;
        int sawchar = 0;

#define STEPS()  if( ++s >= end)   {*s = 0; return(slen);}

        while( s <= end ) {
            if( tlgch[ *s ] ) sawchar++;
            if( *s == '{' ) {
                while( *s != '}' )
                        STEPS()
            }
            switch( units ) {
                case WORD:
                        /* deal with hyphenated words */
                        if( *s == '-' ) {
                            while( ! tlgch[ *s ] ) {
                                if( *s == '{' ) {
                                    while(*s != '}' )
                                        STEPS()
                                }
                                if( *s == '\n' ) {
                                    STEPS()
                                    if( *s == '~' ) {
                                        while(*s != '\n' ) {
                                             STEPS()
                                        }
                                    }
                                }
                                STEPS()
                            }
                        }
                        if( wordbound[ *s ] ) {
                                if( cursep++ >= separation ) {
                                        *s = 0;
                                        return( (int)(s-startp) );
                                }
                                while( wordbound[ *s ] )
                                        STEPS()
                                /* skip metatext */
                                while( ! tlgch[ *s ] ) {
                                        /* skip marginalia */
                                        if( *s == '{' ) {
                                                STEPS()
                                                while( *s != '}' )
                                                        STEPS()
                                        }
                                        STEPS()
                                }
                        }
                        break;
                case LINE:
                        if( *s == '\n' ) {
        /*
         * check to make sure you aren't looking at a citation reference
         * and make sure there were some textual characters in the previous
         * line
         */
                                if( *(s+1) != '~' && sawchar ) {
                                        if( cursep++ >= separation ) {
                                                *s = 0;
                                                return( s - startp );
                                        }
                                }
                                while( *s == '\n' )
                                        STEPS()
                                sawchar = 0;
                        }
                        break;
                case SENTENCE:
                        if( *s == '{' ) {
                            while( *s != '}' ) 
                                STEPS()
                        }
                        if( *s == '\n' ) {
                            STEPS()
                            if( *s == '~') {
                                while(*s != '\n' )
                                    STEPS()
                            }
                        }
                        if( sentbound[ *s ] ) {
                                if( ++cursep >= separation ) {
                                        STEPS()
                                        *s = 0;
                                        return( s - startp );
                                }
                        }
                        break;
                default:
                        break;
            }
            STEPS()
        }
        return(slen);
}
