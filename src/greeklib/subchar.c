/*
 * gregory crane
 * 
 * harvard university
 */
 
#include <greek.h>

#include "subchar.proto.h"

subchar(char *s, int c1, int c2)
{
	while(*s) {
		if(*s == c1) *s = c2;
		s++;
	}
}