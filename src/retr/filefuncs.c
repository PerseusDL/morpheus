/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "config.h"
#if CDFS
#include "/usr/CDFS/inc_list.h"
static CDMOUNTED = 0;
#endif

#include "sysinc.h"
#include "defcons.h"

int noerrmess;
static LocFclose(char *, char *);

/*
 * Files associated with individual authors
 */
    static FILE * fprec         =       NULL;
    static FILE * fp2   =       NULL;
    static FILE * ftlg  =       NULL;
    static FILE * find  =       NULL;
    static FILE * fpoint        =       NULL;
    static FILE * fworkfile     =       NULL;
    static FILE * fcomwords =   NULL;
    static FILE * flistind  =   NULL;
    static FILE ** curfp;

#if CDFS
    static CDFILE * cdfprec         =       NULL;
    static CDFILE * cdfp2   =       NULL;
    static CDFILE * cdftlg  =       NULL;
    static CDFILE * cdfind  =       NULL;
    static CDFILE * cdfpoint        =       NULL;
    static CDFILE * cdfworkfile     =       NULL;
    static CDFILE * cdfcomwords =   NULL;
    static CDFILE * cdflistind  =   NULL;
    static CDFILE ** cdcurfp;
#endif


/*
 * Files found only in the big index
 */
    static FILE * ftlgp2        =       NULL;
    static FILE * fauthors      =       NULL;
    static FILE * fdbaslist     =       NULL;

#if CDFS
    static CDFILE * cdftlgp2        =       NULL;
    static CDFILE * cdfauthors      =       NULL;
    static CDFILE * cdfdbaslist     =       NULL;
#endif

    char * TlgAuthDirectory();
    char * LocFgets();

#if CDFS
    long cd_read_seek();
    long cdftell();
    CDFILE * cdfopen();
    char * cdfgets();
#endif
    /*size_t fseek();*/
    char * fgets();
    FILE * fopen();
    long ftell();

/*
 * functions to open and close various index files
 */


 OpComwordsFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfcomwords;
#endif
		curfp = &fcomwords;
        return((OpTlgIndFile(authname,".comwords")) ? 1 : 0 );
}

 OpPrecFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfprec;
#endif
		curfp = &fprec;
        return((OpTlgIndFile(authname,".prec")) ? 1 : 0 );
}

 OpTxtFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdftlg;
#endif
		 curfp = &ftlg;
        return( OpTlgIndFile(authname,".tlg") );
}

 OpWorkfFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfworkfile;
#endif
		curfp = &fworkfile;
        return((OpTlgIndFile(authname,".workfile")) ? 1 : 0 );
}

 OpPointFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfpoint;
#endif
		curfp = &fpoint;
        return((OpTlgIndFile(authname,".point")) ? 1 : 0 );
}

 OpP2File(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfp2;
#endif
		curfp = &fp2;
        return((OpTlgIndFile(authname,".p2")) ? 1 : 0 );
}

 OpIndFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfind;
#endif
		curfp = &find;

        return((OpTlgIndFile(authname,".ind")) ? 1 : 0 );
}


 OpTlgp2File(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdftlgp2;
#endif
		curfp = &ftlgp2;
        return((OpTlgIndFile(authname,".tlgp2")) ? 1 : 0 );
}

OpAuthorsFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfauthors;
#endif
		curfp = &fauthors;
        return((OpTlgIndFile(authname,".authors")) ? 1 : 0 );
}

 OpListindFile(authname)
  char * authname;
{
        char tmp[128];

        sprintf(tmp,"%cwordlist.index", PATHSEPCHAR );
        if( flistind ) {
                fprintf(stderr,"flistind not null!\n");
                return(-1);
        }
#if CDFS
		cdcurfp = &cdflistind;
#endif
		curfp = &flistind;
        return((SuffFopen(authname,tmp,"r")) ? 1 : 0 );
}

 OpDbaslist(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfdbaslist;
#endif
		curfp = &fdbaslist;
        return((OpTlgIndFile(authname,".list")) ? 1 : 0 );
}

 ClComwordsFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfcomwords;
