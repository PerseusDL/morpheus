
/* morphkeys.c */
int ScanAsciiKeys(char *, gk_word *, gk_string *, gk_string *);
char *NextEndTable(int *, Stemtype);
/*
char *NameOfDerivtype(Derivtype);
char *NameOfStemtype(Stemtype);
char *NameOfDomain(Stemtype);
char *NameOfPerson(word_form);
char *NameOfNumber(word_form);
char *NameOfTense(word_form);
char *NameOfMood(word_form);
char *NameOfVoice(word_form);
char *NameOfDialect(Dialect);
*/
int DomainNames(char *, char *, char *);
int DialectNames(Dialect, char *, char *);
int GeogRegionNames(GeogRegion, char *, char *);
char *NameOfGender(word_form);
char *NameOfCase(word_form);
char *NameOfDegree(word_form);
char *NameOfMorphFlags(long);
int AddMorphKey(gk_string *, char *);
Stemtype GetStemNum(char *);
int init_stems(void);
int has_octal(char *);
int init_keys(void);
Stemtype GetStemClass(char *);
Stemtype GetIsProse(char *);
