/*  ssearch.h 1.5 8/25/85  */

#include  "usual.h"
#if MACINTOSH
#include  "godzilla_1:lightspeed:LS2.Libraries:#include files:unix #Includes:types.h"
#else
#include "sys/types.h"
#endif
#include  "token.h"

typedef struct  {
                uchar  cx;
                uchar  cflags;
                }  Centry;

typedef struct  {
                short  mval;
                off_t  moffset;
                short  mleng;
                uchar *mstring;
                uchar *(* mlist)[2];
                }  SSmtext, *SSmatch;

typedef struct  {
                uchar    xttype;
                uchar   *xtstart;
                long     xtcnt;
                }  Context, *Ctxt;

typedef struct  {
                uchar   **ssarray;
                short    ssnsub;
                uchar   *(* ssubst)[2];
                short   *ssubleng;
                short   *sstkleng;
                uchar   *(* ssescr)();
                long     (* ssbufr)();
                Centry  *ssctab;
                TKtree   sstree;
                Rstack  *ssxtack;
                Stack   *ssptack;
                Context *ssxthd;
                int      ssfd;
                uchar   *sscbuf;
                uchar   *ssobuf;
                long     sscct;
                long     ssoct;
/*
 * these added by GRC 9/1/85 so that an automaton can save its position in
 * a buffer
 */
                uchar   *ssiptr;
                int      ssict;
/* end of addition */
                off_t    sscofft;
                off_t    ssoofft;
                uchar    sswbr;
                uchar    ssmode;
                uchar    ssmind[128];
                uchar    sssind[128];
                }  SSmach, *SSauto;

/*      Arguments       */

#define  NEWFILE   -1
#define  FREEBUF   -2

/*      Constants       */

#define  SEVENBIT  0177
#define  WBC       ' '

/*      Parameters      */

#define  SSBUFSIZ  2048
#define  FDBASE    01000

/*      Flags           */

#define  CF_NORM  (uchar) '\00'
#define  CF_ESC   (uchar) '\01' /* escape sequence leader               */
#define  CF_MSG   (uchar) '\02' /* YES => message text; NO => metatext  */

/*      Macros
 *
 *              Note that ssict gives the number of characters remaining in
 *      the current context and ssiptr points to the next char to be returned
 *      by ssgetc() or the character just "backed up over" and returned by
 *      ssungetc().
 */

/* 
 * mod by GRC 9/1/85
#define  ssgetc()       ( ssict-- ? *(ssiptr++) : ssctxt(EOT))
 * if you were only looking at one block of text and the end of that
 * block of text cut off an escape sequence, then you would crash.
 * ssgetc() in betaesc() would see the end of the buffer when ssict hit
 * zero, but would not return anything to indicate the end of a block.
 * ssgetc() would be called by the main loop with ssict == -1 and would
 * blithely keep reading forever
 */
#define  ssgetc()       ( ssict-- > 0 ? *(ssiptr++) : ssctxt(EOT))
#define  ssungetc()     ( (ssiptr == ssitxt) ? \
                            ssctxt(BOT) : ( ++ssict, *(--ssiptr)) )
#define JustOneBuf( SSAUTO ) ( SSAUTO->ssbufr == ssonebuf )

/*      ssctxt states                                                   */

static enum  XTstate    {
                        STARTUP,
                        EOT,
                        ESCSEQ,
                        BOT,
                        SUBSTTXT,
                        BACKTRACK,
                        BACKEOT,
                        STXTFAIL,
                        MSUCCESS,
                        LONGMATCH
                        };

/*      Type declarations       */

extern uchar   *ssitxt;         /* ptr to head of current text segment  */
extern uchar   *ssiptr;         /* ssgetc buffer ptr                    */
extern long     ssict;          /* ssgetc buffer counter                */

SSauto   ssinit();
SSauto   init_words();
SSmatch  ssearch();
short    ssctxt();
long     ssbuffer();
long     ssonebuf();
off_t    ssbuftell();
