/*
 *      Written by Jud Harward, University of Cincinnati, 20 August 1985
 */


/*LINTLIBRARY*/

#include  "ssearch.h"
#include  "assert.h"

static char  SCCS_ID[] = " ssearch.c  1.5  8/25/85 ";


/*      Parameters                                                      */

#define  MAXMATCH   120         /* max length of reconstructed matching
                                /*   string                             */
#define  MAXLIST    20          /* max number of elements in context
                                /*   list, mlist                        */
#define  MAXPEND    3           /* max number of pending contexts       */
#define  MAXCTXT    30          /* max number of Contexts in ring stack */


/*      External definitions for this package                           */

uchar   *ssitxt;                /* ptr to head of current text segment  */
uchar   *ssiptr;                /* ssgetc buffer ptr                    */
long     ssict;                 /* ssgetc buffer counter                */


/*      External static definitions for this package                    */

static SSauto   Ssaton;         /* ptr to current automaton             */

static uchar   *Mlist[MAXLIST+1][2];
static uchar    Mstring[MAXMATCH+1];
static SSmtext  Ssmtext = {
                    0,
                    (off_t) 0,
                    0,
                    Mstring + MAXMATCH,
                    Mlist + MAXLIST
                };

static short    sstoken;        /* most recent token matched            */
static short    sstc;           /* most recent base text char read      */
static uchar   *ssmptr;         /* ssbmatch string ptr                  */
static long     ssmct;          /* ssbmatch string counter              */
static uchar   *ssbtxt;         /* ptr to head of current backtrack     */
                                /*   text segment                       */
static uchar   *ssbptr;         /* ssback ptr into current backtrack    */
                                /*   text segment                       */
static uchar   *sslnwbp;        /* ptr to last non-wordbreak char
                                /*   during backtrack                   */
static off_t    sstofft;        /* offset of tail of current match      */


/*      ssearch states                                                  */

static enum  SSstate    {
                        PROCESS,
                        MATCH,
                        EVAL,
                        WRAPUP
                        };


/*
 *      Process states and context types:
 *
 *      Note there is much overlap here.  Context types can be process
 *      states, and certain process states have several names.
 */

#define  START  0       /* State/Type           */
#define  BASE   1       /* State/Type           */
#define  MSG    1       /* State/Type           */
#define  SRCH   2       /* State/Type           */
#define  ESC    3       /* State/Type           */
#define  RMSG   3       /* State/Type           */
#define  BMSG   4       /* State                */
#define  BSRCH  5       /* State                */
#define  META   6       /* Type                 */


/*
 *      Macros
 */

#define  SSMode( MD )   ( Ssaton->ssmode == MD )
#define  ssbmatch()     ( ssmct-- ? *(--ssmptr) : NUL )
#define  ssback()       ( (ssbptr == ssbtxt) ? ssctxt(BACKEOT) :  *(--ssbptr) )
#define  ssmcput( c )   ( (Ssmtext.mstring == Mstring) ? ssctxt(LONGMATCH) : \
                            ( sslnwbp = ssbptr, *(--Ssmtext.mstring) = c ) )
#define  sswbput( )     ( (Ssmtext.mstring == Mstring) ? ssctxt(LONGMATCH) : \
                            ( *(--Ssmtext.mstring) = WBC ) )

#define  RSremove( XT )   rsremove( &XT, Ssaton->ssxtack )
#define  RSpush( XT )  rspush( &XT, Ssaton->ssxtack )
#define  RSget( XT )   rsget( &XT, Ssaton->ssxtack )
#define  RSpop( XT )   rspop( &XT, Ssaton->ssxtack )
#define  RSreset( )    rsreset( Ssaton->ssxtack )

#define  XTpop( XT )   ( spop( &XT, Ssaton->ssptack ))
#define  XTpush( XT )  ( spush( &XT, Ssaton->ssptack ))


