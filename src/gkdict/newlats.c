#include <gkstring.h>

int do_simpnom(char *, char*);
int dump_nom(char *stem,int trunc, char * tags);
int probe_fem(char *);
int do_regnom(char*stem,char*key1,char*key2,char*key3);
int dump_entry(char *stem,int trunc, char * tags,char * etag,FILE *);
FILE * fverbs;
char numsuff[BUFSIZ];

main()
{
	char line[BUFSIZ];
	char savel[BUFSIZ];
	char curw[BUFSIZ];
	char firstkey[BUFSIZ];
	char seckey[BUFSIZ];
	char thrdkey[BUFSIZ];
	char *s;
	int rval = 0;

	if( ! (fverbs=fopen("/tmp/ls.vbs","w"))) {
		fprintf(stderr,"could not open /tmp/ls.vbs!\n");
		exit(-1);
	}

	while(gets(line)) {
		if( ! line[0]) continue;
		if( ! isdigit(line[0])) continue;

		strcpy(savel,line);
		firstkey[0] = seckey[0] = thrdkey[0] = 0;
		/* skip tokens 1 and 3, but keep #2 */
		s = strtok(line," \t");
		s = strtok((char * )NULL," \t");
		strcpy(curw,s);

		numsuff[0] = 0;
		s = curw;
		while(*s&&*s!='#') s++;
		if(*s=='#') {
			strcpy(numsuff,s);
			*s = 0;
		}

		if( is_verb(curw) ) continue;
		s=strtok((char * )NULL," \t");
		s=strtok((char * )NULL," \t");
		if(s) strcpy(firstkey,s);
		s=strtok((char * )NULL," \t");
		if(s) strcpy(seckey,s);
		s=strtok((char * )NULL," \t");
		if(s) strcpy(thrdkey,s);

		if( ! strncmp(firstkey,"<gen",4)) {
		/*	printf("%s %s\n", curw , firstkey );*/
			if( ! do_simpnom(curw,firstkey) ) {
				printf("0:%s\n", savel );
			}
			continue;
		}

		if( ! strncmp(firstkey,"<itype>",7)) {
			if( ! do_regnom(curw,firstkey,seckey,thrdkey) ) {
				printf("0:%s\n", savel );
			}
			continue;
		}
		if( is_adverb(curw,firstkey) ) continue;
		if( is_teos(curw) ) continue;
		printf("0:%s\n", savel );
	}
	fclose(fverbs);
}

