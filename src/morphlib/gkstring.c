#include <gkstring.h>


gk_string *
CreatGkString(int num)
{
	gk_string * tmpgstring = NULL;
/*
printf("creat gstr %d\n", num * (sizeof * tmpgstring) );
*/
	tmpgstring = (gk_string *)calloc((size_t)num, (size_t)sizeof * tmpgstring);
	if( tmpgstring == NULL ) {
		fprintf(stderr,"Out of memory for %ld bytes to create %d gstrings\n",
		(size_t)(num * sizeof * tmpgstring), num );
	}
	return( tmpgstring );
}

FreeGkString(gk_string *gstring)
{
	if( ! gstring ) {
		fprintf(stderr,"hey! asked to free NULL gstring \n");
		return;
	}
/*
printf("free gstring \n");
*/
	xFree((char *)gstring,"FreeGkString");
}

gk_analysis *
CreatGkAnal(int num)
{
	gk_analysis * tmpanal = NULL;

	tmpanal= (gk_analysis *)calloc((size_t)num, (size_t)sizeof * tmpanal);
/*
printf("creat ganal %d\n", num * (sizeof * tmpanal) );
*/

	return(tmpanal);
}

FreeGkAnal(gk_analysis *gkanal)
{
	xFree((char *)gkanal,"freegkanal");
/*
printf("free gkanal \n");
*/
}

gk_word *
CreatGkword(int num)
{
	gk_word * tmpgword = NULL;
	
	tmpgword = (gk_word *)calloc((size_t)num,(size_t)(sizeof * tmpgword) );
/*
printf("creat gword %d\n", num * (sizeof * tmpgword) );
*/
	if( ! tmpgword ) {
		fprintf(stderr,"Could not allocate %d gwords\n", num );
		return((gk_word *)NULL);
	}
	return( tmpgword );
}

static gk_string BlnkGstr;

ClearGkstring(gk_string *gstr)
{
	gk_string *gstring;
	gk_string *CreatGkString();
	
	*gstr = BlnkGstr;
	return;
/*
	gstring = CreatGkString(1);
	*gstr = * gstring;
	FreeGkString(gstring,"freegkstring");
*/
}

FreeGkword(gk_word *Gkword)
{
	if( ! Gkword ) {
		fprintf(stderr,"hey! asked to free NULL gkword \n");
		return;
	}
	if( totanal_of(Gkword) && analysis_of(Gkword) )
		FreeGkAnal(analysis_of(Gkword));
	if( oddkeys_of(Gkword) ) 
		free(oddkeys_of(Gkword));
/*
printf("free gkword \n");
*/
	xFree((char *)Gkword,"freegkword");
}

CpGkAnal(gk_word *Gkword1, gk_word *Gkword2)
{
	totanal_of(Gkword1) = totanal_of(Gkword2);
	analysis_of(Gkword1) = analysis_of(Gkword2);
}

