#include <gkstring.h>

#include "derivio.proto.h"
static checkforderiv2(char *stemstr, char *stemkeys, char *had_redupl, char *redupstem);
static checkforderiv2(char * stemstr,char * stemkeys,char * had_redupl,char * redupstem);
int checkcomderivs(char * derivs,char * defstem,char * suffix,char * lemmkeys,char * nkeys,char * had_redupl,char * redupstem);
int checkcomderiv(char * derivs,char * defstem,char * suffix,char * lemmkeys,char * nkeys,char * had_redupl,char * redupstem);
int checkcomderiv2(char * asuffkeys,char * dstem,char * dstemkeys,char * suffix,char * lemma,char * lkeys,char * rkeys,char * had_redupl,int markedstem);

static gk_string BlnkGstr;
int checkedsuffs = 0;
int checkedderivs = 0;
int realderivs = 0;
checkforderiv(char *stemstr, char *stemkeys)
{
	int rval = 0;
	int rval2 = 0;
	char * p, * is_substring();
	char stemkeys2[LONGSTRING];
	int oldsuffs = checkedsuffs;

	stemkeys2[0] = 0;
	checkedderivs++;

/*
	if( stemstr_in_cache(stemstr,stemkeys) ) {
		if( *stemkeys ) return(1);
		else return(0);
	}
*/
	
	rval=checkforderiv2(stemstr,stemkeys,"","");

/*	if( rval ) return(rval);*/
	
	
	rval2 = checkforredupderiv(stemstr,stemkeys2);
	if( rval2 ) {
		if( *stemkeys ) strcat(stemkeys," ");
		strcat(stemkeys,stemkeys2);
	}
/*
printf("%d) %d %d [%s] checkedsuff %d, added %d\n", checkedderivs , realderivs++,
rval+rval2 ,stemstr , checkedsuffs, checkedsuffs - oldsuffs );
*/
	add_deriv_cache(stemstr,stemkeys);
	return(rval+rval2);

}

checkforredupderiv(char *stemstr, char *stemkeys)
{
	char noredup[MAXWORDSIZE];
		
	if( Is_cons(*stemstr) && cur_lang() != LATIN  && cur_lang() != ITALIAN ) {
		if( ! un_redupl(stemstr,noredup,'e')) return(0);
/*
		return(checkforderiv2(noredup,stemkeys,stemstr,""));
*/
		return(checkforderiv2(noredup,stemkeys,"redupl",""));
	}
	return(checkaugredup(stemstr,stemkeys));
}

#define MAXREDUPLS 	04
static init_stor = 0;
static 	gk_string * tstemtab[MAXREDUPLS];
/*
 * store stems that would have a quantity marked
 * e.g., a)_kolouqh/seis -- doric future perfect
 *
 * grc 3/21/91
 */
static 	gk_string * tqstemtab[MAXREDUPLS];

