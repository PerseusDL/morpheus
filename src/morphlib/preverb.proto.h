
/* preverb.c */
bool checkprevb(char *, char *, bool *);
bool prvbcmp(char *, char *, bool *);
int getrest(char *, char *, char *, char *);
int rstprevb(char *, char *, gk_string *);
int First_K_aspirate(char *);
int shift_su_to_cu(char *);
int shift_eis_to_es(char *);
int shift_pros_to_poti(char *);
int shift_pros_to_proti(char *);
int shift_upo_to_upai(char *);
int shift_uper_to_upeir(char *);
int shift_para_to_parai(char *);
int shift_meta_to_peda(char *);
int shift_en_to_eni(char *);
int set_odd_prvb(MorphFlags *, char *);
