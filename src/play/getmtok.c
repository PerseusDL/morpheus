#include <stdio.h>
#include "y.tab.h"
#include <string.h>

char line[10000];
char anals[10000];

yylex()
{

	while(gets(line)) {
		gets(anals);
		passVal(line);
		if(is_substring(" article",anals)) return ARTICLE;
		if(is_substring("<NL>N",anals)) return(NOUN);
		if(is_substring("<NL>P",anals)) return(NOUN);
		if(is_substring(" prep",anals)) return(PREP);
	}	
	return(0);
}


passVal()
{
        yylval.string = (char *)malloc( (strlen(line) + 1)  );
        if (!yylval.string)
                fprintf(stderr, "Out of memory for %s\n", line );
        else
                strcpy( yylval.string, line );
/*        fprintf(stderr, "%s\n",yylval.string);*/
}

