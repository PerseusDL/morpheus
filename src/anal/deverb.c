#include <gkstring.h>
int quickflag = 0;
int comstemtypes1(char *,char *, char *, char *);
int comstemtypes(char *, char *, char *);
#define VERBMATCH 1
#define DERIVMATCH 2
#define NOMMATCH 3
#define ADJMATCH 4
#define NOMMATCH2 5
#define MAMATCH 6

main()
{
	char line[BUFSIZ];
	char tmp[BUFSIZ];
	char tmpstem[BUFSIZ];
	char curlemma[BUFSIZ];
	char needlemma[BUFSIZ];
	char transkeys[BUFSIZ];
	char *s;
	char *p;
	char keys[BUFSIZ];
	char reskeys[BUFSIZ];
	int rval;

	while(gets(line)) {
		transkeys[0] = keys[0] = reskeys[0] = 0;
		strcpy(tmp,line);
		s = line;

		strcpy(curlemma,line);
		firstkey(curlemma);
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) *s++ = 0;

		strcpy(needlemma,s);
		firstkey(needlemma);
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) *s++ = 0;

		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) *s++ = 0;

		p = s;

		while(*s&&!isspace(*s)) s++;
		if(*s) *s++ = 0;
		while(isspace(*s)) s++;
		strcpy(keys,s);
		stripquant(p);
		stripstemsep(p);
		strcpy(tmpstem,p);
/*printf("curlemma [%s] needlemma [%s] tmpstem [%s] keys [%s]\n", curlemma, needlemma, tmpstem, keys );*/
		rval = testcmpstem(needlemma,tmpstem,reskeys,keys,transkeys);

		s = tmp;
		while(*s&&!isspace(*s)) s++;
		while(isspace(*s)) s++;
		
		zaptabs(line);
		zaptabs(s);
/*printf("stem [%s] keys [%s] s [%s] transkeys [%s]\n", tmpstem, keys , s ,transkeys);*/
		printf("%d\t%s\t%s\t%s\t", rval, line, s, transkeys);

		s = reskeys;
		while(*s) { 
			if(*s == ' ') putchar('\t');
			else putchar(*s);
			s++;
		}
		putchar('\n');
		
	}
}

gk_string Gstr, BlankGstr;
testcmpstem(char *needlemma,char *stem,char * stemkeys,char* matchkeys,char * transkeys)
{
	char rawprvb[BUFSIZ], fullprevb[BUFSIZ], half2[BUFSIZ];
	char *s;
	int rval;

	rval = testcmpstem2(needlemma,stem, stemkeys, matchkeys,transkeys);
	if( rval ) return(rval);
	if( !rval ) {
		s = stem+strlen(stem)-1;
		while(s>stem) {
			Gstr = BlankGstr;
			fullprevb[0] = 0;
			strcpy(half2,s);
			strcpy(rawprvb,stem);
			rawprvb[strlen(rawprvb) - strlen(s)] = 0;
			set_gkstring(&Gstr,half2);
			if( is_preverb(rawprvb,fullprevb,&Gstr) ) {
				char tmp[BUFSIZ];
				tmp[0] = 0;

				SprintGkFlags(&Gstr,tmp,":",1);
				if(testcmpstem2(needlemma,half2, stemkeys, matchkeys,transkeys)) { 
					strcat(transkeys,":pb:");
					strcat(transkeys,fullprevb);
					strcat(stemkeys,tmp);
					return(DERIVMATCH);
				}
			}

			s--;
		}
	}
	return(0);
}