#endif
		curfp = &fcomwords;
        LocFclose(authname,".comwords");
        fcomwords = NULL;
#if CDFS
	cdfcomwords = NULL;
#endif
}
 ClPrecFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfprec;
#endif
		curfp = &fprec;
        LocFclose(authname,".prec");
        fprec = NULL;
#if CDFS
	cdfprec = NULL;
#endif
}

 ClTxtFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdftlg;
#endif
		curfp = &ftlg;
        LocFclose(authname,".tlg");
#if CDFS
	cdftlg = NULL;
#endif
        ftlg = NULL;
}
        
        
 ClWorkfFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfworkfile;
#endif
		curfp = &fworkfile;
        LocFclose(authname,".workfile");
#if CDFS
	cdfworkfile = NULL;
#endif
        fworkfile = NULL;
}
 ClPointFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfpoint;
#endif
		curfp = &fpoint;
        LocFclose(authname,".point");
#if CDFS
	cdfpoint = NULL;
#endif
        fpoint = NULL;
}

 ClP2File(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfp2;
#endif
		curfp = &fp2;
        LocFclose(authname,".p2");
#if CDFS
	cdfp2 = NULL;
#endif
        fp2 = NULL;
}
 ClIndFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfind;
#endif
		curfp = &find;
        LocFclose(authname,".ind");
#if CDFS
	cdfind = NULL;
#endif
        find = NULL;
}


 ClTlgp2File(authname)
  char * authname;
{
#if CDFS
	cdcurfp = &cdftlgp2;
#endif
	curfp = &ftlgp2;

        LocFclose(authname,".tlgp2");
#if CDFS
	cdftlgp2 = NULL;
#endif
        ftlgp2 = NULL;
}

 ClAuthorsFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdfauthors;
#endif
		curfp = &fauthors;
        LocFclose(authname,".authors");
#if CDFS
	cdfauthors = NULL;
#endif
        fauthors = NULL;
}

 ClListindFile(authname)
  char * authname;
{
#if CDFS
		cdcurfp = &cdflistind;
#endif
		curfp = &flistind;
        LocFclose(TlgAuthDirectory(authname),"/wordlist.index");
#if CDFS
	cdflistind = NULL;
#endif
        flistind = NULL;
}

 ClDbaslist(authname)
  char * authname;
{
#if CDFS
	cdcurfp = &cdfdbaslist;
#endif
	curfp = &fdbaslist;
        LocFclose(TlgAuthDirectory(authname),"/dbaslist");
#if CDFS
	cdfdbaslist = NULL;
#endif
        fdbaslist = NULL;
}

 OpTlgIndFile(authname,suffix)
  char * authname;
  char * suffix;
{
/*
 * make sure that no file pointer to this file, either on CD or on HD,
 * is open
 */

        if( *curfp != NULL ) {
                fprintf(stdout,"Hey! file ptr for %s%s not null!\n",authname,suffix);
                return(NULL);
        }

#if CDFS
	if( *cdcurfp != NULL )  {
		fprintf(stdout,"Hey! cdfile ptr for %s%s not null!\n",authname,suffix);
		return(NULL);
	}
#endif

        if( ! AuthFopen(authname,suffix,"r") ) {
			return(0);
        }
	return(1);
}


/*
 * check to see if this author had an index online
 */

 NoTlgIndex(authname)
  char * authname;
{

        noerrmess++;
        
        if( OpP2File(authname) == NULL )  {
                noerrmess = 0;
                return( 1 );
        }
        ClP2File(authname);
        if( OpPrecFile(authname) == NULL ) {
                noerrmess = 0;
                return( 1 );
        }
        ClPrecFile(authname);
        noerrmess = 0;
        return( 0 );
}


/*
 * Operations that deal with the list of common words (auth.comwords)
 */



char *
 GetComword(authname,s,len)
  char * authname;
  char * s;
  int len;
{
#if CDFS
	cdcurfp = &cdfcomwords;
#endif
	curfp = &fcomwords;
	return(LocFgets(s,len,authname));
}


/*
 * functions that deal with the wordlist.index file
 */

