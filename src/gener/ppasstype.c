#include <contract.h>

gk_string * ppass_table = NULL;
static int nppass = 0;

makeppass(origstem,gstr) 
char * origstem;
gk_string * gstr;
{
	char newstem[MAXWORDSIZE];
	char stemname[MAXWORDSIZE];
	Stemtype GetStemNum();
	
	
	if( ! get_ppasstype(origstem,newstem,stemname) ) return;
	strcpy(origstem,newstem);
	set_stemtype(gstr,GetStemNum(stemname));
}

get_ppasstype(stem,newstem,stemname)
char *stem;
char * newstem;
char * stemname;
{
	int  i;
	char * p;
	
	if( Is_vowel(*(lastn(stem,1)))  )
		return(0);
	strcpy(newstem,stem);
	strcpy(stemname,"perfp_vow");
	if( ! ppass_table ) {
		ppass_table = load_euph_tab(PPASSLIST,&nppass);

		if( ! ppass_table)  return(0);
	}
	for(i=0;i<nppass;i++) {
		p = gkstring_of(ppass_table+i);
		if( ends_in(stem,p) ) {
			*(lastn(newstem,strlen(p))) = 0;
			strcpy(stemname,p+MAXSUBSTRING);

			return(1);
		}

	}
	return(0);
}


