#include <stdio.h>
#include <ctype.h>

main()
{
	char line[BUFSIZ];
	char * s;

	while(gets(line)) {
		s = line;

		while(*s&&!isspace(*s)) {
			if( *s != '_' && *s!= '^' ) putchar(*s);
			s++;
		}
		printf(" %s\n",line );
	}
}

