#include "usual.h"
#include "datatypes.h"

#define MAXLINE 80

Stack *stack;

main()
{
    char  cline[MAXLINE];
    char  *qline,*malloc();
    Stack *screate();

	stack = screate( POINTER , 10 );
        printf("ready\n");
	printf("The length of stack for the test is 10\n");
	printf("Type is LONG\n");
	printf("To pop type 'pop' and to push just type one");
        printf(" number/line\n");
	while( gets(cline) != NULL)  {
	   if ( !strcmp( cline, "pop")) {
		if ( spop( &qline, stack) == FAILURE ) {
		printf("stack empty\n");
		}
		else {
		      printf("%s\n",qline);
		}
	   }
	   else  {
		    		qline = malloc( strlen(cline) + 1);
				strcpy( qline,cline);
				if ( spush( &qline,stack) == FAILURE) 
				printf("stack full\n");
		}
	}
	while( spop( &qline,stack) == SUCCESS )
		printf("%s\n");
	printf("stack empty\n");
	sdestroy(stack);
	printf("stack destroyed \n");
}

