#include <gkstring.h>

#define NextStem(f,stem,stemkeys) NextDictLine(f,stem,stemkeys,":")
#define NextLemma(f,lemma,lemmakeys) NextDictLine(f,lemma,lemmakeys,":le:")

gk_string * chckendings();
gk_word * GenStemForms();
gk_word * GenIrregForm();
static gk_word Blnk;
static gk_string BlnkGstr;
static showdialect;
static char defbuf[8000];
static char curlemma[LONGSTRING];
#define TO_SMARTA 1
#define TO_SMK		02
#define FULL_DUMP 1
#define DICT_ENTRY 2
#define MORPH_INFO 3
static int print_mode = FULL_DUMP;

 GenSynForms(f,fout)
  FILE * f;
  FILE * fout;
{
	
	int rval = 0;
	int nl = 0;
	int i;
	gk_word * Rvals = NULL;
	char lemmakeys[LONGSTRING];
	char tmp[LONGSTRING];
	char baseentry[LONGSTRING];
	char * stemkeys;
	char line[LONGSTRING*2];
	gk_word * Gkword = NULL;
	char * s;


	Gkword = CreatGkword(1);
	if( ! Gkword ) {
		fprintf(stderr,"failed to get memory in GenSynForms!\n");
		return(-1);
	}
	
	i = 0;
	baseentry[0] = 0;

	while( fgets(line,sizeof line,f ) ) {
		char saveline[BUFSIZ*2];

		strcpy(saveline,line);

		showdialect = 0;
		if( is_blank(line) ) {
			fprintf(fout,"--%s", saveline );
			continue;
		}
		zap_tabs(line);
		if(line[0] == '?' ) {
			if( line[1] == '#' ) continue;
			if( line[1] == '?' && line[2] == '#' ) continue;
		}
		if(line[0] == '#') continue;
		
		if(/*line[0] == '@' || */ line[0] == ';' ) {
			fprintf(fout,"%s", line );
			continue;
		}
		
		if( line[0] == '@' ) {
			Xstrncpy(tmp,baseentry,sizeof tmp);
			Xstrncat(tmp,line+1,sizeof tmp);
			Xstrncpy(line,tmp,sizeof line);
		}
		
		if( line[0] != ':' ) {
			s = line+strlen(line)-1;
			if( *s == '\n') {
				while(isspace(*s)&&s>line) *s-- = 0;
				s++;
				*s = ' ';
			}

			proc_beta(line,fout,TO_SMARTA);

			nl  = 0;
			continue;
		}

		if( !strncmp(line,":dnum",5) ) {
			if( ! nl ) fputc('\n',fout);
			fprintf(fout,":dnum\n");
			line[5] = '&';
			s = line+strlen(line)-1;
			if( *s == '\n') 
				*s = ' ';
			proc_beta(line+5,fout,TO_SMARTA);
			nl = 0;
			continue;
		}
		if( ! strncmp(line,":def",4) ) {
			if( ! nl ) fputc('\n',fout);
			fprintf(fout,":def\n");
			continue;
		}
		if( ! strncmp(line,":le:",4) ) {
			char saveline[LONGSTRING];
			
			defbuf[0] = 0;
			
			zap_hyph(line);
			stripquant(line);
			stripdiaer(line);
			Xstrncpy(saveline,line,sizeof saveline);
			if( line[4] == '!' ) {
				Xstrncpy(line+4,line+5,(sizeof line) - 4);
				s = line+strlen(line)-1;
				fprintf(fout,"\n\n%s", line );
				if( *s == '\n') 
					*s = ' ';
				Xstrncat(line," &root\n",sizeof line);
			} else
				fprintf(fout,"\n%s", line );
			line[3] = '$';
			Xstrncpy(curlemma,line+4,sizeof curlemma);
			if( *(lastn(curlemma,1)) == '\n' ) *(lastn(curlemma,1)) = 0;
/* grc 6/2/89 -- take this out for now, as we just dump into beta
			proc_beta(line+3,fout,TO_SMK);
*/
			nl++;
			continue;
		}
		
		
		* Gkword = Blnk;
		/*
		 * process a regular stem
		 */
		if( !strncmp(line,":aj:",4) || ! strncmp(line,":no:",4) || ! strncmp(line,":vs:",4)) {
			gk_string Gstr;
			
			Gstr = BlnkGstr;
			
			zap_rootmarker(line);
			set_baseentry(line,baseentry,(int)sizeof line);

			stemkeys = line;
			while(*stemkeys&&!isspace(*stemkeys)) stemkeys++;
			if( isspace(*stemkeys) ) *stemkeys++ = 0;
			while(isspace(*stemkeys)) stemkeys++;
/*			
			stemkeys = stpblk(line);
			*stemkeys++ = 0;
*/
			set_stem(Gkword,line+4);
			set_lemma(Gkword,curlemma);
			paradigm_keys(stemkeys);
/*

printf("stemkeys [%s]\n", stemkeys );
			nl++;
			ScanAsciiKeys(stemkeys,Gkword,&Gstr,NULL);
			set_dialect(Gkword,dialect_of(&Gstr));
			set_geogregion(Gkword,geogregion_of(&Gstr));
			set_domains(Gkword,domains_of(&Gstr));

/*
			set_morphflags(Gkword, morphflags_of(&Gstr));
*/


			Rvals = GenStemForms(Gkword,stemkeys,0);

		} else if( ! strncmp(line,":wd:",4) || ! strncmp(line,":vb:",4) ) {
			gk_string Gstr;
			int mode = 0;
			
			Gstr = BlnkGstr;

			/*
			stemkeys = stpblk(line);
			*/
			set_baseentry(line,baseentry,(int)sizeof line);

			stemkeys = line;
			while(*stemkeys&&!isspace(*stemkeys)) stemkeys++;
			if( isspace(*stemkeys) ) *stemkeys++ = 0;
			while(isspace(*stemkeys)) stemkeys++;
		
			set_stem(Gkword,line+4);
			set_lemma(Gkword,curlemma);

			paradigm_keys(stemkeys);
			ScanAsciiKeys(stemkeys,Gkword,&Gstr,NULL);
			set_morphflags(Gkword, morphflags_of(&Gstr));
			if( !strncmp(line,":wd:",4) ) {
				mode = INDECL;
			}

			Rvals = GenIrregForm(Gkword,stemkeys,mode);
			nl++;
		} else if( ! strncmp(line,":xref",strlen(":xref") ) ) {
			if( !nl ) fprintf(fout,"\n");
			fprintf(fout,":xf:");
			line[5] = '$';
			proc_beta(line+5,fout,TO_SMARTA);
			fprintf(fout,"%s", saveline);
			continue;
		} else if( ! strncmp(line,":de:",strlen(":de:") ) ) {
			if( !nl ) fprintf(fout,"\n");
			fprintf(fout,"%s",line);
			continue;
		} else if( ! strncmp(line,":comm",strlen(":comm") ) ) {
			if( !nl ) fprintf(fout,"\n");
			fprintf(fout,"%s", saveline);
			line[5] = '&';
			proc_beta(line+5,fout,TO_SMARTA);
			continue;
		} else if( ! strncmp(line,":eq ",strlen(":eq ") ) ) {
			if( !nl ) fprintf(fout,"\n");
			fprintf(fout,":eq:");
			line[4] = '$';
			proc_beta(line+4,fout,TO_SMARTA);
			fprintf(fout,"%s", saveline);
			continue;
		} else {
			nl++;
			proc_beta(line,fout,TO_SMARTA);
			fprintf(fout,"%s", saveline);
			continue;
		}
		if( ! Rvals ) {
			fprintf(fout,"line:%s\n", line );
			fprintf(fout,"@failed with stem [%s] and keys [%s]\n", stem_of(Gkword) , stemkeys );
			fprintf(stderr,"@failed with stem [%s] and keys [%s]\n", stem_of(Gkword) , stemkeys );
/*			SawBadForm(lemma_of(Gkword), stem_of(Gkword), stemkeys );*/

			set_stem(Gkword,"");
			set_endstring(Gkword,"");
			if( (oddkeys_of(Gkword) ))  *(oddkeys_of(Gkword)) = 0;
	
			continue;
		}

		PrntSynForms(Gkword,Rvals,fout);

/*
 if( ! (i++ % 50 ) ) fprintf(stderr,"just processed %d [%s]\n", i-1 , stem_of(Gkword) );
*/

		fprintf(fout,"%s", saveline);
		FreeGkword(Rvals);
		Rvals = NULL;
		/*set_printword(Gkword,"");*/
		set_stem(Gkword,"");
		set_endstring(Gkword,"");
		if( (oddkeys_of(Gkword) ))  *(oddkeys_of(Gkword)) = 0;
	}
	finish:
if( i > 30 ) fprintf(stderr,"out of loop with i %d\n", i );
		FreeGkword( Gkword ); 
		Gkword = NULL;
		return(rval);
}

