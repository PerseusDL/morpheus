/* 
 * Greg Crane - Harvard
 * Jud Harward - Cincinnati
 * 1984-1985
 */
#include <greek.h>

#define DECALPHA 1
#include "vaxwords.proto.h"

/*
 * read in a 32 bit data word that has been written out to the disk on
 * a vax -- gets around different byte orders on different machines
 */
get_int32(int32 *lword, FILE *f)
{
	
	int32 tmp;
	int i;
	int c;

	for(*lword=0,i=0;i<4;i++) {
		c = getc(f);
		tmp = (int32)c;
		tmp &= 0377;
		tmp = tmp << (8 * i);

		*lword += tmp;
	}
}

put_int32(int32 *lword, FILE *f)
{
	
	int32 tmp;
	int i;
	int c;

	for(i=0;i<4;i++) {
		tmp = *lword;
		tmp = tmp >> (8 * i);
		c = tmp & 0377;
		fputc(c , f );

	}
}

/*
 * read or write in a double -- note that doubles can be 8 or 10 bytes
 */ 
get_double(double *lword, int dsize, FILE *f)
{
	
	int32 tmp;
	int i;
	int c;

	for(*lword=0,i=0;i<dsize;i++) {
		c = getc(f);
		tmp = (long)c;
		tmp = tmp << (8 * i);

		*lword += tmp;
	}
}

put_double(double *lword, int dsize, FILE *f)
{
	
	int32 tmp;
	int i;
	int c;

	for(i=0;i<dsize;i++) {
		tmp = *lword;
		tmp = tmp >> (8 * i);
		c = tmp & 0377;
		fputc(c , f );

	}
}

/*
 * read in a 16 bit data word that has been written out to the disk on
 * a vax -- gets around different byte orders on different machines
 */
get_short(unsigned short *sword, FILE *f)
{
	unsigned short tmp;
	unsigned short i;
	unsigned int c;

	for(*sword=0,i=0;i<2;i++) {
		c = getc(f);
		tmp = (short)(c&0377);
		tmp = tmp << (8 * i);

		*sword += tmp;
	}
}

put_short(short *sword, FILE *f)
{
	
	unsigned short tmp;
	int i;
	unsigned short c;

	for(i=0;i<2;i++) {
		tmp = *sword;
		tmp = tmp >> (8 * i);
		c = tmp & 0377;
		fputc(c , f );

	}
}

/*
 *	Routine converts reads shorts and longs written into a file in
 *	VAX byte order.
 *
 */


vax_fread(char *Buffer, size_t size, int nswap, FILE *f)
{
    register int i;
    register unsigned t;
    int32 * longp;
    unsigned short * shortp;
     double * doubp, *sdoubp;
/*
     short double * sdoubp;
*/
	
	switch( size )  {

	    case 1:
					/* BYTES */
		return( fread( Buffer, size, nswap , f) );
	    case 2:			/* SHORTS */
		shortp = (unsigned short *)Buffer;

		shortp = (unsigned short *)Buffer;

		for ( i=1; i <= nswap; i++)  {
			get_short(shortp,f);
			shortp++;
		}
		return(nswap);

	    case 4:			/* LONGS */

		longp = ( int32 *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			get_int32(longp,f);
			longp++;
		}
		return(nswap);

		case 8: /* DOUBLES */
#ifdef DECALPHA
		longp = ( int32 *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			get_int32(longp,f);
			longp++;
		}
		return(nswap);

#endif
/*			
		sdoubp = (double *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			get_double((double *)sdoubp,size,f);
			sdoubp++;
		}
		return(nswap);


		case 10:

		doubp = (double *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			get_double(longp,size,f);
			longp++;
		}
		return(nswap);
*/
		
	    default:

		fprintf(stderr, "vax_words: byte swap error, size = %d\n", size);
		return(-1);
	}
}

vax_fwrite(char *Buffer, size_t size, int nswap, FILE *f)
{
    register int i;
    register unsigned t;
    register int32 * longp;
    register short * shortp;
    register double * doubp, *sdoubp;
/*
    register short double * sdoubp;
*/
	
	switch( size )  {
	    case 1:
					/* BYTES */
		return( fwrite( Buffer, size, nswap , f) );

	    case 2:			/* SHORTS */

		shortp = (short *)Buffer;

		for ( i=1; i <= nswap; i++)  {
			put_short(shortp,f);
			shortp++;
		}
		return(nswap);

	    case 4:			/* LONGS */

		longp = (int32 *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			put_int32(longp,f);
			longp++;
		}
		return(nswap);

	    case 8:			/* DOUBLES */
#ifdef DECALPHA
		longp = (int32 *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			put_int32(longp,f);
			longp++;
		}
		return(nswap);
#endif

/*
		sdoubp = (double *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			put_double(sdoubp,size,f);
			longp++;
		}
		return(nswap);
*/

	    case 10:			/* DOUBLES */
/*
		doubp = (double *)Buffer;
		for ( i=1; i <= nswap; i++)  {
			put_double(longp,size,f);
			longp++;
		}
		return(nswap);
*/
	    default:

		fprintf(stderr, "vax_words: byte swap error, size = %d\n", size);
		return(-1);

	}
}
