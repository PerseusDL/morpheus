#include <gkstring.h>
#define MAXCRASIS 12

#include "checkcrasis.proto.h"
typedef struct {
 	char crasis[MAXWORDSIZE];
 	char curstring[MAXWORDSIZE];
 	int w_gender;
 	int w_case;
 	int w_number;
 	Dialect possdial;
 } precise_crasis;
 
 precise_crasis CrasTab[] = {
 	"o(",	"ai(",	FEMININE, NOMINATIVE, PLURAL,		0,
 	"o(",	"oi(",	MASCULINE, NOMINATIVE, PLURAL,		0,
 	"o(",	"o(",	MASCULINE, NOMINATIVE, SINGULAR,	0,
 	"o(",	"h(",	FEMININE, NOMINATIVE, SINGULAR,		0,
 	
 	"to/",	"to/",	NEUTER,	NOMINATIVE, SINGULAR,		0,
 	"to/",	"to/",	NEUTER,	VOCATIVE, SINGULAR,			0,
 	"to/",	"to/",	NEUTER,	ACCUSATIVE, SINGULAR,		0,
 	"to/",	"ta/",	NEUTER,	NOMINATIVE, PLURAL,			0,
 	"to/",	"ta/",	NEUTER,	VOCATIVE, PLURAL,			0,
 	"to/",	"ta/",	NEUTER,	ACCUSATIVE, PLURAL,			0,
 	
 	"ta/",	"ta/",	NEUTER,	NOMINATIVE, PLURAL,			0,
 	"ta/",	"ta/",	NEUTER,	VOCATIVE, PLURAL,			0,
 	"ta/",	"ta/",	NEUTER,	ACCUSATIVE, PLURAL,			0,
 	"ta/",	"ta/",	0,		0, 			0,				0,
 	"to/",	"to/",	0,		0, 			0,				0,
/*
 	"e)gw/", "e)gw/", 0,	0,			0,				0,
*/
 	
/*
 	"tou=",	"o(",	NEUTER|MASCULINE,	GENITIVE, SINGULAR,	0,
 	"th=|",	"h(",	FEMININE,		DATIVE, SINGULAR,	0,
 	"tou=",	"o(",	NEUTER|MASCULINE,	DATIVE, SINGULAR,	0,
*/
 };

 
 typedef struct {
 	char mungedword[MAXCRASIS];
 	char wordstart[MAXCRASIS];
 	char preword[MAXCRASIS];
 	Dialect possdial;
 } poss_crasis;
 
 poss_crasis PossCras[] = {

"*)=w",		"*)/a",	"w)=", (Dialect)0,		/* *)=wpollon << w)= *)/apollon */
"*)=w",		"*)e",	"w)=", (Dialect)0,		/* *)wkba/atana << w)= *)ekba/tana */
"ka)",		"*)a",	"kai/", (Dialect)0,		/* k)axerousi/ous << kai\ *)axerousi/ous */
"a(=",		"a)/",	"o(", (Dialect)0,		/* a(=ndres << oi( a)/ndres */
"a(",		"a)",	"o(", (Dialect)0,		/* a(nh/r << o( a)nh/r */
"a(",		"e)",	"a(/", (Dialect)0,		/*  */
"ei(",		"ei)",	"a(/", (Dialect)0,		/* ei(=don << a(\ ei)=don */
"au(",		"au)",	"o(", (Dialect)0,		/* au(to/s << o( au)to/s */
"dau)",		"au)",	"de/", (Dialect)0,		/* dau)=te << de\ au)=te */

"dh)",		"e)",	"dh/", (Dialect)0,		/* dh)/peita << dh\ e)/peita */
"da)",		"a)",	"dh/", (Dialect)0,		/* da)/n << dh\ a)/n */
"hu(",		"eu)",	"h(", (Dialect)0,		/* hu(la/beia << h( eu)la/beia */
"qat",		"e(t",	"tou=", (Dialect)0,		/* qate/rou << tou= e(te/rou */
"qa)/",		"e(/",	"to/", (Dialect)0,		/* qa(/teron << to\ e(/teron */
"qoi)",		"i(",	"to/", (Dialect)0,		/* qoi)ma/tion << to\ i(ma/tion */
"qai)",		"i(",	"ta/", (Dialect)0,		/* qai)ma/tia << ta\ i(ma/tia */
"qou)",		"u(",	"to/", (Dialect)0,		/* qou(/dwr << to\ u(/dwr */
"qou(",		"e(",	"to/", (Dialect)0,		/* qou(/rmaion << to\ e(/rmaion */
"qou)",		"e(",	"to/", (Dialect)0,		/* qou)/rmaion << to\ e(/rmaion */
"qh)",		"h(",	"th=|", (Dialect)0,		/* qh(me/ra| << th=| h(mera| */
"qh)",		"h(",	"tou=", (Dialect)0,		/* qh(mete/rou << tou= h(mete/rou */
"qh)",		"h(",	"to/", (Dialect)0,		/* qh(mete/rou << to\ h(rw=|on */
"qa)",		"e(",	"th=|", (Dialect)0,		/* qa(te/ra| << th=| e(te/ra| */
"qa)",		"a(",	"ta/", (Dialect)0,		/* qa(ma/rtia << ta\ a(ma/rtia */
"qa)",		"e(",	"tou=", (Dialect)0,		/* qa(te/rou << tou= e(te/rou */
"qa/t",		"e(/t",	"to/", (Dialect)0,		/* qa/teron << to\ e(/teron */
"kai)",		"ai)",	"kai/", (Dialect)(DORIC|EPIC),		/* kai) << kai\ ai)  */
"kei)",		"ei)",	"kai/", (Dialect)0,		/* kei) << kai\ ei)  */
"kei)",		"ei)",	"kai/", (Dialect)0,		/* kei) << kai\ ei)  */
"keu)",		"eu)",	"kai/", (Dialect)0,		/* keu)qu/s << kai\ eu)qu/s  */
"ka)=|",	"ei)=",	"kai/", (Dialect)0,		/* ka)=|ta << kai\ ei)=ta  */
"ka)|",		"ai)",	"kai/", (Dialect)0,		/* ka)|sxrw=n << kai\ ai)sxrw=n  */
"ta)|",		"ai)",	"ta/", (Dialect)0,		/* ta)|sxrw=n << ta\ ai)sxrw=n  */
"ka)=",		"a)/",	"kai/", (Dialect)0,		/* ka)=llos << kai\ a)/llos  */
"ka)",		"a)",	"kai/", (Dialect)0,		/* ka)gaqo/s << kai\ a)gaqo/s */
"katta",	"ta",	"kata/", (Dialect)DORIC,		/* katta/ << kata\ ta\ */
"kadd",	"d",	"kata/", (Dialect)EPIC,		/* kaddu/namin << kata\ du/namin */
"ka)",		"e)",	"kai/", (Dialect)0,		/* ka)kei=non << kai\ e)kei=non */
"kw)",		"o)",	"kai/", (Dialect)0,		/* kw)dunwme/nh << kai\ o)dunwme/nh */
"kw)",		"w)",	"kai/", (Dialect)0,		/* kw)=ze << kai\ w)=ze */
"kou)",		"ou)",	"kai/", (Dialect)0,		/* kou)/ << kai\ ou) */
"kau)",		"au)",	"kai/", (Dialect)0,		/* kau)=qis << kai\ au)=qis */
"khu)",		"hu)",	"kai/", (Dialect)0,		/* khu)/xonto << kai\ hu)/xonto */
"moi)",		"oi)",	"mou", (Dialect)0,		/* moi)/xetai << mou oi)/xetai */
"ma)",		"a)",	"mh/", (Dialect)0,		/* ma)dikei=n << mh\ a)dikei=n */
"mh)/",		"e)",	"mh/", (Dialect)0,		/* mh)/sti << mh/ e)sti */
"mou)",		"e)",	"mou", (Dialect)0,		/* mou)/sti << mou e)sti */
"ou(",		"e)",	"o(/", (Dialect)0,		/* ou(/cerw= << o(\ e)cerw= */
"ou(",		"o)",	"o(", (Dialect)0,		/* ou(/fis << o( o)/fis */
"ou(",		"e(",	"o(", (Dialect)0,		/* ou(/teros << o( e(/teros */
"ou(",		"u(",	"o(", (Dialect)0,		/* ou(po/qeis << o( u(po/qeis */
"qw)/",		"o(/",	"ta/", (Dialect)0,		/* qw)/pl' << ta\ o(/pl' */
"pottw/s",	"tw/s",	"poti/", (Dialect)DORIC,		/* pottw/s << poti\ tw/s */
"ta)/|",		"ai)/",	"to/", (Dialect)0,		/* ta)/|tion << to\ ai)/tion */
"ta)=",		"a)/",	"ta/", (Dialect)0,		/* ta)=lla << ta\ a)/lla */
"ta)",		"a)",	"ta/", (Dialect)0,		/* ta)/lla << ta\ a)/lla */
"ta)",		"a)",	"tou=", (Dialect)0,		/* ta)ndro/s << tou= a)ndro/s */
"ta)",		"a)",	"to/", (Dialect)0,		/* ta)gaqo/n << to\ a)gaqo/n */
"ta)/",		"*)/a",	"to/", (Dialect)0,		/* ta)rgos << to\ *)/argos */
"ta)",		"e)",	"ta/", (Dialect)0,		/* ta)kei= << ta\ e)kei= */
"th)",		"e)",	"th=|", (Dialect)0,		/* th)mh=| << th=| e)kmh=| */
"tau)",		"au)",	"tou=", (Dialect)0,		/* tau)toma/tou << tou= au)toma/tou */
"tau)",		"au)",	"to/", (Dialect)0,		/* tau)to/n << to\ au)to/n */
"tu/xa)gaqh=|",		"a)gaqh=|",	"tu/xh|", (Dialect)0,		/* tu/xa)gaqh=| << tu/xh| a)gaqh=| */
"tu/xa)gaqh|",		"a)gaqh=|",	"tu/xh|", (Dialect)0,		/* tu/xa)gaqh=| << tu/xh| a)gaqh=| */
"tw)",		"*)a",	"tou=",	 (Dialect)0,	/* tw)rgei/ou << tou= *)argei/ou */
"tw)",		"a)",	"tou=",	 (Dialect)0,	/* tw)rgei/ou << tou= *)argei/ou */
"tw)",		"a)",	"tou=",	 (Dialect)0,	/* tw)rgei/ou << tou= *)argei/ou */
"tw)=",		"a)/",	"toi/",	 (Dialect)DORIC,	/* tw)=ndres << toi\ a)/ndres */
"tw)",		"w)",	"to/",	 (Dialect)0,	/* tw)|dei=on << to\ w)|dei=on */
"tw)",		"h(",	"to/",	 (Dialect)0,	/* tw)/misu << to\ h(/misu */
"tw)",		"o)",	"tw=|",	 (Dialect)0,	/* tw)nei/rati << tw=| o)nei/rati */
"sou)",		"o(",	"sou",	 (Dialect)0,	/* sou)ri/zei << sou o(ri/zei */
"sou)",		"e(",	"sou",	 (Dialect)0,	/* sou)/neka << sou e(/neka */
"sou)",		"e)",	"sou",	 (Dialect)0,	/* sou)/sti << sou e)/sti */
"tou)",		"o)",	"to/",	 (Dialect)0,	/* tou)/noma << to\ o)/noma */
"tou)",		"e)",	"to/", (Dialect)0,		/* tou)nanti/on << to\ e)nanti/on */
"tou)",		"e)",	"to/", (Dialect)0,		/* tou)/mpalin << to\ e)/mpalin */
"tou)",		"e)",	"tou=", (Dialect)0,		/* tou)mou= << tou= e)mou= */
"tou)=",	"e)/",	"tou=", (Dialect)0,		/* tou)=rgon << tou= e)/rgou */
"tou)=",	"o)/",	"to/", (Dialect)0,		/* tou)=yon << to\ o)/yon */
"tw)",		"e)",	"tw=|", (Dialect)0,		/* tou)mw=| << tw=| e)mw=| */
"tou)",		"ou)",	"tou=", (Dialect)0,		/* tou)ranou= << tou= ou)ranou= */
"tou)",		"e(",	"to/", (Dialect)0,		/* tou)/teron << to\ e(/teron */
"tw)u",		"au)",	"ta/", (Dialect)IONIC,		/* twu)ta/  << ta/ au)ta/ */
"tw)u",		"au)",	"to/", (Dialect)IONIC,		/* twu)to/  << to/ au)to/ */
"tw)u",		"au)",	"tou=", (Dialect)IONIC,		/* twu)tou=  << tou= au)tou= */
"twu)",		"au)",	"ta/", (Dialect)IONIC,		/* twu)to/  << ta/ au)ta/ */
"twu)",		"au)",	"to/", (Dialect)IONIC,		/* twu)to/  << to/ au)to/ */
"twu)",		"au)",	"tou=", (Dialect)IONIC,		/* twu)tou=  << tou= au)tou= */
"tw)",		"a)",	"to/", (Dialect)IONIC,		/* tw)/galma  << to\ a)/galma */
"tw)",		"a)",	"toi/", (Dialect)DORIC,		/* tw)/dres  << toi\ a)/ndres */
"tau)",		"au)",	"to/", (Dialect)0,		/* tau)ta/ << ta\ au)ta/ */
"ou(",		"e)",	"o(",	 (Dialect)0,		/* ou(mo/s << o( e)mo/s */
"prou)",	"proe",	"",	 (Dialect)0,		/* prou)/legon << proe/legon */
"sumprou",		"sumproe",	"",	 (Dialect)0,		/* sumprou/pempe << sumproe/pempe */
"cumprou",		"cumproe",	"",	 (Dialect)0,		/* sumprou/pempe << sumproe/pempe */
"a)ntiprou",		"a)ntiproe",	"",	 (Dialect)0,		/* a)ntiprou/teine << a)ntiproe/teine */
"prou",		"proe",	"",	 (Dialect)0,		/* prou/legon << proe/legon */
"prou",		"proo",	"",	 (Dialect)0,		/* proufeilome/nh << proofeilome/nh */
"prwu",		"proau",	"",	 (Dialect)0,		/* prwuda=n << pro\ au)da=n */
"e)gw)=i",	"oi)=", "e)gw/", (Dialect)0,	/* e)gw)=|mai << e)gw/ + oi)=mai */
"e)gw)=|",	"oi)=", "e)gw/", (Dialect)0,	/* e)gw)=|mai << e)gw/ + oi)=mai */
"e)gw=|",	"oi)=", "e)gw/", (Dialect)0,	/* e)gw=|da << e)gw/ + oi)=da */
"e)mou)",	"e)", "e)moi", 	(Dialect)0,		/* e)mou)/sti << e)moi e)/sti */
"kh)",		"E)",	"kai/",	 (Dialect)0,	/* kh)k  < kai/ + e)k */
"kh)",		"e)",	"kai/",	 (Dialect)0,	/* kh)leusu/nia  < kai/ + E)leusu/nia */
"xh)",		"h(",	"kai/",	 (Dialect)0,	/* xh)mei=s  < kai/ + h(mei=s */
"xh(",		"h(",	"kai/",	 (Dialect)0,	/* xh)mei=s  < kai/ + h(mei=s */
"xa)",		"a(",	"kai/",	 (Dialect)DORIC,	/* xa)  < kai/ + a( */
"xa)",		"e(",	"kai/",	 (Dialect)0,	/* xa)te/rwn  < kai/ + e(te/rwn */
"xai)",		"ai(",	"kai/",	 (Dialect)0,	/* xai)  < kai/ + ai( */
"xoi)",		"oi(",	"kai/",	 (Dialect)0,	/* xoi)  < kai/ + oi( */
"xau)",		"au(",	"kai/",	 (Dialect)0,	/* xau)/th  < kai/ + au(/th */
"xou)",		"ou(",	"kai/",	 (Dialect)0,	/* xou)=tos  < kai/ + ou(=tos */
"xu)",		"u(",	"kai/",	 (Dialect)0,	/* xu)mei=s  < kai/ + u(mei=s */
"xw)",		"o(",	"kai/",	 (Dialect)0,	/* xw)po/qen  < kai/ + o(po/qen */
"xw(",		"o(",	"kai/",	 (Dialect)0,	/* xw(po/qen  < kai/ + o(po/qen */
"xw)",		"w(",	"kai/",	 (Dialect)0,	/* xw)=nper  < kai/ + w(=nper */
"w(n",		"a)n",	"o(",	 (Dialect)0,	/* w(nh/r < o( + a)nh/r */
"w(/n",		"a)/n",	"oi(",	 (Dialect)0,	/* w(/nqrwpoi < oi( + a)/nqrwpoi */
"w(u",		"au)",	"o(",	 (Dialect)0,	/* w(uto/s < o( + au)to/s */
"wu)",		"au)",	"o(",	 (Dialect)0,	/* wu)to/s < o( + au)to/s */
"w(u",		"au)",	"oi(",	 (Dialect)0,	/* w(uto/i < o( + au)to/i */
"w)=gaqe",		"a)gaqe/",	"w)=",	 (Dialect)0,	/* w)=gaqe  < w)= + a)gaqe/ */
"w)=",		"a)/",	"w)=",	 (Dialect)0,	/* w)=nac  < w)= + a)/nac */
"w)|",		"oi)",	"w)=",	 (Dialect)0,	/* w)|zu/r'  < w)= + oi)zu/r' */

"w)=",		"o)/",	"w)=",	 (Dialect)0,	/* w)=rniqes < w)= + o)/rniqes */
"w)",		"a)",	"w)=",	 (Dialect)0,	/* w)gaqe/  < w)= + a)gaqe/ */
"w(=",		"a)/",	"oi(",	 (Dialect)0,	/* w)=nac  < w)= + a)/nac */
"w)/",		"a)/",	"w)=",	 (Dialect)0,	/* w)/nassa  < w)= + a)/nassa */

};

 poss_crasis LatSync[] = {
"cognor",		"cognover",	"",	 (Dialect)0,	
"ignor",		"ignover",	"",	 (Dialect)0,	
"cognoss",		"cognoviss",	"",	 (Dialect)0,	
"nosse",		"novisse",	"",	 (Dialect)0,	
"copt",			"coopt",	"",	 (Dialect)0,	/* cooptari --> coptari  */
"der",			"deer",	"",	 (Dialect)0,	/* deest --> dest  */
"des",			"dees",	"",	 (Dialect)0,	/* deest --> dest  */
"abin",			"abis",		"ne",	(Dialect)0,	/* abis +ne --> abin */
"adeon",			"adeo",	"ne",	 (Dialect)0,	/* adeo +ne --> adeon  */
"ain",			"ais",	"ne",	 (Dialect)0,	/* ais +ne --> ain  */
"eccam",		"ecce",		"eam",	(Dialect)0,	/* ecce + pronouns */
"eccum",		"ecce",		"eum",	(Dialect)0,
"eccas",		"ecce",		"eas",	(Dialect)0,
"eccos",		"ecce",		"eos",	(Dialect)0,
"eccillum",		"ecce",		"illum",	(Dialect)0,
"eccillam",		"ecce",		"illam",	(Dialect)0,
"eccistum",		"ecce",		"istum",	(Dialect)0,
"eccistam",		"ecce",		"istam",	(Dialect)0,
 };

