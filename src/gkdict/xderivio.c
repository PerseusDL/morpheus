#include <gkstring.h>

#include "xderivio.proto.h"

checkforderiv(char *stemstr, char *stemkeys)
{
	int rval = 0;
	int rval2 = 0;
	char * p, * is_substring();
	char stemkeys2[LONGSTRING];
	
	stemkeys2[0] = 0;
	
	rval=checkforderiv2(stemstr,stemkeys,0);

/*	if( rval ) return(rval);*/
	
	
	rval2 = checkforredupderiv(stemstr,stemkeys2);
	if( rval2 ) {
		if( *stemkeys ) strcat(stemkeys," ");
		strcat(stemkeys,stemkeys2);
	}
	return(rval+rval2);

}

checkforredupderiv(char *stemstr, char *stemkeys)
{
	char noredup[MAXWORDSIZE];
		
	if( Is_cons(*stemstr) ) {
		if( ! un_redupl(stemstr,noredup,'e')) return(0);
		return(checkforderiv2(noredup,stemkeys,1));
	}
	return(checkaugredup(stemstr,stemkeys));
}
#define MAXREDUPLS 	04
checkaugredup(char *stemstr, char *stemkeys)
{
	int hits = 0;
	int i;
	int poss_redupls = 0;
	int possno = 0;
	char tmpkeys[LONGSTRING];


	gk_string * tstemtab[MAXREDUPLS];

	for(i=0;i<MAXREDUPLS;i++) {
		tstemtab[i] = CreatGkString(1);
	}
	poss_redupls = unaugment(stemstr,tstemtab,MAXREDUPLS,ALL_DIAL,1);
	
	for(i=0;i<poss_redupls;i++) {
		tmpkeys[0] = 0;
/*
printf("checking [%s]\n", gkstring_of(tstemtab[i]) );
*/
		if( checkforderiv2(gkstring_of(tstemtab[i]),tmpkeys,1) ) {
			if(*stemkeys) Xstrncat(stemkeys," ",LONGSTRING);
			Xstrncat(stemkeys,tmpkeys,LONGSTRING);
			hits++;
		}
/*
		printf("hits %d for [%s]\n", hits , gkstring_of(tstemtab[i]) );
*/
		
	}
	for(i=0;i<MAXREDUPLS;i++) {
		FreeGkString(tstemtab[i]);
	}
	return(hits);
}

checkforderiv2(char *stemstr, char *stemkeys, int had_redupl)
{
	char * ep;
	char derivstr[LONGSTRING];
	int rval = 0;
	int sofar = 0;
	int slen;
	char derivkeys2[LONGSTRING*2];
	char resbuf[LONGSTRING*2];
	
	ep = lastn(stemstr,1);
	slen = strlen(stemstr)-1;
	derivkeys2[0] = resbuf[0] = 0;
	Xstrncpy(derivstr,stemstr,LONGSTRING);

	rval = chckdvend("*",stemkeys);
	if(  chckderiv(derivstr,derivkeys2) ) {
		int n;
		n=checkcomderivs(stemkeys,"",derivkeys2,resbuf,had_redupl);
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
				n=checkcomderivs(stemkeys,ep,derivkeys2,resbuf,had_redupl);
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

checkcomderivs(char *derivs, char *suffix, char *lemmkeys, char *nkeys, int had_redupl)
{
	int rval = 0;
	char lkeybuf[LONGSTRING], curlemmkeys[LONGSTRING];
	
	Xstrncpy(curlemmkeys,lemmkeys,LONGSTRING);

	while(nextkey(curlemmkeys,lkeybuf)) {
		
		rval += checkcomderiv(derivs,suffix,lkeybuf,nkeys,had_redupl);
	}
	return(rval);
	
}

#define Is_perfect(STYPE) (((STYPE&VERBSTEM)== PP_PP)||\
							((STYPE&VERBSTEM)== PP_PF))

checkcomderiv(char *derivstr, char *suffix, char *lkeys, char *rkeys, int had_redupl)
{
	char curderiv[LONGSTRING];
	char curstem[LONGSTRING];
	char dbuf[LONGSTRING*4];
	char keybuf[LONGSTRING*2];
	char lemma[LONGSTRING+1];
	char tmpderivstr[MAXWORDSIZE];
	char stembuf[MAXWORDSIZE];
	gk_string Gstr;
	char * s;
	int rval = 0;

	Xstrncpy(dbuf,derivstr,sizeof dbuf);
	Xstrncpy(curstem,lkeys,sizeof curstem);
	s=curstem; /* separate off the stem if one is marked */
	while(*s&&*s!=':') s++;
	if(*s) {
		*s++ = 0;
	}
	Xstrncpy(lemma,s,LONGSTRING);

	if( curstem[0] ) {
		Xstrncpy(stembuf,curstem,MAXWORDSIZE);
		Xstrncat(stembuf,suffix,MAXWORDSIZE);
	}

	s = lemma;
	while(*s&&*s!=':') s++; /* now get the lemma */
	if(*s) {
		*s++ = 0;
	}
	
	Xstrncpy(keybuf,s,sizeof keybuf); /* now get the rest of the keys */
	s=keybuf;
	while(*s) {
		if(*s == ':' )
			*s = ' ';
		s++;
	}

	while(nextkey(dbuf,curderiv)) {
		stembuf[0] = 0;
		s=curderiv;
		if( *s && *s != ':' ) {
			char * p;
			
			strncpy(tmpderivstr,s,MAXWORDSIZE);
			s++;
			while(*s&&*s!=':') s++;
			if(*s) s++;
			strcpy(curderiv,s);
			
			p = tmpderivstr;
			while(*p&&*p!=':') p++;
			if(*p) *p = 0;
			if( curstem[0] ) {
				Xstrncpy(stembuf,curstem,MAXWORDSIZE);
				Xstrncat(stembuf,tmpderivstr,MAXWORDSIZE);
			}
			
		} else {
			if( curstem[0] ) {
				Xstrncpy(stembuf,curstem,MAXWORDSIZE);
				Xstrncat(stembuf,suffix,MAXWORDSIZE);
			}
		
		}
		while(*s) {
			if(*s == ':' )
				*s = ' ';
			s++;
		}

		if( CompatKeys(curderiv,keybuf,&Gstr))  {
			char tmp1[LONGSTRING*2], tmp2[LONGSTRING*2];
			
			/*
			 * grc 5/30/89
			 *
			 * don't accept things like "fi/lhka".  if the stemtype is a perfect,
			 * then the stem must have had a reduplication
			 */

			tmp1[0] = 0;
			if( ! had_redupl &&  (Is_perfect(stemtype_of(&Gstr) )) ) 
				continue;

			if( had_redupl && ! (Is_perfect(stemtype_of(&Gstr))) )
				continue;
			if( *rkeys ) 
				Xstrncat(rkeys," ",LONGSTRING);
			
			if( had_redupl ) add_morphflag(morphflags_of(&Gstr),REDUPL);
			SprintGkFlags(&Gstr,tmp1,":",1);
			sprintf(tmp2,"%s:%s%s", stembuf, lemma , tmp1);
/*
printf("success on [%s] and [%s]\n", curderiv, keybuf );
printf("about to add [%s]\n", tmp2 );
*/
			Xstrncat( rkeys,tmp2,LONGSTRING);
			rval++;
		}	

		
	}
	return(rval);
}