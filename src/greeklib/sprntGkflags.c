#include	<gkstring.h>

#include "sprntGkflags.proto.h"

/*
	Created:	04.24.92
	Author:		jjake
	This is essentially the SprintGKFlags routine, excpet I have modified it to accept
	a second delimiter for the lists of Dialects,regions,domains and morph names.
	
	modified:	04.29.92
	By:			jjake
	It seems that the attributes called stem_type,GeogRegionNames and DomainNames are
	always empty. Hence I am commenting those parts out. (This was deduced from running
	morphGrinder on all of Thucydides.
	
	modified: 	04.30.92
	By:			jjake
	I got the wrong fields. It seems that derivType is the empty one, and not stemtype, and
	furthermore that there is an extra tab somewhere. So Here goes…
*/
JakeSprintGkFlags(gk_string *gstr, char *buf, char *dels, char *more_dels, int pretty)
{
		char dialbuf[LONGSTRING*2];
		char * s;
		word_form wf;
					
		wf = forminfo_of(gstr);
		
		s=NameOfStemtype(stemtype_of(gstr));

/*		
		For some reason we are getting two tabs in arow here, and so we need to get
		rid of one for now.
		
		if( *s || *dels == '\t' )
			strcat(buf,dels);
			
*/
		if( * s ) {
			strcat(buf, NameOfStemtype(stemtype_of(gstr) ) );
		}

/*
		s=NameOfDerivtype(derivtype_of(gstr));
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, NameOfDerivtype(derivtype_of(gstr) ) );
		}
		
*/		s=NameOfTense(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf,s );
		}
		
		s=NameOfMood(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, s );
		}
		
		s=NameOfVoice(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, s );
		}
	
		s=NameOfGender(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, s );
		}
		
		s=NameOfCase(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, s );
		}

		s=NameOfDegree(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, s );
		}

		s=NameOfPerson(wf);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, s );
		}
		s=NameOfNumber(wf);		
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( * s ) {
			strcat(buf, NameOfNumber(wf ) );
		}

		dialbuf[0] = 0;
		DialectNames(dialect_of(gstr),dialbuf,more_dels);
		if( *s || *dels == '\t' )
			strcat(buf,dels);	
		if( dialbuf[0] ) {
			strcat(buf,dialbuf );
		}

/*SEE HEADER COMMENT:
 *		
 *		dialbuf[0] = 0;
 *		GeogRegionNames(geogregion_of(gstr),dialbuf,more_dels);
 *		if( *s || *dels == '\t' )
 *			strcat(buf,dels);
 *		if( dialbuf[0] ) {
 *			strcat(buf,dialbuf );
 *		}
 *		
 *		
 *		dialbuf[0] = 0;
 *		DomainNames(domains_of(gstr),dialbuf,more_dels);
 *		if( *s || *dels == '\t' )
 *			strcat(buf,dels);
 * 		if( dialbuf[0] ) {
 *			strcat(buf,dialbuf );
 *		}
 *	
 */		
		dialbuf[0] = 0;
		MorphNames(morphflags_of(gstr),dialbuf,more_dels,pretty);
		if( *s || *dels == '\t' )
			strcat(buf,dels);
		if( dialbuf[0] ) {
			strcat(buf,dialbuf );
		}
}

