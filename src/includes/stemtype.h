
#define LEMMA 		01
#define PRES_PPART 	02
#define FUT_PPART	03
#define AOR_PPART	04
#define PERFA_PPART	05
#define PERFP_PPART	06
#define AORP_PPART	07
#define FUTP_PPART	010	
#define IRREG_INDECL	011
#define IRREG_VERB	012
#define INDECL		(04000)


typedef unsigned int Stemtype;

/*
#define VERBSTEM	(0100)
*/

#define DECL1			(0100)
#define DECL2			(0200)
#define DECL3			(0400)
#define DECL4			(01000)
#define DECL5			(02000)
#define ADJSTEM			(04000)
#define NOUNSTEM		(010000)
#define CONNECTIVE		(040001)
#define EXPLETIVE 		(040002)
#define	NUMERAL			(040003)
#define PREPOSITION		(040004)
#define ARTICLE			(040005)
#define PRONOUN			(040006)
#define	INDEF_PRON		(040007)
#define	PERS_PRON		(040010)
#define	REL_PRON		(040011)
#define	INDEF_REL_PRON		(040012)
#define PARTICLE		(040013)
#define CONJUNCT		(040014)
#define ADVERB			(040005)

#define VERBSTEM 		   (01000000)
#define REG_DERIV  	 	   (02000000)
#define PRIM_DERIV  	 	   (04000000)
#define VERB_MASK		 (~077000000)
#define PRIM_CONJ		(PRIM_DERIV|VERBSTEM)
#define REG_CONJ		(REG_DERIV|VERBSTEM)

#define STEMTYPE    (VERBSTEM|DECL1|DECL2|DECL3|DECL4|DECL5|NOUNSTEM|ADJSTEM)

#define PPARTMASK	(070000000)
#define PP_PR		(010000000)
#define PP_FU		(020000000)
#define PP_AO		(030000000)
#define PP_PF		(040000000)
#define PP_PP		(050000000)
#define PP_AP		(060000000)
#define PP_FP		(070000000)
#define PP_VA		(ADJSTEM)
#define PP_VN		(NOUNSTEM)
/* latin supine */
#define PP_SU		(060000000)

#define has_passive_stype(stype) ((stype & PPARTMASK ) == PP_AP)
#define has_middle_stype(stype) (((stype & PPARTMASK ) == PP_FU) || ((stype & PPARTMASK ) == PP_AO))
