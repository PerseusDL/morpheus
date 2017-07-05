
/* latnom.c */
int dump_adv();
int set_lemma(char *);
int set_orth(int);
int sameend(char *, char *);
int set_orthalt(int );
int unique_lastc(char *, int, int);
int dump_adj(int, char *, char *, char *);
int dump_nom(int, char *, char *, char *);
int dump_ent(int, char *, char *, char *, char *);
int dump_form(char *);
int is_itype(unsigned char *, unsigned char *);
int dump_form2(int n);
int dump_adj1(int n);
int dump_form3(int n);
int trimstem(unsigned char *, int);
int is_prevborth(char *);