long
 ListindFseek(authname,Offset)
  char * authname;
  long Offset;
{
#if CDFS
	if(cdflistind)
		return(cd_read_seek(cdflistind,Offset));
	else
#endif
		return(fseek(flistind,Offset,0));
}

char *
 ListindFgets(s,len,authname)
  char * s;
  int len;
  char * authname;
{
#if CDFS
	cdcurfp = &cdflistind;
#endif
	curfp = &flistind;
	return(LocFgets(s,len,authname));
}


/*
 * functions that deal with the author.prec file
 */



long
 P2toFreq(p2,authname)
  long p2;
  char * authname;
{
        long ptr; 


        OpPrecFile(authname);
#if CDFS
	if( cdfprec ) {
		cdcurfp = &cdfprec;
		cd_read_seek(*cdcurfp, (4L * (p2) ) );
        } else {
#endif
		curfp = &fprec;
		fseek( *curfp , (4L * (p2) ) , 0 );
#if CDFS
	}
#endif
/*
        vax_fread( &ptr , sizeof ptr , 1 , authname );
*/
        Vax_words( &ptr , sizeof ptr , 1 , authname );
        ClPrecFile(authname);
        return(ptr);
}

 GetPrecArr(PrecArr,PA,Freq,authname)
  long * PrecArr;
  long PA;
  long Freq;
  char * authname;
{
        long LocFreq, i;
        long * PrecPtr = PrecArr;

        OpPrecFile(authname);
#if CDFS
	if( cdfprec ) {
		cdcurfp = &cdfprec;
		cd_read_seek( *cdcurfp , (4L * (PA) ) );
	} else {
#endif
		curfp = &fprec;
		fseek( *curfp , (4L * (PA) ) , 0 );
#if CDFS
	}
#endif
        Vax_words( &LocFreq , sizeof LocFreq , 1 , authname );
        if( Freq != LocFreq ) {
                fprintf(stderr,"Error in Prec file: read in freq ");
                fprintf(stderr,"%ld; expected %ld\n", LocFreq , Freq );
                ClPrecFile(authname);
                return(0);
        }
        for(i=0;i<Freq;i++) {
                Vax_words( PrecArr , sizeof *PrecArr , 1 , authname );
                PrecArr++;
        }

        ClPrecFile(authname);
        return(1);
}


 TxtOpen(authname)
  char * authname;
{
#if CDFS
	if( cdftlg ) 
		return( 1);
	else
#endif
		return( ftlg != NULL );
}

 TlgOnline(authname)
  char * authname;
{
        noerrmess++; 

	if( TxtOpen(authname ) ) return(1);
        if( ! OpTxtFile(authname) ) {
                noerrmess = 0;
                return(0);
        }
        ClTxtFile(authname);
        noerrmess = 0;
        return(1);
}

 ThesaurOnline(thesname)
  char * thesname;
{
        noerrmess++;
        if( ! OpIndFile(thesname) ) {
                noerrmess = 0;
                return(0);
        }
        ClIndFile(thesname);
        noerrmess = 0;
        return(1);
}

/*
 * funcs that deal with the auth.tlg file
 */
char *
 TxtFgets(s,len,authname)
  char * s;
  int len;
  char * authname;
{
#if CDFS
	cdcurfp = &cdftlg;
#endif
	curfp = &ftlg;
        return(LocFgets(s,len,authname));
}


/*
 * warning: this does not reliably return the offset: this is
 * not (I don't think) the rval of cd_read_seek()
 */
long
 TxtFseek(authname,Offset)
  char * authname;
  long Offset;
{
#if CDFS
	if( cdftlg ) 
		return( cd_read_seek(cdftlg,Offset) );
	else
#endif
		return( fseek(ftlg,Offset,0) );
}

long 
 TxtFtell(authname)
  char * authname;
{
#if CDFS
	if( cdftlg )
		return(cdftell(cdftlg));
	else
#endif
		return(ftell(ftlg));
}

