/*
 * grc 2/7/88
 */
 
#include <greek.h>

#include "stripstemsep.proto.h"

stripstemsep(char *word)
{
	register char *p;
	for (p=lastn(word,1);p>=word;p--)
		if( Is_stemsep(*p) )
			strsqz(p,1);
}
