/*
 * Copyright Gregory Crane
 * April 1987
 */

/* if compiling on a vax */
#ifndef VAX
#define VAX 0
#endif
/* if compiling on a MACINTOSH */
#define MACINTOSH 0
/*
 * if you want to use the Automaton in ../auto/gen.a
 * define AUTOMATON as 1
 *
/* should be defined in command line
#define AUTOMATON 1
*/

/* 
 * if using CDFS, you must set CDFS to 1
 *
/* should be defined in command line
#define CDFS 1 
*/
