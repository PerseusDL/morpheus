#include  <usual.h>
#include  "../../include/datatypes.h"

#define  MAXLINE  80

Queue  *queue;

main()
{
    int   nitems;
    char  cline[MAXLINE];
    char  qchar, *malloc();
    Queue *qcreate();

	queue = qcreate( CHAR, 5 );
	printf("ready\n");
	while ( gets(cline) != NULL )  {
	    if ( !strcmp( cline, "remove" ))  {
		if ( qremove( &qchar, queue ) == FAILURE )  {
		    printf("queue empty\n");
		    continue;
		}
		else  {
		    printf("%c\n", qchar);
		}
	    }
	    else if ( !strcmp( cline, "read" ))  {
		if ( qread( &qchar, queue ) == FAILURE )  {
		    printf("queue exhausted\n");
		    continue;
		}
		else  {
		    printf("%c\n", qchar);
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
		qchar = cline[0];
		if ( qadd( &qchar, queue ) == FAILURE )
		    printf("queue full\n");
	    }
	}

	while ( qremove( &qchar, queue ) == SUCCESS )
	    printf("%c\n");
	printf("queue empty\n");
}
