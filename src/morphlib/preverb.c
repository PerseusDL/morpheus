/*	Univ. of Calif. Greek Project	*/
/*	1985-86				*/
/*	Joshua Kosman			*/
/*	David Neel Smith		*/
/* 
 * modified by Greg Crane
 * Harvard University 1987
 */

#include <string.h>

#include <gkstring.h>
#include <preverb.h>

#include "preverb.proto.h"
static comp_preverb(char *, int, MorphFlags *);
static getprvbform(char *, char *, MorphFlags *);
static int verbose = 0;

bool checkprevb(char *word, char *prevb, bool *brflg)
/* remove preverb from word and reply whether preverb was found */
/* found preverb returned in prevb */
/* brflg = YES -> questionable breathing on word. Must try both types */
{
	int i;

/*
 * this loop allows you to come back to the list of preverbs
 * and skip over an aborted match.
 * e.g. skip past "pros" to "pro" if you had unsuccessfully
 * looked for "pros-ainw" rather than "pro-sainw"
 */
	for(i=0;i<NUMPREVBS;i++) {
		if( !*prevb ) break;
		if( ! strcmp(prevb,prevbs[i] ) ) {
			i++;
			break;
		}
	}


	for(;i<NUMPREVBS;i++)
		if (prvbcmp(prevbs[i],word,brflg)) {
			Xstrncpy(prevb,prevbs[i],MAXWORDSIZE);
			return (YES);
			}
	return(NO);
}



bool prvbcmp(char *prevb, char *word, bool *brflg)
/* does word begin with prevb? If so, strip it out */
{
	char workp[MAXPRVBSIZE],workw[MAXWORDSIZE];
	char workrest[MAXWORDSIZE];
	int lastc = *lastn(workp,1);

	Xstrncpy(workp,prevb,MAXWORDSIZE);
	Xstrncpy(workw,word,MAXWORDSIZE);
	stripacc(workp);
	stripacc(workw);
	*brflg = NO;

	/* Stab #2: if preverb ends in vowel (but isn't "pro"), check
		elided form */
	if (Is_vowel(lastc) && 0!=strcmp(lastn(workp,3),"pro")) {
		strsqz(lastn(workp,1),1);
		if (0==Xstrncmp(workp,workw,Xstrlen(workp))) {
			getrest(workrest,word,workw,workp);
			if (Is_vowel(workrest[0])) {	/* checkback */
				addbreath(workrest,SMOOTHBR);
				if (!Is_unasp(lastc))
					*brflg = YES;
				Xstrncpy(word,workrest,MAXWORDSIZE);
				return (YES);
				}
			}
		}

	/* first try: word begins with preverb in pristine form */

	if (0==Xstrncmp(workp,workw,Xstrlen(workp))) {
		getrest(workrest,word,workw,workp);
		if (Is_vowel(workrest[0])) {
			addbreath(workrest,SMOOTHBR);
			/* unless preverb ends in an unaspirated stop,
				nature of breathing is ambiguous */
			if (!Is_unasp(lastc))
				*brflg = YES;
			}
		else if (workrest[0] == 'r') {
			if (workrest[1] == 'r')
				strsqz(workrest,1);	/* drop duplicate r */
			cinsert(ROUGHBR,workrest+1);
			}
		Xstrncpy(word,workrest,MAXWORDSIZE);
		return (YES);
		}

	/* Number 3: check ek -> ec before vowels */
	if (0==strcmp(workp,"e)k") && 0==Xstrncmp(workw,"e)c",3)) {
		getrest(workrest,word,workw,workp);
		if (Is_vowel(workrest[0])) {	/* checkback */
			addbreath(workrest,SMOOTHBR);
			*brflg = YES; 	/* breathing always uncertain */
			Xstrncpy(word,workrest,MAXWORDSIZE);
			return (YES);
			}
		}

	/* Number 4: try aspirating final stop in preverb */
	if (Is_unasp(lastc)) {
		aspirate(lastn(workp,1));
		if (0==Xstrncmp(workp,workw,Xstrlen(workp))) {
			getrest(workrest,word,workw,workp);
			if (Is_vowel(workrest[0])) {
				/* checkback: there must be elision (else why
					aspirate?) */
				addbreath(workrest,ROUGHBR);
				Xstrncpy(word,workrest,MAXWORDSIZE);
				return (YES);
				}
			}
		}

	/* Number 5: final n (en or sun) changing euphonically */
	if ( (lastc=='n' || lastc == 'g' || lastc == 'r' || lastc == 'l') && 0==Xstrncmp(workp,workw,Xstrlen(workp)-1)) {
		Xstrncpy(workp,workw,Xstrlen(workp));  /* get beginning of word */
		getrest(workrest,word,workw,workp);
		switch (lastc) {
			case 'm':
				if (Is_labial(workrest[0]) ||
				    workrest[0] == 'm') {
					Xstrncpy(word,workrest,MAXWORDSIZE);
					return (YES);
					}
				break;
			case 'g':
				if (Is_palatal(workrest[0])) {
					Xstrncpy(word,workrest,MAXWORDSIZE);
					return (YES);
					}
				break;
			case 'l':
				if (workrest[0] == 'l') {
					Xstrncpy(word,workrest,MAXWORDSIZE);
					return (YES);
					}
				break;
			case 'r':
				if (workrest[0] == 'r') {
					cinsert(ROUGHBR,&workrest[1]);
					Xstrncpy(word,workrest,MAXWORDSIZE);
					return (YES);
					}
				break;
			}	/* switch */
		}
		
	
	return (NO);
}