paradigm_keys(keys)
char * keys;
{
	gk_string * gstr;
	gk_string * avoidgstr;
	Stemtype GetStemNum(), snum;
	word_form  wf;
	gk_word * dummyword;
	
	gstr = CreatGkString(1);
	if( ! gstr ) {
		fprintf(stderr,"no memory for gstr in paradigm keys\n");
		return;
	}
	
	avoidgstr = CreatGkString(1);
	if( ! avoidgstr ) {
		FreeGkString(gstr);
		gstr = NULL;
		fprintf(stderr,"no memory for avoidgstr in paradigm keys\n");
		return;
	}
	
	dummyword = CreatGkword(1);
	if( ! dummyword ) {
		FreeGkString(avoidgstr);
		FreeGkString(gstr);
		gstr = avoidgstr = NULL;
		fprintf(stderr,"no memory for dummyword in paradigm keys\n");
		return;
	}
	

	clear_globs(keys);


	ScanAsciiKeys(keys,dummyword,gstr,avoidgstr);

	wf = forminfo_of(avoidgstr);
	set_gkstring(gstr,endstring_of(dummyword));

	if( gkstring_of(gstr)[0] && *(lastn(gkstring_of(gstr),1))!='-') goto finish;

	if( tense_of(wf) ||  mood_of(wf) || voice_of(wf) || person_of(wf) || number_of(wf)
		|| gender_of(wf) )
				goto finish;
/*
 * don't put any further restrictions on the form if doing a full dump
 */
	if( print_mode == FULL_DUMP ) goto finish;
	

	wf = forminfo_of(gstr);
	if( Is_adjform(gstr) || mood_of(wf) == PARTICIPLE ) {
/*
printf("stype [%o] adjform [%o] part %o keys:%s\n",  stemtype_of(gstr) , Is_adjform(gstr) , mood_of(wf) == PARTICIPLE,
keys ); 
*/
			if( ! number_of(wf) )
				Xstrncat(keys," sg",LONGSTRING);
			if( ! case_of(wf) )
				Xstrncat(keys," nom ",LONGSTRING);
			if( ! gender_of(wf) )
				Xstrncat(keys," masc fem neut",LONGSTRING);
			if( ! degree_of(wf) && strcmp("wn_on_comp",NameOfStemtype(stemtype_of(gstr))) )
				Xstrncat(keys," no_comp",LONGSTRING);
	} else if( Is_nounform(gstr)) {
			if( ! number_of(wf) )
				Xstrncat(keys," sg",LONGSTRING);
			if( ! case_of(wf) )
				Xstrncat(keys," nom gen",LONGSTRING);
	} else if( Is_verbform(gstr) ) {

			if( mood_of(wf) == INFINITIVE || mood_of(wf) == IMPERATIVE )
				goto finish;
				
/*
			if( mood_of(wf) == INFINITIVE || mood_of(wf) == IMPERATIVE || mood_of(wf) == OPTATIVE || 
			mood_of(wf) == SUBJUNCTIVE  )
				goto finish;
			else
				Xstrncat(keys," ind",LONGSTRING);
*/
			if( ! voice_of(wf) ) {

				if( is_mp_stem(stemtype_of(gstr) ) )
					Xstrncat(keys," mp",LONGSTRING);
				else if( is_pass_stem(stemtype_of(gstr) ) ) {
					Xstrncat(keys," pass",LONGSTRING);
/*
					if( ! tense_of(wf) ) Xstrncat(keys," aor",LONGSTRING);
*/
				} else
					Xstrncat(keys," act",LONGSTRING);
			}
			if( ! number_of(wf) )
				Xstrncat(keys," sg",LONGSTRING);
			if( ! person_of(wf) ) {
				if( number_of(wf) == DUAL ) 
					Xstrncat(keys," 2nd",LONGSTRING);
				else
					Xstrncat(keys," 1st",LONGSTRING);
			}
			if( ! tense_of(wf) ) {
				snum = stemtype_of(gstr);
				if( (snum & VERBSTEM) == PP_PR ) {
					Xstrncat(keys," pres",LONGSTRING);
				} else 
				if( (snum & VERBSTEM) == PP_FU ) {
					Xstrncat(keys," fut",LONGSTRING);
				} else 
				if( (snum & VERBSTEM) == PP_AO ) {
					Xstrncat(keys," aor",LONGSTRING);
				} else 
				if( (snum & VERBSTEM) == PP_AP ) {
					Xstrncat(keys," aor",LONGSTRING);
				} else 
				if( (snum & VERBSTEM) == PP_PF ) {
					Xstrncat(keys," perf",LONGSTRING);
				} else 
				if( (snum & VERBSTEM) == PP_FP ) {
					Xstrncat(keys," futperf",LONGSTRING);
				} 
			}

		}
		if( ! dialect_of(gstr) && ! has_morphflag(morphflags_of(gstr),UNAUGMENTED) && 
				 ! has_morphflag(morphflags_of(gstr),ITERATIVE)  )
			Xstrncat(keys," attic parad_form",LONGSTRING);
		else {
			showdialect++;
		}
		if( oddkeys_of(dummyword) ) {
			strcat(keys," ");
			strcat(keys,oddkeys_of(dummyword));
		}

	finish:

		FreeGkString(gstr);
		FreeGkString(avoidgstr);
		FreeGkword(dummyword);
		gstr = avoidgstr = NULL;
		dummyword = NULL;
		
/*fprintf(stderr,"keys:%s\n", keys );*/
}

