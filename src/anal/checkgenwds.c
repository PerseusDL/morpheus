#include <gkstring.h>

#include "checkgenwds.proto.h"

static anals_seen = 0;
static lems_seen = 0;

/*
 * ok, check an array of gk_string's against a single printword to figure
 * out which ones really do match. this is where we distinguish between
 * "pisteu=sai" "pi/steusai" and "pisteu/sai"
 */

CheckGenWords(gk_word *Gkword, gk_word *gkforms)
{
	int i = 0;
	int hits = 0;
	char accword[MAXWORDSIZE+1];
	char wordnoacute[MAXWORDSIZE+1];
	char curform[MAXWORDSIZE+1];
	char * checks;
	char * preverb = preverb_of(gkforms);
	char * lemma = lemma_of(gkforms);
/* grc 6/8/89
	char * origword = rawword_of(gkforms);
*/
	char * origword = workword_of(Gkword);

	Xstrncpy(accword,origword,(int)sizeof accword);
	/*
	 * grc 10/24/87
	 *
	 * if you have a form such as "h(/bwsa", just leave it 
	 * but if you have something like "e)nh(/bwsa", where the
	 * rough breathing is marked, even after the preverb, try
	 * standardizing the orthography here.
	 *
	 * we leave this to such a late stage in the process, so that
	 * Morpheus will be able to take advantage of the fact that the
	 * rough breathing was marked.
	 */

	 zap_extra_breath(accword);
/*
 * note that diaeresis is so intermittently included that
 * you had best just ignore it at this stage.
 */
	stripdiaer(accword);

	stripquant(accword);
	Xstrncpy(wordnoacute,accword,(int)sizeof  wordnoacute);
	
/*
 *	no-- don't strip all accents. the only reason you do this is so that you can
 *	match words such as enclitics in which the accent is variable, but enclitics never
 *	take circumflexes! you don't want to interpret "ei)=si" as being from ei)mi/.
	stripacc(wordnoacute);
 *
 * grc 12/30/89
 * ho! ho! ho! not so fast--tinw=n does in fact take a circumflex. nevertheless, best to
 * leave this as is and put "tinw=n" accented into the dictionary.  otherwise, it will
 * be messy distinguishing between ei)si/ and ei)=si.
 */
 	stripacute(wordnoacute);
	
/*
printf("\nin checkgenword accword [%s]\n", accword );
*/

	hits = 0;

	for(i=0;workword_of((gkforms+i))[0];i++) {

		Xstrncpy(curform,workword_of(gkforms+i),(int)sizeof  curform);
/*
 * if we are looking at an enclitic that does not have
 * a preverb, we will not have generated it with an accent
 * (that would only come from interacting with possible words
 * around it). thus we ignore the accent on the original word.
 * 
 * this allows us to match "e)/sti" or "e)sti/" with "e)sti"
 *
 * NOTE THOUGH, that if you use this algorithim, 
 * "ti/" would match "ti"! 
 */
	if( (prntflags_of(Gkword) & IGNORE_ACCENTS) ) {
		char wordnoacc[MAXWORDSIZE];

		strcpy(wordnoacc,wordnoacute);
		stripacc(wordnoacc);
		checks = wordnoacc;
	
		stripacc(curform);
	} else 
		if( Is_enclitic(morphflags_of(stem_gstr_of(gkforms+i))) && ! * preverb ) {
			checks = wordnoacute;
		} /* else if( Is_proclitic(morphflags_of(gkforms+i)) ) {
			checks = wordnoacute;
	    } */else {
			checks = accword;
		}
/*
 *	grc 7/22/89
 *
 * added this routine because we were failing on tou)/neka.  the breathing was punted
 * from checks but not from curform.
 */
 	 zap_extra_breath(curform);
/*
 * grc 8/26/93
 *
 * added this routine because we were failing on qa/lamo/nde etc.
 */
 	 zap2acc(curform);

if( *(lastn(curform,1)) == HARDLONG && *(lastn(origword,1)) == HARDSHORT )  {
/*
printf("failed with curform [%s] and origword [%s]\n", curform , origword );
*/
	continue;
}
		stripdiaer(curform);
		stripmetachars(curform);
/*
printf("workword is [%s]\n", workword_of(gkforms+i));
fprintf(stdout,"comparing [%s] and [%s]\n", curform , checks );
fputc('\n',stdout);
fprintf(stderr,"onwards\n");
*/
		if( !morphstrcmp( curform , checks )) {
/*
			if(*preverb && !Check_preverb(Gkword,gkforms+i) ) {
					near_miss(gkforms+i,checks,0);
					continue;
			}
*/
			if( Comp_only(morphflags_of(stem_gstr_of(gkforms+i))) && ! * preverb ) {
				near_miss(gkforms+i,checks,COMP_ONLY);
/*
				printf("could be--[%s]",workword_of(gkforms+i));
				PrntAVerb(gkforms+i,lemma,stdout);
			printf("but this only shows up in composition\n");
*/

				continue;
			} 
			if( Not_in_compos(morphflags_of(stem_gstr_of(gkforms+i))) && *preverb ) {
				near_miss(gkforms+i,checks,NOT_IN_COMPOSITION);
/*
				printf("could be--[%s]",workword_of(gkforms+i));
				PrntAVerb(gkforms+i,lemma,stdout);
			printf("but this does not show up in composition\n");
*/
				continue;

			}


			if( AddAnalysis(Gkword,gkforms+i) )
				hits++;
/*
printf("liked [%s] hits [%d]\n", checks , hits);
*/

			continue;
		} 
		near_miss(gkforms+i,checks,0);
/*
		printf("wanted [%s] and got ", checks );
		PrntAVerb(gkforms+i,lemma,stdout);
*/
		
	}
	return(hits);
}