int 
 TxtFread(authname,bufp,len)
  char * authname;
  char * bufp;
  int len;
{
	int n;
#if CDFS
	if( cdftlg )
		n = cdfread(   bufp , sizeof * bufp , len , cdftlg );
	else
#endif
		n = fread(   bufp , sizeof * bufp , len , ftlg );
	return(n);
}

long
 TxtLen(authname)
  char * authname;
{
        long n;
        long savepos;


#if CDFS
	if( cdftlg )
		return(cdftlg->bytes_total);
#endif
        if( ftlg ) {
                savepos = ftell(ftlg);
                n = fseek(ftlg,0L,2);
                fseek(ftlg,savepos,2);
                return(ftell(ftlg));
        }
        OpTxtFile(authname);
#if CDFS
	n = cdftlg->bytes_total;
#else
        fseek(ftlg,0L,2);
        n = ftell(ftlg);
#endif
        ClTxtFile(authname);

        return(n);
}


/* 
 * author.workfile functions
 */



long
 WorkfOffset(authname)
  char * authname;
{
#if CDFS
	if( cdfworkfile )
		return(cdftell(cdfworkfile));
	else
#endif
		return(ftell(fworkfile));
}

char * 
 WorkfFgets(s,len)
  char * s;
  int len;
{
#if CDFS
	cdcurfp = &cdfworkfile;
#endif
	curfp = &fworkfile;
        return(LocFgets(s,len,fworkfile));
}


/*
 * given an offset, look in the author.point file and put the appropriate
 * data in ref
 */

#include "tlg.h"


 SetRefForOffset(ref,authname,Offset)
  reference * ref;
  char * authname;
  long Offset;
{

        OpPointFile(authname);

#if CDFS
	if( cdfpoint ) {
	    cdcurfp = &cdfpoint;
            if( cd_read_seek( *cdcurfp , (Offset/1000L) * RECLEN ) < 0 ) {
                fprintf(stdout,"SetRefForOffset: error seeking in fpoint");
 	    }
        } else {
#endif
	    curfp = &fpoint;
            if( fseek( fpoint , (Offset/1000L) * RECLEN , 0 ) < 0 ) {
	    fprintf(stdout,"SetRefForOffset: error seeking in fpoint");
            }
#if CDFS
	}
#endif
        NextSect(authname, ref );
        ClPointFile(authname);
}

