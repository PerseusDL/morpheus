
%%

^[A-Za-z\^\_\-]+o[#1-9]* 	set_lemma();
^[A-Za-z\^\_\-]+or[#1-9]* 	set_lemma();
^[A-Za-z\^\_\-]+[ei]t[#1-9]* 	set_lemma();

"<itype>"[^<]+"</itype>"	do_itype();
"<orth>"[^<]+"</orth>"	set_orth();

%%

#include <string.h>

int sawi = 0;
int sawpass = 0;

char orthstem[BUFSIZ];

unsigned char stem[BUFSIZ], lemma[BUFSIZ];

char *spectypes[] = {
"<itype>po^su^i, po^si^tum, 3</itype>",
"<itype>e^ru^i, ertum, 4</itype>",
"<itype>cu^bu^i, cu^bi^tum, 3</itype>",
"<itype>se_di, sessum, 2</itype>",
"<itype>se_di, 2</itype>",
"<itype>se_di, sessum, 3</itype>",
"<itype>se_di, 3</itype>",
"<itype>exi, ectum, 3</itype>",
"<itype>inxi, ictum, 3</itype>",
"<itype>i_si, issum, 3</itype>",
"<itype>i_si, i_sum, 3</itype>",
"<itype>ortus, 4</itype>",
"<itype>ui, u_tum, 3</itype>",
"<itype>fe_ci, factum, 3</itype>",
"<itype>fe_ci, factum</itype>",
"<itype>e_mi, emptum, 3</itype>",
"<itype>du^i, 3</itype>",
"<itype>nxi, nctum, 3</itype>",
"<itype>mi_si, missum, 3</itype>",
"<itype>fu_di, fu_sum, 3</itype>",
"<itype>cessi, cessum, 3</itype>",
"<itype>ve_ni, ventum, 4</itype>",
"<itype>di, sum, 4</itype>",
"<itype>ru^i, 3</itype>",
"<itype>di, sum, 3</itype>",
"<itype>lu^i, 3</itype>",
"<itype>gressus, 3</itype>",
"<itype>fu_gi, 3</itype>",
"<itype>fre_gi, fractum, 3</itype>",
"<itype>tu^i, 3</itype>",
"<itype>ce_pi, ceptum, 3</itype>",
"<itype>bu^i, 3</itype>",
"<itype>ussi, ustum, 3</itype>",
"<itype>xu^i, xtum, 3</itype>",
"<itype>cu^i, ci^tum, 2</itype>",
"<itype>u_si, u_sum, 3</itype>",
"<itype>cessi, cessum, 3</itype>",
"<itype>e_vi, e_tum, 2</itype>",
"<itype>e_vi, e_tum, 3</itype>"
};

do_itype()
{
	int rval;
	
if( !strcmp(yytext,"<itype>e_re</itype>") )	return( doverb("conj2"));
if( !strcmp(yytext,"<itype>e^re</itype>") )	return( doverb("conj3"));
if( !strcmp(yytext,"<itype>i_re</itype>") )	return( doderiv("ire_vb"));
if( !strcmp(yytext,"<itype>i_ri</itype>") )	{sawpass = 1; return( doderiv("ire_vb")); }
if( !strcmp(yytext,"<itype>a_re</itype>") )	return( doderiv("are_vb"));
if( !strcmp(yytext,"<itype>a_ri</itype>") ) {sawpass = 1; return( doderiv("are_vb")); }
if( !strcmp(yytext,"<itype>xi, 3</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>xi, xum, 3</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>si, sum</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>sum, 3</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>si, 2</itype>") )	return( do_vstems("conj2",1));
if( !strcmp(yytext,"<itype>xi, 2</itype>") )	return( do_vstems("conj2",1));
if( !strcmp(yytext,"<itype>xi, ctum, 3</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>si, sum, 2</itype>") )	return( do_vstems("conj2",1));
if( !strcmp(yytext,"<itype>si, sum, 3</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>psi, ptum, 3</itype>") )	return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>di^di, di^tum, 3</itype>") ) return( do_vstems("conj3",1));
if( !strcmp(yytext,"<itype>si, sum, 4</itype>") ) return( do_vstems("conj4",1));

if( !strcmp(yytext,"<itype>u^i, itum, 2</itype>") )	return( do_vstems("conj2",0));
if( !strcmp(yytext,"<itype>i^ti, i^tum, 1</itype>") )	return( do_vstems("conj1",0));
if( !strcmp(yytext,"<itype>ii, i_tum, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>i^tus, 2</itype>") )	return( do_vstems("conj2",0));
if( !strcmp(yytext,"<itype>ii, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>u^i, e_re</itype>") )	return( do_vstems("conj2",0));
if( !strcmp(yytext,"<itype>ui, i^tum, 1</itype>") )	return( do_vstems("conj1",0));
if( !strcmp(yytext,"<itype>ui, i^tum, 2</itype>") )	return( do_vstems("conj2",0));
if( !strcmp(yytext,"<itype>i_vi, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>i_tus, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>u^i, i^tum, 1</itype>") )	return( do_vstems("conj1",0));
if( !strcmp(yytext,"<itype>u^i, 1</itype>") )	return( do_vstems("conj1",0));
if( !strcmp(yytext,"<itype>ui, 1</itype>") )	return( do_vstems("conj1",0));
/*
if( !strcmp(yytext,"<itype>u^i, u_tum, 3</itype>") )	return( do_vstems("conj3",0));
*/
if( !strcmp(yytext,"<itype>u^i, 1</itype>") )	return( do_vstems("conj1",0));
if( !strcmp(yytext,"<itype>u^i, 2</itype>") )	return( do_vstems("conj2",0));
if( !strcmp(yytext,"<itype>ui, 2</itype>") )	return( do_vstems("conj2",0));
if( !strcmp(yytext,"<itype>u^i, 3</itype>") )	return( do_vstems("conj3",0));
if( !strcmp(yytext,"<itype>u^i</itype>") )	return( do_vstems("conj3",0));
if( !strcmp(yytext,"<itype>i_tum, 4</itype>") )	return( do_vstems("conj4",0));

if( !strcmp(yytext,"<itype>i_vi, or i^i, i_tum, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>i_vi, or i^i, i_tum, 3</itype>") )	return( do_vstems("conj3",0));
if( !strcmp(yytext,"<itype>i_vi, or i^i, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>i_vi, or i^i, i_tum, 3</itype>") )	return( do_vstems("conj3",0));

if( !strcmp(yytext,"<itype>u^i, i^tum, 3</itype>") )	return( do_vstems("conj3",0));

if( !strcmp(yytext,"<itype>i_vi, i_tum, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>i^i, i^tum, 4</itype>") )	return( do_vstems("conj4",0));
if( !strcmp(yytext,"<itype>u^i, i^tum, 2</itype>") )	return( do_vstems("conj2",0));

if( !strcmp(yytext,"<itype>e_gi, actum, 3</itype>") ) {
printf("\nlem:%s\n", lemma );
	if( !strcmp(lemma+strlen(lemma)-strlen("igo"),"igo") || 
		!strcmp(lemma+strlen(lemma)-strlen("igor"),"igor") || 
		!strcmp(lemma+strlen(lemma)-strlen("ingo"),"ingo") ) 

			return( do_vstems("conj3",'i'));
	else return( do_vstems("conj3",'a'));
}

if( !strcmp(yytext,"<itype>essi, essum, 3</itype>") ) {
	if( strchr(lemma,'e') )	return( do_vstems("conj3",yytext[7]));
	else return( do_vstems("conj3",'i'));
}

if( !strcmp(yytext,"<itype>sum, 2</itype>") )	return( do_vstems("conj2",'d'));
if( !strcmp(yytext,"<itype>u^i, u_tum, 3</itype>") )	return( do_vstems("conj3",'u'));
if( !strcmp(yytext,"<itype>ve_ni, ventum</itype>") )	return( do_vstems("conj4",'v'));
if( !strcmp(yytext,"<itype>cu_tus, 3</itype>") )	return( do_vstems("conj3",'q'));
if( !strcmp(yytext,"<itype>mpsi</itype>") )	return( do_vstems("conj3",yytext[7]));
if( !strcmp(yytext,"<itype>ui, u_tum, 3</itype>") )	return( do_vstems("conj3",yytext[7]));
if( !strcmp(yytext,"<itype>fe_ci, factum</itype>") )	return( do_vstems("conj3_io",yytext[7]));

if( (rval=is_spectype()) ) {
	char tmp[BUFSIZ];

	strcpy(tmp,"conjX");
	tmp[4] = rval;

	return( do_vstems(tmp,yytext[7]));
}

/*
if( isalpha( yytext[7] ) && ! strchr("aeioux",yytext[7]) )
	 return( do_vstems("conj3",yytext[7]));
*/


ECHO;
}

#define LENGTH_OF(X) (sizeof X/sizeof X[0])
is_spectype()
{
	int i;

	for(i=0;i<LENGTH_OF(spectypes);i++) {
		if( ! strcmp(yytext,spectypes[i]) ) {
			if( isdigit(yytext[yyleng-strlen("</itype>")-1]))
				return(yytext[yyleng-strlen("</itype>")-1]);
			else
				return(0);
		}
	}

	if( isalpha( yytext[7] ) && ! strchr("aeioux",yytext[7] )
	    && isdigit(yytext[yyleng-strlen("</itype>")-1]))
			return(yytext[yyleng-strlen("</itype>")-1]);

	return(0);
}


set_lemma()
{
	unsigned char *t;

	ECHO;
	sawi = sawpass = orthstem[0] = 0;
	sawi = 0;
	strcpy(lemma,yytext);

	t = lemma;

	while(*t&&!isspace(*t)) t++;
	*t = 0;

	strcpy(stem,lemma);

	t = lemma;
	while(*t) {
		if( !isalpha(*t) && *t!='#' && !isdigit(*t) ) {
			strcpy(t,t+1);
			continue;
		}
		t++;
	}

	t = stem;
	while(*t&&*t!='#') t++;
	*t = 0;
	
	t = stem+strlen(stem) - 4;

	if( ! strcmp(t,"i^or")  ) {
		sawi = 1;
		*t = 0;
	} else if( ! strcmp(t,"e^or") ) {
		*t = 0;
		sawpass = 1;
	} else if( ! strcmp(++t,"i^o") ) {
		sawi = 1;
		*t = 0;
	} else if( ! strcmp(t,"e^o") ) {
		*t = 0;
	} else if( ! strcmp(t,"ior") ) {
		sawi = 1;
		*t = 0;
		sawpass = 1;
	} else if ( ! strcmp(t,"eor") ) {
		*t = 0;
		sawpass = 1;
	} else if( ! strcmp(++t,"or") ) {
		*t = 0;
		sawpass = 1;
	} else if( ! strcmp(t,"eo") ) {
		*t = 0;
	} if ( ! strcmp(t,"it") || ! strcmp(t,"et") ) {
		*t = 0;
	} if ( ! strcmp(t,"io") ) {
		sawi = 1;
		*t = 0;
	} else *++t = 0;
}
/*

*/


doderiv(char * tag)
{
	unsigned char *t;
	char addi[BUFSIZ], deptag[BUFSIZ];


	if( orthstem[0] ) printf("\north: [%s] [%s]\n", stem, orthstem);
	orthstem[0] = 0;
	printf("\n:le:%s\n", lemma );

	deptag[0] = addi[0] = 0;
	if( ! strcmp(tag,"are_vb") && sawi ) strcpy(addi,"i");
	if( sawpass ) strcpy(deptag," dep");
	
	printf(":de:%s%s\t%s%s\n", stem, addi, tag ,deptag);
	if( orthstem[0] ) {
		printf(":de:%s%s\t%s%s orth\n", orthstem, addi, tag ,deptag);
	}
	sawi = sawpass = 0;
}

set_orth()
{
	unsigned char * t = yytext + 6;
	unsigned char * p = orthstem;
	ECHO;

	strcpy(orthstem,stem);


	if(!strcmp("<orth>adf-</orth>",yytext) ) {
		if( ! strncmp(orthstem,"af-f",4) ) {
			orthstem[1] = 'd';
			return;
		}
	}

	if(!strcmp("<orth>adl-</orth>",yytext) ) {
		if( ! strncmp(orthstem,"al-l",4) ) {
			orthstem[1] = 'd';
			return;
		}
	}

	if(!strcmp("<orth>adn-</orth>",yytext) ) {
		if( ! strncmp(orthstem,"an-n",4) ) {
			orthstem[1] = 'd';
			return;
		}
	}

	if(!strcmp("<orth>ads-</orth>",yytext) ) {
		if( stem[2] == 'c' || stem[2] == 't' ) {
			char tmp[BUFSIZ];

			strcpy(tmp,orthstem+1);
			orthstem[1] = 'd';
			strcpy(orthstem+2,tmp);
		} else {
			orthstem[1] = 'd';
		}

		return;
	}
	orthstem[0] = 0;
return;


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

doverb(char * vtag)
{
	char tmp[BUFSIZ];


	strcpy(tmp,vtag);
	printf("\n:le:%s\n", lemma );
	if( sawi && !strcmp("conj3",tmp) ) strcpy(tmp,"conj3_io");

	printf(":vs:%s\t%s\n", stem, tmp );
	if( orthstem[0] ) {
		printf(":vs:%s\t%s orth\n", orthstem, tmp );
	}
	
	sawi = 0;
}

do_vstems(char * vtag, int trimn )
{
	unsigned char tmpstem[BUFSIZ], perfsuff[BUFSIZ] , supsuff[BUFSIZ];
	unsigned char tmporths[BUFSIZ];
	unsigned char * t;

	doverb(vtag);


	strcpy(tmpstem,stem);
	strcpy(tmporths,orthstem);

	truncstem(tmpstem,trimn);
	truncstem(tmporths,trimn);

/*
	if( trimn == 1) {
		t = tmpstem+strlen(tmpstem)-2;
		if( !strcmp("ct",t)) *t = 0;
		else *++t = 0;
	} else if( isalpha(trimn) ) {
		t = tmpstem+strlen(tmpstem)-1;
		while(t>=tmpstem) {
			if(*t == trimn ) {
				*t = 0;
				break;
			}
			t--;
		}
	}
*/


	t = yytext+strlen("<itype>");

#define isbreak(X) (X == ',' || X == '.' || X == '<')

	perfsuff[0] = supsuff[0] = 0;
	strcpy(perfsuff,t);
	t = perfsuff;
	while(*t&&!isspace(*t)&&!isbreak(*t)) t++;
	*t++ = 0;

	if( perfsuff[strlen(perfsuff)-1] == 'i' ) {
		perfsuff[strlen(perfsuff)-1] = 0;

		while(isspace(*t)||isbreak(*t)) t++;


		if( !strncmp("or ",t,3)) {
			printf(":vs:%s%s perfstem\n", tmpstem , perfsuff);
			t += 3;

			strcpy(perfsuff,t);
			t = perfsuff;
			while(*t&&!isspace(*t)&&!isbreak(*t)) t++;
			*t++ = 0;
			if( perfsuff[strlen(perfsuff)-1] == 'i' ) 
				perfsuff[strlen(perfsuff)-1] = 0;
			while(isspace(*t)) t++;
		}
		if( ! isdigit(*t) && strcmp("</itype>",t)) {
			strcpy(supsuff,t);
			t = supsuff;
			while(*t&&!isspace(*t)&&!isbreak(*t)) t++;
			*t++ = 0;
			supsuff[strlen(supsuff)-2] = 0;
		}

	} else if( perfsuff[strlen(perfsuff)-2] == 'u' ) {
		perfsuff[strlen(perfsuff)-2] = 0;
		strcpy(supsuff,perfsuff);
		perfsuff[0] = 0;
	}

	
	if( perfsuff[0] ) {
		printf(":vs:%s%s perfstem\n", tmpstem , perfsuff);
		if( orthstem[0] ) printf(":vs:%s%s perfstem orth\n", tmporths , perfsuff);
	}

	if( supsuff[0] ) {
		printf(":vs:%s%s pp4\n", tmpstem , supsuff);
	}

}

truncstem(char * workstem, int trimn)
{
	char  * t;

	if( trimn == 1) {
		t = workstem+strlen(workstem)-2;
		if( !strcmp("ct",t)) *t = 0;
		else *++t = 0;
	} else if( isalpha(trimn) ) {
		t = workstem+strlen(workstem)-1;
		while(t>=workstem) {
			if(trimn == 's' && (*t=='d'||*t=='q')) {
				*t = 0;
				break;
			}
			if(*t == trimn ) {
				*t = 0;
				break;
			}
			t--;
		}
	}
}
