#include <gkstring.h>

#include "endio.proto.h"

WriteEnding(FILE *f, gk_string *gstr, int maxend)
{
	int32 max;

	max = maxend;

	localtrimwhite(gkstring_of(gstr),maxend);
	if(vax_fwrite(gkstring_of(gstr), sizeof * gkstring_of(gstr), maxend, f)< 0) 
		goto outputerr;
	if(vax_fwrite((char *)&forminfo_of(gstr), 
		sizeof forminfo_of(gstr), 1, f)< 0) 
			goto outputerr;
	if(vax_fwrite((char *)&dialect_of(gstr), 
		sizeof dialect_of(gstr), 1, f)< 0) 
			goto outputerr;
	if(vax_fwrite((char *)&geogregion_of(gstr), 
		sizeof geogregion_of(gstr), 1, f)< 0) 
			goto outputerr;
	if(vax_fwrite((char *)&stemtype_of(gstr), 
		sizeof stemtype_of(gstr), 1, f)< 0) 
			goto outputerr;
	if(vax_fwrite((char *)&derivtype_of(gstr), 
		sizeof derivtype_of(gstr), 1, f)< 0) 
			goto outputerr;

	if(vax_fwrite((char *)morphflags_of(gstr), 
		1, sizeof morphflags_of(gstr), f)< 0) 
			goto outputerr;

	if(vax_fwrite(domains_of(gstr), 
		1, sizeof domains_of(gstr), f)< 0) 
			goto outputerr;

	return(1);
	outputerr:
		fprintf(stderr,"output error!\n");
		return(-1);
}


ReadEnding(FILE *f, gk_string *gstr, int maxend)
{
	int nread = 0;
	if((nread=vax_fread(gkstring_of(gstr), sizeof * gkstring_of(gstr), maxend , f))<= 0)
		goto inputerr;
	if((nread=vax_fread((char *)&(forminfo_of(gstr)), 
		sizeof forminfo_of(gstr), 1, f))<= 0)
			goto inputerr;
	if((nread=vax_fread((char *)&(dialect_of(gstr)), 
		sizeof dialect_of(gstr), 1, f))<= 0)
			goto inputerr;
	if((nread=vax_fread((char *)&(geogregion_of(gstr)), 
		sizeof geogregion_of(gstr), 1, f))<= 0)
			goto inputerr;
	if((nread=vax_fread((char *)&(stemtype_of(gstr)), 
		sizeof stemtype_of(gstr), 1, f))<= 0)
			goto inputerr;
	if((nread=vax_fread((char *)&(derivtype_of(gstr)), 
		sizeof derivtype_of(gstr), 1, f))<= 0)
			goto inputerr;

	if((nread=vax_fread((char *)(morphflags_of(gstr)), 
		1, sizeof morphflags_of(gstr),  f))<= 0)
			goto inputerr;

	if((nread=vax_fread((char *)(domains_of(gstr)), 
		1, sizeof domains_of(gstr),  f))<= 0)
			goto inputerr;


	return(1);
	inputerr:
		if( nread < 0 ) {
			fprintf(stderr,"input error!\n");
		}
		return(nread);
}

/*
 * note that the size of maxstring when written in a file is 32 bits.
 * these routines make sure that, whether an int is 16 or 32 bits is
 * the size of a default int on the current system, we cast the value
 * to 32 bits.
 */
set_endheader(FILE *f, int maxstring)
{
#ifdef DECALPHA
	unsigned int morph_version;
	int len;
#else
	unsigned long morph_version;
	long len;
#endif

	morph_version = MORPH_VERSION;
#ifdef DECALPHA
	len = maxstring;
#else
	len = (long)maxstring;
#endif

	if( vax_fwrite((char *)&morph_version, sizeof morph_version,  1 , f ) < 0 )
		return(-1);
	if( vax_fwrite((char *)&len, sizeof len, 1, f ) )
		return(-1);
	return(1);
}

/*
 * return the number of endings in this particular file
 */
get_endheader(FILE *f, int *maxp)
{
#ifdef DECALPHA
	int morph_version;
	int len;
	int curpos, filelen;
	int endlen;
#else
	long morph_version;
	long len;
	long curpos, filelen;
	long endlen;
#endif
	int gstrsize = 0;

	int nendings;
	int unitsize;
	gk_string * fred;

	gstrsize = (int)( sizeof fred->gs_forminfo + sizeof fred->gs_steminfo + sizeof fred->gs_dialect + sizeof fred->gs_derivtype + sizeof fred->gs_geogregion + sizeof fred->gs_morphflags + sizeof fred->st_domains + sizeof fred->gs_gkstring);

	if( vax_fread((char *)&morph_version, sizeof morph_version,  1 , f ) < 0 )
		return(-1);
	if( morph_version != MORPH_VERSION ) {
		fprintf(stderr,"Hey! new version of Morpheus!\n");
		return(-1);
	}

	if( vax_fread((char *)&len, sizeof len, 1, f ) < 0 )
		return(-1);
	*maxp = (int) len;
	
	curpos = ftell(f);
	fseek(f,0L,2);
	filelen = ftell(f);
	fseek(f,curpos,0);

#ifdef DECALPHA
	unitsize = gstrsize - (sizeof gkstring_of(fred)) + *maxp /*- 1*/;
	endlen = filelen - (sizeof morph_version+ sizeof len);
	nendings = (int)(endlen / unitsize);
#else
	unitsize = (sizeof * fred) - (sizeof gkstring_of(fred)) + *maxp - 1;
	endlen = filelen - (long)(sizeof morph_version+ sizeof len);
	nendings = (int)(endlen / (long) unitsize);
#endif
#ifdef DECALPHA
	if( endlen % unitsize ) {
#else
	if( endlen % (long) unitsize ) {
#endif
printf("gstrsize %d endlen %d unitsize %d, mod %d, nendings %d filelen %ld\n", gstrsize, endlen, unitsize, ( endlen % unitsize ), nendings, filelen );
		fprintf(stderr,"Error in endio!\n");
		return(0);
	}
	return(nendings);
}

localtrimwhite(char *s,int n)
{
	int i;
	int sdone = 0;
	for(i=0;i<n;i++) {
		if(!*s) sdone=1;
		if(sdone) *s = 0;
		s++;
	}
	
}
