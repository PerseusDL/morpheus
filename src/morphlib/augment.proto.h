
/* augment.c */
int do_syllaug(gk_word *, int);
int do_tempaug(gk_word *, int);
int unaugment(char *, gk_string *[], gk_string *[], int, Dialect, int, int);
int unaugfromlemma(char *, char *);
int add_augment(gk_word *, MorphFlags *, int);
int needs_augment(gk_string *);
int needs_augment2(gk_word *, char *);
int simpleaugment(char *, bool);
int simpleredupit(char *, int, int);
int redupit2(gk_word *, int, int, int);
int un_redupl(char *, char *, int);
int add_double_augment(char *, MorphFlags *);
