#include <contract.h>

#include "loadeuph.proto.h"

gk_string * Euph_table;
gk_string *
load_euph_tab(char *filename, int *gotno, int is_contr)
{
	int nunits;
	FILE * f;
	int i;
	char * s;
	char * raw;
	char * cooked;
	char line[BUFSIZ];
	char tmpa[MAXWORDSIZE];
	char tmp[MAXWORDSIZE];
	gk_string CurStr;
	gk_word * TmpGkword;
	int RevCompByStr();


	if( (f=MorphFopen(filename,"r")) == NULL ) {
		fprintf(stderr,"Could not open [%s]\n", filename );
		return(NULL);
	}
	TmpGkword = CreatGkword(1);
	
	nunits = count_rlines(f);
	
	Euph_table = CreatGkString(nunits+1);
	if( ! Euph_table ) {
		fprintf(stderr,"no memory for %d big Euph_table\n", nunits+1 );
		xFclose(f);
		FreeGkword(TmpGkword);
		return(NULL);
	}

	for(i=0;GetTableLine(line,sizeof line,f);i++) {
		if( i >= nunits) {
			printf("hey! more than %d contracts!\n", nunits);
			xFclose(f);
			FreeGkword(TmpGkword);
			return(NULL);
		}
		CurStr = Blnk;
		s = gkstring_of(&CurStr);
/*
printf("line:%s\n", line );
*/
		nextkey(line,s);
		nextkey(line,s+MAXSUBSTRING);
		/*
		 * if raw and cooked are the same then we hit an infinitely
		 * recursive loop. mark cooked with a diaeresis if it is the same as raw so
		 * that this will not happen.
		 */
		 raw = s;
		 cooked = s+MAXSUBSTRING;

		 if( ! Xstrncmp(raw,cooked,Xstrlen(raw)) && Xstrlen(raw) > 1 && is_contr == YES) {
				
		 		tmp[0] = *cooked;
		 		tmp[1] = '+';
		 		tmp[2] = 0;
		 		Xstrncat(tmp,cooked+1,MAXWORDSIZE);
		 		Xstrncpy(cooked,tmp,MAXWORDSIZE);

		 }
		set_morphflag(morphflags_of(prvb_gstr_of(TmpGkword)),0);
		ScanAsciiKeys(line,TmpGkword,&CurStr,NULL);
/*
		InsertGstr(Euph_table,&CurStr,i,strcmp,YES);
*/
		add_morphflags(&CurStr,morphflags_of(prvb_gstr_of(TmpGkword)));
		*(Euph_table+i) = CurStr;
	}
	* gotno = i;

/* 
 * grc 12/15/96
 *
 * took this out because it was sorting "ds -> ss epic" before "ds --> s"
 * 
 * The default future of yeu/dw was "yeu/ssw epic".
 * 
 * You now need to set the sort order in the file -- not ideal.
 *
	qsort(Euph_table,(size_t)i,(size_t)sizeof * Euph_table,RevCompByStr);
*/

/*
for(i=0;i<*gotno;i++) printf("%d) [%s] [%s]\n", i, gkstring_of(Euph_table+i),
gkstring_of(Euph_table+i)+MAXSUBSTRING );
*/
	xFclose(f);
	FreeGkword(TmpGkword);
	return(Euph_table);
}

count_rlines(FILE *f)
{
	char line[BUFSIZ];
	int nlines = 0;

	while(GetTableLine(line,sizeof line,f)) {
		nlines++;
	}
	fseek(f,0L,0);
	return(nlines);
}
