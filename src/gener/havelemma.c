#include <gkstring.h>
#define LEMMAFILE "vlist"
static int firstshot = 1;
/*
char * calloc();
*/
char ** lemmentries = NULL;
static	int nlines = 0;
int xstrcmp();

checkforlemma(lemmastr)
char * lemmastr;
{
	int rval;
	char tmplemm[MAXWORDSIZE];
	
	if( ! lemmentries ) 
		if( ! init_lemmentries() ) return(0);
	strcpy(tmplemm,lemmastr);
	stripquant(tmplemm);
	stripdiaer(tmplemm);

	rval = binlook( lemmentries , tmplemm , nlines , sizeof * lemmentries , 1 , xstrcmp);

	return(rval);
}

init_lemmentries()
{
	FILE * flemm;
	char line[LONGSTRING], *p;
	int i;

	if( (flemm=fopen(LEMMAFILE,"r")) == NULL ) {
		if( firstshot )
			fprintf(stderr,"could not open [%s]\n", LEMMAFILE );
		firstshot = 0;
		return(0);
	}
	
	while(fgets(line,sizeof line,flemm)) {
		nlines++;
	}
	lemmentries = (char **) calloc(nlines+1,sizeof *lemmentries);
	
	fseek(flemm,0L,0);
	
	for(i=0;fgets(line,sizeof line,flemm);i++) {
		*(lemmentries+i) = (char *)calloc(strlen(line)+1,sizeof **lemmentries);
		
		p = &line[strlen(line)-1];
		while(isspace(*p)&&p>line) *p-- = 0;  /* zap newline */
		strcpy(*(lemmentries+i),line);
	}
/*
	fprintf(stderr,"%d lemmas first %s last %s\n", 
		nlines, *lemmentries , *(lemmentries+nlines-1));
*/
	fclose(flemm);
	return(1);

}

xstrcmp(p1,p2)
  char * p1;
  char ** p2;
{
	int rval;
	
	rval = strcmp(p1,*p2);
/*
fprintf(stderr,"rval [%d] for [%s] and [%s]\n", rval  , *p1, *p2 );
*/
	return(rval);
}
