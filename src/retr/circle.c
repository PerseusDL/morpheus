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
#define MAXRANGE 4096

    static int len;
    static long scanned;
    static drops;
    static hits;
    uchar * ssbackup();
    static long ssp_start; /* start of search space */
    static SSauto query = NULL;
    static GkSelection Gksel;

    static srch_state * tmp_srch = NULL;
    long dummy_zap();
    char * Calloc();
    long TxtFtell();
    long TxtFseek();
 
 circ_search(srch,ccenter)
  srch_state * srch;
  long ccenter;
{
        char centerw[MAXWORD+1];
        long centerp;
        long savepos;
        SSmatch  Pmatch;
        long lseek();

        strncpy(Gksel.gkselauth,srch->sname,sizeof Gksel.gkselauth);
        Gksel.gkselcenter = ccenter;
        drops++;

        if( ! query ) {
                printf("circ_search:query not initialized!\n");
                return(ERROR);
        }

        if( Gksel.gkselbufp ) 
                free(Gksel.gkselbufp);
        Gksel.gkselunits = srch->sepunits;
        Gksel.gkselnunits = srch->lsep;
        Gksel.gkselbufp = (char *) Calloc((unsigned)(Gksel.gkselnunits * Gksel.gkselunits) + 1 , sizeof * Gksel.gkselbufp );
        if( Gksel.gkselbufp == NULL ) {
                fprintf(stderr,"Gksel.gkselbufp not initialized!");
                return(ERROR);
        }
        if( ! tmp_srch ) {
                tmp_srch = (srch_state *) Calloc( 1 , sizeof * tmp_srch );
        }
        savepos = TxtFtell(srch->sname);


        ssreset( query );
        len = GkselByOff(&Gksel);
        if( query ) {
                query->ssobuf = query->ssiptr = (uchar *)Gksel.gkselbufp;
                query->ssict = len;
                query->ssoofft = Gksel.gkselstart;
        }

        Gksel.gksellen = len;
        scanned += len;
        ssetbuf( (long)len , Gksel.gkselbufp );
        query->sscbuf = (uchar *)Gksel.gkselbufp;
        query->ssbufr = dummy_zap;
        ssctxt(EOT);
        centerp = srch->pword;
        while( ( Pmatch = ssearch( query )) != NULL ) {
        /*
         * first, check to make sure that this word does not overlap with
         * the main word, around which this buffer is built. ie., if you
         * are looking for a word repeated, you want to be able to ignore
         * the first instance of the word.
         */
                if( Pmatch->moffset >= srch->pword && 
                  Pmatch->moffset <= Gksel.gkselcEnd ) {
                        continue;
                }

                (* tmp_srch) = (* srch);
                if( tmp_srch->rflags & VERBOSE ) {
                        printf("%s\n\n", query->ssobuf );
                }
                hits++;
                strcpy( centerw , tmp_srch->gotstr );
                if( Pmatch->moffset > tmp_srch->pword ) {
                        tmp_srch->pword = centerp;
                        strcpy( tmp_srch->gotstr , centerw );
                        tmp_srch->pw2 = Pmatch->moffset;
                        strcpy( tmp_srch->gotstr2 , Pmatch->mstring );
                } else {
                        tmp_srch->pw2 = centerp;
                        tmp_srch->pword = Pmatch->moffset;
                        strcpy( tmp_srch->gotstr2 , centerw );
                        strcpy( tmp_srch->gotstr , Pmatch->mstring );
                }
                workbyoff(tmp_srch,tmp_srch->pword);
                fput_rec( stdout, tmp_srch , " " );
        }
        srch->pword = srch->pw2 = 0;
        TxtFseek(srch->sname,savepos);
}

long
 dummy_zap()
{
        return(0);
}


 InitContext(max,matchquery)
  int max;
  SSauto matchquery;
{
        query = matchquery;

}


 circ_hits()
{
        printf("%ld bytes scanned, %d drops, %d hits\n", scanned , drops , hits );
}
