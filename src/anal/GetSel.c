#include <textedit.h>

#include "GetSel.proto.h"

GetSelection(char *s1, TEHandle te, int n)
{
char *s2;
	int sa, sb;
	
	s2 = *(TEGetText(te))+ (**te).selStart;
	
	if (n > 0)
	{
		while (n-- && (*s1++ = *s2++));
	
		while (n>0)
		{	/* pad out to n chars -- H&S specs it this way... */
		
			*s1++ = '\0';
			n--;
		}
	}
		
}