is_pass_stem(stype)
Stemtype stype;
{
	
/*
		if( stype == GetStemNum("aor_pass") || stype == GetStemNum("aor2_pass") )
*/
		if( (stype & VERBSTEM ) == PP_AP )
			return(1);
		return(0);
}

is_mp_stem(stype)
Stemtype stype;
{
/*
		if( stype >= GetStemNum("perfp_g") && stype <= GetStemNum("perfp_r") )
*/
		if( (stype & VERBSTEM ) == PP_PP )
			return(1);
		return(0);
		
}
		
PrntSynForms(Gkword,gkform,fout)
 gk_word * Gkword;
 gk_word * gkform;
 FILE * fout;
{
	int i;
	char dialbuf[LONGSTRING];
	char linebuf[LONGSTRING*2];
	char tmp[LONGSTRING];
	Dialect d;
	int num, formcnt, CompGkForms();
	
	num = number_of(forminfo_of(gkform));
	for(formcnt=0;workword_of((gkform+formcnt))[0];formcnt++) ;
/*
printf("formcnt=%d\n", formcnt);
*/

	if( ! gkform ) return;

/*
	fprintf(stderr,"formcnt:%d\n", formcnt );
*/
	
	qsort(gkform,formcnt,sizeof * gkform,CompGkForms);
	
	if( print_mode == MORPH_INFO ) {
		char tmplem[BUFSIZ];

		strcpy(tmp,workword_of(gkform));
		strcpy(tmplem,lemma_of(gkform));
		stripmetachars(tmp);
		stripdiaer(tmp);
		standalpha(tmplem);
		if(isdigit(tmplem[strlen(tmplem)-1]))
			tmplem[strlen(tmplem)-1] = 0;
		if( strcmp(tmp,tmplem)) {
			char tmp2[BUFSIZ];

			strcpy(tmp2,workword_of(gkform));
			standalpha(tmp2);
			stripmetachars(tmp2);
			stripdiaer(tmp2);
			if( strcmp(tmp2,tmplem) && !is_exception(tmp2,tmplem) ) 
				fprintf(fout,":st:%s %s\n", tmp, lemma_of(Gkword));
		}
		return;
	}
	if( print_mode == FULL_DUMP ) {
		for(i=0;i<formcnt;i++) {
			char tmp[BUFSIZ*2];
			if( number_of(forminfo_of(gkform+i)) == DUAL ) continue;
			tmp[0] = 0;
			/*stripquant( workword_of(gkform+i) );*/
			fprintf(fout,"<G>%s</G> ", workword_of(gkform+i) );
			SprintGkFlags(ends_gstr_of(gkform+i),tmp," ",1);
			fprintf(fout,"%s\n", tmp );
		}
		return;
	}
	

/*
for(i=0;i<formcnt;i++) {
char tmp[LONGSTRING];

tmp[0] = 0;
SprintGkFlags(gkform+i,tmp," ");
printf("%d) %s\t%s\t%o\n", i, workword_of(gkform+i) , tmp, 
dialect_of(ends_gstr_of(gkform+i) ));
}
*/
	dialbuf[0] = linebuf[0] = 0;
	Xstrncpy(linebuf,"?",sizeof linebuf);
	if( (Is_adjform(gkform) || Is_nounform(gkform) || 
			Is_participle(gkform))  && ! Is_irregform(morphflags_of(gkform)) ) {
		for(i=0;i<formcnt;i++) {
			if( i == 0 ) Xstrncat(linebuf,"$",sizeof linebuf);
			if( i > 0 ) Xstrncat(linebuf,", ",sizeof linebuf);
			Xstrncat(linebuf, workword_of(gkform+i),sizeof linebuf );
		}
		if( Is_participle(gkform) ) {
			Xstrncat(linebuf,"& ",sizeof linebuf);
		    Xstrncat(linebuf , NameOfStemtype(stemtype_of(gkform)),sizeof linebuf );
		    Xstrncat(linebuf , " ",sizeof linebuf);
			AddParadigmInfo(linebuf,forminfo_of(gkform)," ");
		} else if( Is_nounform(gkform) && ! Is_irregform(morphflags_of(gkform)) ) {

			switch(gender_of(forminfo_of(gkform))) {
				case MASCULINE|FEMININE:
					if( num == PLURAL )
						Xstrncat(linebuf,", oi(, ai(",sizeof linebuf);
					else
						Xstrncat(linebuf,", o(, h(",sizeof linebuf);
					break;
				case MASCULINE:
					if( num == PLURAL )
						Xstrncat(linebuf,", oi(",sizeof linebuf);
					else
						Xstrncat(linebuf,", o(",sizeof linebuf);
					break;
				case FEMININE:
					if( num == PLURAL )
						Xstrncat(linebuf,", ai(",sizeof linebuf);
					else
						Xstrncat(linebuf,", h(",sizeof linebuf);
					break;
				case NEUTER:
					if( num == PLURAL )
						Xstrncat(linebuf,", ta/",sizeof linebuf);
					else
						Xstrncat(linebuf,", to/",sizeof linebuf);
					break;
				default:
					break;
				}
			}
			Xstrncat(linebuf,"& ",sizeof linebuf);
	} else {
		char tmp[LONGSTRING];
		sprintf(tmp,"$%s, &%s ", workword_of(gkform) , NameOfStemtype(stemtype_of(gkform)) );
		if( derivtype_of(gkform) ) {
			Xstrncat(tmp,NameOfDerivtype(derivtype_of(gkform)),sizeof tmp);
			Xstrncat(tmp," ",sizeof tmp);
		}
		Xstrncat(linebuf,tmp,sizeof linebuf);
		AddParadigmInfo(linebuf,forminfo_of(gkform)," ");

		if( Is_irregform(morphflags_of(gkform)) || person_of(forminfo_of(gkform)) != PERS1) {
			if( Is_verbform(gkform) ) {
				AddPersNumInfo(linebuf,forminfo_of(gkform)," ");
				AddAdjInfo(linebuf,forminfo_of(gkform)," ");
			} else {
				AddAdjInfo(linebuf,forminfo_of(gkform)," ");
				AddPersNumInfo(linebuf,forminfo_of(gkform)," ");
			}
		}
	}
	
	if(!(d=(dialect_of(stem_gstr_of(gkform)))&(dialect_of(ends_gstr_of(gkform))))) {

		d = ((dialect_of(prvb_gstr_of(gkform)))|(dialect_of(aug1_gstr_of(gkform)))|
			 (dialect_of(stem_gstr_of(gkform)))|(dialect_of(ends_gstr_of(gkform))));

		if( dialect_of(aug1_gstr_of(gkform)) ) 
			d &= dialect_of(aug1_gstr_of(gkform));
	}
	if( dialect_of(Gkword) )
		d &= dialect_of(Gkword);
		 
	if( showdialect || (d && d != ATTIC) )	{			
		DialectNames(d,dialbuf," ");
		if( dialbuf[0] ) {
			Xstrncat(linebuf," ",sizeof linebuf);
			Xstrncat(linebuf, dialbuf ,sizeof linebuf);
		}
	}

	dialbuf[0] = 0;
	GeogRegionNames(geogregion_of(gkform),dialbuf," ");
	if( dialbuf[0] ) {
		strcat(linebuf," "); 
		strcat(linebuf,dialbuf );
	}
		

	dialbuf[0] = 0;
	add_morphflags(gkform,morphflags_of(stem_gstr_of(gkform)));
	add_morphflags(gkform,morphflags_of(prvb_gstr_of(gkform)));
	add_morphflags(gkform,morphflags_of(aug1_gstr_of(gkform)));
	add_morphflags(gkform,morphflags_of(ends_gstr_of(gkform)));
	MorphNames(morphflags_of(gkform),dialbuf," ",1);
	if( dialbuf[0] ) {
			Xstrncat(linebuf," ",sizeof linebuf);
			Xstrncat(linebuf, dialbuf,sizeof linebuf );
	}
	if( Has_crasis(Gkword) ) {
		char tmp[MAXWORDSIZE];
		
		sprintf(tmp," crasis $%s& ", crasis_of(Gkword) );
		Xstrncat(linebuf, tmp,sizeof linebuf );
	}
	dialbuf[0] = 0;
	DomainNames(domains_of(gkform),dialbuf," ");
	if( dialbuf[0] ) {
		strcat(linebuf," &1"); 
		strcat(linebuf,dialbuf );
		strcat(linebuf,"&");
	}

		
	if(oddkeys_of(Gkword) && *(oddkeys_of(Gkword))) {
		Xstrncat(linebuf," ",sizeof linebuf);
		Xstrncat(linebuf,oddkeys_of(Gkword),sizeof linebuf);
		ShowOddKeys(lemma_of(Gkword),oddkeys_of(Gkword));
	}
	Xstrncat(linebuf,"\n",sizeof linebuf);

	proc_beta(linebuf,fout,TO_SMARTA);
}

