#include <greek.h>
#include <endtags.h>

#include "keyio.proto.h"

WriteKey(char *key, int *offp, FILE *f)
{
	int nwritten;

	if((nwritten=vax_fwrite(key,(size_t)sizeof * key, (int)KEYLEN,f)) <= 0 )
		return(nwritten);
	if((nwritten=vax_fwrite((char *)offp,(size_t)sizeof (* offp), 1,f)) <= 0 )
		return(nwritten);
	return(nwritten);
}

ReadKey(char *key, int *offp, FILE *f)
{
	int nread;

	if((nread=vax_fread(key,sizeof * key, (int)KEYLEN,f)) <= 0 ) {
		return(nread);
	}
	if((nread=vax_fread((char *)offp,sizeof * offp , 1,f)) <= 0 ) {
		return(nread);
	}
	return(nread);
}
