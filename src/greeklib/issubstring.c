/*
 * Gregory Crane
 * Harvard University
 * February 1987
 *
 * 8/31/88
 */
 
 /*
  * find s1 in s2 
  */
#include <stdio.h>

#include "issubstring.proto.h"
char * 
is_substring(char *s1, char *s2)
{
	int slen;
	register char * p;


	slen = Xstrlen(s1);
	if( ! slen ) return(NULL);
	if(slen > Xstrlen(s2) ) return(NULL);
	
	p = s2;

	while(*p) {
		if(*p == *s1) {
			if( ! Xstrncmp(p,s1,slen))
				return(p);
		}
		p++;
		while(*p && *p != *s1 ) p++;
	}

	return(NULL);
}