SSauto
ssinit( nstr, sarray, subst, ctable, escrout, bufrout )
short   nstr;
uchar  *sarray[];
uchar  *subst[][2];
Centry  ctable[128];
uchar  *(* escrout)();
long    (* bufrout)();
{
    register SSauto  Ssauto;
    short  nsub;
    short  i, k;
    short  tkl;
    Ctxt   xttemp;
    TKtrans  Trans;
    uchar *tcp;
    uchar *xcp;
    char  *malloc();
    char  *calloc();
                

        if (( Ssauto = (SSauto) calloc( sizeof( SSmach ), 1 )) == NULL )
            return( NULL );
        Ssaton = Ssauto;
        Ssauto->ssarray = sarray;
        Ssauto->ssubst = subst;
        Ssauto->ssctab = ctable;

        if (( Ssauto->ssescr = escrout ) == NULL )
            ssdie( "ssinit: no escape handling routine\n" );
        if (( Ssauto->ssbufr = bufrout ) == NULL )
            ssdie( "ssinit: no buffer handling routine\n" );

        if (( Ssauto->ssxtack = rscreate( POINTER, MAXCTXT )) == NULL ) {
            goto  abort;
        }
        if (( Ssauto->ssptack = screate( POINTER, MAXPEND )) == NULL ) {
            goto  abort;
}
        if (( Ssauto->ssxthd = (Ctxt) calloc( sizeof( Context ), MAXCTXT ))
                == NULL )  {
            goto  abort;
        }
        if (( Ssauto->sstree = tkcreate()) == NULL )  {
                goto  abort;
        }

    /* Load the context ring stack                                      */
        for ( k = 0; k < MAXCTXT; k++ )  {
            xttemp = &(Ssauto->ssxthd[k]);
            RSpush( xttemp );
        }

    /* Count the subst entries, record the lengths of subst strings     */
    /*  and substitution text.  Then enter the subst strings in the     */
    /*  token automaton.                                                */
        if ( subst )  for ( nsub = 0; subst[nsub][0]; nsub++ ) ;
        else  nsub = 0;
        Ssauto->ssnsub = nsub;
        if (( Ssauto->sstkleng = (short *) malloc( 2 * (nsub + nstr))) == NULL ){
            goto  abort;
        }
        if ( nsub > 0 )  {
            if (( Ssauto->ssubleng = (short *) malloc( 2 * nsub )) == NULL ){
                goto  abort;
            }
        }
        else  Ssauto->ssubleng = NULL;
        for ( k = 0; k<nsub; k++ )  {
            Ssauto->sstkleng[k] = strlen( subst[k][0] );
            Ssauto->ssubleng[k] = strlen( subst[k][1] );
            if ( tkenter( Ssauto->sstree, subst[k][0], k+1 ) == FAILURE ){
                goto  abort;
            }
        }

    /* Record the lengths of the sarray search strings and enter them   */
    /*  in the token automaton, performing ctable translation.          */
        for ( k = nsub; k < nsub + nstr; k++ )  {
            Ssauto->sstkleng[k] = tkl = strlen( sarray[ k-nsub ] );
            if (( tkl == 0) || (tkl > MAXMATCH))
                ssdie( "ssinit: illegal search string \"%s\"\n",
                    sarray[ k-nsub ] );
            xcp = Mstring;
            for ( tcp = sarray[ k-nsub ]; *tcp != NUL; tcp++ )  {
                if ( ctable )  {
                    if (( *xcp = ctable[ *tcp & SEVENBIT ].cx ) == NUL )
                        continue;
                    else  xcp++;
                }
                else  *( xcp++ ) = *tcp;
            }
            *xcp = NUL;
            if ( tkenter( Ssauto->sstree, Mstring, k+1 ) == FAILURE )
/*
                ssdie( "ssinit: can't enter search string \"%s\"\n",
                    sarray[ k-nsub ] );
*/
                fprintf(stderr, "ssinit: can't enter search string \"%s\"\n",
                    sarray[ k-nsub ] );
        }

        if ( tkcompile( Ssauto->sstree ) == FAILURE ) {
            goto  abort;
        }

    /* Set up the index arrays for ssearch()                            */

        Trans = Ssauto->sstree->link->child;    /* WCARD state          */
        for ( Trans = Trans->sibling; Trans; Trans = Trans->sibling )
            (Ssauto->sssind)[ Trans->cval ] = YES;
        for ( i=0;  i<128; i++ )  {
            (Ssauto->ssmind)[ i ] = (Ssauto->sssind)[ ctable[ i ].cx ];
            if ( ctable[ i ].cflags & CF_ESC )
                (Ssauto->ssmind)[ i ] = YES;
        }

        Ssauto->sswbr = NO;
        Ssauto->ssmode = START;
        Ssauto->ssfd = NEWFILE;
        if (( Ssauto->sscct =
                (* Ssauto->ssbufr)( &Ssauto->sscbuf, &Ssauto->ssfd , SSBUFSIZ )) == 0 )
                    ssdie( "ssinit: buffer routine failure or null file\n" );

        return( Ssauto );

abort:  ssend( Ssauto );
        return( NULL );

}


ssreset( Ssauto )
SSauto  Ssauto;
{
        Ssauto->sswbr = NO;
        tkreset( Ssauto->sstree );
}


