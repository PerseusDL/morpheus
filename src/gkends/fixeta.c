#include <gkstring.h>
#define MAXEUPHS 5

#include "fixeta.proto.h"
gk_string * CreatGkString();

/*
 *	ote/rhs	--> ote/ra_s	attic
 *	hs --> a_s for rho, eta, alpha in  attic
 */
gk_string *
fix_eta(gk_string *gstr)
{
	gk_string * euphs;
	char * is_substring();
	char * orgstr;
	char * curs;
	Dialect d;


	euphs =  CreatGkString(MAXEUPHS);
	/*
	 * deal with h --> a_ in Attic after rho, epsilon and iota
	 */
	
	orgstr = gkstring_of(gstr);
/*
PrntGkStr(gstr,stdout);
*/

	if( *orgstr == 'h' && !has_morphflag(morphflags_of(gstr), INDECLFORM) && 
	(((stemtype_of(gstr) & (DECL1|DECL2) ) || degree_of(forminfo_of(gstr)) )
		|| Is_participle(gstr) || Is_deriv(morphflags_of(gstr)))) {
		if( (d=AndDialect(dialect_of(gstr) , (Dialect) RHO_ALPHA_DIAL)) >= 0 ) {

			*euphs = *gstr;
			curs = gkstring_of(euphs);
			strcpy(curs,"a_");
			strcat(curs,orgstr+1);
			add_morphflag(morphflags_of(euphs),R_E_I_ALPHA);
			set_dialect(euphs,ATTIC);
			return(euphs);
		}
	}

	if( dialect_of(gstr) != RHO_ETA_DIAL &&
		( degree_of(forminfo_of(gstr)) || Is_participle(gstr) || (stemtype_of(gstr) & (DECL1|DECL2) ) ) ) {

		if( (is_substring("rh",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;

			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("rh",orgstr);
			*s = 0; s++; s++;
			strcpy(tmp,s);
			strcat(orgstr,"ra_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		} /* check only for forms such as a)ciwte/ra_ / a)ciwte/rh */
		
		 else if( (is_substring("ih",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("ih",orgstr);
			*s = 0; s++; s++;
			strcpy(tmp,s);
			strcat(orgstr,"ia_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		 } else if( (is_substring("i!h",orgstr))) {
		 /*
		  * grc 10/17/93
		  * get ou)demi!a_s to be marked as attic!
		  */
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("i!h",orgstr);
			*s = 0; s++; s++; s++;
			strcpy(tmp,s);
			if(tmp[0] == '=' )
				strcat(orgstr,"i!a");
			else
				strcat(orgstr,"i!a_");
			
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		} else if( (is_substring("i_h",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("i_h",orgstr);
			*s = 0; s++; s++;s++;
			strcpy(tmp,s);
			strcat(orgstr,"i_a_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);

			return(euphs);
			} else if( (is_substring("i/h",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("i/h",orgstr);
			*s = 0; s++; s++; s++;
			strcpy(tmp,s);
			strcat(orgstr,"i/a_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		} else if( (is_substring("i_/h",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("i_/h",orgstr);
			*s = 0; s++; s++;s++; s++;
			strcpy(tmp,s);
			strcat(orgstr,"i_/a_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);

			return(euphs);
		} 	else if( (is_substring("e/-h",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("e/-h",orgstr);
			*s = 0;/* s++; s++; s++; */
			strcpy(tmp,s+strlen("e/-h"));

			strcat(orgstr,"e/-a_");
			strcat(orgstr,tmp);

			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		}	/* else if( (is_substring("eh",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("eh",orgstr);
			*s = 0; s++; s++; 
			strcpy(tmp,s);
			strcat(orgstr,"ea_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		} else if( (is_substring("i_/h",orgstr))) {
			char tmp[MAXWORDSIZE];
			char * s;
	
			*euphs = *gstr;
			orgstr = gkstring_of(euphs);
			s = is_substring("i_/h",orgstr);
			*s = 0; s++; s++; s++; s++;
			strcpy(tmp,s);
			strcat(orgstr,"i_/a_");
			strcat(orgstr,tmp);
			set_dialect(euphs,ATTIC);
			dialect_of(gstr) &= ~(ATTIC);
			return(euphs);
		}*/
	}



	FreeGkString(euphs);
	return(NULL);
}
