#include <greek.h>
/*
 * deal with lemmas from the LSJ
 * 10/3/94 grc
 */

char firsthalf[BUFSIZ];
main()
{
	char line[BUFSIZ];
	char curlem[BUFSIZ];

	while(gets(line)) {
		if( ! line[0] || isspace(line[0]) ) continue;
		
		getlem(line,curlem);
		printf("[%s] [%s]\n", curlem, line );
	}
}


getlem(char *s, char *lem)
{
	char *savelem = lem;
	char *p;

	if(*s == '-' ) {
		strcpy(lem,firsthalf);
		while(*lem) lem++;
	} else
		*lem = 0;
	while(*s&&!isspace(*s)) *lem++ = *s++;
	*lem = 0;

	if((p=strchr(savelem,'-')) && *savelem != '-') {
		strcpy(firsthalf,savelem);
		*(strchr(firsthalf,'-')) = 0;
	}
}
