#include <gkstring.h>

static	char origformula[LONGSTRING];
static	char curlemma[LONGSTRING];

combine_conj(fout,lemma,origline,stemstr,derivstr,globalkeys,localkeys)
FILE * fout;
char * lemma;
char * origline;
char * stemstr;
char * derivstr;
char * globalkeys;
char * localkeys;
{
	gk_string CurGstr;
	Stemtype ppartflag, ConjGkstr();
	char stembuf[MAXWORDSIZE];
	char suffbuf[MAXWORDSIZE];
	char oddkeys[LONGSTRING*2];
	char preverb[MAXWORDSIZE];

	preverb[0] = suffbuf[0] = oddkeys[0] = 0;
	strcpy(origformula , origline);
	strcpy(curlemma , lemma);
	
	strcpy(stembuf,stemstr);

/*
fprintf(stdout,"stemstr [%s] derivstr [%s] keys [%s]\n", stemstr, derivstr, localkeys );
*/
	ppartflag = ConjGkstr(&CurGstr,suffbuf,globalkeys,localkeys,oddkeys,preverb);

/*
printf("ppartflag %o\n", ppartflag );
*/
	if( DoConjStem(fout,derivstr,&CurGstr,suffbuf,ppartflag,stembuf,oddkeys,preverb) <= 0 ) {
		return(0);
	} return(1);
}

DoConjStem(fout,derivstr,gstr,suffstr,ppartflag,stemstr,oddptr,preverb)
FILE * fout;
char * derivstr;
gk_string * gstr;
char * suffstr;
Stemtype ppartflag;
char * stemstr;
char * oddptr;
char * preverb;
{
	char derivfile[MAXPATHNAME];
	FILE * fderiv, *MorphFopen();
	int lno, maxend, i, rval;
	gk_string CurGstr;
	int gotstem = 0;
	Stemtype ConjGkstr();

	sprintf(derivfile,"derivs:out:%s.out", derivstr);

	if( (fderiv=MorphFopen(derivfile,"rb")) == NULL ) {
		fprintf(stderr,"could not open [%s] for %s\n", derivfile, derivstr );
		return(0);
	}
	
	lno = get_endheader(fderiv,&maxend);
	if( lno < 0 ) {
/*
		fprintf(stderr,"failed on %s\n", derivstr );
*/
		fclose(fderiv);
		return(0);
	}
	for(i=0;i<lno;i++ ) {
		rval=ReadEnding(fderiv,&CurGstr,maxend);

		if (rval <= 0 ) {
			fprintf(stdout,"hey! fname [%s] wanted [%d] endings got [%d]!\n", derivstr, lno , i );
			fclose(fderiv);
			return(0);
		}

/*

printf("stype [%o] VB %o [%o] ppflag [%o]\n", stemtype_of(&CurGstr), PPARTMASK, (stemtype_of(&CurGstr) & PPARTMASK), ppartflag );
*/
		if( ((stemtype_of(&CurGstr) & PPARTMASK) == ppartflag ) ||
		    ((stemtype_of(&CurGstr) & ADJSTEM) == ppartflag ) ||
		    ((stemtype_of(&CurGstr) & NOUNSTEM) == ppartflag )) {
/*
printf("suffstr [%s] gkstring [%s]\n", suffstr , gkstring_of(&CurGstr) );
*/
			if( *suffstr && !MatchSuff(gkstring_of(&CurGstr), suffstr))
				continue;
			if( (gotstem=CheckConjPpart(fout,derivstr,gstr,&CurGstr,stemstr,oddptr,preverb)) ) 
				break;
		} /*else printf("%s failed on ppartflag %o stemtype %o\n",gkstring_of(&CurGstr), ppartflag,  (stemtype_of(&CurGstr)) );*/
		
	}
	
	fclose(fderiv);
	return(gotstem);
}

gk_string *  CreatGkString();
gk_word *  CreatGkword();
gk_string blnk;

