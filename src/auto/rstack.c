/*	rstack.c 1.2.1.2 8/19/85	*/

/*	#include <datatypes.h>
 *
 *	Rstack  *rscreate(type,nitems)
 *	short  type;
 *	long   nitem;
 *
 *			Create a rstack of nitems. Type must be one of the
 *	following: CHAR,SHORT,LONG,POINTER,FLOAT,or,DOUBLE. Returns NULL
 *	if storage cannot be allocated.
 *
 *
 * 	rspush(pitem,rstack)
 *	char     *pitem;
 *	register Rstack    *rstack;
 *
 *			Push the item pointed to by pitem on the rstack.
 *	If stack is full then it is over written in circular fashion.	
 *
 *
 *	rspop(pitem,rstack)
 *	char	*pitem;
 *	register Rstack	*rstack;
 *
 *			Get the top item from rstack and store it at
 *	pitem. Return SUCCESS or FAILURE ( if rstack is empty).
 *
 *
 *	rsget(pitem,rstack)
 *      char	*pitem;
 *	register Rstack	*rstack;
 *			Reads the top most unread element of the rstack.
 *	The element is not popped.
 *
 * 
 *	rsreset(rstack)
 *	register Rstack	*rstack;
 *			Resets all the elements of rstack to unread.
 *
 *
 *	rsclear(rstack)
 *	register Rstack	*rstack;
 *			Pops all the elements from the stack.
 *
 *
 * 	rsremove(pitem,rstack)
 * 	register Rstack *rstack;
 *	char     *pitem;
 *		
 *			Oldest element is removed from the rstack.
 *
 *	rsdestroy(rstack)
 *	register Rstack	*rstack;
 *
 *			Destroy the rstack and release storage.
 *
 *	written by Raj K. Jhanwar,
 *		Dept. of Electrical & Computer Engineering, 
 *		University of Cincinnati,
 *		July 24,1985.
 */

		
#define SOURCE

#include <usual.h>
#include <datatypes.h>


Rstack *
rscreate(type,nitems)
short	type;
long	nitems;
{
  int	slength;
  register Rstack	*news;
  char 	*malloc();

	if(( news = ( Rstack *) malloc( sizeof( Rstack ))) == NULL)
	   return(NULL);
	news->rstype = type;
	news->items  = nitems;
	slength = typsiz[type] *  nitems ;

	if ((news->rfirst = malloc( slength )) == NULL) {
	   free(news);
       	   return(NULL);
	}
	else {
	      news->rtop = news->rbottom = news->rptr = news->rfirst;
	      news->rlast = news->rfirst + ( slength -
 					       typsiz[news->rstype] );        
	      news->count = news->rcount = 0;
	      return(news);
	}
}



rspush(pitem,rstack)
char	*pitem;
register Rstack *rstack;

{
	/* increment the counter */
	rstack->count++;
        dassign(rstack->rstype,rstack->rtop,pitem); 
	if ( rstack->rtop == rstack->rlast )
	    rstack->rtop = rstack->rfirst;
	else
	    rstack->rtop += typsiz[rstack->rstype];
	if (rstack->count > rstack->items)  {
	    rstack->rbottom = rstack->rtop;
	    rstack->count = rstack->items;
	}
	/* reset the read pointer */
	rstack->rptr = rstack->rtop;
	rstack->rcount = 0;
	return(SUCCESS);
}


rspop(pitem,rstack)
char	*pitem;
register Rstack *rstack;

{
	/* check if rstack is empty */
	if ( rstack->count == 0 )
	   return(FAILURE);
	if (rstack->rtop == rstack->rptr) {
	    if ( rstack->rtop == rstack->rfirst)  {
		rstack->rptr = rstack->rtop = rstack->rlast;
	    }
	    else  rstack->rtop = rstack->rptr -= typsiz[rstack->rstype];
	    rstack->rcount++;
	}
	else  rstack->rtop -= typsiz[rstack->rstype];
	dassign(rstack->rstype,pitem,rstack->rtop);
	/* decrement the # of elements in the stack */
	rstack->count--;
	if ( rstack->rcount > 0 )  rstack->rcount--;
	return(SUCCESS);
}


rsdestroy(rstack)
register Rstack	*rstack;

{
	free(rstack->rfirst);
	free(rstack);
}

rsget(pitem,rstack)
register Rstack	*rstack;
char	*pitem;
{
	if ( rstack->rcount >= rstack->count )
	   return(FAILURE);
        if ( rstack->rptr == rstack->rfirst)
	   rstack->rptr = rstack->rlast;
        else
           rstack->rptr -= typsiz[rstack->rstype];
	dassign(rstack->rstype,pitem,rstack->rptr);
	rstack->rcount++;
	return(SUCCESS);
}


rsreset( rstack )
register Rstack	*rstack;
{
	rstack->rptr = rstack->rtop;
	rstack->rcount = 0;
}

rsclear( rstack )
register Rstack	*rstack;
{
    char  *pitem;

	rstack->rcount = rstack->count = 0;
	rstack->rptr = rstack->rtop = rstack->rbottom = rstack->rfirst;
}

rsremove(pitem,rstack)
register Rstack *rstack;
char   *pitem;
{
	if ( rstack->count == 0 )
	    return(FAILURE);
	else {
	    dassign(rstack->rstype,pitem,rstack->rbottom);
	    if ( rstack->rbottom == rstack->rlast )
		rstack->rbottom = rstack->rfirst;
	    else
		rstack->rbottom += typsiz[rstack->rstype];
	    rstack->count--;
	    return(SUCCESS);
	}
}
