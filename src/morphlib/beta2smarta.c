#include <gkstring.h>
#include <smk.h>
#define ACUTEFLAG 		01
#define GRAVEFLAG 		02
#define CIRCUMFLAG 		04
#define SMOOTHFLAG 		010
#define	ROUGHFLAG		020
#define LONGMARK		040
#define DIAERFLAG		0100
#define SHORTFLAG		0200
#define ISUBFLAG		0400
#define EQUALS   		'='
#define UCASEMARKER		'^'
#define SMARTA_ROUGH_RHO		0373
#define SMK_ROUGH_RHO		075
#define TERMINAL_SIGMA	'w'
#define GREEK 			0100
#define ROMAN 			0200
#define AISUB			046
#define HISUB			0372
#define WISUB			0304
#define IS_CHARSTYLE(S) (*S == '&' && (*(S+1) == '3' || *(S+1) == '1' ))
#define END_CHARSTYLE(S) if (xlit==SMARTA) 	*S++ = 0253;/* \
else { strcpy(S,"}"), S ++; }*/

#define GKFONT "}{\\f132 "
#define ROMANFONT "}{"
#define BOLDFONT "}{\\b "
#define ITALICFONT "}{\\ulw "
static int charstyle_flag = 0;
#define ITALIC '3'
#define BOLD '1'

#include "beta2smarta.proto.h"
static init_gktab(void);
static int acctab[] = {
	ACUTEFLAG,
	GRAVEFLAG,
	CIRCUMFLAG,
	SMOOTHFLAG,
	ROUGHFLAG,
	SMOOTHFLAG|ACUTEFLAG,
	ROUGHFLAG|ACUTEFLAG,
	SMOOTHFLAG|GRAVEFLAG,
	ROUGHFLAG|GRAVEFLAG,
	SMOOTHFLAG|CIRCUMFLAG,
	ROUGHFLAG|CIRCUMFLAG
};

static int gktab[256];
static int accenttab[256];
static gkinit = 0;
static cur_font = GREEK;
char * greekfont(),  * romanfont();

static 
init_gktab(void)
{
	
	gkinit++;
	
	accenttab['/'] = ACUTEFLAG;
	accenttab['\\'] = GRAVEFLAG;
	accenttab['='] = CIRCUMFLAG;
	accenttab[')'] = SMOOTHFLAG;
	accenttab['('] = ROUGHFLAG;
	accenttab[HARDLONG] = LONGMARK;
	accenttab['+'] = DIAERFLAG;
	accenttab[HARDSHORT] = SHORTFLAG;
	accenttab['|'] = ISUBFLAG;
	
	gktab[' '] = 0200;
	gktab['a'] = 0213;
	gktab['e'] = 0241;
	gktab['h'] = 0256;
	/* note that 'v' is SMK for omega (beta code 'w'). */
	gktab['v'] = 0305;
	gktab['i'] = 0333;
	gktab['u'] = 0346;
	gktab['o'] = 0361;
	gktab[AISUB] = 0226;
	gktab[WISUB] = 0320;
	gktab[HISUB] = 0271;
}

/*
static int gktab[256];
*/
#define Is_accflag(X) (accenttab[X] > 0 && accenttab[X] <= ISUBFLAG )
#define SMARTA 2
#define SMK 4

beta2smarta(char *source, char *res)
{
	beta2mac(source,res,SMARTA);
}

beta2smk(char *source, char *res)
{
	beta2mac(source,res,SMK);
}

set_greek(void)
{
	cur_font = GREEK;
}

set_roman(void)
{
	cur_font = ROMAN;
}

