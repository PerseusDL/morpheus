
/* indkeys.c */
int index_list(char *, char *, int);
#ifdef DECALPHA
int prockeyline(char *, int, int, FILE *);
#else
int prockeyline(char *, int, long, FILE *);
#endif
