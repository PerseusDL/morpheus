#include <greek.h>
#include "strsqz.proto.h"

#include "stripacute.proto.h"

/*
 * gregory crane
 *
 * harvard university
 */
 
 stripacute(char *s)
{
	while(*s) {
		if( *s == ACUTE ) 
				strsqz(s,1);
		s++;
	}
}
