/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#include <malloc.h>
void * Malloc(size_t);

srch_state * srch;
srch_state Srch;

#define MAXCNT 200

char * wordarr[MAXCNT];
char * autharr[MAXCNT];


#if MACINTOSH
_main( argc , argv )
#else
main(argc,argv)
#endif
int argc;
char * argv[];
{
        char * s;
        int i = 0;
        int nwords = 0;
        int nauths = 0;
        int wflag = 0;
        int aflag = 0;
        int max;
        int textflag = 0;

        srch = &Srch;

        if( argc <= 2 ) {
                fprintf(ERRFILE, "usage:%s [options] string author\n", argv[0] );
                exit( -1 );
        }
        for(i=0;i<MAXCNT;i++) {
                wordarr[i] = (char *)Malloc((size_t)SHORTS);
                if( ! wordarr[i] ) {
                        fprintf(stderr,"could not Malloc wordarr[%d]\n",i);
                        exit(-1);
                }       
                autharr[i] = (char *)Malloc(SHORTS);
                if( ! autharr[i] ) {
                        fprintf(stderr,"could not Malloc autharr[%d]\n",i);
                        exit(-1);
                }       
        }
                

        while (--argc > 0 && (++argv)[0][0]=='-') 
                switch (argv[0][1]) {

                case 'o':
                        strcpy( srch->savefile , &argv[0][2] );
                        continue;

		case 'S':
                        srch->rflags |= SPELL_CHECK;
			continue;


                case 'r':
                        s = &argv[0][2];
                        srch->lsep = atol( s );
                        while( isdigit( *s ) )
                                s++;
                        switch( *s ) {
                                case 's':
                                        srch->sepunits = SENTENCE;
                                        max = MAXSENT + (srch->lsep * MAXSENT);
                                        break;
                                case 'w':
                                        if( ! srch->lsep ) {
                                            srch->lsep = 1;
                                        }
                                        srch->sepunits = WORD;
                                        max = MAXWORD + (srch->lsep * MAXWORD);
                                        break;
                                case 'l':
                                case '\0':
                                        srch->sepunits = LINE;
                                        max = MAXLINE + (srch->lsep * MAXLINE);
                                        break;
                        
                                default:
                                        fprintf(stderr,
                                          "Uknown unit: %c\n", *s );
                                        break;
                                }
                        continue;

                case 'w':
                        if( (nwords=loadwords( &argv[0][2] )) < 0 )
                                exit( -1 );
                        wflag++;
                        continue;

                case 'c':
                        srch->rflags |= ONLY_VIEW_CHARS|LINEAR;
                        srch->rflags &= ~(INDEX);
                        textflag++;
                        continue;

                case 'm':
                        srch->rflags |= TWOWORDS;
#if AUTOMATON
                        if( ! srch->sepunits ) {
                                srch->lsep = 1;
                                srch->sepunits = SENTENCE;
                                max = (MAXSENT * 2) + (srch->lsep * MAXSENT);
                        }
                        CheckContext(&argv[0][2],max);
                        continue;
#endif

                case 'b':
                        srch->rflags |= BYTEFLAG;
                        continue;

                case 'O':
                        srch->rflags |= SHOWOFFS;
                        continue;

                case 'v':
                        srch->rflags |= VERBOSE;
                        continue;

                case 'a':
                        if( THESAURUS&(srch->rflags) )
                                continue;
                        if( (nauths=loadauths( &argv[0][2] )) < 0 )
                                exit( -1 );
                        aflag++;
                        continue;

                case 's':
                        srch->rflags &= ~(INDEX);
                        srch->rflags |= LINEAR;
                        textflag++;
                        continue;

                case 'p':
                        srch->rflags |= THESAURUS|INDEX ;
                        strcpy( autharr[0] , BIGINDNAME );
                        strcpy( srch->sname , BIGINDNAME );
                        nauths = 1;
                        continue;
                default:
                        fprintf(ERRFILE, "tlg_sel: unknown flag\n");
                        continue;
                }

        
        if( !wflag ) {
        strcpy( wordarr[nwords++] , *argv );
        argc--; argv++;
        }

        while( argc-- > 0 && ! (srch->rflags&THESAURUS) ) {
                strncpy( autharr[nauths++] ,  *argv , SHORTS);
                argv++;
        }
        

printf("nauths %d\n", nauths );
        for(i=0;i<nauths;i++) {
                srch_state LoopSrch;
                int j;
        
        /*
         * you want to reset the srch_state after every author has been searched
         */
                for( j=0;j<nwords;j++) {
                        LoopSrch = * srch;
                        strncpy( LoopSrch.sname , autharr[i], sizeof LoopSrch.sname );
                        strncpy( LoopSrch.key , wordarr[j], sizeof LoopSrch.key );
                        
			if( srch->rflags & SPELL_CHECK ) 
				printf("%s", LoopSrch.key );
			else
				printf("Looking for %s in %s\n",LoopSrch.key,LoopSrch.sname );
                        if( ! PickSearch(&LoopSrch) && (srch->rflags & SPELL_CHECK) ) {
				printf("\tMISS\n");
				stripdiacrit(LoopSrch.key);
				printf("%s", LoopSrch.key );
				if( ! PickSearch(&LoopSrch) ) {
					printf("\tMISS2\n");
				}
			}
                }
        }
}


loadwords( infile )
char * infile;
{
        FILE * f;
        char tmpb[BUFSIZ];
        int i  = 0;

        if( (f=fopen(infile,"r")) == NULL ) {
                fprintf(ERRFILE,"Could not open %s\n", infile);
                return( -1 );
        }

        while( fgets( tmpb , sizeof tmpb , f ) && i < MAXCNT - 1 ) {
                if( tmpb[0] == '\n' )
                        continue;
                strncpy( wordarr[i] , tmpb , SHORTS );
                wordarr[i][ strlen( wordarr[i] ) - 1 ] = 0;
		trim_white( wordarr[i] );
                i++;
        }
        fclose( f );
        return( i );
}

loadauths( infile )
char * infile;
{
        FILE * f;
        char tmpb[BUFSIZ];
        int i  = 0;

        if( (f=fopen(infile,"r")) == NULL ) {
                fprintf(ERRFILE,"Could not open %s\n", infile);
                return( -1 );
        }

        while( fgets( tmpb , sizeof tmpb , f ) && i < MAXCNT - 1 ) {
                if( tmpb[0] == '\n' )
                        continue;
                strncpy( autharr[i] , tmpb , SHORTS );
                autharr[i][ strlen( autharr[i] ) - 1 ] = 0;
		trim_white( autharr[i] );
                i++;
        }
        fclose( f );
printf("retuning %d\n", i );
        return( i );
}
