/*	stack.c 1.3 8/21/85	*/

/*	#include <datatypes.h>
 *
 *	Stack  *screate(type,nitems)
 *	short  type;
 *	long   nitem;
 *
 *			Create a stack of nitems. Type must be one of the
 *	following: CHAR,SHORT,LONG,POINTER,FLOAT,or,DOUBLE. Returns NULL
 *	if storage cannot be allocated.
 *
 *
 * 	spush(pitem,stack)
 *	char     *pitem;
 *	Stack    *stack;
 *
 *			Push the item pointed to by pitem on the stack.
 *	Return SUCCESS or FAILURE (if stack is full).
 *
 *
 *	spop(pitem,stack)
 *	char	*pitem;
 *	Stack	*stack;
 *
 *			Get the top item from stack and store it at
 *	pitem. Return SUCCESS or FAILURE ( stack is empty).
 *
 * 
 *	sdestroy(stack)
 *	Stack	*stack;
 *
 *			Destroy the stack and release storage.
 *
 *	written by Raj K. Jhanwar,
 *		Dept. of Electrical & Computer Engineering, 
 *		University of Cincinnati,
 *		July 24,1985.
 */

		
#define SOURCE

#include "usual.h"
#include "datatypes.h"


Stack	*screate(type,nitems)
short	type;
long	nitems;
{
  int	slength;
  Stack	*news;
  char 	*malloc();

	if(( news = ( Stack *) malloc( sizeof( Stack ))) == NULL)
	   return(NULL);
	news->stype = type;
	slength = typsiz[type] * nitems;

	if ((news->sptr = malloc( slength )) == NULL) {
	   free(news);
       	   return(NULL);
	}
	else {
	      news->stop = news->sptr;
	      news->send = news->sptr + slength;
	      return(news);
	}
}



spush(pitem,stack)
char	*pitem;
register Stack *stack;

{
	/* check if stack is full */
	if (stack->stop >= stack->send)
	    return(FAILURE);
	dassign( stack->stype,stack->stop,pitem);
	stack->stop +=typsiz[stack->stype];
	return(SUCCESS);
}


spop(pitem,stack)
char	*pitem;
register Stack *stack;

{
	/* check if stack is empty */
	if (stack->stop <= stack->sptr)
	   return(FAILURE);
	stack->stop -= typsiz[stack->stype];
	dassign( stack->stype,pitem,stack->stop);
	return(SUCCESS);
}


sdestroy(stack)
Stack	*stack;

{
	free(stack->sptr);
	free(stack);
}

