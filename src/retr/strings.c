#include <srchstate.h>

trim_white(s)
char * s;
{
	char tmp[MAXLINE];
	char * a;
	char * b;

/*
 * skip any leading white space
 */
	a = s;
	while(WHITE(*a)) a++;

/*
 * trim any trailing whitespace
 */
	b = a;
	while(*b) b++; b--;

	while(WHITE(*b))  {
		*b-- = 0;
	}
	
	strcpy(s,a);
}

s_blank(s)
register char * s;
{
        while( *s ) {
                if( ISTLGC( *s ) )
                        return( 0 );
                s++;
        }
        return( 1 );
}
