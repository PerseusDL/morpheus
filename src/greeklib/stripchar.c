#include <stdio.h>
#include <string.h>

#include "stripchar.proto.h"

stripchar(char *s, int c)
{
	register char * s1;
	
	s1 = s;
	
	while(*s1) {
		if( *s1 == c ) {
			strcpy(s1,s1+1);
			continue;
		}
		s1++;
	}
}