/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 * this module contains some simple versions of routines that appear elsewhere.
 * this allows subsets of the programs to be compiled.
 */
#include "srchstate.h"


static long * PrecArr;

#if AUTOMATON == 0
fadd_newline(f)
  FILE * f;
{
        fprintf(f,"\n");
}
#endif



 ftlg_offs(srch,pA)
  srch_state * srch;
  long pA;
{
        int i;

                PrecArr = (long  *)calloc((size_t)srch->freq,sizeof * PrecArr );
                if( ! PrecArr) {
                        fprintf(stderr,"Could not allocate PrecArr ");
                        fprintf(stderr,"%ld units long!\n", srch->freq );
                        return(-1);
                }


        if( ! GetPrecArr(PrecArr,srch->p2,srch->freq,srch->sname)){
                fprintf(stderr,"Error in GetPrecArr\n");
                return(-1);
        }
                
        for(i=0;i<srch->freq;i++) {
                srch->pword = *(PrecArr+i);


#if AUTOMATON
                if( srch->rflags & TWOWORDS ) {
			int wasclosed = 0;

			if( ! TxtOpen(srch->sname) ) {
				wasclosed = 1;
				OpTxtFile(srch->sname);
			}
                        circ_search(srch,srch->pword );
			if( wasclosed )
				ClTxtFile(srch->sname);
                } else {
#endif
                        workbyoff( srch , srch->pword );
                        fput_rec(stdout,srch," ");
#if AUTOMATON
                }
#endif
        }
        free(PrecArr);
        return( 1 );
}

long memtot;

char *
Calloc(nitems,sizeitem)
unsigned nitems;
unsigned sizeitem;
{
	memtot += (long) (nitems * sizeitem);
	return(calloc(nitems,sizeitem));
}

char *
Malloc(nbytes)
size_t nbytes;
{
	memtot += nbytes;
	return(malloc(nbytes));
}
