#include <greek.h>

set_baseentry(source,baseentry,n)
char * source;
char * baseentry;
int n;
{
	char * s = baseentry;
	
	Xstrncpy(baseentry,source,n);
	
	/*
	 * grab the first two words
	 */
	while(*s&&!isspace(*s)) s++; while(isspace(*s)) s++;
	while(*s&&!isspace(*s)) s++; *s = 0;
	
}

clear_globs(s)
char *s;
{
	while(isspace(*s)) s++;
	while(*s&&!isspace(*s)) {
		if(*s == ',' ) *s = ' ';
		s++;
	}

}

FILE * fbumwords = NULL;
FILE * foddkeys = NULL;

SawBadForm(lemmastr, stemstr, stemkeys )
char * lemmastr;
char * stemstr;
char * stemkeys;
{
	if( ! fbumwords ) {
		if( ! (fbumwords = fopen("bumwords","w")) ) {
			return(0);
		}
	}
	fprintf(fbumwords,"%s\t%s\t%s\n\n", lemmastr, stemstr, stemkeys );
}

ShowOddKeys(lemmastr,s)
char * lemmastr;
char *s;
{
	if( ! foddkeys ) {
		if( ! ( foddkeys = fopen("oddkeys2","w")) ) {
				return(0);
		}
	}
	fprintf(foddkeys,"%s\t%s\n", lemmastr, s );
	
}