/*
 * compare two Greek strings.
 *
 * this routine *ignores* the actual character strings,
 * and uses the grammatical information as the basis for 
 * sorting.
 *
 * this routine allows you to sort a bunch of forms into
 * paradigms: so that we could store forms in approximately
 * the following order:
 *
 *	pres act indicative
 * 		1st sg, 2nd sg, 3rd sg, 1st pl etc.
 *	pres act subj
 * 		1st sg, 2nd sg, 3rd sg, 1st pl etc.
 *
 * and so on.
 */
 int
 CompGkString(const void *gstr1, const void *gstr2)
{
	int persnum1, persnum2;
	word_form f1;
	word_form f2;
	int n1, n2;
	Stemtype s1, s2;
	Dialect d1, d2;
	int rval = 0;

	f1 = forminfo_of((gk_string *)gstr1);
	f2 = forminfo_of((gk_string *)gstr2);
	
	s1 = stemtype_of((gk_string *)gstr1) & STEMTYPE;
	s2 = stemtype_of((gk_string *)gstr2) & STEMTYPE;
		
	if( s1 != s2 ) {
		rval = s1 - s2;
		goto finish;
	}
	
	if( has_morphflag(morphflags_of((gk_string *)gstr1),ITERATIVE) !=
		has_morphflag(morphflags_of((gk_string *)gstr2),ITERATIVE) ) {
		
		rval = has_morphflag(morphflags_of((gk_string *)gstr1),ITERATIVE) -
			has_morphflag(morphflags_of((gk_string *)gstr2),ITERATIVE);
		goto finish;
	}
	
	if( tense_of( f1 ) != tense_of( f2  ) ) {
		rval = tense_of( f1 ) - tense_of( f2  );
		goto finish;
	}
	
	if( voice_of( f1 ) != voice_of( f2  ) ) {
		rval = voice_of( f1 ) - voice_of( f2  );
		goto finish;
	}

	if( mood_of( f1 ) != mood_of( f2  ) ) {
		rval =  mood_of( f1 ) - mood_of( f2  );
		goto finish;
	}

	if( degree_of( f1 ) != degree_of( f2  ) ) {
		rval = degree_of( f1 ) - degree_of( f2 );
		goto finish;
	}
	
	if( case_of(f1) && case_of(f2) ) {
		int c1, c2;

		c1 = (1000 * number_of(f1)) + 
			(10 * (low_bit_of(case_of(f1)))) + 
			(low_bit_of(gender_of(f1)));
		c2 = (1000 * number_of(f2)) + 
			(10 * (low_bit_of(case_of(f2)))) + 
			low_bit_of(gender_of(f2));
		if( c1 != c2 ) {
			rval = c1 - c2 ;
			goto finish;
		}
	}

	if( gender_of(f1) && gender_of(f2) ) {
		if( low_bit_of(gender_of( f1 )) != low_bit_of(gender_of( f2  )) ) {
				rval= low_bit_of(gender_of( f1 )) - low_bit_of(gender_of( f2  ));
				goto finish;
		}
	}
		
	if( has_morphflag(morphflags_of((gk_string *)gstr1),UNAUGMENTED) !=
		has_morphflag(morphflags_of((gk_string *)gstr2),UNAUGMENTED) ) {
		
		rval = has_morphflag(morphflags_of((gk_string *)gstr1),UNAUGMENTED) -
			has_morphflag(morphflags_of((gk_string *)gstr2),UNAUGMENTED);
		goto finish;
	}
		
	if( person_of(f1) && person_of(f2) ) {
		persnum1 = (10 * number_of( forminfo_of( (gk_string *)gstr1 ) )) + person_of( forminfo_of( (gk_string *)gstr1 ) );
		persnum2 = (10 * number_of( forminfo_of( (gk_string *)gstr2 ) )) + person_of( forminfo_of( (gk_string *)gstr2 ) );
		if( persnum1 != persnum2 )  {
			rval = persnum1 - persnum2 ;
			goto finish;	
		}
	}
	
	n1 = low_bit_of(number_of(f1));
	n2 = low_bit_of(number_of(f2));
	
	if( number_of(f1) && number_of(f2)) {
		n1 = low_bit_of(number_of(f1));
		n2 = low_bit_of(number_of(f2));
		if( n1 != n2 ) {
			rval = n2-n1;
			goto finish;
		}
	}

	d1 = dialect_of((gk_string *)gstr1) & PARADIGM;
	d2 = dialect_of((gk_string *)gstr2) & PARADIGM;

	if( d1 != d2 ) {
		rval = d2-d1;
		goto finish;
	}
			

	d1 = dialect_of((gk_string *)gstr1) & ATTIC;
	d2 = dialect_of((gk_string *)gstr2) & ATTIC;

	if( d1 != d2 ) {
		rval = d2-d1;
		goto finish;
	}
			
	if( dialect_of( (gk_string *)gstr1 ) != dialect_of( (gk_string *)gstr2  ) ) {
		rval = dialect_of( (gk_string *)gstr1 ) - dialect_of( (gk_string *)gstr2  );
		goto finish;
	}
	finish:
/*if( ! strcmp(gkstring_of((gk_string *)gstr1),"ei=n") || ! strcmp(gkstring_of((gk_string *)gstr2),"ei=n") )
printf("1 [%s] 2 [%s] rval %d\n", gkstring_of((gk_string *)gstr1), gkstring_of((gk_string *)gstr2), rval );*/

		if( ! rval ) {
			int p1, p2;
			p1 = has_morphflag(morphflags_of((gk_string *)gstr1),PARADIGM);
			p2 = has_morphflag(morphflags_of((gk_string *)gstr2),PARADIGM);
			
			if( p1 != p2 ) return(p2-p1);
		}
		return(rval);
}

