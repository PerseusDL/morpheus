/*
 * copyright Gregory Crane
 *
 * February 1987
 */

#include "morphkeys.h"
#include <stdlib.h>
#include <string.h>
#include "../greeklib/xstrings.proto.h"
#include "gkstring.proto.h"
#ifdef LIGHTSPEED

/*
 char * p_eq_morph_keys();
*/
#else

/*
static char * NextEndTable();
static char * p_eq_morph_keys();
*/

#endif
Stemtype GetStemClass(char * );
Stemtype GetIsProse(char *);

#ifndef LIGHTSPEED
static GetGkFlag();
static GetMorphKeys();
#endif

static RearrangeMorphflags(gk_word *, gk_string *);
static GetGkFlag(char *, gk_string *, char *, char *, char *);
static char *p_eq_morph_keys(long, Morph_args *);
static int keys_inited = 0;
static int nstems = 0;
static int nderivs = 0;
static int ndomains = 0;
static int nkeys = 0;
/*int keycomp1(Morph_args **, Morph_args **);*/
int keycomp1(const void *, const void *);
static Morph_args ** key_table = NULL;

 ScanAsciiKeys(char *s, gk_word *Gkword, gk_string *want, gk_string *avoid)
{
	char savekeys[LONGSTRING];
	char curkey[LONGSTRING];
	gk_string * gstr = want;
	char * preverb;
	char * lemma;
	
	if( ! Gkword ) {
		fprintf(stderr,"Hey! null Gkword in scanasciikeys!\n");
		exit(-1);
/*
		preverb = NULL;
		lemma = NULL;
*/
	} else {
		preverb = preverb_of(Gkword);
		lemma = lemma_of(Gkword);
	}
	if( Gkword && oddkeys_of(Gkword) )
		*(oddkeys_of(Gkword)) = 0;
	Xstrncpy((char *)savekeys,(const char *)s,(size_t)LONGSTRING);

	while(nextkey(savekeys,curkey)) {
		if( ! strcmp( "not" , curkey )  ) {
			if( avoid ) {
				gstr = avoid;
			} else /* if no place to store the stuff to be avoided, just quit */
				break;
/* 
			  else {
			 	fprintf(stderr,"hey: got a negation in [%s], but no place to put it!\n", savekeys);
				return;
			}
*/
			continue;
		}

		if( ! strcmp( "crasis" , curkey ) ) {
			nextkey(savekeys,curkey);
			set_crasis(Gkword,curkey);
/*			
printf("crasis now set to [%s]\n", crasis_of(Gkword) );
*/
			continue;
		}

	
	if( ! strcmp(curkey,"pb") ) {
		nextkey(savekeys,curkey);
		if( preverb ) {
		    Xstrncpy(preverb,curkey,MAXWORDSIZE);
		    zap_morphflag(morphflags_of(gstr),ROOT_PREVERB);
		    add_morphflag(morphflags_of(gstr),HAS_PREVERB);
		}
		continue;
	}

	if( ! strcmp(curkey,"rpb") ) {
		nextkey(savekeys,curkey);
		if( preverb ) {
		    Xstrncpy(preverb,curkey,MAXWORDSIZE);
		    zap_morphflag(morphflags_of(gstr),HAS_PREVERB);
		    add_morphflag(morphflags_of(gstr),ROOT_PREVERB);
		}
		continue;
	}

		if( ! GetGkFlag(curkey,gstr,endstring_of(Gkword),preverb,lemma) ) {
		/*
			fprintf(stderr,"could not match key [%s] in [%s]\n", curkey , s);
		*/
			if( Gkword ) {
				if( ! oddkeys_of(Gkword) ) {
					oddkeys_of(Gkword) = (char *)malloc(LONGSTRING+1);
					*(oddkeys_of(Gkword)) = 0;
				}
				if(*oddkeys_of(Gkword))
					Xstrncat(oddkeys_of(Gkword)," ",LONGSTRING);
				Xstrncat(oddkeys_of(Gkword),curkey,LONGSTRING);
			}
		}
	}

	if( preverb_of(Gkword)[0] ) {

		if(  has_morphflag(morphflags_of(gstr),ROOT_PREVERB)) {
			add_morphflag(morphflags_of(Gkword),ROOT_PREVERB);
			add_morphflag(morphflags_of(stem_gstr_of(Gkword)),ROOT_PREVERB);
			zap_morphflag(morphflags_of(Gkword),HAS_PREVERB);
			zap_morphflag(morphflags_of(gstr),HAS_PREVERB);
			zap_morphflag(morphflags_of(stem_gstr_of(Gkword)),HAS_PREVERB);
		} else {
			zap_morphflag(morphflags_of(Gkword),ROOT_PREVERB);
			zap_morphflag(morphflags_of(stem_gstr_of(Gkword)),ROOT_PREVERB);
			add_morphflag(morphflags_of(Gkword),HAS_PREVERB);
			add_morphflag(morphflags_of(stem_gstr_of(Gkword)),HAS_PREVERB);
		}
	}

	if( Gkword )
		RearrangeMorphflags(Gkword,want);
	if( stemtype_of(want) == 0 ) 
		return(0);
	else
		return(1);
}

