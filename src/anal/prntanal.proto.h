
/* prntanal.c */
int PrntAnalyses(gk_word *, PrntFlags, FILE *);
char *anal_buf(void);
int PrntOneAnalysis(gk_analysis *, PrntFlags, FILE *);
int near_miss(gk_string *, char *, int);
int odd_morpheme(gk_analysis *, gk_string *, char *, char *, int);
int dump_all_anals(gk_word *, PrntFlags, FILE *);
int SortAnals(gk_analysis *, int);
int DumpLemmaInfo(gk_word *, PrntFlags , FILE *);
int CompAnals(const void*, const void*);
int DumpOneAnalysis(gk_word *, PrntFlags, gk_analysis *, FILE *, int);
int DumpEndingIndex(gk_word *, PrntFlags, gk_analysis *, FILE *, int);
int DumpPerseusAnalysis(gk_word *, PrntFlags, gk_analysis *, FILE *, int);
int DumpGstr(char *, gk_string *, FILE *, int);
int DumpDbGkString(gk_string *, FILE *);