beta2mac(char *source, char *res, int xlit)
{
	 char * sp;
	/*unsigned*/ char * rp;
	int acc;
	int saw_isub = 0;
	int long_vowel = 0;
	
	if( ! gkinit ) init_gktab();
	
	sp = source; rp = res;
	
	while(*sp) {
		if( *sp == '$' ) {
			if( charstyle_flag ) {
				if( rp == res ) {
					END_CHARSTYLE(rp);
/*					*rp++ = 0253;*/
				} else {
					if( rp > res) rp--;
/* grc 6/26/89
					while(*rp == ' ' && rp > res ) rp--;
*/
					if( ispunct(*rp) ) {
						*(rp+1) = *rp;
						END_CHARSTYLE(rp);
/*						*rp = 0253;
						rp++; 
*/
						rp++;
					} else {
						rp++;
						END_CHARSTYLE(rp);
/*						*rp++ = 0253;*/
					}
/*
					*rp++ = ' ';
*/
				}
				charstyle_flag = 0;
			}
			sp = greekfont(sp);
			if( xlit == SMK ) {
				strcpy(rp,GKFONT); 
				rp += Xstrlen(GKFONT);
			}
			continue;
		} else if( *sp == '&' ) {

			if( charstyle_flag  && ! IS_CHARSTYLE(sp)) {
				END_CHARSTYLE(rp);
				charstyle_flag = 0;
			}
/*
			} else if( ! charstyle_flag && IS_CHARSTYLE(sp)  ) {
*/
			if( IS_CHARSTYLE(sp) ) {
				if( (*(sp+1) == '3' && charstyle_flag == BOLD ) &&
					(*(sp+1) == '1' && charstyle_flag == ITALIC ) ) {
						END_CHARSTYLE(rp);
						charstyle_flag = 0;
				}
				if( *(sp+1) == '3' )
					charstyle_flag = ITALIC;
				else if( *(sp+1) == '1' )
					charstyle_flag = BOLD;
/*
				*rp++ = ' ';
*/
				if( xlit == SMARTA ) 
					*rp++ = 0137;
				else {
					if( charstyle_flag == ITALIC ) {
						strcpy(rp,ITALICFONT); rp += Xstrlen(ITALICFONT);
					} else {
						strcpy(rp,BOLDFONT); rp += Xstrlen(BOLDFONT);
					}
				}
				sp += 2;
				while(isspace(*sp)) sp++;
			}
			sp = romanfont(sp);
			if( xlit == SMK && ! charstyle_flag && *(rp-1) != '}' ) {
				strcpy(rp,ROMANFONT);  rp += Xstrlen(ROMANFONT);
			}
			continue;
		}
			
		if( *sp == '%' ) {
			int n;
			char numbuf[8];
			char * np;
			
			np = numbuf;
			n = atoi(++sp);
			while(isdigit(*sp)) *np++ = *sp++;
			*np = 0;
			
			switch(n) {
				case 1:
					*rp++ = '?';
					break;
				case 2:
					*rp++ = '*';
					break;
				case 4:
					*rp++ = '!';
					break;
				case 6:
					if( xlit == SMARTA ) 
						*rp++ = EQUALS;
					else {
						if( cur_font == GREEK ) {
							strcpy(rp,ROMANFONT);
							rp += Xstrlen(ROMANFONT);
							strcpy(rp,"=}{");
							rp += 3;
							strcpy(rp,GKFONT);
							rp += Xstrlen(GKFONT);
						} else
							*rp++ = '=';
					}
					break;
				case 10:
					if( xlit == SMARTA )
						*rp++ = '`';
					else
						*rp++ = ':';
					break;
				case 40:
					if( xlit == SMK ) {
						*rp++ = ' ';
						*rp++ = SMK_SHORTMARK;
					} else if( xlit == SMARTA ) {
						*rp++ = SMARTA_SHORTMARK;
						break;
					}
				case 41:
					if( xlit == SMK ) {
						*rp++ = ' ';
						*rp++ = SMK_LONGMARK;
						break;
					} else if( xlit == SMARTA ) {
						*rp++ = SMARTA_LONGMARK;
					}
					
				default:
					np = numbuf;
					*rp ++ = '%';
					while(*np) *rp++ = *np++;
					break;
				}
			continue;
		}
		if( *sp == '*' && cur_font == ROMAN ) {
			if( xlit == SMARTA ) {
				*rp++ = UCASEMARKER;
			} else if (xlit == SMK ) {
				sp++;
				strcpy(rp,sp);
				if( islower(*rp) ) *rp = toupper(*rp);
				rp++;
			}
			sp++;
			continue;
		}
		if( cur_font == ROMAN &&isalpha(*sp) ) {
			if( isupper(*sp) ) {
				*rp++ = UCASEMARKER;
				*rp++ = *sp++;
				continue;
			} else {
				if( xlit == SMARTA ) 
					*rp++ = toupper(*sp++);
				else
					*rp++ = *sp++;
			}
			continue;
		}
		if( *sp == '[' && *(sp+1) == '1' && *(sp+2) != '.' ) {
				/* 
				 * grc 6/5/88
				 *
				 * note that we want to accept things like "[1.]" which show up
				 * all the time in the Greek English Lexicon.
				 */
				*rp++ = '(';
				sp += 2;
				continue;
		}
		
		if( *sp == ']' && *(sp+1) == '1') {
				*rp++ = ')';
				sp += 2;
				continue;
		}
		
		if(isalpha(*sp) || *sp == '*') {
			acc = 0;
			
			
			if( xlit == SMK && *sp == '*' ) {
				if( Is_accflag(*(sp+1)) ) {
					 char * t = sp;
					*sp = ' ';
					while(*t&&!isalpha(*t)) t++;
					if(isalpha(*t) && islower(*t) ) *t = toupper(*t);
				} else {
					strcpy(sp,sp+1);
					if(islower(*sp)) *sp = toupper(*sp);
				}
			} 
			

			*rp = *sp++;
			
			
			if( isupper(*rp) && xlit == SMARTA ) {
					*(rp+1) = tolower(*rp);
					*rp++ = UCASEMARKER;
			}

/*			if( *rp == '*' ) {
				if( xlit == SMARTA )
					*rp = UCASEMARKER;
				*sp = smk_char_xlit(*sp,sp+1);
			} else 
*/
				*rp = smk_char_xlit(*rp,sp,xlit);
/*			
			if( *rp == 's' && !isalpha(*sp) && *sp != '\'' && *sp != '-' )
				*rp = TERMINAL_SIGMA;
			else if( *rp == 'w' )
				*rp = 'v';
			else if( *rp == 'q' )
				*rp = 'y';
			else if( *rp == 'Q' )
				*rp = 'Y';
			else if( *rp == 'c' )
				*rp = 'j';
			else if( *rp == 'C' )
				*rp = 'J';
			else if (*rp == 'y' )
				*rp = 'c';
			else if (*rp == 'W' )
				*rp = 'V';
			else if (*rp == 'V' )
				*rp = 'C';
			else if( *rp == 'v' ) /* digamma *
				*rp = 'W';
			else if( *rp == '*' && xlit == SMARTA ) {
					*rp = UCASEMARKER;
			} /*else if ( xlit == SMK && ) {
					unsigned char * t = sp;
					if( Is_accflag(*sp)) {
							*rp = ' ';
						while(*t&&!isalpha(*t)) t++;
						if(isalpha(*t)&&islower(*t)) *t = toupper(*t);
					} else {
						*rp = toupper(*sp++);
					}
				}
					
			}*/
			
			while( Is_accflag(*sp) ) {

				if( *sp == HARDLONG ) {
					long_vowel++;
					sp++;
				} else if( *sp == '|' )  {
					saw_isub++;
					sp++;
				} else if (*sp == HARDSHORT)
					sp++;
				/*
				 * don't count the hard short marker (no way to print it for now)
				 */
				 else		
					acc += accenttab[*sp++];
			}
/*
printf("got [%o] ", acc );
*/
/*
			if( *sp == '|' ) {
				saw_isub++;
				sp++;
			}
*/
			/*
			 * if you see a capital letter marker 
			 * then keep that and find the letter that that
			 * capital would cover.
			 */
			if( acc && *rp == UCASEMARKER && xlit == SMARTA ) {
				if( isalpha(*sp ) ) {
					*++rp = *sp++;
					*rp = smk_char_xlit(*rp,sp,xlit);
				}
			} 
			
			/*
			 * don't bother showing the long mark if the letter is
			 * accented with a circumflex
			 */
			if( long_vowel )  {
				if( ! (acc & CIRCUMFLAG ) ) {
					if(xlit == SMARTA ) {
						if( *rp == 'a' )
							*rp = 046;
						else if( *rp == 'i' ) {
							*rp = 0372;
							*rp &= 0377;
						} else if( *rp == 'u' ) {
							*rp = 0304;
							*rp &= 0377;
						}
					} else if( xlit == SMK ) {
						*(rp+1) = *rp;
						*rp++ = '*';
					}
				} 
				long_vowel = 0;
			}
			if( saw_isub && xlit == SMK ) {
				switch(*rp) {
					case 'a':
						*rp = AISUB;
						break;
					case 'h':
						*rp = HISUB;
						*rp &= 0377;
						break;
					case 'v':
						*rp = WISUB;
						*rp &= 0377;
						break;
					default:
						break;
				}
				saw_isub = 0;
			} 
				
			
			if( acc ) {
				if(*rp == 'r' && acc == ROUGHFLAG ) {
					if( xlit == SMK ) 
						*rp = SMK_ROUGH_RHO;
					else
						*rp = SMARTA_ROUGH_RHO;
				} else if( acc == DIAERFLAG  &&
							(*rp == 'i' || *rp == 'u') ) {
					if( *rp == 'i' ) 
						*rp = 0363;
					else 
						*rp =  043;
				} else if( acc == (DIAERFLAG|ACUTEFLAG)  &&
							(*rp == 'i' || *rp == 'u') ) {
					if( *rp == 'i' ) 
						*rp = 0375;
					else 
						*rp =  0100;
				}else if( acc == (DIAERFLAG|GRAVEFLAG)  &&
							(*rp == 'i' || *rp == 'u') ) {
					if( *rp == 'i' ) 
						*rp = 0376;
					else 
						*rp =  0243;
				} else if( !gktab[*rp] ) {
					*(rp+1) = *rp;
					*rp = '?';
					rp += 2;
					*rp = '?';
				} else
					*rp = (unsigned char) (gktab[*rp] + accnum(acc));
/*
if(1) {
int n;
n = *rp;
n &= 0377;
printf(" *rp [%o] n [%o] ", *rp , n  );
}
*/
			}
			if( saw_isub && xlit == SMARTA ) {
				saw_isub = 0;
				*++rp = 'i';
			}
		}  else if( *sp == '_' ) {
			*rp = '-';
			sp++;
		} else
			*rp = *sp++;
		rp++;
	}
	*rp = 0;
}

