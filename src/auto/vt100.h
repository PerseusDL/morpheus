
/*
 * this is a list of Ascii-Roman type chars, for terminal this list
 * is the same for Ascii-Italic and Ascii-Bold, but on the typesetter
 * the accents for Ascii-Italic are different--hence each font has the
 * different tables
 */
#define num( X ) ( X - 'a' + 1 )

comb ** vt100aico;
comb ** vt100abco;

static fchanges vt100fnts = {
	"\033[m",		/* go into roman */
	"\033[4m",		/* go into "italic" (underline) */
	"\033[7m",		/* turn on bolding */
	"\033[m",		/* turn off bolding */
	"\033[0;1m",		/* go into greek */
	"\033[7m",		/* go into reverse video */
	};
	
static comb  vt100arco[] = {
/* ' ' with accents */
	ACUTE,	LOWER,	C_BLANK ,	"\016.\b'\017",
	GRAVE,	LOWER,	C_BLANK ,	"\016.\b`\017",
	UMLAUT,	LOWER, 	C_BLANK ,	"\016.\b!\017",	
	LONG,	LOWER, 	C_BLANK ,	"\016.\b,\017",	
	HAT,	LOWER,	C_BLANK ,	"\016.\b>\017",
	UDOT,	LOWER, 	C_BLANK ,	"\016.\b.\017",
	CIRCLE,	LOWER,	C_BLANK ,	"\016.\bt\017",
	HACTIL,	LOWER,	C_BLANK ,	"\016.\b=\017",
/* lower case 'a' with accents */
	ACUTE,	LOWER,	num( 'a' ),	"\016\033Q\7\033R\b'\017",
	GRAVE,	LOWER,	num( 'a' ),	"\016\033Q\7\033R\b`\017",
	UMLAUT,	LOWER, 	num( 'a' ),	"\016\033Q\7\033R\b!\017",	
	LONG,	LOWER, 	num( 'a' ),	"\016\033Q\7\033R\b,\017",	
	HAT,	LOWER,	num( 'a' ),	"\016\033Q\7\033R\b>\017",
	UDOT,	LOWER, 	num( 'a' ),	"\016\033Q\7\033R\b.\017",
	CIRCLE,	LOWER,	num( 'a' ),	"\016\033Q\7\033R\bt\017",
/* 'A' with accents */
	ACUTE,	UPPER,	num( 'a' ),	"\016A\b'\017",	
	GRAVE,	UPPER,	num( 'a' ),	"\016A\b`\017",
	UMLAUT,	UPPER, 	num( 'a' ),	"\016A\b!\017",	
	LONG,	UPPER, 	num( 'a' ),	"\016A\b,\017",	
	HAT,	UPPER,	num( 'a' ),	"\016A\b>\017",
	UDOT,	UPPER, 	num( 'a' ),	"\016A\b.\017",
	CIRCLE,	UPPER,	num( 'a' ),	"\016A\bt\017",
/* 'e' with accents */
	ACUTE,	LOWER,	num( 'e' ),	"\016e\b'\017",
	GRAVE,	LOWER,	num( 'e' ),	"\016e\b`\017",
	UMLAUT,	LOWER, 	num( 'e' ),	"\016e\b!\017",	
	LONG,	LOWER, 	num( 'e' ),	"\016e\b,\017",	
	HAT,	LOWER,	num( 'e' ),	"\016e\b>\017",
	UDOT,	LOWER, 	num( 'e' ),	"\016e\b.\017",
	CIRCLE,	LOWER,	num( 'e' ),	"\016e\bt\017",
/* 'E' with accents */
	ACUTE,	UPPER,	num( 'e' ),	"\016E\b'\017",	
	GRAVE,	UPPER,	num( 'e' ),	"\016E\b`\017",
	UMLAUT,	UPPER, 	num( 'e' ),	"\016E\b!\017",	
	LONG,	UPPER, 	num( 'e' ),	"\016E\b,\017",	
	HAT,	UPPER,	num( 'e' ),	"\016E\b>\017",
	UDOT,	UPPER, 	num( 'e' ),	"\016E\b.\017",
	CIRCLE,	UPPER,	num( 'e' ),	"\016E\bt\017",
/* 'i' with accents */
	ACUTE,	LOWER,	num( 'i' ),	"\016\033Q\034\033R\b'\017",
	GRAVE,	LOWER,	num( 'i' ),	"\016\033Q\034\033R\b`\017",
	UMLAUT,	LOWER, 	num( 'i' ),	"\016\033Q\034\033R\b!\017",	
	LONG,	LOWER, 	num( 'i' ),	"\016\033Q\034\033R\b,\017",	
	HAT,	LOWER,	num( 'i' ),	"\016\033Q\034\033R\b>\017",
	UDOT,	LOWER, 	num( 'i' ),	"\016\033Q\033\033R\b.\017",
	CIRCLE,	LOWER,	num( 'i' ),	"\016\033Q\034\033R\bt\017",
/* 'I' with accents */
	ACUTE,	UPPER,	num( 'i' ),	"\016I\b'\017",	
	GRAVE,	UPPER,	num( 'i' ),	"\016I\b`\017",
	UMLAUT,	UPPER, 	num( 'i' ),	"\016I\b!\017",	
	LONG,	UPPER, 	num( 'i' ),	"\016I\b,\017",	
	HAT,	UPPER,	num( 'i' ),	"\016I\b>\017",
	UDOT,	UPPER, 	num( 'i' ),	"\016I\b.\017",
	CIRCLE,	UPPER,	num( 'i' ),	"\016I\bt\017",
/* 'o' with accents */
	ACUTE,	LOWER,	num( 'o' ),	"\016o\b'\017",	
	GRAVE,	LOWER,	num( 'o' ),	"\016o\b`\017",
	UMLAUT,	LOWER, 	num( 'o' ),	"\016o\b!\017",	
	LONG,	LOWER, 	num( 'o' ),	"\016o\b,\017",	
	HAT,	LOWER,	num( 'o' ),	"\016o\b>\017",
	UDOT,	LOWER, 	num( 'o' ),	"\016o\b.\017",
	CIRCLE,	LOWER,	num( 'o' ),	"\016o\bt\017",
/* 'O' with accents */
	ACUTE,	UPPER,	num( 'o' ),	"\016O\b'\017",	
	GRAVE,	UPPER,	num( 'o' ),	"\016O\b`\017",
	UMLAUT,	UPPER, 	num( 'o' ),	"\016O\b!\017",	
	LONG,	UPPER, 	num( 'o' ),	"\016O\b,\017",	
	HAT,	UPPER,	num( 'o' ),	"\016O\b>\017",
	UDOT,	UPPER, 	num( 'o' ),	"\016O\b.\017",
	CIRCLE,	UPPER,	num( 'o' ),	"\016O\bt\017",
/* 'u' with accents */
	ACUTE,	LOWER,	num( 'u' ),	"\016\033Q\010\033R\b'\017",
	GRAVE,	LOWER,	num( 'u' ),	"\016\033Q\010\033R\b`\017",
	UMLAUT,	LOWER, 	num( 'u' ),	"\016\033Q\010\033R\b!\017",	
	LONG,	LOWER, 	num( 'u' ),	"\016\033Q\010\033R\b,\017",	
	HAT,	LOWER,	num( 'u' ),	"\016\033Q\010\033R\b>\017",
	UDOT,	LOWER, 	num( 'u' ),	"\016\033Q\010\033R\b.\017",
	CIRCLE,	LOWER,	num( 'u' ),	"\016\033Q\010\033R\bt\017",
/* 'U' with accents */
	ACUTE,	UPPER,	num( 'u' ),	"\016\033Q\020\033R\b'\017",
	GRAVE,	UPPER,	num( 'u' ),	"\016\033Q\020\033R\b`\017",
	UMLAUT,	UPPER, 	num( 'u' ),	"\016\033Q\020\033R\b!\017",	
	LONG,	UPPER, 	num( 'u' ),	"\016\033Q\020\033R\b,\017",	
	HAT,	UPPER,	num( 'u' ),	"\016\033Q\020\033R\b>\017",
	UDOT,	UPPER, 	num( 'u' ),	"\016\033Q\020\033R\b.\017",
	CIRCLE,	UPPER,	num( 'u' ),	"\016\033Q\020\033R\bt\017",
/* 'c' */
	ACUTE, 	LOWER,	num( 'c' ),	"\016j\b'\017",
	GRAVE, 	LOWER,	num( 'c' ),	"\016j\b`\017",
	HACTIL,	LOWER,  num( 'c' ),	"\016j\b=\017",
	UDOT,	LOWER,	num( 'c' ),	"\016j\b.\017",
/* c cedila */
	LONG,	LOWER,  num( 'c' ),	"\016.\bL\017",
/* 'C' */
	ACUTE, 	UPPER,	num( 'c' ),	"\016J\b'\017",
	GRAVE, 	UPPER,	num( 'c' ),	"\016J\b`\017",
	HACTIL,	UPPER,	num( 'c' ),	"\016J\b=\017",
	UDOT,	UPPER,	num( 'c' ),	"\016J\b.\017",
	ACUTE,	UPPER,	num( 'c' ),	"\016\\\017",
	LONG,	UPPER,  num( 'c' ),	"\016J\bv\017",
/* 'n' */
	HACTIL,	LOWER,	num( 'n' ),	"\016*\b~\017",
/* 'N' */
	HACTIL, LOWER,	num( 'n' ),	"\016N\b~\017",
/* 's' */
	HACTIL,	LOWER,	num( 's' ),	"\016\033Q\016\033R\b=\017",
	UDOT,	LOWER,	num( 's' ),	"\016\033Q\016\033R\b.\017",
/* 'S' */
/* no 'S' on concept prom yet */
	HACTIL,	UPPER,	num( 's' ),	"\016S\b=\017",
	UDOT,	UPPER,	num( 's' ),	"\016S\b.\017",
/* 't' */
	UDOT,	LOWER,	num( 't' ),	"\016\033Q\015\033R\b.\017",
/* 'T' */
	UDOT,	UPPER,	num( 't' ),	"\016\033QT\033R\b.\017",

/* special characters, not treated as accented */
/* polish 'l' */
	ANYACC,	LOWER,	LPOLISH,	"\016\033Q\036\033R\017",
	ANYACC,	UPPER,	LPOLISH,	"\016`\017",
/* serbian 'd' and 'D' (has horizontal line thru it ) */
	ANYACC,	LOWER,	DSERB,		"\016\033Q\035\033R\017",
	ANYACC,	UPPER,	DSERB,		"\016\\\017",	
/* 'c' and 'C' cedila */
	ANYACC, LOWER, CCEDILA,		"\016.\bL\017",
	ANYACC, UPPER, CCEDILA,		"\016J\bv\017",
	};



