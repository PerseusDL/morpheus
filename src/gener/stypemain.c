#include <stdio.h>
#include <gkstring.h>

gk_word GkWord, BlankGkWord;
gk_string Gstr, AvoidGstr, BlankGstr;
main()
{
	char line[2000];
	char curlemma[LONGSTRING];
	char *s;

	while(fgets(line, 2000, stdin)) {
		if( !strncmp(":le:",line,4)) {
			strcpy(curlemma,line+4);
			continue;
		}
		if( strncmp(":no:",line,4) && strncmp(":wd:",line,4) &&  strncmp(":aj:",line,4) ) continue;
		Gstr = AvoidGstr = BlankGstr;
		GkWord = BlankGkWord;
		s = line;
		while(*s) {
			if(*s == ',' ) *s = ' ';
			s++;
		}
		ScanAsciiKeys((char *)line,&GkWord,&Gstr,&AvoidGstr);	
		if( !stemtype_of(&Gstr)) printf("%s - %s\n", curlemma, line );
	}
}
