/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"

#define GETNWORDS 10
#define TMPL BUFSIZ
#define MAXMEM 32
static DumpWords(srch_state * srch,int n);
static unsigned GetFreq( long freq );
static GetAuthNum(long dataword );
static GkCompare(char * s,char * t);
static GetCurIndWord(char * source,char * target);
static SetSliceOfIndex(srch_state * srch, char * key);

    static long * gotp2;
    static char * gotstrings[GETNWORDS+1];
    srch_state * TmpSrch;
    static int first = 1;
    char * authtab[MAXAUTH];
    static long * ThTlgp2;
    static long * ThAuthors;

    srch_state tmpR;
    long ThFreq;
    int gotpA = 0;
    char * Calloc();
    char * Malloc();

/*
 * function definitions
 */
    long IndLen();

/*
 * scan the big index for a word
 */
 ScanThesaur(srch)
  srch_state * srch;
{

        if( StringIsPhrase(srch->key) ) {
                fprintf(stderr,"cannot use Big Index to search for phrase\n");
                return(-1);
        }

        InitBigind();
        strcpy( srch->sname , BIGINDNAME );
        if( ! ThesaurOnline(BIGINDNAME) ) {
		fprintf(stderr,"Big index not online\n");
                return(-1);
	}
        ScanIndex(srch);
        return(1);
}


/*
 * scan a subset of the index for words that begin with a particular
 * string
 */
 ScanIndex(srch)
  srch_state * srch;
{
        int i;
	int hits = 0;
	char * s, *is_common();
        char key[SHORTS];


        if( ! TlgOnline(srch->sname) && ! (srch->rflags&THESAURUS) ) {
                printf("%s not online!\n", srch->sname );
                return(-1);
        }

	s = is_common(srch->key);
	if( s && (srch->rflags&SPELL_CHECK) ) {
		printf("\t%s", s );
		hits++;
	}

        if( ! gotp2 ) {
                gotp2 = (long *)Calloc((unsigned)GETNWORDS+1, (unsigned)(sizeof * gotp2) );
                if( ! gotp2 ) {
                        fprintf(stderr,"ScanIndex:no room for gotp2\n");
                        return(-1);
                }
        }

        if( ! gotstrings[0] ) {
                for(i=0;i<GETNWORDS+1;i++) {
                        gotstrings[i] = (char *)Calloc(sizeof srch->gotstr + 1,sizeof * gotstrings[0]);
                        if( ! gotstrings[i] ) {
                                fprintf(stderr,"ScanINdex:no room for gotstrings[%d]\n", i);
                                return(-1);
                        }
                }
        }
        srch->rflags |= INDEX;
        strcpy(key,srch->key);

        SetSliceOfIndex(srch , key );
        InitLinLookup(srch);
        for(i=0;NextLinPhrase(srch);i++) {
		hits++;
                gotp2[i] = srch->p2;
                strcpy(gotstrings[i],srch->gotstr);
        /*
         * buffer hits up so that you do not have to seek out of
         * the index file on each hit -- this should save seek
         * time on the slow compact disk (if we ever get one that
         * we can use)
         */
                if( i == GETNWORDS - 1 ) {
                        DumpWords(srch,GETNWORDS);
                        i = -1; /* note: i will be incremented 
                                   before the loop repeats */
                }
        }

        DumpWords(srch,i);
	if( hits ) putchar('\n');
	return(hits);


}

