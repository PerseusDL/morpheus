#include <stdio.h>
#include <ctype.h>

char curlem[BUFSIZ];

main()
{
	char line[BUFSIZ*10];
	while(gets(line)) {
		if( !strncmp(":le:",line,4)) {
			strcpy(curlem,line+4);
			continue;
		}
		if( !strncmp(":no:",line,4) ||  !strncmp(":aj:",line,4)) {
			printf("%s\t%s\n", curlem, line );
		}
	}
}
