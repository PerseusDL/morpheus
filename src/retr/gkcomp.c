/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "gkcomp.h"
#include "srchstate.h"
static char * nextChar(char *s);
static char * nextDiacrit(char * s);

    char * nextChar();
    char * nextDiacrit();
    static char gk_tab[128];
    static setup = 0;

 gkcmpinit()
{
        set_gkorder(gk_tab,sizeof gk_tab);
        setup = 1;
}

 gk_strcmp(a,b)
  char * a;
  char * b;
{
        int n;

        if( ! setup )
                gkcmpinit();

        /*
         * if the alphabetic values of the two strings differs,
         * return the difference
         */
        if( (n=gk_lexcmp(a,b)) ) 
                return(n);

        /*
         * now check for case -- all upper case instances of same sequence
         * of alphabetic chars have a lower sort weight
         */
        if( (n=gk_casecheck(a,b)) )
                return(n);

        /*
         * now check for diacritics 
         */
        if( (n=gk_diacritcmp(a,b)) )
                return(n);
        return(0);
}

 gk_casecheck(a,b)
  char * a;
  char * b;
{
        int au, bu;

        if( (au=gk_isupper(a)) == (bu=gk_isupper(b)) ) {
                return(0);
        }
        return(au>bu?CASEGREATER:CASELESS);
}

/*
 * check to see if a beta string is upper case
 */
 gk_isupper(s)
  char * s;
{
        while(*s) {
                if( *s == '*' )
                        return(1);
                s++;
        }
        return(0);
}

 gk_lexcmp(pa, pb)
  register char *pa, *pb;
{
        char * a = pa;
        char * b = pb;

        for(;;) {
                a = nextChar(a);
                b = nextChar(b);

                if( !*a && !*b )
                        return(0);
                if( *a == *b || *a == WILDC ) {
                        a++; b++;
                        continue;
                }
                if( *a && ! *b )
                        return(LEXLONGER);
                if( *b && ! *a )
                        return(LEXSHORTER);
                return(gk_tab[ *a ] > gk_tab[ *b ]?LEXGREATER:LEXLESS);
        }
}

 gk_diacritcmp(pa, pb)
  register char *pa, *pb;
{
        char * a = pa;
        char * b = pb;

        for(;;) {
                a = nextDiacrit(a);
                b = nextDiacrit(b);
                if( !*a && !*b )
                        return(0);
                if( *a == *b ) {
                        a++; b++;
                        continue;
                }
                return(*a > *b ? ACCGREATER : ACCLESS );
        }
}

static char *
 nextChar(char *s)
{
        while(*s && *s != '\n' && !isalpha(*s) && *s != WILDC ) s++;
        return(s);
}

static char *
 nextDiacrit(char * s)
{
        while(*s && *s != '\n' && !DIACRITS(*s) ) s++;
        return(s);
}

    char gktoasc[]= {
/*      alpha */        'a',    'a' + 01,
/*      beta */         'b',    'a' + 02,
/*      gamma */        'g',    'a' + 03,
/*      delta */        'd',    'a' + 04,
/*      epsilon */      'e',    'a' + 05,
/*      zeta */         'z',    'a' + 06,
/*      eta */          'h',    'a' + 07,
/*      theta */        'q',    'a' + 010,
/*      iota */         'i',    'a' + 011,
/*      kappa */        'k',    'a' + 012,
/*      lambda */       'l',    'a' + 013,
/*      mu */           'm',    'a' + 014,
/*      nu */           'n',    'a' + 015,
/*      xi */           'c',    'a' + 016,
/*      omicron */      'o',    'a' + 017,
/*      pi */           'p',    'a' + 020,
/*      rho */          'r',    'a' + 021,
/*      sigma */        's',    'a' + 022,
/*      tau */          't',    'a' + 023,
/*      upsilon */      'u',    'a' + 024,
/*      phi */          'f',    'a' + 025,
/*      chi */          'x',    'a' + 026,
/*      psi */          'y',    'a' + 027,
/*      omega */        'w',    'a' + 030,
/*      this if for english words such as 
 *      "survive", that might creep
 *      into a word list */
                        'v',    'a',
                        'j',    'a',
};


 set_gkorder( s , len )
  register char * s;
  register len;
{
        int i;

/* set all bytes to a default */
        for(i=0;i<len && i < 256;i++)
                s[i] = i;

/* now set sort order for all alphabetic chars */
        for(i=0;i< sizeof gktoasc;) {
                s[ gktoasc[ i ] ] = gktoasc[ i+1 ] ;
                i += 2;
        }
}
