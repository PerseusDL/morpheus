#include <gkstring.h>	

#include "new_val.proto.h"

void
new_person(gk_string *gstr, unsigned long val)
{
		set_person(forminfo_of(gstr),val);
}
void
new_number(gk_string *gstr, unsigned long val)
{
		set_number(forminfo_of(gstr),val);
}

void
new_case(gk_string *gstr, unsigned long val)
{
		add_case(forminfo_of(gstr),val);
}


void
new_tense(gk_string *gstr, unsigned long val)
{
		set_tense(forminfo_of(gstr),val);
}


void
new_voice(gk_string *gstr, unsigned long val)
{
		if( val == ACTIVE && (voice_of(forminfo_of(gstr)) & (MEDIO_PASS) ) ) 
			set_voice(forminfo_of(gstr),val);
		else if( ( val & (MEDIO_PASS) ) && (voice_of(forminfo_of(gstr)) ==ACTIVE) )
			set_voice(forminfo_of(gstr),val);
		else add_voice(forminfo_of(gstr),val);
}


void
new_mood(gk_string *gstr, unsigned long val)
{
		set_mood(forminfo_of(gstr),val);
}



void
new_degree(gk_string *gstr, unsigned long val)
{
		set_degree(forminfo_of(gstr),val);
}


void
new_gender(gk_string *gstr, unsigned long val)
{
		add_gender(forminfo_of(gstr),val);
}


void
new_dialect(gk_string *gstr, unsigned long val)
{
		add_dialect(gstr,(Dialect)val);
}


void
new_region(gk_string *gstr, unsigned long val)
{
		add_geogregion(gstr,(GeogRegion)val);
}


void
new_morphflags(gk_string *gstr, unsigned long val)
{

		add_morphflag(morphflags_of(gstr),(int)val);
}
	

void
new_stemtype(gk_string *gstr, unsigned long val)
{
		set_stemtype(gstr,(Stemtype)val);
}


void
new_domain(gk_string *gstr, unsigned long val)
{
		add_domain(gstr,(int)val);
}

	

void
new_derivtype(gk_string *gstr, unsigned long val)
{
		set_derivtype(gstr,(Derivtype)val);
}

