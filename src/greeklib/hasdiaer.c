/*
 * gregory crane
 *
 * harvard university
 */
 
#include <greek.h>

#include "hasdiaer.proto.h"


has_diaeresis(char *s)
 {
 	while(*s) {
 		if( *s == DIAERESIS )
 			return(1);
 		s++;
 	}
 	return(0);
 }