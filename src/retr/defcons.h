/*
 * Copyright Gregory Crane
 * April 1987
 */

#define RECLEN 16
#define MAXLIN 124
#define TOP_EDGE 3
#define MAXSCREEN 20

#define REDRAW          1
#define SCROLLF         2
#define SCROLLB         4
#define PUTLINES        010

#define ERRFILE stdout

#define SHORTS 24
#define LONGS 128
#define MAXREF 40
#define MAXAUTH 256
#define MAX_KEYS 256
#define MAXPATHNAME 512
#define MAXMESS 80

#define SORTFLG         01
#define THESAURUS       02
#define QUIET           04
#define TWOWORDS        010     /* looking for two words/phrases */
/* 5 - 8 */
#define TLGREAD         020     /* paging through a text, using tlgread */
#define VERBOSE         040
#define TLGREF          0100
#define TLGEXP          0200
/* 9 - 12 */
#define JUSTREF         0400
#define FULLREC         01000
#define JUSTLINE        02000
#define LINEAR          04000   /* running linear search */
/* 13 - 16 */
#define SUBWIND         010000  /* sub window */
#define BYTEFLAG        020000  /* dump number of bytes scanned */
#define INDEX           040000  /* scanning through an index */
#define SHOWOFFS        0100000 /* show individual offsets */
/* 17 - 20 */
#define SUBSRCH         0200000 /* sub search */
#define BETAFORM        0400000 /* dump greek in beta format */
#define GET_PASS        01000000 /* get a pointer to a specific passage */
#define ONLY_VIEW_CHARS 02000000 /* ignore all but chars and accents in search */
/* 21 - 24 */
#define FIRSTLINE       04000000 /* first line of passage */
#define PRINTFLAG       010000000 /* print  */
#define USE_CD          020000000 /* author is on CDFS  */
#define USE_HD          040000000 /* author is on Hard Disk  */
/* 25 - 28 */
#define SPELL_CHECK	0100000000


/* return values */

/*
 *      -1      exit
 *       0      go on to next record in record list.
 *       1      consult list of records
 *       2      have chosen a record, but do not need to consult rec list.
 *       4      go back to top window.
 *       010    advance
 *       020    go back to previous level
 */

#define ERROR          -1
#define NEXTREC         0
#define RECLIST         01
#define GOTREC          02
#define TOPWIND         04
#define ADVANCE         010
#define PREVLEV         020
#define OK              040

#define MAXWORD 40
#define MAXLINE 160
#define MAXSENT 512
#define LINE MAXLINE
#define SENTENCE MAXSENT
#define WORD MAXWORD

#define BIGINDNAME      "bigind"

#define DIACRITS( X ) ( X == ')' || X == '(' || X == '=' || X == '\\' || X == '/' || X == '|' || X == '?' || X == '+' || X == '*' )
#define ISTLGC( X ) ( DIACRITS( X ) || isalpha( X ) )
#define WHITE( X ) ( X == '\t' || X == ' ' || X == '\n' )

#define WILDC '.'

#include "sysinc.h"
#include "config.h"
#include <malloc.h>

#if MACINTOSH
#define PATHSEPCHAR ':'
#else
#define PATHSEPCHAR '/'
#endif

typedef unsigned int int32;