int nocrasis = 0;

checkcrasis(gk_word *Gkword)
{
	int i;
	char saveword[MAXWORDSIZE];
	char* string = workword_of(Gkword);
	char* mungedword;
	int rval = 0;
	
	if( nocrasis ) return(0);
	
	if( cur_lang() == LATIN )
	{
		Xstrncpy(saveword, string, MAXWORDSIZE);
		for (i = 0; i < MAXWORDSIZE;  i ++)
		{
			if (string[i] == 0)
				break;
			string[i] = tolower(string[i]);
		}
		for(i=0;i<LENGTH_OF(LatSync);i++) {
			mungedword = LatSync[i].mungedword;
		
			if( *string == * mungedword && !Xstrncmp(mungedword , string , Xstrlen(mungedword) ) ) {
				rval += testcrasis(Gkword,mungedword,LatSync[i].wordstart,LatSync[i].preword, LatSync[i].possdial);
			}
		}
		return(rval);
	}

	for(i=0;i<LENGTH_OF(PossCras);i++) {
		mungedword = PossCras[i].mungedword;
		
		if( *string == * mungedword && !Xstrncmp(mungedword , string , Xstrlen(mungedword) ) ) {
			rval += testcrasis(Gkword,mungedword,PossCras[i].wordstart,PossCras[i].preword, PossCras[i].possdial);
			/*
			if( rval ) return(rval);
			*/
		}
	}
	return(rval);
}

