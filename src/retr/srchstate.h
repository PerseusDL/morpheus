/* srchstate.h	2.1  9/26/87 */
/*
 * Copyright Gregory Crane
 * April 1987
 */

#include <defcons.h>


typedef struct {
        long wkend;
        long wkoff;
        int wknum;
        char wkname[12];
        long off_in_workfile;
        } shortw;

typedef struct {
        long recpoint;          /* pointer for this record */
        char sname[SHORTS+1];   /* short name of current author file */
                                /* e.g. "soph" */
        char fname[MAXWORD+1];  /* fuller name of current author file */
                                /* e.g. "Sophocles" */
	shortw *wtab;		/* pointer to work table for current author */
        char savefile[MAXWORD]; /* file for saving text */
        char recfile[MAXWORD];  /* file with tlg records in it used by rec_scanlist() */
        char logfile[MAXWORD];  /* a log of all entry points into show_rec()
                                        that have occured in current session */
        char curline[LONGS];    /* the current central line: e.g.
                                        if looking at a word, this is the
                                                line that contains that word;
                                        if looking at a passage, this is the
                                                line with which that passage
                                                begins. */
        long freq;              /* number of times a given string occurs in
                                        an author file */
        char Print_ref[MAXWORD+1];      /* the reference to a passage in output format */
        char Raw_ref[MAXWORD+1];        /* the reference to a passage in more structured format */
        char key[MAXWORD+1];    /* current target string */
        char key2[MAXWORD+1];   /* second target string for words in context*/
        char gotstr[MAXWORD + 1]; /* string matching target string */
        char gotstr2[MAXWORD + 1]; /* string matching second target string */
        int  device; /* current device */
        int  nitems;    /* number of "records" in a file */
        int  currec;    /* current record being consulted */
        int  curitem;   /* 
                         *      a single record can refer to many items: e.g.
                         *      it may point to N instances of string S
                         *      in author A 
                         */
        /*
         * various pointers to words:
         */

        long p2;        /* in an indexed search, this points into the index
                                kept in author.prec */
        long pnull;     /* common words are not indexed. this pointer is set
                                to indicate that no pointer for the current
                                string is available */
        long pword;     /* this is the offset in a file at which a word occurs*/
        long pw2;       /* in search for strings in context, points to second word */

        long pstart;    /* the start offset of a passage */
        long pend;      /* the end offset of a passage */

        char phrase1[40]; /* phrases to define beginning and end of a passage */
        char phrase2[40];

        long rflags;
        long l_len;
        long l_lno;
        long l_start;
        long filelen;   /* length of the current author file */
        int lsep;       /* separation allowed between words in context */
        int sepunits;   /* units of separation between words: lines,sentences,words */
        int authnum;
        long authend;   /* for files with more than one author: offset at which
                                current author ends */

        char endref[MAXREF]; /* reference at end of a passage */
        
        int noddfields; /* anyfields that do not have a place in this data 
                                structure should be stored as char strings
                                here */
        char **oddfields;

        int nworks;
        char title[MAXWORD+1];
        int recwknum;
        long recwkstart; /* offset at which current work begins */
        long recwkend;  /* offset at which current work ends */
        int text_height;
        int wind_height;
        long highlight_offs[3]; /* offsets to highlight */
        } srch_state ;


