#include <stdio.h>
#define LOCBUF 256

#include "endsinstr.proto.h"

/*
 * s1 ends with s2?
 */
ends_in(char *s1, char *s2)
 {
 	register char *p1;
 	register char * p2;
 	int n;
 	char tmp1[LOCBUF];
 	char tmp2[LOCBUF];
 	char b1[LOCBUF];
 	char b2[LOCBUF];
 	int i;
 	
 	strcpy(tmp1,s1);  s1 = tmp1;
 	strcpy(tmp2,s2);  s2 = tmp2;
 	
 	stripacc(tmp1); stripacc(tmp2);
 	stripdiaer(tmp1); stripdiaer(tmp2);
 	
 	if( (n=Xstrlen(s1)) > LOCBUF ) p1 = s1 + LOCBUF - 1;
 	else p1 = s1 + n - 1; 
 	
 	for(i=0;;i++) {
 		if(p1 < s1 )
 			break;
 		b1[i] = *p1--;
 	}
 	b1[i] = 0;
 	
 	if( (n=Xstrlen(s2)) > LOCBUF ) p2 = s2 + LOCBUF - 1;
 	else p2 = s2 + n - 1; 
 	
  	for(i=0;;i++) {
 		if(p2 < s2 )
 			break;
 		b2[i] = *p2--;
 	}
 	b2[i] = 0;

	return( Xstrncmp(b2,b1,Xstrlen(b2)) ? 0 : 1 );
 	
 }