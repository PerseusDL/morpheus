/*
 * Greg Crane 
 * June 1987
 */

#include <gkstring.h>
#define MAXCONTRACTS 10
#define MAXSUBSTRING 10
Dialect AndDialect();
#include "libfiles.h"


gk_string *poss_contracts(gk_string *, Dialect);
gk_string * load_euph_tab();
char * is_substring();

static gk_string Blnk;