static
 DumpWords(srch_state * srch,int n)
{
        int j;

        if( ! TmpSrch ) {
                TmpSrch = (srch_state * )Calloc(1,sizeof * TmpSrch);
                if( ! TmpSrch ) {
                        fprintf(stderr,"Dump:Could not allocate TmpSrch \n");
                        return(-1);
                }
        }
        *TmpSrch = * srch;
        for(j=0;j<n;j++) {
                TmpSrch->p2 = gotp2[j];
		if( TmpSrch->rflags & SPELL_CHECK  ) {
			
			printf("\t%s", gotstrings[j] );
			continue;
		}
                strcpy( TmpSrch->key , gotstrings[j] );
                strcpy( TmpSrch->gotstr , gotstrings[j] );
                if( TmpSrch->rflags & THESAURUS ) {
                    thesaur(stdout,TmpSrch,gotp2[j],gotstrings[j]);
                } else if ( TmpSrch->rflags & (TWOWORDS|SHOWOFFS )) {
                    GetFreqP2( TmpSrch->sname , TmpSrch->p2 , &TmpSrch->freq , &TmpSrch->p2 );
                        ftlg_offs(TmpSrch,TmpSrch->p2);
                } else {
                    GetFreqP2( TmpSrch->sname , TmpSrch->p2 , &TmpSrch->freq , &TmpSrch->p2 );

/*
printf("--sn:%s wd:%s af:%ld pA:%ld; pword %ld\n", srch->sname , TmpSrch->gotstr , TmpSrch->freq , TmpSrch->p2 , TmpSrch->pword );
*/

                   fput_rec( stdout , TmpSrch , "  " );fflush(stdout);
                } 
        }
        
}


/*
 * figure out from two lines in wordlist.index
 *   a) where to start looking in the index 
 *              --> srch->l_start
 *   b) what line number (ie. record number) this is in the wordlist
 *              --> srch->l_lno
 *   c) how far you need to read (the byte offset associated with the
 *         next line in wordlist.index minus srch->l_start)
 *              --> srch->l_len
 * these lines have the form:
 *      word <WHITESPACE> byte_offset <WHITESPACE> line_number
 */
static
 ParseWlistLine(srch,s,nexts)
  srch_state * srch;
  char * s;
  char * nexts;
{
        long atol();
        char *lp = s;
        char *wp = srch->gotstr;

        while(!WHITE(*lp) && *lp) 
                *wp++ = *lp++;
        *wp = 0;

        while(WHITE(*lp) && *lp )
                lp++;
        srch->l_start = atol(lp);

        while(isdigit(*lp) && *lp )
                lp++;
        srch->l_lno = atol(lp);


/*
        if( ! * nexts ) {
 */
        if( ! nexts ) {		/* mod made by vjh -- 5 June 1987 */
                srch->l_len = IndLen(srch->sname) - srch->l_start;
        } else {
                lp = nexts;
                while(!WHITE(*lp) && *lp) 
                        *lp++;

                while(WHITE(*lp) && *lp )
                        lp++;
                srch->l_len = atol(lp) - srch->l_start;
        }
}

  static char gk_tab[256];
  static char prev_line[256];
  static char cur_line[256];
  static char cur_ind_word[256];
  char *  ListindFgets();



/*
 * use wordlist.index to figure out what subset of the index you have to
 * scan
 */
static 
 SetSliceOfIndex(srch_state * srch, char * key)
{
	char curkey[64];

	strcpy(curkey,key);
        if( curkey[0] != '@' && ! isupper(curkey[0]) && curkey[0] != '*' ) {
                srch->l_lno = 1;
                srch->l_start = 0;
                return;
        }

/*
	if( *(curkey+1) == '*') {
		strcpy(curkey+1,curkey+2);
		*(curkey+1) = toupper(*(curkey+1));
	}
*/
        set_gkorder( gk_tab , sizeof gk_tab );

        prev_line[0] = 0;
        
/*  MOD made by vjh to check for wordlist.index files -- not present in early
 *  author distributions.
        OpListindFile(srch->sname);
*/
        if ( ! OpListindFile(srch->sname))  {
            fprintf( stderr, "Can not open wordlist.index file for author %s\n",
                srch->sname );
            exit( 1 );
        }
/* End of MOD */

        while(ListindFgets(cur_line,sizeof cur_line,srch->sname) ) {
                GetCurIndWord(cur_line,cur_ind_word);

                if(GkCompare(curkey,cur_ind_word)<=0) {
                        ParseWlistLine(srch,prev_line,cur_line);
                        goto finish;
                }
                strcpy(prev_line,cur_line);
        }
        ParseWlistLine(srch,prev_line,NULL);

        finish:
                ClListindFile(srch->sname);
/*
printf("srch->l_start %ld; l_lno %ld; l_len %ld\n", srch->l_start , srch->l_lno , srch->l_len);
*/
                return;
}