getrest(char *workrest, char *word, char *workw, char *workp)
/* put non-preverb part of word into workrest */
/* workw and workp are unaccented word and preverb, respectively */
{
	register char *p1,*p2;

	p1 = workw+Xstrlen(workp);
	p2 = lastn(word,Xstrlen(p1));
	if (0==strcmp(p1,p2))
		Xstrncpy(workrest,p2,MAXWORDSIZE);
	else
		Xstrncpy(workrest,p2-1,MAXWORDSIZE);
/* nb this assumes no more than one accent in word; what if there's more? */
}

rstprevb(char *word, char *prevb, gk_string *gstr)
/* word <- prevb+word */
/* prevb should be fully accented (i.e.,from the array) */
{
	int max, i;
	char work[MAXWORDSIZE];
	char fullpb[MAXWORDSIZE];
	char tmpword[MAXWORDSIZE];
	gk_string TmpGstr;
	MorphFlags * oddpb = morphflags_of(gstr);

	fullpb[0] = 0;
	if( Is_indeclform(oddpb) ) return;

	if( cur_lang() == LATIN || cur_lang() == ITALIAN ) {
	   if( !has_morphflag(oddpb,RAW_PREVERB) ) {
		char * t;

		strcpy(work,prevb);
		t = work+strlen(work)-1;

		if( !strcmp(prevb,"circum") && *word == 'i' ) {
			*t = 0;
		}

		if( has_morphflag(oddpb,D_PREVB) ) {
			strcpy(work,prevb);
			strcat(work,"d");
		}

		if( has_morphflag(oddpb,T_PREVB) && !strcmp(prevb,"re") ) {
			strcpy(work,"ret");
		}

		if( !strcmp(prevb,"sub") || !strcmp(prevb,"ob") ) {

			switch(*word) {
				case 'c':
				case 'f':
				case 'g':
				case 'p':
					*t = *word;
					break;
				default:
					break;
			}
		}

		if( !strcmp(prevb,"ex") ) {

			if( ! strchr("aeioucpqt",*word) ) {
				if( *word == 'f') 
					*t = *word;
				else
					*t = '_';
			}
		}

		if( !strcmp(prevb,"trans") ) {

			switch(*word) {
				case 'i':
				case 'j':
				case 'd':
				case 'l':
				case 'm':
				case 'n':
					*(t-1) = 0;
					break;
				case 's':
					*t = 0;
					break;
				default:
					break;
			}
		}

/* 
 * dis- unchanged before "di" but loses 's' before 'd' otherwise 
 */
		if( !strcmp(prevb,"dis") && strncmp(word,"di",2)  ) {

			switch(*word) {
				case 'b':
				case 'd':
				case 'g':
				case 'l':
				case 'm':
				case 'n':
				case 'r':
				case 'v':
					*t = 0;
					break;
				case 'f':
					*t = 'f';
					break;
				default:
					break;
			}
		}

		if( !strcmp(prevb,"sub") ) {

			switch(*word) {
				case 'r':
				case 'm':
					*t = *word;
					break;
				case 's':
					*t = 0;
					break;
				default:
					break;
			}
		}

		if( !strcmp(prevb,"in") ) {

			switch(*word) {
				case 'l':
					*t = 'l';
					break;
				case 'b':
				case 'p':
				case 'm':
					*t = 'm';
					break;
			}
		}

		if( !strcmp(prevb,"con") ) {

			switch(*word) {
				case 'b':
				case 'p':
				case 'm':
					*t = 'm';
					break;
				case 'r':
				case 'l':
					*t = * word;
					break;
				case 'n':
					*t = '_';
					break;
				default:
					break;
			}
		}

		if( !strcmp(prevb,"ad") ) {

			switch(*word) {
				case 'c':
				case 'f':
				case 'l':
				case 'n':
				case 'p':
				case 's':
				case 't':
					*(work+strlen(work)-1) = * word;
					break;
				case 'g':
					*t = 0;
					break;
				default:
					break;
			}
		}
	
		
		strcat(work,word);
		strcpy(word,work);
		return;
	   }
	}
	

	if( has_morphflag(oddpb,DOUBLED_CONS) ) {
		for(i=0;*word && !Is_cons(*word);i++) tmpword[i] = *word++;
		tmpword[i] = * word;
		i++;
		Xstrncpy(tmpword+i,word,MAXWORDSIZE);
	} else
		Xstrncpy(tmpword,word,MAXWORDSIZE);
		
		
	if( Keep_rawpreverb(oddpb) ) {
/*
 * grc 6/27/89
 *
 * the key word raw_preverb only pertains the connection between preverb and verb,
 * not to the way in wich preverbs pile up on each other:  thus, we want to get
 *
 * a)ntapo-ai/rw
 *
 * but *not* a)ntiapo-ai/rw (or, worse, a)nti/,a)po/-ai/rw!)
 */	
		Xstrncpy(work,prevb,MAXWORDSIZE);
		comp_preverb(work,0,oddpb);
		if( Is_vowel(*(lastn(work,1))) && Is_vowel(*word) ) strcat(work,"+");
		set_odd_prvb(oddpb,work);
		stripbreath(tmpword); /* avoid forms such as a)na-oi)/gw */
		Xstrncat(work,tmpword,MAXWORDSIZE);
		Xstrncpy(word,work,MAXWORDSIZE);
		return;
	}
	
	set_morphflag(morphflags_of(&TmpGstr),0);
	exp_preverb(prevb,fullpb,&TmpGstr);

	if( fullpb[0] )
		Xstrncpy(work,fullpb,MAXWORDSIZE);
	else
		Xstrncpy(work,prevb,MAXWORDSIZE);
	stripacc(work);
	
	if( Has_apocope(oddpb) ) {
		char * s = work + Xstrlen(work) - 1;

		if( *s == 'a' || *s == 'o' ) {
			*s = 0;
		}
	} 
	
	if( has_morphflag(oddpb,IOTA_INTENS) && *lastn(work,1) == 'n' ) {
		strcat(work,"i");
	}

	comp_preverb(work,has_morphflag(oddpb,UNASP_PREVERB),oddpb);
	set_odd_prvb(oddpb,work);
/*	
	if( has_morphflag(oddpb,SIG_TO_CI) ) {
		shift_su_to_cu(work);
	}
	if( has_morphflag(oddpb,SHORT_EIS) ) {
		shift_eis_to_es(work);
	}
	if( has_morphflag(oddpb,PROS_TO_POTI) ) {
		shift_pros_to_poti(work);
	}
	if( has_morphflag(oddpb,PROS_TO_PROTI) ) {
		shift_pros_to_proti(work);
	}
	if( has_morphflag(oddpb,META_TO_PEDA) ) {
		shift_meta_to_peda(work);
	}
*/
	getprvbform(tmpword,work,oddpb);

	max = MAXWORDSIZE - Xstrlen(work);
	if(Xstrlen(tmpword) >= max) {
		tmpword[max-1] = 0;
		tmpword[max-2] = CONTCHAR;
	}
	stripbreath(tmpword);

	Xstrncat(work,tmpword,MAXWORDSIZE);
	Xstrncpy(word,work,MAXWORDSIZE);
}

