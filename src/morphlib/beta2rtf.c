#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libfiles.h"
#define SEGSIZE 100000
#define MAXDOMAINS 256

#include "beta2rtf.proto.h"

char * domlist[MAXDOMAINS];
char lastdom[BUFSIZ];

_main(int argc, char *argv[])
{
	 char line[BUFSIZ*6];
	FILE * f, *MorphFopen();
	char fname[BUFSIZ];
	char basename[BUFSIZ];
	char outfname[BUFSIZ];
	 char *p;
	FILE *fout = stdout;
	long nfile = 0;
	long ftell();
	int i = 0;
	unsigned char result[BUFSIZ*6];
	
	
	sprintf(basename,"%s", argv[1]);
	sprintf(outfname,"%s.rtf", basename );
	if( ! (fout=fopen(outfname,"w")) ) {
		fprintf(stderr,"could not open [%s]\n", outfname );
		exit(-1);
	}

	if( ! (f=fopen("rtfhead","r")) ) {
		fprintf(stderr,"could not open rtfhead!\n");
		fprintf(stderr,"place a copy of the file \"rtfhead\" into this folder!\n");
		exit(-1);
	}
	
	while(fgets(line,sizeof line ,f)) {
		fprintf(fout,"%s", line );
	}
	fclose(f);
	if( ! (f=fopen(basename,"r")) ) {
		fprintf(stderr,"could not open [%s]\n", basename );
		exit(-1);
	}
	while(fgets(line,sizeof line,f)) {
		if( isspace(line[0]) || line[0] == '?' || line[0] == '#' ) {
/*			fprintf(fout,"\\par\n");*/
			continue;
		}
		p = line + strlen(line)-1;
		if( *p == '\n' ) *p = 0;
		conv_defline(line,fout);
/*
		beta2smk(line,result);

		fprintf(fout,"{%s\\par}\n", result );
*/		

	}
	fclose(f);
/*
	fclose(fout);
*/
}

conv_defline(char *s, FILE *fout)
{
	char res1[128], res2[128], result[BUFSIZ*6];
	char * introp;
	int levnum;
	
	res1[0] = 0;
	introp = "";
	
	if( has_pref(s,":dnum") ) {
		
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) s++;
		
		

		levnum = check_deflev(s,res1,sizeof res1);
		set_roman();
		beta2smk(res1,res2);
		strcat(res2,"\t");
		if (levnum == 2 )
			introp = "\\s2\\fi-510\\li1134\\sb80\\sa80\\tx1134 \\f20";
		else if( levnum == 3 ) 
			introp = "\\s3\\fi-539\\li1701\\sb60\\sa60\\tx1729 \\f20";
		else if( levnum == 4 ) 
			introp = "\\s4\\fi-510\\li652\\sb80\\sa80\\tx652 \\f20";
		else if( levnum == 5 ) 
			introp = "\\s5\\fi-539\\li2296\\sb80\\sa80\\tx2296 \\f20";
		else if( levnum == 9 )  {
			introp = "\\s9\\sb60\\sa60 \\f20";
			strcpy(res2,"");
		}
		fprintf(fout,"\\pard\\plain{%s {%s",  introp, res2 );

		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) s++;

		beta2smk(s,result);
		fprintf(fout,"%s}\\par\\pard\\plain}\n",  result );
		return;
	}
	if( has_pref(s,":xref") ) {
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) s++;
		
		beta2smk(s,result);
		fprintf(fout,"\\s6{%s}\\par\\pard\\plain\n", result );
		return;
	}
	if( has_pref(s,":le:") || has_pref(s,":cv:")  ) {
		*(s+3) = '$';
		beta2smk(s+3,result);

		fprintf(fout,"\\s7\\sb160 \\b\\f20\\fs24{%s}\\par\\pard\\plain\n", result);
		return;
	}
	if( has_pref(s,":comm") ) {
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) s++;
		
		beta2smk(s,result);
		fprintf(fout,"\\s8{%s}\\par\n", result );
		return;
	}

	fprintf(fout,"%s\\par\n", s );
}

check_deflev(char *p, char *res, int len)
{
	char * s;
	
	if( *p == '[' ) p++;
	if( *p == '&' ) p++;
	strncpy(res,p,len);

	s = res;
	
	while(*s&&*s!=']') s++;
	*s = 0;
	s = res;
	
	if( * res == '0' ) return(9);
	if( *res ==  '*' ) {
		res++;
		if( *res == 'i' || * res == 'v' ) return(2);
		if( isalpha(*res) ) return(4);
		return(0);
	}
	if( isdigit(*res) ) return(3);
	if( isalpha(*res) ) return(5);
	
	return(0);
}

has_pref(char *s, char *prefs)
{
	return(!strncmp(s,prefs,strlen(prefs)));
}


is_greek(char *s)
{
	int n = 0;
	
	while(*s&&!isspace(*s)) {
		switch(*s) {
			case '=':
			case '/':
			case '\\':
				return(1);
				break;
			default:
				break;
		}
		s++;
	}
	return(0);
}
