#include <gkstring.h>

#include "propname.proto.h"
int quickflag = 0;
char * anal_buf();
long prevmemory = 0;
FILE * fpnames = NULL;
char tbuf[5000], possbuf[10000];

main(void)
{
	FILE * finput, *foutput, *fnew;
	char line[BUFSIZ*4];
	char fname[BUFSIZ],inpname[BUFSIZ], outname[BUFSIZ];
	char newname[BUFSIZ];
	
	int rval;
	long freemem = 0;
	long nwords = 0;
	long nhits = 0;
	char * p;
	fname[0] = 0;

	fprintf(stderr,"use stdout? ");
	gets(line);
	
	if(line[0] == 'y' ) {
		fprintf(stderr,"type in forms\n");
		strcpy(outname,"out.morph");
		finput = stdin;
	} else {
		fprintf(stderr,"word file? ");
		gets(fname);
		
		strcpy(inpname,fname);
		strcat(inpname,".words");
		
		strcpy(outname,fname);
		strcat(outname,".morph");

		strcpy(newname,fname);
		strcat(newname,".nstem");

		if((finput=fopen(inpname,"r")) == NULL) {
			fprintf(stderr,"cannot find [%s]!\n", inpname);
			exit(-1);
		}

		if((fnew=fopen(newname,"w")) == NULL) {
			fprintf(stderr,"cannot create [%s]!\n", newname);
			exit(-1);
		}

	
	}
			
	if( ! fpnames ) {
			char tmp[MAXWORDSIZE];
			
			if( ! fname[0] ) {
				printf("basename? ");
				gets(fname);
			}
			strcpy(tmp,fname);
			strcat(tmp,".enames");
			fpnames = fopen(tmp,"r");
			if( !fpnames ) {
				fprintf(stderr,"%s not found!\n", tmp);
				exit(-1);
			}
		}
	

	if( (foutput=fopen(outname,"w")) == NULL) {
		fprintf(stderr,"cannot find [%s]!\n", outname);
		exit(-1);
	}

	while(fgets(line,sizeof line,finput)) {
/*
		printf("%s %s %d\n", line, prevl , dictstrcmp(line,prevl) );
		strcpy(prevl,line);
		continue;
*/		
		trimwhite(line);
		trimdigit(line);
		p = line;
		while(*p&&!isspace(*p)) p++;
		if(*p) *p = 0;
		if( isspace(line[0]) ) continue;
		if( line[2] == '*' ) continue;
		rval = checkstring(line,(PrntFlags)SHOW_LEMMA|STRICT_CASE,foutput);
/*
		if( rval ) 
			printf("%s",anal_buf() );
*/
		if( ! rval ) 
			rval = checkpropname(line,fnew);
		nwords++;
		if( rval ) {
			nhits++;
		} else {
/*
			printf(":failed %s\n", line );
*/
			fprintf(foutput,":failed %s\n", line );
			fflush(foutput);
		}
/*
freemem = (long) FreeMem();
fprintf(stderr,"%ld %ld %0.2f %s %d %ld %ld \n", 
nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval , freemem , prevmemory - freemem );
		prevmemory = freemem;
*/
if( ! (nwords % 50 ) ) 
fprintf(stderr,"%ld %ld %0.2f %s %d\n", 
nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval  );
	}
	if( finput != stdin )
		fclose(finput);
	fclose(foutput);
}

trimdigit(char *s)
{
	char * p = s;
	while(*s) s++;
	s--;
	while(isdigit(*s)&&s>p) *s-- = 0;
}

checkpropname(char *s, FILE *f)
{
	char tmpname[BUFSIZ], *wp, curend[BUFSIZ], endkeys[BUFSIZ];
	char half1[BUFSIZ];
	int is_ending = 0;
	char xlit[BUFSIZ];
	int rval = 0;
	
	strcpy(tmpname,s);
	endkeys[0] = 0;
/*
printf("%s\n", s);	
*/
	wp = tmpname;
	while( *wp ) {

	    strcpy(curend,wp);
	    stripacc(curend);
	    stripdiaer(curend);
	    Xstrncpy(half1,tmpname,sizeof half1);
	    half1[wp-tmpname]=0;
	    wp++;

		is_ending = chcknend(curend,endkeys);
		if( is_ending ) {
			Xliterate(half1,xlit/*,curend*/);
/*
			printf("%s\t%s\t%s\t%s\n", xlit, half1, curend, endkeys );
*/
			rval += tryxlits(f,xlit,endkeys,s,half1,curend);
		}

	}

	return(rval);
}

tryxlits(FILE *f, char *xlit, char *keys, char *fulls, char *half1, char *ends)
{
	char curkey[BUFSIZ];
	char workkey[BUFSIZ];
	int rval = 0;
	
	strcpy(workkey,keys);
	
	possbuf[0] = 0;
	while(nextkey(workkey,curkey) ) {
		rval += checkposs(f,xlit,curkey,fulls,half1,ends);
	}
	if(rval ) fprintf(f,"%s", possbuf);
	fflush(f);
	return(rval);
}