testcmpstem2(char *needlemma,char *stem,char * stemkeys,char* matchkeys,char * transkeys)
{
	int rval;

	rval=testcmpstem3(needlemma,stem, stemkeys, matchkeys,transkeys);
/*
 * grc 9/7/94
 *
 * you get metrical lengthening in poetry: e.g. 
 *	dus-ech/nustos for dus-ec-a/nustos
 * check for this.
 *
 */
	if( ! rval ) {
		char tmpstem[BUFSIZ];
		if( *stem == 'h' ) {
			strcpy(tmpstem,stem);
			tmpstem[0] = 'e';
			rval=testcmpstem3(needlemma,tmpstem, stemkeys, matchkeys,transkeys);
			if(rval) {
				strcat(transkeys,":metrical_long:poetic");
				return(rval);
			}
			tmpstem[0] = 'a';
			rval=testcmpstem3(needlemma,tmpstem, stemkeys, matchkeys,transkeys);
			if(rval) {
				strcat(transkeys,":metrical_long:poetic");
				return(rval);
			}
		} else if(*stem == 'w' ) {
		}
	}
	return(rval);
}

testcmpstem3(char*needlemma,char *stem,char * stemkeys,char* matchkeys,char*transkeys)
{
	char savestem[BUFSIZ], tmp[BUFSIZ];
	int rval = 0;
	
	stemkeys[0] = 0;

        if( *stem == 'r'  && getbreath(stem) == NOBREATH ) {

		if( *(stem+1) == 'r' ) strcpy(stem,stem+1); /* rr --> r */
                Xstrncpy(tmp,"r(",(int)sizeof tmp);
                Xstrncat(tmp,stem+1,(int)sizeof tmp);
                Xstrncpy(stem,tmp,BUFSIZ);
                rval = checkvcomp(needlemma,stem,stemkeys,matchkeys);
		if( rval ) return(rval);
		return(0);
        }

        if( Is_vowel(*stem) && getbreath(stem) == NOBREATH  && cur_lang() != LATIN ) {

                strcpy(savestem,stem);
/*
 * check for rough breathing
 */

                addbreath(stem,ROUGHBR);
		rval = checkvcomp(needlemma,stem, stemkeys,matchkeys);
		if( rval ) return(rval);

		strcpy(stem,savestem);
                addbreath(stem,SMOOTHBR);
		rval = checkvcomp(needlemma,stem, stemkeys,matchkeys);
		if( rval ) return(rval);
		strcpy(stem,savestem);
	}
	rval = checkvcomp(needlemma,stem, stemkeys,matchkeys);
	/*if( rval ) printf("%d:[%s] [%s] [%s]\n", rval, stem, stemkeys, matchkeys);*/
	return(rval);
}

checkvcomp(char * needlemma,char * stem,char * stemkeys,char * matchkeys)
{
	int rval = 0;
	char mbuf[BUFSIZ];


	*stemkeys = 0;
	strcpy(mbuf,matchkeys);

	rval = chcknstem(stem,stemkeys);
	if( rval ) rval = comNomstemtypes(needlemma,stem,stemkeys,matchkeys);
	if( rval ) return(rval);
	strcpy(matchkeys,mbuf);

	*stemkeys = 0;
	rval = chckvstem(stem,stemkeys);
	if( rval ) rval = comstemtypes1(needlemma,stem,stemkeys,matchkeys);
	if( rval ) return(NOMMATCH);
	strcpy(matchkeys,mbuf);

	*stemkeys = 0;
	if( ! rval ) rval = checkforderiv(stem, stemkeys);
/*printf("rval:%d stem [%s] [%s] [%s]\n", rval , stem, stemkeys, matchkeys );*/
	if( rval ) rval = comstemtypes1(needlemma,stem,stemkeys,matchkeys);
	if( rval ) return(NOMMATCH);
	stemkeys[0] = 0;
	strcpy(matchkeys,mbuf);

	return(0);
}

chcknstem(char * stem,char *stemkeys)
{
	int rval;
	* stemkeys = 0;
	rval = chckstem(stem,stemkeys,1);
	return(rval);
}


