#include "contract.h"

#include "lcontr.proto.h"

gk_string * CreatGkString();

gk_string * load_euph_tab();

gk_string * 
load_ccontr(int *gotno)
{
/*
	char fullname[MAXPATHNAME];
	
	MorphPathName(CONSEUPH,fullname);
	return(load_euph_tab(fullname,gotno,YES));
*/
	return(load_euph_tab(CONSEUPH,gotno,YES));
}

gk_string * 
load_vcontr(int *gotno)
{
/*
	char fullname[MAXPATHNAME];
	
	MorphPathName(VOWCONTRACTS,fullname);
	return(load_euph_tab(fullname,gotno,YES));
*/
	return(load_euph_tab(VOWCONTRACTS,gotno,YES));
}

