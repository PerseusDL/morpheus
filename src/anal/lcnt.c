#include <stdio.h>
#include <prntflags.h>
int quickflag = 0;

main()
{
	char line[BUFSIZ];
	int n;

	while(gets(line)) {
		n=checkstring(line,(PrntFlags) LEMCOUNT,stdout);
		printf("rval for [%s] is [%d]\n", line, n );
	}
}