comNomstemtypes(char * needlemma,char * stem,char * stemkeys,char * matchkeys)
{
	char tmpkeys[BUFSIZ], mbuf[BUFSIZ];
	char tmpstem[BUFSIZ];
	int rval = 0;

	tmpkeys[0] =  tmpstem[0] =  0;
	strcpy(mbuf,matchkeys);
	strcpy(tmpstem,stemkeys);
	rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
	if( rval ) return( NOMMATCH );

/*printf("stem [%s] stemkeys [%s] mbuf [%s]\n", stem,stemkeys,mbuf );*/
	if( !strncmp("os_h_on",matchkeys,strlen("os_h_on"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"os_ou");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH);
	}
	if( !strncmp("os_on",matchkeys,strlen("os_on"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"h_hs os_ou a_hs");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH);

		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"os_h_on");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(ADJMATCH);

		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"hs_ou");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH);

		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"hs_eos");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH);

		if( stem[strlen(stem)-1] == 'm' ) {
			char tmps[BUFSIZ];
			
			strcpy(tmps,stem);
			strcpy(stemkeys,tmpstem);
			tmps[strlen(tmps)-1] = 0;
			strcpy(mbuf,"ma_matos");
			rval = comstemtypes1(needlemma,tmps,stemkeys,mbuf);
			if(rval) return(MAMATCH);
		}

	}
	if( !strncmp("os_h_on",matchkeys,strlen("os_h_on"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"os_on");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(ADJMATCH);

		strcpy(stemkeys,tmpstem);
	}
	if( !strncmp("hs_es",matchkeys,strlen("hs_es"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"hs_eos os_ou h_hs a_hs ws_oos");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH2);

		strcpy(stemkeys,tmpstem);
	}
	if( !strncmp("wn_on",matchkeys,strlen("wn_on"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"wn_onos");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH2);

		strcpy(stemkeys,tmpstem);
	}
	if( !strncmp("is_idos",matchkeys,strlen("is_idos"))) {
		strcpy(stemkeys,tmpstem);
	/*
	 * grc 9/7/94
	 * note: this allows us to go from is_idos_adj --> is_idos
 	 * as in dusmhn is_idos_adj --> mhn is_idos
	 */
		strcpy(mbuf,"is_idos is_ews");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH2);

		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"h_hs");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH2);

		strcpy(stemkeys,tmpstem);
	}
	if( !strncmp("us_eia_u",matchkeys,strlen("us_eia_u"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"us_uos uLs_uos us_ews");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH2);

		strcpy(stemkeys,tmpstem);
	}
		
	if( !strncmp("oos_oon",matchkeys,strlen("oos_oon"))) {
		strcpy(stemkeys,tmpstem);
		strcpy(mbuf,"oos_oou");
		rval = comstemtypes1(needlemma,stem,stemkeys,mbuf);
		if(rval) return(NOMMATCH2);

		strcpy(stemkeys,tmpstem);
	}
		
	return(0);
}

zaptabs(s)
char *s;
{
	while(*s) {
		if(*s=='\t') *s =' ';
		s++;
	}
}

comstemtypes1(char *needlemma,char *stem,char *stemkeys,char *matchkeys)
{
	char tmp[BUFSIZ];
	int rval;

	rval = comstemtypes(stem,stemkeys,matchkeys);
if(*stemkeys)
printf("needlemma [%s] stemkeys [%s] match [%s]\n", needlemma, stemkeys , matchkeys);
	if(rval && *needlemma) {
		char * sp;
		char curbuf[BUFSIZ];
		strcpy(tmp,needlemma);
		strcat(tmp,":");

		curbuf[0] = 0;
		sp = stemkeys;
		while(*sp) {	

			if( !strncmp(tmp,sp,strlen(tmp)) ) {
				char * t = curbuf;
				if(curbuf[0]) strcat(curbuf," ");
				strcat(curbuf,sp);
				while(*t&&!isspace(*t))t++;
				*t = 0;
				sp = curbuf;
			}
			while(*sp&&!isspace(*sp)) sp++;
			while(isspace(*sp)) sp++;
		}
		if( !curbuf[0] ) {
			return(0);
		}
		strcpy(stemkeys,curbuf);
	}
	return(rval);
}

firstkey(char *s)
{
	while(*s&&!isspace(*s)) s++;
	if(isspace(*s)) *s=0;
}
