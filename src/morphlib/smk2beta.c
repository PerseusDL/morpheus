#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "smk2beta.h"

#define MAXCHAR 		256
#define MAXSUBSTRING 	6
#define ROMAN 1
#define GREEK 2
#define ITALIC 3

#include "smk2beta.proto.h"
static conv(char *, char *);
static add_acc(char *, int);
static int smkinited = 0;
char *Xlit_table_smk[MAXCHAR+1];
char *Xlit_table_smarta[MAXCHAR+1];
char **Xlit_table;
char smarta_char[MAXCHAR+1];
static int fromsmk = 0;
static int cur_font = 0;

smarta2beta(char *start, char *result)
{
	Xlit_table = Xlit_table_smarta;
	
	fromsmk = 0;
	
	conv(start,result);
}

smk2beta(char *start, char *result)
{
	Xlit_table = Xlit_table_smk;

	fromsmk = 1;
	
	conv(start,result);
}

static
conv(char *start, char *result)
{
	char tmp[BUFSIZ];
	/*unsigned*/ char * s = start;
	
	cur_font =  0;
	if( !smkinited ) {
		smkinited++;
		init_smk();
	}
	
	*result = 0;
	/*
	 * make sure that any unaccented upper case char gets properly converted
	 */
	if(isupper(*s) && fromsmk) {
		strcpy(tmp,s+1);
		*(s+1) = tolower(*s);
		*s = '*';
		strcpy(s+2,tmp);
	}
	
	while(*s) {
/*
if( Xstrlen(result) > 256 ) {
printf("hey:%s\n", result);
*(result+256 ) = 0;
return;
}
*/
		if( *s == '^' && ! fromsmk ) {
			s++;

			trap_upper(result,s);
			s++;
/*
			strcat(result,"*");
*/
			continue;
		}
		
		if(isupper(*s) && ! fromsmk ) {
			if( cur_font == GREEK || ! cur_font ) 
				set_cur_font(ROMAN,result);
			tmp[0] = tolower(*s);
			tmp[1] = 0;
			strcat(result,tmp);
			s++;
			continue;
		}
		if( *s == '_' && ! fromsmk ) {
			set_cur_font(ITALIC,result);
			s++;
			continue;
		}
		if( *s == '«' && ! fromsmk ) {
			set_cur_font(ROMAN,result);
			s++;
			continue;
		}
		if(*s == '`' && ! fromsmk ) {
			if( ! cur_font || cur_font == GREEK ) {
				set_cur_font(ROMAN,result);
			}
			strcat(result,":");
			s++;
			continue;
		}
		
		if( (*s & 0377) >= 0202 && (*s & 0377) <= 0212 ) {
			set_cur_font(GREEK,result);	
			strcat(result,Xlit_table[(int)(*s++ & (0377))]);
			
			/*
			 * we should only have an accented space (0202 thru 0212)
			 * if we have an upper case vowel following. in this case,
			 * we want to convert to a slighly different sequence for
			 * beta. 
			 *
			 * something like "\0205A" would be "*)/a" in beta
			 * transliteration
			 */
			if( isupper(*s) ) {
				tmp[0] = tolower(*s);
			} else
				tmp[0] = *s;
			tmp[0] = smk2betachar(tmp[0]);
			tmp[1] = 0;
			strcat(result,tmp);
			s++;	
		} else {
			if( ! fromsmk ) {
				if( (smarta_char[(int)(*s & (0377))] || islower(*s)) && 
				  (cur_font == ROMAN || cur_font == ITALIC || ! cur_font ) )
					set_cur_font(GREEK,result);	
			}
			strcat(result,Xlit_table[(int)(*s++ & (0377))]);
		}
	}
}

smk2betachar(int c)
{
	if( c == 'v' ) return('w');
	if( c == 'y' ) return('q');
	if( c == 'c' ) return('y');
	if( c == 'j' ) return('c');
	if( c == 'W' ) return('v');
}

