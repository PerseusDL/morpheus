#include <greek.h>
#define Is_zeroend(X) (X=='*')

#include "stripzeroend.proto.h"
stripzeroend(char *word)
{
	int n;

	n = Xstrlen(word);

	if (Is_zeroend(*(word+n-1)) )
		*(word+n-1) = 0;
}
