/*
 * Copyright Gregory Crane
 * April 1987
 */

#include        "srchstate.h"

/* 
 * use this loop if you want to do a linear searchon the index or wish to search
 * the whole index
 */
 ScanAuthor(srch)
  srch_state * srch;
{
        InitLinLookup(srch);
        while(NextLinPhrase(srch)) {
                workbyoff(srch,srch->pword);
printf("srch [%s] pword [%ld]\n", srch->gotstr, srch->pword);
		if( srch->rflags & TWOWORDS ) {
			circ_search(srch,srch->pword);
		} else {
			fput_rec( stdout , srch , "\t" );
			srch->nitems++;
		}
        }
	return(srch->nitems);
}

 ScanOneWordInAuthor(srch)
  srch_state * srch;
{
        InitLinLookup(srch);
        NextLinPhrase(srch);
	workbyoff(srch,srch->pword);
	ClTxtFile(srch->sname);
}
