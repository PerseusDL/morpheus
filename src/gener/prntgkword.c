#include <gkstring.h>

PrntGkWord(Gkword,gstring,fout)
gk_word * Gkword;
gk_string * gstring;
FILE * fout;
{
	int i;

printf("crasis [%s]\n", crasis_of(Gkword) );

	for(i=0;gkstring_of((gstring+i))[0];i++) {
		PrntAWord(gstring+i,Gkword,lemma_of(Gkword),fout);

/*
 * ayeee!
 * "pro/" plus "e)" goes both to "proe/" and "prou/", e.g.
 * you get both "proe/feron" and "prou/feron".
 * 
 * this kludge looks for such cases and makes sure that both forms
 * are generated.
 */
/*
		if( (! strcmp(preverb,"pro/") || ! strcmp(preverb,"pro")) && ! Xstrncmp(gkstring_of(gstring+i),"proe",XstrlenXstrlen("proe"))) {
			gkstring_of(gstring+i)[3] = 'u';	
			PrntAWord(gstring+i,Gkword,lemma_of(Gkword),fout);
		}
*/
	}
}

PrntAWord(gkform,Gkword,lemma,fout)
gk_word * gkform;
gk_word * Gkword;
char * lemma;
FILE * fout;
{
	char buf[BUFSIZ];
	char res[BUFSIZ];

	buf[0] = res[0] = 0;

	sprintf(buf,"$%s& ", workword_of(gkform));
	
printf("geog [%o]\n", geogregion_of(gkform) );

	SprintGkFlags(gkform,buf," ",1);

	if( Has_crasis(gkform)) {
		char tmp[MAXWORDSIZE];
		
		sprintf(tmp,"$%s& ", crasis_of(Gkword) ) ;
		Xstrncat(buf,tmp,BUFSIZ);
	}
	
	beta2smarta(buf,res);

	fprintf(fout,"%s\n", res );
	fflush(fout);

}

PrntAGstr(gstr,fout)
gk_string * gstr;
FILE * fout;
{
	char buf[512];
	char res[512];

	buf[0] = res[0] = 0;
	sprintf(buf,"$%s& ", gkstring_of(gstr));
	SprintGkFlags(gstr,buf," ",1);

	beta2smarta(buf,res);
	fprintf(fout,"%s\n", res );
	fflush(fout);
}