/*
 * use the author.point file to get as close to the ref described
 * in wantref as possible. store the result in gotref.
 *
 * start looking at startOffset
 */
 SetRefForRef(wantref,gotref,startOffset,authname)
  reference * wantref;
  reference * gotref;
  long startOffset;
  char * authname;
{
        reference * PrevRef;

        if( (PrevRef = (reference *)calloc(1 , sizeof * PrevRef )) == NULL ) {
                fprintf(stdout,"SetRefForRef:could not initalize PrevRef");
                return(-1);
        }

        OpPointFile(authname);

#if CDFS
	if( cdfpoint ) {
	    cdcurfp = &cdfpoint;
            if( cd_read_seek( *cdcurfp , (startOffset/1000L) * RECLEN ) < 0 ) {
                fprintf(stdout,"SetRefForRef: error seeking in cdfpoint");
	    }
	} else {
#endif
	    curfp = &fpoint;
            if( fseek( fpoint , (startOffset/1000L) * RECLEN , 0 ) < 0 ) {
                fprintf(stdout,"SetRefForRef: error seeking in fpoint");
	    }
#if CDFS
        }
#endif
        /*
         * first make sure you seek through the .point file
         * till you get the right work.
         *   ie., you might start with a record that points to offset
         *   30,000, whereas you want a reference in work XXX, that
         *   begins at offset 30,001.
         * the work number for the initial offset will be one less than
         * the work that you want, and this will confuse RefEqual().
         */
        for(;;) {
                NextSect(authname, gotref );
                if(gotref->Offset >= startOffset )
                        break;
        }
        gotref->refwknum = wantref->refwknum;

/*
 * if the first read out of the .point file puts you further than you want
 * to go, then set got->Offset to the beginning of the work and
 * initialize the mark maintained in marker.c
 */
        if( RefEqual(gotref,wantref) > 0 ) {
                gotref->Offset = startOffset;
                /*clear_mark();*/
        } else if( 1 ) {
                    for(;;) {
                        /* if you have come to the end of file */
                        if( NextSect(authname,gotref) == NULL ) {
                                goto finish;
                        }

                        /*
                         * if gotref is greater than the target ref,
                         * you are one too far. so save the contents
                         * of PrevRef in gotref.
                         */
                        if( RefEqual(gotref,wantref) >= 0 ||
				gotref->Offset > wantref->wrkend  ) {
                                *gotref = * PrevRef;
                                break;
                        }

                        *PrevRef = *gotref;
                    }

        }


   finish:
        ClPointFile(authname);
        free(PrevRef);
        return(1);
}


 NextSect(authname , ref )
  char * authname;
  reference * ref;
{
        static gkfield G_field;

#if CDFS
	if( cdfpoint ) {
	    if( ! cdfpoint ) {
                fprintf(stdout,"Hey! cdfpoint not opened!\n");
                return(0);
	    }
	} else
#endif
        if( fpoint == NULL ) {
                fprintf(stdout,"Hey! fpoint not opened!\n");
                return(0);
        }
#if CDFS
	cdcurfp = &cdfpoint;
#endif
	curfp = &fpoint;

        if( ! Vax_words( &ref->Offset , sizeof ref->Offset , 1 , authname ) ) {       

                fprintf(stderr,"Vax_words failed!\n");
                return( 0 );
        }

        if( ! Vax_words( &G_field.num , sizeof G_field.num , 1 , authname ) )
                return( 0 );
        G_field.ch = LocFgetc( authname );
        G_field.oddlabel[0] = 0;
        ref->w_field = G_field;
        G_field.num = G_field.ch = G_field.oddlabel[0] = 0;


        if( ! Vax_words( &G_field.num , sizeof G_field.num , 1 , authname ) )
                return( 0 );
        G_field.ch = LocFgetc( authname );
        G_field.oddlabel[0] = 0;
        ref->x_field = G_field;
        G_field.num = G_field.ch = G_field.oddlabel[0] = 0;
        if( ! Vax_words( &G_field.num , sizeof G_field.num , 1 , authname ) )
                return( 0 );
        G_field.ch = LocFgetc( authname );
        G_field.oddlabel[0] = 0;
        ref->y_field = G_field;
        G_field.num = G_field.ch = G_field.oddlabel[0] = 0;

        G_field = ref->z_field;
        if( ! Vax_words( &G_field.num , sizeof G_field.num , 1 , authname ) )
                return( 0 );

        /*
         * this line num refers to the next line in text, but G_field
         * register will be incremented before reading the next line.
         * this compensates.
         */

        G_field.num--;
        G_field.ch = LocFgetc( authname );
        G_field.oddlabel[0] = 0;
        ref->z_field = G_field;

        return( 1 );
}