static
 GetCurIndWord(char * source,char * target)
{
        while(*source != ' ' && *source != '\t' && *source != '\n' && *source )
                *target++ = *source++;
        *target = 0;
}

standucase(s)
char *s;
{
	char * a = s;
	while(*a&&!isalpha(*a)) a++;
	*s = *a;
	strcpy(a,a+1);
}

/*
 *      s --> the key
 *      t --> the word in the index 
 */
static
 GkCompare(char * s,char * t)
{

        if( *s == '@' ) s++;
        if( isupper( *s ) ) *s = tolower( *s );
	else if( *s == '*' ) { /*
				* *)/andra --> a)/ndra	
				* *kadmei=on --> kadmei=on
				*/
		standucase(s);
/*
		char * a = s;
		while(*a&&!isalph(*a)) a++;
		*s = *a;
		strcpy(a,a+1);
*/
	}
        if( isupper( *t ) ) *t = tolower( *t );
	else if( *t == '*' ) {
		standucase(t);
	}
        for(;;) {
                for(;*s==*t;s++,t++) {
                        if(*s==0) {
                                return(0);
                        }
                }
/*
 * don't fail if the word in the index does not match on a
 * non alphabetic char
 */
                if( ! isalpha( *t ) && *t ) {
                        t++;
                        continue;
                } else
                        break;
        }

        while(*s && !isalpha(*s) && *s != '\n' ) s++;
        if(*s==0 || *s == WILDC )
                return( -1 );

        if( *t==0 || *t == WILDC )
                return( 1 );
                
        if( gk_tab[ *s ] < gk_tab[ *t ] )
                return( -2 );
        else
                return( 2 );
}


/*
 * functions specific to scanning the big index
 */

 thesaur( fout , srch , ptr , string )
  FILE * fout;
  srch_state * srch;
  long ptr;
  char * string;
{
        long i;
        long p2;
        char gots[64];

        gotpA = 0;
        
        if( ! ThTlgp2 ) {
                ThTlgp2 = (long *)Calloc(256, sizeof * ThTlgp2 );
        }
        
        if( ! ThAuthors ) {
                ThAuthors = (long *)Calloc(256,sizeof *ThAuthors);
        }

        OpP2File( BIGINDNAME );

        if( OpAuthorsFile( BIGINDNAME ) )
                gotpA++;
        ThesPtrP2(ptr,&p2,BIGINDNAME);

/*
printf("p2=%ld\n", p2 );
*/
        ThesFrqAuthors( p2 , &ThFreq , ThAuthors , BIGINDNAME );
if( ThFreq == 0 ) {
	fprintf(stdout,"failed on [%s]\n", string);
	fprintf(stderr,"failed on [%s]\n", string);
        ClP2File( BIGINDNAME );
        ClAuthorsFile( BIGINDNAME );
	return;
}

        if( OpTlgp2File( BIGINDNAME ) ) {
                ThesFrqTlgp2( p2 , &ThFreq , ThTlgp2, BIGINDNAME  );
        }


        ClP2File( BIGINDNAME );
        ClTlgp2File( BIGINDNAME );
        ClAuthorsFile( BIGINDNAME );


        fprintf(fout,"\"%s\" ", string );
        fprintf(fout,"appears in %ld authors", ThFreq );
        fadd_newline(fout);
	fflush(fout);


        strcpy( gots , srch->gotstr );
                for(i=0;i<ThFreq;i++) {
                        strcpy( srch->gotstr , gots );
                        strcpy( srch->key , gots );
                        ThDumprec(  fout , srch , i , string );
                }
                fadd_newline(fout);
                if( fout != stdout )
                        fclose( fout );
}

 ThDumprec( fout , srch , index , s )
  FILE * fout;
  srch_state * srch;
  long index;
  char * s;
{
        short n;
        unsigned x;
        unsigned GetFreq();

        n = GetAuthNum( ThAuthors[index] );
        x = GetFreq( ThAuthors[index] );
        tmpR = * srch;
        tmpR.pword = 0;
        ngetauth( n , tmpR.sname );
        if( gotpA ) {
                tmpR.p2 = ThTlgp2[index];
                tmpR.freq = x;
                strcpy( tmpR.key , s );
        } else {
                tmpR.p2 = tmpR.freq = 0;
        }

#if AUTOMATON
        if( srch->rflags & TWOWORDS ) {

                if(! TlgOnline(tmpR.sname) ) {
                    fprintf(fout,"%s.tlg not online", tmpR.sname );
                    fadd_newline(fout);
                        return(-1);
                }

                tmpR.rflags = srch->rflags;
                ftlg_offs(&tmpR,tmpR.p2);
                ClTxtFile(tmpR.sname);
        } else
#endif
	if( srch->rflags & SHOWOFFS ) {
                tmpR.rflags = srch->rflags;
                ftlg_offs(&tmpR,tmpR.p2);
                ClTxtFile(tmpR.sname);
	} else
                fput_rec( fout , &tmpR, "\t" );
        fflush( fout );
}

