#include <gkstring.h>

#include "ultform.proto.h"

/*
 * check to see if this form takes an accent on its ending
 * e.g. E(lla/s, E(lla/dos
 */

ultima_form(gk_string *gstr)
{
	return(Is_ultima_accent(morphflags_of(gstr)));
}
