#include <gkstring.h>
#include <gkdict.h>
#include <endtags.h>
#define STEMCACHE 0
FILE * getlemmstart();
endtags * init_preind(), *init_dict();
FILE * MorphFopen();

/*int dictstrcmp(), dictstrncmp(), morphstrcmp(), morphstrncmp();*/

#include "../morphlib/morphstrcmp.proto.h"


endtags * VbTags = NULL;
endtags * NomTags = NULL;
static int num_of_ntags = 0;
static int num_of_vtags = 0;
char * vbindex = VBINDEX;
char * nomindex = NOMINDEX;
#include "retrentry.proto.h"
 int Use_hqdict = 0;

#if STEMCACHE
Stemcache * scache;
int cacheflag = 1;
#define CACHESIZE 48
#endif

#include "dictio.proto.h"


endtags *
init_dict(char *fname, int *ntags)
{
	if( Use_hqdict ) {
		fname = STEMLIST;
		vbindex = STEMLIST;
		nomindex = STEMLIST;
	}
	return(init_preind(fname,ntags));
}


/*
 * check to see if the current string is an irregular verb.
 */
 chckirrverb(char *irregstr, char *lemmas)
{
	char workstem[MAXWORDSIZE];
	int rval;
	long startoff;
	
	workstem[0] = '1';
	Xstrncpy(workstem+1,irregstr,MAXWORDSIZE);
	stripmetachars(workstem);
	stripacc(workstem);
	rval = chckvstem(workstem,lemmas);
	return(rval);

	if( ! VbTags ) {
		VbTags = init_dict(vbindex,&num_of_vtags);
	}
#if STEMCACHE
	if( ! scache ) {
		init_scache();
	}
	if( (rval=is_instemcache(workstem,Xstrlen(workstem),lemmas) ) )
		return(rval);
#endif

	startoff = ChckPreIndex(VbTags,workstem,num_of_vtags,YES,morphstrcmp);

	if( startoff < 0 ) return(0);
	if( ChckFullIndex(workstem,lemmas,vbindex,startoff,morphstrncmp) ) {
#if STEMCACHE
		add_stemcache(scache,workstem,lemmas);
#endif
		return(1);
	}
	return(0);
}


/*
 * check to see if string "indeclstring" is in the indeclinable list. if so, 
 * store any flags associated with it in the ascii string "lemmas".
 * 
 * return 0 if "indeclstring" is not in the indeclinable list.
 */
 chckindecl(char *indeclstr, char *lemmas)
{
	long startoff;
	int rval = 0;
	char tmpindecl[MAXWORDSIZE];
	
	*lemmas = 0;
	if( ! NomTags ) {
		NomTags = init_dict(nomindex,&num_of_ntags);
	}
	tmpindecl[0] = '2';
	Xstrncpy(tmpindecl+1,indeclstr,MAXWORDSIZE);
	stripquant(tmpindecl);
	stripdiaer(tmpindecl);
	stripacc(tmpindecl);

#if STEMCACHE
	if( ! scache ) {
		init_scache();
	}
	if( (rval=is_instemcache(tmpindecl,Xstrlen(tmpindecl),lemmas) ) )
		return(rval);
#endif

/*
	printf("will look for [%s] in indecl\n", tmpindecl );
*/
	startoff = ChckPreIndex(NomTags,tmpindecl,num_of_ntags,NO,morphstrcmp);
/*
printf("startoff [%ld]\n", startoff );
*/
	if( startoff < 0 ) return(0);
	if( ChckFullIndex(tmpindecl,lemmas,nomindex,startoff,morphstrncmp) ) {
#if STEMCACHE
		add_stemcache(scache,tmpindecl,lemmas);
#endif
		return(1);
	}

	return(rval);
}

