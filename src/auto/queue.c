/*
 *	#include  <datatypes.h>
 *
 *	Queue  *qcreate( type, nitems )
 *	short  type;
 *	long   nitems;
 *
 *		Create a queue of nitems.  type must be one of the
 *	following:  CHAR, SHORT, LONG, POINTER, FLOAT, or DOUBLE.
 *	Returns NULL if storage cannot be allocated.
 *
 *
 *	qadd( pitem, queue )
 *	char  *pitem;
 *	Queue *queue;
 *
 *		Add the item pointed to by pitem to the queue.  Return
 *	SUCCESS or FAILURE (if the queue is full).
 *
 *
 *	qremove( pitem, queue )
 *	char  *pitem;
 *	Queue *queue;
 *
 *		Get the next item off the queue and store it at pitem.
 *	Return SUCCESS or FAILURE (if queue is empty).
 *
 *
 *	qread( pitem, queue )
 *	char  *pitem;
 *	Queue *queue;
 *
 *		Read next item from queue and store it at pitem but
 *	don't delete item from queue.  Return SUCCESS or FAILURE
 *	if queue has been exhausted.  Read pointer is reset by
 *	calls to qdelete(), qremove(), qreset(), and qclear().
 *
 *
 *	qreset( queue )
 *	Queue *queue;
 *
 *		Reset the read pointer to point to the first element
 *	of queue.
 *
 *
 *	qdelete( nitems, queue )
 *	long   nitems;
 *	Queue *queue;
 *
 *		Delete the first nitems items from the queue.  Return
 *	SUCCESS or FAILURE if there were not that many items on the
 *	queue.
 *
 *
 *	qclear( queue )
 *	Queue *queue;
 *
 *		Delete all items from the queue;
 *
 *
 *	qdestroy( queue )
 *	Queue *queue;
 *
 *		Destroy queue and release storage.
 *
 *
 *	Written by V. J. Harward, University of Cincinnati, 10 July 1985
 */

static char  SCCS_ID[] = "queue.c 1.5 8/10/85";

#define  SOURCE

#include <usual.h>
#include <datatypes.h>


Queue  *
qcreate( type, nitems )
short type;
long nitems;
{
    int    qlength;
    Queue  *newq;
    char   *malloc();

	if (( newq = (Queue *) malloc( sizeof( Queue )) )  == NULL )
	    return( NULL );
	newq->qtype = type;
	newq->qsize = typsiz[type] * (nitems + 1);
	if (( newq->qptr = malloc( newq->qsize )) == NULL )  {
	    free( newq );
	    return( NULL );
	}
	else  {
	    newq->qhead = newq->qtail = newq->qrptr = newq->qptr;
	    newq->qend = newq->qptr + newq->qsize - 1;
	    newq->qitems = 0;
	    return( newq );
	}
}


qadd( pitem, queue )
char  *pitem;
register Queue  *queue;
{
    char  *rear;

	rear = queue->qtail + typsiz[queue->qtype];
	if ( rear > queue->qend )  rear = queue->qptr;
	if ( queue->qhead == rear )		/* queue full? */
	    return( FAILURE );
	dassign( queue->qtype, rear, pitem );
	queue->qitems++;
	queue->qtail = rear;
	return( SUCCESS );
}


qremove( pitem, queue )
char  *pitem;
register Queue  *queue;
{
    char  *front;

	if ( queue->qhead == queue->qtail )	/* queue empty ? */
	    return( FAILURE );

	front = queue->qhead + typsiz[queue->qtype];
	if ( front > queue->qend )  front = queue->qptr;
	dassign( queue->qtype, pitem, front );
	queue->qrptr = queue->qhead = front;
	queue->qitems--;
	return( SUCCESS );
}


qread( pitem, queue )
char  *pitem;
register Queue  *queue;
{
    char  *curr;

	if ( queue->qrptr == queue->qtail )	/* queue exhausted ? */
	    return( FAILURE );

	curr = queue->qrptr + typsiz[queue->qtype];
	if ( curr > queue->qend )  curr = queue->qptr;
	dassign( queue->qtype, pitem, curr );
	queue->qrptr = curr;
	return( SUCCESS );
}


qreset( queue )
Queue *queue;
{
	queue->qrptr = queue->qhead;
}


qdelete( nitems, queue )
long  nitems;
register Queue  *queue;
{
    char  *qtemp;

	if ( nitems < 0 )  {
	    fprintf( stderr, "qdelete: can't delete a negative items\n");
	    exit( 1 );
	}
	if ( nitems > queue->qitems )  {
	    queue->qitems = 0;
	    queue->qrptr = queue->qhead = queue->qtail;
	    return( FAILURE );
	}
	else  {
	    qtemp = queue->qhead + nitems * typsiz[queue->qtype];
	    if ( qtemp > queue->qend )
		qtemp -= queue->qsize;
	    queue->qrptr = queue->qhead = qtemp;
	    queue->qitems -= nitems;
	    return( SUCCESS );
	}
}


qclear( queue )
Queue  *queue;
{
	queue->qrptr = queue->qhead = queue->qtail;
	queue->qitems = 0;
}


qdestroy( queue )
Queue  *queue;
{

	free( queue->qptr );
	free( queue );
}
