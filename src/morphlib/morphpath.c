#include <gkstring.h>

#include "morphpath.proto.h"
static filesopened = 0;

FILE *
 MorphFopen(char *fname, char *mode)
{
 	FILE * f;
 	char tmpname[BUFSIZ];

 	filesopened++;
 	MorphPathName(fname,tmpname);

 	if( !(f=fopen(tmpname,mode)) ) {
 		fprintf(stderr,"MorphFopen: could not open [%s]\n", tmpname );
/* just die here -- should go up higher but will live with this for now. */

/*
 		return(NULL);
*/
 	}
 	
	return(f);
}

NumFilesOpened(void)
{
	printf("filesopened [%d]\n", filesopened );
}

/*
 * take a short pathname (e.g. "lib/vowcontr.table") and derive from it a
 * full path name (e.g. "/usr/src/local/morpheus/lib/vowcontr.table")
 */
static char volName[128];

MorphPathName(char *shorts, char *full)
 {
 	char * s;
 	short vRefNum;
 
 	
#ifdef MACINTOSH
 	if( ! volName[0] ) {
 		GetVol((StringPtr) volName, &vRefNum);
 		PtoCstr((StringPtr)volName);
 	}
#endif
 	
/*
 	sprintf(full,"/as/fass/faculty/gcrane/morph/stemlib/%s", shorts );
*/
	s = getenv("MORPHLIB");

	if( ! s ) {
		printf("MORPHLIB not set in your environment!\n");
		return;
	}
	
	if( cur_lang() == LATIN ) 
		sprintf(full,"%s/Latin/%s", s , shorts );
	else if ( cur_lang() == ITALIAN ) 
		sprintf(full,"%s/Italian/%s", s , shorts );
	else
		sprintf(full,"%s/Greek/%s", s , shorts );
	
 	/*
 	 * this checks to make keep compatibility with the Mac
 	 * pathname conventions
 	 */
	if( DIRCHAR != '/' ) {
		s=full;
		while(*s) {
			if( *s == '/' ) *s = DIRCHAR;
			s++;
		}
	} else if (DIRCHAR == '/' ) {
		s=full;
		while(*s) {
			if( *s == ':' ) *s = DIRCHAR;
			s++;
		}
	}
 }
 
 
SysFolderFile(char *fullname, char *shorts)
 {
 	char * s;
 	short vRefNum = 0;
 	char vName[128];
 	
#ifdef MACINTOSH
 	GetVol((StringPtr)vName,&vRefNum);
 	PtoCstr((StringPtr)vName);
  	
 	sprintf(fullname,"%s:[System Folder]:%s",volName, shorts );
#endif
	
 	/*
 	 * this checks to make keep compatibility with the Mac
 	 * pathname conventions
 	 */
	if( DIRCHAR != '/' ) {
		s=fullname;
		while(*s) {
			if( *s == '/' ) *s = DIRCHAR;
			s++;
		}
	}
 }