Stemtype
ConjGkstr(gstr,suffstr,globalkeys,keys,oddkeys,preverb)
gk_string * gstr;
char * suffstr;
char * globalkeys;
char * keys;
char * oddkeys;
char * preverb;
{
	char keytmp[LONGSTRING];
	gk_word * TmpGkword;
/*
	gk_string * blnk;
*/
	char * s;
	char ppartname[MAXWORDSIZE];
	char tmp[LONGSTRING];
	Stemtype stype, GetStemClass();		
	int npparts;
	
/*	blnk = (gk_string *) CreatGkString(1);
	* gstr = * blnk;
	FreeGkString(blnk);
*/
	*gstr = blnk;
	
	TmpGkword = (gk_word *) CreatGkword(1);
	
/*printf("suffstr [%s] keys [%s]\n", suffstr, keys );*/
	strcpy(keytmp,keys);

	s = keytmp;
	while(*s&&*s!=' ') { 
		if(*s == ',' ) 
			*s = ' ';
		s++;
	}
	strcpy(ppartname,"pp_");
	nextkey(keytmp,ppartname+3);

	stype = GetStemClass(ppartname,npparts);

	if( keytmp[0] == '-' ) {
		/*
		 * note that global keys precede curkeys -- that means that
		 * curkeys will override global keys. Thus if a verb is listed generally
		 * as "mp" (middle-passive) but the curkeys for a particular form specify
		 * "mid", then that form will be marked as "middle".
		 */
		
		nextkey(keytmp,suffstr);
		strcpy(suffstr,suffstr+1);
	}
	if( * globalkeys ) {
		char tmp[LONGSTRING];
		
		sprintf(tmp,"%s %s", globalkeys , keytmp);
		strcpy(keytmp,tmp);
	}

	ScanAsciiKeys(keytmp,TmpGkword,gstr,NULL);

	add_morphflags(gstr,morphflags_of(prvb_gstr_of(TmpGkword)) );
	
	if( oddkeys_of(TmpGkword) )
		strcpy(oddkeys,oddkeys_of(TmpGkword) );
	else
		oddkeys[0] = 0;
		
	preverb[0] = 0;
	strcpy(preverb,preverb_of(TmpGkword));
	 
	set_gkstring(gstr,endstring_of(TmpGkword) );

	add_morphflag(morphflags_of(gstr),IS_DERIV);
	
	FreeGkword(TmpGkword);

	if(stype >= 0)
		return(stype);
	else 
		return(0);

}

