#include <gkstring.h>
#include "endfiles.h"
#define MAX_END_TABLE	12000
char ** endlines;
static int endcount = 0;
gk_string Gstr;
static gk_string Blnk;
static int xstrcmp();
#define DELIMITER " "

#include "countendtables.proto.h"

countendtables(Stemtype stype, int is_deriv)
{

	int index = 0;
	int i;
	int nends = 0;
	int totends = 0;
	char * curtable, *basen, * dirp;
	char shortname[LONGSTRING];
	char curderivname[LONGSTRING];
	char tmp[LONGSTRING*8];
	char prevtag[LONGSTRING];
	char prevkey[LONGSTRING];
	char curtag[LONGSTRING];
	char savestr[LONGSTRING];
	char markedstr[MAXWORDSIZE];
	gk_string Gstr;
	FILE * finput, *foutput;
	int maxstring = 0;
	int ntypes = 0;
	char * typestr;
	char * NextEndTable(), *NextSuffTable();
	
	if( is_deriv ) 
		dirp = DERIVTABLEDIR;
	else
		dirp = ENDTABLEDIR;
	
	endlines = (char **) calloc(MAX_END_TABLE,sizeof *endlines);
	
/*
	while( (curtable=NextEndTable(&index,stype))) {
*/
	for(;;) {
		if( is_deriv ) {
			gk_string * gstring;
			gk_word * tmpGkword;
			int rconj;
		
			curtable = NextSuffTable(tmp);
			nextkey(tmp,curderivname);
			if( ! curtable ) break;
			curtable = curderivname;
			gstring = CreatGkString(1);
			tmpGkword = CreatGkword(1);
			ScanAsciiKeys(curtable,tmpGkword,gstring,NULL);
			rconj = Is_regconj(gstring);
			
			FreeGkString(gstring);
			FreeGkword(tmpGkword);
			if( ! rconj ) {
				printf("[%s] not a regular conj\n", curtable );
				continue;
			}
		} else 
			curtable=NextEndTable(&index,stype);
		if( ! curtable ) break;
		
	/*
		printf("about to compile [%s]\n", curtable );
	*/
		sprintf(shortname,"%s%cout%c%s.out", dirp, DIRCHAR, DIRCHAR, curtable );

		if(! (finput=MorphFopen(shortname,"rb"))) {
			continue;
		}
		Gstr = Blnk;	
		nends = get_endheader(finput,&maxstring);
		totends += nends;
		ntypes++;
		ReadEnding(finput,&Gstr,maxstring);
		if( (stemtype_of(&Gstr)&NOUNSTEM) ) typestr = "noun";
		else if( (stemtype_of(&Gstr)&ADJSTEM) ) typestr = "adj";
		else typestr = "verb";
		printf("%s\t%s\t%d\t%d\n", curtable, typestr,  nends, totends );
		
		fclose(finput);
	}

	printf("grand total: %d types %d endings\n",ntypes, totends );
}

xstrcmp(char **p1, char **p2)
{
	int rval;
	
	rval = morphstrcmp(*p1,*p2);

/*
fprintf(stderr,"rval [%d] for [%s] and [%s]\n", rval  , *p1, *p2 );
*/
	return(rval);
}
