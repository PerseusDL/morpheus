/*
 * this program was the first created. it is unbelievably ugly and impossible to figure out,
 * but it has proven fairly reliable.
 */
#include <stdio.h>
#include <ctype.h>
#define MAXLIN 2048
#define GREEK 1
#define ROMAN 2

char tlgch[256];
char wbound[ 256 ];

long previous = 0;
int firstwork = 1;
int firstauth = 1;
int authcount = 0;
int endwork = 0;
int wordfont = GREEK;
int curfont = GREEK;
int sawchar = 0;
int broken = 0;
char anum[15];
char oldanum[15];
char wknum[15];
char oldwknum[15];
char wkname[15];
char oldwkname[15];
long workwords;
long authwords;
long startcnt;
long workcnt;
long authcnt;
long ftell();


long bytcnt = -1;
long start = 0;
long nwords = 0;
int nworks = 0;
int nauths = 1;
long curword = 0;
long wlen = 0;
long maxword = 0;
long maxsep = 0;
long firstw, nextw;
int boundflg = 1;
int hyphflg = 0;
int init = 1;
char base[MAXLIN];
char line[MAXLIN];
char tmp[MAXLIN];
char * slide;
int needchar = 0;
FILE * fin;
FILE * fbroken;
FILE * froman;
FILE * fgreek;
char workfile[MAXLIN];
char commonfile[MAXLIN];
char filefile[MAXLIN];
char authfile[MAXLIN];
char outline[MAXLIN];
char basename[MAXLIN];