CheckConjPpart(fout,derivstr,gstr1,gstr2,stemstr,oddptr,preverb)
FILE * fout;
char * derivstr;
gk_string * gstr1;
gk_string * gstr2;
char * stemstr;
char * oddptr;
char * preverb;
{
	int rval, rpb_flag;
	char word[MAXWORDSIZE];
	char showbuf[LONGSTRING];
	Stemtype ppartflag;
	register char * ep = gkstring_of(gstr2);

    ppartflag = stemtype_of(gstr2) & PPARTMASK;
/*
printf("pflag %o stype %o vstem %o\n", ppartflag , stemtype_of(gstr2) , PPARTMASK );
*/

/*	
	markstem(stemstr,gstr1);
*/
	if( ! dialect_of(gstr1) && !gkstring_of(gstr2)[0] )
		set_dialect(gstr1,(Dialect)ATTIC);

	if( stemtype_of(gstr1) && stemtype_of(gstr1) != stemtype_of(gstr2) ) {
		goto failure;
	}

	if( ppartflag == PP_PF && (voice_of(forminfo_of(gstr1)) & MEDIO_PASS) ) goto failure;
	rval=WantGkEnd(gstr1,gstr2,0,0);
/*
printf("str1 [%s] str2 [%s] rval %d\n", gkstring_of(gstr1), gkstring_of(gstr2), rval );
*/
	if( rval ) {
		Dialect d, AndDialect();
		char *getaccp();
		
		strcpy(word,stemstr);

		if( has_morphflag(morphflags_of(gstr1),PRES_REDUPL)) {
			pres_redupl(word);
		}
	
			if( has_morphflag(morphflags_of(gstr1),N_INFIX) )
				addninfix(word);
		if( *ep != '*' ) {

	/*
	 * add needed diaeresis 
	 * grc 9/13/88
	 *
	 * a)gla i/zw --> a)glai/+izw
	 * *)amukla i/zw --> *)amuklai/+izw
	 */
			if( Is_vowel(*ep) && ! is_diphth(ep+1,ep) && Is_vowel(*(lastn(word,1))) ) {
				/*
				 * check to see if this would be a diphthong,
				 * thus
				 *  a)gla i/zw --> a)glai/+zw
				 * but
				 *  bru a/zw --> brua/zw (not brua/+zw)
				 */
				char tmp[MAXWORDSIZE];
				tmp[0] = *(lastn(word,1));
				tmp[1] = *ep;
				tmp[2] = 0;
				if( is_diphth(tmp+1,tmp) )
					addaccent(ep,DIAERESIS,ep);

			}
			if( *stemstr == ROUGHBR || * stemstr == SMOOTHBR ) {
				strcpy(word,ep);
				addbreath(word,*stemstr);
			} else {
				conjoinX(gstr2,word,gkstring_of(gstr2));
			}
		}


	if( (ppartflag == PP_PF || ppartflag == PP_PP || ppartflag == PP_FP) ) {

			if( ! has_morphflag(morphflags_of(gstr1),NO_REDUPL) ) 
				simpleredupit(word,has_morphflag(morphflags_of(gstr1),SYLL_AUG),'e');

			if( Is_primconj(gstr2) ) {
				if( ppartflag == PP_PF ) fixperf(word);
				else if( ppartflag == PP_PP) makeppass(word,gstr2);

			}
		}
		
	if( do_dissim(word,ppartflag)) {
			add_morphflag(morphflags_of(gstr1),DISSIMILATION);
	}

		
	/*
	 * at this point, no further changes should take place on the stem itself
	 */
		 
		 
		 
		if( dialect_of(gstr1) ) {
			d = AndDialect(dialect_of(gstr1),dialect_of(gstr2));
			if( d < 0 ) goto failure;
			if( ! dialect_of(gstr2) )
				set_dialect(gstr2,d);
			else
				set_dialect(gstr2,dialect_of(gstr1));
		}

		add_morphflags(gstr2,morphflags_of(gstr1));

		zap_morphflag(morphflags_of(gstr2),IS_DERIV);
		zap_morphflag(morphflags_of(gstr2),R_E_I_ALPHA);

		if( voice_of(forminfo_of(gstr1)) ) {
			int v = voice_of(forminfo_of(gstr1));

			if( v == MEDIO_PASS ) {
				if( has_passive_stype(stemtype_of(gstr2))) 
					set_voice(forminfo_of(gstr2),PASSIVE);
				else if( has_middle_stype(stemtype_of(gstr2))) 
					set_voice(forminfo_of(gstr2),MIDDLE);
				else
					set_voice(forminfo_of(gstr2),v);

			} else {
				set_voice(forminfo_of(gstr2),v);

			}
		}
		if( tense_of(forminfo_of(gstr1)) )  
			set_tense(forminfo_of(gstr2),tense_of(forminfo_of(gstr1)));
		if( mood_of(forminfo_of(gstr1)) )  
			set_mood(forminfo_of(gstr2),mood_of(forminfo_of(gstr1)));
		if( person_of(forminfo_of(gstr1)) )  
			set_person(forminfo_of(gstr2),person_of(forminfo_of(gstr1)));
		if( number_of(forminfo_of(gstr1)) )  
			set_number(forminfo_of(gstr2),number_of(forminfo_of(gstr1)));


		showbuf[0] = 0;

		if( has_morphflag(morphflags_of(gstr2),ROOT_PREVERB)) {
			rpb_flag = 1;
			zap_morphflag(morphflags_of(gstr2),ROOT_PREVERB);
		} else
			rpb_flag = 0;
		if( has_morphflag(morphflags_of(gstr2),R_E_I_ALPHA) ) 
			zap_morphflag(morphflags_of(gstr2),R_E_I_ALPHA);
			
		
		strcpy(domains_of(gstr2),domains_of(gstr1));
		SprintGkFlags(gstr2,showbuf," ",0);
/* fflush(fout);*/
		if( stemtype_of(gstr2) & PPARTMASK ) fprintf(fout,":vs:");
		else if( stemtype_of(gstr2) & ADJSTEM ) fprintf(fout,":aj:");
		else if( stemtype_of(gstr2) & NOUNSTEM ) fprintf(fout,":no:");
		else fprintf(fout,":??:");

		fprintf(fout,"%s ", word );
		fprintf(fout,"%s",  showbuf );
		if( gkstring_of(gstr1)[0] )  {
			fprintf(fout," end:%s", gkstring_of(gstr1) );
		}

		if( *preverb ) {
			char tmppb[MAXWORDSIZE*2];
			
			if( rpb_flag ) strcpy(tmppb,"rpb:");
			else strcpy(tmppb,"pb:");
			strcat(tmppb,preverb);
			fprintf(fout," %s", tmppb );
		}
		
		if( *oddptr ) {
			fprintf(fout," %s", oddptr);
			add_oddstuff(oddptr);
		}
	
		fputc('\n',fout);

		DataBaseFormat(word,gstr2,gkstring_of(gstr1),preverb,oddptr);

	} else {
		goto failure;
	}
	return(1);
	failure:
		return(0);
}
static int firstfail = 1;
static FILE * fdbaseform = NULL;
static FILE * foddfile = NULL;