accnum(int n)
{
	int i;
	
	for(i=0;i<sizeof acctab/sizeof acctab[0];i++ )
		if( n == acctab[i] )
			return(i);
	return(0);
}

char * 
romanfont(char *s)
{
	cur_font = ROMAN;
	while(*s && *s=='&') s++;
	if( isdigit(*s) ) while(isdigit(*s)) s++;
	else if( *s == ' '&& *(s+1) == ' ' ) s++;
	return(s);
}

char * 
greekfont(char *s)
{
	cur_font = GREEK;
	while(*s && *s=='$') s++;
	if( isdigit(*s) ) while(isdigit(*s)) s++;
	else if( *s == ' ' && *(s+1) == ' '  ) s++;
	return(s);
}

smk_char_xlit(int c, char *s, int xlit)
{
			if( c == 's' && !isalpha(*s) && *s != '\'' && *s != '-' )
				c = TERMINAL_SIGMA;
			else if( c == 'w' )
				c = 'v';
			else if( c == 'q' )
				c = 'y';
			else if( c == 'Q' )
				c = 'Y';
			else if( c == 'c' )
				c = 'j';
			else if( c == 'C' )
				c = 'J';
			else if (c == 'y' )
				c = 'c';
			else if (c == 'W' )
				c = 'V';
			else if (c == 'V' )
				c = 'C';
			else if( c == 'v' ) /* digamma */
				if( xlit == SMARTA ) 
					c = 'q';
				else c = 'W';
			else if( c == '*' && xlit == SMARTA ) 
				c = UCASEMARKER;

			return(c);
}
