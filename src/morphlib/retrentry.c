#include <gkstring.h>
#include <endtags.h>
#define LINDEXSUFFIX "lindex"

#include "retrentry.proto.h"
#include "morphstrcmp.proto.h"
/*
long fseek();
long ftell();
*/
int morphstrcmp();
FILE * MorphFopen();
	
endtags *
init_preind(char *fname, int *maxkeys)
{
	FILE * f;
	endtags * etags;
	register char * s;
	register char * t;
	int flen;
	long divisor = 0;
	int i, j;
	char tmp[LONGSTRING];


	sprintf(tmp,"%s.%s", fname , LINDEXSUFFIX );
	
	if( (f=MorphFopen(tmp,"rb"))==NULL) {
		fprintf(stderr,"init_preind: could not open %s\n", tmp );
		return( NULL );
	}
	
	fseek(f,0L,2);
	divisor = (long) KEYLEN + (sizeof tagoffset_of(etags));
	flen = (int)(ftell(f)/divisor);

	fseek(f,0L,0);
	*maxkeys = flen;
	etags = (endtags *) calloc((size_t)flen + 1,(size_t) sizeof * etags );

	for(i=0;  i < flen/*+1*/; i++) {
		if( ! ReadKey(tagstring_of(etags+i),&tagoffset_of(etags+i),f))
			break;
/*
if( ! (i % 25) )
printf(" i %d last tags [%s]\n",  i , tagstring_of(etags+i) );
*/
	}
/*
printf("flen %d i %d last tags [%s]\n", flen, i , tagstring_of(etags+i) );
*/
	fclose(f);
	return(etags);
}

long
ChckPreIndex(endtags *etags, char *tag, int ntags, int exact_match, int (*scmp )())
{
	int rval;
	long roff;
	char curtag[KEYLEN+1];
	
	if( Xstrlen(tag) > KEYLEN ) exact_match = NO;
	strncpy(curtag,tag,KEYLEN);
	curtag[KEYLEN] = 0;
	rval = binlook( (char *)etags , curtag , ntags , (int)sizeof *etags , exact_match ,scmp );
	if( rval < 0 )
		return((long) -1 );

	if( ! rval )
		roff = 0;
	else
		roff = tagoffset_of(etags+rval);
	
return( roff  );
}


ChckFullIndex(char *s, char *keys, char *fname, long offset, int (*scmp )())
{
	FILE * f;
	register char * a;
	char buf[BUFSIZ*4];
	size_t slen;
	int comp;
	int rval = 0;
	int i;
int firstline = 1;

	*keys = 0;

	if( (f=MorphFopen(fname,"r"))==NULL) {
		fprintf(stderr,"ChckFullIndex(): could not open:%s\n", fname );
		return( -1 );
	}
	fseek(f,offset,0);
/*
printf("starting off at %ld\n", offset);
*/
	slen = strlen(s);
	while(fgets(buf,(int)sizeof buf , f)) {

/*
 * this little dance splits the line into two parts, the initial
 * key and everthing that follows. if you do not null terminate that
 * initial string one way or another, you end up having a string
 * such as "basile" get matched against "basileu"
 */



/*
		comp = morphstrncmp(s,buf,slen);
*/
		comp = (*scmp)(s,buf,slen);

/*
if( firstline ) {
fprintf(stderr,"starts comp [%d] s [%s] buf [%s]\n", comp , s , buf );
firstline = 0;
}
*/
		if( ! comp && isspace(*(buf+slen)) ) {
			a = buf+slen;
			while(isspace(*a)) a++;
			Xstrncpy(keys,a,LONGSTRING);
			rval = 1;
			break;
		} else if (comp < 0 ) {
			rval = 0;
			break;
		}
	}
/*
fprintf(stderr,"ends comp [%d] s [%s] buf [%s]\n", comp , s , buf );
getchar();
*/
	finish:
		fclose(f);
		return(rval);
}
