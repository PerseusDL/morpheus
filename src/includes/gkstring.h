#include <greek.h>
#include "dialect.h"
#include "stemtype.h"
#include "derivtype.h"
#include "morphflags.h"
#include "prntflags.h"
#define MORPH_VERSION 44440001
#define MAXENDSTRING 15
#define MAXDOMAINS 20
#define COMMENT_CHAR '#'
#define Is_comment(S) *(S) == COMMENT_CHAR
/* commented out for ANSI grc 3/12/91
long fseek();
*/
typedef struct {
	word_form	gs_forminfo;
	Stemtype	gs_steminfo;
	Derivtype   gs_derivtype;
	Dialect		gs_dialect;
	GeogRegion  gs_geogregion;
	MorphFlags	gs_morphflags[MORPHFLAG_BYTES];
	char  		st_domains[MAXDOMAINS+1];
	char 		gs_gkstring[MAXWORDSIZE];
} gk_string;

/*
	modified 4/23/92 by jjake so that gk_analysis includes an st_crasis element.
*/
typedef struct {
	word_form	gs_forminfo;
	Stemtype	gs_steminfo;
	Derivtype   gs_derivtype;
	Dialect		gs_dialect;
	GeogRegion  gs_geogregion;
	MorphFlags	gs_morphflags[MORPHFLAG_BYTES];
	char  		st_domains[MAXDOMAINS+1];
	char 		st_lemma[MAXWORDSIZE]; /* LSJ dict entry to lookup */
/* grc 8/26/94
 * in some cases, you have different stems under the same dictionary entry,
 * e.g., e.g., a(broko/mhs and a(broxai/ths.
 */
	char 		st_dictform[MAXWORDSIZE]; 
/*
 * some words are not in LSJ but are in some english resource (e.g., people,
 * places, things
 */
	char 		st_engform[MAXWORDSIZE]; /* e.g. Athena for *)aqh/nh */
	gk_string	gs_preverb;
	gk_string	gs_aug1;
	gk_string	gs_stem;
	gk_string	gs_suffix;
	gk_string 	gs_endstring;
	char 		st_rawprvb[MAXWORDSIZE];
	char 		st_rawword[MAXWORDSIZE];
	char 		st_workword[MAXWORDSIZE];
	char 		st_crasis[MAXWORDSIZE];
	char 		z[MAXWORDSIZE];
} gk_analysis;

typedef struct {
	word_form	gs_forminfo;
	Stemtype	gs_steminfo;
	Derivtype   gs_derivtype;
	Dialect		gs_dialect;
	GeogRegion  gs_geogregion;
	MorphFlags	gs_morphflags[MORPHFLAG_BYTES];
	char  		st_domains[MAXDOMAINS+1];
	PrntFlags	gs_prntflags;
	int			gw_totanal;
	char 		st_lemma[MAXWORDSIZE];
	gk_string	gs_preverb;
	gk_string	gs_aug1;
	gk_string	gs_stem;
	gk_string	gs_suffix;
	gk_string 	gs_endstring;
	char 		st_rawprvb[MAXWORDSIZE];
	char 		st_rawword[MAXWORDSIZE];
	char 		st_workword[MAXWORDSIZE];
	char 		st_crasis[MAXWORDSIZE];
	char * 		st_oddkeys;
	gk_analysis  *	gw_analysis;
} gk_word;


#define totanal_of(X)		(X)->gw_totanal
#define set_totanal(X,Y)	totanal_of(X) = Y

#define analysis_of( X ) (X)->gw_analysis
#define set_analysis( X , Y ) analysis_of(X) = Y

#define dialect_of( X ) (X)->gs_dialect
#define add_dialect( X , Dial ) dialect_of(X) |= Dial
#define set_dialect( X , Dial ) dialect_of(X) = Dial

#define geogregion_of( X ) (X)->gs_geogregion
#define add_geogregion( X , Dial ) geogregion_of(X) |= Dial
#define set_geogregion( X , Dial ) geogregion_of(X) = Dial


#define forminfo_of(X) 	(X)->gs_forminfo
#define verbinfo_of( X ) forminfo_of(X)
#define adjinfo_of( X ) forminfo_of(X)

#define gkstring_of( X ) (X)->gs_gkstring
#define	set_gkstring( X , s ) Xstrncpy(gkstring_of(X),s,sizeof gkstring_of(X) )

#define stemtype_of( X ) (X)->gs_steminfo
#define set_stemtype( X , stemtype ) stemtype_of(X) = stemtype

#define derivtype_of( X ) (X)->gs_derivtype
#define set_derivtype( X , derivtype ) derivtype_of(X) = derivtype

#define dictform_of( X ) (X)->st_dictform
#define	set_dictform( X , s ) Xstrncpy(dictform_of(X),s,sizeof dictform_of(X) )

#define lemma_of( X ) (X)->st_lemma
#define	set_lemma( X , s ) Xstrncpy(lemma_of(X),s,sizeof lemma_of(X) )

#define prvb_gstr_of(X) (&(X)->gs_preverb)
#define preverb_of( X ) gkstring_of(prvb_gstr_of(X))
#define	set_preverb( X , s ) Xstrncpy(preverb_of(X),s,sizeof preverb_of(X) )

#define aug1_gstr_of(X) (&(X)->gs_aug1)
#define aug1_of( X ) gkstring_of(aug1_gstr_of(X))
#define	set_aug1( X , s ) Xstrncpy(aug1_of(X),s,sizeof aug1_of(X) )

