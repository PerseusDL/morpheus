/*
 * Copyright Gregory Crane
 * April 1987
 */

/* flags for tlg_marker() */
#define NOPRINT         1
#define STRFLG          2
#define GETLAB          4

#define REGSIZ          0
#define BIG             1
#define REALBIG         2
#define SMALL           3
#define REALSMALL       4

#define EXPANDED        0
#define SUPERSCRIPT     1
#define SUBSCRIPT       2

#define ROMAN           0
#define BOLD            1
#define ITALIC          2



#define LOWER 1
#define UPPER 2

/*
#define DIG     'V' - 'A' + 1

#define alpha   'a' - 'a' + 1
#define beta    'z' - 'a' + 1
#define gamma   'g' - 'a' + 1
#define delta   'd' - 'a' + 1
#define epsilon 'e' - 'a' + 1
#define zeta    'z' - 'a' + 1
#define eta     'h' - 'a' + 1
#define theta   'q' - 'a' + 1
#define iota    'i' - 'a' + 1
#define kappa   'k' - 'a' + 1
#define lambda 'a' + 1
#define nu      'n' - 'a' + 1
#define xi      'c' - 'a' + 1
#define omicron 'o' - 'a' + 1
#define pi      'p' - 'a' + 1
#define rho     'r' - 'a' + 1
#define sigma   's' - 'a' + 1
#define tsigma  'v' - 'a' + 1
#define tau     't' - 'a' + 1
#define upsilon 'u' - 'a' + 1
#define phi     'f' - 'a' + 1
#define chi     'x' - 'a' + 1
#define psi     'y' - 'a' + 1
#define omega   'w' - 'a' + 1

#define ALPHA   'A' - 'A' + 1
#define BETA    'Z' - 'A' + 1
#define GAMMA   'G' - 'A' + 1
#define DELTA   'D' - 'A' + 1
#define EPSILON 'E' - 'A' + 1
#define ZETA    'Z' - 'A' + 1
#define ETA     'H' - 'A' + 1
#define THETA   'Q' - 'A' + 1
#define IOTA    'I' - 'A' + 1
#define KAPPA   'K' - 'A' + 1
#define LAMBDA  'L' - 'A' + 1
#define MU      'M' - 'A' + 1
#define NU      'N' - 'A' + 1
#define XI      'C' - 'A' + 1
#define OMICRON 'O' - 'A' + 1
#define PI      'P' - 'A' + 1
#define RHO     'R' - 'A' + 1
#define SIGMA   'S' - 'A' + 1
#define TSIGMA  'V' - 'A' + 1
#define TAU     'T' - 'A' + 1
#define UPSILON 'U' - 'A' + 1
#define PHI     'F' - 'A' + 1
#define CHI     'X' - 'A' + 1
#define PSI     'Y' - 'A' + 1
#define OMEGA   'W' - 'A' + 1
*/

/* no accents admissable on this char */
#define ANYACC  -1
/*
 * MASK to find any GREEK accent except underline dot: to see if
 * we need to print a space in front of an accented upper case
 * character
 */

/* Greek accents */
#define GACUTE  01
#define GGRAVE  02
#define GSMOOTH 04
#define GROUGH  010
#define GDIAER  020
#define GUDOT   040
#define GCIRC   0100
#define GISUB   0200    /* iota subscript */

#define ELLIPSIS        28
#define RDOUBBR         29
#define LDOUBBR         30
#define LHALFBR         31
#define RHALFBR         32
#define HIDOT           'f' - 'a' + 1

/* European Accents */
#define ACUTE   01
#define GRAVE   02
#define UMLAUT  04
#define LONG    010
/*
 * HACTIL- hacek/tilda
 * this flag stands for both hacek and '~'. this is on the theory
 * that no character (at least that i know of) can be accented with
 * a hacek and '~'. otherwise we are do not have enough flags 
 */
#define HAT     020
#define UDOT    040
#define HACTIL  0100
#define CIRCLE  0200

#define CCEDILA 0200
#define DSERB   0201
#define LPOLISH 0202

#define SHORTLAB 24

typedef struct {
        short num;
        short ch;
        char oddlabel[SHORTLAB];
        short flag;
}gkfield;


typedef struct {
        long Offset;
        long wrkend;
        long refflags;
        char rauth[SHORTLAB];
        char stitle[SHORTLAB];
        gkfield w_field;
        gkfield x_field;
        gkfield y_field;
        gkfield z_field;
        int refwknum;
        } reference;
