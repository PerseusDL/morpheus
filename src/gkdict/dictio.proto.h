
/* dictio.c */
endtags *init_dict(char *fname, int *ntags);
int chckirrverb(char *irregstr, char *lemmas);
int chckindecl(char *indeclstr, char *lemmas);
int chckderiv(char *derivstr, char *derivkeys);
int chckstem(char *stemstr, char *stemkeys, int is_nom);
int init_scache(void);
int is_instemcache(char *tag, int taglen, char *stemkeys);
int add_stemcache(Stemcache *cache, char *stem, char *keys);
int prntlemmentry(char *lemma, char *preverb, FILE *f);
FILE *getlemmstart(char *lemma, char *lemmfile, long *lemmoff);
int lemma_exists(char *lemma);
