
/* genwd.c */
int GenDictEntry(gk_word *, char *);
int GenNxtWord(FILE *, int, FILE *);
gk_word * GenStemForms(gk_word *, char *, int);
gk_word * GenIrregForm(gk_word *, char *, int);
int NextDictLine(FILE *, char *, char *, char *);
int AddWdEndings(gk_word *, gk_string *, gk_word *, int);
int BuildAWord(gk_word *, gk_string *, gk_word *);
int BuildANoun(gk_word *, gk_string *, gk_word *);
int BuildAVerb(gk_word *, gk_string *, gk_word *);
int MonoSyllVb(gk_word *, word_form, char *);