/* output table for vt100 terminal */
static comb vt100gkco[] = {
	GSMOOTH|GACUTE, LOWER, alpha,	"&",
	GSMOOTH|GGRAVE, LOWER, alpha,	"(",
	GSMOOTH|GCIRC, LOWER, alpha,	"*",
	GROUGH|GACUTE, LOWER, alpha,	"'",
	GROUGH|GGRAVE, LOWER, alpha,	")",
	GROUGH|GCIRC, LOWER, alpha,	"+",
	GACUTE, LOWER, alpha,	"!",
	GGRAVE, LOWER, alpha,	"\"",
	GCIRC, LOWER, alpha,	"#",
	GSMOOTH, LOWER, alpha,	"$",
	GROUGH, LOWER, alpha,	"%",
	GSMOOTH|GACUTE, LOWER, epsilon,	"0",
	GSMOOTH|GGRAVE, LOWER, epsilon,	"2",
	GROUGH|GACUTE, LOWER, epsilon,	"1",
	GROUGH|GGRAVE, LOWER, epsilon,	"3",
	GACUTE, LOWER, epsilon,	",",
	GGRAVE, LOWER, epsilon,	"-",
	GSMOOTH, LOWER, epsilon,	".",
	GROUGH, LOWER, epsilon,	"/",
	GSMOOTH|GACUTE, LOWER, eta,	"q",
	GSMOOTH|GGRAVE, LOWER, eta,	"s",
	GSMOOTH|GCIRC, LOWER, eta,	"u",
	GROUGH|GACUTE, LOWER, eta,	"r",
	GROUGH|GGRAVE, LOWER, eta,	"t",
	GROUGH|GCIRC, LOWER, eta,	"v",
	GACUTE, LOWER, eta,	"l",
	GGRAVE, LOWER, eta,	"m",
	GCIRC, LOWER, eta,	"n",
	GSMOOTH, LOWER, eta,	"o",
	GROUGH, LOWER, eta,	"p",
	GSMOOTH|GACUTE, LOWER, iota,	"9",
	GSMOOTH|GGRAVE, LOWER, iota,	";",
	GSMOOTH|GCIRC, LOWER, iota,	"=",
	GROUGH|GACUTE, LOWER, iota,	":",
	GROUGH|GGRAVE, LOWER, iota,	"<",
	GROUGH|GCIRC, LOWER, iota,	">",
	GACUTE, LOWER, iota,	"4",
	GGRAVE, LOWER, iota,	"5",
	GCIRC, LOWER, iota,	"6",
	GSMOOTH, LOWER, iota,	"7",
	GROUGH, LOWER, iota,	"8",
	GSMOOTH|GACUTE, LOWER, omicron,	"|",
	GSMOOTH|GGRAVE, LOWER, omicron,	"y",
	GROUGH|GACUTE, LOWER, omicron,	"g",
	GROUGH|GGRAVE, LOWER, omicron,	"z",
	GACUTE, LOWER, omicron,	"}",
	GGRAVE, LOWER, omicron,	"~",
	GSMOOTH, LOWER, omicron,	"f",
	GROUGH, LOWER, omicron,	"}",
	GSMOOTH|GACUTE, LOWER, upsilon,	"d",
	GSMOOTH|GGRAVE, LOWER, upsilon,	"z",
	GSMOOTH|GCIRC, LOWER, upsilon,	"j",
	GROUGH|GACUTE, LOWER, upsilon,	"e",
	GROUGH|GGRAVE, LOWER, upsilon,	"{",
	GROUGH|GCIRC, LOWER, upsilon,	"k",
	GACUTE, LOWER, upsilon,	"{",
	GGRAVE, LOWER, upsilon,	"`",
	GCIRC, LOWER, upsilon,	"a",
	GSMOOTH, LOWER, upsilon,	"b",
	GROUGH, LOWER, upsilon,	"c",
	GSMOOTH|GACUTE, LOWER, omega,	"\033[0mg\033[1m",
	GSMOOTH|GGRAVE, LOWER, omega,	"\033[0mz\033[1m",
	GSMOOTH|GCIRC, LOWER, omega,	"\033[0m`\033[1m",
	GROUGH|GACUTE, LOWER, omega,	"\033[0my\033[1m",
	GROUGH|GGRAVE, LOWER, omega,	"\033[0m{\033[1m",
	GROUGH|GCIRC, LOWER, omega,	"\033[0ma\033[1m",
	GACUTE, LOWER, omega,	"w",
	GGRAVE, LOWER, omega,	"x",
	GCIRC, LOWER, omega,	"\033[0mf\033[1m",
	GSMOOTH, LOWER, omega,	"\033[0m}\033[1m",
	GROUGH, LOWER, omega,	"\033[0m|\033[1m",
	GROUGH, LOWER, rho,	"\033[0mb\033[1m",
	GSMOOTH, LOWER, rho,	"\033[0mc\033[1m",
	ANYACC, C_UPPER, sigma,	"S",
	ANYACC, C_UPPER, lsigma,	"S",
	ANYACC, C_UPPER, tsigma,	"S",
	ANYACC,	LOWER,	LDOUBBR,	"[[",
	ANYACC,	LOWER,	RDOUBBR,	"]]",
	ANYACC,	LOWER,	LHALFBR,	"\033[0md\033[1m",
	ANYACC,	LOWER,	RHALFBR,	"\033[0me\033[1m",
	ANYACC,	LOWER,	ELLIPSIS,	".",
	GSMOOTH|GCIRC, LOWER, C_BLANK,	"{",	
	GSMOOTH|GACUTE, LOWER, C_BLANK,		"^",	
	GSMOOTH|GGRAVE, LOWER, C_BLANK,		"`",
	GROUGH|GCIRC, LOWER, C_BLANK,		"|",	
	GROUGH|GACUTE, LOWER, C_BLANK,		"_",	
	GROUGH|GGRAVE, LOWER, C_BLANK,		"(\\",
	GSMOOTH, LOWER, C_BLANK,		"\\",	
	GROUGH, LOWER, C_BLANK,		"]",
	GACUTE, LOWER, C_BLANK,		"?",	
	GGRAVE, LOWER, C_BLANK,		"@",	
	GCIRC, LOWER, C_BLANK,		"[",	
	ANYACC,	LOWER,	C_BLANK,	" ",
	ANYACC, LOWER,	'.',		"\033[0m.\033[1m",
	ANYACC, LOWER,	',',		"\033[0m,\033[1m",
	ANYACC, LOWER,	'`',		"\033[0m`\033[1m",
	ANYACC, LOWER,	'\'',		"\033[0m'\033[1m",
	ANYACC, LOWER,	'"',		"\033[0m\"\033[1m",
	ANYACC, LOWER,	':',		"~",	/* raised dot */
	ANYACC, LOWER,	';',		"\033[0m;\033[1m",
	ANYACC, LOWER,	'?',		"\033[0m;\033[1m",
	};

