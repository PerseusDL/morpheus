#include <gkstring.h>
#include "endfiles.h" 
#define ENDCACHESIZE 45

#include "getcurrend.proto.h"
static int curecache = 0;
static int prevcache = 0;

gk_string * EndingCache[ENDCACHESIZE+1];

gk_string * CreatGkString();
gk_string * CheckEndCache();

gk_string *
GetCurrentEndList(gk_string *gstr, int *lnump)
{
	char fname[MAXPATHNAME];
	gk_string * CurEndList;
	FILE * f  = NULL;
	int maxend = 0;
	int rval;
	int i = 0;
	int lno = 0;
	
	CurEndList = CheckEndCache(gstr);

	if( CurEndList) {
		for(i=0;;i++) {
			if( ! gkstring_of(CurEndList+i)[0] ) break;
		}
		*lnump = i;
		return(CurEndList);
	}

	sprintf(fname,"%s/out/%s.out", ENDTABLEDIR , NameOfStemtype(stemtype_of(gstr)) );

	if( (f=MorphFopen(fname,"rb")) == NULL ) {
		fprintf(stderr,"stemtype %o, could not open %s\n", stemtype_of(gstr), fname );
		return(NULL);
	}

	lno = get_endheader(f,&maxend);
	if( lno < 0 ) {
		fprintf(stderr,"problem with endfile [%s]\n", NameOfStemtype(stemtype_of(gstr)) );
		xFclose(f);
		f = NULL;
		return(NULL);
	}

/*
printf("opening %s %d %d %ld\n", NameOfStemtype(stemtype_of(gstr)), curecache , lno, 
(long) (lno * (sizeof *gstr - (sizeof gkstring_of(gstr) + maxend ) )) );
*/
	
	*lnump = lno;
	CurEndList = (gk_string *) CreatGkString( lno + 2 );

	if( ! CurEndList ) {
		fprintf(stderr,"Out of memory loading in %d new endings!\n", lno+2);
		xFclose(f);
		f = NULL;
		exit(-21);
		return(NULL);
	}

	for(i=0;i<lno;i++ ) {
		rval=ReadEnding(f,CurEndList+i,maxend);
		set_stemtype(CurEndList+i,stemtype_of(gstr));

		if (rval <= 0 ) {
			fprintf(stderr,"hey! fname [%s] wanted [%d] endings got [%d]!\n", fname, lno , i );
			xFclose(f);
			f = NULL;
			return(NULL);
		}
	}
/*
fprintf(stderr,"about to close %s\n", NameOfStemtype(stemtype_of(gstr)) );
*/
	xFclose(f);
	f = NULL;

	InsertEndCache(CurEndList);
	return(CurEndList);
}

static int csize = 0;

gk_string *
CheckEndCache(gk_string *gstr)
{
	int i;
	
	
cacheconsistent();

	for(i=0;i<ENDCACHESIZE;i++) {
		if(! EndingCache[i] ) break;
		if( stemtype_of(EndingCache[i]) == stemtype_of(gstr)) 
			return(EndingCache[i]);
	}
	return(NULL);
}

cacheconsistent(void)
{
	int i;
	
	for(i=0;i<ENDCACHESIZE;i++) {
		if( ! EndingCache[i] ) break;
		if( ! NameOfStemtype(stemtype_of(EndingCache[i])) ) {
			if( i > 1 ) 
				printf("%d) prev type %s\n", i, 
				NameOfStemtype(stemtype_of(EndingCache[i-1])) );
			else
				printf("first stemtype has been zapped!\n");
			break;
		}
	}
	if( i < csize ) {
		printf("saw only %d of %d ending tables\n", i , csize );
	} else
		csize = i;
	
}
InsertEndCache(gk_string *gstr)
{
	int i;
	
	if( EndingCache[curecache] ) {
		FreeGkString(EndingCache[curecache] );
		EndingCache[curecache] = NULL;
/*
printf("dumping %s curc %d\n", NameOfStemtype(stemtype_of(EndingCache[curecache])) ,
curecache);
*/
	}

	EndingCache[curecache] = gstr;

	prevcache = curecache;
	if( ++curecache >= ENDCACHESIZE ) curecache = 0;
}
