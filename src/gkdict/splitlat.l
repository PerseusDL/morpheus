
%%

"<pos>v. a.</pos>\t<orth>"[^<]+"</orth>"	newentr();
"</pos>\t<orth>"[^<]+"</orth>"	newentr();
"</itype>\t<orth>"[^<]+"</orth>"	newentr();
"</gen>\t<orth>"[^<]+"</orth>"	newentr();

%%

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
