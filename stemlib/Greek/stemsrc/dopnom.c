#include <stdio.h>
#include <ctype.h>

main()
{
	char line[BUFSIZ];

	while(gets(line)) {
		char *s;
		if(strncmp(line,":ns:",4)) continue;
		s = line+4;
		printf(":le:");
		while(*s&&!isspace(*s)) putchar(*s++);
		putchar('\n');
		while(isspace(*s)) s++;
		if( strncmp(s,":wd:",4) ) printf(":no:");
		printf("%s\n\n"	, s);

	}
}
