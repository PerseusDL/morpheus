/*
 * this program compiles a table of Greek endings.
 *
 * first it expands any macros that are in the tables: thus, "omen@adj1" get turned into "o/menos"
 * 	"ome/nou" "ome/nw|" etc.
 *
 * then, it sorts the resulting endings according to the ascii lexical sort weights of the endstrings:
 *	thus, "w" gets placed after "eis".
 */
#include <gkstring.h>
#include "endfiles.h"
#include "compostypes.h"

#include "expendtable.proto.h"
gk_string * CreatGkString();
static gk_string Blnk;

 expendtables(char *tabname, int maintable, int formcode)
{
	FILE * finput;
	FILE * foutput;
	char line[BUFSIZ];
	char shortname[MAXWORDSIZE];
	char fname[MAXPATHNAME];
	char inpfname[MAXPATHNAME];
	char outfname[MAXPATHNAME];
	char curendstr[MAXWORDSIZE];
	int maxstring = 0;
	char basename[MAXWORDSIZE];
	char * typep;
	char *s;
	gk_string TmpGstr;
	Stemtype stype;

	
	/*
	 * deal with things like Unix relative path names
	 */
	s = tabname;
	while(*s) s++;
	s--;
	while( (s>tabname) && (*s != DIRCHAR) ) {
		s--;
	}

	if( maintable ) {
		if( *s == DIRCHAR ) s++;
		strcpy(fname,s);
		strcpy(basename,s);
/*
		if( formcode == DODERIV ) strcat(basename," is_deriv"); 
		else if( formcode == DOWORD ) strcat(basename," indeclform"); 
*/	
		TmpGstr = Blnk;
		stype = 0;
		
		if( formcode == DODERIV ) {
			
			add_morphflag(morphflags_of(&TmpGstr),IS_DERIV);
			sprintf(shortname,"%s.deriv", fname );
			if(! (finput=fopen(shortname,"r"))) {
				sprintf(shortname,"derivs%csource%c%s.deriv",  DIRCHAR, DIRCHAR, fname );
				if(! (finput=MorphFopen(shortname,"r"))) {
					printf("could not open [%s.deriv] or [%s]\n", fname,  shortname );
					return(-1);
				}
			sprintf(shortname,"%s%cout%c%s.out", DERIVTABLEDIR,DIRCHAR, DIRCHAR, fname );
			}
		} else {
			gk_word * TmpGkword;
			
			TmpGkword = CreatGkword(1);
			ScanAsciiKeys(basename,TmpGkword,&TmpGstr,NULL);
			FreeGkword(TmpGkword);
			
			stype = stemtype_of(&TmpGstr);

			sprintf(shortname,"%s.end", fname );
			if(! (finput=fopen(shortname,"r"))) {
				sprintf(shortname,"endtables%csource%c%s.end",  DIRCHAR, DIRCHAR, fname );
				if(! (finput=MorphFopen(shortname,"r"))) {
					printf("could not open [%s.end] or [%s]\n", fname,  shortname );
					return(-1);
				}
			}
			sprintf(shortname,"%s%cout%c%s.out", ENDTABLEDIR,DIRCHAR, DIRCHAR, fname );
		}
			
	
		if(! (foutput=MorphFopen(shortname,"wb"))) {
	/*		fprintf(stderr,"could not open %s for writing\n", shortname );*/
			fclose(finput);
			return(-1);
		}
	} else {
		strcpy(fname,s);
		basename[0] = 0;
		if(! (finput=fopen(fname,"r"))) {
			fprintf(stderr,"could not open %s for reading\n", fname );
			fclose(finput);
			return(-1);
		}
	}
	if( formcode == DODERIV ) strcat(basename," is_deriv"); 
	else if( formcode == DOWORD ) strcat(basename," indeclform"); 
	
	if( ! InitGstrMem() )  {
		fprintf(stderr,"Could not allocate storage for ending array\n" );
		exit(-1);
	}

	while(fgets(line,sizeof line,finput) ) {
		if( is_blank(line) )
			continue;
		if( Is_comment(line) )
			continue;
		nextkey(line,curendstr);
		if( strlen(curendstr) >= maxstring && strlen(curendstr) <= MAXENDSTRING )
			maxstring = strlen(curendstr)+1;
	}
	

	fseek(finput,0L,0);
	while(fgets(line,sizeof line,finput) ) {
		char tmp[BUFSIZ];

		if( is_blank(line) )
			continue;
		if( Is_comment(line) )
			continue;

/*
		if( maintable ) {
			if( AddEndLine(/*foutput,*line,basename,maxstring) < 0 )

				break;
		} else {
*/
/*
fprintf(stderr,"basenam [%s] line [%s]\n", basename , line );
*/
			if( AddEndLine(/*foutput,*/line,basename,maxstring) < 0 )
				break;
/*
		}
*/
	}

	fclose(finput);
	if( maintable && formcode != DOWORD ) {
		PrntNewGstrings(foutput,1);
		if( foutput != stdout )
			fclose(foutput);
	}
	
	sprintf(shortname,"%s%cascii%c%s.asc", formcode == DODERIV? DERIVTABLEDIR : ENDTABLEDIR,DIRCHAR, DIRCHAR, fname );
printf("%s\n", shortname );
	if( (foutput=MorphFopen(shortname,"w")) == NULL ) {
		fprintf(stderr,"Could not open [%s]\n", shortname );
	} else {
		PrntNewGstrings(foutput,0);
		fclose(foutput);
	}
	if( stype & ADJSTEM ) stype |= NOUNSTEM;
	else if( stype & NOUNSTEM ) stype |= ADJSTEM;
/*
	indexendtables(stype);
*/

}

AddEndLine(/*FILE *f,*/ char *el, char *basename, int maxstring)
{
	char havestr[MAXWORDSIZE];
	gk_string * Have;
	gk_string * Avoid;
	gk_word * TmpGkword;

	Have = CreatGkString(1);
	Avoid = CreatGkString(1);
	TmpGkword = CreatGkword(1);

	nextkey(el,havestr);
	ScanAsciiKeys(basename,TmpGkword,Have,Avoid);
	ScanAsciiKeys(el,TmpGkword,Have,Avoid);
/*
printf("indeclform %d %d\n",  has_morphflag(morphflags_of(TmpGkword),INDECLFORM),
has_morphflag(morphflags_of(Have),INDECLFORM) );
*/
	set_gkstring(Have,havestr);

/*printf("[%s] [%s]\n", havestr, basename );*/
	mk_end(havestr,Have,Avoid);

	FreeGkString(Have);
	FreeGkString(Avoid);
	FreeGkword(TmpGkword);
	return(1);
}