static acc vt100gkac[] = {
	01,		"?",	/* acute */	
	02,		"@",	/* grave */
	0100,		"[",	/* circ */
	0104,		"{",	/* smooth circ */
	04,		"\\",	/* smooth breathing */
	05,		"^",	/* smooth breathing acute */
	06,		"`",	/* smooth breathing grave */
	010,		"]",	/* rough breathing */
	0110,		"|",	/* rough breathing circ */
	011,		"_",	/* rough breathing acute */
	012,		"(\\",	/* rough breathing grave  */
	020,		"",	/* diaeresis */
	040,		"\033[0m?\033[1m",	/* underline dot */
	0200,		"i",	/* iota subscript */
	};

	
comb vt100odco[] = {
	ANYACC,	LOWER,	num( 'a'),	"[a]",	/* full over and underline */
	ANYACC,	LOWER,	num( 'b'),	"[b]",	/* full overline */
	ANYACC,	LOWER,	num( 'c'),	"[c]",	/* full underline */
	ANYACC,	LOWER,	num( 'd'),	"[d]",	/* short mark */
	ANYACC,	LOWER,	num( 'e'),	"[e]",	/* long mark */
	ANYACC,	LOWER,	num( 'f'),	"[f]",	/* raised dot */
	ANYACC,	LOWER,	num( 'g'),	"[g]",	/* double crux */
	ANYACC,	LOWER,	num( 'h'),	"[h]",	/* fat period */
	ANYACC,	LOWER,	num( 'i'),	"[i]",	/* paragraph sign */
	ANYACC,	LOWER,	num( 'j'),	"[j]",	/* short vertical bar */
	ANYACC,	LOWER,	num( 'k'),	"[k]",	/* double vertical bar */
	ANYACC,	LOWER,	num( 'l'),	"[l]",	/* french circumflex */
	ANYACC,	LOWER,	num( 'm'),	"[m]",	/* left half bracket
							w full overline */
	ANYACC,	LOWER,	num( 'n'),	"[n]",	/* left lower half
						bracket w full underline */
	ANYACC,	LOWER,	num( 'o'),	"[o]",	/* large left brack
						w full ov and und line */
	ANYACC,	LOWER,	num( 'p'),	"[p]",	/* c cedila */
	ANYACC,	LOWER,	num( 'q'),	"[q]",	/* first half synaphoea */
	ANYACC,	LOWER,	num( 'r'),	"[r]",	/* double subscript dot */
	ANYACC,	LOWER,	num( 't'),	"[t]",	/* two shorts w a long
							underneath */
	ANYACC,	LOWER,	num( 'u'),	"[u]",	/* anceps */
	ANYACC,	LOWER,	num( 'v'),	"[v]",	/* short with a long
							underneath */
	ANYACC,	LOWER,	num( 'w'),	"[w]",	/* long with a short
							underneath */
	ANYACC,	LOWER,	num( 'x'),	"[x]",	/* neutral single quote */
	ANYACC,	LOWER,	num( 'y'),	"[y]",	/* upper curve of
							left compound brace
				   extending two or more lines --
				   TLG char [20 */
	ANYACC,	LOWER,	num( 'z'),	"[z]",	/* upper curve of
						right compound brace */
	ANYACC,	UPPER,	num( 'a'), 	"[A]",	/* middle segment
						of left compound brace */
	ANYACC,	UPPER,	num( 'b'),	"[B]",	/* middle segment
						of right compound brace*/
	ANYACC,	UPPER,	num( 'c'),	"[C]",	/* intermediate vertical
						seg of comp brace */
	ANYACC,	UPPER,	num( 'd'),	"[D]",	/* bottom curve of
						left compound brace */
	ANYACC,	UPPER,	num( 'e'),	"[E]",	/* bottom curve of
						right comp brace */
	ANYACC,	UPPER,	num( 'f'),	"[F]",	/* right upper half
						brack w full overl */
	ANYACC,	UPPER,	num( 'g'),	"[G]",	/* right half brack
						w full underl */
	ANYACC,	UPPER,	num( 'i'),	"[I]",	/* large right brackets
						for upper and lower l*/
	ANYACC,	UPPER,	num( 'j'),	"l",	/* upper and lower full line */
	ANYACC,	UPPER,	num( 'k'),	"[K]",	/* second half underline
							synaphoea */
	ANYACC,	UPPER,	num( 'l'),	"[L]",	/* left double brack */
	ANYACC,	UPPER,	num( 'm'),	"[M]",	/* right double brack */
	ANYACC,	UPPER,	num( 'n'),	"[N]",	/* left oversized
						square brack - non-joining */
	ANYACC,	UPPER,	num( 'o'),	"[O]",	/* right oversized
						square brack - non-joining*/
	ANYACC,	UPPER,	num( 'p'),	"[P]",	/* unbroken long
						vertical bar */
	ANYACC,	UPPER,	num( 'q'),	"\033[0mn\033[1m", /* dagger */
	ANYACC,	UPPER,	num( 'r'),	"[R]",	/* long dash */
	ANYACC,	UPPER,	num( 's'),	"[S]",	/* prodelision marker */
	ANYACC,	UPPER,	num( 't'),	"[T]",	/* left half bracket */
	ANYACC,	UPPER,	num( 'u'),	"[U]",	/* right half bracket */
	ANYACC,	UPPER,	num( 'v'),	"[V]",	/* open double quote */
	ANYACC,	UPPER,	num( 'w'),	"[W]",	/* close double quote */
	ANYACC,	UPPER,	num( 'x'),	"[X]",	/* open single quote */
	ANYACC,	UPPER,	num( 'y'),	"[Y]",	/* close single quote */
	};