Xliterate(char *s1, char *s2)
{
	char tmp[BUFSIZ];
	int add_h = 0;
	
	strcpy(tmp,s1);
	if( getbreath(tmp) == ROUGHBR) {
		add_h = 1;
	}

	strcpy(tmp,s1+1);
	stripbreath(tmp);
	stripacc(tmp);
	stripdiaer(tmp);
	reliterate(tmp);
	
	if( add_h ) {
		if( tmp[0] == 'r' ) {
			strcpy(s2,"rh");
			strcat(s2,tmp+1);
		} else {
			strcpy(s2,"h");
			strcat(s2,tmp);
		}
	} else
		strcpy(s2,tmp);
	*s2 = toupper(*s2);
}


typedef struct {
	char stype[20];
	char suffix[20];
	char addsuff[20];
	char keys[30];
} nom_tab;

nom_tab Nom_tab[] = {
	"s_tos",		"s",	"",		" ",
	"n_ntos",		"n",	"",		"masc ",
	"n_nos",		"n",	"",		"masc ",
	"aos_aou",		"aus",	"",		"masc ",
	"us_uos",		"ys",	"",		" ",
	"wr_oros",		"or",	"",		"masc ",
	"c_ktos",		"x",	"",		"masc ",
	"c_kos",		"x",	"",		"masc ",
	"y_pos",		"ps",	"",		"masc ",
	"wn_ontos",		"on",	"",		"masc ",
	"wn_onos",		"on",	"",		"masc ",
	"wn_onos",		"ones",	"",		"masc pl",
	"w_oos",		"o",	"",		"fem ",
	"pous_podos",		"pous",	"",		" ",
	"klehs_kleous",		"cles",	"",		"masc",
	"is_ios",		"is",	"",		"fem ",
	"is_idos",		"is",	"",		"fem ",
	"is_ews",		"is",	"",		"fem ",
	"eus_ews",		"eus",	"",		"masc ",
	"eus_ews",		"ian",	"",		"masc ",
	"eus_ews",		"an",	"",		"masc ",
	"as_ados",		"adian", "",		"fem ",
	"as_antos",		"as",	"",		"masc ",
	"a_hs",			"a",	"",		"fem ",
	"h_hs",			"e",	"",		"fem ",
	"h_hs",			"a",	"",		"fem doric",
	"h_hs",			"ae",	"",		"fem pl",
	"hs_ou",		"",	"",		"masc ",
	"hs_ou",		"ae",	"",		"masc pl",
	"hs_ou",		"as",	"",		"masc doric",
	"hs_eos",		"crates",	"krat",		"masc ",
	"hs_ou",		"es",	"",		"masc ",
	"hs_eos",		"es",	"",		"masc ",
	"os_ou",		"us",	"",		"masc ",
	"os_ou",		"um",	"",		"neut ",
	"os_h_on",		"ian",	"",		"",
	"os_h_on",		"an",	"",		"",
	"os_h_on",		"ans",	"",		"",
	0,
};


checkposs(FILE *fout, char *xlit, char *curs, char *fulls, char *stems, char *ends)
{
	char tmpxlit[BUFSIZ];
	char tmpstem[MAXWORDSIZE];
	char tmpkeys[MAXWORDSIZE];
	int i = 0;
	int hits = 0;
	int rval = 0;
	int poss = 0;

	strcpy(tmpstem,stems);
	stripacc(tmpstem);
	
	for(i=0;Nom_tab[i].stype[0];i++) {
		if( ! strcmp(curs,Nom_tab[i].stype) ) {
			strcpy(tmpxlit,xlit);
			strcat(tmpxlit,Nom_tab[i].suffix);
			if( is_propname(tmpxlit) ) {
				sprintf(tmpkeys,"%s", Nom_tab[i].keys );
				rval = stem_can_work(tmpxlit,fulls, tmpstem, ends, Nom_tab[i].stype, tmpkeys );
/*			
				sprintf(stemkeys,"%s %s %s %s",tmpxlit, tmpstem, Nom_tab[i].stype, Nom_tab[i].keys );
				subchar(stemkeys,' ',':');
				set_stem(Gkword,tmpstem);
				set_endstring(Gkword,ends);
				set_gkstring(curstem,tmpstem);
				set_workword(Gkword,fulls);
				rval = checkdict(Gkword,curstem,stemkeys );
*/
				if( ! rval ) {
					sprintf(tmpkeys,"%s suff_acc", Nom_tab[i].keys );
					rval = stem_can_work(tmpxlit, fulls,tmpstem, ends, Nom_tab[i].stype, tmpkeys );
				}
				if( ! rval ) {
					sprintf(tmpkeys,"%s stem_acc", Nom_tab[i].keys );
					rval = stem_can_work(tmpxlit, fulls,tmpstem, ends, Nom_tab[i].stype, tmpkeys );
				}
				if( rval && is_propname(tmpxlit) == 1 ) {
					/*fprintf(fout,":ns:%s %s %s %s\n", tmpxlit,  tmpstem, Nom_tab[i].stype, tmpkeys );*/
					sprintf(tbuf,"%s :ns:%s %s %s %s\n", fulls, tmpxlit, tmpstem, Nom_tab[i].stype, tmpkeys );
					strcat(possbuf,tbuf);
					poss++;
/*
					printf("%s %s %s %s\n", tmpxlit,  tmpstem, Nom_tab[i].stype, tmpkeys );
*/
				}
				hits += rval;
			}
		}
	}

/*	if( poss == 1 ) fprintf(fout,"%s", possbuf);*/
/*	
	printf("\t%s\t%s\n", xlit, curs );
*/
	return(hits);
}

