
/* retrends.c */
gk_string *chckendings(char *, char *, char *, char *, Dialect, int *);
int CompatKeys(char *, char *, gk_string *);
int EndingOk(char *, gk_string *, gk_string *, int);
int WantGkEnd(gk_string *, gk_string *, bool, int);
int RightMorphflags(gk_string *, gk_string *);
int setwendstr(char *, char *);
int endstrcmp(char *, char *);
int noaccstrcmp(char *, char *);
int has_quantacc(char *);
int stripquantacc(char *);
