#include <gkstring.h>

#include "errormess.proto.h"

ErrorMess(char *s)
{
#ifdef LIGHTSPEED
/*
	char tmp[LONGSTRING];
	char * CtoPstr();
	
	Xstrncpy(tmp,s,LONGSTRING);
	CtoPstr(tmp);
	ErrMesg(tmp);*/
	fprintf(stderr,"%s\n", s );
/*
	DebugStr(tmp);
*/
#else
	fprintf(stderr,"%s\n", s );
#endif
}

/*
int sprintf(dest, fmt)
char    *dest;		/* pointer to buffer space *
char    *fmt;		/* pointer to format string *
{
	return xprintf(dest, &fmt,false);
}
*/
