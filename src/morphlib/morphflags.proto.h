
/* morphflags.c */
int add_morphflags(gk_string *, MorphFlags *);
int set_morphflags(gk_string *, MorphFlags *);
int set_gwmorphflags(gk_word *, MorphFlags *);
int zap_morphflags(gk_string *, MorphFlags *);
int has_morphflags(gk_string *, MorphFlags *);
int no_morphflags(gk_string *);
int add_morphflag(MorphFlags *, int);
int overlap_morphflags(MorphFlags *, MorphFlags *);
int has_morphflag(MorphFlags *, int);
int zap_morphflag(MorphFlags *, int);
int set_morphflag(MorphFlags *, int);
int no_morphflag(MorphFlags *);
int mflag_num_to_bits(int, int *, int *);
int mflag_bit_to_num(int, int);
int Dump_morphflag(MorphFlags *);
int is_pretty_morphflag(long);
int init_ugly_tab(void);
int is_prvb_morphflag(long);
int init_prvb_tab(void);
int xfer_prvbflags(MorphFlags *, MorphFlags *);
int MorphNames(MorphFlags *, char *, char *, int);
