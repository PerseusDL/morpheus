#include <gkstring.h>
static gk_word Blnk;
static char curlemma[LONGSTRING];
static gk_string BlnkGstr;
gk_word *  GenStemForms(gk_word *,char *,int);
gk_word *  GenIrregForm(gk_word *,char *,int);
int CompGkForms(gk_word *gkform1, gk_word *gkform2);

 GenStemLink(FILE * f,FILE * fout)
{
	gk_word * Rvals = NULL;
	gk_word *Gkword;
	char line[BUFSIZ*4];
	char baseentry[LONGSTRING], * stemkeys;
	int nl = 0;

	Gkword = CreatGkword(1);
	if( ! Gkword ) {
		fprintf(stderr,"failed to get memory in GenSynForms!\n");
		return(-1);
	}
	
	while(fgets(line,sizeof line,f)) {
		char saveline[BUFSIZ*4];

		fflush(fout);
		strcpy(saveline,line);
		*Gkword = Blnk;
		if( ! strncmp(line,":le:",4) ) {
			strcpy(curlemma,line+4);
			if( curlemma[strlen(curlemma)-1] == '\n' )
				curlemma[strlen(curlemma)-1] = 0;
			fprintf(fout,"%s", line );
			continue;
		}
		/*
		 * process a regular stem
		 */
		else if( !strncmp(line,":aj:",4) || ! strncmp(line,":no:",4) || ! strncmp(line,":vs:",4)) {
			gk_string Gstr;
			
			Gstr = BlnkGstr;
			
			zap_rootmarker(line);
			set_baseentry(line,baseentry,(int)sizeof line);

			stemkeys = line;
			while(*stemkeys&&!isspace(*stemkeys)) stemkeys++;
			if( isspace(*stemkeys) ) *stemkeys++ = 0;
			while(isspace(*stemkeys)) stemkeys++;

			set_stem(Gkword,line+4);
			set_lemma(Gkword,curlemma);
			paradigm_keys(stemkeys);
/*
printf("stemkeys [%s]\n", stemkeys );
*/
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
		} else {
			fprintf(fout,"%s", line );
			continue;
		}
		if(  Rvals ) {
			PrntSynForms(Gkword,Rvals,fout);
			FreeGkword(Rvals);
		} else {
			fprintf(stderr,"Rvals null!\n");
			fprintf(fout,"Rvals null!\n");
		}
		fprintf(fout,"%s", saveline );
		Rvals = NULL;
		/*set_printword(Gkword,"");*/
		set_stem(Gkword,"");
		set_endstring(Gkword,"");
		if( (oddkeys_of(Gkword) ))  *(oddkeys_of(Gkword)) = 0;
	}
}
