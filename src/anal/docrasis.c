#include <gkstring.h>

#include "docrasis.proto.h"
typedef struct {
 	char crasis[MAXWORDSIZE];
 	char curstring[MAXWORDSIZE];
 	int w_gender;
 	int w_case;
 	int w_number;
 } crasis_table;
 
 crasis_table CrasTab[] = {
 	"o(",	"ai(",	FEMININE, NOMINATIVE, PLURAL,
 	"o(",	"oi(",	MASCULINE, NOMINATIVE, PLURAL,
 	"o(",	"o(",	MASCULINE, NOMINATIVE, SINGULAR,
 	"o(",	"h(",	FEMININE, NOMINATIVE, SINGULAR,
 	
 	"to/",	"to/",	NEUTER,	NOMINATIVE, SINGULAR,
 	"to/",	"to/",	NEUTER,	VOCATIVE, SINGULAR,
 	"to/",	"to/",	NEUTER,	ACCUSATIVE, SINGULAR,
 	"to/",	"ta/",	NEUTER,	NOMINATIVE, PLURAL,
 	"to/",	"ta/",	NEUTER,	VOCATIVE, PLURAL,
 	"to/",	"ta/",	NEUTER,	ACCUSATIVE, PLURAL,
 	
 	"ta/",	"ta/",	NEUTER,	NOMINATIVE, PLURAL,
 	"ta/",	"ta/",	NEUTER,	VOCATIVE, PLURAL,
 	"ta/",	"ta/",	NEUTER,	ACCUSATIVE, PLURAL,
 	
 	"tou=",	"tou=",	NEUTER|MASCULINE,	GENITIVE, SINGULAR,
 	"tou=",	"tw=|",	NEUTER|MASCULINE,	DATIVE, SINGULAR,
	
 };

do_crasis(gk_string *gstring, char *crasis)
{
	int gend, num, wcase;
	int saw_this_crasis = 0;
	int i;
	
	num = number_of(forminfo_of(gstring));
	gend = gender_of(forminfo_of(gstring));
	wcase = case_of(forminfo_of(gstring));

	for(i=0;i<LENGTH_OF(CrasTab);i++) {
		if( !strcmp(crasis, CrasTab[i].crasis ) ) {
			saw_this_crasis++;
			if( num == CrasTab[i].w_number && (gend & CrasTab[i].w_gender)  && (wcase & CrasTab[i].w_case) ) {
				strcpy(crasis,CrasTab[i].curstring);
				return(1);
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
/*
	if( ! strcmp(crasis,"o(")) {
		if( num == PLURAL && gend == FEMININE  && wcase == NOMINATIVE ) {
			strcpy(crasis,"ai(");
			return(1);
		} else if( num == PLURAL && gend == MASCULINE && wcase == NOMINATIVE ) {
			strcpy(crasis,"oi(");
			return(1); 
		} else if( num == SINGULAR && gend == FEMININE  && wcase == NOMINATIVE ) {
			strcpy(crasis,"h(");
			return(1);
		} else if( num == SINGULAR && gend == MASCULINE  && wcase == NOMINATIVE ) {
			return(1);
		}
		return(0);
	}
*/
	return(1);
}