#define stem_gstr_of(X) (&(X)->gs_stem)
#define stem_of( X ) gkstring_of(stem_gstr_of(X))
#define	set_stem( X , s ) Xstrncpy(stem_of(X),s,sizeof stem_of(X) )

#define suffix_gstr_of(X) (&(X)->gs_suffix)
#define suffix_of( X ) gkstring_of(suffix_gstr_of(X))
#define	set_suffix( X , s ) Xstrncpy(suffix_of(X),s,sizeof suffix_of(X) )

#define ends_gstr_of(X) (&(X)->gs_endstring)
#define endstring_of( X ) gkstring_of(ends_gstr_of(X))
#define	set_endstring( X , s ) Xstrncpy(endstring_of(X),s,sizeof endstring_of(X) )

#define rawprvb_of( X ) (X)->st_rawprvb
#define	set_rawprvb( X , s ) Xstrncpy(rawprvb_of(X),s,sizeof rawprvb_of(X) )

#define workword_of( X ) (X)->st_workword
#define	set_workword( X , s ) Xstrncpy(workword_of(X),s,MAXWORDSIZE)

#define rawword_of( X ) (X)->st_rawword
#define	set_rawword( X , s ) Xstrncpy(rawword_of(X),s,sizeof rawword_of(X) )

#define crasis_of( X ) (X)->st_crasis
#define	set_crasis( X , s ) Xstrncpy(crasis_of(X),s,sizeof crasis_of(X) )
#define Has_crasis( X ) ((X)->st_crasis[0])

#define oddkeys_of(X) (X)->st_oddkeys
#define domains_of(X) (X)->st_domains
#define	set_domains( X , s ) Xstrncpy(domains_of(X),s,sizeof domains_of(X) )

#define add_gender(X, Y) 	gender_of(X) |= Y
#define add_case(X, Y) 		case_of(X) |= Y
#define add_voice(X, Y) 	voice_of(X) |= Y

#define Want_Gender(X,Y)	((gender_of(X))&(gender_of(Y)))
#define Want_Case(X,Y)		((case_of(X))&(case_of(Y)))
#define Want_Voice(X,Y)		((voice_of(X))&(voice_of(Y)))

#define Any_dialect(gs) ((dialect_of(gs))==ALL_DIAL)
#define and_dialect(gs,Dial)  (dialect_of(gs) ? ((dialect_of(gs)) &= (Dial)) : (set_dialect(gs,Dial)))
#define Or_dialect(gs,Dial)  ((dialect_of(gs)) |= (Dial))

#define and_geogregion(gs,Dial)  (geogregion_of(gs) ? ((geogregion_of(gs)) &= (Dial)) : (set_geogregion(gs,Dial)))
#define Or_geogregion(gs,Dial)  ((geogregion_of(gs)) |= (Dial))

#define Is_verbform(gs) ((stemtype_of(gs))&(PPARTMASK))
#define Is_adjform(gs) ((stemtype_of(gs))&(ADJSTEM))
#define Is_nounform(gs) ((stemtype_of(gs))&(NOUNSTEM))
#define Is_participle(gs) ((mood_of(forminfo_of(gs)))==PARTICIPLE)
#define Is_superlative(f)	((degree_of(f)) == SUPERLATIVE)
#define Is_comparative(f)	((degree_of(f)) == COMPARATIVE)
		
#define Is_decl3(gs)	((stemtype_of(gs))&DECL3)

#define Is_betacode_upper(X) (*(X) == BETA_UCASE_MARKER )

#define LONGSTRING 1024


/*
 * this char serves as a place holder for "zero length" endings.
 * e.g. the voc sing of pai=s, "pai=", where the ending series is
 * viewed as s, *, dos, di, da etc.
 */
#define ZEROEND 	'*'
#define Is_zeroend(X) (X == ZEROEND)
#define set_zeroend( gs ) sprintf(endstring_of(gs),"%c", ZEROEND )

gk_string * CreatGkString();
gk_word * CreatGkword();
gk_analysis * CreatGkAnal();
FILE * getlemmstart();
FILE * MorphFopen(char *, char *);

#ifdef LIGHTSPEED
#define MorpheusDir "herbert:Utilities Folder:LSC:Morpheus"
#define DIRCHAR ':'
#else
#define MorpheusDir "/usr/src/local/Morpheus"
#define DIRCHAR '/'

#endif
#define MAXANALYSES 25

#define PROSEAUTHOR 0100
#define LENGTH_OF(X) (sizeof X/sizeof X[0])

int Xstrcpy(char *, const char *);
int Xstrncpy(char *, const char *, size_t);
int GetTableLine(char *,int,FILE *);
int ScanAsciiKeys(char *,gk_word *, gk_string *, gk_string * );


void new_degree();
void new_person();
void new_morphflags();
void new_gender();
void new_case();
void new_number();
void new_tense();
void new_voice();
void new_mood();
void new_dialect();
void new_region();
void new_stemtype();
void new_stemclass();
void new_derivtype();
void new_domain();

char * NameOfTense(word_form vf);
char * NameOfMood(word_form vf);
char * NameOfVoice(word_form vf);
char * NameOfPerson(word_form vf);
char * NameOfNumber(word_form vf);
char * NameOfGender(word_form af);
char * NameOfCase(word_form af);
char * NameOfDegree(word_form af);
char * NameOfDialect(Dialect di);
char * NameOfStemtype(Stemtype st);
char * NameOfDerivtype(Derivtype st);