int CompGkForms(gk_word *gkform1, gk_word *gkform2)
{
	gk_string Gstr1;
	gk_string Gstr2;
	int rval =0;
	
	if( (rval=CompGkString(ends_gstr_of(gkform1),ends_gstr_of(gkform2))))
		return(rval);
	
	if( (rval=CompGkString(stem_gstr_of(gkform1),stem_gstr_of(gkform2))))
		return(rval);
	
	if( (rval=CompGkString(aug1_gstr_of(gkform2),aug1_gstr_of(gkform1))))
		return(rval);
	
	if( (rval=CompGkString(prvb_gstr_of(gkform1),prvb_gstr_of(gkform2))))
		return(rval);
	
	return(rval);
	Gstr1 = *ends_gstr_of(gkform1);
	add_dialect(&Gstr1,dialect_of(stem_gstr_of(gkform1)) );
	add_dialect(&Gstr1,dialect_of(aug1_gstr_of(gkform1)) );
	add_dialect(&Gstr1,dialect_of(prvb_gstr_of(gkform1)) );
	set_gkstring(&Gstr1,workword_of(gkform1));
	
	Gstr2 = *ends_gstr_of(gkform2);
	add_dialect(&Gstr2,dialect_of(stem_gstr_of(gkform2)) );
	add_dialect(&Gstr2,dialect_of(aug1_gstr_of(gkform2)) );
	add_dialect(&Gstr2,dialect_of(prvb_gstr_of(gkform2)) );
	set_gkstring(&Gstr2,workword_of(gkform2));
	
	return(CompGkString(&Gstr1,&Gstr2));
}

low_bit_of(int n)
{
	int i;
	int mask = 0;
	
	for(i=0;i<((int)sizeof i) * 8;i++) {
		mask += i;
		if( n & mask ) {
			return(n & mask );
		}
	}
		
}

int
CompByDictStr(const void *gstr1, const void *gstr2)
{
	return(dictstrcmp(gkstring_of((gk_string *)gstr1),gkstring_of((gk_string *)gstr2)));
}

RevCompByStr(gk_string *gstr1, gk_string *gstr2)
{
	return(CompByDictStr(gstr1,gstr2) * -1);
}

 PrntGkStrings(gk_string *gstr, FILE *f)
{
	while((gkstring_of(gstr))[0]) {
		PrntGkStr(gstr,f);
		gstr++;
	}
	
}

/*
 *  this expects an array of data structures of type gk_string
 */
 PrntGkParadigm(gk_string *gstr, FILE *f)
{
	Stemtype stemtype;
	int tense, mood, voice;
	word_form winfo;

	tense = mood = voice = 0;

	while((gkstring_of(gstr))[0]) {
		winfo = forminfo_of(gstr);

		if( stemtype != stemtype_of(gstr) ) {
			tense = mood = voice = 0;
			stemtype = stemtype_of(gstr);
			PrntStemtype(stemtype_of(gstr),f);
			fprintf(f,"\n");
		}
		if( tense != tense_of( winfo ) ||
		    voice != voice_of( winfo ) ||
		    mood != mood_of( winfo ) ) {
			tense = tense_of( winfo );
			mood = mood_of( winfo );
			voice = voice_of( winfo );
			fprintf(f,"\n");
			PrntParadigmInfo(winfo,f);
			fprintf(f,"\n");
		}
		
		PrntGkStr(gstr,f);
		gstr++;
	}

}