stem_can_work(char *englem, char *fulls, char *stem, char *ends, char *stype, char *keys)
{
	gk_word * Gkword;
	gk_string * curstem;
	char stemkeys[BUFSIZ];
	int rval = 0;
	
	Gkword = CreatGkword(1);
	curstem = CreatGkString(1);
	stemkeys[0] = 0;

	sprintf(stemkeys,"%s %s %s %s",englem, stem, stype, keys );
	subchar(stemkeys,' ',':');
	set_stem(Gkword,stem);
	set_endstring(Gkword,ends);
	set_gkstring(curstem,stem);
	set_workword(Gkword,fulls);
	rval = checkdict(Gkword,curstem,stemkeys );

	
	FreeGkword(Gkword);
	FreeGkString(curstem);
	return(rval);
}

typedef struct {
	char raw[20];
	char done[20];
} xlit_tab;


xlit_tab Xlit_list[] = {
	"aue",	"ave",
	"auh",	"ave",
	"eui",	"evi",
	"eue",	"eve",
	"euh",	"eve",
	"eua",	"eva",
	"aui",	"avi",
	"au",	"au",
	"eu",	"eu",
	"h",	"e",
	"k",	"c",
	"c",	"x",
	"q",	"th",
	"u",	"y",
	"f",	"ph",
	"x",	"ch",
	"y",	"ps",
	"w",	"o",
	"ai",	"ae",
	"oi",	"oe",
	"ou",	"u",
	"rr",	"rrh",
	"ei",	"i",
	"gg",	"ng",
	"gx",	"nch",
	"gk",	"nc",
	0,
	};
	
reliterate(char *s)
{
	char tmp[BUFSIZ];
	int i = 0;
	int sawone = 0;
	
	while(*s) {
		for(i=0;Xlit_list[i].raw[0];i++) {
			if( ! Xstrncmp(s,Xlit_list[i].raw,Xstrlen(Xlit_list[i].raw) ) ) {
				strcpy(tmp,s+Xstrlen(Xlit_list[i].raw) );
				strcpy(s,Xlit_list[i].done);
				strcat(s,tmp);
				s += Xstrlen(Xlit_list[i].done);
				sawone = 1;
			}
		}

		if( sawone) 
			sawone = 0;
		else
			s++;
	}
	
}


AlphStrcmp(char *s1, char *s2)
{
	char * p = s2;
	char tmp[MAXWORDSIZE];
	
	strcpy(tmp,s1);
	while(*p) {
		if( *p == 'a' && *(tmp+(p-s2)) == 'e' ) {
			*(tmp+(p-s2)) = 'a';
		}
		p++;
	}
	return(strcmp(tmp,s2));
}

char *pnametab[10000];
int pnames = 0;

init_pnametab()
{
	char line[BUFSIZ];
	int i = 0;

	if( pnames ) return;
	for(pnames=0;pnames<10000;pnames++) {
		if( ! fgets(line,sizeof line,fpnames) ) {
			if( pnames == 1 ) pnames = 0;
			break;
		}
		if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = 0;
		pnametab[pnames] = (char*) malloc((size_t)strlen(line)+1);
		strcpy(pnametab[pnames],line);
	}

}

is_propname(char *s)
{
	char line[BUFSIZ];
	int i = 0;
	
	if( ! pnames ) init_pnametab();
	if( ! pnames ) return(0);

	fseek(fpnames,0L,0);
	for(i=0;i<pnames;i++) {
		if( ! strcmp(s,pnametab[i]) ) return(1);
		if( ! AlphStrcmp(s,pnametab[i]) ) return(2);
	}
	return(0);

	fseek(fpnames,0L,0);
	while( fgets(line,sizeof line,fpnames) ) {
		line[Xstrlen(line)-1] = 0;
		if( ! strcmp(s,line) ) return(1);
		if( ! AlphStrcmp(s,line) ) return(2);
	}
	return(0);
}

