/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/
#define ANSI 1
/*
#define LIGHTSPEED 1
*/

/*======================================*/
/*	INCLUDES			*/
/*======================================*/

#define DECALPHA 1
#ifdef DECALPHA
typedef unsigned int int32;
#else
typedef unsigned long int32;
#endif

#ifdef SYS5
#include <sys/types.h>
#endif
#ifndef LIGHTSPEED
#include <sys/file.h>
#endif
#include <ctype.h>
#include <stdio.h>
#ifdef ANSI
#include <string.h>
#else
#include <strings.h>
#endif

#include <stdlib.h>
/*======================================*/
/*	GENERAL PURPOSE DEFINES		*/
/*======================================*/

#define	MAXWORDSIZE	60
#define MAXENTRYSIZE	sizeof(analysis)
/* NB this got away from us. Assume "analysis" struct (entry for ANL_EXC
	file) is the largest entry in any of the lists. If this is not
	so, this sucker better get changed accordingly. */
#define MAXBUFSIZE	1024
#define MAXPATHNAME	512
#define	MAXANLS		32
#define	MAXFNAME	64
#define INPSIZE		128
#define	NOUNLBLSIZE	8

#define	YES	1
#define	NO	0
#define COMMENT		'#'
#define CONTCHAR	'>'
#define	IRREGLINE	'~'
#define	GKPRT_OFF	'!'

#define	PRVBSTKSIZE	6	/* preverb stack */
#define MAXPRVBSIZE	8

/* error returns */
#define	I_ERR	-1
#define	P_ERR	(char *) -1
#define	C_ERR	(char) -1
#define	FD_ERR	0

/* null args */
/* useful for lint */
#define	NULL_P	((char *) 0)
#define	ZERO_EXT	((ext_type) 0) /* not a null, really. 0 is a */
					/* perfectly good extension */
/* can't get this one to work, don't know why */
#define NULL_PSTK	((char *) 0)

typedef FILE *grkfd;
typedef int bool;

/*======================================*/
/*	VERBS				*/
/*======================================*/

typedef	int32	ext_type;

typedef struct {
		unsigned f_voice : 3;
		unsigned f_mood : 4;
		unsigned f_tense : 4; /* 11 bits */
		unsigned f_person : 2;
		unsigned f_number : 2; /* 15 bits */
		} verb_form;

typedef struct {
		unsigned f_voice : 3;
		unsigned f_mood : 4;
		unsigned f_tense : 4;	/* 11 bits */
		unsigned f_person : 3;
		unsigned f_number : 3;
		unsigned f_case : 6;  	/* 23 bits */
		unsigned f_degree : 2;
		unsigned f_gender : 4;	/* 29 bits */
		} word_form;

#define  voice_of(vf)	(vf).f_voice
#define  set_voice(vf,val)	voice_of(vf) = (val)
#define  mood_of(vf)	(vf).f_mood
#define  set_mood(vf,val)	mood_of(vf) = (val)
#define  tense_of(vf)	(vf).f_tense
#define  set_tense(vf,val)	tense_of(vf) = (val)
#define  person_of(vf)	(vf).f_person
#define  set_person(vf,val)	person_of(vf) = (val)
#define  number_of(vf)	(vf).f_number
#define  set_number(vf,val)	number_of(vf) = (val)

#define  pernum_of(vf)	(vf).f_person + (vf).f_number
#define  set_pernum(vf,val)	number_of(vf) = (val/4); person_of(vf) = (val&03)


/*
 * grc 1/22/87
 *
#define lemma_of(anal)  anal->lemma
#define set_lemma(anal,lemma)	strncpy(anal->lemma,lemma,sizeof anal->lemma)
replaced with something in <gkstring.h> grc 2/1/87
*/

/* verb tenses */
#define	NTENSES	8
#define SECONDARY 010
#define	PRESENT	01
#define	IMPERF	(02|SECONDARY)
#define	FUTURE	03
#define	AORIST	(04|SECONDARY)
#define	PERFECT	05
#define	PLUPERF	06
#define	FUTPERF	(07|SECONDARY)
#define PASTABSOLUTE	010

/* verb voices */
#define	NVOICES	5
#define	ACTIVE	01
#define	MIDDLE	02
#define	PASSIVE	04
#define	MEDIO_PASS	(MIDDLE|PASSIVE)
#define	DEPONENT	(MIDDLE|ACTIVE)

