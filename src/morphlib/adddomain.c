#include <gkstring.h>

#include "adddomain.proto.h"

add_domain(gk_string *gstr, int n)
{
	int len;
	char * p = domains_of(gstr);
	
	if( Xstrlen(domains_of(gstr)) >= MAXDOMAINS )
		return(-1);
		
	while(*p) {
		if( *p ==   n )
			return(0);
		p++;
	}
	*p =  n;
	return(1);
}
