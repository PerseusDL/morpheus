/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/

/*
 * grc 2/20/88
 */
#include <greek.h>

#include "stripquant.proto.h"

stripquant(char *word)
{
	stripshortmark(word);
	striplongmark(word);
}


stripshortmark(char *word)
{
	register char *p;
	for (p=lastn(word,1);p>=word;p--)
		if( *p == HARDSHORT )
			strsqz(p,1);
}

striplongmark(char *word)
{
	register char *p;
	for (p=lastn(word,1);p>=word;p--)
		if( *p == HARDLONG )
			strsqz(p,1);
}
