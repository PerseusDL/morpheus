
%%

.+"care"$	sawvb("care_vb",4);
.+"gare"$	sawvb("gare_vb",4);
.+"ciare"$	sawvb("ciare_vb",5);
.+"giare"$	sawvb("giare_vb",5);
.+"are"$	sawvb("are_vb",3);
.+"ere"$	sawvb("ere_vb",3);
.+"ire"$	sawvb("ire_vb",3);

.+"o"$	sawnom("no","o_i masc",1);
.+"a"$	sawnom("no","a_e fem",1);
.+"mente"	sawnom("wd","adverb",0);
.+"e"$	sawnom("no","e_i masc",1);
. |
\n	;


%%

int doverb = 1;
sawvb(char *suff, int n)
{
	if( ! doverb ) return;

	printf("\n:le:%s\n", yytext );
	yytext[yyleng-n] = 0;

	printf(":de:%s %s\n", yytext, suff);
}

sawnom(char * pref, char * suff, int n)
{

	if( doverb ) return;

	printf("\n:le:%s\n", yytext );
	yytext[yyleng-n] = 0;
	printf(":%s:%s\t%s\n", pref, yytext, suff);
}

main(int argc, char * argv[])
{
	if( !strcmp(argv[1] ,"noun") ) doverb = 0;
	yylex();
}