checkaugredup(char *stemstr, char *stemkeys)
{
	int hits = 0;
	int i;
	int poss_redupls = 0;
	int possno = 0;
	char had_redupl[MAXWORDSIZE];
	char tmpkeys[LONGSTRING];



	if( ! init_stor ) {
		init_stor = 1;
		for(i=0;i<MAXREDUPLS;i++) {
			tstemtab[i] = CreatGkString(1);
			tqstemtab[i] = CreatGkString(1);
		}
	}
	for(i=0;i<MAXREDUPLS;i++) {
		ClearGkstring(tstemtab[i]);
		ClearGkstring(tqstemtab[i]);
	}

	/*
	 * grc 8/4/89
	 *
	 * don't accept this possibility unless you have a word beginning with two
	 * consonants or a double consonant
	 */
	 
	if( !Xstrncmp(stemstr,"e)",2) && ! Is_cons(*(stemstr+3)) ) {
		if( *(stemstr+2) != 'z' && *(stemstr+2) != 'c' && *(stemstr+2) != 'y' )
			return(0);
	}
	poss_redupls = unaugment(stemstr,tstemtab,tqstemtab,MAXREDUPLS,(Dialect)ALL_DIAL,1,1);

	for(i=0;i<poss_redupls;i++) {
		char tempstem[BUFSIZ];
		tmpkeys[0] = 0;
/*
printf("checking [%s] [%s] [%s]\n", stemstr , gkstring_of(tstemtab[i]) , tmpkeys );
*/
		tempstem[0] = 0;
		SprintGkFlags(tstemtab[i],tmpkeys,"	",1);
		Xstrncpy(tempstem,gkstring_of(tstemtab[i]),(int)sizeof tempstem );

		if( has_morphflag(morphflags_of(tstemtab[i]),SYLL_AUGMENT)  ) 
			strcpy(had_redupl,"syll_aug");
		else
			strcpy(had_redupl,"temp_aug");
/*
 * grc 3/21/91
 *
 * if you have a doric stem, for example, then pass this info
 * along
 */

		if( tmpkeys[0] ) {
			strcat(had_redupl," ");
			strcat(had_redupl,tmpkeys);
		}

		if( checkforderiv2(tempstem,tmpkeys,had_redupl,
				gkstring_of(tqstemtab[i])[0] ? gkstring_of(tqstemtab[i]) :"") ) {
			if(*stemkeys) Xstrncat(stemkeys," ",LONGSTRING);
			Xstrncat(stemkeys,tmpkeys,LONGSTRING);
			hits++;
		}

		
	}

	return(hits);
}

static
checkforderiv2(char *stemstr, char *stemkeys, char *had_redupl, char *redupstem)
{
	char * ep;
	char derivstr[LONGSTRING];
	int rval = 0;
	int sofar = 0;
	int slen;
	char derivkeys2[LONGSTRING*2];
	char resbuf[LONGSTRING*2];
	
	ep = lastn(stemstr,1);
	slen = Xstrlen(stemstr)-1;
	derivkeys2[0] = resbuf[0] = 0;
	Xstrncpy(derivstr,stemstr,LONGSTRING);

	rval = chckdvend("*",stemkeys);

	if(  chckderiv(derivstr,derivkeys2) ) {
		int n;
		n=checkcomderivs(stemkeys, derivstr,"",derivkeys2,resbuf,had_redupl,redupstem);
		if( n ) sofar++;
	}
	
	while(ep>stemstr) {
/*
		printf("for [%s] of [%s]\n", ep, stemstr );
*/
		rval = chckdvend(ep,stemkeys);
		if( rval ) {
			derivstr[slen] = 0 ;
/*
printf("[%s] ok trying [%s]\n", ep, derivstr );
*/
			if(  chckderiv(derivstr,derivkeys2) ) {
				int n;
				n=checkcomderivs(stemkeys, derivstr,ep,derivkeys2,resbuf,had_redupl,redupstem);
				if( n ) sofar++;
			}
		}
		ep--;
		slen--;
	}
	if( sofar ) {
		Xstrncpy(stemkeys,resbuf,LONGSTRING);
/*
printf("sofar [%d] stemkeys [%s] stemstr [%s]\n", sofar , stemkeys, stemstr );
*/
	}
	return(sofar);
}

checkcomderivs(char *derivs, char *defstem, char *suffix, char *lemmkeys, char *nkeys, char *had_redupl, char *redupstem)
{
	int rval = 0;
/*
	char lkeybuf[LONGSTRING], curlemmkeys[LONGSTRING];
*/
	char *lkeybuf, *curlemmkeys;

	lkeybuf = (char *)malloc((size_t)LONGSTRING);
	curlemmkeys = (char *)malloc((size_t)LONGSTRING);
	
	Xstrncpy(curlemmkeys,lemmkeys,LONGSTRING);

	while(nextkey(curlemmkeys,lkeybuf)) {
		
		rval += checkcomderiv(derivs,defstem,suffix,lkeybuf,nkeys,had_redupl,redupstem);

	}
	
	free(lkeybuf);
	free(curlemmkeys);
	return(rval);
	
}

#define Is_perfect(STYPE) (((STYPE&PPARTMASK)== PP_PP)||\
							((STYPE&PPARTMASK)== PP_PF)||((STYPE&PPARTMASK)== PP_FP))

