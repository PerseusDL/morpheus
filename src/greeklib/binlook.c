#include <greek.h>

int BinLookPrnt = 0;

binlook(char *table, char *tag, int nelems, int size, bool exact_match, int (*compare )())
{
	int high;
	int low;
	int mid;
	int comp;
	int i;
	long offset;

	high = nelems-1;
	low = 0 ;


	while( low<=high ) {
		mid = (low+high)/2 ;
		offset = (long)(mid) * (long)size;

		comp = (*compare)( tag , (char *)table+offset );
if( BinLookPrnt )
printf("off %ld comparing [%s] and [%s]\n", offset, tag ,table+offset);

		if( comp < 0 ) 
			high = mid - 1 ;
		else if ( comp > 0 )
			low = mid + 1;
		else  { /* found match */
if( BinLookPrnt )
printf("A returning with tag [%s] tagstring [%s]\n", tag, table+offset  );

 			return(mid);
		}
	}

if( BinLookPrnt )
printf("B mid %d nelems %d with em %d tag [%s] tagstring [%s]\n",mid,nelems,exact_match, tag, table +(size * mid) );

	if( exact_match ) return(-1);
	if( mid > 0 ) {
		for(i=mid-1;i<nelems;i++) {
			offset = (long) size * (long)i;
			if( (*compare)(tag,table+offset) < 0 ) {
				break;
			}
		}
		if( i > 0 ) i--;
	} else
		i = 0;

if( BinLookPrnt )
printf("C returning with i %d tag [%s] tagstring [%s]\n",i, tag, table + offset );

	return( i );
}
