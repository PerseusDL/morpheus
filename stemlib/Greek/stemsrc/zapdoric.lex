
%%

[rei][ ]+"h_hs".+"doric" zapdor();
[rei][ ]+"hs_ou".+"doric" zapdor();
%%

zapdor()
{
	yytext[yyleng-strlen("doric")] = 0;
	printf("%s", yytext);
}