checkcomderiv(char *derivstr, char *defstem, char *suffix, char *lkeys, char *rkeys, char *had_redupl, char *redupstem)
{
	char *asuffkeys;
	char *dstemkeys;
	char *lemma;
	char *tmpdstem;
	char * tmpsuff = suffix;
	int markedstem = 0;
	char * s;
	int rval = 0;

	asuffkeys = (char *)malloc((size_t)LONGSTRING*2);
	dstemkeys = (char *)malloc((size_t)LONGSTRING*2);
	lemma = (char *)malloc((size_t)LONGSTRING+1);
	tmpdstem = (char *)malloc((size_t)LONGSTRING+1);
	
	Xstrncpy(asuffkeys,derivstr,LONGSTRING*2);
	Xstrncpy(tmpdstem,lkeys,LONGSTRING);
	s=tmpdstem; /* separate off the stem if one is marked */

	while(*s&&*s!=':') s++;
	if(*s==':') {
		*s++ = 0;
	}
	/*
	 * save the rest of the keys in the lemma slot
	 */
	Xstrncpy(lemma,s,LONGSTRING);

	/*
	 * tmpdstem now includes any specially marked stems, e.g. "ti_m" as in tima/w,
	 * while defstem contains "tim", the stem without the long mark.
	 */
	if( tmpdstem[0] ) {
		markedstem++;
	} else {
		Xstrncpy(tmpdstem,defstem,MAXWORDSIZE);
	}
	


	s = lemma;
	while(*s&&*s!=':') s++; /* now get the lemma */
	if(*s== ':') {
		*s++ = 0;
	}
	
	Xstrncpy(dstemkeys,s,LONGSTRING*2); /* now get the rest of the keys */
	s=dstemkeys;
	while(*s) {
		if(*s == ':' )
			*s = ' ';
		s++;
	}
	if( *had_redupl && Is_vowel(tmpdstem[0]) && ! *redupstem) {
		rval += checkmultredups(asuffkeys,tmpdstem,dstemkeys,tmpsuff,lemma,lkeys,rkeys,had_redupl,markedstem);
	} else {
			if( *had_redupl ) {
				if( *redupstem ) {
			/*
			 * grc 3/21/91
			 *
			 * this case covers an instance such as a)kolouqh/s-eis, where 
			 * this *could* be a doric reduplicated form, but we want to make sure
			 * that we have labelled the long alpha:  a)_kolouqhs-
			 */
						markedstem++;
						strcpy(tmpdstem,redupstem);
						tmpsuff = "";
					} else
						simpleredupit(tmpdstem,NO,'e');	
				
		}	
		rval += checkcomderiv2(asuffkeys,tmpdstem,dstemkeys,tmpsuff,lemma,lkeys,rkeys,had_redupl,markedstem);
	}
	free(asuffkeys);
	free(dstemkeys);
	free(lemma);
	free(tmpdstem);
	return(rval);
}

checkmultredups(char *asuffkeys, char *dstem, char *dstemkeys, char *suffix, char *lemma, char *lkeys, char *rkeys, char *had_redupl, int markedstem)
{
	int rval = 0;
	int gotredups = 0;
	int i;
	gk_word * gkform;
	gk_string * gstr;
	char curstemkeys[LONGSTRING];

	gkform = CreatGkword(6);
	gstr = CreatGkString(1);
	if( ! gkform ) {
		fprintf(stderr,"no memory for gkform in checkmultredups of [%s]\n",asuffkeys);
		return;
	}
		
	set_workword(gkform,dstem);
	set_dialect(gstr,(Dialect)0);
	ScanAsciiKeys(dstemkeys,gkform,gstr,(gk_string *)NULL);
	set_dialect(gkform,dialect_of(gstr));
	
	gotredups = redupit2(gkform,NO,'e',5);
	for(i=0;i<gotredups;i++) {
		char * p;
		
		curstemkeys[0] = 0;
		set_dialect(gstr,dialect_of(gkform+i) );
		SprintGkFlags(gstr,curstemkeys," ",1);
		p = workword_of(gkform+i);
		rval += checkcomderiv2(asuffkeys,p,curstemkeys,suffix,lemma,lkeys,rkeys,had_redupl,markedstem);
	}

	FreeGkword(gkform);
	FreeGkString(gstr);

	
	return(rval);
}