main( argc , argv )
int argc;
char * argv[];
{
int c;
FILE * f;

	if( argc == 1 )
		fin = stdin;
	else {
		strcpy( base , argv[1] );
		strcat( base , ".tlg" );
		if( (fin = fopen( base , "r" )) == NULL ) {
			fprintf(stderr,"could not open %s\n", base );
			exit( 0 );
		}
	}

	if( setup() < 0 ) {
		fprintf(stderr,"setup failed\n");
		exit(-1);
	}

	strcpy( basename , argv[1] );

	strcpy( base , argv[1] );
	strcat( base , ".words" );
	fgreek = fopen( base , "w" );
	if( fgreek == NULL ) {
		fprintf(stderr,"could not open %s.words\n", base );
		exit( 0 );
	}

	strcpy( commonfile , argv[1] );
	strcat( commonfile , ".comwords" );

	strcpy( workfile , argv[1] );
	strcat( workfile , ".workfile" );
	if( (f=fopen(workfile,"w")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", workfile );
		exit( -1 );
	}
	fclose( f );

	unlink("auths.common");
	unlink("works.common");
	
	strcpy( authfile , argv[1] );
	strcat( authfile , ".auth" );
	f = fopen( authfile , "w" );
	if( f == NULL ) {
		fprintf(stderr,"could not open %s\n", authfile );
		exit( 0 );
	}
	fclose( f );	

	strcpy( filefile , argv[1] );
	strcat( filefile , ".file" );
	f = fopen( filefile , "w" );
	if( f == NULL ) {
		fprintf(stderr,"could not open %s\n", filefile );
		exit( 0 );
	}
	fclose( f );

	strcpy( base , argv[1] );
	strcat( base , ".roman" );
	froman = fopen( base , "w" );
	if( froman == NULL ) {
		fprintf(stderr,"could not open %s.roman\n", base );
		exit( 0 );
	}

	strcpy( base , argv[1] );
	strcat( base , ".broken" );
	fbroken = fopen( base , "w" );
	if( fbroken == NULL ) {
		fprintf(stderr,"could not open %s.broken\n", base );
		exit( 0 );
	}

	slide = line;


	while( (c=getC( )) != EOF )
		judge( c );

	endwork++;
	dumpwork();
	dumpauth();
	dumpfile();
	exit( 1 );


}

static char * wordp = outline;

judge( c )
int c;
{
if( wbound[ c ] )
	{
	
/*
printf("%d [%s]\n", boundflg, outline );
*/
	wordp = outline;
	if( !boundflg )
		{
		if( curword > maxword )
			maxword = curword;
		curword = 0;
		outline[50] = 0;
		if( sawchar ) {
			nwords++;
			workwords++;
			authwords++;
		}
/*
printf("toocommon(%s) %d\n", outline , toocommon(outline) );
*/
		if( !toocommon( outline ) && sawchar )
			{
			sawchar = 0;
			zap2ndacc(outline);
			sprintf(outline, "%s\t%0.8ld\n", outline , start );
			if( broken ) {
				if( worthit( outline ) ) 
					fprintf(fbroken, "%s",outline );
				broken = 0;
			} else
				if( wordfont == GREEK ) {
/*
printf("gkword:%s\n", outline );
*/
					fprintf(fgreek, "%s",outline );
				} else {
					fprintf(froman, "%s", outline );
					fflush( froman );
				}
		    }
		sawchar = 0;
		}
		
	boundflg++;
	wordfont = curfont;
	return;
	}
if( tlgch[ c ] )
	{
	if( isalpha( c ) )
		sawchar++;
	if( boundflg ) 
		{
		previous = start;
		start = bytcnt;
		boundflg = 0;
		}
	curword++;
	wlen++;
	if( c == '\\' )
		c = '/';
	*wordp++ = c ;
	*wordp = 0;
	}
}


getC()
{
int c;

	for(;;) {
		c = Getchar();

		if( c == '{' ) {
			while( (c=Getchar()) != '}' )
				;
			continue;
		}
		if( c == '-' ) {
			hyphflg++;
			while( (c=Getchar()) != '\n' )
				;
			needchar++;
			continue;
		}
		if( needchar ) {
			if( !tlgch[ c ] )
				continue;
			needchar = 0;
		}
		break;
	}
	
	return( c );
}

Getchar()
{
	if( !*slide ) {
		for(;;) {
		/*
		 * reset bytcnt before each line
		 */
			bytcnt = ftell(fin);
			if( !tlg_fgets( line , MAXLIN , fin )  )
				return( EOF );
			if( line[0] == '~' ) {
				if( line[1] == 'a' || line[1] == 'b'
				    || line[1] == 'c' ) {
					newwork( &line[1] );
				}
				bytcnt = ftell(fin);
				continue;
			}
			slide = line;
			break;
		}
	} else
		bytcnt++;
	if( *slide == '$' )
		curfont = GREEK;
	if( *slide == '&' )
		curfont = ROMAN;

	if( *slide == ' ' ) {
		if( *(slide+1) == '?' ) {
			slide++; slide++;
			bytcnt++;
			broken++;
			return( '!' );
		} else
			broken = 0;
	} 
	if( *slide == '!' )
		broken++;
	return( *slide++ );
}



same_w( s1 , s2 )
register char * s1;
register char * s2;
{
	if( *s1 == '*' ) s1++;

	if( !strcmp( s1 , s2 ) )
		return( 1 );
	else
		return( 0 );
}

/*
newgap( gap , sbyte , endbyte , prevbyte )
long gap;
long sbyte;
long endbyte;
long prevbyte;
{

int i;

for(i=GAPLIST;i>=0;i--)
	{
	if( gap >= Gaps[i].separation && i > 0 )
		{
		Gaps[i].separation = Gaps[i-1].separation;
		Gaps[i].first = Gaps[i-1].first;
		Gaps[i].second = Gaps[i-1].second;
		Gaps[i].previous = Gaps[i-1].previous;
		}
	else
		{
		Gaps[i+1].separation = gap;
		Gaps[i+1].first = sbyte;
		Gaps[i+1].second = endbyte;
		Gaps[i+1].previous = prevbyte;
		return;
		}
	}
}

showgap()
{
int i;
for(i=0;i<=GAPLIST;i++)
	{
		Gaps[i].separation,Gaps[i].first, Gaps[i].second ,
		Gaps[i].previous, Gaps[i].second - Gaps[i].previous );
	}

for(i=0;i<SEPTAB;i++)
}
*/

worthit( word )
register char * word;
{
	int i;
	char * s = word;

	for(i=0;*s;s++) {
		if( isalpha( *s ) )
			i++;
	}
	if( i > 2 )
		return( 1 );
	return( 0 );
}

setup()
{
	int i;

	if( tabsetup() < 0 )
		return(-1);

	tlgch[ ')' ]++;
	tlgch[ '(' ]++;
	tlgch[ '/' ]++;
	tlgch[ '\\' ]++;
	tlgch[ '=' ]++;
	tlgch[ '+' ]++;
	tlgch[ '|' ]++;
	tlgch[ '*' ]++;
	tlgch[ '!' ]++;
	tlgch[ '\'' ]++;
	
	for(i='A';i<='Z';i++)
		tlgch[ i ] ++ ;
	for(i='a';i<='z';i++)
		tlgch[ i ] ++ ;

	wbound[ '$' ] ++;
	wbound[ '&' ] ++;

	wbound[ '.' ] ++;
	wbound[ ',' ] ++;
	wbound[ ' ' ] ++;
	wbound[ ';' ] ++;
	wbound[ ':' ] ++;
	wbound[ '_' ] ++;
	wbound[ '\n' ] ++;

}


newwork( s )
register char * s;
{
	register char * a;
	char * startp;

	startp = s;


	while( *s ) {
	    switch( *s ) {
		case 'a':
			firstauth = 0;
			anum[0] = 0;
			s++;
			a = anum;
			if( *s++ != '"' ) {
				fprintf(stderr,"bad format: %s\n", s-1 );
				return;
			}
			while( *s != '"' && *s )
				*a++ = *s++;
			*a = 0;
			if( strcmp( anum , oldanum ) && oldanum[0] ) {
				dumpauth();
				nauths++;
				authcount++;
				authwords = 0;
				if( bytcnt < 0 )
					authcnt = 0;
				else
					authcnt = bytcnt;
			}
			strcpy( oldanum , anum );
			if( *s != '"' ) {
				fprintf(stderr,"Bad format: %s\n", startp );
			}
			s++;
			break;
		case 'b':
			if( !firstwork ) {
				dumpwork();
			}
			wkname[0] = 0;
			strcpy( oldwknum , wknum );
			strcpy( oldwkname , wkname );
			nworks++;

			s++;
			a = wknum;
			if( *s++ != '"' ) {
				fprintf(stderr,"bad format: %s\n", s-1 );
				return;
			}
			while( *s != '"' && *s )
				*a++ = *s++;
			*a = 0;
			if( *s != '"' ) {
				fprintf(stderr,"Bad format: %s\n", startp );
			}
			s++;
			if( bytcnt < 0 )
				workcnt = 0;
			else
				workcnt = bytcnt;
			workwords = 0;
			firstwork = 0;
			break;
		case 'c':
			wkname[0] = 0;
			s++;
			a = wkname;
			workwords = 0;

			if( *s++ != '"' ) {
				fprintf(stderr,"bad format: %s\n", s-1 );
				return;
			}
			while( *s != '"' && *s )
				*a++ = *s++;
			*a = 0;
			if( *s != '"' ) {
				fprintf(stderr,"Bad format: %s\n", startp );
			}
			s++;
			break;
		default:
			s++;
			return;
		}
	}
}



#include <stdio.h>
#define MAXARR 1000
#define MAXKEY 30
char comwords[MAXARR][MAXKEY];
long workfreq[MAXARR];
long authfreq[MAXARR];
long filefreq[MAXARR];
#define HASHSIZE 1024
int hashtab[HASHSIZE];
int ncomwords = 0;

	
tabsetup()
{
	FILE * f;

	char * libp;
	char * getenv();
	char common[BUFSIZ];
	
	if((libp=getenv("LIBDIR")) == NULL ) {
		fprintf(stderr,"Need to set LIBDIR in your environment!\n");
		return(-1);
	}

	sprintf(common,"%s/common.sort", libp );

	if( (f=fopen(common,"r"))==NULL) {
		fprintf(stderr,"could not open %s\n", common );
		exit( -1 );
	}
	
	while( fgets( comwords[ncomwords] , sizeof comwords[0] , f ) && ncomwords < MAXARR - 1 ) {
		comwords[ncomwords][ strlen( comwords[ncomwords] ) - 1 ] = 0;
		hashtab[ hash( comwords[ncomwords] ) ]++;
		ncomwords++;
	}
}

toocommon( s )
char * s;
{
int high;
int low;
int mid;
int comp;

	if( !hashtab[ hash( s ) ] )
		return( 0 );

	high = ncomwords-1;
	low = 0 ;
	
	while( low<=high ) {
		mid = (low+high)/2 ;
		comp = strcmp( s , comwords[mid] );
		if( comp < 0 ) 
			high = mid - 1 ;
		else if ( comp > 0 )
			low = mid + 1;
		else  { /* found match */
			authfreq[mid] ++;
			filefreq[mid] ++;
			workfreq[mid] ++;
			return( 1 );
		}
	}
	return( 0 );
}

hash( s )
register char * s;
{
	int i = 0;
	while( *s ) 
		i += *s++;
	return( (i % HASHSIZE) );
}

dumpauth()
{
FILE * f;
int i;

	if( (f=fopen(authfile,"a")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", authfile );
		exit( -1 );
	}

	fprintf(f,"%ld,%ld\tan:%s wc:%ld\n",
		authcnt, bytcnt - authcnt , oldanum , authwords );

	fclose( f );

	if( endwork && authcount == 0 )
		return;

	if( authwords == 0 )
		return;

	if( (f=fopen("auths.common","a")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", authfile );
		exit( -1 );
	}
		for(i=0;i<ncomwords;i++) {
/*
			float tmpfrq ;
			tmpfrq = (float)authfreq[i];
			authfreq[i] = 0;
			fprintf(f,"%s\twn:%s\twd:%s\taf:%.0f\trf:%.2f\n",
				comwords[i] , oldanum, comwords[i] , tmpfrq , 
				( (tmpfrq*10000)/(float)authwords) ); 
*/
		}
	fclose( f );
}

dumpwork()
{
FILE * f;
int i;

	if( (f=fopen(workfile,"a")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", workfile );
		exit( -1 );
	}

/*
if( nworks == 1 && endwork )
	{ strcpy( oldwknum , wknum ); strcpy( oldwkname , wkname ); }
*/

/*
	fprintf(f,"%ld,%ld\twk:%s ti:%s wc:%ld\n",
		workcnt, bytcnt - workcnt , oldwknum , oldwkname, workwords );
*/

	fprintf(f,"%ld,%ld\twk:%s ti:%s wc:%ld\n",
		workcnt, bytcnt - workcnt , wknum , wkname, workwords );

	fclose( f );

	if( workwords == 0 )
		return;
	if( (f=fopen("works.common","a")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", workfile );
		exit( -1 );
	}
	for(i=0;i<ncomwords;i++) {
/*
		float tmpfrq ;
		tmpfrq = (float)workfreq[i];
		workfreq[i] = 0;
		fprintf(f,"%s\twk:%s ti:%s wd:%s af:%.0f rf:%.2f\n",
/*
			comwords[i] , oldwknum,  oldwkname ,comwords[i] , tmpfrq , 
*
			comwords[i] , wknum,  wkname ,comwords[i] , tmpfrq , 
			( (tmpfrq*10000)/(float)workwords) ); 
*/
	}
	fclose( f );
}

dumpfile()
{
	FILE * f;
	int i;
	char pathname[1024];

#ifdef SYS5
	getcwd( pathname );
#else
	getwd( pathname );
#endif

	if( (f=fopen(filefile,"w")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", filefile );
		exit( -1 );
	}
	fprintf(f,"%s\tsn:%s ln:%ld Ac:%d Wc:%d to:%ld\n",
		basename,  basename,  bytcnt, nauths , nworks, nwords );
	fclose( f );

	if( (f=fopen(commonfile,"w")) == NULL ) {
		fprintf(stderr,"Could not open %s\n", commonfile );
		exit( -1 );
	}
	
	for(i=0;i<ncomwords;i++) {
/*
		float tmpfrq ;
		tmpfrq = (float)filefreq[i];
		filefreq[i] = 0;
		fprintf(f,"%s\tsn:%s\twd:%s\taf:%.0f\trf:%.2f\n",
			comwords[i] , basename,  comwords[i] , tmpfrq , 
			( (tmpfrq*10000)/(float)nwords) ); 
*/
	}
	fclose( f );
}

tlg_fgets( char * line , int nlen , FILE * fin )
{
	char * p = line;
	int c;

	while((c=fgetc(fin))>=0200&&c!=EOF) ;
	if( c == EOF ) return(0);
	*p++ = c;
	for(;;) {
		c = fgetc(fin);
		if( c == EOF ) return(0);
		if(c>=0200) {
			/*while((c=fgetc(fin))>=0200&&c!=EOF) ;*/
			break;
		}
		*p++ = c;
	}
	*p++ = '\n';
	*p = 0;
/*
printf("[%s]\n", line );
*/
	if(c == EOF ) return( 0 );
	return(1);
}

zap2ndacc(char *s)
{
	int hasacc = 0;

	while(*s) {
		if(*s=='//' || *s == '=' ) {
			if(hasacc ) {
				strcpy(s,s+1);
				continue;
			}
			hasacc++;
		}
		s++;
	}
}
