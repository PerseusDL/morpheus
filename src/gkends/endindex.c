#include <gkstring.h>
#include <endindex.h>

#include "../morphlib/morphstrcmp.proto.h"
#include "endfiles.h"
#include "gkdict.h"
#define MAXENDTAGS 100

#include "endindex.proto.h"

long matchendtag();
/*int dictstrcmp(), dictstrncmp(), morphstrcmp(), morphstrncmp();*/

endind * DictEntTags = NULL;
static int ndictenttags = 0;

endind * CmpVbtags = NULL;
static int ncmpvbtags = 0;

endind * VbEtags = NULL;
static int nvbetags = 0;

endind * DerEtags = NULL;
static int nderetags = 0;

endind * NomEtags = NULL;
static int nnometags = 0;

endind * VstemEtags = NULL;
static int nvstemetags = 0;

endind * init_endind();

chcknend(char *endstr, char *keys)
{
	long startoff;
	char tmpendstr[MAXWORDSIZE+1];

	Xstrncpy(tmpendstr,endstr,(int)sizeof  tmpendstr);
	/*
	 * ignore '_' (long marker), so that a simple 'a' will match
	 * an "a_".
	 */
	stripquant(tmpendstr);
	
	if( ! NomEtags ) {
		NomEtags = (endind *) calloc((size_t)1, (size_t) sizeof * NomEtags);
		if( ! NomEtags ) {
			fprintf(stderr,"could not allcoate NomEtags\n");
			return(0);
		}
		init_endind(NENDLIST,NomEtags);
	}
	return( checkendind(NomEtags,tmpendstr,keys,morphstrncmp));
}


chckdictent(char * possent, char *keys)
{
	long startoff;
	char tmpendstr[MAXWORDSIZE+1];

	Xstrncpy(tmpendstr,possent,(int)sizeof  tmpendstr);
	/*
	 * ignore '_' (long marker), so that a simple 'a' will match
	 * an "a_".
	 */
	stripquant(tmpendstr);
	
	if( ! DictEntTags ) {
		DictEntTags = (endind *) calloc((size_t)1, (size_t) sizeof * DictEntTags);
		if( ! DictEntTags ) {
			fprintf(stderr,"could not allcoate DictEntTags\n");
			return(0);
		}
		init_endind(DICTENTLIST,DictEntTags);
	}
	return( checkendind(DictEntTags,tmpendstr,keys,strncmp));
}

chckcmpvb(char *endstr, char *keys)
{
	long startoff;
	char tmpendstr[MAXWORDSIZE+1];

	Xstrncpy(tmpendstr,endstr,(int)sizeof  tmpendstr);
	/*
	 * ignore '_' (long marker), so that a simple 'a' will match
	 * an "a_".
	 */
	stripquant(tmpendstr);
	
	if( ! CmpVbtags ) {
		CmpVbtags = (endind *) calloc((size_t)1, (size_t) sizeof * CmpVbtags);
		if( ! CmpVbtags ) {
			fprintf(stderr,"could not allcoate CmpVbtags\n");
			return(0);
		}
		init_endind(CMPVBLIST,CmpVbtags);
	}
	return( checkendind(CmpVbtags,tmpendstr,keys,strncmp));
}

chckend(char *endstring) 
{
	char tmp[LONGSTRING];

	tmp[0] = 0;

	return(chckvend(endstring,tmp)||chcknend(endstring,tmp));
}

chckvend(char *endstr, char *keys)
{
	long startoff;
	int curhit;
	
	if( ! VbEtags ) {
		VbEtags = (endind *) calloc((size_t)1, (size_t)sizeof * VbEtags);
		if( ! VbEtags ) {
			fprintf(stderr,"could not allcoate VbEtags\n");
			return(0);
		}
		init_endind(VENDLIST,VbEtags);
	}
	curhit = checkendind(VbEtags,endstr,keys,morphstrncmp);

	return(curhit);
}

chckvstem(char *stemstr, char *keys)
{
	long startoff;
	int curhit;
	
	if( ! VstemEtags ) {
		VstemEtags = (endind *) calloc((size_t)1, (size_t)sizeof * VstemEtags);
		if( ! VstemEtags ) {
			fprintf(stderr,"could not allcoate VstemEtags\n");
			return(0);
		}
		init_endind(VBINDEX,VstemEtags);
	}
	curhit = checkendind(VstemEtags,stemstr,keys,morphstrncmp);

	return(curhit);
}

