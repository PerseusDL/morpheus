#include <ctype.h>

#include "isblank.proto.h"

is_blank(char *s)
{
	while(*s && isspace(*s)) s++;
	if( ! *s  ) return(1);
	return(0);
}