static
comp_preverb(char *pb, int unasp, MorphFlags *oddpb)
{
	char *s;
	gk_string  Gstr;
	int added_aug = 0;

	s = pb;
	set_morphflag(morphflags_of(&Gstr),HAS_PREVERB);
	if( unasp ) add_morphflag(morphflags_of(&Gstr),UNASP_PREVERB);
/*
 * grc 1/22/90
 * unbelievable kludge so that we can get e)ni-ka/t-qeo through (from hesiod)
 */
	if( has_morphflag(oddpb,EN_TO_ENI) ) 
			add_morphflag(morphflags_of(&Gstr),EN_TO_ENI);

	
	if( ! strchr(s,',') && has_morphflag(oddpb,PREVB_AUGMENT) && ! added_aug) {
			add_double_augment(s,oddpb);
			added_aug++;
	}
	
	while(*s) {
		if(*s == ',') {
			
			*s = 0;
			s++;
			if( ! strchr(s,',') && has_morphflag(oddpb,PREVB_AUGMENT) && ! added_aug) {
					add_double_augment(s,oddpb);
					added_aug++;
			}

/*
			rstprevb(s,pb,morphflags_of(&Gstr));
*/
			rstprevb(s,pb,&Gstr);
			Xstrncpy(pb,s,MAXWORDSIZE);

			s = pb;

			continue;
		}
		s++;
	}
}