ssend( Ssauto )
register SSauto  Ssauto;
{

        assert( Ssauto );
        Ssauto->ssfd = FREEBUF;
        if ( Ssauto->sscbuf )
            (* Ssauto->ssbufr)( &Ssauto->sscbuf, &Ssauto->ssfd , SSBUFSIZ );
        if ( Ssauto->ssobuf )
            (* Ssauto->ssbufr)( &Ssauto->ssobuf, &Ssauto->ssfd , SSBUFSIZ );
        if ( Ssauto->ssubleng )  free( (char *) Ssauto->ssubleng );
        if ( Ssauto->sstkleng )  free( (char *) Ssauto->sstkleng );
        if ( Ssauto->ssxthd )  free( (char *) Ssauto->ssxthd );
        if ( Ssauto->ssptack )  sdestroy( Ssauto->ssptack );
        if ( Ssauto->ssxtack )  rsdestroy( Ssauto-> ssxtack );
        if ( Ssauto->sstree )  tkdestroy( Ssauto->sstree );
        free( (char *) Ssauto );
}


/*
 *      ssearch() is called by the user and processes text contexts
 *      using the token tree generated by ssinit().  It incoporates
 *      code modified from tkmatch() to save on subroutine calls.
 *      ssearch() does not worry about where the input characters
 *      come from.  That is the concern of ssctxt(), with which
 *      ssearch() communicates via the messages of enum  XTstate
 *      (in ssearch.h).  ssearch() and ssctcxt() are coroutines,
 *      the former concerned with characters and their meanings,
 *      the latter with contexts and buffers.
 */

SSmatch
ssearch( Ssauto )
register SSauto  Ssauto;
{
    register TKtree   Mtree;
    register TKtrans  Trans;
    register TKtrans  Tfail;
    TKtrans           Ostate;
    Centry           *Tcent;

    enum SSstate      sstate;
    register short    tcx;
    unsigned char     tcf;
    register uchar    idle;

    Ssaton = Ssauto;                    /* SETUP */
    Mtree = Ssauto->sstree;
    ssctxt( STARTUP );
    if ( Mtree->cstate->cval == WCARD )  idle = YES;
    else  idle = NO;
    sstate = (Mtree->ostate) ? MATCH : PROCESS;

    for (;;)  {

#ifdef  DEBUG
    fprintf(stderr, "ssearch: state = %d, ssmode = %d\n",
            sstate, Ssauto->ssmode);
#endif

        switch( sstate )  {             /* DISPATCH */

        case  PROCESS:
            while (( sstc = ssgetc()) != EOF )  {
#ifdef  DEBUG
                fputc(sstc, stderr); 
#endif
                if ( idle && !( SSMode( SRCH ) ?
                    Ssauto->sssind[sstc] : Ssauto->ssmind[sstc] ))  continue;
                if ( !SSMode( SRCH ) )  {
                    Tcent = (Ssauto->ssctab) ?
                                &(Ssauto->ssctab)[sstc & SEVENBIT] : NULL;
                    tcx = Tcent ? Tcent->cx : (uchar) sstc;
                    tcf = Tcent ? Tcent->cflags : CF_NORM;
                    if ( tcf & CF_ESC )  {
                        ssctxt( ESCSEQ );
                        continue;
                    }
                    if ( tcx == NUL )  continue;
                }
                else  tcx = sstc;
                if ( tcx == WBC )  {
                    if ( Ssauto->sswbr )  continue;
                    Ssauto->sswbr = YES;
                }
                else  Ssauto->sswbr = NO;
                idle = NO;


                Tfail = Mtree->cstate;
                Trans = Tfail->child;
                Mtree->cstate = NULL;

mfail:          if ( Trans != NULL && Trans->cval == WCARD )  {
                    Mtree->cstate = Trans;
                    Trans = Trans->sibling;
                }
                while ( Trans != NULL )  {
                    if ( Trans->cval > tcx )  break;
                    else if ( Trans->cval == tcx )  {
                        Mtree->cstate = Trans;
                        break;
                    }
                    else  Trans = Trans->sibling;
                }
        /* failure transition                                           */
                if ( Mtree->cstate == NULL )  {
                    Tfail = Tfail->fail;
                    Trans = Tfail->child;
                    goto  mfail;
                }
        /* wildcard or normal transition                                */
                else  if ( Trans && (Trans->sflags & SF_OUTPUT) )  {
                            Mtree->ostate = Trans;      /*  MATCH       */      
                            break;
                }
                else  {
        /* Trans == NULL ==> WCARD transition; set idle                 */
                    if ( !Trans )  idle = YES;
                    continue;
                }
            }

            if ( sstc == EOF )  {
                sstate = WRAPUP;
                continue;
            }
            else  {
                while (( sstc = ssgetc()) != EOF )  {
                    Tcent = (Ssauto->ssctab) ?
                                &(Ssauto->ssctab)[sstc & SEVENBIT] : NULL;
                    if ( (Tcent->cx != NUL) || !(Tcent->cflags & CF_MSG) )
                        break;
                }
                if ( sstc != EOF )  ssungetc();
                sstate = MATCH;
            }                                           /* Fall Through */


        case  MATCH:
            Ssauto->ssiptr = ssiptr;
            Ssauto->ssict = ssict;

            Ostate = Mtree->ostate;
            Ostate = Ostate->rstate;
            sstoken = Ostate->sval;
            Ostate = Ostate->fail;
            if ( !(Ostate->sflags & SF_OUTPUT) )
                Mtree->ostate = NULL;
            else  Mtree->ostate = Ostate;               /* Fall Through */


        case EVAL:
            if ( sstoken <= Ssauto->ssnsub )  {
                ssctxt( SUBSTTXT );
                sstate = PROCESS;
                continue;
            }
            else if ( ssbtrack() == FAILURE )  {
                sstate = PROCESS;
                continue;
            }

            else  return( &Ssmtext );                   /* REPORT */


        case  WRAPUP:
            if (( sstoken = tkmatch( Ssauto->sstree, WBC )) >0 )  {
                sstate = EVAL;
                continue;
            }
            else  return( NULL );


        default:
            ssdie( "ssearch: illegal state = %d\n", sstate);


        }
    }
}

