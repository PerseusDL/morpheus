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

#define MAXKEY  100
#define WHITE( X ) (X == ' ' || X == '\n' || X == '\t')

extern Centry  betatab[];
extern uchar  *betaesc();

SSauto
InitWords(file,nkeys,ctable,escrout,bufrout)
char * file;
uchar ** nkeys;
Centry  ctable[128];
uchar  *(* escrout)();
long    (* bufrout)();
{
	SSauto tauto;
	int i;
        FILE * fwords;
        char   cline[MAXLINE];
        short svalue;
        short clen;
        uchar *tline, *Malloc();

        if( (fwords=fopen(file , "r")) == NULL ) {
                fprintf(stderr,"could not open %s\n", file );
                return( NULL );
        }

        svalue = 0;
        while ( fgets(cline,sizeof cline , fwords) != NULL )  {
            if( s_blank( cline ) )
                continue;
	    trim_white(cline);
            s_wd_division(cline);
            clen = strlen( cline );
            tline = Malloc( clen + 1);
            strncpy( tline, cline, clen );
            nkeys[svalue] = tline;
            svalue++;
        }
        fclose( fwords );

        return( ssinit( svalue, nkeys, NULL, ctable, escrout, bufrout));
}
/*
 * standardize word division: by convention '@' marks a word boundary
 * in TLG search programs, but the automaton recognizes ' ' as a word
 * boundary. using a space complicates instances where you want to 
 * put a multi-word phrase on the command line (e.g. kai@dh@kai).
 * this routine converts '@' in a string to  ' '.
 */
s_wd_division(s) 
register char * s;
{
        while( *s ) {
                if( *s == '@' )
                        *s = ' ';
                s++;
        }
}
        

static int initialized = 0;
static SSauto tauto;

SSauto InitWords();

CheckContext(wfile,max)
char * wfile;
int max;
{
        static uchar buf[2048];
        static uchar keys[MAXKEY+1];
        
        if( initialized ) {
                printf("can only call check_context once!\n");
                return(-1);
        }
        initialized = 1;

        ssetbuf((long)1,buf);
        if( (tauto = InitWords(wfile,keys,betatab,betaesc,ssonebuf)) == NULL ){
                printf("could not initialize context automaton!\n");
                return( -1 );
        }
        InitContext(max,tauto);
}