/* verb moods */
#define	NMOODS	9
#define	INDICATIVE	1
#define	SUBJUNCTIVE	2
#define	OPTATIVE	3
#define	IMPERATIVE	4
#define	INFINITIVE	5
#define	PARTICIPLE	6
#define	GERUNDIVE	7
#define	SUPINE		8
#define	CONDITIONAL		9
/*
#define TOS_VADJ	7
#define TEOS_VADJ	8

#define declines(vf)	((mood_of(vf) == PARTICIPLE) || \
				(mood_of(vf) == TOS_VADJ) || \
				(mood_of(vf) == TEOS_VADJ))
*/

/* person/number */
/*
#define	NPERNUMS	9
#define	SING1	1
#define	SING2	2
#define	SING3	3
#define	DUAL2	4
#define	DUAL3	5
#define	PLUR1	6
#define	PLUR2	7
#define	PLUR3	8
*
* new versions, allowing us to mask bits when we want just sing or plural
* which you can't really do with the values above.
* grc 1/24/87
*
*/
#define	NPERNUMS	9
#define SINGULAR     01
#define DUAL     02
#define PLURAL   04

#define PERS1    01
#define PERS2    02
#define PERS3    04

#define	SING1	(SINGULAR*4) + PERS1
#define	SING2	(SINGULAR*4) + PERS2
#define	SING3	(SINGULAR*4) + PERS3
#define	DUAL2	(DUAL*4) + PERS2
#define	DUAL3	(DUAL*4) + PERS3
#define	PLUR1	(PLURAL*4) + PERS1
#define	PLUR2	(PLURAL*4) + PERS2
#define	PLUR3	(PLURAL*4) + PERS3


#define	NSYNFORMS	241
#define	SYNMAPSIZE	(NSYNFORMS / 8) + 1

/*======================================*/
/*	NOUNS				*/
/*======================================*/

typedef int noun_form;
#define	set_casenum(nounform,casenum)	(nounform) = (1<<(casenum))
#define	add_casenum(nounform,casenum)	(nounform) |= (1<<(casenum))
#define	test_casenum(nounform,casenum)	((nounform) & (1<<(casenum)))

/* cases */
#define NOMINATIVE	01
#define GENITIVE	02
#define DATIVE		04
#define ACCUSATIVE	010
#define VOCATIVE	020
#define ABLATIVE	040
/*
#define LOCATIVE	6
#define INSTRUMENTAL	7
*/

/* nominal forms */
/* we shouldn't use these flags as it is better to keep number and case
 * separate: grc 1/28/87
 */
#define	NCASENUMS	11
#define	NOM_S	0
#define	GEN_S	1
#define	DAT_S	2
#define	ACC_S	3
#define	VOC_S	4
#define	NAV_D	5
#define	GD_D	6
#define	NV_P	7
#define	GEN_P	8
#define	DAT_P	9
#define	ACC_P	10

#define NNOUNCLASSES	80	

/*======================================*/
/*	ADJECTIVES			*/
/*======================================*/

/*
typedef struct {
		int gender;
		int degree;
		} adj_form;
*/
typedef struct {
		unsigned f_case : 6; /* leave plenty of room for weird 
				       * cases like locative and instrumental
				       */
		unsigned f_number : 2;
		unsigned f_gender : 3;
		unsigned f_degree : 2;
		} adj_form;

/* number_of(X) and set_number(X) are defined above with the verbs */
#define  case_of(af)	(af).f_case
#define  set_case(af,val)	case_of(af) = (val)
#define  gender_of(af)	(af).f_gender
#define  set_gender(af,val)	gender_of(af) = (val)
#define  degree_of(af)	(af).f_degree
#define  set_degree(af,val)	degree_of(af) = (val)

/* values for gender field */
#define NGENDERS	6
#define	MASCULINE	01
#define	FEMININE	02
#define	NEUTER		04
#define	ADVERBIAL		010 /* NB!! */
#define	COMMON_GNDR	MASCULINE|FEMININE|NEUTER
/*
#define	COMMON_GNDR	4
*/
/*
#define	ADVERB		5 /* NB!! */

/* values for degree field */
#define NDEGREES	3
#define	POSITIVE	0
#define	COMPARATIVE	1
#define	SUPERLATIVE	2

