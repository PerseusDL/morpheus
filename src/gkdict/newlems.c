#include <greek.h>


char half1[BUFSIZ];

main()
{
	char line[BUFSIZ];
	char savel[BUFSIZ];
	char curw[BUFSIZ];
	char *hp;

	while(gets(line)) {
		strcpy(savel,line);
		hp = strtok(line," \t");
		if( ! hp ) continue;
		hp = strchr(line,'-');
		strcpy(curw,line);
		if(hp==line) buildw(curw,half1,line);
/*sprintf(curw,"%s%s", half1, line);*/
		else if( hp) {
			strcpy(half1,line);
			half1[hp-line] = 0;
			stripacc(half1);
		}
		/*else half1[0] = 0;*/
		printf("%d %s %s\n", checkcurw(curw), curw , savel);
/*
		printf("[%s] [%s]\n", curw , line );
*/

		/*printf("%d:%s\n", hp != NULL, line );*/
	}
}

buildw(char *targ,char *h1, char *h2)
{
	sprintf(targ,"%s%s", h1 , h2);
	if( !hasaccent(targ)) putsimpleacc(targ);
}

checkcurw(char*curw)
{
	char tmp[BUFSIZ];
	char keybuf[BUFSIZ];
	int rval = 0;
	
	strcpy(tmp,curw);
	keybuf[0] = 0;

	stripmetachars(tmp);
	
	rval = chckdictent(tmp,keybuf);
/*
 * e.g., look for words that may have multiple entries: e.g., le/gw1, le/gw2
 */
	if( !rval ) {
		strcat(tmp,"1");
		rval = chckdictent(tmp,keybuf);

	}
	return(rval);
}

