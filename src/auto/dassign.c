/*
 *	#include  <datatypes.h>
 *
 *	dassign( TYPE, destin, source )
 *	short  TYPE;
 *	char  *destin;
 *	char  *source;
 *
 *		dassign() is a general data assignment routine for
 *	use with the datatypes package (queue, stack, rstack, etc.)
 *	It copies a data element of type TYPE (CHAR, SHORT, LONG,
 *	POINTER, FLOAT, or DOUBLE) stored at a location pointed to
 *	by source to a location pointed to by destin.  The routine
 *	is portable and gets around data typing although it requires
 *	an extra subroutine call.
 */

static char  SCCS_ID[]= "dassign.c 1.2 8/19/85";

#include  <stdio.h>
#include  <datatypes.h>

dassign( type, destin, source )
short  type;
char  *destin;
char  *source;
{

	switch ( type )  {

	    case CHAR:
		* destin = * source;
		break;

	    case SHORT:
		* (short *) destin = * (short *) source;
		break;

	    case LONG:
		* (long *) destin = * (long *) source;
		break;

	    case POINTER:
		* (char **) destin = * (char **) source;
		break;

	    case FLOAT:
		* (float *) destin = * (float *) source;
		break;

	    case DOUBLE:
		* (double *) destin = * (double *) source;
		break;

	    default:
		fprintf( stderr, "dassign: illegal data type\n" );
		exit( 1 );
	}
}
