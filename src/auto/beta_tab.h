#include "filttab.h"


#define	GK_NOR	"a"
#define GK_BD_NM	"b"
/* not dealing with beta font change $2: shift into expanded greek font*/
#define GK_IT_NM	"d"
#define GK_SUP_NM	"e"
#define GK_SUB_NM	"f"

#define GK_BD_SUP	"g"
/* not dealing with beta font change $7: shift out of expanded greek font*/
/* or with $8: shift to vertical Greek font */
#define GK_SMALL		"h"	/* $10 smaller than normal Greek font */
#define GK_BD_S		"i"	/* $11 smaller than normal Greek Boldface */
#define GK_SP_S		"j"	/* $14 smaller than normal superscript */
#define GK_SB_S		"k"	/* $15 smaller than normal subscript*/
#define GK_SPBS		"l"	/* $16 smaller than normal boldface supers*/

#define GK_BIG		"m"	/* $20 larger than normal Greek font */
#define GK_SPB		"n"	/* $24 larger than normal superscript font*/
#define GK_SBB		"o"	/* $25 larger than normal subscript font*/

#define GK_VSMALL	"p"	/* $30 smaller than $10 */
#define GK_VBIG		"q"	/* $40 bigger than $20 */

int new_ch();

filt_tab beta_tab[] =  {
	"$", p_font, NORM_GREEK,
	"a/", new_ch, "'a",
	"a\\", new_ch, "`a",
	"a=", new_ch, "~a",
	"a(", new_ch, "<a",
	"a(/", new_ch, "<'a",
	"a(\\", new_ch, "<`a",
	"a(=", new_ch, "<~a",
	"a)", new_ch, ">a",
	"a)/", new_ch, ">'a",
	"a)\\", new_ch, ">`a",
	"a)=", new_ch, ">~a",

	"*a", 	new_ch,	"A",
	"*=a", new_ch, "~a",
	"*(a", new_ch, "<a",
	"*(/a", new_ch, "<'a",
	"*(\\a", new_ch, "<`a",
	"*(=a", new_ch, "<~a",
	"*)a", new_ch, ">a",
	"*)/a", new_ch, ">'a",
	"*)\\a", new_ch, ">`a",
	"*)=a", new_ch, ">~a",

	"a|", new_ch, "|a",
	"a/|", new_ch, "/|a",
	"a\\|", new_ch, "\\|a",
	"a=|", new_ch, "~|a",
	"a(|", new_ch, "<|a",
	"a(/|", new_ch, "<'|a",
	"a(\\|", new_ch, "<`|a",
	"a(=|", new_ch, "<~|a",
	"a)|", new_ch, ">|a",
	"a)/|", new_ch, ">'|a",
	"a)\\|", new_ch, ">`|a",
	"a)=|", new_ch, ">~|a",

	"*b", new_ch, "B",
	"*g", new_ch, "G",
	"*d", new_ch, "D",

	"*e", new_ch, "E",
	"*(e", new_ch, "<a",
	"*(/e", new_ch, "<'a",
	"*(\\e", new_ch, "<`a",
	"*)e", new_ch, ">a",
	"*)/e", new_ch, ">'a",
	"*)\\e", new_ch, ">`a",

	"e/", new_ch, "'a",
	"e\\", new_ch, "`a",
	"e(", new_ch, "<a",
	"e(/", new_ch, "<'a",
	"e(\\", new_ch, "<`a",
	"e)", new_ch, ">a",
	"e)/", new_ch, ">'a",
	"e)\\", new_ch, ">`a",

	"*z", new_ch, "Z",

	"*h", new_ch, "H",
	"*/h", new_ch, "'a",
	"*\\h", new_ch, "`a",
	"*=h", new_ch, "~a",
	"*(h", new_ch, "<a",
	"*(/h", new_ch, "<'a",
	"*(\\h", new_ch, "<`a",
	"*(=h", new_ch, "<~a",
	"*)h", new_ch, ">a",
	"*)/h", new_ch, ">'a",
	"*)\\h", new_ch, ">`a",
	"*)=h", new_ch, ">~a",

	"h/", new_ch, "'a",
	"h\\", new_ch, "`a",
	"h=", new_ch, "~a",
	"h(", new_ch, "<a",
	"h(/", new_ch, "<'a",
	"h(\\", new_ch, "<`a",
	"h(=", new_ch, "<~a",
	"h)", new_ch, ">a",
	"h)/", new_ch, ">'a",
	"h)\\", new_ch, ">`a",
	"h)=", new_ch, ">~a",

	"h|", new_ch, "|a",
	"h/|", new_ch, "/|a",
	"h\\|", new_ch, "\\|a",
	"h=|", new_ch, "~|a",
	"h(|", new_ch, "<|a",
	"h(/|", new_ch, "<'|a",
	"h(\\|", new_ch, "<`|a",
	"h(=|", new_ch, "<~|a",
	"h)|", new_ch, ">|a",
	"h)/|", new_ch, ">'|a",
	"h)\\|", new_ch, ">`|a",
	"h)=|", new_ch, ">~|a",

	"*q", new_ch, "Q",

	"*i", new_ch, "I",
	"*/i", new_ch, "'a",
	"*\\i", new_ch, "`a",
	"*=i", new_ch, "~a",
	"*(i", new_ch, "<a",
	"*(/i", new_ch, "<'a",
	"*(\\i", new_ch, "<`a",
	"*(=i", new_ch, "<~a",
	"*)i", new_ch, ">a",
	"*)/i", new_ch, ">'a",
	"*)\\i", new_ch, ">`a",
	"*)=i", new_ch, ">~a",

	"i/", new_ch, "'a",
	"i\\", new_ch, "`a",
	"i=", new_ch, "~a",
	"i(", new_ch, "<a",
	"i(/", new_ch, "<'a",
	"i(\\", new_ch, "<`a",
	"i(=", new_ch, "<~a",
	"i)", new_ch, ">a",
	"i)/", new_ch, ">'a",
	"i)\\", new_ch, ">`a",
	"i)=", new_ch, ">~a",

	"*k", new_ch, "K",
	"*l", new_ch, "L",
	"*m", new_ch, "M",
	"*n", new_ch, "N",
	"*c", new_ch, "C",

	"*o", new_ch, "O",
	"o/", new_ch, "'a",
	"o\\", new_ch, "`a",
	"o(", new_ch, "<a",
	"o(/", new_ch, "<'a",
	"o(\\", new_ch, "<`a",
	"o)", new_ch, ">a",
	"o)/", new_ch, ">'a",
	"o)\\", new_ch, ">`a",

	"*/o", new_ch, "'a",
	"*\\o", new_ch, "`a",
	"*(o", new_ch, "<a",
	"*(/o", new_ch, "<'a",
	"*(\\o", new_ch, "<`a",
	"*)o", new_ch, ">a",
	"*)/o", new_ch, ">'a",
	"*)\\o", new_ch, ">`a",

	"*p", new_ch, "P",
	"*r", new_ch, "R",

	"s1", new_ch, "s",
	"s2", new_ch, "s",
	"s3", new_ch, "s",
	"*s", new_ch, "S",
	"*s1", new_ch, "S",
	"*s2", new_ch, "S",
	"*s3", new_ch, "S",

	"*t", new_ch, "T",
	
	"*u", new_ch, "U",
	"*/u", new_ch, "'a",
	"*\\u", new_ch, "`a",
	"*=u", new_ch, "~a",
	"*(u", new_ch, "<a",
	"*(/u", new_ch, "<'a",
	"*(\\u", new_ch, "<`a",
	"*(=u", new_ch, "<~a",
	"*)u", new_ch, ">a",
	"*)/u", new_ch, ">'a",
	"*)\\u", new_ch, ">`a",
	"*)=u", new_ch, ">~a",

	"u/", new_ch, "'a",
	"u\\", new_ch, "`a",
	"u=", new_ch, "~a",
	"u(", new_ch, "<a",
	"u(/", new_ch, "<'a",
	"u(\\", new_ch, "<`a",
	"u(=", new_ch, "<~a",
	"u)", new_ch, ">a",
	"u)/", new_ch, ">'a",
	"u)\\", new_ch, ">`a",
	"u)=", new_ch, ">~a",

	"*f", new_ch, "F",
	"*x", new_ch, "X",
	"*y", new_ch, "Y",

	"*w", new_ch, "I",
	"*/w", new_ch, "'a",
	"*\\w", new_ch, "`a",
	"*=w", new_ch, "~a",
	"*(w", new_ch, "<a",
	"*(/w", new_ch, "<'a",
	"*(\\w", new_ch, "<`a",
	"*(=w", new_ch, "<~a",
	"*)w", new_ch, ">a",
	"*)/w", new_ch, ">'a",
	"*)\\w", new_ch, ">`a",
	"*)=w", new_ch, ">~a",

	"w/", new_ch, "'a",
	"w\\", new_ch, "`a",
	"w=", new_ch, "~a",
	"w(", new_ch, "<a",
	"w(/", new_ch, "<'a",
	"w(\\", new_ch, "<`a",
	"w(=", new_ch, "<~a",
	"w)", new_ch, ">a",
	"w)/", new_ch, ">'a",
	"w)\\", new_ch, ">`a",
	"w)=", new_ch, ">~a",
	
	
	"w|", new_ch, "|a",
	"w/|", new_ch, "/|a",
	"w\\|", new_ch, "\\|a",
	"w=|", new_ch, "~|a",
	"w(|", new_ch, "<|a",
	"w(/|", new_ch, "<'|a",
	"w(\\|", new_ch, "<`|a",
	"w(=|", new_ch, "<~|a",
	"w)|", new_ch, ">|a",
	"w)/|", new_ch, ">'|a",
	"w)\\|", new_ch, ">`|a",
	"w)=|", new_ch, ">~|a",

};