static 
RearrangeMorphflags(gk_word *Gkword, gk_string *gstr)
{
	xfer_prvbflags(morphflags_of(Gkword),morphflags_of(prvb_gstr_of(Gkword)));
	xfer_prvbflags(morphflags_of(gstr),morphflags_of(prvb_gstr_of(Gkword)));
}

static
 GetGkFlag(char *field, gk_string *gstr, char *endstring, char *preverb, char *lemma)
{
	
 	if( ! keys_inited )
 		init_keys();	

	if( AddMorphKey(gstr,field) ) 
		return(1);

/*
 * note that if you try to stick both an ending and a preverb into
 * the same gk_string, the second one in will overwrite the first.
 * 
 * we assume that you will have endstrings with endings and preverbs with
 * stems. if not ....
 */
	if( ! Xstrncmp(field,"end:",4) ) {
		Xstrncpy(endstring,field+4,MAXWORDSIZE);
/*
		set_gkstring(gstr,field+4);
*/
		return(1);
	}

	if( ! Xstrncmp(field,"pb:",Xstrlen("pb:")) ) {
		if( preverb ) {
		    Xstrncpy(preverb,field+3,MAXWORDSIZE);
		    zap_morphflag(morphflags_of(gstr),ROOT_PREVERB);
		    add_morphflag(morphflags_of(gstr),HAS_PREVERB);
		} /* else {
		    fprintf(stderr,"got handed prevb %s but had no place to put it!\n", field+3);
		}*/
		return(1);
	}

	if( ! Xstrncmp(field,"rpb:",Xstrlen("rpb:")) ) {
		if( preverb ) {
		    Xstrncpy(preverb,field+4,MAXWORDSIZE);
		    zap_morphflag(morphflags_of(gstr),HAS_PREVERB);
		    add_morphflag(morphflags_of(gstr),ROOT_PREVERB);

		} /* else {
		    fprintf(stderr,"got handed prevb %s but had no place to put it!\n", field+3);
		}*/
		return(1);
	}

	if( ! Xstrncmp(field,"le:",Xstrlen("le:")) ) {
		if( ! lemma ) {
		    fprintf(stderr,"got handed lemma %s but had no place to put it!\n", field+3);
		} else {
			Xstrncpy(lemma,field+3,MAXWORDSIZE);
		}
		return(1);
	}
	return(0);
}