static analerror  = 0;
AddAnalysis(gk_word *Gkword, gk_word *gkform)
{
	gk_analysis * curanal;
	int i;
	int newlem = 1;
	char tmplem[MAXWORDSIZE];
	char cmplem[MAXWORDSIZE];

	if (analerror) {
		fprintf(stderr,"something wrong with the analysis storage!\n");
		return(0);
	}

	if( analysis_of(Gkword) == NULL ) {
		if( ! ( analysis_of(Gkword) = (gk_analysis *)CreatGkAnal(MAXANALYSES+1) )) {
			fprintf(stderr,"not enough memory for greek analysis\n");
			analerror++;
			return(0);
		}
		if( totanal_of(Gkword) != 0 ) {
			fprintf(stderr,"hey! anal pointer NULL but totanal is %d\n", totanal_of(Gkword) );
			analerror++;
			return(0);
		}
	}


/*
	GenDictEntry(gkform,tmplem);
	if(strcmp(tmplem,lemma_of(gkform)) set_dictform(gkform,tmplem);
*/

	if( totanal_of(Gkword) >= MAXANALYSES ) {
		fprintf(stderr,"%s:  ran out of space with %d analyses!\n",
			rawword_of(Gkword), totanal_of(Gkword) );
		return(0);
	} 
	curanal = analysis_of(Gkword) + totanal_of(Gkword);
	
	if( crasis_of(gkform)[0] ) {
		set_crasis(curanal,crasis_of(gkform));
		if( ! do_crasis(gkform,crasis_of(curanal)))
			return(0);
	}

	 cmplem[0] = 0;
	if( preverb_of(gkform)[0] ) {
		char * s = tmplem;
		char * t;
		char tmphalf1[MAXWORDSIZE];
		tmphalf1[0] = tmplem[0] = cmplem[0] = 0;
		
		sprintf(tmplem,"%s-%s", preverb_of(gkform) , lemma_of(gkform));
		for(;;) {
			/*
			 * grc 6/12/94
			 *
			 * if you have an entry for u(poba/llw
			 * but you are looking at a)nti/,u(po/-ba/llw
			 * send the user to a)nti,-u(poba/llw
			 * not a)nti/,u(po/-ba/llw
			 *
			 */
/*
printf("tmphalf1 [%s] s [%s]\n", tmphalf1, s );
*/
			chckcmpvb(s,cmplem);
			if( cmplem[0] ) {
				if( tmphalf1[0] ) {
					strcat(tmphalf1,"-");
					strcat(tmphalf1,cmplem);
					strcpy(cmplem,tmphalf1);
				}
				break;
			}
			
			t = s;
			s = strchr(s,',');
/*
printf("s [%s] tmplem [%s] tmphalf1 [%s] t [%s] cmplem[%s]\n", s , tmplem , tmphalf1 ,t, cmplem);
*/
			if(!s ) {
				if( tmphalf1[0] ) strcat(tmphalf1,",");
				strcat(tmphalf1,t);
				strcpy(tmplem,tmphalf1);
				 break;
			}
			*s++ = 0;
			if( tmphalf1[0] ) strcat(tmphalf1,",");
			strcat(tmphalf1,t);
/*
printf("tmphalf1 [%s] tmplem[%s] s [%s]\n", tmphalf1 , tmplem, s);
*/
		}
		if( cmplem[0] ) {
			set_lemma(curanal,cmplem);
		} else
			set_lemma(curanal,tmplem);
	}  else
		set_lemma(curanal,lemma_of(gkform));

/*
printf("lemam now [%s]\n", lemma_of(curanal) );
*/
	set_preverb(curanal,preverb_of(gkform));

	* (prvb_gstr_of(curanal)) = * (prvb_gstr_of(gkform));
	* (aug1_gstr_of(curanal)) = * (aug1_gstr_of(gkform));
	* (stem_gstr_of(curanal)) = * (stem_gstr_of(gkform));
	* (ends_gstr_of(curanal)) = * (ends_gstr_of(gkform));

	set_rawword(curanal,rawword_of(gkform));
	set_workword(curanal,workword_of(gkform));
	
	forminfo_of(curanal) = forminfo_of(gkform);

	set_geogregion(curanal,geogregion_of(gkform));
/*
	add_geogregion(curanal,geogregion_of(Gkword));
*/

	set_dialect(curanal,(dialect_of(prvb_gstr_of(curanal))|
					     dialect_of(aug1_gstr_of(curanal))|
					     dialect_of(stem_gstr_of(curanal))|
					     dialect_of(ends_gstr_of(curanal))));

	if( Has_apocope(morphflags_of(prvb_gstr_of(gkform))) ) {
 		if((dialect_of(Gkword) & HOMERIC ) )
			add_dialect(curanal,(Dialect)HOMERIC);
		if( dialect_of(Gkword) != HOMERIC )
			add_morphflag(morphflags_of(curanal),POETIC);
	}
	
	if( Has_unasp_preverb(morphflags_of(prvb_gstr_of(gkform)))&& 
		getbreath(stem_of(gkform)) == ROUGHBR ) {
			Dialect d;
			 if ((d=AndDialect(dialect_of(prvb_gstr_of(gkform)),(Dialect)IONIC)) < 0) 
			 	return(0);
			 d = AndDialect(dialect_of(curanal),(Dialect)IONIC);
			 set_dialect(curanal,d);
	}
/*
	if( ((has_morphflag(morphflags_of(prvb_gstr_of(gkform)),POETIC) ) 
	          || Has_apocope(morphflags_of(prvb_gstr_of(gkform)))) 
	          && (dialect_of(Gkword) & PROSE)) {
		return(0);
	}
*/
	if( cur_lang() != LATIN && has_morphflag(morphflags_of(stem_gstr_of(gkform)) , UNAUGMENTED ) ) {
		if( dialect_of(curanal)) 
			add_dialect(curanal,(dialect_of(curanal) & (HOMERIC|IONIC)) );
		else
			add_dialect(curanal,(HOMERIC|IONIC) );
/*
 grc 6/27/95
 * i don't think so -- lack of augment ain't poetic in hdt!
   in a tragic RHESIS, its poetic because its epic/ionic.
		add_morphflag(morphflags_of(prvb_gstr_of(gkform)),POETIC) ;
 */
	/*
	 * grc 3/20/91
	 *
	 * don't accept any unaugmented forms unless you are working with the indicative
	 * -- otherwise its not a meaningful form!
	 *
	 * e)lastrh/seis is not a 2nd sg short subj aor that is unaugmented!
	 */
	 	if( mood_of(forminfo_of(curanal)) != INDICATIVE ) return(0);
	}
	set_stemtype(curanal,stemtype_of(gkform));
	set_derivtype(curanal,derivtype_of(gkform));
	set_morphflags(curanal,morphflags_of(gkform));
	add_morphflags(curanal,morphflags_of(prvb_gstr_of(gkform)));
	add_morphflags(curanal,morphflags_of(stem_gstr_of(gkform)));
	add_morphflags(curanal,morphflags_of(ends_gstr_of(gkform)));
/*
printf("analysis [%s] [%o]", rawword_of(curanal), dialect_of(curanal) );
PrntAWord(curanal,Gkword,lemma_of(curanal),stdout);
printf("prvb: "); PrntAGstr(prvb_gstr_of(curanal),stdout);
printf("aug1: "); PrntAGstr(aug1_gstr_of(curanal),stdout);
printf("stem: "); PrntAGstr(stem_gstr_of(curanal),stdout);
printf("ends: "); PrntAGstr(ends_gstr_of(curanal),stdout);

printf("\n");
*/
	/*
	 * if this is just a duplicate of some other analysis, do not
	 * increment totanal_of(Gkword) -- thus leaving this redundant
	 * analysis out.
	 */
	for(i=0;i<totanal_of(Gkword);i++) {
		if( equiv_anal(curanal,analysis_of(Gkword)+i) ) {
			merge_anal_dialects(analysis_of(Gkword)+i,curanal);

			return(0);
		}
		if( !strcmp(lemma_of(curanal),lemma_of(analysis_of(Gkword)+i))) {
			newlem = 0;
		}
	}
	totanal_of(Gkword)++;
	anals_seen++;
	lems_seen += newlem;
	return(1);
}

