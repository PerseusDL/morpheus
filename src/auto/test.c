#include <stdio.h>
#include "devices.h"
#include "print.h"

	char line[256];
main()
{
	int len;

	gk_startup(GREEK_KEYS);

	gk_sprint("$",0);
	while( fgets(line,sizeof line , stdin) ) {
		len=gk_sprint(line,1);
	}
	
}

