#include <gkstring.h>
#include <libfiles.h>
static OpenDerivFile(void);

static FILE * fsuff = NULL;
static int noderivfile = 0;

char * 
NextSuffTable(char *entry)
{
		if( ! fsuff ) {
			
			if(  noderivfile ) 
				return(NULL);
			if( ! OpenDerivFile() )
				return(NULL);
		}
		if( ! fgets(entry,MAXPATHNAME,fsuff) ) {
			fclose(fsuff);
			fsuff = NULL;
			return(NULL);
		}
		*(entry+strlen(entry)-1) = 0;
		return(entry);
}

static
OpenDerivFile(void)
{
	fsuff = MorphFopen(DERIVTYPES,"r");
	if( ! fsuff ) 
		noderivfile = 1;
	return( noderivfile == 0 );
}
