#define SHOW_ANAL	01
#define SHOW_LEMMA	02
#define SHOW_MISSES	04

#define BUFFER_ANALS	010
#define CHECK_PREVERB	020
#define KEEP_BETA		040

#define SHOW_FULL_INFO	0100
#define DBASEFORMAT	0200
#define DBASESHORT	(0400|DBASEFORMAT)

#define STRICT_CASE	01000
#define PARSE_FORMAT	02000
#define PERSEUS_FORMAT	04000
#define ENDING_INDEX	010000
#define IGNORE_ACCENTS	020000
#define LEXICON_OUTPUT	040000
#define GREEK		0		/* default language */
#define LATIN		0100000
#define LEMCOUNT	0200000
#define VERBS_ONLY	0400000
#define ITALIAN		01000000

typedef int PrntFlags;

#define prntflags_of( X ) (X)->gs_prntflags
#define add_prntflags( X , Flags ) prntflags_of(X) |= Flags
#define set_prntflags( X , Flags ) prntflags_of(X) = Flags
#define Should_check_preverb(X) (prntflags_of(X) & CHECK_PREVERB)

