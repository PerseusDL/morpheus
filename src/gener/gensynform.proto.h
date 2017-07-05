
/* gensynform.c */
int GenSynForms(FILE *, FILE *);
int paradigm_keys(char *);
int is_pass_stem(Stemtype);
int is_mp_stem(Stemtype);
int PrntSynForms(gk_word *, gk_word *, FILE *);
int zap_hyph(register char *);
int zap_rootmarker(register char *);
int proc_beta(char *, FILE *, int);
int zap_tabs(char *);
int is_exception(char *, char *);
