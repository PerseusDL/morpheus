/* dialects */
/* #define ALL_DIAL	01 */

/*
 * Dialects
 *
 * arranged as according to C. D. Buck, The Greek Dialects (Chicago 1955) p. 9.
 *
 * yes, yes, i know--this is 30 years old, and can be improved upon, but it 
 * will do for now.
 *		GRC 6/6/87
 */
#define ATTIC		02
#define IONIC		010
#define AEOLIC		020
#define LESBIAN		040
#define HOMERIC		0100 /* add this as separate dialect */
#define DORIC 		0200
#define PARADIGM		0400
#define ALL_DIAL	0
#define RHO_ETA_DIAL	(EPIC|IONIC)
#define RHO_ALPHA_DIAL	(ATTIC|DORIC|AEOLIC)

/*#define POETIC		01000*/
#define NON_HOMERIC_EPIC		02000
#define EPIC		(NON_HOMERIC_EPIC|HOMERIC)
#define HERODOT		IONIC
#define PROSE		(04000)

#define PHOCIS		01
#define LOCRIS		02
#define ELIS		04

#define LACONIA		020
#define HERACLEA	040
#define MEGARID	0100
#define ARGOLID		0200
#define RHODES		0400
#define COS			01000
#define THERA		02000
#define CYRENE		04000
#define CRETE		010000

#define ARCADIA		020000
#define CYPRUS		040000
#define BOEOTIA		0100000



/*
#define EO_EU_DIAL	IONIC|HOMERIC
#define EO_OU_DIAL 	ATTIC
#define NO_CONTR_FUT 	HOMERIC|IONIC
#define	UN_CONTR 	(IONIC|DORIC|AEOLIC)
#define	EE_EE_DIAL 	(ALL_DIAL & (~ATTIC))
#define	EO_EO_DIAL 	(ALL_DIAL & (~ATTIC))
#define	EOU_EOU_DIAL 	(ALL_DIAL & (~ATTIC))
#define	EW_EW_DIAL 	(ALL_DIAL & (~ATTIC))
#define A_NO_CONTR 	(HOMERIC|DORIC)
#define RHO_ETA_DIAL	(HOMERIC|IONIC)
#define RHO_ALPHA_DIAL	(ATTIC|DORIC)
*/



typedef short Dialect;
typedef int32 GeogRegion;
