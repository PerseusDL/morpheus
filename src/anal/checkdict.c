#include <gkstring.h>
#include <modes.h>
#define MAXPPARTS 12

#include "checkdict.proto.h"
gk_word * GenStemForms();
static int count = 0;
char * 	GetLemmStem();

extern verbose;

checkdict(gk_word *Gkword, gk_string *stem, char *stemkeys)
{
	int i, j;
	int hits;
	gk_word * gkforms = NULL;
	char tmp[MAXWORDSIZE];
	gk_word SaveGkword;
	char * prevb = preverb_of(Gkword);
	char * pbptr;
	char curkeys[LONGSTRING+1];
	char keyp[LONGSTRING+1];
	char *is_substring();

	hits = 0;
	
/*
 * grc 2/13/87
 *
 * putative stem may not be same as actual stem.
 * e.g., we wanted to analyze "Ka=ra", but the analyzer wanted
 * "Ka/ra", ie. it didn't remember that the 'a' was long and
 * needed a circumflex.
 *   turns out that it was not looking at the stem that it
 * got from the dictionary (which was "Ka-r"), but at the
 * stem that it had deduced ("Kar" which does not have the long mark).
 */
	
	SaveGkword = *Gkword;
	Xstrncpy(curkeys,stemkeys,LONGSTRING);

	*stem_gstr_of(Gkword) = * stem;
	if( has_morphflag(morphflags_of(stem),SYLL_AUGMENT) ) {
		zap_morphflag(morphflags_of(stem_gstr_of(Gkword)),SYLL_AUGMENT);
		add_morphflag(morphflags_of(Gkword),SYLL_AUGMENT);
	} else 
		zap_morphflag(morphflags_of(Gkword),SYLL_AUGMENT);

	strcpy(keyp , GetLemmStem(curkeys,lemma_of(Gkword),stem_of(Gkword)));
	pbptr = is_substring("pb:",keyp);
	/*
	 * 
	 * grc 7/23/89
	 *
	 * we were failing on words such as a)mna/seie that had an entry
	 * :vs:a)mnas aor1 a_stem doric opt rpb:a)na/
	 *
	 * ignore examples of "rpb:"
	 */
	if( pbptr && pbptr > keyp && *(pbptr-1) == 'r') {
		pbptr = NULL;
	}

/*
fprintf(stderr,"checkdict: stem [%s] endstring [%s] keyp [%s]\n", stem_of(Gkword) , endstring_of(Gkword) , keyp);
*/
	/*
	 * if this stem has a preverb and you don't want a preverb, punt this
	 * possibility
	 */
	if( pbptr )
	 	if( prevb[0] == 0 ) 
	 		return(0);
	
	if( prevb[0] ) {
		if( pbptr == NULL )  {
			Xstrncat(keyp,":pb:",LONGSTRING);
			Xstrncat(keyp,prevb,LONGSTRING);
		}
		/*
		 * if this stem already has a preverb and it differs
		 * from the one that you assume here, don't bother going
		 * any further.
		 */
		else {
			char tmppb[LONGSTRING];
			
			strcpy(tmppb,pbptr+3);
			if( *(lastn(tmppb,1)) == ':' ) *(lastn(tmppb,1)) = 0;
	/*
	 * grc 6/29/89
	 * suppose you start with a)nali/skw and you want to analyze e)canali/skw
	 *
	 * just make sure that the last preverbs match.
	 */
			if(Xstrncmp(tmppb,lastn(prevb,Xstrlen(tmppb)),Xstrlen(prevb)))
				goto finish;
			Xstrncat(keyp,":pb:",LONGSTRING);
			Xstrncat(keyp,prevb,LONGSTRING);
		}
	} 

	subchar(keyp,':',' ');
	gkforms = GenStemForms(Gkword,keyp,ANALYSIS);

/*
 * grc 2/14/87
 *
 * yet another ugly kludge
 *
 * if you couldn't get any forms if you 
 * looked for the accent on the ending,
 * try stripping the accent
 */
	if( ! gkforms ) {
/*
 * if the accent landed on the ending because this particular
 * stem takes a persistent accent on the ending
 * 	e.g.  i)sxu/s
 * or if our "stem" is 0 syllables long
 *	e.g.  Trw=es, which we segment Tr + w=es
 * or if you may have a third declension monosyllabic stem
 *	e.g.  nu/c, nukto/s
 */
		if( Is_ultima_accent(morphflags_of(Gkword)) || 
		     nsylls(stem_of(Gkword)) == 0 ||
		     poss_thirdmono(stemtype_of(Gkword),
			stem_of(Gkword),
			endstring_of(Gkword) ) ) {
				stripacc(endstring_of(Gkword));
				gkforms = GenStemForms(Gkword,keyp,ANALYSIS); 
		}
	}	

	if( ! gkforms ) {
		*Gkword = SaveGkword;
		return(0);
	}
	hits += CheckGenWords(Gkword,gkforms);
	
	finish:

		* prvb_gstr_of(Gkword) = * prvb_gstr_of(&SaveGkword);
		* aug1_gstr_of(Gkword) = * aug1_gstr_of(&SaveGkword);
		* stem_gstr_of(Gkword) = * stem_gstr_of(&SaveGkword);
		* ends_gstr_of(Gkword) = * ends_gstr_of(&SaveGkword);
	
		if( gkforms ) {
			FreeGkString(gkforms);
			gkforms = NULL;
		}
	
		return(hits);
}
	
char *
GetLemmStem(char *keys, char *lemma, char *stem)
{
	register char * a;
	
	if( *keys == ':' ) keys++;
	
	a = lemma;
	while(*keys&&*keys!=':') *a++ = *keys++;
	*a = 0;
	if( *keys == ':' ) keys++;

	a = stem;
	while(*keys&&*keys!=':') *a++ = *keys++;
	*a = 0;
	if( *keys == ':' ) keys++;
	return(keys);
	
	
}
