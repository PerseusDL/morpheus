/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#include "../auto/devices.h"


parseref(srch,p)
srch_state * srch;
char * p;
{
	char * getf();
	char tmpbuf[BUFSIZ];
	char * s;
	int i;
	int still_chars = 1;
	int have_reference = 0;
	int SecondHalfOfRange = 0;
	srch_state SecSrch;

	strncpy(tmpbuf,p,sizeof tmpbuf );
	p = tmpbuf;
	for(i=0;still_chars;p=s,i++) {
		while( WHITE(*p) && *p )
			p++;
		s = p;
		while( ! WHITE(*s) && *s )
			s++;
		if( ! *s ) still_chars = 0;
		*s = 0;
		s++;
		printf("p:[%s]\n", p );

	    if( *p == '-' ) {
		i = 0;
		SecondHalfOfRange++;
		SecSrch = * srch;
printf("Hah! got a range:[%s]\n", p );
		continue;
	    }
	    if( SecondHalfOfRange ) {
		switch(i) {
			case 1:
				/* 
				 * if it begins with a digit, it better
				 * be a reference of some kind
				 */
				if( isdigit(*p) ) {
				    strcpy( SecSrch.Print_ref , p );
printf("SecSrch:%s\n", SecSrch.Print_ref );
				    if( SetRefFromString(&SecSrch) < 0 ) {
					printf("could not find ref %s in work number %d of %s\n", SecSrch.Print_ref , SecSrch.recwknum , SecSrch.sname );
				    }
printf("p is reference:%s\n", p );
				    srch->pend = SecSrch.pend;
				    break;
				}
			case 2:
				/*
				 * otherwise it should be a string 
				 * to be searched for 
				 */
				SecSrch.l_start = SecSrch.pstart;
				SecSrch.l_len = SecSrch.pend - SecSrch.pstart;
				strcpy(SecSrch.key,p);
printf("SecSrch.key:%s\n", SecSrch.key );
/*
				ScanAuthor(&SecSrch);
*/
				ScanOneWordInAuthor(&SecSrch);
printf("sec range pend:%ld\n", SecSrch.pend );
			        srch->pend = SecSrch.pend;
			default:
				break;
		}
	    } else switch(i) {
		case 0:
			printf("will prompt for argument\n");
			strcpy(srch->sname,p);
printf("sname1:%s\n", srch->sname );
			break;
		case 1:	/* browse author work  OR */
			/* browse author reference */
			
			/* get author name */
printf("sname2:%s\n", srch->sname );
			/* try next arg as a work reference first */
			if( workbykey(srch,p) < 0 ) {
			
			/*
			 * well, if that didn't work, assume its the
			 * first work that you want
			 */
				workbynum(srch,1);
				strcpy( srch->Print_ref , p );
printf("refstring:%s\n", srch->Print_ref );
				SetRefFromString(srch);
				have_reference++;
printf("srch->pstart:%ld\n", srch->pstart );
			} else {
printf("got worknumber:%d\n", srch->recwknum );
				srch->pstart = srch->recwkstart;
				srch->pend = srch->recwkend;
			}
			break;
		case 2:
			if( ! have_reference ) {
				strcpy( srch->Print_ref , p );
				SetRefFromString(srch);
				have_reference++;
			} 
			break;
		case 3:
/*
gk_startup(FILEFORMAT);
OpTxtFile(srch->sname);
save_from_to(srch,srch->pstart,srch->pend+1);
*/

			srch->l_start = srch->pstart;
			srch->l_len = srch->pend - srch->pstart;
			strcpy(srch->key,p);
printf("srch->key:%s\n", srch->key );
/*
			ScanAuthor(srch);
*/
			ScanOneWordInAuthor(srch);
printf("pend:%ld\n", srch->pend );
			srch->pstart = srch->pword;

		default:
			break;
		}
	}	
}
