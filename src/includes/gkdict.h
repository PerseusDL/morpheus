/*
#define WORDLIST "gkdict/gkdict"
#define INDECLIST "gkdict/indices/indecl"
#define IRREGLIST "gkdict/indices/irrverb"
#define STEMLIST "gkdict/indices/stindex"
*/
#define WORDLIST "hqdict/hqdict"
#define COMPHEADS "/tmp/nom.heads"
#define NOMLIST "/tmp/nommorph"
#define NOMINDEX "steminds/nomind"
#define VBLIST "/tmp/vbmorph"
#define VBINDEX "steminds/vbind"
#define INDECLIST "hqdict/indices/indecl"
#define IRREGLIST "hqdict/indices/irrverb"
#define STEMLIST "hqdict/indices/stindex"

#define LEMMTAG		":le:"

typedef struct {
	int clen;
	char **citem;
	int curindex;
} Stemcache;