PrntGkStr(gk_string *gstr, FILE *f)
{
	fprintf(f,"%s ", gkstring_of(gstr) );
	PrntGkFlags(gstr,f);
	fprintf(f,"\n");
}

 PrntGkFlags(gk_string *gstr, FILE *f)
{
	PrntVerbInfo(forminfo_of(gstr),f);
	PrntAdjInfo(forminfo_of(gstr),f);
	PrntStemtype(stemtype_of(gstr),f);
	if(dialect_of(gstr) != ALL_DIAL)
		PrntDialect(dialect_of(gstr),f);
	PrntMorphFlags(morphflags_of(gstr),f);
	PrntDomains(domains_of(gstr),f);
}

PrntDomains(char *doms, FILE *f)
{
	char * p=doms;
	
	while(*p) {
		fprintf(f,"%s ", NameOfDomain(*p) );
		p++;
	}
}
  
 PrntMorphFlags(MorphFlags *mf, FILE *f)
{
	char buf[256];
	
 	MorphNames(mf,buf," ",1);
 	fprintf(f,"%s ", buf );
}

 PrntVerbInfo(word_form vf, FILE *f)
{
	char paradigm[LONGSTRING];
	
	paradigm[0] = 0;
	
	AddParadigmInfo(paradigm,vf," ");
	AddPersNumInfo(paradigm,vf," ");
	fprintf(f,"%s", paradigm);
}

 PrntParadigmInfo(word_form vf, FILE *f)
{
	char paradigm[LONGSTRING];
	paradigm[0] = 0;
	
	AddParadigmInfo(paradigm,vf," ");
	fprintf(f,"%s", paradigm);
}
	

