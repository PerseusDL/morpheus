
%%

"<pos>v. a.</pos>\t<orth>"[^<]+"</orth>"	newentr();
"</pos>\t<orth>"[^<]+"</orth>"	newentr();
"</itype>\t<orth>"[^<]+"</orth>"	newentr();
"</gen>\t<orth>"[^<]+"</orth>"	newentr();
"<orth>"[^<]+"or</orth>\t<itype>a_ri<"	newentr2();

%%

newentr2()
{
	char * s = yytext;
	
	putchar('\n');
	while(*s!='>' && *s) s++; 
	if(*s) s++;
	while(*s!='<') putchar(*s++);
	if(*s == '<') while(*s!='>' && *s) s++;
	if(*s=='>') s++;
	printf("%s", s);
}

newentr()
{
	unsigned char * t;

	t = yytext;

	while(*t&&*t!='\t') putchar(*t++);
	if(*t) t++;
	putchar('\n');

	while(*t&&*t!='>') t++;
	if(*t) t++;

	while(*t&&*t!='<') putchar(*t++);
}
