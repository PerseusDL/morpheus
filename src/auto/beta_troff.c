#include <stdio.h>
#include "devices.h"
#include "print.h"

#define MAXLINE 4028

char line[MAXLINE];
main()
{
	int len;

	gk_startup(FILEFORMAT);

	while( fgets(line,sizeof line , stdin) ) {
		if( line[0] == '.' ) {
			printf("%s", line );
			continue;
		}
		zap_emdash(line);
		len=gk_sprint(line,1);
	}
	
}

zap_emdash(s)
char * s;
{
	while(*s) {
		if( *s == '_' )
			*s = ' ';
		s++;
	}
}