/*
 * takes an authname and suffix, figures out the author directory and creates
 * a pathname of form: AuthDirectory/authname.suffix
 */

 TlgFopen( authname, suff , mode )
  char *authname;
  char *suff;
  char *mode;
{
        char full[BUFSIZ];

        sprintf(full,"%s%c%s%s", TlgAuthDirectory(authname) , PATHSEPCHAR, authname , suff );
	*curfp = fopen( full , mode );
	return( *curfp != NULL );
}


 AuthFopen(  authname , suff , mode )
  char *authname;
  char *suff;
  char *mode;
{
        char * TlgAuthDirectory();
/*
        char full[BUFSIZ];

        sprintf(full,"%s%c%s%s", TlgAuthDirectory(authname) , PATHSEPCHAR, authname , suff );
	*curfp = fopen( full , mode );
*/
	TlgFopen(authname,suff,mode);

/*
#ifdef SYS5
*/
#define SYS5FILENAME 14
#define SHORTNAME 6
	if( ! *curfp ) {
/*
 * GRC 12/6/86
 *
 * OK here we go with a big kludge to get around (yet again) one of
 * System V's many inferiorities to Berkeley Unix.
 *
 * System V truncates filenames at SYS5FILENAME chars, so a file like
 * "hesiod.workfile" will get truncated to "hesiod.workfil".
 * This portion of the code looks to see if by truncating the suffix,
 * it might be able to find the file that it could not find before. Ugh.
 *
 * IBM and AT&T deserve System V...
 */
                char mess[MAXMESS];

		if( strlen( authname ) + strlen( suff ) > SYS5FILENAME ) {
		  char shortsuff[SYS5FILENAME];
		  char shortauth[SYS5FILENAME];

		  strncpy( shortsuff ,suff , SYS5FILENAME - strlen(authname));
		  shortsuff[SYS5FILENAME - strlen(authname)] = 0;
		  if(  TlgFopen(authname,shortsuff,mode) )
			return(1);
/*
 * GRC 3/21/87
 *
 * ho, ho, ho--you probably thought that things 
 * couldn't get any worse. ha!
 *
 * we now try looking for a shortened version of the author name. 
 * this is because
 * some author names on the CD are so long that AIX 
 * leaves no room for extensions,
 * (e.g. "st_athanasius" which gets truncated 
 * to "st_athanasius." no matter what you stick
 *   after the ".")
 * so, we try created a truncated version of the 
 * name with only SYS5FILENAME/2 chars in it
 */

		  strncpy(shortauth,authname,SYS5FILENAME);
		  shortauth[SHORTNAME] = 0;
		  if( TlgFopen(shortauth,suff,mode) ) {
                    return(1);
		  }
		}
	}
/*
#endif
*/
	

	if( ! *curfp ) {
#if CDFS
	char cdfname[BUFSIZ];

		if( ! CDMOUNTED ) {
			CDMOUNTED++;
			mount_CDFS(0);
		}
	/*
	 * GRC
 	 * oops! all authors on the TLG CDROM are in directories
	 * formed by their names, i.e. homer is in /homer, hesiod is
 	 * in /hesiod; the full pathname for hesiod.tlg is /hesiod/hesiod.tlg
	 * etc.
	 * 	there is *one* exception to this: the big index. this
	 * is in directory /dbase, but has basename bigind. thus the
	 * list of all unique strings in the big index is "/dbase/bigind.ind"
	 * rather than "/bigind/bigind.ind". this is not how i would do
	 * things if i had it to do over again, but when a CD is 
	 * mastered....
	 *	so the program looks to see is the authname is "bigind"
	 * before deciding how to look for the data on the CD.
	 */

		if( ! strcmp( authname , BIGINDNAME ) )
			sprintf(cdfname,"%cdbase%c%s%s", PATHSEPCHAR , PATHSEPCHAR, authname , suff );
		else
			sprintf(cdfname,"%c%s%c%s%s", PATHSEPCHAR, authname, PATHSEPCHAR, authname , suff );

		*cdcurfp = cdfopen( cdfname, mode );
		if( ! *cdcurfp ) {
			return(0);
		}

#else
	return(0);
#endif
	} 
	return(1);
}

/*
 * same as above, except it creates a pathname of form
 *      AuthDir/suffix
 */
 SuffFopen(  authname , suff , mode )
  char *authname;
  char *suff;
  char *mode;
{
        char full[BUFSIZ];

        sprintf(full,"%s%s", TlgAuthDirectory(authname) , suff );

	*curfp = fopen( full , mode );
	if( ! *curfp ) {
#if CDFS
		char cdfname[BUFSIZ];

/*
 * for an explanation of this yooogly if-else, see how cdfname is
 * set in AuthFopen()
 */
		if( ! strcmp( authname , BIGINDNAME ) )
			sprintf(cdfname,"/dbase%s",  suff );
		else
			sprintf(cdfname,"/%s%s", authname, suff );
		*cdcurfp = cdfopen( cdfname , mode );
		if( ! *cdcurfp ) {
			if( ! noerrmess )
				fprintf(stderr,"Could not open:%s or %s on CD\n", full , cdfname );
			return(0);
		}
#else
		return(0);
#endif
	}
	return(1);

	
}

 GetFreqP2( authname , ptr , pfreq , p2 )
  char * authname;
  size_t ptr;
  int32 * pfreq;
  int32 * p2;
{
        int32 n;

        OpP2File(authname);


#if CDFS
	if( cdfp2 ) {
		cdcurfp = &cdfp2;
		cd_read_seek( *cdcurfp , (4 * (ptr - 1) ) );
	} else {
#endif
		curfp = &fp2;
		fseek( *curfp , (4 * (ptr - 1) ) , 0 );
#if CDFS
	}
#endif
        Vax_words( &n , sizeof( n ) , 1 , authname );
        *p2 = n;
        ClP2File(authname);

        OpPrecFile(authname);
#if CDFS
	if( cdfprec ) {
		cdcurfp = &cdfprec;
		cd_read_seek( *cdcurfp , (4 * n) );
	} else {
#endif
		curfp = &fprec;
		fseek( *curfp , (4 * n), 0 );
#if CDFS
	}
#endif
        Vax_words( &n , sizeof( n ) , 1 , authname );
        *pfreq = n;

        ClPrecFile(authname);
}