do_simpnom(char* stem,char* gend)
{


	if( !strcmp(stem+strlen(stem)-3,"i^o") 
		&& !strcmp(gend,"<gen>f.</gen>")) {
		dump_nom(stem,1,"o_onis fem");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-2,"a") 
		&& !strcmp(gend,"<gen>f.</gen>")) {
		dump_nom(stem,2,"a_ae fem");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-2,"us") 
		&& !strcmp(gend,"<gen>m.</gen>")) {
		dump_nom(stem,2,"us_i masc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-2,"is") 
		&& !strcmp(gend,"<gen>f.</gen>")) {
		dump_nom(stem,2,"is_is fem");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"i^o") 
		&& !strcmp(gend,"<gen>f.</gen>")) {
		dump_nom(stem,1,"o_onis fem");
		return(1);
	}

	return(0);
	if( !strcmp(stem+strlen(stem)-4,"i/+a") ) {
		dump_nom(stem,3,"h_hs fem");
		return(1);
	}

	if( (!strcmp((stem+strlen(stem)-1),"a") ||
	     !strcmp((stem+strlen(stem)-1),"h"))
		&& !strcmp(gend,"<gen>h(</gen>")) {
		probe_fem(stem);
		return(1);
	}

	if( (!strcmp(stem+strlen(stem)-2,"h/") ||
	     !strcmp(stem+strlen(stem)-2,"a/") ) 
		&& !strcmp(gend,"<gen>h(</gen>")) {
		dump_nom(stem,2,"h_hs fem suff_acc");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-1,"c") 
		&& !strcmp(gend,"<gen>h(</gen>")) {
		dump_nom(stem,1,"c_kos fem");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-2,"ma") 
		&& !strcmp(gend,"<gen>to/</gen>")) {
		dump_nom(stem,2,"ma_matos neut");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-2,"a/") 
		&& !strcmp(gend,"<gen>ta/</gen>")) {
		dump_nom(stem,2,"os_ou neut pl");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-4,"mata") 
		&& !strcmp(gend,"<gen>ta/</gen>")) {
		dump_nom(stem,4,"ma_matos neut pl");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-5,"i/des") 
		&& !strcmp(gend,"<gen>ai(</gen>")) {
		dump_nom(stem,5,"is_idos fem pl suff_acc");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-3,"a/s") 
		&& !strcmp(gend,"<gen>h(</gen>")) {
		dump_nom(stem,2,"s_dos fem stem_acc");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-5,"a/des") 
		&& !strcmp(gend,"<gen>ai(</gen>")) {
		dump_nom(stem,4,"s_dos fem pl stem_acc");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-3,"sis") 
		|| !strcmp(stem+strlen(stem)-3,"cis")
		|| !strcmp(stem+strlen(stem)-3,"yis") ) {
		dump_nom(stem,2,"is_ews fem");
		return(1);
	}
	
	if( !strcmp(stem+strlen(stem)-4,"pais") 
		&& !strcmp(gend,"<gen>o(</gen>")) {
		dump_nom(stem,4,"pais_paidos masc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"qric") 
		&& !strcmp(gend,"<gen>o(</gen>")) {
		dump_nom(stem,4,"qric_trixos masc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"pous") 
		&& !strcmp(gend,"<gen>o(</gen>")) {
		dump_nom(stem,4,"pous_podos masc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-5,"podes") 
		&& !strcmp(gend,"<gen>oi(</gen>")) {
		dump_nom(stem,5,"pous_podos masc pl");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"ai/") 
		&& !strcmp(gend,"<gen>ai(</gen>")) {
		dump_nom(stem,3,"h_hs fem pl suff_acc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"h/s") 
		&& !strcmp(gend,"<gen>o(</gen>")) {
		dump_nom(stem,3,"hs_ou masc suff_acc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-2,"w/") 
		&& !strcmp(gend,"<gen>h(</gen>")) {
		dump_nom(stem,2,"w_oos fem suff_acc");
		return(1);
	}

	if(!strcmp(stem+strlen(stem)-3,"o/s") ||
		!strcmp(stem+strlen(stem)-3,"o/n"))  {
		char curg[BUFSIZ], tmptags[BUFSIZ];

		if(!strcmp(gend,"<gen>h(</gen>")) strcpy(curg,"fem");
		if(!strcmp(gend,"<gen>to/</gen>")) strcpy(curg,"neut");
		else strcpy(curg,"masc");

		sprintf(tmptags,"os_ou suff_acc %s", curg );
		dump_nom(stem,3,tmptags);
		return(1);
	}

	if( (!strcmp(stem+strlen(stem)-2,"oi") || 
		!strcmp(stem+strlen(stem)-3,"oi/"))
		&& !strcmp(gend,"<gen>oi(</gen>")) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		strcpy(tmptags,"os_ou masc pl");
		checkaccent(stem,&syllno,&curacc);
		if( syllno == ULTIMA ) {
			strcat(tmptags," suff_acc");
		} else if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		if( *(stem+strlen(stem)-1) == '/')
			dump_nom(stem,3,tmptags);
		else
			dump_nom(stem,2,tmptags);
		return(1);
	}

	if( (!strcmp(stem+strlen(stem)-2,"ai") || 
		!strcmp(stem+strlen(stem)-3,"ai/"))
		&& !strcmp(gend,"<gen>oi(</gen>")) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		strcpy(tmptags,"hs_ou masc pl");
		checkaccent(stem,&syllno,&curacc);
		if( syllno == ULTIMA ) {
			strcat(tmptags," suff_acc");
		} else if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		if( *(stem+strlen(stem)-1) == '/')
			dump_nom(stem,3,tmptags);
		else
			dump_nom(stem,2,tmptags);
		return(1);
	}

	if( (!strcmp(stem+strlen(stem)-2,"hs")  ||
	     !strcmp(stem+strlen(stem)-2,"as"))
		&& !strcmp(gend,"<gen>o(</gen>")) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		strcpy(curg,"masc");
		
		sprintf(tmptags,"hs_ou %s", curg );
		checkaccent(stem,&syllno,&curacc);
		if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		dump_nom(stem,2,tmptags);
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-1,"a")  
		&& !strcmp(gend,"<gen>ta/</gen>") ) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		strcpy(tmptags,"os_ou neut pl");
		checkaccent(stem,&syllno,&curacc);
		if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		dump_nom(stem,1,tmptags);
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-2,"os")  
		&& !strcmp(gend,"<gen>to/</gen>") ) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		strcpy(tmptags,"hs_eos neut");
		checkaccent(stem,&syllno,&curacc);
		if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		dump_nom(stem,2,tmptags);
		return(1);
	}

	if( (!strcmp(stem+strlen(stem)-2,"on")  ||
	     !strcmp(stem+strlen(stem)-2,"o/n"))
		&& !strcmp(gend,"<gen>to/</gen>") ) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		strcpy(tmptags,"os_ou neut");
		checkaccent(stem,&syllno,&curacc);
		if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		dump_nom(stem,2,tmptags);
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-2,"os") 
		&& (!strcmp(gend,"<gen>h(</gen>") ||
			!strcmp(gend,"<gen>o(</gen>"))) {
		int syllno, curacc;
		char curg[BUFSIZ], tmptags[BUFSIZ];

		if(!strcmp(gend,"<gen>h(</gen>")) strcpy(curg,"fem");
		else strcpy(curg,"masc");
		
		sprintf(tmptags,"os_ou %s", curg );
		checkaccent(stem,&syllno,&curacc);
		if( nsylls(stem)>2 && syllno == PENULT ) {
			strcat(tmptags, " stem_acc");
		}
		dump_nom(stem,2,tmptags);
		return(1);
	}

	return(0);
}