checkcomderiv2(char *asuffkeys, char *dstem, char *dstemkeys, char *suffix, char *lemma, char *lkeys, char *rkeys, char *had_redupl, int markedstem)
{	
	char * derivsuff;
	char * tmpdsuff;
	char * stembuf;
	char * dbuf;
	register char * s;
	gk_string * gstr;
	int rval = 0;
	
	derivsuff = (char *)malloc((size_t)LONGSTRING);
	tmpdsuff = (char *)malloc((size_t)LONGSTRING);
	dbuf = (char *)malloc((size_t)LONGSTRING);
	stembuf = (char *)malloc((size_t)MAXWORDSIZE);
	gstr = CreatGkString(1);

	Xstrncpy(dbuf,asuffkeys,LONGSTRING);
	
	while(nextkey(dbuf,derivsuff)) {
		stembuf[0] = 0;
		s=derivsuff;
		if( *s && *s != ':' ) {
			char * p;
			
			Xstrncpy(tmpdsuff,s,LONGSTRING);
			s++;
			while(*s&&*s!=':') s++;
			if(*s) s++;
			strcpy(derivsuff,s);
			p = derivsuff;
			while(*p) {
				if( *p == ':' ) *p = ' ';
				p++;
			}
			
			p = tmpdsuff;
			while(*p&&*p!=':') p++;
			if(*p) *p = 0;
			markedstem++;
			
		} else {
			Xstrncpy(tmpdsuff,suffix,LONGSTRING);
		
		}
		
		if( markedstem ) sprintf(stembuf,"%s%s",dstem,tmpdsuff );
		else stembuf[0] = 0;
		
		while(*s) {
			if(*s == ':' )
				*s = ' ';
			s++;
		}

		if( DstemTakesDsuff(derivsuff,dstemkeys,gstr,dstem,tmpdsuff))  {
			char tmp1[LONGSTRING*2], tmp2[LONGSTRING*2];
			
			/*
			 * grc 5/30/89
			 *
			 * don't accept things like "fi/lhka".  if the stemtype is a perfect,
			 * then the stem must have had a reduplication
			 */

			tmp1[0] = 0;
			if( cur_lang() != LATIN && cur_lang() != ITALIAN ) {
				if( ! (*had_redupl) &&  (Is_perfect(stemtype_of(gstr) )) ) {
					continue;
				}
			}

			if( *had_redupl && ! (Is_perfect(stemtype_of(gstr))) )
				continue;


/*
 * grc 8/4/89
 *
 * if the stem doesn't take a syllabic augment, then don't accept a syllabically
 * augmented perfect
 */
			if( ! Xstrncmp(had_redupl,"syll_aug",Xstrlen("syll_aug")) && 
				! has_morphflag(morphflags_of(gstr),SYLL_AUGMENT) ) {
					continue;
			}
			if( *rkeys ) 
				Xstrncat(rkeys," ",LONGSTRING);
			
			if( *had_redupl ) {
				gk_word * gkword;
				add_morphflag(morphflags_of(gstr),REDUPL);
				gkword = CreatGkword(1);
				/*
				 * grc 3/21/91
				 *
				 * the first argument in had_redup will be whether we have a redup,
				 * or, if the stem starts with a vowel, if we have a temporal or a
				 * syllabic augment for redup.
				 *
				 * the second may be a dialect (e.g., a)_kolouqhs- is a doric
				 * future perfect stem
				 */
				ScanAsciiKeys(had_redupl,gkword,gstr,(gk_string *)NULL);
				FreeGkword(gkword);
			}
			
			SprintGkFlags(gstr,tmp1,":",1);
/*
printf("curstemkyes [%s] %o\n", tmp1 , has_morphflag(morphflags_of(gstr),R_E_I_ALPHA));
*/
/*
			
			sprintf(tmp2,"%s:%s%s", ((*had_redupl) ? dstem : stembuf), lemma , tmp1);
*/
			sprintf(tmp2,"%s:%s%s",  stembuf, lemma , tmp1);
/*
printf("success on [%s] and [%s]\n", derivsuff, dstemkeys );
printf("about to add [%s]\n", tmp2 );
*/
			Xstrncat( rkeys,tmp2,LONGSTRING);
			rval++;
		}	

		
	}
	free(derivsuff);
	free(tmpdsuff);
	free(stembuf);
	free(dbuf);
	FreeGkString(gstr);
	return(rval);
}

