#include <greek.h>

#include "morphstrcmp.proto.h"

static char comptab[128];
static char betatab[128];
static int tabinited = 0;
static int betatabinited = 0;

/*
 * Compare strings:  s1>s2: >0  s1==s2: 0  s1<s2: <0
 */
morphstrcmp(char *s1, char *s2)
{
	if( ! tabinited ) {
		init_comptab();
	}
/*
fprintf(stderr,"looking at [%s] and [%s]\n", s1, s2 );
*/
	while(1) {
		if(comptab[*s1] != comptab[*s2]) 
			return((int)(comptab[*s1] - comptab[*s2]));
		if (*s1=='\0')
			return(0);
		s1++; s2++;
	}
	return(0);
}

betastrcmp(char *s1, char *s2)
{
	if( ! betatabinited ) {
		init_betatab();
	}
	while(1) {
		while(*s1&&!betatab[*s1]) s1++;
		while(*s2&&!betatab[*s2]) s2++;

		if(betatab[*s1] != betatab[*s2]) 
			return((int)(betatab[*s1] - betatab[*s2]));
		if (*s1=='\0')
			return(strcmp(s1,s2));
		s1++; s2++;
	}
/*
 * if the two strings are equal alphanumerically,
 * then check the rest
 */
 
	return(strcmp(s1,s2));

}

morphstrncmp(char *s1, char *s2, size_t n)
{
	if( ! tabinited ) {
		init_comptab();
	}
	if (n <= 0) return ( 0 );
	for (; --n && (comptab[*s1] == comptab[*s2]); s1++, s2++) {
		if (!*s1) break;
	}
		
	return ((int)(comptab[*s1] - comptab[*s2]));
}

dictstrcmp(char *s1, char *s2)
{
	register char * t1, * t2;
	t1 = s1; t2 = s2;
	if( ! tabinited ) {
		init_comptab();
	}

	while(1) {
		while(! isalpha(*s1) && *s1 != '|'  && *s1 != HARDLONG && *s1 ) s1++;
		while(! isalpha(*s2) && *s2 != '|'  && *s2 != HARDLONG && *s2 ) s2++;
		if(comptab[*s1] != comptab[*s2]) 
			return(comptab[*s1] - comptab[*s2]);
		if (*s1=='\0'||isspace(*s1))

			return(0);
 /*
 			return(Xstrlen(t1)-Xstrlen(t2));
 */
		s1++; s2++;
/*
		while(! isalpha(*s1) && *s1 != '|'  && *s1 ) s1++;
		while(! isalpha(*s2) && *s2 != '|' && *s2 ) s2++;
*/
	}
}

dictstrncmp(char *s1, char *s2, size_t n)
{
	char b1[BUFSIZ/2];
	char b2[BUFSIZ/2];
	register char * s;
	
	s = b1;
	while(*s1) {
		if( ! isalpha(*s1) ) {
			s1++;
			continue;
		}
		*s++ = *s1++;
	}
	*s = 0;
	
	s = b2;
	while(*s1) {
		if( ! isalpha(*s2) ) {
			s2++;
			continue;
		}
		*s++ = *s2++;
	}
	*s = 0;
	
	return(morphstrncmp(b1,b2,n));
}

init_comptab(void)
{
	int i;
	
	tabinited++;
	for(i=0;i<128;i++)
		comptab[i] = i;
	comptab['|'] = 'i'; /* iota subscript matches as an 'i' */
}

init_betatab(void)
{
	int i;
	
	betatabinited++;
	for(i=0;i<128;i++) {
/*		if( isalpha(i) )*/
			betatab[i] = i;
	}
	betatab['|'] = 'i'; /* iota subscript matches as an 'i' */
	set_gkorder( betatab );
}