show_totanals()
{
	return(anals_seen);
}

show_totlems()
{
	return(lems_seen);
}

merge_anal_dialects(gk_analysis *anal1, gk_analysis *anal2)
{
	/*
	 * grc 3/10/91:  if anal1 has no dialects set, then this form can appear in
	 * any dialect.  don't add false constraints here.
	 */
	 if( dialect_of(anal1) )
		dialect_of(anal1) |= dialect_of(anal2);	
}

equiv_anal(gk_analysis *anal1, gk_analysis *anal2)
{	
	if( strcmp(lemma_of(anal1),lemma_of(anal2))) 
		return(0);
	/*
	 * grc 2/16/88
	 *
	 * we were getting extraneous analyses from the form a)=gon:
	 *
	 * first, Morpheus would find the stem "a)_g" in the dictionary
	 * as the augmented doric imperfect, and would come up with the
	 * analyses.
	 * 
	 * then, Morpheus would come up with the same forms by augmenting
	 * the normal stem "a)g" to Doric "a)_g".
	 *
	 * this routine was not seeing the fact that it had redundant analsyses
	 * because the stems ("a)_g" vs. "a)g") were different.
	 * 
	 * i have therefore removed the stem comparison: heaven knows what 
	 * awful side effects this may have...
	 */
	/*if( strcmp(stem_of(anal1),stem_of(anal2))) return(0);*/
	if( strcmp(aug1_of(anal1),aug1_of(anal2))) return(0);
	if( strcmp(preverb_of(anal1),preverb_of(anal2))) return(0);
	if( strcmp(workword_of(anal1),workword_of(anal2))) return(0);
	if( strcmp(endstring_of(anal1),endstring_of(anal2))) return(0);
		
	if( ! eq_forminfo(forminfo_of(anal1),forminfo_of(anal2))) return(0);
	
	/*
	 * don't check for simple equivalence.
	 * thus, if anal2 has homeric and ionic, but anal1 has simply ionic, then anal1
	 * makes no contribution to the overall analysis (at least as far as dialects are
	 * concerned
	 */
/* grc 2/16/88 -- ignore dialects for now
 * grc 8/24/88 -- put the dialects back in */
/* grc 9/1/88 -- put them back in: don't need analysis a stating that the word
 * is ionic while analysis b says that it could be ionic and epic -- analysis a 
 * is a subset of analysis b and should be ignored 
	if( (dialect_of(anal2) | dialect_of(anal1)) != dialect_of(anal2)) return(0);
	if( dialect_of(anal2) && ! dialect_of(anal1)) return(0);
*/
/* grc 3/10/91
 * ugh -- we need the damn dialects.  somehow we are getting forms such as
 * a)dikei=te listed as doric imperatives rather than just as standard greek.
 *
 * this case states that if the existing form is not marked for any dialects, but the new
 * one is, ignore the new one, since this form can appear anywhere in greek.
 */
/*
 * grc 3/20/91
 * we are getting the analyses of a)kolouqh/sei as a doric futperf (with a)_kol--) and
 * an ionic-epic form in which the redup/augment simply does notshow up.
 * 
 * if dial2 and dial1 aren't the same and if dial2 is not a subset of dial1, then
 * keep them separate
 *
 	if( dialect_of(anal2) && 
 		((dialect_of(anal2) & (dialect_of(anal1))) == 0) ) return(0);
 * grc 3/20/91
 * gave up again trying to get this to work
 */
/*
 *  grc -- zap it for now -- does not seem to have solved the problem
 	if(  dialect_of(anal1) && dialect_of(anal2)) return(0);
 */


/* 
 * grc 8/2/95
 *  
 * if you have qhra/sw that could be aeolic/doric (all alphas)
 * or have the alpha in Attic because of the rho, then keep them
 * separate...
 */
	if( has_morphflag(morphflags_of(stem_gstr_of(anal1)),R_E_I_ALPHA) != 
	    has_morphflag(morphflags_of(stem_gstr_of(anal2)),R_E_I_ALPHA))
			return(0);

	if(stemtype_of(anal1) != stemtype_of(anal2)) return(0);
	
	return(1);
}