DstemTakesDsuff(char *dsuffkeys, char *dstemkeys, gk_string *gstr, char *defstem, char *derivstr)
{
	int rval = 0;

checkedsuffs++;	
	add_morphflag(morphflags_of(gstr),IS_DERIV);
/*
 * grc 7/31/89
 *
 * avoid forms such as i)sxuri+zomai
 */
 	if( has_diaeresis(derivstr) && ! ends_in_vowel(defstem) ) 
 		return(0);

	rval = CompatKeys(dsuffkeys,dstemkeys,gstr);
	zap_morphflag(morphflags_of(gstr),IS_DERIV);
/*
printf("rval %d dsuff [%s %s] dstem [%s %s]\n", rval, defstem, dsuffkeys , derivstr, dstemkeys );
*/
	if( ! rval ) return(0);
	if( !Xstrncmp(derivstr,"a_",2) && ! Is_rei_char(*(lastn(defstem,1))) &&
		need_rei_alpha(dsuffkeys) ) 
		rval = 0;
/*
if( ! rval ) printf("defstem [%s %s] derivstr [%s %s]\n", defstem , dstemkeys, 
derivstr , dsuffkeys );
*/
	return(rval);
}

need_rei_alpha(char *dsuffkeys)
{
	gk_string * gstr;
	gk_word * Gkword;
	int rval = 0;
	
	gstr = CreatGkString(1);
	Gkword = CreatGkword(1);
	
	ScanAsciiKeys(dsuffkeys,Gkword,gstr,(gk_string *)NULL);

	if( has_morphflag(morphflags_of(gstr),R_E_I_ALPHA) ) {
		rval = 1;
	}

	FreeGkString(gstr);
	FreeGkword(Gkword);
	return(rval);
}

#define BADTRIES 12
char * cache_stems[BADTRIES];
char * cache_keys[BADTRIES];
static int badinit = 0;
static int badindex = 0;
stemstr_in_cache(char *s, char *stemkeys)
{
	int i;
	
	for(i=0;i<BADTRIES;i++) {
		if( ! strcmp(s,cache_stems[i]) ) {
			if( cache_keys[i] ) Xstrncpy(stemkeys,cache_keys[i] ,LONGSTRING);
			else *stemkeys = 0;
			return(1);
		}
		
	}
	return(0);
}

add_deriv_cache(char *s, char *keys)
{
	int i;
	
	if( ! badinit ) {
		for(i=0;i<BADTRIES;i++) {
			cache_stems[i] = (char *)malloc((size_t)MAXWORDSIZE+1);
			cache_stems[i][0] = 0;
			cache_keys[i] = NULL;
		}
		badinit = 1;
	}
	if( badindex >= BADTRIES ) badindex = 0;
	Xstrncpy(cache_stems[badindex],s,MAXWORDSIZE);
	if( cache_keys[badindex] ) {
		free(cache_keys[badindex]);
	}
	if( ! *keys ) {
		cache_keys[badindex] = NULL;
	} else {
		cache_keys[badindex] = (char *)malloc((size_t)Xstrlen(keys)+1);
		strcpy(cache_keys[badindex],keys);
	}
	badindex++;
}

ends_in_vowel(char *s)
{
	char * p;
	
	p = lastn(s,1);
	while(p>=s&&!isalpha(*p)) p--;
	return(Is_vowel(*p));
}
