#define MODULUS	10
#define KEYLEN 6
#define MAXTAG KEYLEN + 1

typedef struct {
	char *ebuf;
	char **eptr;
	int nelems;
} endind;

#define endbuffer_of( X ) (X->ebuf)
#define endeptr_of( X ) (X->eptr)
#define endlen_of(X) (X->nelems)

endind * init_endind();
