#include <ctype.h>
#include <stdio.h>
#define IS_ACC(X) (X == '\\' || X == '/' || X == '=' || X == '+' || X == '|' )
#define IS_BREATH(X) (X == '(' || X == ')' )

stripdiacrit(s)
char * s;
{
	stripaccent(s);
	stripbreathing(s);
}


stripaccent(s)
register char * s;
{
	while(*s) {
		if( IS_ACC(*s) ) {
			strcpy(s,s+1);
			continue;
		}
		s++;
	}
		
}

stripbreathing(s)
register char * s;
{
	while(*s) {
		if( IS_BREATH(*s) ) {
			strcpy(s,s+1);
			continue;
		}
		s++;
	}
		
}


has_accent(s)
register char *s;
{
	while(*s) {
		if( IS_ACC(*s) ) 
			return(1);
		s++;
	}
	return(0);
}

#define Is_vowel(X) (X=='a'||X=='e'||X=='i'||X=='o'||X=='u'||X=='h'||X=='w')

lacks_breathing(s)
register char * s;
{
	register char * t = s;
	int vowel = 0;

	while(*s) {
		if( isalpha(*s) ) {
			if( Is_vowel(*s) )
				vowel++;
			break;
		}
		s++;
	}

	s = t;
	while(*s) {
		if( *s == '*' || Is_vowel(*s) )
			break;
		s++;
	}
	if( vowel ) {
		if( !IS_BREATH(*(s+1)) && !IS_BREATH(*(s+2)) )
			return(1);
	}
	return(0);
}