void circ2long(char*s)
{
	while(*s) {
	 if( !strncmp("oi=",s,3) || !strncmp("ai=",s,3) || !strncmp("ei=",s,3)
	  || !strncmp("ou=",s,3) || !strncmp("au=",s,3) || !strncmp("eu=",s,3)) {
			s+= 3; 
			continue;
		}
		if((*s=='a'||*s=='i'||*s=='u') && *(s+1) == CIRCUMFLEX)
			*(s+1) = HARDLONG;
		s++;
	}
}

int dump_adj(char *stem,int trunc, char * tags)
{

	return(dump_entry(stem,trunc,tags,":aj:",stdout));
}

int dump_nom(char *stem,int trunc, char * tags)
{

	return(dump_entry(stem,trunc,tags,":no:",stdout));
}

int dump_entry(char *stem,int trunc, char * tags,char * etag, FILE * fout)
{
	char shorts[BUFSIZ];
	strcpy(shorts,stem);
	stripmetachars(stem);
	shorts[strlen(shorts)-trunc] = 0;
	if(shorts[strlen(shorts)-1] == '-')
		shorts[strlen(shorts)-1] = 0;
	/* first -- if you have a circumflex on i,u,a, turn it into a
  	   long mark!
  	*/
	circ2long(shorts);
	stripacc(shorts);
	fprintf(fout,":le:%s%s\n%s%s %s\n\n", stem, numsuff,etag,shorts, tags);
	return(1);
}



char * getaccp(char *, int);
probe_fem(char * stem)
{
	int syllno;
	int curacc;

	/* is it a short alpha? */
		checkaccent(stem,&syllno,&curacc);
		if(syllno == ANTEPENULT)
			dump_nom(stem,1,"a_hs fem");
/*
		else if( syllno == PENULT && curacc == CIRCUMFLEX )
			dump_nom(stem,1,"a_hs fem");
*/
	/* guess not... */
		else dump_nom(stem,1,"h_hs fem");
		return(1);
}