char * 
 NextEndTable(int *index, Stemtype mask)
{
	Morph_args * morph_args;
	Dialect oldmask = mask;
	
	mask &= (PPARTMASK|ADJSTEM|NOUNSTEM);
 
 	if( ! keys_inited )
 		init_keys();
	morph_args = arg_stemtype + *index;
 		
 	while( morph_args->morph_key[0] ) {
		if( ! mask ) {
			(*index)++;
if( mask )
printf("0 mask returns [%s]\n", morph_args->morph_key );
			return(morph_args->morph_key);
		} else if( ( (long)mask & morph_args->morph_flags ) ) {
/*
printf("mask of [%o] on [%lo] returns [%s]\n", mask , morph_args->morph_flags , morph_args->morph_key );
*/
			(*index)++;
			return(morph_args->morph_key);
		}
/*
printf("stype [%o] fails on [%s]\n", mask , morph_args->morph_key );
*/
		(*index)++;
		morph_args++;
	}
	return(NULL);

}

char *
 NameOfDerivtype(Derivtype st)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)st,arg_derivtype) );
}


char *
 NameOfStemtype(Stemtype st)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)st,arg_stemtype) );
}

/*
char * 
  part_of_speech(st)
    Stemtype st;
{
	 	if( ! keys_inited )
 		init_keys();
 		
 		if( 

}
*/

char *
 NameOfDomain(Stemtype st)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)st,arg_domain) );
}

char *
 NameOfPerson(word_form vf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)person_of(vf),arg_person) );
}

char *
 NameOfNumber(word_form vf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)number_of(vf),arg_number) );
}

char *
 NameOfTense(word_form vf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)tense_of(vf),arg_tense) );
}

char *
 NameOfMood(word_form vf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)mood_of(vf),arg_mood) );
}

char *
 NameOfVoice(word_form vf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)voice_of(vf),arg_voice) );
}


char *
 NameOfDialect(Dialect di)
{
	 if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)di,arg_dialect) );
}


DomainNames(char *domp, char *res, char *dels)
{
	char * p = domp;
	
	while(*p) {
		if( *res )
			Xstrncat(res,dels,MAXWORDSIZE);
		Xstrncat(res,NameOfDomain((Stemtype)*p),MAXWORDSIZE);
		p++;
	}
}
  
 DialectNames(Dialect di, char *res, char *dels)
{
	char * s;
	int i;
	Dialect mask = 1;
	Dialect sofar = 0;
	Morph_flags mf;
	Morph_args * morph_args;
	
	morph_args = arg_dialect;
	
	*res = 0;
	if( ! di )
		return;
	mf = (Morph_flags)di;

	while( morph_args->morph_key[0] ) {
		if( morph_args->morph_flags && 
		   ( (mf & morph_args->morph_flags) == morph_args->morph_flags ) ) {

			if(*res) Xstrncat(res,dels,LONGSTRING);
			Xstrncat(res,morph_args->morph_key,LONGSTRING);
			mf &= ~(morph_args->morph_flags);
		}
		morph_args++;
	}
	return;
}

 GeogRegionNames(GeogRegion gr, char *res, char *dels)
{
	char * s;
	int i;
	GeogRegion mask = 1;
	GeogRegion sofar = 0;
	Morph_flags mf;
	Morph_args * morph_args;
	
	morph_args = arg_geogregion;
	
	*res = 0;
	if( ! gr )
		return;
	mf = (Morph_flags)gr;

	while( morph_args->morph_key[0] ) {
		if( morph_args->morph_flags && ( (mf & morph_args->morph_flags) == morph_args->morph_flags ) ) {
			if(*res) Xstrncat(res,dels,LONGSTRING);
			Xstrncat(res,morph_args->morph_key,LONGSTRING);
			mf &= ~(morph_args->morph_flags);
		}
		morph_args++;
	}
	return;
}

char *
 NameOfGender(word_form af)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)gender_of(af),arg_gender) );
}

char *
 NameOfCase(word_form af)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)case_of(af),arg_case) );
}

char *
 NameOfDegree(word_form wf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys((long)degree_of(wf),arg_degree) );
}

 
char * 
 NameOfMorphFlags(long mf)
{
 	if( ! keys_inited )
 		init_keys();
 		
	return( p_eq_morph_keys(mf,arg_morphflags) );
	
}


