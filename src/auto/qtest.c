#include  <usual.h>
#include  "../../include/datatypes.h"

#define  MAXLINE  80

Queue  *queue;

main()
{
    int   nitems;
    char  cline[MAXLINE];
    char *qline, *malloc();
    Queue *qcreate();

	queue = qcreate( POINTER, 5 );
	printf("ready\n");
	while ( gets(cline) != NULL )  {
	    if ( !strcmp( cline, "remove" ))  {
		if ( qremove( &qline, queue ) == FAILURE )  {
		    printf("queue empty\n");
		    continue;
		}
		else  {
		    printf("%s\n", qline);
		}
	    }
	    else if ( !strcmp( cline, "read" ))  {
		if ( qread( &qline, queue ) == FAILURE )  {
		    printf("queue exhausted\n");
		    continue;
		}
		else  {
		    printf("%s\n", qline);
		}
	    }
	    else if ( !strcmp( cline, "reset" ))  {
		qreset( queue );
	    }
	    else if ( !strcmp( cline, "clear" ))  {
		qclear( queue );
	    }
	    else if ( !strncmp( cline, "delete ", 7 ))  {
		if ( sscanf( cline, "delete %d", &nitems ) != 1 )  {
		    printf("What?\n");
		    continue;
		}
		if ( qdelete( nitems, queue ) == FAILURE )
		    printf("too many items\n");
	    }
	    else  {
		qline = malloc( strlen(cline) + 1);
		strcpy( qline, cline);
		if ( qadd( &qline, queue ) == FAILURE )
		    printf("queue full\n");
	    }
	}

	while ( qremove( &qline, queue ) == SUCCESS )
	    printf("%s\n");
	printf("queue empty\n");
}
