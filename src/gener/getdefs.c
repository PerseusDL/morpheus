#include <stdio.h>
#include <ctype.h>
char * malloc();

_main()
{
		int c,hcode;
		char line[BUFSIZ], *s;
		char curlemma[BUFSIZ];
		char number[80], defstr[BUFSIZ*4];
		curlemma[0] = 0;
		
		while(gets(line)) {
			if( !strncmp(line,":le:",4) ) {
				strcpy(curlemma,line+4);
				s = curlemma+strlen(curlemma)-1;
				while(isspace(*s) && s>curlemma) *s-- = 0;
				continue;
			}
			if(line[0] !=':' && line[0] != '?' && line[0] != ';' && line[0] != '@' ) {
				if( line[0] == '[' ) {
					strcpy(number,line+1);
					s = line+1;
					while(*s && *s!=']') s++;
					if( *s )
						*s++ = 0;
				} else {
					s = line;
					strcpy(number,"0");
				}
				while(*s && isspace(*s)) s++;
				strcpy(defstr,s);
				printf("%s\t%s\t%s\n", curlemma, number, defstr );
			}
		}
		
}