#define	NADJCLASSES	16

/*======================================*/
/*	OTHER DATA TYPES		*/
/*======================================*/

typedef struct {
		int part_of_speech;
		noun_form noun_info;
		verb_form verb_info;
		adj_form adj_info;
		} form_id;

/* values for part_of_speech field */
#define	NOUN		01
#define	VERB		02
#define ADJECTIVE	03

/* for these, see stemtype.h, grc 2.16/87
#define ADVERB		04
#define	PARTICLE	05
#define	CONJUNCTION	06
#define	PREPOSITION	07*/
/* added these two classes, 2/16/87 grc */
/*
#define	CONNECTIVE	010
#define	PRONOUN		011
#define EXPLETIVE	012
#define NUMERAL	013*/

typedef struct {
		int part_of_speech;
		int listno;
		} list_id_type;

typedef struct {
		list_id_type list_id;
		form_id form;
		int prefl_type;
		} hypoth;

/* preflection types */
#define	NPREFLS		5
#define NO_PREFL	0
#define	SYLL_AUG	1
#define	SYLL_REDUP	2
#define	AUG_REDUP	3
#define	TEMPORAL	4

#define	MAXHYPS	48	/* largest no. of hypotheses for an ending */
#define	TOPHYPEXT	1024

#define	hyp_esize(wlen)     ((wlen) + sizeof(ext_type) + sizeof(hypoth))

typedef struct {
		char lemma[MAXWORDSIZE];
		form_id form;
		} analysis;

/* return codes for analyze() */
/* NB: These are in order, lowest value takes priority */
#define	UTTER_MISS	0
#define	VOCAB_MISS	-1
#define	GENER_MISS	-2

/* return codes for all generate routines */
/* the first 3 are also values for synform_type.vbcode */
/* and exc_entry.exc_code */
#define	GOOD_GENER	0	/* for gener return */
#define NO_CODE		0	/* alias for vbcode & exc_code */
/*#define	DEPONENT	1*/
#define	NONEXISTENT	2
#define NO_LEMMA	3	/* aka word not found */
#define ILLEGAL_FORM	4
#define	BAD_GENDER	5	/* e.g. asked for feminine on 2-ending adj. */
#define	INTERNAL_ERR	6	/* i.e., "This should never happen" */

#define OK_GENER(gen_return)	(((gen_return)==GOOD_GENER) || \
				 ((gen_return)==DEPONENT)   || \
				 ((gen_return)==NONEXISTENT))

typedef struct {
		bool found;
		char retval[MAXENTRYSIZE];
		int offset;
		} lookup_res_type;

typedef struct {
		int entrysz;	/* size of lookup retval only.... */
		bool wordext;	/* does this file carry an extension? */
		struct {
			int c_offset, c_size;
			} index[MAXWORDSIZE];
		} filehead;

/*======================================*/
/*	FILE STUFF			*/
/*======================================*/

#define	NMISC_FILES	9
#define	HYPOTHLIST	0
#define	ANL_EXC		1
#define NOUNLEX		2
#define	NLEX_EXC	3
#define	VERBLEX		4
#define	VLEX_EXC	5
#define	VLEX_SUPPL	6
#define ADJLEX		7
#define	ALEX_EXC	8
#define	Is_misc(filenum)	((filenum) < NMISC_FILES)

/* entry structs for misc files */
typedef struct {
		char stem[MAXWORDSIZE];
		int nclass,gender;
		noun_form irreg;
		} nlex_entry;

typedef struct {
		char vstem[MAXWORDSIZE];
		int vbcode;
		int subsynop;	/* is there subsynoptic irregularity here? */
		} synform_type;

/* values for subsynop field are NO,YES and: */
#define	NO_STEM		2	/* when synform exists only to flag subsynoptic
					irregularity, not to supply a stem */


typedef union {
		struct {
			char synmap[SYNMAPSIZE];
			bool supplflg;	/* are there supplementary forms? */
			} vlex_0;
		synform_type synform;
		} vlex_entry;

#define	NSUPPLS		4
typedef struct {
		struct {
			int syn_num;
			synform_type synform;
			} suppl_syns[NSUPPLS];
		} vlex_suppl_entry;