/*
 * check to see if string "derivstr" is in the deriv list. if so, 
 * store any flags associated with it in the ascii string "derivkeys".
 * 
 * return 0 if "indeclstring" is not in the indeclinable list.
 */
 chckderiv(char *derivstr, char *derivkeys)
{
	long startoff;
	int rval = 0;
	char tmpderivstr[MAXWORDSIZE];
	
/*
	*derivkeys = 0;
*/
	tmpderivstr[0] = '3';
	Xstrncpy(tmpderivstr+1,derivstr,MAXWORDSIZE);
	stripquant(tmpderivstr);
	stripdiaer(tmpderivstr);
	rval = chckvstem(tmpderivstr,derivkeys);
	return(rval);
	
	if( ! VbTags ) {
		VbTags = init_dict(vbindex,&num_of_vtags);
	}


/*
	printf("will look for [%s] in indecl\n", derivstr );
*/
	startoff = ChckPreIndex(VbTags,tmpderivstr,num_of_vtags,YES,morphstrcmp);
/*
printf("startoff [%ld]\n", startoff );
*/
	if( startoff < 0 ) return(0);
	if( ChckFullIndex(tmpderivstr,derivkeys,vbindex,startoff,morphstrncmp) ) {
#if STEMCACHE
		add_stemcache(scache,tmpderivstr,derivkeys);
#endif
		return(1);
	}
	return(0);
}


 chckstem(char *stemstr, char *stemkeys, int is_nom)
{
	long startoff;
	int rval = 0;
	int rval2 = 0;
	int taglen;
	int curntags = 0;
	char tmpkeys[LONGSTRING];
	char * indfile;
	endtags * CurTags = NULL;
	
	stripquant(stemstr);
	stripdiaer(stemstr);
	*stemkeys = tmpkeys[0] = 0;
	if( is_nom )  {
/*
		rval = chcknstem(stemstr,stemkeys);
		rval2 = checkforderiv(stemstr,tmpkeys);
		if( rval2 ) {
			if( rval ) Xstrncat(stemkeys," ",LONGSTRING);
			Xstrncat(stemkeys,tmpkeys,LONGSTRING);
		}
	
		return(rval+rval2);
*/
		indfile = nomindex;
	} else {
		rval = chckvstem(stemstr,stemkeys);
		rval2 = checkforderiv(stemstr,tmpkeys);
		if( rval2 ) {
			if( rval ) Xstrncat(stemkeys," ",LONGSTRING);
			Xstrncat(stemkeys,tmpkeys,LONGSTRING);
		}
	
		return(rval+rval2);

		indfile = vbindex;
	}
	if( ! *stemstr ) return(0);
	
	
	if( ! VbTags ) {
		VbTags = init_dict(vbindex,&num_of_vtags);
	}
	if( ! NomTags ) {
		NomTags = init_dict(nomindex,&num_of_ntags);
	}
	if( is_nom ) {
		CurTags = NomTags;
		curntags = num_of_ntags;
	} else {
		CurTags = VbTags;
		curntags = num_of_vtags;
	}
	
#if STEMCACHE
	if( ! scache ) {
		init_scache();
	}
#endif

	taglen = Xstrlen(stemstr);

#if STEMCACHE
	if( (rval=is_instemcache(stemstr,taglen,stemkeys) ) )
		return(rval);
#endif
	startoff = ChckPreIndex(CurTags,stemstr,curntags,is_nom? NO : YES,morphstrcmp);

	if( startoff >= 0 ) 
		rval = ChckFullIndex(stemstr,stemkeys,indfile,startoff,morphstrncmp);

#if STEMCACHE
	if(rval)
		add_stemcache(scache,stemstr,stemkeys);
#endif
/*
	if( ! rval ) {
		rval = checkforderiv(stemstr,stemkeys);
	}
*/
/*
	if( ! is_nom ) 
		rval2 = checkforderiv(stemstr,tmpkeys);
	if( rval2 ) {
		if( rval ) Xstrncat(stemkeys," ",LONGSTRING);
		Xstrncat(stemkeys,tmpkeys,LONGSTRING);
	}

	return(rval+rval2);
*/
	return(rval);
}