/*
 *      ssbtrack():  backtrack to check match against matchtext in sarray
 */

ssbtrack()
{
    short     tc;
    uchar     mc;
    uchar     tcx;
    uchar     tcf;
    uchar     bwbr;
    Centry   *Tcent;

        ssctxt( BACKTRACK );
        bwbr = NO;
#ifdef  DEBUG
        fprintf(stderr, "ssbtrack: beginning bactrack on %s\n",
            (Ssaton->ssarray)[Ssmtext.mval] );
#endif

        while (( mc = ssbmatch()) != NUL )  {
gettc:      if (( tc = ssback()) == EOF )  goto  sfail;
#ifdef  DEBUG
            fputc( tc, stderr);
#endif
            Tcent = (Ssaton->ssctab) ? &(Ssaton->ssctab)[tc & SEVENBIT] : NULL;
            tcx = Tcent ? Tcent->cx : (uchar) tc;
            tcf = Tcent ? Tcent->cflags : CF_NORM;

            if ( ( SSMode( BSRCH ) ? tc : tcx) == WBC )  {
                if ( bwbr )  goto gettc;
                bwbr = YES;
                if ( mc != WBC )  {
sfail:              if ( SSMode( BSRCH ) )  {
                        ssctxt( STXTFAIL );
                        continue;
                    }
                    else  return( FAILURE );
                }
                else  continue;
            }
            else  {
                if ( bwbr )  sswbput();
                bwbr = NO;
                if ( SSMode( BMSG ) )  {
                    if ( tcx == NUL )  {
                        if ( tc == mc )  {
                            ssmcput( tc );
                            continue;
                        }
                        else  {
                            if ( tcf & CF_MSG )  ssmcput( tc );
                            goto  gettc;
                        }
                    }
                    else  {
                        if ( tcx == mc )  {
                            ssmcput( tc );
                            continue;
                        }
                        else  return( FAILURE );
                    }
                }
                else  {
                    if ( tc == mc )  continue;
                    else  {
                        ssctxt( STXTFAIL );
                        continue;
                    }
                }
            }
        }
        ssctxt( MSUCCESS );
        return( SUCCESS );
}


/*
 *      ssctxt() handles the context stacks but knows nothing about
 *      the contents.  ssearch() makes all decisions involving character
 *      types.
 *
 *      Ssaton->ssxtack points to the processed context ring stack
 *      (stack/queue).  The top element refers to the currently open
 *      context, i.e. the one being processed.  Xtcurr points to the
 *      top element.
 *
 *      Ssaton->ssptack points to the pending context stack.
 */

short
ssctxt( xtstate )
enum XTstate  xtstate;
{
    static TKhead   Xttkhead;           /* to preserve automaton state  */
    static Ctxt     Xtcurr;             /* pts to current top of context
                                        /*   stack                      */
    static Ctxt     Xtback;             /* scans context rstack during 
                                        /*   backtrack                  */
    static uchar   *xtfmptr;            /* ptr to beginning of search
                                        /*   text back match            */
    static long     xtfmct;             /* length of search text back
                                        /*   match                      */
    static uchar   *xtlast;             /* ptr to 1 past the last char  */
                                        /*   looked at                  */

    off_t ssbuftell();
    long            xtct;
    long            xtct1;
    off_t           xtofft;
    uchar          *xttxt;
    Ctxt            Xttemp1;
    Ctxt            Xttemp2;
    Ctxt            Xtesc;


