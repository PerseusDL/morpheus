#include <stdio.h>
#include <netinet/in.h>

main()
{
	long int i = 0;

	FILE *f;
	int n = 0;
	f=fopen("fred","wb");
	if( ! f ) {
		fprintf(stderr,"could not open output file!\n");
		exit(1);
	}
	for(i=0;i<10;i++) {
		n = htonl((unsigned int)i);
printf("na=%d size of n %d\n", n , sizeof n );		
		n = ntohl((unsigned int)n);
printf("nb=%d size of n %d\n", n , sizeof n );		
		fwrite(&n, sizeof n, (size_t) 1, f);
	}
	fclose(f);

	
}
