
%%


"esco"\t+"<itype>e_vi, e_tum</itype>"	printf("esco\t\t<itype>e_vi, e_tum, 3</itype>");
"<itype>cu_tus</itype>"			printf("<itype>cu_tus, 3</itype>");
"<itype>e_vi, e_tum</itype>"		printf("<itype>e_vi, e_tum, 2</itype>");
"<itype>fe_ci, fa^ce^re</itype>"	printf("<itype>fe_ci, factum, 3</itype>");
"<itype>i_vi or i^i,"			printf("<itype>i_vi, or i^i,");
"<itype>i_vi and ii,"			printf("<itype>i_vi, or i^i,");
"<itype>i_vi and i^i,"			printf("<itype>i_vi, or i^i,");
"<itype>i_vi or"			printf("<itype>i_vi, or");
"<itype>i_vi or ii,"			printf("<itype>i_vi, or i^i,");
" i_re</itype>"				printf(" 4</itype>");
"<itype>i_vi, or i^i,"			printf("<itype>i_vi, or i^i,");
"<itype>i^i or i_vi,"			printf("<itype>i_vi, or i^i,");
"<itype>a_vi, a_re</itype>"		printf("<itype>a_re</itype>");
"<itype>i_re, 4</itype>"		printf("<itype>i_re</itype>");
"<itype>4</itype>"			printf("<itype>i_re</itype>");
"<itype>ce^re</itype>"			printf("<itype>e^re</itype>");
" e^re</itype>"				printf(" 3</itype>");
"<itype>e^re, 3</itype>"		printf("<itype>e^re</itype>");
"<itype>e_re, 2</itype>"		printf("<itype>e_re</itype>");
" e_re</itype>"				printf(" 2</itype>");
"<itype>3</itype>"			printf("<itype>e^re</itype>");
"<itype>1</itype>"			printf("<itype>a_re</itype>");
"<itype>2</itype>"			printf("<itype>e_re</itype>");
"<itype>i^i, i^tum, i_re</itype>"	printf("<itype>i^i, i^tum, 4</itype>");
"<itype>a_vi, a_tum, a_re</itype>" 			printf("<itype>a_re</itype>");
"<itype>a_re</itype>" 			printf("<itype>a_re</itype>");
"<itype>a_re,"[ ]+"1</itype>" 		printf("<itype>a_re</itype>");
"<itype>a_tum,"[ ]+"1</itype>" 		printf("<itype>a_re</itype>");
"<itype>a_vi,"[ ]+"1</itype>" 		printf("<itype>a_re</itype>");
"<itype>a_vi,"[ ]+"a_tum,"[ ]+"1</itype>" printf("<itype>a_re</itype>");
"<itype>a_vi,"[ ]+"a_tum</itype>" 	printf("<itype>a_re</itype>");
"<itype>a_tus,"[ ]+"1</itype>"   	printf("<itype>a_re</itype>");

"<itype>a_tus sum, 1</itype>"		printf("<itype>a_ri</itype>");
"<itype>a_ri,"[ ]+"1</itype>" 		printf("<itype>a_ri</itype>");
"<itype>a_ri,"[ ]+"a_tus,"[ ]+"1</itype>" printf("<itype>a_ri</itype>");
"<itype>a_tus</itype>"			 printf("<itype>a_ri</itype>");
"<itype>a_ri</itype>"			 printf("<itype>a_ri</itype>");

%%

#include <string.h>

char orthstem[BUFSIZ];

unsigned char stem[BUFSIZ], lemma[BUFSIZ];

set_lemma()
{
	unsigned char *t;

	orthstem[0] = 0;
	strcpy(lemma,yytext);

	t = lemma;

	while(*t&&!isspace(*t)) t++;
	*t = 0;

	strcpy(stem,lemma);

	t = lemma;
	while(*t) {
		if( !isalpha(*t)) {
			strcpy(t,t+1);
			continue;
		}
		t++;
	}

	t = stem;
	while(*t&&*t!='#') t++;
	*t = 0;
	
	t = stem+strlen(stem) - 3;
	if( ! strcmp(t,"ior") || ! strcmp(t,"eor") ) {
		*t = 0;
	} else if( ! strcmp(++t,"or") || ! strcmp(t,"eo") || ! strcmp(t,"io") ) {
		*t = 0;
	} else *++t = 0;
}
/*

*/


doderiv(char * tag,int trimn)
{
	unsigned char *t;


	if( orthstem[0] ) printf("\north: [%s] [%s]\n", stem, orthstem);
	orthstem[0] = 0;
	printf("\n:le:%s\n", lemma );
	printf(":de:%s\t%s\n", stem, tag );
}

set_orth()
{
	unsigned char * t = yytext + 6;
	unsigned char * p = orthstem;
	ECHO;

	strcpy(orthstem,stem);

	while(*t && *t !='<') {
		if(!isalpha(*p) ) {
			p++;
			continue;
		}
		if(!isalpha(*t) ) {
			t++;
			continue;
		}
		*p++ = *t++;
	}
printf("\nstem:[%s] + [%s] = [%s]\n", stem , yytext+6, orthstem );
}

doverb(char * vtag, int trimn )
{

	printf("\n:le:%s\n", lemma );
	printf(":vs:%s\t%s\n", stem, vtag );
}
