#include <stdio.h>

main()
{
	char line[200];

	while(gets(line)) {
		putsimpleacc(line);	
		printf("%s\n", line );
	}
}