    for (;;)  {
    
#ifdef  DEBUG
    fprintf(stderr, "ssctxt: state = %d, ssmode = %d\n",
            xtstate, Ssaton->ssmode);
#endif

        switch( xtstate )  {


        case  STARTUP:

            RSreset();
            if ( XTpop( Xtcurr )  ==  FAILURE )  {

        /* The real startup                                             */
/*
                assert( Ssaton->sscbuf  &&  !Ssaton->ssobuf );
                assert( Ssaton->sscbuf  &&  !Ssaton->ssobuf && 
                        Ssaton->ssbufr != ssonebuf );
*/
                RSremove( Xtcurr );
                Xtcurr->xttype = START;
                RSpush( Xtcurr );
                RSremove( Xtcurr );
                Xtcurr->xttype = BASE;
/*
 * mod by GRC 9/1/85 so that if ssearch() is called several times on the
 * same buffer, ssctxt() will not keep starting the search again at the
 * beginning of the buffer.
 */

                if( Ssaton->ssiptr ) {
                        Xtcurr->xtstart = Ssaton->ssiptr;
                        Xtcurr->xtcnt = Ssaton->ssict;
                } else {
                        Xtcurr->xtstart = Ssaton->sscbuf;
                        Xtcurr->xtcnt = Ssaton->sscct;
                }
/* the way it was 
                Xtcurr->xtstart = Ssaton->sscbuf;
                Xtcurr->xtcnt = Ssaton->sscct;
*/
            }
                                                /* Fall Through         */
        /* Restart                                                      */
                xtlast = ssitxt = ssiptr = Xtcurr->xtstart;
                ssict = Xtcurr->xtcnt;
                Ssaton->ssmode = Xtcurr->xttype;
                RSpush( Xtcurr );
                return( NUL );


        case  EOT:      /*  End of current text context                 */

            if ( SSMode( SRCH ) )  Ssaton->ssmode = BASE;

            if ( XTpop( Xtcurr ) == FAILURE )  {
#ifdef  DEBUG
                fprintf(stderr, "ssctxt(EOT): XTpop failed\n");
#endif
    /*  No pending context;  get new buffer                             */
                xttxt = Ssaton->ssobuf;
                if (( xtct = (*Ssaton->ssbufr)( &xttxt, &Ssaton->ssfd , SSBUFSIZ ))
                        == 0 )  return( EOF );
                Ssaton->ssobuf = Ssaton->sscbuf;
                Ssaton->sscbuf = xttxt;
                Ssaton->ssoofft = Ssaton->sscofft;
/* MOD -- use tell() to update overall file pos */
/* GRC 8/29/85 */
                Ssaton->sscofft = ssbuftell(Ssaton);
/*
                Ssaton->sscofft += Ssaton->sscct;
*/
                Ssaton->ssoct = Ssaton->sscct;
                Ssaton->sscct = xtct;
                RSremove( Xtcurr );
                Xtcurr->xttype = BASE;
                Xtcurr->xtstart = xttxt;
                Xtcurr->xtcnt = xtct;
            }
            else  {
#ifdef  DEBUG
            fprintf(stderr, "ssctxt(EOT): XTpop succeeded, type=%d, ct=%d\n",
                Xtcurr->xttype, Xtcurr->xtcnt);
#endif
    /*  There is a pending context; set mode from its type              */
                Ssaton->ssmode = Xtcurr->xttype;
            }

            ssitxt = ssiptr = Xtcurr->xtstart;
            ssict = Xtcurr->xtcnt;
            RSpush( Xtcurr );
            return( ssgetc() );


        case  ESCSEQ:           /* Process escape sequence              */

            Ssaton->ssmode = ESC;

            Xtcurr->xtcnt -= (ssict + 1);  /* truncate current ctxt     */
            RSremove( Xtcurr );
            Xtcurr->xttype = RMSG;
            Xtcurr->xtstart = ssiptr - 1;
            Xtcurr->xtcnt = ssict + 1;
            RSpush( Xtcurr );           /* push potential RMSG ctxt     */
            Xtesc = Xtcurr;
            ssitxt = ssiptr;

            if (( xttxt = (*Ssaton->ssescr)(sstc)) == NULL )  {
    /* Return of NULL ==> pushed RMSG context(s) is really metatext.
    /*   Truncate last context where escape processing left off.        */
                Xtcurr->xtcnt -= ssict;
                Xtcurr->xttype = META;
                if ( Xtesc != Xtcurr )     /* escape processing crossed */
                    Xtesc->xttype = META;  /*   a buffer boundary       */
    /* Set up processing of a new BASE context where escape processing
    /*   left off.                                                      */
                RSremove( Xtcurr );
                Xtcurr->xttype = BASE;
                Xtcurr->xtstart = ssiptr;
                Xtcurr->xtcnt = ssict;
                ssitxt = ssiptr;
                Ssaton->ssmode = BASE;
                RSpush( Xtcurr );
            }

            else  {
    /* There is a SRCH text string to be substituted for the RMSG context(s).
    /*   Truncate last RMSG context and push remainder of buffer on pending
    /*   stack.                                                         */
                Xtcurr->xtcnt -= ssict;
                RSremove( Xttemp1 );
                Xttemp1->xttype = BASE;
                Xttemp1->xtstart = xtlast = ssiptr;
                Xttemp1->xtcnt = ssict;
                assert( XTpush( Xttemp1 ) == SUCCESS );
#ifdef  DEBUG
                fprintf(stderr, "ssctxt(ESCSEQ): XTpush, type=%d, ct=%d\n",
                    Xttemp1->xttype, Xttemp1->xtcnt);
#endif
    /* Install SRCH replacement text as current context                 */
                RSremove( Xtcurr );
                Xtcurr->xttype = SRCH;
                Xtcurr->xtstart = ssitxt = ssiptr = xttxt;
                Xtcurr->xtcnt = ssict = strlen( xttxt );
                RSpush( Xtcurr );
                Ssaton->ssmode = SRCH;
            }

            return( NUL );


        case  BOT:      /* ssungetc() has backed up past the beginning
                        /*   of the current context.  Pop it and put
                        /*   it on the pending stack.                   */
            RSpop( Xttemp1 );
            assert( XTpush( Xttemp1 ) == SUCCESS );
            RSget( Xtcurr );
            if ( (Ssaton->ssmode == ESC)  &&  (Xtcurr->xttype != ESC) )  {
                XTpop( Xttemp1 );
                ssdie( "ssctxt: illegal unget during escape processing of \
\'%c\'\n", Xttemp1->xtstart[0]);
            }
            RSreset();
            ssitxt = Xtcurr->xtstart;
            ssiptr = ssitxt + Xtcurr->xtcnt;
            ssict = 0;
            Ssaton->ssmode = Xtcurr->xttype;
            return( ssungetc() );


        case SUBSTTXT:

    /* A token match has been recognized for the first element of a
    /*   subst[][2] pair.  Substitute the replacement string for the
    /*   matched portion of the current context.  No match checking is
    /*   done.  We assume subst message strings contain no null
    /*   translated characters.                                         */

            xttxt = (Ssaton->ssubst)[sstoken-1][0];
            xtct = (Ssaton->sstkleng)[sstoken-1];
            if ( Ssaton->ssmode == SRCH )
                ssdie( "ssctxt: illegal nested substitution involving \
\"%s\"\n", xttxt);
            RSpop( Xtcurr );
            xtct1 = xtct - (ssiptr - ssitxt);

            if ( xtct1 > 0 )  {
    /* Subst message text extends beyond the current context            */
                RSget( Xttemp1 );
                if ( Xttemp1->xtcnt < xtct1  ||  Xttemp1->xttype != MSG )
                    ssdie( "ssctxt: illegally recognized substitution \
string \"%s\"\n", xttxt);
                else if ( Xttemp1->xtcnt == xtct1 )
    /* Subst text extends just to beginning of previous context         */
                    Xttemp1->xttype = RMSG;
                else  {
    /* Subst text occupies end of previous context.  Close the portion
    /*   portion of the previous context that precedes the sust text    */
                    Xttemp1->xtcnt -= xtct1;
                    RSremove( Xttemp2 );
                    Xttemp2->xttype = RMSG;
                    Xttemp2->xtstart = Xttemp1->xtstart + Xttemp1->xtcnt;
                    Xttemp2->xtcnt = xtct1;
                    RSpush( Xttemp2 );
                }
            }
            else if ( xtct1 < 0 )  {
    /* Subst text contained in current context.  Close portion of
    /*   current context before subst text.                             */
                RSremove( Xttemp1 );
                Xttemp1->xttype = BASE;
                Xttemp1->xtstart = Xtcurr->xtstart;
                Xttemp1->xtcnt = -xtct1;
                RSpush( Xttemp1 );
                Xtcurr->xtstart -= xtct1;
                Xtcurr->xtcnt = xtct;
            }

    /* Put remainder of current buffer on pending stack                 */
            Xtcurr->xttype = BASE;
            Xtcurr->xtstart = xtlast = ssiptr;
            Xtcurr->xtcnt = ssict;
            assert( XTpush( Xtcurr ) == SUCCESS );
            RSremove( Xtcurr );
    /* Set subst SRCH string as current context                         */
            Xtcurr->xttype = SRCH;
            Xtcurr->xtstart = ssiptr = ssitxt = (Ssaton->ssubst)[sstoken-1][1];
            Xtcurr->xtcnt = ssict = (Ssaton->ssubleng)[sstoken-1];
            RSpush( Xtcurr );
            Ssaton->ssmode = SRCH;

            return( NUL );


        case  BACKTRACK:        /* Set up for backtrack to check match  */

            RSreset();
            Ssmtext.mval = sstoken - Ssaton->ssnsub - 1;
            Ssmtext.mleng = 0;
            Ssmtext.mstring = Mstring + MAXMATCH - 1;
            Ssmtext.mlist = Mlist + MAXLIST -1;

            ssmct  = (Ssaton->sstkleng)[sstoken - 1];
            ssmptr = (Ssaton->ssarray)[Ssmtext.mval] + ssmct;

            if ( SSMode( SRCH ) )  {
                sstofft = xtlast - Ssaton->sscbuf - 2 + Ssaton->sscofft;
                                

                Xttkhead = *(Ssaton->sstree);
                xtfmct = ssmct;
                xtfmptr = ssmptr;
                Ssaton->ssmode = BSRCH;
            }
            else  {
/* 
 * GRC Kludge 8/24/86
 *
 *              sstofft = ssiptr - Ssaton->sscbuf - 1 + Ssaton->sscofft;
 */
                sstofft = ssiptr - Ssaton->ssobuf - 1 + Ssaton->ssoofft;

/* end Kludge */

                Ssaton->ssmode = BMSG;
            }
            ssbtxt = ssitxt;
            sslnwbp = ssbptr = ssiptr;

            RSget( Xtback );
            return( NUL );


        case BACKEOT:   /* Beginning of context encountered during
                        /*   backtrack                                  */
            do  {
        /* Can be entered with context types SRCH or BASE/MSG; can      */
        /*   cycle with types SRCH, BASE/MSG, or RMSG.                  */
                if ( Xtback->xttype == RMSG )  {
                    Ssmtext.mstring -= Xtback->xtcnt;
                    strncpy( Ssmtext.mstring, Xtback->xtstart, Xtback->xtcnt );
        /* we assume RMSG text contains no word breaks                  */
                    sslnwbp = Xtback->xtstart;
                }
                if ( Xtback->xttype != SRCH )  {
                    (*--Ssmtext.mlist)[0] = Xtback->xtstart;
                    (*Ssmtext.mlist)[1] = Xtback->xtstart + Xtback->xtcnt - 1;
                }

                do  {
                    if ( RSget( Xtback ) == FAILURE )
                        ssdie( "ssctxt: overran context stack on match %s\n",
                            (Ssaton->ssarray)[sstoken - Ssaton->ssnsub - 1] );
                }  while  ( Xtback->xttype == META ) ;
            }  while ( Xtback->xttype == RMSG );

            if ( Xtback->xttype == START )  return( EOF );

            else if ( Xtback->xttype == SRCH )  {
                Ssaton->ssmode = BSRCH;
                Xttkhead = *(Ssaton->sstree);
                xtfmct = ssmct;
                xtfmptr = ssmptr;
            }

            else  Ssaton->ssmode = BMSG;

            ssbtxt = Xtback->xtstart;
            ssbptr = ssbtxt + Xtback->xtcnt;
#ifdef  DEBUG
            ssxtdump( Xtback );
#endif
            return( ssback() );


        case STXTFAIL:

    /* Context match on a SRCH context failed.  Substitute the RMSG
    /*   context(s) and back up the automaton.                          */

            if ( (RSget( Xtback ) == FAILURE)  ||  (Xtback->xttype != RMSG) )
                ssdie( "ssctxt: context stack failure on match %s\n",
                    (Ssaton->ssarray)[sstoken - Ssaton->ssnsub - 1] );
            Ssaton->ssmode = BMSG;
            *(Ssaton->sstree) = Xttkhead;
            ssmptr = xtfmptr;
            ssmct = xtfmct;
            ssbptr = Xtback->xtstart + Xtback->xtcnt;
            ssbtxt = Xtback->xtstart;

            return( NUL );
        

        case  MSUCCESS:         /* Match confirmed. Prepare the SSmtext
                                /*   return structure                   */

        /* Put the last context to bed and push the remainder on the
        /* pending stack.                                               */

            Xtcurr->xtcnt -= ssict;
            RSremove( Xttemp1 );
            Xttemp1->xttype = Xtcurr->xttype;
            Xttemp1->xtstart = ssiptr;
            Xttemp1->xtcnt = ssict;
            assert( XTpush( Xttemp1 ) == SUCCESS );

        /* Calculating where the last non-wordbreak character (lnwbc)
        /* was matched and adjusting mstring, mlist, and moffset,
        /* involves 3 cases.                                            */
        /* Was the lnwbc in the current context?                        */

            if ( sslnwbp >= Xtback->xtstart  &&
                   sslnwbp < Xtback->xtstart + Xtback->xtcnt )  {

        /* Yes.  Then, is that context MSG text?  If yes, mstring is up to
        /* date, and we only need to add one row to mlist.  moffset will
        /* be calculated later once for all the cases.                  */

                if ( Xtback->xttype == MSG )  {
                    (*--Ssmtext.mlist)[0] = sslnwbp;
                    (*Ssmtext.mlist)[1] = Xtback->xtstart + Xtback->xtcnt - 1;
                }

        /* Or is that context SRCH text?  Then add the replaced RMSG
        /* segments to mstring and mlist.                               */

                else  {
                    do  {
                        if ( RSget( Xtback ) == FAILURE )
                            ssdie( "ssctxt: stack overflow on match %s\n",
                                (Ssaton->ssarray)[sstoken-Ssaton->ssnsub-1]);
                        Ssmtext.mstring -= Xtback->xtcnt;
                        strncpy( Ssmtext.mstring, Xtback->xtstart,
                            Xtback->xtcnt );
                        (*--Ssmtext.mlist)[0] = Xtback->xtstart;
                        (*Ssmtext.mlist)[1] =
                            Xtback->xtstart + Xtback->xtcnt - 1;
                    }  while ( Xtback->xttype == RMSG );
                    sslnwbp = Xtback->xtstart;
                }
            }

        /* Now let's suppose that the lnwbc was not in the current context.
        /* Then mstring is up to date, and lnwbc was either in the
        /* immediately previous SRCH context (since we assume that
        /* there are no word breaks in RMESG text) or in a previous
        /* MSG context.  In either case we roll back the mlist, until
        /* we find a row in which the lnwbc position fits.  Adjust
        /* and calculate moffset.                                       */

            else  {
                for  (;;)  {
                    if ( sslnwbp >= (*Ssmtext.mlist)[0]  &&
                         sslnwbp <= (*Ssmtext.mlist)[1] )    break;
                    {
                    uchar  *cp;
                        for ((cp=(*Ssmtext.mlist)[0]); cp<=(*Ssmtext.mlist[1]);
                            cp++)  fputc( *cp, stderr);
                    }
                    if ( (*++Ssmtext.mlist)[0] == NULL )
                        ssdie( "ssctxt: no non-wordbreak characters on match \
\'%s\'\n", (Ssaton->ssarray)[sstoken - Ssaton->ssnsub - 1] );
                }
                (*Ssmtext.mlist)[0] = sslnwbp;
            }

        /* Calculate moffset and mleng for all cases                    */


            if ( sslnwbp >= Ssaton->sscbuf &&
                   sslnwbp < Ssaton->sscbuf + Ssaton->sscct )  {
if( Ssaton->sscofft )
                xtofft = Ssaton->sscofft;
else
	xtofft = Ssaton->ssoofft;

                xttxt = Ssaton->sscbuf;
/*
fprintf(stderr,"xtofft %ld from sscofft; xttxt, %ld from cbuf\n",xtofft,xttxt);
*/
            }
            else  {
if( Ssaton->ssoofft )
                xtofft = Ssaton->ssoofft;
else
	xtofft = Ssaton->sscofft;
                xttxt = Ssaton->ssobuf;
            }

            Ssmtext.moffset = xtofft + sslnwbp - xttxt;
            Ssmtext.mleng = sstofft - Ssmtext.moffset + 1;
            return( NUL );


        case  LONGMATCH:

            ssdie( "ssctxt: matched message text too long \n\t\"%s\"\n",
                Mstring );


        default:

            ssdie("ssctxt: illegal state = %d\n", xtstate);

        }
    }
}


/*VARARGS*/

ssdie( format )
char  *format;
{
/*
        fprintf(stderr, "%r", &format );
*/
        fprintf(stderr, "%s", format );
        exit( 1 );
}


#ifdef  DEBUG
ssxtdump( XT )
Ctxt  XT;
{
    short i;
    uchar  *cp;

        fprintf(stderr, "ssxtdump: type = %d\n", XT->xttype );
        fprintf(stderr, "ssxtdump: count = %d\n", XT->xtcnt );
        cp = XT->xtstart;
        fprintf(stderr, "ssxtdump: front = ");
        for ( i=0; i < (XT->xtcnt<10?XT->xtcnt:10); i++)
            fputc( *(cp + i), stderr);
        fputc( '\n', stderr );
        cp = XT->xtstart + XT->xtcnt;
        fprintf(stderr, "ssxtdump: rear = ");
        for ( i=1; i <= (XT->xtcnt<10?XT->xtcnt:10); i++)
            fputc( *(cp - i), stderr);
        fputc( '\n', stderr );
}
#endif

ssbufreset(Ssauto)
SSauto Ssauto;
{
            ssiptr = Ssauto->ssiptr;
            ssict = Ssauto->ssict;
}