zap_hyph(s)
register char * s;
{
	while(*s) {
		if( *s == '-' ) {
			strcpy(s,s+1);
			continue;
		}
		s++;
	}
}

zap_rootmarker(s)
register char * s;
{
	while(*s) {
		if( *s == '!' ) {
			strcpy(s,s+1);
			continue;
		}
		s++;
	}
}

proc_beta(buf,fout,to_xlit)
char * buf;
FILE * fout;
int to_xlit;
{
	char res[8000];
	
return;
	stripshortmark(buf);
	
	/* clear out white space and junk left at the start of lines
	*/
	while(isspace(*buf)) buf++;
	if( *buf == '%' && *(buf+1) == '1' ) {
			buf++; buf++;
			if( isdigit(*buf) ) buf++;
			while(isspace(*buf) ) buf++;
	} else if( *buf == ':' || *buf == ';' || *buf == ',' ) {
		buf++;
		while(isspace(*buf)) buf++;
	}
fprintf(fout,"\t%s",buf );
return;
	if(to_xlit == TO_SMARTA )
		beta2smarta(buf,res);
	else if(to_xlit == TO_SMK ) 
		beta2smk(buf,res);
	fprintf(fout,"%s", res);
}

zap_tabs(s)
char * s;
{
	while(*s) {
		if(*s == '\t' ) *s = ' ';
		s++;
	}
}

int
is_exception(char *s1, char * s2)
{
	char tmp1[BUFSIZ], tmp2[BUFSIZ];

	strcpy(tmp1,s1);
	strcpy(tmp2,s2);

	/* 
 	 * if one ends in oos or ous, see if the other does too 
 	 */
	if( strcmp(s1+strlen(s1)-3,"oos") || strcmp(s1+strlen(s1)-3,"ous")) {
		tmp1[strlen(tmp1)-3] = 0;
		if( strcmp(s2+strlen(s2)-3,"oos") || strcmp(s2+strlen(s2)-3,"ous")) {
			tmp2[strlen(tmp2)-3] = 0;
			if( !strcmp(tmp1,tmp2) ) return(1);
		}
	}
	return(0);
}