static
getprvbform(char *word, char *prevb, MorphFlags *oddpb)
{
	
	stripacc(prevb); /* accents on the word stem take priority */
	
	if (!verbose) {		/* process normally */
	
	/*
	 * grc 7/14/89
	 *
	 * cope with forms such as pera/ptwn
	 */
		if( (! strcmp(lastn(prevb,4),"peri") || ! strcmp(lastn(prevb,5),"proti"))
			&& has_morphflag(oddpb,ELIDE_PREVERB)) {
			*lastn(prevb,1) = 0;
		} else 
		
		/*
		 * grc 6/5/88
		 * a)mfi-exw --> a)mp-exw
		 * a)mfi-isxw --> a)mp-isxw
		 */
		if( !strcmp(lastn(prevb,3), "mfi")) {
			if( /*First_K_aspirate(word)  && */has_dissimilation(oddpb) ) {
				*(lastn(prevb,2)) = 'p'; /* dissimilate */
				if( Is_vowel(*word) ) strsqz(lastn(prevb,1),1);
	/*
	 * note the convoluted, but deliberate transformation that takes place 
	 * at this point:
	 *
	 * a)mfi-e(/cw --> a)mpi-e(/cw --> a)mp-e(/cw --> a)mf-e(/cw
	 *
	 * This process gets us to the form a)mf-e/cw rather than a)mfi-e/cw
	 */
				if( getbreath(word) == ROUGHBR ) {
					*lastn(prevb,1) = 'f';
					zap_morphflag(oddpb,DISSIMILATION);
				}
			} else
			/*
			 * grc 6/5/88
			 * note that you often do not elide the 'i' at the end of
			 * a)mfi/. we handle this as follows:
			 *		a)mfi + i --> elide an iota
			 *		or if the morphflag ELIDE_PREVERB is set --> elide the iota
			 *		otherwise --> leave it be
			 *
			 */

				if( *word == 'i' || elide_preverb(oddpb) )  strsqz(lastn(prevb,1),1);
		} 
		/* a)nti+oxeu/omai --> a)ntioxeu/omai, not a)ntoxeu/omai */
		else if( !strcmp(lastn(prevb,3), "nti") && Is_vowel(*word) )  {
			if( *word != 'o'  ) {
				*lastn(prevb,1) = 0;
			} else if( *word == 'o' &&  elide_preverb(oddpb) ) {
				*lastn(prevb,1) = 0;
			} else 
				if( elide_preverb(oddpb) ) *lastn(prevb,1) = 0;
		/*
		 * grc 8/3/89
		 * added this condition to account for a)nqi/stanto
		 */
			if( *lastn(prevb,1) == 't' && getbreath(word) == ROUGHBR && 
			  ! has_morphflag(oddpb,UNASP_PREVERB) )
				*lastn(prevb,1)  = 'q';
		} else if (Is_vowel(*word) ) {
			  if( strcmp(lastn(prevb,3),"pro")&&strcmp(lastn(prevb,4),"peri")&&
			  	 strcmp(lastn(prevb,5),"proti")){
				if (Is_vowel(*lastn(prevb,1))) {
					if (*lastn(prevb,1) != 'i') {	/* dia + vowel --> di */
						strsqz(lastn(prevb,1),1);
					} else if( *lastn(prevb,2) !='d'/* &&
						   *lastn(prevb,2) !='r' */ ) {
						strsqz(lastn(prevb,1),1);
					}
				}

				if( *(lastn(prevb,1)) == 'k' ) 
					*lastn(prevb,1) = 'c';
				else if (Is_unasp(*lastn(prevb,1)) &&
				    getbreath(word)==ROUGHBR && !Has_unasp_preverb(oddpb))
						aspirate(lastn(prevb,1));
			  } else {
			  	strcat(prevb,"+");
/*
 * grc 7/14/89 
 *
 * deal with forms such as pro/idon 
 */
 			}
 			
		}
/*
 * grc 7/13/89
 *
 * kat-ba/llei --> kab-ba/llei
 * ka/t-lipe --> ka/llipe
 * kat-pau/ei --> kappau/ei
 *
 * grc 8/18/89
 * kat-kei/ontes --> kak-kei/ontes
 */
		else if( *lastn(prevb,1) == 't' ) {
			if( *word == 'f' ) 
				*lastn(prevb,1) = 'p';
			if( *word == 'd' ) /* kat-draqe/thn --> kan-draqe/thn */
				*lastn(prevb,1) = 'd';
			if( *word == 'n' ) /* kat-neu/sas --> kan-neu/sas */
				*lastn(prevb,1) = 'n';
			else if( *word == 's' ) 	
				*lastn(prevb,1) = 0;
			else if( Is_labial(*word) || Is_liquid(*word) || *word == 'p' || *word == 'b' || *word == 'k'  ) {
				*lastn(prevb,1) = *word;
			}  
		} else if (*lastn(prevb,1) == 'p') {	/* u(po/ */
			if( *word == 'b' ) 
				*lastn(prevb,1) = 'b';	/* u(p-ba/llein --> u(b-ba/llein */
		}
		   else if (*lastn(prevb,1) == 'n') {	/* en & sun */
			if (Is_labial(*word) || *word == 'm'|| *word == 'y')
				*lastn(prevb,1) = 'm';
			else if (Is_palatal(*word))
				*lastn(prevb,1) = 'g';
			else if (*word == 'r' || *word == 'l')
				*lastn(prevb,1) = *word;
/*
 * 2/22/87
 * added by grc to account for forms such as "sustrateu/w" ( < sun + strateu/w )
 * so if preverb is "sun", truncate it to "su"
 */
/*
 * 7/1/89 grc
 *
 * added the case for 'z' to deal with forms such as su-zhte/w
 */
		
			else if ((*word == 's'||*word=='z')  && *lastn(prevb,2) == 'u' ) {
				if( Is_stop(*(word+1)) || *word == 'z')
					*lastn(prevb,1) = 0;
				else
/*
 * 7/1/89 grc
 * this condition added to deal with verbs such as sus-sebi/zw, sus-seu/w
 */
 					*lastn(prevb,1) = 's';
				}
		}
/*
 *
 * grc 6/29/89
 *
 * this check was producing forms such as ei)s-rre/w
 *
 		else if (*word == 'r' && *lastn(prevb,1) != 'r' )	/* double it *
 */
		else if (*word == 'r' && Is_vowel(*lastn(prevb,1))  &&
/* grc 6/29/89 -- add the check for raw_preverb when i failed to analyze e)kprore/w */
			!has_morphflag(oddpb,RAW_PREVERB) )	/* double it */
				cinsert('r',word);

		if (getbreath(word) != NOBREATH)
			stripbreath(word);
		}
	else		/* be explicit */
		Xstrncat(prevb," + ",MAXWORDSIZE);
}

