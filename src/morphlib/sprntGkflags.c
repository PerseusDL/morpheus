#include	<gkstring.h>

#include "sprntGkflags.h"

/*
  Created:	04.24.92
  Author:		jjake
  This is essentially the SprintGKFlags routine, excpet I have modified it to accept
  a second delimiter for the lists of Dialects,regions,domains and morph names.
	
*/
JakeSprintGkFlags(gk_string *gstr, char *buf, char *dels, int more_dels, int pretty)
{
  char dialbuf[LONGSTRING*2];
  char * s;
  word_form wf;
  
  wf = forminfo_of(gstr);
  s=NameOfStemtype(stemtype_of(gstr));
  if( *s || *dels == '\t' )
    strcat(buf,dels);
  if( * s ) {
    strcat(buf, NameOfStemtype(stemtype_of(gstr) ) );
  }
		
  s=NameOfDerivtype(derivtype_of(gstr));
  if( *s || *dels == '\t' )
    strcat(buf,dels);
  if( * s ) {
    strcat(buf, NameOfDerivtype(derivtype_of(gstr) ) );
  }
		
  s=NameOfTense(wf);
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
  DialectNames(dialect_of(gstr),dialbuf,dels);
  if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
		
  dialbuf[0] = 0;
  GeogRegionNames(geogregion_of(gstr),dialbuf,dels);
  if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
		
		
  dialbuf[0] = 0;
  DomainNames(domains_of(gstr),dialbuf,dels);
  if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
	
		
  dialbuf[0] = 0;
  MorphNames(morphflags_of(gstr),dialbuf,dels,pretty);
  if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
}

GregSprintGkFlags(gk_string *gstr, char *buf, char *dels, int more_dels, int pretty)
{
  char dialbuf[LONGSTRING*2];
  char * s;
  word_form wf;
		
  wf = forminfo_of(gstr);

  s=NameOfTense(wf);
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
  DialectNames(dialect_of(gstr),dialbuf,dels);
  /*
    if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
    */
  strcat(buf,"\t");

  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
		
  dialbuf[0] = 0;
  GeogRegionNames(geogregion_of(gstr),dialbuf,dels);
  if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
		
		
  dialbuf[0] = 0;
  DomainNames(domains_of(gstr),dialbuf,dels);
  if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
	
		
  dialbuf[0] = 0;
  MorphNames(morphflags_of(gstr),dialbuf,dels,pretty);
  /*
    if( dialbuf[0] || *dels == '\t' )
    strcat(buf,dels);
    */
  strcat(buf,"\t");
  if( dialbuf[0] ) {
    strcat(buf,dialbuf );
  }
		
  s=NameOfStemtype(stemtype_of(gstr));
  strcat(buf,"\t");
  if( * s ) {
    strcat(buf, NameOfStemtype(stemtype_of(gstr) ) );
  }
		
  s=NameOfDerivtype(derivtype_of(gstr));
  if( * s ) {
    strcat(buf,",");
    strcat(buf, NameOfDerivtype(derivtype_of(gstr) ) );
  }
		


}