/*
 * Functions that deal with author.ind
 */

long
 IndFseek(authname,off)
  char * authname;
  long off;
{
#if CDFS
	if( cdfind )
		return( cd_read_seek(cdfind,off) );
	else
#endif
		return( fseek(find,off,0) );
}


long
 IndLen(authname)
  char * authname;
{
        long n;
        long savepos;

#if CDFS
	if( cdfind )
                return(cdfind->bytes_total);
#endif
        if( find ) {
                savepos = ftell(find);
                fseek(find,0L,2);
                n = ftell(find);
                fseek(find,savepos,0);
                return(n);
        }
                
        OpIndFile(authname);
#if CDFS
	if( cdfind )
		n = cdfind->bytes_total;
#endif
	if( find ) {
		fseek(find,0L,2);
		n = ftell(find);
	}
        ClIndFile(authname);
        return(n);
}

long
 IndFtell(authname)
  char * authname;
{
#if CDFS
	if( cdfind )
		return(cdftell(cdfind));
	else
#endif
		return(ftell(find));
}

int
 IndFread(authname,bufp,len)
  char * authname;
  char * bufp;
  int len;
{
        int n;

#if CDFS
	if( cdfind )
		n=cdfread( bufp, sizeof * bufp , len , cdfind );
	else
#endif
		n=fread( bufp, sizeof * bufp , len , find );
        return(n);
}

/*
 * Functions that deal with the big index
 */




 BigindOnline(authname)
  char * authname;
{
        if( OpIndFile(authname)) {
                ClIndFile(authname);
                return(1);
        }
        return(0);
}


/*
 * given the number in which a string occurs in bigind.ind,
 * look up its index in bigind.p2
 */

 ThesPtrP2( ptr , p , thesname )
  long ptr;
  long *p;
  char * thesname;
{
#if CDFS
	if( cdfp2 ) {
		cdcurfp = &cdfp2;
		cd_read_seek( *cdcurfp , (4 * (ptr-1) ) );
	} else {
#endif
		curfp = &fp2;
		fseek( fp2 , (4 * (ptr-1) ) , 0 );
#if CDFS
	}
#endif
        Vax_words( p , sizeof( *p ) , 1 , thesname );
}

 ThesFrqTlgp2( p2 , pfreq , lpoint , thesname )
  long p2;
  long *pfreq;
  long * lpoint;
  char * thesname;
{
        long * lp;
	long nfreq;
        long i;

#if CDFS
	if( cdftlgp2 ) {
		cdcurfp = &cdftlgp2;
		cd_read_seek( *cdcurfp , (p2 * 4L) );
	} else {
#endif
		curfp = & ftlgp2;
		fseek( *curfp , (p2 * 4L) , 0 );
#if CDFS
	}
#endif
        Vax_words( &nfreq , sizeof( nfreq ) , 1 , thesname );
	lp = lpoint;
        for(i=0;i<(*pfreq);i++) {
                Vax_words( lp , sizeof (*lp) , 1 , thesname );
                lp++;
        }

}
                

 ThesFrqAuthors( p2 , pfreq , lpoint , thesname )
  long p2;
  long *pfreq;
  long * lpoint;
  char * thesname;
{
        long *  lp;
        long i;

#if CDFS
	if( cdfauthors ) {
		cdcurfp = &cdfauthors;
		cd_read_seek( *cdcurfp , (p2 * 4L) );
	} else {
#endif
		curfp = &fauthors;
		fseek( fauthors , (p2 * 4L) , 0 );
#if CDFS
	}
#endif
        Vax_words( pfreq , sizeof( *pfreq ) , 1 , thesname );
	if( *pfreq > 500 ) {
		*pfreq = 0;
		return(0);
	}

        for(i=0,lp=lpoint;i<(*pfreq);i++) {
                Vax_words( lp , sizeof (*lp) , 1 , thesname );
                lp++;
        }
	return(1);
}
                

 DbaslNexts(s, len , thesname )
  char * s;
  int len;
  char * thesname;
{

#if CDFS
	cdcurfp = &cdfdbaslist;
#endif
	curfp = &fdbaslist;
        if( LocFgets(s,len,thesname) )
                return(1);
        else
                return(0);
}

