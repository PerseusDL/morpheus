char * is_common();

main()
{
	char line[128];
	char * p;

	while(gets(line))  {
		p=is_common(line);
		if(p) printf("got [%s]\n", p );
		else printf("failed on [%s]\n", line );
	}
}
