#include <stdio.h>

main()
{
	char line[1000];
	char curlemma[BUFSIZ];
	char *s;
	
	while(gets(line)) {
		if( ! strncmp(":le:",line,4)) {
			strcpy(curlemma,line+4);
			continue;
		}
		printf("%s\t", curlemma );
		s = line+4;
		while(*s&&*s!='-') putchar(*s++);
		if(*s=='-') { putchar(' '); s++;}
		printf("%s\n", s );
	}
}

