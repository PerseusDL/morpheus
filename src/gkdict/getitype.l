

%%

"<itype>"[^<]+"</itype>\t<gen>"[^<]+"</gen>"	printf("%s\n", yytext );
"<gen>"[^<]+"</gen>"	printf("%s\n", yytext );

.	;
\n	;

%%