set_nocrasis()
{
	nocrasis = 1;
}

testcrasis(gk_word *Gkword, char *mungedword, char *wordstart, char *preword,Dialect possdial)
{
	char saveword[MAXWORDSIZE];
	char word1[MAXWORDSIZE];
	char word2[MAXWORDSIZE];
	Dialect olddial = 0;
	int rval = 0;
	gk_word  tmpGkword;
	
/*
	tmpGkword = (gk_word *) CreatGkword(1);
*/	
	tmpGkword = * Gkword;

	Xstrncpy(saveword,workword_of(&tmpGkword),(int)sizeof saveword);
	Xstrncpy(workword_of(&tmpGkword),wordstart,(int)sizeof workword_of(&tmpGkword));
	Xstrncat(workword_of(&tmpGkword),saveword+Xstrlen(mungedword),(int)sizeof workword_of(&tmpGkword));
	set_crasis(&tmpGkword,preword);

	olddial = dialect_of(&tmpGkword);
	add_dialect(&tmpGkword,possdial);
	add_dialect(stem_gstr_of(&tmpGkword),possdial);
	rval = checkstring3(&tmpGkword);

	if( rval ) {
		gk_analysis * curanal = analysis_of(&tmpGkword);
		int i=0;
		int nanals;

		nanals = totanal_of(&tmpGkword);

		for(i=0;i<nanals;i++) {
			curanal = analysis_of(&tmpGkword)+i;
			add_dialect(curanal,possdial);
		}
		CpGkAnal(Gkword,&tmpGkword);
	}
	set_dialect(&tmpGkword,olddial);
	set_crasis(&tmpGkword,"");
	set_workword(&tmpGkword,saveword);

	return(rval);
}
	

