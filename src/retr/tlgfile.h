/*
 * Copyright Gregory Crane
 * April 1987
 */

#define MAXAUTHNAME 512
#define MAXDIRNAME 512
typedef struct {
        char    tlgsname[MAXAUTHNAME];
        int     tlgnworks;
        long    tlgfilelen;
        char    tlgauthdir[MAXDIRNAME];
        char    tlgbasename[MAXDIRNAME];
	long	tlgflags;
} tlgauthor;


