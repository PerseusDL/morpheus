/*
 * Copyright Gregory Crane
 * April 1987
 */


/* constants */
#define TXT_YTOP        1
#define TXT_XTOP        1
#define TXT_HEIGHT      19              /* maximum size of window */
#define TXT_WIDTH       80


#define W_TEXT  0       /* text */
#define W_COMM  1       /* comment lines at the bottom of the text */
#define W_DELIM 2       /* line between text and comment */
#define W_STAT  3       /* status lines */

#define W_ARGLEN 80
#define W_LENGTH        80
#define W_HEIGHT        24


#define WAUTHST  W_STAT , 1 , 2         /* author field */
#define WCURAUTH W_STAT , 41 , 2        /* current author */
#define WAUTHLN 40
#define WQPMPTN W_STAT , 41 , 2         /* "Total: N" */
#define WPMPRLN 11
#define WNUMLEN 4
#define WQUERST  W_STAT ,  52 , 2       /* string requested */
#define WFILE W_STAT , 1 , 2            /* name of file */
#define WQUERLN 29
#define WNWORDS W_STAT , 1 , 3          /* current word */
#define WWRDLEN 40                      
#define WCURPAS W_STAT , 41 , 3         /* number of current passage */
#define WPASPMT W_STAT , 45 , 3         /* "of " */
#define WTOTPAS W_STAT , 48 , 3         /* total number of passages for curw */
#define WTAGST  W_STAT , 52 , 3         /* tag for current passage */
#define WTAGLN  29
#define WCURLST W_STAT , 1 , 4          /* current line with word */
#define WLINLEN 80
#define WCOMLST W_STAT , 1 , 5          /* start of command line */

#define NOSCROLL 0
#define SCROLL 1

#define STAT_HEIGHT 5
#define PROMPT( X ) w_lclear(WCOMLST); printf( X )
#define BROWSEPROMPT "Browsing TLG Data Base"