do_crasis(gk_string *gstring, char *crasis)
{
	int gend, num, wcase;
	int saw_this_crasis = 0;
	int i;
	
	num = number_of(forminfo_of(gstring));
	gend = gender_of(forminfo_of(gstring));
	wcase = case_of(forminfo_of(gstring));

/*
 * grc 9/7/89
 *
 * just comment this out for now
 *
 * we are failing on ou(c (from o( e)c)
 */
 	return(1);
	for(i=0;i<LENGTH_OF(CrasTab);i++) {
		if( !strcmp(crasis, CrasTab[i].crasis ) ) {
			saw_this_crasis++;
			if( num == CrasTab[i].w_number && 
					(((gend & CrasTab[i].w_gender) || gend == CrasTab[i].w_gender) ) && 	
					(((wcase & CrasTab[i].w_case) ) || wcase == CrasTab[i].w_case) ) {

				if( AndDialect(dialect_of(gstring),CrasTab[i].possdial) >= 0 ) {
					Xstrncpy(crasis,CrasTab[i].curstring,MAXWORDSIZE);
					return(1);
				}

			}
		}
	}
	/*
	 * if you saw this crasis (e.g. "o(") but could not find a match, then  you
	 * should have seen a match and have some illegal form (e.g. "a(/ndra << o( a)/ndra")
	 *
	 * if you did not see the crasis in the table at all, then assume your crasis is good
	 * and don't do anything but return 1
	 */
	if( saw_this_crasis ) {
		*crasis = 0;
		return(0);
	}
	return(1);
}