init_smk(void)
{
	int i;
	char tmp[80];

	for(i=0;i<MAXCHAR;i++) {
		Xlit_table_smk[i] = malloc((size_t)MAXSUBSTRING);
		*Xlit_table_smk[i] = 0;

		Xlit_table_smarta[i] = malloc((size_t)MAXSUBSTRING);
		*Xlit_table_smarta[i] = 0;
	}
		
	for(i=0;i<sizeof Beta_SMK/sizeof Beta_SMK[0];i++) {
		strncpy(Xlit_table_smk[Beta_SMK[i].keycode],Beta_SMK[i].keystring,MAXSUBSTRING);
		strncpy(Xlit_table_smarta[Beta_SMK[i].keycode],Beta_SMK[i].keystring,MAXSUBSTRING);
		smarta_char[Beta_SMK[i].keycode] =1;
/*
printf("%d) Xlit_table [%s]\n", Beta_SMK[i].keycode , Xlit_table[Beta_SMK[i].keycode] );
*/
	}
	for(i=0;i<sizeof Beta_Smarta/sizeof Beta_Smarta[0];i++) {
		strncpy(Xlit_table_smarta[Beta_Smarta[i].keycode],Beta_Smarta[i].keystring,MAXSUBSTRING);
	}
	
	for(i=0;i<256;i++) {
		if( ! *Xlit_table_smk[i] ) {
			sprintf(Xlit_table_smk[i] , "%c", i );
		}
		if( ! *Xlit_table_smarta[i] ) {
			sprintf(Xlit_table_smarta[i] , "%c", i );
		}
	}

}

set_cur_font(int n, char *s)
{
	if( fromsmk ) return;
	
	if( n != cur_font ) {
		switch(n) {
			case GREEK:
				strcat(s,"$");
				break;
			case ROMAN:
				strcat(s,"&");
				break;
			case ITALIC:
				strcat(s,"&3");
				break;
			default:
				strcat(s,"?Font?");
				break;
			}
		cur_font = n;
		}
}
#define SPACE_ACUTE 0200
#define ALPHA_ACUTE 0213
#define EPSILON_ACUTE 0241
#define IOTA_ACUTE 0333
#define OMICRON_ACUTE 0361	
#define UPSILON_ACUTE 0346
#define ETA_ACUTE 0256
#define WMEGA_ACUTE 0305
#define AISUB_ACUTE 0226
#define EISUB_ACUTE 0372
#define WISUB_ACUTE 0304

trap_upper(char *res, char *s)
{
	char tmp[BUFSIZ];
	
	if( isupper(*s) ) {
		if( !cur_font || cur_font == GREEK ) {
			set_cur_font(ROMAN,res);
		}

		tmp[0] = '*';
		tmp[1] = tolower(*s);
		tmp[2] = 0;
		strcat(res,tmp);
		return;
	}
	
	if( islower(*s) ) {
		if( !cur_font || cur_font == ROMAN || cur_font == ITALIC ) {
			set_cur_font(GREEK,res);
		}
		tmp[0] = '*';
		tmp[1] = *s;
		tmp[2] = 0;
		strcat(res,tmp);
		return;
	}

	tmp[0] = 0;
	if( SMK_ALPHA(*s) ) {
		add_acc(tmp, *s - ALPHA_ACUTE + SPACE_ACUTE);
		strcat(tmp,"a");
	} else if( SMK_EPSILON(*s) ) {
		add_acc(tmp, *s - EPSILON_ACUTE + SPACE_ACUTE);
		strcat(tmp,"e");
	} else if( SMK_IOTA(*s) ) {
		add_acc(tmp, *s - IOTA_ACUTE + SPACE_ACUTE);
		strcat(tmp,"i");
	} else if( SMK_OMICRON(*s) ) {
		add_acc(tmp, *s - OMICRON_ACUTE + SPACE_ACUTE);
		strcat(tmp,"o");
	} else if( SMK_UPSILON(*s) ) {
		add_acc(tmp, *s - UPSILON_ACUTE + SPACE_ACUTE);
		strcat(tmp,"u");
	} else if( SMK_ETA(*s) ) {
		add_acc(tmp, *s - ETA_ACUTE + SPACE_ACUTE);
		strcat(tmp,"h");
	} else if( SMK_WMEGA(*s) ) {
		add_acc(tmp, *s - WMEGA_ACUTE + SPACE_ACUTE);
		strcat(tmp,"w");
	} else if( SMK_AISUB(*s) ) {
		add_acc(tmp, *s - AISUB_ACUTE + SPACE_ACUTE);
		strcat(tmp,"_");
		strcat(tmp,"a");
	} else if( SMK_EISUB(*s) ) {
		add_acc(tmp, *s - EISUB_ACUTE + SPACE_ACUTE);
		strcat(tmp,"_");
		strcat(tmp,"h");
	} else if( SMK_WISUB(*s) ) {
		add_acc(tmp, *s - WISUB_ACUTE + SPACE_ACUTE);
		strcat(tmp,"_");
		strcat(tmp,"w");
	}
	if( tmp[0] ) {
		if( ! cur_font || cur_font == ROMAN || cur_font == ITALIC )
			set_cur_font(GREEK,res);
		strcat(res,tmp);
	}
}

static 
add_acc(char *s, int anum)
{
	strcpy(s,Xlit_table[(int)( anum & (0377))]);
}
