#define MODULUS	10
#define KEYLEN 8
#define MAXTAG KEYLEN + 1

typedef struct {
	char tagstring[MAXTAG];
	long tagoffset;
} endtags;

#define tagstring_of(X) (X)->tagstring
#define tagoffset_of(X) (X)->tagoffset

endtags * init_preind();
