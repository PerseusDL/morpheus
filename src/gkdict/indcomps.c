#include <stdio.h>
#include <stdlib.h>
#include <gkstring.h>

#include <gkdict.h>
#define MAX_END_TABLE 50000

gk_word GkWord;
gk_word BlnkWord;
gk_string Gstr;
gk_string AvoidGstr;
gk_string Blnk;
char ** stems;
char curlemma[BUFSIZ];

main()
{
	char line[5000];
	char tmp[5000];
	char * s;
	char * tailp;

        while(gets(line)) {
		Gstr = Blnk;
		if( !strncmp(":le:",line,4) ) strcpy(curlemma,line+4);
		if( strncmp(":aj:",line,4) &&  strncmp(":no:",line,4) ) {
			continue;
		}
		
		s = line;
		while(*s) {
			if(*s==',') *s = ' ';
			s++;
		}
		strncpy(gkstring_of(&Gstr),line,MAXWORDSIZE );
		s = gkstring_of(&Gstr);
		while(*s&&!isspace(*s)) s++;
		*s = 0;
		if( (tailp=strchr(gkstring_of(&Gstr),'-')) == NULL ) {
			continue;
		}

		s = line;
		while(*s&&!isspace(*s)) s++;
		
		ScanAsciiKeys((char *)s,&GkWord,&Gstr,&AvoidGstr);
		tmp[0] = 0;
		SprintGkFlags(&Gstr,tmp," ",0);
/*printf("line:%s gkstring:%s\n", line , gkstring_of(&Gstr) );*/
		s = tailp + 1;
		while(*s) {
			if(*s!='_' &&*s!='^') putchar(*s);
			s++;
		}
		putchar('\t');
		printf("%s\t%s\t%s %s\n", tailp+1, tmp, curlemma, gkstring_of(&Gstr)+4 );
	}
	
}