add_oddstuff(s)
char *s;
{
	if( ! foddfile ) {
		foddfile = fopen("oddfile","w");
		if( ! foddfile)  return;
	}
	fprintf(foddfile,"%s\t%s\n", curlemma , s );
}

DataBaseFormat(word,gstr,endstring,preverb,oddptr)
char * word;
gk_string * gstr;
char * endstring;
char * preverb;
char * oddptr;
{
	char curbuf[BUFSIZ*4];
	char curformula[BUFSIZ*4];
	char * s;
return;	
	strcpy(curformula,origformula);
	curbuf[0] = 0;
	
	s = curformula;
	while(*s) { 
		if(*s=='\t') *s = ' ';
		s++;
	}
	
	if( ! fdbaseform ) {
		fdbaseform = fopen("dbasefile","w");
		if( ! fdbaseform ) {
			if( firstfail ) fprintf(stderr,"could not open dbasefile\n");
			firstfail = 0;
			return(0);
		}
	}
	fprintf(fdbaseform,"%s\t%s\t%s\t%s\t%s\t", curlemma, curformula , word, endstring, preverb );
	DbaseFormat(gstr,curbuf,"\t",0);
	fprintf(fdbaseform,"%s\t", curbuf );
	fprintf(fdbaseform,"%s\n", oddptr );
}

/*
 * grc 8/29/94
 *
 * the logic of this is that if you want a long alpha, you got to ask
 * for it.

 * if you just ask for an "a", you match either "a" or "a^"
 */
MatchSuff(char * s1,char * s2)
{
	char tmp[BUFSIZ];

	if( !strcmp(s1,s2) ) return(1);
	strcpy(tmp,s1);
	stripshortmark(tmp);
	if( !strcmp(s2,tmp) ) return(1);

	return(0);
	
}

gk_string *
 do_euph(gk_string *, Dialect );

gk_string BlnkGstr, Gstr;
conjoinX(gk_string *gstr,char * s1,char * s2)
{
	int i;

	gk_string *newgstr;

	Gstr = BlnkGstr;
	strcat(s1,s2);

	set_gkstring(gstr,s1);

	newgstr = do_euph(gstr,(Dialect)0);

	if( ! newgstr ) {
		/*fprintf(stderr,"no contracts for [%s]\n", gkstring_of(gstr) );*/
		return;
	}
	
/*
	for(i=0;i<10;i++) {
		if( ! gkstring_of(newgstr+i)[0] ) break;
		printf("%d:[%s]\n", i, gkstring_of(newgstr+i) );
	}
*/
	*gstr = *newgstr;
	strcpy(s1,gkstring_of(newgstr));

	return(i);
}
