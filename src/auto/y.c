#include <stdio.h>

main()
{
	int i;

	for(i=' ';i<256;i++)
		fprintf(stdout,"%c %o %d\r", i , i , i );
}
