#include <stdio.h>
#include <ctype.h>

main()
{
	char line[BUFSIZ];

	char * s;
	while(gets(line)) {
		s = line;
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) s++;
		printf("%s\n", s );
	}
}
