
/* xderivio.c */
int checkforderiv(char *stemstr, char *stemkeys);
int checkforredupderiv(char *stemstr, char *stemkeys);
int checkaugredup(char *stemstr, char *stemkeys);
int checkforderiv2(char *stemstr, char *stemkeys, int had_redupl);
int checkcomderivs(char *derivs, char *suffix, char *lemmkeys, char *nkeys, int had_redupl);
int checkcomderiv(char *derivstr, char *suffix, char *lkeys, char *rkeys, int had_redupl);
