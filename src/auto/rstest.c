#include <usual.h>
#include <datatypes.h>

#define MAXLINE 80

Rstack *rstack;

main()
{
    char  cline[MAXLINE];
    char  *qline,*malloc();
    Rstack *rscreate();

	rstack = rscreate( POINTER , 5 );
        printf("ready\n");
	printf("The length of rstack for the test is 5\n");
	printf("Type is POINTER\n");
	printf("Following functions are available:\n");
	printf("	1. pop\n");
	printf("	2. rem (remove)\n");
	printf("	3. get\n");
	printf("	4. reset\n");
	printf("	5. clear\n");
        printf(" just type to 'push'\n");
	while( gets(cline) != NULL)  {
	   if ( !strcmp( cline, "pop")) {
		if ( rspop( &qline, rstack) == FAILURE ) {
		printf("stack empty\n");
		}
		else {
		      printf("%s\n",qline);
		}
	   }
	   else  {
		if ( !strcmp( cline, "rem")) {
		   if (rsremove(&qline,rstack)==FAILURE) {
		      printf("No old elements: stack empty\n");
		   }
		   else {
		         printf("%s\n",qline);
		   }
		}
		else {
		if ( !strcmp( cline, "get")) {
		   if (rsget(&qline,rstack)==FAILURE) {
		      printf("All elements read\n");
		   }
		   else {
		         printf("%s\n",qline);
		   }
		}
		else {
		     if (!strcmp(cline,"clear")) {
		         rsclear(rstack);
		     }
		     else {
			   if ( !strcmp( cline, "reset")) {
			       rsreset(rstack);
			   }
			   else {

		    		qline = malloc( strlen(cline) + 1);
				strcpy( qline,cline);
				if ( rspush( &qline,rstack) == FAILURE) 
				printf("stack full\n");
	   	           }
		      }
		   }
		}
	    }
         }
	while( rspop( &qline,rstack) == SUCCESS )
		printf("%s\n");
	printf("stack empty\n");
	rsdestroy(rstack);
	printf("stack destroyed \n");
}

