/*
 * Copyright Gregory Crane
 * April 1987
 */

typedef struct {
    char    gkselauth[SHORTS+1];  /* name of author from which selection taken */
    int     gkselwknum; /* work number */
    long    gkselstart; /* offset at which selection starts */
    long    gkselend;   /* offset at which it ends */
    long    gkselcenter;/* offset of object at focus of selection */
    long    gkselcEnd;  /* end of object at focus of selection */
    long    gkselclen;  /* len of object at focus of selection */
    long    gksellen;   /* length of selection */
    int     gkselunits; /* units of selection -- words, lines, sentences */
    int     gkselnunits;/* number of units */
    char *  gkselbufp;  /* pointer to a buffer containing selection */
} GkSelection;
