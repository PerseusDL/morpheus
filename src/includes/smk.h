#define SMK_ALPHA(X) (X=='a'||X=='A'||(X>=0213&&X<=0225))
#define SMK_AISUB(X) (X==046||(X>=0226&&X<=0240))
#define SMK_EPSILON(X) (X=='e'||X=='E'||(X>=0241&&X<=0250))
#define SMK_ETA(X) (X=='h'||X=='H'||(X>=0256&&X<=0270))
#define SMK_EISUB(X) (X==0372||(X>=0271&&X<=0303))
#define SMK_IOTA(X) (X=='i'||X=='I'||(X>=0333&&X<=0345))
#define SMK_OMICRON(X) (X=='o'||X=='O'||(X>=0361&&X<=0371))
#define SMK_UPSILON(X) (X=='u'||X=='U'||(X>=0346&&X<=0360))
#define SMK_WMEGA(X) (X=='v'||X=='V'||(X>=0305&&X<=0317))
#define SMK_WISUB(X) (X==0304 || (X>=0320&&X<=0332)) 
#define SMK_IDIAER(X)  (X==0363 || X==0375 || X==0376)
#define SMK_UDIAER(X)  (X==043 || X==0100 || X==0347)
#define SMK_DIAER(X) (SMK_UDIAER(X) || SMK_IDAER(X))

#define SMK_VOWEL(X) (SMK_ALPHA(X)  || \
	SMK_AISUB(X) || \
	SMK_EPSILON(X) || \
	SMK_ETA(X) || \
	SMK_EISUB(X) || \
	SMK_IOTA(X) || \
	SMK_OMICRON(X) || \
	SMK_UPSILON(X) || \
	SMK_WMEGA(X) || \
	SMK_WISUB(X) || \
	SMK_IDIAER(X) || \
	SMK_UDIAER(X) )

#define SYNIZESIS 'X'
#define SMARTA_LONGMARK '^'
#define SMARTA_SHORTMARK 0255
#define SMK_LONGMARK '*'
#define SMK_SHORTMARK 0255
#define SMK_DAGGER '~'