typedef struct {
		char mstem[MAXWORDSIZE],fstem[MAXWORDSIZE];
		int adjclass;
		noun_form irreg[NGENDERS];
		bool irr_degree[NDEGREES]; /* are comp or sup forms on file ? */
		} alex_entry;		/* used in 0-ext only */

typedef struct {
		char fullword[MAXWORDSIZE];
		int exc_code;
		} exc_entry;

#define	FIRSTNOUNLIST	NMISC_FILES
#define	NNOUNLISTS	94
#define	Is_nounlist(filenum)	((filenum) >= FIRSTNOUNLIST && \
				(filenum) < FIRSTNOUNLIST + NNOUNLISTS )
#define	NOUNLIST(n)	(Is_nounlist(FIRSTNOUNLIST + (n)) ? \
				(FIRSTNOUNLIST + (n)) : I_ERR)

#define	FIRSTVERBLIST	(FIRSTNOUNLIST + NNOUNLISTS)
#define	NVERBLISTS	85
#define	Is_verblist(filenum)	((filenum) >= FIRSTVERBLIST && \
				(filenum) < FIRSTVERBLIST + NVERBLISTS )
#define	VERBLIST(n)	(Is_verblist(FIRSTVERBLIST + (n)) ? \
				(FIRSTVERBLIST + (n)) : I_ERR)

#define	FIRSTADJLIST	(FIRSTVERBLIST + NVERBLISTS)
#define	NADJLISTS	(NADJCLASSES + 5)	/* 0 not used, 1-16, +4 */
#define	Is_adjlist(filenum)	((filenum) >= FIRSTADJLIST && \
				(filenum) < FIRSTADJLIST + NADJLISTS )
#define	ADJLIST(n)	(Is_adjlist(FIRSTADJLIST + (n)) ? \
				(FIRSTADJLIST + (n)) : I_ERR)

#define	RealFile(filenum)	( Is_misc(filenum) || Is_nounlist(filenum) || \
				Is_verblist(filenum) || Is_adjlist(filenum) )

#define	NFILES	(FIRSTADJLIST + NADJLISTS)  /* biggest file number in system */
#define	MAXFILES	10	/* can be open at one time */

#define	CLOSED	I_ERR
/*
#define	GREEKDIR	"/r/husc6/usr/src/local/morpheus/lists/"
#define	FILEBASE	"grk.list"
*/
/*======================================*/
/*	STRING-HANDLING &		*/
/*	LEXICAL MACROS			*/
/*======================================*/

#define lastn(word,n)	(word + Xstrlen(word) - n)
		/* returns pointer to last n chars of word */

#define elided(word)	(*lastn(word,1) == '\'')
#define	aphaeresis(word)	(*(word) == '\'')

#define	Is_alph(c)	((isalpha(c))	/*from ctype.h*/   && \
				((c)!='j')&&((c)!='v')&&((c)!='J')&&((c)!='V'))

#define	Is_shvwl(c) (((c)=='a')||((c)=='e')||((c)=='i')||((c)=='o')||((c)=='u')\
	||((c)=='A')||((c)=='E')||((c)=='I')||((c)=='O')||((c)=='U'))
#define Is_lvwl(c) (((c)=='h')||((c)=='w')||\
	((c)=='H')||((c)=='W'))
#define Is_vowel(c)	((Is_shvwl(c))||(Is_lvwl(c)))
#define Is_cons(c)	((Is_alph(c)) && !(Is_vowel(c)) )
#define Is_dblcons(c) ((c)=='c'||(c)=='y'||(c)=='z')

/*
#define Is_liquid(c) ((c)=='r'||(c)=='l')
#define Is_stop(c) ((c)=='p'||(c)=='b'||(c)=='f' || \
					(c)=='t'||(c)=='d'||(c)=='q' || \
					(c)=='k'||(c)=='g'||(c)=='x')
*/

#define	ACUTE	'/'
#define	GRAVE	'\\'
#define	CIRCUMFLEX	'='
#define	NOACCENT	' '
#define	Is_accent(c)	(((c)==ACUTE)||((c)==GRAVE)||((c)==CIRCUMFLEX))
#define DIAERESIS '+'
#define BETA_UCASE_MARKER '*'

#define	ULTIMA		0
#define	PENULT		1
#define ANTEPENULT	2
#define	LONG	1
#define	SHORT	0

#define	SUBSCR		'|'