AddParadigmInfo(char *s, word_form vf,char * dels)
{
	char * p;
	
	p=NameOfTense(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
	p=NameOfMood(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
	p=NameOfVoice(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
}

AddPersNumInfo(char *s, word_form vf,char * dels)
{
	char * p;
	
	p=NameOfPerson(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
	p=NameOfNumber(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
}

PrntPersNumInfo(word_form vf, FILE *f)
{
	fprintf(f,"%s ", NameOfPerson(vf ) );
	fprintf(f,"%s ", NameOfNumber(vf ) );
}

 PrntAdjInfo(word_form af, FILE *f)
{
	char adjbuf[MAXWORDSIZE];
	adjbuf[0] = 0;
	
	AddAdjInfo(adjbuf,af," ");
	fprintf(f,"%s", adjbuf );
/*
	fprintf(f,"%s ", NameOfGender(af ) );
	fprintf(f,"%s ", NameOfCase(af ) );
	fprintf(f,"%s ", NameOfDegree(af) );
*/
}

AddAdjInfo(char *s, word_form vf,char * dels)
{
	char * p;
	
	p=NameOfGender(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
	p=NameOfCase(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	p=NameOfDegree(vf);
	if( *p ) {
		strcat(s,dels);
		strcat(s,p);
	}
	
	
}

int
 PrntStemtype(st,f)
 Stemtype st;
 FILE *f;
{
	fprintf(f,"%s ", NameOfStemtype(st ) );
}

int
 PrntDialect(di,f)
 Dialect di; 
 FILE *f;
{
	char * s;
	int i;
	Dialect mask = 1;
	char dialbuf[MAXWORDSIZE];

	dialbuf[0] = 0;
	AddDialect(di,dialbuf);
	fprintf(f,"%s ", dialbuf);
/*
	for(i=0;i<(((int)sizeof di) * 8);i++) {
		if( (s=NameOfDialect(di&mask)) )
			if( *s )
				fprintf(f,"%s ", s );
		mask = mask << 1;
	}
*/
}

int AddDialect(di, dialb,dels)
	Dialect di;
	char *dialb;
	char *dels;
{
	char * s;
	int i;
	Dialect mask = 1;

	for(i=0;i<(((int)sizeof di) * 8);i++) {
		if( (s=NameOfDialect(di&mask)) )
			if( *s ) {
				if( *dialb ) strcat(dialb,dels);
				strcat(dialb, s );
			}
		mask = mask << 1;
	}

}


/*
 * see if the dialect of the stem and of the ending are
 * compatible. if they are not, return 0. otherwise,
 * "and" the dialects together.
 */
Dialect
 AndDialect(Dialect Dial1, Dialect Dial2)
{

	/*
 	 * if no dialect set for either
	 */
	if( ! Dial1 && ! Dial2 )
		return(0);
	/*
	 * if dialects for both Stem and End
	 */
	else if( Dial1 && Dial2 ) {
/*
		and_dialect(End,Dial2);	
*/
		Dial1 &= Dial2;
		if( ! Dial1 )
			return((Dialect) -1);
		else
			return(Dial1);
	} else if( (!Dial1 && Dial2 ) ) {
/*
fprintf(stderr,"End dial [%o] stem [%o]\n", Dial1 , Dial2 );
*/
		return(Dial2);
	} else if( Dial1 && ! Dial2 )
		return(Dial1);
	else
		return((Dialect)0);

}

static int (*gkCompare)();

 xInsertGstr(gk_string *oldgstr, gk_string *newgstr, int len, int (*compare )(), int backwards)
{
	char * news, *olds;
	int i;
	
	gkCompare = compare;

	news = gkstring_of(newgstr);

	if( len == 0 ) {
		*oldgstr = * newgstr;
	} else {
		for(i=len;i>0;i--) {
			olds = gkstring_of(oldgstr+i-1);
			*(oldgstr+i) = *(oldgstr+i-1);
			if( backwards == NO ) {
				if(((*gkCompare)(olds,news)) <= 0 )  {
					break;
				}
			} else if( ((*gkCompare)(olds,news)) > 0 )  {
				break;
			}
			
		}
		*(oldgstr+i) = *newgstr;
			
	}

	return(++len);
}

GetTableLine(char *s, int len, FILE *f)
{
	while(fgets(s,len,f)) {
		if( is_blank(s) )
			continue;
		if( Is_comment(s) )
			continue;
		return(1);
	}
	return(0);
}

eq_forminfo(word_form f1, word_form f2)
{
	if( voice_of(f1) != voice_of(f2)) return(0);
	if( mood_of(f1) != mood_of(f2)) return(0);
	if( tense_of(f1) != tense_of(f2)) return(0);
	if( person_of(f1) != person_of(f2)) return(0);
	if( number_of(f1) != number_of(f2)) return(0);
	if( degree_of(f1) != degree_of(f2)) return(0);
	if( gender_of(f1) != gender_of(f2)) return(0);
	if( case_of(f1) != case_of(f2)) return(0);

	return(1);
}
		
SprintGkFlags(gk_string *gstr, char *buf, char *dels, int pretty)
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


DbaseFormat(gk_string *gstr, char *buf, char *tabstr, int pretty)
{
		char dialbuf[LONGSTRING];
		char * s;
		word_form wf;
		
		wf = forminfo_of(gstr);
		s=NameOfStemtype(stemtype_of(gstr));
		if( * s ) {
			strcat(buf, NameOfStemtype(stemtype_of(gstr) ) );
		}
		
		strcat(buf,tabstr);
		s=NameOfDerivtype(derivtype_of(gstr));
		if( * s ) {
			strcat(buf, NameOfDerivtype(derivtype_of(gstr) ) );
		}
		

		strcat(buf,tabstr);
		AddParadigmInfo(buf,wf," ");
		
		strcat(buf,tabstr);
		AddPersNumInfo(buf,wf," ");

		strcat(buf,tabstr);
		AddAdjInfo(buf,wf," ");
		
		dialbuf[0] = 0;
		DialectNames(dialect_of(gstr),dialbuf," ");
		if( dialbuf[0] ) {
			strcat(buf,tabstr); 
			strcat(buf,dialbuf );
		}
		
		
		
		dialbuf[0] = 0;
		MorphNames(morphflags_of(gstr),dialbuf," ",pretty);
		if( dialbuf[0] ) {
			strcat(buf,tabstr); 
			strcat(buf,dialbuf );
		}
}
