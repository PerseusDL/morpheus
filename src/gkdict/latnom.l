
%%

^[A-Za-z][a-z\^\_\-]+"ter\t"$	dump_adv();
^[A-Za-z\^\_\-\+]+[#1-9]* 	set_lemma(yytext);

"<orth type=alt>"[A-Za-z][^ <]+[\-\.]"</orth>"	set_orthalt(15);
"<orth>"[A-Za-z][^ <]+[\-\.]"</orth>"	set_orthalt(6);
"<orth>"[A-Za-z][^ <]+[a-z]"</orth>"	set_orth(4);
"<orth>"[A-Za-z][^ <]+[a-z][;:]"</orth>"	set_orth(4);
"<itype>"[^<]+"</itype>\t<pos>adj.</pos>"	dump_adj1(7);
"<itype>"[^<]+"</itype>\t<gen>"[^<]+"</gen>"	dump_form(yytext+yyleng-8);
"<itype>"[^<]+"</itype>"	dump_form2(7);
"<gen>"[^<]+"</gen>"	dump_form2(5);
"<pos>"[^<]+"</pos>"	dump_form3(5);

%%

#include <string.h>
#define MAXORTH 12
unsigned char orthtab[MAXORTH][BUFSIZ];

unsigned char curlemma[BUFSIZ], curstem[BUFSIZ], stemnoacc[BUFSIZ], curitype[BUFSIZ];
unsigned char curpat[BUFSIZ];
int dumped_stem = 0;


dump_adv()
{
	set_lemma(yytext);
	printf("\n:le:%s\n:wd:%s\tadverb\n", curlemma, yytext );
}

set_lemma(char *p)
{
	char * t = curlemma;
	int i;

	dumped_stem = 0;
	for(i=0;i<MAXORTH;i++) orthtab[i][0] = 0;

	ECHO;
	strcpy(curlemma,p);
	while(*t) {
		if( !isalpha(*t) && *t!='#' && !isdigit(*t) ) {
			strcpy(t,t+1);
			continue;
		}
		t++;
	}
	strcpy(stemnoacc,curlemma);
	if( strchr(stemnoacc,'#') ) *(strchr(stemnoacc,'#')) = 0;
	

	strcpy(curstem,yytext);

	if( strchr(curstem,'#') ) *(strchr(curstem,'#')) = 0;
}

set_orth(int tlen)
{
	unsigned char curpat[BUFSIZ], *s;
	
	ECHO;
	yytext[yyleng-tlen-3] = 0;

	strcpy(curpat,yytext+tlen+2);

	s = curpat; while(*s) s++; s--;
	if(*s == ';' || *s == ':' ) *s = 0;

	if( sameend(curpat,curstem) ) {
		strcpy(orthtab[0],curpat);
	}
}

sameend(char *s1, char *s2)
{
	/* don't need an alternate if the two are the same */
	if( ! strcmp(s1,s2)) return(0);
	if(*s1) {
		while(*s1) s1++; s1--;
	}


	if(*s2) {
		while(*s2) s2++; s2--;
	}
	return(*s1==*s2);
}

set_orthalt(int tlen)
{
	unsigned char curpat[BUFSIZ], *s;
	int rval;
	int lastc;

	ECHO;
	yytext[yyleng-8] = 0;
	strcpy(curpat,yytext+tlen);

	if( !strcmp(curpat,"trisyl.") || ! strcmp(curpat,"dissyl.")
	   || !strcmp(curpat,"quadrisyl.") ) return;

	s = strchr(curpat,0);
	while(s>=curpat&&!isalpha(*s)) s--;
	lastc = *s;
	if( unique_lastc(curstem,lastc,strlen(curpat)+2) ) {
		strcpy(orthtab[0],curpat);
		strcat(orthtab[0],strchr(curstem,lastc)+1);
	} else if( (rval=is_prevborth(curpat)) ) {
		char * t1, *t2;
		int i;
		strcpy(orthtab[0],curstem);
/*
 * e.g. acclamatio with orth "adc" --> adclamatio 
 */

		t1 = orthtab[0];
		for(i=0;i<rval;i++) {
			while(*t1&&!isalpha(*t1)) 
				t1++; /* point to first alphabetic char*/
			t1++;
		}
		while(*t1&&!isalpha(*t1)) t1++; /* point to 2nd alphabetic char*/
		t2 = t1;
		t2++;
		while(*t1&&!isalpha(*t2)) t2++; /* point to 2nd alphabetic char*/
		if( *t2 == *t1 ) {
			*t1 = curpat[rval]; /* unassimilate the 'd' */
		} else orthtab[0][0] = 0;
	}
}

unique_lastc(char * s, int n,int maxc)
{
	int rval = 0;
	int i = 0;

if( maxc > 2 ) s++;
/*
 * don't fail on "maxumus" vs. "maximus"
 */
	while(*s) {
		if(*s++ == n ) rval++;
		if(++i> maxc ) break;
		
	}
	return(rval == 1);
}

dump_adj(int trimn,char * stype,char *glab,char * nlab)
{
	dump_ent(trimn,"aj", stype,glab, nlab);
}

dump_nom(int trimn,char * stype,char *glab,char * nlab)
{
	
	dump_ent(trimn,"no", stype,glab, nlab);
}

dump_ent(int trimn,char *etag,char * stype,char *glab,char * nlab)
{

	unsigned char * s;
	char tmp[BUFSIZ];
	int i;
	

	dumped_stem = 1;
	if( ! trimn ) trimn = yytext[7];
	

/*
 * if trimn < 0, then you have a stem like "liber" which you do not
 * want to truncate!
 */

	strcpy(tmp,curstem);
	trimstem(curstem,trimn);
/*
	if( trimn > 0 ) {
		s = curstem;
		while(*s) s++; s--;
		while(s>=curstem && *s != trimn ) s--;
		*s = 0;
	}
*/

	printf("\n:le:%s\n", curlemma );
	printf(":%s:%s\t%s%s%s\n",etag, curstem, stype, glab, nlab );
	
	for(i=0;i<MAXORTH;i++) {
		if( ! orthtab[i][0] ) break;
		trimstem(orthtab[i],trimn);
		printf(":%s:%s\t%s%s%s orth\n\n",etag, orthtab[i], stype, glab, nlab );
	}
	putchar('\n');
	strcpy(curstem,tmp);
}

dump_form(char *p)
{
	char gendlab[BUFSIZ], numlab[BUFSIZ];
	char * t;

	strcpy(curpat,yytext);
	numlab[0] = 0;
	

	while(p>=yytext) {
		if(*p=='>') {
			p++;
			break;
		}
		p--;
	}

	switch(*p) {
		case 'c':
			strcpy(gendlab," masc fem");
			break;
		case 'm':
			strcpy(gendlab," masc");
			break;
		case 'n':
			strcpy(gendlab," neut");
			break;
		case 'f':
			strcpy(gendlab," fem");
			break;
		default:
			gendlab[0] = 0;
			break;
	}

	t = strchr(curpat,'\t') ;
	if( t ) *t = 0;

	strcpy(curitype,curpat+strlen("<itype>"));
	curitype[strlen(curitype)-strlen("</itype>")]  = 0;


if( is_itype("is","is") )	return( dump_nom('i',"is_is",gendlab,numlab));
if( is_itype("i","i^us") )	return( dump_nom('i',"ius_i",gendlab,numlab));
if( is_itype("i","ius") )	return( dump_nom('i',"ius_i",gendlab,numlab));
if( is_itype("i","us") )	return( dump_nom('u',"us_i",gendlab,numlab));
if( is_itype("i","os") )	return( dump_nom('o',"os_i",gendlab,numlab));
if( is_itype("i","um") )	return( dump_nom('u',"us_i",gendlab,numlab));
if( is_itype("um","es") )	return( dump_nom('e',"0_is",gendlab," pl"));
if( is_itype("um","a") )	return( dump_nom('a',"0_is",gendlab," pl"));
if( is_itype("i","on") )	return( dump_nom('o',"os_i",gendlab,numlab));
if( is_itype("i","er") )	return( dump_nom('e',"er_i",gendlab,numlab));
if( is_itype("ei","eus") )	return( dump_nom('e',"eus_ei",gendlab,numlab));
if( is_itype("vi^ri","ir") )	return( dump_nom(-1,"0_i",gendlab,numlab));
if( is_itype("e^i","eus") )	return( dump_nom('e',"eus_ei",gendlab,numlab));

if( is_itype("y^os","ys") )	return( dump_nom(0,"ys_yos",gendlab,numlab));
if( is_itype("o_nis","o") )	return( dump_nom(0,"o_oLnis",gendlab,numlab));
if( is_itype("o_nis","on") )	return( dump_nom(0,"oLn_oLnis",gendlab,numlab));
if( is_itype("o^nis","on") )	return( dump_nom(0,"oLn_onis",gendlab,numlab));
if( is_itype("o_ris","or") )	return( dump_nom(0,"or_oLris",gendlab,numlab));
if( is_itype("o^ris","or") )	return( dump_nom(0,"or_oris",gendlab,numlab));
if( is_itype("a^ris","ar") )	return( dump_nom(-1,"0_is",gendlab,numlab));
if( is_itype("u^ris","ur") )	return( dump_nom(-1,"0_is",gendlab,numlab));
if( is_itype("o^ris","or") )	return( dump_nom(-1,"0_is",gendlab,numlab));
if( is_itype("o^ris","us") )	return( dump_nom('u',"us_oris"," neut",numlab));
if( is_itype("oris","or") )	return( dump_nom(0,"or_oris",gendlab,numlab));
if( is_itype("e_dis","es") )	return( dump_nom('e',"es_eLdis",gendlab,numlab));
if( is_itype("y^dis","ys") )	return( dump_nom('s',"s_dis",gendlab,numlab));
if( is_itype("pe^dis","pes") )	return( dump_nom('p',"peLs_pedis",gendlab,numlab));

if( is_itype("e_s","e") ) return( dump_nom(0,"e_es",gendlab,numlab));
if( is_itype("es","e") ) return( dump_nom(0,"e_es",gendlab,numlab));
/*
if( is_itype("i^dis","is") )	return( dump_nom('s',"s_dis",gendlab,numlab));
*/
if( is_itype("i^dis","is") ) return( dump_nom(0,"is_idis",gendlab,numlab));
if( is_itype("i_cis","ix") ) return( dump_nom(0,"ix_iLcis",gendlab,numlab));
if( is_itype("i^cis","ix") ) return( dump_nom(0,"ix_icis",gendlab,numlab));
if( is_itype("i^cis","ex") ) return( dump_nom('e',"ex_icis",gendlab,numlab));
if( is_itype("e^o_s","eus") ) return( dump_nom('e',"eus_ei",gendlab,numlab));
if( is_itype("e^o_s","is") ) return( dump_nom('i',"is_eos",gendlab,numlab));
if( is_itype("e^os","eus") ) return( dump_nom('e',"eus_ei",gendlab,numlab));
if( is_itype("e^os","is") ) return( dump_nom('i',"is_eos",gendlab,numlab));
if( is_itype("e^os","os") ) return( dump_nom('o',"is_eos",gendlab,numlab));
if( is_itype("a^cis","ax") ) return( dump_nom('x',"x_cis",gendlab,numlab));
if( is_itype("e^ris","us") ) return( dump_nom('u',"us_eris",gendlab,numlab));
if( is_itype("e^ris","is") ) return( dump_nom('i',"is_eris",gendlab,numlab));
if( is_itype("e^ris","er") ) return( dump_nom('e',"er_eris",gendlab,numlab));
if( is_itype("e_ris","er") ) return( dump_nom('e',"eLr_eLis",gendlab,numlab));
if( is_itype("a_ris","ar") ) return( dump_nom(-1,"0_is",gendlab,numlab));
if( is_itype("a_lis","al") ) return( dump_nom(-1,"0_is",gendlab,numlab));
if( is_itype("e_nis","al") ) return( dump_nom(-1,"0_is",gendlab,numlab));
if( is_itype("o^pis","ps") ) return( dump_nom('s',"s_is",gendlab,numlab));
if( is_itype("actis","ax") ) return( dump_nom('x',"x_ctis",gendlab,numlab));
if( is_itype("noctis","ox") ) return( dump_nom('x',"x_ctis",gendlab,numlab));
if( is_itype("o_is","os") ) return( dump_nom('o',"os_ois",gendlab,numlab));

if( is_itype("o_rum","i") ) return( dump_nom('i',"us_i",gendlab," pl"));
if( is_itype("o_rum","a") ) return( dump_nom('a',"us_i",gendlab," pl"));
if( is_itype("a_rum","ae") ) return( dump_nom('a',"a_ae",gendlab," pl"));
if( is_itype("arum","ae") ) return( dump_nom('a',"a_ae",gendlab," pl"));

if( is_itype("is","es") ) return( dump_adj('e',"es_is",gendlab,""));
if( is_itype("u_s","us") ) return( dump_nom(0,"us_us",gendlab,""));
if( is_itype("u_s","u") ) return( dump_nom(0,"us_us"," neut",""));
if( is_itype("u_s","o") ) return( dump_nom('o',"o_us",gendlab,""));
if( is_itype("a_tis","tas") ) return( dump_nom('t',"tas_tatis",gendlab,""));
if( is_itype("u_tis","us") ) return( dump_nom('s',"s_tis",gendlab,""));
if( is_itype("o_tis","os") ) return( dump_nom('s',"s_tis",gendlab,""));
if( is_itype("i^nis","o") ) return( dump_nom('o',"o_inis",gendlab,""));
if( is_itype("i^nis","is") ) return( dump_nom('s',"s_nis",gendlab,""));
if( is_itype("i^nis","men") ) return( dump_nom('m',"men_minis",gendlab,""));
if( is_itype("is","es") ) return( dump_nom('e',"es_is",gendlab,""));
if( is_itype("is","e") ) return( dump_nom('e',"is_is",gendlab,""));
if( is_itype("i^um","es") ) return( dump_nom('e',"is_is",gendlab," pl"));
if( is_itype("i^um","ia") ) return( dump_nom('i',"is_is",gendlab," pl"));
if( is_itype("i^um","a") ) return( dump_nom('a',"is_is",gendlab," pl"));
if( is_itype("ium","es") ) return( dump_nom('e',"is_is",gendlab," pl"));
if( is_itype("ium","ia") ) return( dump_nom('i',"is_is",gendlab," pl"));
if( is_itype("ium","a") ) return( dump_nom('a',"is_is",gendlab," pl"));
if( is_itype("a^tis","ma") ) return( dump_nom('m',"ma_matis",gendlab,""));
if( is_itype("e_tis","es") ) return( dump_nom('e',"es_eLtis",gendlab,""));
if( is_itype("e^tis","es") ) return( dump_nom('s',"s_tis",gendlab,""));
if( is_itype("e_i","es") ) return( dump_nom('e',"es_ei",gendlab,""));
if( is_itype("antis","as") ) return( dump_nom('a',"as_antis",gendlab,""));
if( is_itype("ontis","on") ) return( dump_nom('o',"on_ontis",gendlab,""));
if( is_itype("ntis","on") ) return( dump_nom('o',"on_ontis",gendlab,""));
if( is_itype("i^tis","es") ) return( dump_nom('e',"es_itis",gendlab,""));
if( is_itype("entis","ens") ) return( dump_nom('e',"ens_entis",gendlab,""));
if( is_itype("untis","uns") ) return( dump_nom('e',"uns_untis",gendlab,""));

if( is_itype("ii","us") ) return( dump_nom(0,"ius_i",gendlab,""));
if( is_itype("i^i","us") ) return( dump_nom(0,"ius_i",gendlab,""));
if( is_itype("ii","um") ) return( dump_nom(0,"ius_i",gendlab,""));
if( is_itype("ii","on") ) return( dump_nom(0,"ios_i",gendlab,""));
if( is_itype("i^i","on") ) return( dump_nom(0,"ios_i",gendlab,""));
if( is_itype("i^i","um") ) return( dump_nom(0,"ius_i",gendlab,""));

if( is_itype("ae","a") )	return( dump_nom(0,"a_ae",gendlab,numlab));
if( is_itype("ae","e") )	return( dump_nom('e',"a_ae",gendlab,numlab));
if( is_itype("ae","as") ) return( dump_nom('a',"as_ae",gendlab,numlab));
if( is_itype("ae","es") ) return( dump_nom('e',"es_ae",gendlab,numlab));
if( is_itype("a^dis","as") ) return( dump_nom('a',"as_adis",gendlab,numlab));
if( is_itype("tri","er") ) return( dump_nom('e',"er_ri",gendlab,numlab));
if( is_itype("bris","er") ) return( dump_nom('e',"er_ris",gendlab,numlab));
if( is_itype("pri","er") ) return( dump_nom('e',"er_ri",gendlab,numlab));
if( is_itype("bri","er") ) return( dump_nom('e',"er_ri",gendlab,numlab));
if( is_itype("vi^ri","er") ) return( dump_nom(-1,"0_i",gendlab,numlab));
if( is_itype("be^ri","er") ) return( dump_nom('e',"er_ri",gendlab,numlab));
if( is_itype("e^ri","er") ) return( dump_nom('e',"er_ri",gendlab,numlab));
if( is_itype("u_ris","us") ) return( dump_nom('u',"uLs_uLris",gendlab,numlab));
if( is_itype("tis","s") ) return( dump_nom('s',"s_tis",gendlab,numlab));
if( is_itype("untis","us") ) return( dump_nom('u',"us_untis",gendlab,numlab));
if( is_itype("antis","as") ) return( dump_nom('a',"as_antis",gendlab,numlab));
if( is_itype("dri","er") ) return( dump_nom('e',"er_ri",gendlab,numlab));
if( is_itype("i^inis","men") ) return( dump_nom('m',"men_minis",gendlab,numlab));


ECHO;
}

is_itype(unsigned char *s,unsigned char *ends)
{
	int n;

	if( strcmp(s,curitype)) return(0);

	if( ! * ends ) return(1);

	return(! (strcmp(ends,stemnoacc+strlen(stemnoacc)-strlen(ends))) );
}

dump_form2(int n)
{
	strcpy(curitype,yytext+n);
	curitype[strlen(curitype)-(n+1)]  = 0;

	if( is_itype("y^os","ys") )	return( dump_nom(0,"ys_yos"," masc",""));
	if( is_itype("i^nis","is") ) return( dump_nom('s',"s_nis"," masc",""));
if( is_itype("a, um","i^us") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a, um","ius") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a","i^us") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a","ius") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a","us") )	return( dump_adj('u',"us_a_um","",""));
if( is_itype("ci^pi^tis","eps") )	return( dump_adj('e',"eps_ipitis"," masc fem neut",""));
	if( is_itype("a, um","us") )	return( dump_adj('u',"us_a_um","",""));
	if( is_itype("a_cis","ax") )	return( dump_adj('a',"ax_adj","",""));
	if( is_itype("i_cis","ix") )	return( dump_adj('i',"ix_adj","",""));
	if( is_itype("o_cis","ox") )	return( dump_adj('o',"ox_adj","",""));
	if( is_itype("o^pis","ps") )	return( dump_adj('s',"s_e","",""));
	if( is_itype("u^ris","ur") )	return( dump_adj(-1,"0_is"," masc",""));
	if( is_itype("e","is") )	return( dump_adj('i',"is_e","",""));
	if( is_itype("is","is") )	return( dump_adj('i',"is_e","",""));
	if( is_itype("tra, trum","ter") )	return( dump_adj('e',"er_ra_rum","",""));
	if( is_itype("chra, chrum","er") )	return( dump_adj('e',"er_ra_rum","",""));

	if( is_itype("a^dis","as") ) return( dump_nom('a',"as_adis"," fem",""));
	if( is_itype("vi^ri","ir") ) return( dump_nom(-1,"0_i"," masc",""));
	if( is_itype("i^nis","men") ) return( dump_nom('m',"men_minis"," neut",""));
	if( is_itype("a_rum","ae") ) return( dump_nom('a',"a_ae"," fem"," pl"));
	if( is_itype("dri","er") ) return( dump_nom('e',"er_ri"," masc",""));
	if( is_itype("i^tis","es") ) return( dump_nom('e',"es_itis"," masc fem",""));
	if( is_itype("a_tis","as") ) return( dump_nom('t',"tas_tatis"," fem",""));
	if( is_itype("e^tis","es") ) return( dump_nom('s',"s_tis"," masc fem",""));
	if( is_itype("e_tis","es") ) return( dump_nom('e',"es_eLtis"," masc",""));
	if( is_itype("antis","as") ) return( dump_nom('a',"as_antis"," masc",""));
	if( is_itype("untis","us") ) return( dump_nom('u',"us_untis"," fem",""));