Morph_args * 
MatchMorphKey(char *field)
{		
	int rval;
	
	if( ! keys_inited )
		init_keys();

	rval=binlook( (char *)key_table , field , nkeys , (int)sizeof * key_table , 1 ,  keycomp2);
	if( rval < 0 ) {

		return(NULL);
	}
	return(*(key_table+rval));
}

Stemtype
GetStemNum(char *field)
{
	Morph_args * mp, *MatchMorphKey();
	
	mp = MatchMorphKey(field);
	if( ! mp )
		return((Stemtype)0);
	return((Stemtype)(mp->morph_flags));
}

static char *
 p_eq_morph_keys(long flag, Morph_args *morph_args)
{
	if( ! flag )
		return("");
	while( morph_args->morph_key[0] ) {
		if( ( flag == morph_args->morph_flags ) ) {
			return(morph_args->morph_key);
		}
		morph_args++;
	}
	return("");
}
Morph_args * InitStemSuffs(char * fname,void 	(*curfunc)(),Stemtype 	(*classfunc)(),int * snum);


Morph_args * 
InitStemSuffs(char *fname, void (*curfunc )(), Stemtype (*classfunc )(), int *snum)
{
	FILE * f;
	int i, j;
	char line[LONGSTRING];
	Stemtype stemnum = 0;
	Stemtype declnum = 0;
	char stemname[MAXWORDSIZE];
	char decl[MAXWORDSIZE];
	Morph_args * targs = NULL;

	
	if( (f=MorphFopen(fname,"r")) == NULL ) {
		fprintf(stderr,"could not open [%s]\n", fname );
		return(NULL);
	}
	
	while(GetTableLine(line,(int)sizeof line,f)) (*snum)++;
	fseek(f,0L,0);
	
	targs = (Morph_args *) calloc((size_t)((*snum)+1),(size_t)sizeof * targs);

	for(i=0;GetTableLine(line,(int)sizeof line, f);i++) {
		int n = 0;
		declnum = stemnum = 0;

		if( has_octal(line)) {
			sscanf(line,"%s %o %s", stemname , &n , decl );
			stemnum = (Stemtype) n;
		} else {
			sscanf(line,"%s %d %s", stemname , &n , decl );
			stemnum = (Stemtype) n;
		}
		Xstrncpy(targs[i].morph_key , stemname,(size_t)MAXWORDSIZE);
		declnum = (*classfunc)(decl);
		

/*		if( declnum == 0 ) { 
			fprintf(stdout,"could not recognize [%s]\n", decl );
			targs[i].morph_flags = (stemnum );
		} else */
			targs[i].morph_flags = (stemnum | declnum);
		targs[i].add_val = curfunc;

/*
		printf("name [%s] num [%o] declnum [%o] decl [%s]\n", stemname , stemnum, declnum, decl);
		printf("morphflags %lo\n", targs[i].morph_flags );
*/
	}
	fclose(f);
	return(targs);
}


init_stems(void)
{
	
	arg_stemtype = InitStemSuffs(STEMTYPES,new_stemtype,GetStemClass,&nstems);
	arg_derivtype = InitStemSuffs(DERIVTYPES,new_derivtype,GetStemClass,&nderivs);
	arg_domain = InitStemSuffs(DOMAINLIST,new_domain,GetIsProse,&ndomains);

}
	
	
has_octal(char *s)
{
	while(*s&& !isspace(*s)) s++;
	while(isspace(*s)) s++;
	if(*s == '0' ) return(1);
	return(0);
}