First_K_aspirate(char *word)
{
	while(*word&&!Is_cons(*word)) word++;
	if( ! *word ) return(0);
	if(Is_asp(*word) || Is_asp(*(word+1)) ) return(1);
	return(0); 
}

shift_su_to_cu(char *s)
{
	while(*s) {
		if(*s=='s'&&*(s+1)=='u') *s = 'c';
		s++;
	}
}

shift_eis_to_es(char *s)
{
	while(*s) {
		if(!Xstrncmp(s,"eis",3) || !Xstrncmp(s,"ei)s",4) ) {
			strcpy(s+1,s+2);
			return;
		}
		s++;
	}
}
shift_pros_to_poti(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"pros",4) ) {
			strcpy(tmp,s+4);
			strcpy(s,"poti");
			strcat(s,tmp);
			return;
		}
		s++;
	}
}
shift_pros_to_proti(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"pros",4) ) {
			strcpy(tmp,s+4);
			strcpy(s,"proti");
			strcat(s,tmp);
			return;
		}
		s++;
	}
}
shift_upo_to_upai(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"upo",3) ) {
			strcpy(tmp,s+3);
			strcpy(s,"upai");
			strcat(s,tmp);
			return;
		} else if(!Xstrncmp(s,"u(po",4) ) {
			strcpy(tmp,s+4);
			strcpy(s,"u(pai");
			strcat(s,tmp);
			return;
		}
		s++;
	}
}
shift_uper_to_upeir(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"uper",4) ) {
			strcpy(tmp,s+4);
			strcpy(s,"upeir");
			strcat(s,tmp);
			return;
		} else if(!Xstrncmp(s,"u(per",5) ) {
			strcpy(tmp,s+5);
			strcpy(s,"u(peir");
			strcat(s,tmp);
			return;
		}
		s++;
	}
}
shift_para_to_parai(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"para",4) ) {
			strcpy(tmp,s+4);
			strcpy(s,"parai");
			strcat(s,tmp);
			return;
		} 
		s++;
	}
}
shift_meta_to_peda(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"meta",4) ) {
			strcpy(tmp,s+4);
			strcpy(s,"peda");
			strcat(s,tmp);
			return;
		}
		s++;
	}
}
shift_en_to_eni(char *s)
{
	char tmp[MAXWORDSIZE];
	
	while(*s) {
		if(!Xstrncmp(s,"e)n",3) && Xstrncmp(s,"e)ni",4)) {
			strcpy(tmp,s+3);
			strcpy(s,"e)ni");
			strcat(s,tmp);
			return;
		}
		if(!Xstrncmp(s,"en",2) && Xstrncmp(s,"eni",3)) {
			strcpy(tmp,s+2);
			strcpy(s,"eni");
			strcat(s,tmp);
			return;
		}
		s++;
	}
}

set_odd_prvb(MorphFlags *oddpb, char *work)
{	

	if( has_morphflag(oddpb,SIG_TO_CI) ) {
		shift_su_to_cu(work);
	}
	if( has_morphflag(oddpb,SHORT_EIS) ) {
		shift_eis_to_es(work);
	}
	if( has_morphflag(oddpb,PROS_TO_POTI) ) {
		shift_pros_to_poti(work);
	}
	if( has_morphflag(oddpb,PROS_TO_PROTI) ) {
		shift_pros_to_proti(work);
	}
	if( has_morphflag(oddpb,META_TO_PEDA) ) {
		shift_meta_to_peda(work);
	}
	if( has_morphflag(oddpb,UPO_TO_UPAI) ) {
		shift_upo_to_upai(work);
	}
	if( has_morphflag(oddpb,PARA_TO_PARAI) ) {
		shift_para_to_parai(work);
	}
	if( has_morphflag(oddpb,UPER_TO_UPEIR) ) {
		shift_uper_to_upeir(work);
	}
	if( has_morphflag(oddpb,EN_TO_ENI) ) {
		shift_en_to_eni(work);
	}
}