#if STEMCACHE
init_scache(void)
{
	char ** pp, *s;
	int i;

	if( !(scache=(Stemcache *)calloc((size_t)1,(size_t)sizeof * scache))) {
		char errmess[LONGSTRING];
		
		sprintf(errmess,"could not init scache\n");
		ErrorMess(errmess);
		cacheflag = 0;
		return(0);
	}
	scache->citem = (char **) calloc((size_t)CACHESIZE, (size_t)sizeof * scache->citem );
	if( ! scache->citem ) {
		char errmess[LONGSTRING];
		
		sprintf(errmess,"could not init scache->item\n");
		ErrorMess(errmess);
		cacheflag = 0;
		return(0);
	}	
		
	pp = scache->citem;
	scache->curindex = 0;
	for(i=0;i<CACHESIZE;i++) {
		*(pp+i) = (char *) calloc((size_t)MAXWORDSIZE+1,(size_t)sizeof *(*pp) );
		if( ! *(pp+i) ) {
			fprintf(stderr,"ran out of memory in cache!\n");
			return(0);
		}
	}
}

is_instemcache(char *tag, size_t taglen, char *stemkeys)
{
	char ** pp, *s;
	int i;
	char worktag[MAXWORDSIZE];
	
	Xstrncpy(worktag,tag,MAXWORDSIZE);
	Xstrncat(worktag," ",MAXWORDSIZE);
	taglen++;
	
	pp = scache->citem;
	for(i=0;i<CACHESIZE;i++) {
		s = *(pp+i);

		if( ! *s )
				break;
		if( !morphstrncmp(worktag,s,taglen) ) {
			Xstrncpy(stemkeys,s+taglen,MAXWORDSIZE);

			return( 1 );
		}
	}
	return(0);
}
		
add_stemcache(Stemcache *cache, char *stem, char *keys)
{
	char *tmp = NULL;
	char * s = NULL;
	char ** pp;
	int slen;
	
	tmp = malloc((size_t)LONGSTRING);
	if( cache->curindex >= CACHESIZE ) {
		cache->curindex = 0;
	}
	Xstrncpy(tmp,stem,LONGSTRING);
	Xstrncat(tmp," ",LONGSTRING);
	Xstrncat(tmp,keys,LONGSTRING);

	slen = Xstrlen(tmp);
	pp = cache->citem+cache->curindex;
	if( slen > MAXWORDSIZE ) {
		xFree(*(pp),"pp");
		*(pp) = NULL;
		*(pp) = (char *)calloc((size_t)slen+1,(size_t)sizeof * s);
		if( ! * pp ) {
			fprintf(stderr,"out of memory in cache routine\n");
		}
	}

	s = *(pp);
	Xstrncpy(s,tmp,LONGSTRING);
	xFree(tmp,"scache tmp");
	tmp = NULL;
	cache->curindex++;
}
#endif

endtags * LemmTags = NULL;
static int num_of_ltags = 0;

 prntlemmentry(char *lemma, char *preverb, FILE *f)
{
	long startoff = 0;
	char *lemmfile= NULL;
	char *line = NULL;
	FILE * fword = NULL;

	if( (fword=getlemmstart(lemma,lemmfile,&startoff)) == NULL ) {
		sprintf(line,"No Lemma found under [%s]\n", lemma );
		ErrorMess(line);
		return(-1);
	}
	lemmfile = (char *)malloc((size_t)LONGSTRING);
	line = (char *)malloc((size_t)LONGSTRING);
	*line = * lemmfile = 0;
	while(fgets(line,LONGSTRING, fword) ) {
		if( is_blank(line) ) {
			fprintf(f,"\n\n");
			break;
		}
		trimwhite(line);
		if( *preverb && !Xstrncmp(line,LEMMTAG,Xstrlen(LEMMTAG)) ) {
			rstprevb(line+Xstrlen(LEMMTAG),preverb,0);
			fprintf(f,"%s\n", line );
			continue;
		}
		if( preverb && *preverb )
			fprintf(f,"%s\tpb:%s\n", line , preverb);
		else
			fprintf(f,"%s\n", line );
	}
	xFclose(fword);
	fword = NULL;
	xFree(line,"line prntlem");
	xFree(lemmfile,"lemmfile prntlem");
	line = lemmfile = NULL;
	return(1);
}