chckdvend(char *endstr, char *keys)
{
	long startoff;
	int curhit;
	
	if( ! DerEtags ) {
		DerEtags = (endind *) calloc((size_t)1, (size_t)sizeof * DerEtags);
		if( ! DerEtags ) {
			fprintf(stderr,"could not allcoate DerEtags\n");
			return(0);
		}
		init_endind(DERENDLIST,DerEtags);
	}

	curhit = checkendind(DerEtags,endstr,keys,morphstrncmp);

	return(curhit);
}

endind *
init_endind(char *fname, endind *etags)
{
	FILE * f;
	register char * s;
	register char * t;
	char ** pp;
	long flen;
	int nread;
	long i;
	int j;
	int nlines = 0;
	long sofar = 0;

/*
 * grc 3/12/91
 * clalloc() seems not to exist in ANSI C
 	char * clalloc();
 */
 	if( (f=MorphFopen(fname,"r"))==NULL) {
		fprintf(stderr,"init_endind: could not open %s\n", fname );
		return( NULL );
	}
	fseek(f,0L,2);
	flen = ftell(f);
	fseek(f,0L,0);

/*
	if( !(endbuffer_of(etags) = clalloc(/*(int)*flen + 1,(long) sizeof * endbuffer_of(etags)  ))) {
*/
	if( !(endbuffer_of(etags) = (char *)calloc((size_t)flen + 1, (size_t)sizeof * endbuffer_of(etags)  ))) {

		fprintf(stderr,"could not build buffer for endtags\n");
		return(NULL);
	}
	s = endbuffer_of(etags);
	for(;;) {		
/*
	nread = vax_fread(s,(int)sizeof  * s, (int)flen, f);
*/
		nread = vax_fread((char *)s+sofar,sizeof  * s, BUFSIZ, f);
		if( nread <= 0 ) break;
		sofar += (long)nread;
	}
	for(i=0;i<sofar;i++) {
		if(*(s+i) == '\n' )
			nlines++;
	}
	nlines++;

  	endeptr_of(etags) = (char **) calloc((size_t)nlines,(size_t)sizeof * endeptr_of(etags));
	if( ! endeptr_of(etags) ) {
		fprintf(stderr,"ran out of memory in init_endind\n");
		return(NULL);
	}
	pp = endeptr_of(etags);
	for(i=0;i<nlines;i++) {
		*(pp+i) = s;
		while(*s && *s != '\n')
			s++;
		if( ! *s ) 
			break;
		else if( *s == '\n' ) {
			*s = 0;
			s++;
		}
	}

	endlen_of(etags) = nlines;
/*
	printf("nread %d flen %ld nlines %d\n", nread ,flen , nlines);
	for(i=0;i<10;i++)
		printf("%d) [%s]\n", i , *(pp+i) );
	getchar();
*/
	return(etags);
}

checkendind(endind *etags, char *endstr, char *keys, int (*scmp )())
{
	int high = 0;
	int low = 0;
	int mid = 0;
	int comp;
	int i, ntags;
	char curtag[MAXWORDSIZE];
	size_t taglen;
	char ** pp;
	
	/*
	 * the table is of the form "ending<SPACE>key1<SPACE>key2<SPACE> ..."
	 */
	Xstrncpy(curtag,endstr,MAXWORDSIZE);
	Xstrncat(curtag," ",MAXWORDSIZE);
	taglen = strlen(curtag);
	
	ntags = endlen_of(etags);
	pp = endeptr_of(etags);

	high = ntags-1;
	low = 0 ;
	
	while( low<=high ) {
		mid = (low+high)/2 ;
		/*comp = morphstrncmp( curtag , *(pp+mid) , taglen );*/
		comp = (*scmp)( curtag , *(pp+mid) , taglen );
/*
fprintf(stderr,"comparing [%s] and [%s]\n", curtag , *(pp+mid) );
*/
		if( comp < 0 ) 
			high = mid - 1 ;
		else if ( comp > 0 )
			low = mid + 1;
		else  { /* found match */
/*
printf("A returning with curtag [%s] tagstring [%s]\n", curtag, *(pp+mid) );
*/
			Xstrncpy(keys,*(pp+mid) + taglen,LONGSTRING);
			return(1);
		}
	}
/*	if( mid > 0 ) {
		for(i=mid-1;i<ntags;i++) {
			if( morphstrcmp(curtag,tagstring_of(etags+i)) < 0 ) break;
		}
		if( i > 0 ) i--;
	} else
		i = 0;
		*/
/*
printf("B returning with curtag [%s] tagstring [%s] and off %d\n", curtag, tagstring_of(etags+i) , tagoffset_of(etags+i) );
*/
	*keys = 0;
	return(0);
}


