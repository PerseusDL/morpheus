typedef long Morph_flags;

typedef struct {
	char	morph_key[MAXWORDSIZE];
	Morph_flags	morph_flags;
	void 	(*add_val)();
} Morph_args;