/*
 * given a lemma, find out where in the dictionary it shows up
 *
 * note that this routine should be changed so that it returns the actual
 * entry for that particular lemma. returning an offset presupposes that
 * the dictionary represents a single, big file, and this will not be the 
 * case (I don't think) when we have a 10 mbyte dictionary.
 *
 * this file returns a FILE pointer that is open to the place in
 * a dictionary file in which the lemma entry begins.
 *
 * the offset at which the lemma entry begins in that file is
 * stored (redundantly) in *lemmoff
 */
 
FILE * 
 getlemmstart(char *lemma, char *lemmfile, long *lemmoff)
{
	char curtarget[LONGSTRING];
	char line[LONGSTRING];
	char tmp[LONGSTRING];
	long curoff;
	long ftell();
	FILE * f = NULL;
	long startoff;
	int comp = 0;
	char shorttag[MAXWORDSIZE];
	
 
 	if( ! LemmTags ) {
		LemmTags = init_preind(WORDLIST,&num_of_ltags);
	}

	Xstrncpy(shorttag,lemma,MAXWORDSIZE);
	stripquant(shorttag);
	shorttag[6] = 0;

	startoff = ChckPreIndex(LemmTags,shorttag,num_of_ltags,NO,morphstrcmp);

	if( (f=MorphFopen(WORDLIST,"r")) == NULL ) {
		fprintf(stderr,"getlemmstart: could not find %s\n", line );
		return(NULL);
	}
	fseek(f,startoff,0);

	Xstrncpy(shorttag,lemma,MAXWORDSIZE);
	stripquant(shorttag);

	sprintf(curtarget,":le:%s", shorttag );

	while(1) {
		char curlemm[MAXWORDSIZE];

		curoff = ftell(f);
		if( ! fgets(line,(int)sizeof  line , f)) {
			*lemmoff = -1;
			break;
		}
		if( Xstrncmp(line,LEMMTAG,4) )
			continue;
		trimwhite(line);
		nextkey(line,curlemm);

		comp = morphstrcmp(curtarget,curlemm);
/*
printf("comp [%d] curtarget [%s] curlemm [%s]\n", comp , curtarget , curlemm);
*/
		if(! comp ) {
/*
char errbuf[LONGSTRING];
sprintf(errbuf,"curoff %ld targ [%s] lem [%s]\n", curoff , curtarget, curlemm );
ErrorMess(errbuf);
*/
			*lemmoff = curoff;
			break;
		}
		if( comp < 0 ) {
			*lemmoff = -1;
			break;
		}
	}
	if( *lemmoff < 0 ) {
/*
		char errbuf[LONGSTRING];
		sprintf(errbuf,"error: no such lemma as [%s]\n", shorttag );
		ErrorMess(errbuf);
*/
		*lemmfile = 0;
		xFclose(f);
		f = NULL;
		return(NULL);
	}
	
	Xstrncpy(lemmfile,WORDLIST,MAXWORDSIZE); 
	fseek(f,*lemmoff,0);
	return(f);

}

lemma_exists(char *lemma)
{
	FILE * flemm = NULL;
	char lemmfile[LONGSTRING];
	long lemmoff = 0;
	
	if( (flemm = getlemmstart(lemma,lemmfile,&lemmoff)) == NULL )
		return(0);
	xFclose(flemm);
	flemm = NULL;
	return(1);
}
