#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xstrings.proto.h"

int
Xstrncpy(char *s1, const char *s2, size_t len)
{
/*
strncpy(s1,s2,len);
*/
strcpy(s1,s2);
return(1);
}
	
int
Ystrncpy(char *s1, const char *s2, size_t len)
{
	if( Xstrlen(s2) >= len ) {
		char * p;
		if( len  < 5 || len > BUFSIZ*4 ) {
			fprintf(stderr,"Xstrncpy: hey! len %d for [%s] \n", len, s2 );
		}

		
		p = (char *)malloc((size_t)(len+1));
		if( ! p ) {
			fprintf(stderr,"could not allocate %d byte buf in Xstrncpy!\n", len+1);
			*s1 = 0;
			return;
		}
		strncpy(p,s2,(size_t)len);
		*(p+len-1) = 0;
		strcpy(s1,p);
		xFree(p,"Xstrncpy buffer");
		fprintf(stderr,"%d bytes into %d:%s\n", Xstrlen(s2), len ,s2);
	} else
		strcpy(s1,s2);
}


Xstrncat(char *s1, const char *s2, size_t len)
{
	size_t nlen;
	
	if( len  < 5 || len > BUFSIZ*4 ) {
		fprintf(stderr,"Xstrncat: hey! len %d for [%s] \n", len, s2 );
	}

	if( Xstrlen(s1) + Xstrlen(s2) > len - 1 ) {
		fprintf(stderr,"limit: %d; tacking [%s] + [%s] is too big!\n", len , s1 , s2 );
		nlen = len - Xstrlen(s1) - 1;
fprintf(stderr,"nlen %d\n", nlen );
		strncat(s1,s2,(size_t)nlen);
		*(s1+len-1) = 0;
	} else
		strcat(s1,s2);
}

Xstrncmp(const char *s1, const char *s2, size_t len)
{
	return(strncmp(s1,s2,(size_t)len));
}

Xstrlen(const char *s)
{
	return((int)strlen(s));
}

/*
strcpy(char *s1, const char *s2)
{
	while(*s2) {
		*s1++ = *s2++;
	}
	*s1 = 0;
}
*/
