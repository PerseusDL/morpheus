#include <gkstring.h>

#include "countendmain.proto.h"
static gk_string Gstr;
char fname[MAXWORDSIZE];
static gk_word Gkword;

_main(void)
{
	FILE * ffname;
	Stemtype stype;
	int is_suffix = 0;
	
	countendtables((Stemtype)(NOUNSTEM|ADJSTEM|PPARTMASK),is_suffix);
}