/*
 * the data word is divided up into the following fields:
 *      bits 1-16       16 bits author number
 *      bits 17-32      16 bits the number of times the string occurs
 */

#define FREQMASK        0377600000
#define FREQSHIFT       16
#define HIMASK          0177777

static
 SetAuthNum( source , dest )
  int source;
  long * dest;
{
        long tmp;

        tmp = (long)source;

        
        (*dest) |= ( HIMASK & tmp );
}

static
 GetAuthNum(long dataword )
{
        return( (int)( dataword & HIMASK ) );
}

static
 SetFreq( source , dest )
  long source;
  long * dest;
{
        long tmp;

        tmp = source;
        tmp = FREQMASK & (tmp << FREQSHIFT);
        *dest &= ~FREQMASK;
        *dest |= tmp;
}

static unsigned 
 GetFreq( long freq )
{
        return( (unsigned) (( FREQMASK & freq ) >> FREQSHIFT ) );
}

static
 IsInDbase( dataword , array , len )
  long dataword;
  register long * array;
  int len;
{
        register long anum = dataword & HIMASK;
        int i;

        for(i=0;i<len;i++) {
                if( anum == (array[i] & HIMASK ) )
                        return( 1 );
        }
        return( 0 );
}


 ngetauth( n , s ) 
  int n;
  char * s;
{

        if( first ) {   
                authsetup();
                first = 0;
        }


        if( ! authtab[ n ][ 0 ]  ) {
                char mess[MAXMESS];

                sprintf(mess,"no author listed under %d", n );
                prerror(mess);
                return( ERROR );
        }
                
                
        strcpy( s , authtab[ n ] );
        return( 1 );
}


 authsetup()
{
        FILE * f;
        char * TlgAuthDirectory();
        char mess[MAXMESS];
        char tmp[TMPL];
        char tmpname[TMPL];
        int i;

        if( !authtab[0] ) {
                for(i=0;i<MAXAUTH;i++ ) {
                        authtab[i] = (char *)Malloc(MAXMEM);
                        if( ! authtab[i] ) {
                                fprintf(stderr,"Could not Malloc authtab[%d]\n",i);
                                return(-1);     
                        }
                }
        }
        if( OpDbaslist(BIGINDNAME) <= 0 ) {

                sprintf(mess,"authsetup: could not open %s/dbaslist\n",
                        TlgAuthDirectory(BIGINDNAME) );
                prerror(mess);
                return( ERROR );
        }

        for(;;) {
                int c;
                if( ! DbaslNexts(tmp, sizeof tmp , BIGINDNAME ) )
                        break;
                c=sscanf(tmp,"%s %d", tmpname , &i );
                if( c == EOF )
                        break;
                if( c != 2 ) {
                        sprintf(mess,"authsetup:read in %d args!\n", c );
                        prerror(mess);
                        return(ERROR);
                }
                if( i <=0 ) {
                        fprintf(stderr,"error in authsetup: authline %s\n",
                                tmp );
                        return( ERROR );
                }
                if( i < MAXAUTH )
                        strncpy( authtab[ i ] , tmpname , MAXMEM );
        /* step over anything after the first two arguments of the line */
        }
        ClDbaslist(BIGINDNAME);
}
