#include <stdio.h>

#include "index dict.proto.h"

main(void)
{
	char line[256];
	char stemkeys[256];
	int rval;
	
	printf("dictionary? ");
	gets(line);
	printf("munch %s\n", line );
	rval = index_list(line,":le:");
	printf("done indexing\n");
}
	