init_keys(void)
{
	int sofar = 0;
	int i;
	int morph_key_comp();
	
	keys_inited++;
	init_stems();
	nkeys = nstems  + nderivs + ndomains
		 + LENGTH_OF(arg_degree)
		 + LENGTH_OF(arg_person)
		 + LENGTH_OF(arg_morphflags)
		 + LENGTH_OF(arg_gender)
		 + LENGTH_OF(arg_case)
		 + LENGTH_OF(arg_number)
		 + LENGTH_OF(arg_tense)
		 + LENGTH_OF(arg_voice)
		 + LENGTH_OF(arg_mood)
		 + LENGTH_OF(arg_dialect)
		 + LENGTH_OF(arg_geogregion);
	key_table = (Morph_args **) calloc((size_t)nkeys+1,(size_t)sizeof * key_table );
	
	sofar += add_keyarr(key_table+sofar,arg_stemtype);
	sofar += add_keyarr(key_table+sofar,arg_derivtype);
	sofar += add_keyarr(key_table+sofar,arg_domain);
	sofar += add_keyarr(key_table+sofar,arg_degree);
	sofar += add_keyarr(key_table+sofar,arg_person);
	sofar += add_keyarr(key_table+sofar,arg_gender);
	sofar += add_keyarr(key_table+sofar,arg_case);
	sofar += add_keyarr(key_table+sofar,arg_number);
	sofar += add_keyarr(key_table+sofar,arg_tense);
	sofar += add_keyarr(key_table+sofar,arg_voice);
	sofar += add_keyarr(key_table+sofar,arg_mood);
	sofar += add_keyarr(key_table+sofar,arg_dialect);
	sofar += add_keyarr(key_table+sofar,arg_geogregion);
	sofar += add_keyarr(key_table+sofar,arg_morphflags);

	qsort((void*)key_table,(size_t)sofar,(size_t)sizeof * key_table,keycomp1);

	nkeys = sofar;
/*
if(1) {
Morph_args * mf;
mf = *(key_table+sofar-1);
printf("sofar %d last key [%s] second to last [%s]\n",sofar, mf->morph_key, (--mf)->morph_key);
}
*/

/*
	for(i=0;i<sofar && i < 100;i++) {
		Morph_args * mf;
		
		mf = *(key_table+i);
		printf("%d) [%s]\n", i , mf->morph_key );
	}
*/
/*
 i = binlook( key_table , "wr_oros" , nkeys , sizeof * key_table , 1 , 
 keycomp2);
 printf("i %d\n", i );

getchar();
*/

}

int
keycomp1(const void *k1, const void *k2)
{
	Morph_args ** m1, **m2;

	m1 = (Morph_args **) k1;
	m2 = (Morph_args **) k2;
	return(strcmp( (*m1)->morph_key, (*m2)->morph_key ));
}

int
keycomp2(char *s, Morph_args **kp)
{
	Morph_args * m;
	int rval = 0;
	m = *kp;

	rval = strcmp(s,m->morph_key);

	return(rval);
}

 add_keyarr(Morph_args **ktab, Morph_args *morph_args)
{
	register Morph_args * ms = morph_args;
	
	while( morph_args->morph_key[0] ) {
		*ktab++ = morph_args++;
	}
	return( morph_args - ms );
}

Stemtype		
GetStemClass(char *classp)
{
	int i;
	
	for(i=0;i<(int)(sizeof arg_stemclass/sizeof arg_stemclass[0]);i++) {
		if( ! strcmp(classp,arg_stemclass[i].class_name ) ) {
			return( (Stemtype)arg_stemclass[i].class_num);
		}
	}
	return((Stemtype)-1);
}

Stemtype		
GetIsProse(char *classp)
{

	if(! (strcmp(classp,"prose")))
		return((Stemtype)PROSEAUTHOR);
	return((Stemtype)0);
}

 AddMorphKey(gk_string *gstr, char *field)
{
	void (*func)(gk_string *, Morph_flags);
	Morph_args * mp, *MatchMorphKey(char*);
	
	mp = MatchMorphKey(field);
	if( ! mp )
		return(0);
	func = mp->add_val;

	(*func)(gstr,mp->morph_flags);
	return(1);
}
