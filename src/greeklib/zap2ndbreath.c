#include <greek.h>

#include "zap2ndbreath.proto.h"

/*
 * "e)nh(/bwsa" --> "e)nh/bwsa"
 * "parh(/bwsa" --> "parh/bwsa"
 */

zap_extra_breath(char *s)
{
	int breath_is_extra = 0;
	
	if( *s == 'r' && *(s+1) == ROUGHBR ) s += 2;
	
	while(*s) {
	
		if( Is_cons(*s) ) {
			breath_is_extra++;
			s++;
			continue;
		}
		
		if( *s == ROUGHBR || *s == SMOOTHBR  ) {
			if( ! breath_is_extra ) {
				breath_is_extra++;
				s++;
				continue;
			}
			strcpy(s,s+1);
		}
		s++;
	}
}

has_extra_breath(char *s)
{	
	int breath_is_extra = 0;
	while(*s) {
		if( Is_cons(*s) ) {
			breath_is_extra++;
			s++;
			continue;
		}
	
		if( *s == ROUGHBR || *s == SMOOTHBR) {
			if( ! breath_is_extra ) {
				breath_is_extra++;
				s++;
				continue;
			}
			return(1);
		}
		s++;
	}
	return(0);
}

/*
 * grc 11/17/94
 *
 * e.g., go from a)nanti/r)r(hton to a)nanti/rrhton
 */
zap_rr_breath(s)
char *s;
{
	s++; /* careful about r(i/ptw etc. */
	while(*s) {
		if( *s=='r' && *(s+1) == ')' 
		&&  *(s+2)=='r' && *(s+3) == '(' ) {
			strcpy(s,"rr");
			strcat(s,s+4);
		}
		s++;
	}
}
