
/* derivio.c */
int checkforderiv(char *stemstr, char *stemkeys);
int checkforredupderiv(char *stemstr, char *stemkeys);
int checkaugredup(char *stemstr, char *stemkeys);
int checkcomderivs(char *derivs, char *defstem, char *suffix, char *lemmkeys, char *nkeys, char *had_redupl, char *redupstem);
int checkcomderiv(char *derivstr, char *defstem, char *suffix, char *lkeys, char *rkeys, char *had_redupl, char *redupstem);
int checkmultredups(char *asuffkeys, char *dstem, char *dstemkeys, char *suffix, char *lemma, char *lkeys, char *rkeys, char *had_redupl, int markedstem);
int checkcomderiv2(char *asuffkeys, char *dstem, char *dstemkeys, char *suffix, char *lemma, char *lkeys, char *rkeys, char *had_redupl, int markedstem);
int DstemTakesDsuff(char *dsuffkeys, char *dstemkeys, gk_string *gstr, char *defstem, char *derivstr);
int need_rei_alpha(char *dsuffkeys);
int stemstr_in_cache(char *s, char *stemkeys);
int add_deriv_cache(char *s, char *keys);
int ends_in_vowel(char *s);