if( is_itype("o^ris","or") )	return( dump_nom(-1,"0_is"," masc",""));
if( is_itype("o^ris","us") )	return( dump_nom('u',"us_oris"," neut",""));

	if( is_itype("o_rum","i") ) return( dump_nom('i',"us_i"," masc"," pl"));
	if( is_itype("o_rum","a") ) return( dump_nom('a',"us_i"," neut"," pl"));
	if( is_itype("ae","a") )	return( dump_nom('a',"a_ae"," fem",""));
	if( is_itype("m.","us") )	return( dump_nom('u',"us_i"," masc",""));
	if( is_itype("m.","is") )	return( dump_nom('i',"is_is"," masc",""));
	if( is_itype("i","um") )	return( dump_nom('u',"us_i"," neut",""));
	if( is_itype("ae","es") )	return( dump_nom('e',"es_ae"," masc",""));
	if( is_itype("i^dis","is") )	return( dump_nom('s',"s_dis"," fem",""));
	if( is_itype("y^dis","ys") )	return( dump_nom('s',"s_dis"," fem",""));
	if( is_itype("o_tis","os") ) return( dump_nom('s',"s_tis"," masc fem",""));
	if( is_itype("i^nis","o") )	return( dump_nom('o',"o_inis"," masc",""));
	if( is_itype("adj.","us") )	return( dump_nom('u',"us_a_um"," masc",""));
	if( is_itype("m.","os") )	return( dump_nom('o',"os_i"," masc",""));
	if( is_itype("f.","us") )	return( dump_nom('u',"us_i"," fem",""));
	if( is_itype("f.","os") )	return( dump_nom('o',"os_i"," fem",""));
	if( is_itype("f.","ae") )	return( dump_nom('a',"a_ae"," fem"," pl"));
	if( is_itype("f.","e") )	return( dump_nom('e',"e_es"," fem",""));
	if( is_itype("f.","e") )	return( dump_nom('e',"is_is"," neut",""));
	if( is_itype("f.","ies") )	return( dump_nom('e',"es_eLi"," fem",""));
	if( is_itype("f.","tas") )	return( dump_nom('t',"tas_tatis"," fem",""));
	if( is_itype("f.","x") )	return( dump_nom('x',"x_cis"," fem",""));
	if( is_itype("m.","x") )	return( dump_nom('x',"x_cis"," masc",""));
	if( is_itype("f.","io") )	return( dump_nom('o',"o_oLnis"," fem",""));
	if( is_itype("f.","o") )	return( dump_nom('o',"o_us"," fem",""));
	if( is_itype("f.","a") )	return( dump_nom('a',"a_ae"," fem",""));
	if( is_itype("f.","is") )	return( dump_nom('i',"is_is"," fem",""));
	if( is_itype("f.","ae") )	return( dump_nom('a',"a_ae"," fem"," pl"));
	if( is_itype("e_dis","es") )	return( dump_nom('e',"es_eLdis"," masc fem",""));
	if( is_itype("m.","is") )	return( dump_nom('u',"is_is"," masc",""));
	if( is_itype("n.","a") )	return( dump_nom('a',"us_i"," neut"," pl"));
	if( is_itype("n.","men") )	return( dump_nom('m',"men_minis"," neut",""));
	if( is_itype("n.","um") )	return( dump_nom('u',"us_i"," neut",""));
	if( is_itype("n.","on") )	return( dump_nom('o',"os_i"," neut",""));

	ECHO;
}

