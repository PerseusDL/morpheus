/*
 * gregory crane
 *
 * harvard university
 */
 
#include <greek.h>

#include "hasquant.proto.h"


has_quant(char *s)
 {
 	while(*s) {
 		if( *s == HARDLONG || *s == HARDSHORT)
 			return(1);
 		s++;
 	}
 	return(0);
 }