/*
 * gregory crane
 */
 
#include <greek.h>

#include "checkaccent.proto.h"


checkaccent(char *word, int *syll, int *acc)
{
	*syll = ULTIMA;
	if( (*acc=getaccent(word,*syll)) != NOACCENT)
		return(ULTIMA);
		
	*syll = PENULT;
	if( (*acc=getaccent(word,*syll)) != NOACCENT)
		return(PENULT);
		
	*syll = ANTEPENULT;
	if( (*acc=getaccent(word,*syll)) != NOACCENT)
		return(ANTEPENULT);
	*acc = NOACCENT;
	*syll = -1;		
	return(-1);
}