dump_adj1(int n)
{
	char * t;

	strcpy(curpat,yytext);
	t = strchr(curpat,'\t');
	if(t) *t = 0;

	strcpy(curitype,curpat+n);
	curitype[strlen(curitype)-(n+1)]  = 0;


if( is_itype("a, um","i^us") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a, um","ius") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a","i^us") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a","ius") )	return( dump_adj('i',"ius_ia_ium","",""));
if( is_itype("a","us") )	return( dump_adj('u',"us_a_um","",""));
if( is_itype("o^ris","or") )	return( dump_adj(-1,"0_adj3","",""));
if( is_itype("i^cis","ex") )	return( dump_adj('e',"ex_icis_adj","",""));
	if( is_itype("a, um","us") )	return( dump_adj('u',"us_a_um","",""));
	if( is_itype("fe^ra, fe^rum","er") )	return( dump_adj('e',"er_era_erum","",""));
	if( is_itype("tris, e","er") )	return( dump_adj('e',"er_ris_re","",""));
	if( is_itype("ci^pi^tis","eps") )	return( dump_adj('e',"eps_ipitis"," masc fem neut",""));
	if( is_itype("pe^dis","pes") )	return( dump_adj('p',"peLs_pedis_adj","",""));
	if( is_itype("te^ra, te^rum","er") )	return( dump_adj('e',"er_era_erum","",""));
	if( is_itype("tra, trum","er") )	return( dump_adj('e',"er_ra_rum","",""));
	if( is_itype("chra, chrum","er") )	return( dump_adj('e',"er_ra_rum","",""));
	if( is_itype("gra, grum","er") )	return( dump_adj('e',"er_ra_rum","",""));
	if( is_itype("noctis","ox") ) return( dump_adj('x',"x_ctis","",""));
	if( is_itype("a_cis","ax") )	return( dump_adj('a',"ax_adj","",""));
	if( is_itype("i_cis","ix") )	return( dump_adj('i',"ix_adj","",""));
	if( is_itype("o_cis","ox") )	return( dump_adj('o',"ox_adj","",""));
	if( is_itype("i^dis","is") )	return( dump_nom('i',"is_idis"," masc fem",""));
	if( is_itype("o^pis","ps") )	return( dump_adj('s',"s_e","",""));
	if( is_itype("is","is") )	return( dump_adj('i',"is_e","",""));
	if( is_itype("e","is") )	return( dump_adj('i',"is_e","",""));
	if( is_itype("entis","ens") )	return( dump_adj('e',"ens_adj","",""));
	if( is_itype("ntis","ens") )	return( dump_adj('e',"ens_adj","",""));
	if( is_itype("e^ra, e^rum","er") )	return( dump_adj('e',"er_era_erum","",""));
	if( is_itype("o_ris","r") )	return( dump_adj(-1,"0_e","",""));

	ECHO;

}
dump_form3(int n)
{
	if( dumped_stem ) {
		ECHO;
		return;
	}


	if( !strcmp("<pos>adv.</pos>",yytext ) ) {
		printf("\n:le:%s\n", curlemma );
		printf(":wd:%s\tadverb\n\n", curstem );
		if( orthtab[0][0] ) 
			printf(":wd:%s\tadverb orth\n\n", orthtab[0] );
		return;
	}


	dump_form2(n);
}

trimstem(unsigned char * curs, int trimn)
{
	int n;
	unsigned char * s;

	if( trimn > 0 ) {
		s = curs;
		while(*s) s++; s--;
		
/*
 * kludge! 7/28/98
 * variation of is and es.
 */
		if(trimn=='e'&&!strcmp((s-1),"is")) {
			*(s-1) = 0; 
			return;
		}
		if(trimn=='o'&&!strcmp((s-1),"us")) {
			*(s-1) = 0; 
			return;
		}
		while(s>=curs && *s != trimn ) {
			s--;
		}
		*s = 0;
	}
}

is_prevborth(char *s)
{
	if( ! strncmp(s,"con",3) || ! strncmp(s,"sub",2) ) {
		if( strlen(s) == 4 ) return(2);
		return(0);
	}

	if( ! strncmp(s,"ad",2) || ! strncmp(s,"in",2) || !strncmp(s,"ob",2)) {
		if( !strcmp(s,"inpr") ) return(1);

		if( !strcmp(s,"inpl") ) return(1);

		if( strlen(s) == 3 ) return(1);

		return(0);
	}

	return(0);
}