int
do_regnom(char*stem,char*key1,char*key2,char * key3)
{


	if( !strcmp("<itype>o^nis</itype>",key1) && 
	    !strcmp(key2,"<gen>f.</gen>") && 
	   (!strcmp(stem+strlen(stem)-1,"o")) ) {
		dump_nom(stem,1,"o_onis fem");	
		return(1);
	}

	if( !strcmp("<itype>is</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"is")) ) {
		if( !strcmp(key2,"<gen>m.</gen>") ) 
			dump_nom(stem,2,"is_is masc");	
		else
			dump_nom(stem,2,"is_is fem");	
		return(1);
	}

	if( !strcmp("<itype>is</itype>",key1) && 
	  !strcmp(stem+strlen(stem)-1,"e")) {
		dump_nom(stem,1,"is_is neut");	
		return(1);
	}

	if( !strcmp("<itype>i</itype>",key1) && 
	  !strcmp(stem+strlen(stem)-3,"ium")) {
		dump_nom(stem,2,"us_i neut");	
		return(1);
	}

	if( (!strcmp("<itype>i^i</itype>",key1) ||
	     !strcmp("<itype>ii</itype>",key1))	 && 
	  !strcmp(stem+strlen(stem)-2,"um")) {
		dump_nom(stem,2,"us_i neut");	
		return(1);
	}

	if( (!strcmp("<itype>i^i</itype>",key1) ||
	     !strcmp("<itype>ii</itype>",key1))	 && 
	  !strcmp(stem+strlen(stem)-2,"us")) {
		dump_nom(stem,2,"us_i masc");	
		return(1);
	}


	if( !strcmp("<itype>i</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"os")) ) {
		if( !strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,2,"os_i fem");	
		else
			dump_nom(stem,2,"os_i masc");	
		return(1);
	}

	if( !strcmp("<itype>i</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"o^s")) ) {
	      if( !strcmp(key2,"<gen>f.</gen>") )
		dump_nom(stem,3,"os_i fem");	
	      else
		dump_nom(stem,3,"os_i masc");	
	      return(1);
	}

	if( !strcmp("<itype>antis</itype>",key1) && 
	    !strcmp(key2,"<gen>m.</gen>") && 
	   (!strcmp(stem+strlen(stem)-2,"as")) ) {
		dump_nom(stem,2,"as_antis masc");	
		return(1);
	}

	if( !strcmp("<itype>um</itype>",key1) && 
	    !strcmp(key2,"<gen>m.</gen>") && 
	   (!strcmp(stem+strlen(stem)-2,"es")) ) {
		dump_nom(stem,2,"is_is masc pl");	
		return(1);
	}

	if( !strcmp("<itype>o_ris</itype>",key1) && 
	    !strcmp(key2,"<gen>m.</gen>") && 
	   (!strcmp(stem+strlen(stem)-2,"or")) ) {
		dump_nom(stem,2,"or_oris masc");	
		return(1);
	}

	if( !strcmp("<itype>i_cis</itype>",key1) && 
	    !strcmp(key2,"<gen>f.</gen>") && 
	   (!strcmp(stem+strlen(stem)-1,"x")) ) {
		dump_nom(stem,1,"x_cis fem");	
		return(1);
	}

	if( !strcmp("<itype>ae</itype>",key1) && 
	    !strcmp(key2,"<gen>m.</gen>") && 
	   (!strcmp(stem+strlen(stem)-1,"a")) ) {
		dump_nom(stem,1,"a_ae masc");	
		return(1);
	}

	if( !strcmp("<itype>ae</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"a^")) ) {
	      if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"a_ae masc");	
		else
			dump_nom(stem,2,"a_ae fem");	
		return(1);
	}

	if( !strcmp("<itype>ae</itype>",key1) && 
/*	    !strcmp(key2,"<gen>f.</gen>") && */
	   (!strcmp(stem+strlen(stem)-1,"a")) ) {
		dump_nom(stem,1,"a_ae fem");	
		return(1);
	}


	if( !strcmp("<itype>e_i</itype>",key1) && 
	    !strcmp(key2,"<gen>m.</gen>") && 
	   (!strcmp(stem+strlen(stem)-3,"e_s")) ) {
		dump_nom(stem,3,"es_ei fem");	
		return(1);
	}


	if( !strcmp("<itype>o^nis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"on")) ) {
		    if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"oLn_onis masc");	
		    else
			dump_nom(stem,2,"oLn_onis fem");	
		return(1);
	}

	if( !strcmp("<itype>o^nis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"o_n")) ) {
		    if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,3,"oLn_onis masc");	
		    else
			dump_nom(stem,3,"oLn_onis fem");	
		return(1);
	}

	if( !strcmp("<itype>o_nis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"o_n")) ) {
		    if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,3,"oLn_oLnis masc");	
		    else
			dump_nom(stem,3,"oLn_oLnis fem");	
		return(1);
	}

	if( !strcmp("<itype>o_nis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"on")) ) {
		    if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"oLn_oLnis masc");	
		    else
			dump_nom(stem,2,"oLn_oLnis fem");	
		return(1);
	}

	if( !strcmp("<itype>o_nis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"o_")) ) {
		    if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"o_oLnis masc");	
		    else
			dump_nom(stem,2,"o_oLnis fem");	
		return(1);
	}

	if( !strcmp("<itype>o_nis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-1,"o")) ) {
		    if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,1,"o_oLnis masc");	
		    else
			dump_nom(stem,1,"o_oLnis fem");	
		return(1);
	}

	if( !strcmp("<itype>is</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"es")) ) {
		if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"es_is masc");	
		else
			dump_nom(stem,2,"es_is fem");	
		return(1);
	}

	if( !strcmp("<itype>i^um</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-1,"a")) ) {
		dump_nom(stem,2,"is_is neut pl");	
		return(1);
	}

	if( !strcmp("<itype>i^um</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"es")) ) {
		if( !strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,2,"is_is fem pl");	
		else
			dump_nom(stem,2,"is_is masc pl");	
		return(1);
	}

	if( !strcmp("<itype>is</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"is")) ) {
		if( !strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,2,"is_is fem");	
		else
			dump_nom(stem,2,"is_is masc");	
		return(1);
	}

	if( !strcmp("<itype>ium</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-1,"a")) ) {
		dump_nom(stem,1,"is_is neut pl");	
		return(1);
	}

	if( !strcmp("<itype>ium</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"es")) ) {
		dump_nom(stem,2,"is_is masc pl");	
		return(1);
	}

	if( !strcmp("<itype>u_s</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"us")) ) {
	    	if( !strcmp(key2,"<gen>f.</gen>"))
			dump_nom(stem,2,"us_us fem");	
		else
			dump_nom(stem,2,"us_us masc");	
		return(1);
	}

	if( (!strcmp("<itype>a_rum</itype>",key1) ||
	     !strcmp("<itype>arum</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-2,"ae")) ) {
		if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"a_ae masc pl");	
		else
			dump_nom(stem,2,"a_ae fem pl");	
		return(1);
	}

	if( (!strcmp("<itype>inis</itype>",key1) ||
	     !strcmp("<itype>i^nis</itype>",key1)) && 
	   (!strcmp(stem+strlen(stem)-1,"o")) ) {
		if( ! strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,1,"o_inis masc");	
		else
			dump_nom(stem,1,"o_inis fem");	
		return(1);
	}

	if( (!strcmp("<itype>inis</itype>",key1) ||
	     !strcmp("<itype>i^nis</itype>",key1)) && 
	    !strcmp(key2,"<gen>n.</gen>") && 
	   (!strcmp(stem+strlen(stem)-4,"me^n")) ) {
		dump_nom(stem,4,"men_minis neut");	
		return(1);
	}

	if( (!strcmp("<itype>inis</itype>",key1) ||
	     !strcmp("<itype>i^nis</itype>",key1)) && 
	    !strcmp(key2,"<gen>n.</gen>") && 
	   (!strcmp(stem+strlen(stem)-3,"men")) ) {
		dump_nom(stem,3,"men_minis neut");	
		return(1);
	}

	if( !strcmp("<itype>i_cis</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-2,"ix")))  {

		if( !strcmp(key2,"<gen>m.</gen>")  )
			dump_nom(stem,2,"ix_iLcis masc");	
		else
			dump_nom(stem,2,"ix_iLcis fem");	
		
		return(1);
	}

	if( (!strcmp("<itype>a^dis</itype>",key1) ||
	     !strcmp("<itype>adis</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-2,"as")) ) {
		dump_nom(stem,2,"as_adis fem");	
		return(1);
	}

	if( (!strcmp("<itype>a^dis</itype>",key1) ||
	     !strcmp("<itype>adis</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-3,"a^s")) ) {
		dump_nom(stem,3,"as_adis fem");	
		return(1);
	}

	if( (!strcmp("<itype>a^tis</itype>",key1) ||
	     !strcmp("<itype>atis</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-3,"ma^")) ) {
		dump_nom(stem,3,"ma_matis neut");	
		return(1);
	}

	if( (!strcmp("<itype>a^tis</itype>",key1) ||
	     !strcmp("<itype>atis</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-2,"ma")) ) {
		dump_nom(stem,2,"ma_matis neut");	
		return(1);
	}

	if( (!strcmp("<itype>a_tis</itype>",key1) ||
	     !strcmp("<itype>atis</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-3,"tas")) ) {
		dump_nom(stem,3,"tas_tatis fem");	
		return(1);
	}

	if( (!strcmp("<itype>i^cis</itype>",key1) ||
	     !strcmp("<itype>icis</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-2,"ix")) ) {

		if( !strcmp(key2,"<gen>m.</gen>")  )
			dump_nom(stem,2,"ix_icis masc");	
		else
			dump_nom(stem,2,"ix_icis fem");	
		
		return(1);
	}


	if( !strcmp("<itype>a_cis</itype>",key1) ) {
		if( !strcmp("<pos>adj.</pos>",key2) ) 
			dump_adj(stem,2,"ax_adj");	
		if( !strcmp("<gen>m.</gen>",key2) ) 
			dump_nom(stem,2,"x_cis masc");	
		
		return(1);

	}

	if( !strcmp("<itype>fe^ra,",key1) ) {
		dump_adj(stem,0,"0_a_um");	
		return(1);
	}

	if( !strcmp("<itype>e^ra,",key1) ) {
		dump_adj(stem,0,"0_a_um");	
		return(1);
	}

	if( !strcmp("<itype>antis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"ans")) ) {
	       if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,3,"ans_antis masc");	
		else if( !strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,3,"ans_antis fem");	
		else
			dump_adj(stem,3,"ans_adj");	
		return(1);
	}

	if( !strcmp("<itype>entis</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"ens")) ) {
	       if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,3,"ens_entis masc");	
		else if( !strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,3,"ens_entis fem");	
		else
			dump_adj(stem,3,"ens_adj");	
		return(1);
	}

	if( (!strcmp("<itype>orum</itype>",key1) ||
	     !strcmp("<itype>o_rum</itype>",key1)) && 
	   (!strcmp(stem+strlen(stem)-1,"i")) ) {
	       if( !strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,1,"us_i fem pl");	
		else
			dump_nom(stem,1,"us_i masc pl");	
		return(1);
	}

	if( (!strcmp("<itype>orum</itype>",key1) ||
	     !strcmp("<itype>o_rum</itype>",key1)) && 
	    !strcmp(key2,"<gen>n.</gen>") && 
	   (!strcmp(stem+strlen(stem)-1,"a")) ) {
		dump_nom(stem,1,"us_i neut pl");	
		return(1);
	}

	if( !strcmp("<itype>ae</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"es")) ) {
		dump_nom(stem,2,"es_ae masc");	
		return(1);
	}

	if( !strcmp("<itype>ae</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"as")) ) {
		dump_nom(stem,2,"as_ae masc");	
		return(1);
	}

	if( !strcmp("<itype>ae</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"e_s")) ) {
		dump_nom(stem,3,"es_ae masc");	
		return(1);
	}

	if( !strcmp("<itype>e_s</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"e_")) ) {
	        if( !strcmp(key2,"<gen>m.</gen>") )
			dump_nom(stem,2,"e_es fem");	
		else
			dump_nom(stem,2,"e_es masc");	
		return(1);
	}

	if( !strcmp("<itype>ii</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"on")) ) {
		dump_nom(stem,2,"os_i neut");	
		return(1);
	}

	if( !strcmp("<itype>ii</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"os")) ) {
		if( ! strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,2,"os_i fem");	
		else
			dump_nom(stem,2,"os_i masc");	
		return(1);
	}

	if( !strcmp("<itype>ii</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-3,"o^s")) ) {
		if( ! strcmp(key2,"<gen>f.</gen>") )
			dump_nom(stem,3,"os_i fem");	
		else
			dump_nom(stem,3,"os_i masc");	
		return(1);
	}

	if( !strcmp("<itype>i</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"on")) ) {
		dump_nom(stem,2,"os_i neut");	
		return(1);
	}

	if( !strcmp("<itype>i</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"um")) ) {
		dump_nom(stem,2,"us_i neut");	
		return(1);
	}

	if( !strcmp("<itype>i</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"us")) ) {
	    if( !strcmp(key2,"<gen>f.</gen>") )
		dump_nom(stem,2,"us_i fem");	
	    else
		dump_nom(stem,2,"us_i masc");	
		return(1);
	}


	if( !strcmp("<itype>e</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-2,"is")) ) {
		dump_adj(stem,2,"is_e");	
		return(1);
	}


	if( !strcmp("<itype>a</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-2,"us")) ) {
		dump_adj(stem,2,"us_a_um");	
		return(1);
	}

	if( !strcmp("<itype>a,",key1) && 
	    (!strcmp("um</itype>",key2)) &&
	    (!strcmp(stem+strlen(stem)-2,"us")) ) {
		dump_adj(stem,2,"us_a_um");	
		return(1);
	}


	if( (!strcmp("<itype>i^dis</itype>",key1) ||
	     !strcmp("<itype>i^dis</itype>",key1)) && 
	   (!strcmp(stem+strlen(stem)-2,"is")) ) {
	       if( !strcmp(key2,"<gen>m.</gen>") ) {
			dump_nom(stem,2,"is_idis  masc");	
		} else
			dump_nom(stem,2,"is_idis  fem");	
		return(1);
	}

	return(0);


	if( !strcmp("<itype>essa</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-3,"eis")) ) {
		dump_adj(stem,3,"eis_essa");	
		return(1);
	}

	if( !strcmp("qos</itype>",key1+strlen(key1)-11) && 
	    (!strcmp(stem+strlen(stem)-1,"s")) ) {
		char skeys[BUFSIZ];

		if( !strcmp(key2,"<gen>o(</gen>") && !strcmp(key2,"<gen>h(</gen>"))
			strcpy(skeys,"s_qos masc fem");	
		else if( !strcmp(key2,"<gen>o(</gen>") )
			strcpy(skeys,"s_qos masc");	
		else if( !strcmp(key2,"<gen>h(</gen>") )
			strcpy(skeys,"s_qos fem");	
		else
			strcpy(skeys,"s_qos fem");	
		dump_nom(stem,1,skeys);	
		return(1);
	}

	if( !strcmp("ggos</itype>",key1+strlen(key1)-12) && 
	    (!strcmp(stem+strlen(stem)-2,"gc")) ) {
		char skeys[BUFSIZ];
		int syllno = 0;
		int curacc = 0;

		if( !strcmp(key2,"<gen>o(</gen>") && !strcmp(key2,"<gen>h(</gen>"))
			strcpy(skeys,"gc_ggos masc fem");	
		else if( !strcmp(key2,"<gen>o(</gen>") )
			strcpy(skeys,"gc_ggos masc");	
		else if( !strcmp(key2,"<gen>h(</gen>") )
			strcpy(skeys,"gc_ggos fem");	
		else
			strcpy(skeys,"gc_ggos fem");	

		if(nsylls(stem) > 2 ) {
			if(syllno = PENULT ) strcat(skeys," ant_acc"  );
			checkaccent(stem,&syllno,&curacc);
		}
		dump_nom(stem,2,skeys);
		return(1);
	}

	if( !strcmp("aktos</itype>",key1+strlen(key1)-13) && 
	    (!strcmp(stem+strlen(stem)-2,"ac")|| !strcmp(stem+strlen(stem)-2,"la")) ) {
		char skeys[BUFSIZ];
		int syllno = 0;
		int curacc = 0;

		if( !strcmp(key2,"<gen>o(</gen>") && !strcmp(key2,"<gen>h(</gen>"))
			strcpy(skeys,"c_ktos masc fem");	
		else if( !strcmp(key2,"<gen>o(</gen>") )
			strcpy(skeys,"c_ktos masc");	
		else if( !strcmp(key2,"<gen>h(</gen>") )
			strcpy(skeys,"c_ktos fem");	
		else
			strcpy(skeys,"c_ktos fem");	

		if(nsylls(stem) > 2 ) {
			if(syllno = PENULT ) strcat(skeys," ant_acc"  );
			checkaccent(stem,&syllno,&curacc);
		}
		dump_nom(stem,(strcmp(stem+strlen(stem)-2,"ac")? 1 : 2),skeys);
		return(1);
	}

	if( !strcmp("gos</itype>",key1+strlen(key1)-11) && 
	    (!strcmp(stem+strlen(stem)-1,"c")) ) {
		char skeys[BUFSIZ];
		int syllno = 0;
		int curacc = 0;

		if( !strcmp(key2,"<gen>o(</gen>") && !strcmp(key2,"<gen>h(</gen>"))
			strcpy(skeys,"c_gos masc fem");	
		else if( !strcmp(key2,"<gen>o(</gen>") )
			strcpy(skeys,"c_gos masc");	
		else if( !strcmp(key2,"<gen>h(</gen>") )
			strcpy(skeys,"c_gos fem");	
		else
			strcpy(skeys,"c_gos fem");	

		if(nsylls(stem) > 2 ) {
			if(syllno = PENULT ) strcat(skeys," ant_acc"  );
			checkaccent(stem,&syllno,&curacc);
		}
		dump_nom(stem,1,skeys);
		return(1);
	}

	if( !strcmp("<itype>a^nos</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-3,"a_s")) ) {
		dump_adj(stem,3,"as_aina_an");	
		return(1);
	}

	if( !strcmp("<itype>idos</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-2,"is")) ) {
		dump_acc_nom(stem,2,"is_idos fem");	
/*
		if( *(stem+strlen(stem)-4) == '=' ) 
			dump_nom(stem,2,"is_idos fem stem_acc");	
		else
			dump_nom(stem,2,"is_idos fem");	
*/
		return(1);
	}

	if( (!strcmp("<itype>a_kos</itype>",key1) || !strcmp("<itype>a^kos</itype>",key1))
	    && (!strcmp(stem+strlen(stem)-2,"ac")) ) {
		stem[strlen(stem)-1] = key1[8];
		strcat(stem,"c");
		if( !strcmp(key2,"<gen>h(</gen>") )
			dump_nom(stem,1,"c_kos fem");	
		else
			dump_nom(stem,1,"c_kos masc");	
		return(1);
	}

	if( !strcmp("<itype>akos</itype>",key1) 
	    && (!strcmp(stem+strlen(stem)-2,"ac")) ) {
		if( !strcmp(key2,"<gen>h(</gen>") )
			dump_nom(stem,1,"c_kos fem");	
		else
			dump_nom(stem,1,"c_kos masc");	
		return(1);
	}

	if( !strcmp("<itype>eos</itype>",key1) && 
	    !strcmp("<gen>to/</gen>",key2) &&
	    (!strcmp(stem+strlen(stem)-2,"os")) ) {
		dump_nom(stem,2,"hs_eos neut");	
		return(1);
	}

	if( !strcmp("<itype>u=qos</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-3,"u/s")) ) {
		char tmpstem[BUFSIZ];
/*
 * kludge to get the long mark in over the last consonant
 */
		strcpy(tmpstem,stem);
		strcpy(tmpstem+strlen(stem)-3,"u_/s");

		dump_nom(tmpstem,2,"s_qos fem stem_acc");	
		return(1);
	}

	if( !strcmp("<itype>ews</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-2,"is")) ) {
		dump_nom(stem,2,"is_ews fem");	
		return(1);
	}

	if( (!strcmp("<itype>a</itype>",key1) || 
	     !strcmp("<itype>e/a</itype>",key1)) && 
	    (!strcmp(stem+strlen(stem)-5,"te/os")) ) {
		dump_adj(stem,4,"verb_adj2 suff_acc");	
		return(1);
	}

	if( !strcmp("<itype>a/dos</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-3,"a/s")) ) {
		dump_nom(stem,2,"s_dos fem stem_acc");	
		return(1);
	}

	if( !strcmp("<itype>i/dos</itype>",key1) && 
	    (!strcmp(stem+strlen(stem)-3,"i/s")) ) {
		dump_nom(stem,3,"is_idos fem suff_acc");	
		return(1);
	}

	if( !strcmp("<itype>ontos</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"wn") ) {
		dump_nom(stem,2,"wn_ontos masc");	
		return(1);
	}

	if( !strcmp("<itype>ousa</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"wn") ) {
		dump_adj(stem,2,"wn_ousa_on");	
		return(1);
	}

	if( !strcmp("<itype>on</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"wn") ) {
		dump_adj(stem,2,"wn_on");	
		return(1);
	}

	if( !strcmp("<itype>w=nos</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-3,"w/n") ) {
		dump_nom(stem,1,"n_nos masc stem_acc");	
		return(1);
	}

	if( !strcmp("<itype>u/os</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-3,"u/s") ) {
		dump_nom(stem,3,"us_uos fem suff_acc");	
		return(1);
	}

	if( !strcmp("<itype>wnos</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"wn") ) {
		dump_nom(stem,1,"n_nos masc");	
		return(1);
	}

	if( !strcmp("<itype>onos</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"wn") ) {
		dump_nom(stem,2,"wn_onos masc");	
		return(1);
	}

	if( !strcmp("<itype>htos</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"hs") ) {
		dump_nom(stem,1,"s_tos fem");	
		return(1);
	}

	if( !strcmp("<itype>ou</itype>",key1) && 
	   (!strcmp(stem+strlen(stem)-2,"as") ||
	    !strcmp(stem+strlen(stem)-2,"hs"))) {
		dump_nom(stem,2,"hs_ou masc stem_acc");	
		return(1);
	}

	if( !strcmp("<itype>ou=</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-3,"h/s") ) {
		dump_nom(stem,3,"hs_ou masc suff_acc");	
		return(1);
	}

	if( !strcmp("<itype>es</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-5,"w/dhs") ) {
		dump_adj(stem,2,"hs_es stem_acc");	
		return(1);
	}

	if( !strcmp("<itype>e/s</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-3,"h/s") ) {
		dump_adj(stem,3,"hs_es suff_acc");	
		return(1);
	}

	if( !strcmp("<itype>o/n</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-3,"o/s") ) {
		dump_adj(stem,3,"os_on suff_acc");	
		return(1);
	}

	if( (!strcmp("<itype>h/</itype>",key1) ||
	     !strcmp("<itype>a/</itype>",key1))&& 
	    !strcmp(stem+strlen(stem)-3,"o/s") ) {
		dump_adj(stem,3,"os_h_on suff_acc");	
		return(1);
	}

	if( (!strcmp("<itype>a</itype>",key1)||
		!strcmp("<itype>h</itype>",key1))  && 
	    !strcmp(stem+strlen(stem)-2,"os") ) {
		dump_adj(stem,2,"os_h_on");	
		return(1);
	}

	if( !strcmp("<itype>on</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"os") ) {
		dump_acc_nom(stem,2,"os_on");	
/*
		dump_adj(stem,2,"os_on");	
*/
		return(1);
	}

	if( !strcmp("<itype>atos</itype>",key1) && 
	    !strcmp(key2,"<gen>to/</gen>") ) {
		dump_nom(stem,2,"ma_matos neut");	
		return(1);
	}

	if( !strcmp("<itype>ews</itype>",key1) && 
	    !strcmp(key2,"<gen>h(</gen>") ) {
		dump_nom(stem,2,"is_ews fem");	
		return(1);
	}

	if( !strcmp("<itype>e/ws</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-4,"eu/s") ) {
		dump_nom(stem,4,"eus_ews masc suff_acc");	
		return(1);
	}

	if( !strcmp("<itype>oros</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-2,"wr") ) {
		dump_nom(stem,2,"wr_oros masc");	
		return(1);
	}

	if( !strcmp("<itype>h=ros</itype>",key1) && 
	    !strcmp(stem+strlen(stem)-1,"r") ) {
		dump_nom(stem,1,"r_ros masc stem_acc");	
		return(1);
	}

	return(0);
}

is_verb(char *stem)
{

	if( !strcmp(stem+strlen(stem)-4,"eu/w") ) {
		dump_entry(stem,4,"euw",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-7,"eu/omai") ) {
		dump_entry(stem,7,"euw mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"u/nw") ) {
		dump_entry(stem,4,"unw",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-7,"u/nomai") ) {
		dump_entry(stem,7,"unw mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"e/w") ) {
		dump_entry(stem,3,"ew_denom",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-6,"e/omai") ) {
		dump_entry(stem,6,"ew_denom mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"o/w") ) {
		dump_entry(stem,3,"ow_denom",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-6,"o/omai") ) {
		dump_entry(stem,6,"ow_denom mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"u/zw") ) {
		dump_entry(stem,4,"uzw",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-7,"u/zomai") ) {
		dump_entry(stem,7,"uzw mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"i/zw") ) {
		dump_entry(stem,4,"izw",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-7,"i/zomai") ) {
		dump_entry(stem,7,"izw mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-6,"ssomai") ) {
		dump_entry(stem,6,"ss mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"ssw") ) {
		dump_entry(stem,3,"ss",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"a/zw") ) {
		dump_entry(stem,4,"azw",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-7,"a/zomai") ) {
		dump_entry(stem,7,"azw mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-4,"ia/w") ) {
		dump_entry(stem,4,"iaw_denom",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-7,"ia/omai") ) {
		dump_entry(stem,7,"iaw_denom mp",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-3,"a/w") ) {
		dump_entry(stem,3,"aw_denom",":de:",fverbs);	
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-6,"a/omai") ) {
		dump_entry(stem,6,"aw_denom mp",":de:",fverbs);	
		return(1);
	}

	return(0);
}

int is_adverb(char *stem,char * key1)
{
	if( !strcmp(key1,"<pos>adv.</pos>") ) {
		char tmp[BUFSIZ];


		strcpy(tmp,stem);
		standword(tmp);
		printf(":le:%s%s\n:wd:%s adverb\n\n", tmp, numsuff, stem );
/*
		dump_entry(stem,0,"adverb",":wd:",stdout);	
*/
		return(1);
	}

	return(0);
}

dump_acc_nom(char * stem,int trunc,char * tag) 
{
	char tmptag[BUFSIZ];
	char tmpstem[BUFSIZ];
	int syllno, curacc;

	strcpy(tmpstem,stem);
	*(tmpstem+strlen(tmpstem)-trunc) = 0;

	checkaccent(tmpstem,&syllno,&curacc);
	if( syllno == ULTIMA ) {
		sprintf(tmptag,"%s stem_acc", tag );
		dump_nom(stem,trunc,tmptag);
	} else
		dump_nom(stem,trunc,tag);
}

is_teos(char *stem)
{
	if( !strcmp(stem+strlen(stem)-5,"te/os") ) {
		dump_adj(stem,4,"verb_adj2 suff_acc");
		return(1);
	}

	if( !strcmp(stem+strlen(stem)-5,"te/on") ) {
		dump_adj(stem,4,"verb_adj2 suff_acc");
		return(1);
	}
	return(0);
}
