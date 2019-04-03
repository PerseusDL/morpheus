
/* combconj.c */
int combine_conj(FILE *, char *, char *, char *, char *, char *, char *);
int DoConjStem(FILE *, char *, gk_string *, char *,Stemtype, char *, char *, char *);
Stemtype ConjGkstr(gk_string *, char *, char *, char *, char *, char *);
int CheckConjPpart(FILE *, char *, gk_string *, gk_string *, char *, char *, char *);
int add_oddstuff(char *);
int DataBaseFormat(char *, gk_string *, char *, char *, char *);
int MatchSuff(char *, char *);
int conjoinX(gk_string *, char *, char *);