static
 LocFclose(authname,suffix)
  char * authname;
  char * suffix;
{
#if CDFS
	/*if( TxtIsOnCD(authname) && *cdcurfp ) {*/
	if( *cdcurfp ) {
		cdfclose(*cdcurfp);
		*cdcurfp = NULL;
	} 
		/* else {*/
#endif

	if( *curfp ) {
		fclose(*curfp);
		*curfp = NULL;
	}
}
/*
 * read in a 32 bit data word that has been written out to the disk on
 * a vax -- gets around different byte orders on different machines
 */
 Get_long(lword,authname)
  long * lword;
  char * authname;
{
        
        long tmp;
        int i;
        int c;

        for(*lword=0,i=0;i<4;i++) {
                c = LocFgetc(authname);
                tmp = (long)c;
                tmp = tmp << (8 * i);

                *lword += tmp;
        }
}

/*
 * read in a 16 bit data word that has been written out to the disk on
 * a vax -- gets around different byte orders on different machines
 */
 Get_short(sword,authname)
  short * sword;
  char * authname;
{
        short tmp;
        short i;
        int c;

        for(*sword=0,i=0;i<2;i++) {
                c = LocFgetc(authname);
                tmp = (short)c;
                tmp = tmp << (8 * i);

                *sword += tmp;
        }
}

/*
 *      Routine converts reads shorts and longs written into a file in
 *      VAX byte order.
 *
 */


 Vax_words( Buffer, size, nswap , authname )
  char * Buffer;
  int size;
  int  nswap;
  char * authname;
{
	return( vax_fread( Buffer, size, nswap , *curfp ) );
}

 xVax_words( Buffer, size, nswap , authname )
  char * Buffer;
  int size;
  int  nswap;
  char * authname;
{
    register int i;
    register unsigned t;
    register long * longp;
    register short * shortp;
        
        switch( size )  {

            case 2:                     /* SHORTS */

                shortp = (short *)Buffer;

                for ( i=1; i <= nswap; i++)  {
                        Get_short(shortp,authname);
                        shortp++;
                }
                return(nswap);

            case 4:                     /* LONGS */

                longp = (long *)Buffer;
                for ( i=1; i <= nswap; i++)  {
                        Get_long(longp,authname);
                        longp++;
                }
                return(nswap);

            default:

                fprintf(stderr, "Vax_words: byte swap error, size = %d\n", size);
                exit(1);

        }
}

char *
 LocFgets(s,len,authname)
char * s;
int len;
char * authname;
{
#if CDFS
	if( *cdcurfp )
		return(cdfgets(s,len,*cdcurfp));
	else
#endif
		return(fgets(s,len,*curfp));
}

LocFgetc(authname)
char * authname;
{
#if CDFS
	if( *cdcurfp ) {
		return(cdfgetc(*cdcurfp));
	} else
#endif
		return(fgetc(*curfp));
}