#define	HARDLONG	'_'
/* grc 2/15/88 #define	SOFTLONG	'+' */
#define	HARDSHORT	'^'
#define h_AS_ROUGH '!'
#define H_AS_ROUGH '%'
#define STEMSEP 	'-'
#define	Is_quant(c)	(((c)==HARDLONG) /*|| ((c)==SOFTLONG)*/ || ((c)==HARDSHORT))
#define	Is_stemsep(c)	((c)==STEMSEP)
#define Is_diaeresis(c) ((c)==DIAERESIS)

#define	ROUGHBR		'('
#define	SMOOTHBR	')'
#define	Is_breath(c)	(((c)==ROUGHBR) || ((c)==SMOOTHBR))
#define NOBREATH	' '

#define Is_diacrit(c)	((Is_accent(c))||(Is_quant(c))||(Is_breath(c))|| \
				((c)==SUBSCR) || Is_diaeresis(c) )
#define	Is_greek(c)	((Is_alph(c)) || (Is_diacrit(c)) )

/* Smyth 16 */
#define	Is_labial(c)	(((c)=='p')||((c)=='b')||((c)=='f'))
#define	Is_dental(c)	(((c)=='t')||((c)=='d')||((c)=='q'))
/*
grc 8/21/88 added 'c' (xi) to palatals
#define	Is_palatal(c)	(((c)=='k')||((c)=='g')||((c)=='x'))
*/
#define	Is_palatal(c)	(((c)=='k')||((c)=='g')||((c)=='x')||((c)=='c'))
#define	Is_smooth(c)	(((c)=='p')||((c)=='t')||((c)=='k'))
#define	Is_middle(c)	(((c)=='b')||((c)=='d')||((c)=='g'))
#define	Is_rough(c)	(((c)=='f')||((c)=='q')||((c)=='x'))

#define Is_unasp(c)	(Is_smooth(c) || Is_middle(c))
#define Is_asp(c)	Is_rough(c)
#define Is_stop(c)	(Is_unasp(c)||Is_asp(c))

/* 
 * grc 6/15/89
 */
#define Is_rei_char(c) ((c=='r')||(c=='i')||(c=='e'))

/* Smyth 18-21 */
#define	Is_liquid(c)	(((c)=='l')||((c)=='r'))
#define	Is_nasal(c)	(((c)=='m')||((c)=='n'))
#define	Is_double(c)	(((c)=='z')||((c)=='c')||((c)=='y'))

#define	A_CONTR(verb)	((0==strcmp(lastn(verb,3),"a/w")) || \
			 (0==strcmp(lastn(verb,6),"a/omai") ) )
#define	E_CONTR(verb)	((0==strcmp(lastn(verb,3),"e/w")) || \
			 (0==strcmp(lastn(verb,6),"e/omai") ) )
#define	O_CONTR(verb)	((0==strcmp(lastn(verb,3),"o/w")) || \
			 (0==strcmp(lastn(verb,6),"o/omai") ) )
#define	Is_contr(verb)	/* verb opposes the Sandinista government */  \
			((A_CONTR(verb))||(E_CONTR(verb))||(O_CONTR(verb)))

/*======================================*/
/*	EXTERNAL VARIABLES &		*/
/*	FUNCTION DECLARATIONS		*/
/*======================================*/

extern int errno;

extern	grkfd fds[MAXFILES];
extern	filehead fheaders[MAXFILES];
extern	int openlist[NFILES],nopen;

/*extern lookup_res_type lookup_res;
extern bool debug,verbose,grkchars;*/

extern char tenses[][MAXWORDSIZE];
extern char moods[][MAXWORDSIZE];
extern char voices[][MAXWORDSIZE];
extern char pernums[][MAXWORDSIZE];
extern char casenums[][MAXWORDSIZE];
extern char genders[][MAXWORDSIZE];
extern char degrees[][MAXWORDSIZE];
extern char prefl_types[][MAXWORDSIZE];

char *getsyll(), *getsyll2(), *getaccp();
/*
char getaccent(),getbreath();
*/
bool Is_diphth();
char *skipwhite();
char *parse_nounform(),*parse_verbform(),*parse_adjform(), *next_cons();
ext_type calc_vbext(),calc_adjext(),findhyp();
/*#include "binlook.proto.h"*/

/* addaccent.c */
int addaccent(char *, int, char *);
int cinsert(int, char *);
