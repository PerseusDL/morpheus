/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
*** copy of signifier.c modified for interleaf format
*/
     
#include "filttab.h"

char * ileaf_greek[MAX_GK_CHARS];
char * ileaf_dgreek[MAX_GK_CHARS];

setup_ileaf_greek()
{
	ileaf_greek[alpha] = "a";
	ileaf_greek[a_SM_AC] = "<F47><#13><F46>";
	ileaf_greek[a_SM_GR] = "<F47>D<F46>";
	ileaf_greek[a_SM_CI] = "<F47>F<F46>";
	ileaf_greek[a_RO_AC] = "<F47>d<F46>";
	ileaf_greek[a_RO_GR] = "<F47><#04><F46>";
	ileaf_greek[a_RO_CI] = "<F47>f<F46>";
	ileaf_greek[a_AC] = "<F47>A<F46>";
	ileaf_greek[a_GR] = "<F47><#01><F46>";
	ileaf_greek[a_CI] = "<F47>S<F46>";
	ileaf_greek[a_SM] = "<F47>a<F46>";
	ileaf_greek[a_RO] = "<F47>s<F46>";
	ileaf_greek[a_SM_AC_IS] = "<F47>#<F46>";
	ileaf_greek[a_SM_GR_IS] = "<F47>$<F46>";
	ileaf_greek[a_SM_CI_IS] = "<F47>%<F46>";
	ileaf_greek[a_RO_AC_IS] = "<F47>4<F46>";
	ileaf_greek[a_RO_GR_IS] = "<F47><#1d><F46>";
	ileaf_greek[a_RO_CI_IS] = "<F47>5<F46>";
	ileaf_greek[a_AC_IS] = "<F47>!<F46>";
	ileaf_greek[a_GR_IS] = "<F47>2<F46>";
	ileaf_greek[a_CI_IS] = "<F47>3<F46>";
	ileaf_greek[a_SM_IS] = "<F47>1<F46>";
	ileaf_greek[a_RO_IS] = "<F47>@<F46>";
	ileaf_greek[a_IS] = "<#01>";
	ileaf_greek[ALPHA] = "A";
	ileaf_greek[A_SM_CI] = "<#12>A";
	ileaf_greek[A_SM_AC] = "<#17>A";
	ileaf_greek[A_SM_GR] = "<#05>A";
	ileaf_greek[A_RO_CI] = "<#09>A";
	ileaf_greek[A_RO_AC] = "<#19>A";
	ileaf_greek[A_RO_GR] = "<#15>A";
	ileaf_greek[A_SM] = "<#11>A";
	ileaf_greek[A_RO] = "<#14>A";
	ileaf_greek[A_CI] = "<#0e>A";
	ileaf_greek[beta] = "b";
	ileaf_greek[BETA] = "B";
	ileaf_greek[GAMMA] = "G";
	ileaf_greek[gamma] = "g";
	ileaf_greek[delta] = "d";
	ileaf_greek[DELTA] = "D";
	ileaf_greek[epsilon] = "e";
	ileaf_greek[EPSILON] = "E";
	ileaf_greek[e_SM_AC] = "<F47><#17><F46>";
	ileaf_greek[e_SM_GR] = "<F47>E<F46>";
	ileaf_greek[e_RO_AC] = "<F47>e<F46>";
	ileaf_greek[e_RO_GR] = "<F47><#05><F46>";
	ileaf_greek[e_AC] = "<F47>Q<F46>";
	ileaf_greek[e_GR] = "<F47><#11><F46>";
	ileaf_greek[e_SM] = "<F47>q<F46>";
	ileaf_greek[e_RO] = "<F47>w<F46>";
	ileaf_greek[E_SM_AC] = "<#17>E";
	ileaf_greek[E_SM_GR] = "<#05>E";
	ileaf_greek[E_RO_AC] = "<#19>E";
	ileaf_greek[E_RO_GR] = "<#15>E";
	ileaf_greek[E_SM] = "<#11>E";
	ileaf_greek[E_RO] = "<#14>E";
	ileaf_greek[hta] = "h";
	ileaf_greek[HTA] = "H";
	ileaf_greek[H_SM_CI] = "<#12>H";
	ileaf_greek[H_SM_AC] = "<#17>H";
	ileaf_greek[H_SM_GR] = "<#05>H";
	ileaf_greek[H_RO_CI] = "<#09>H";
	ileaf_greek[H_RO_AC] = "<#19>H";
	ileaf_greek[H_RO_GR] = "<#15>H";
	ileaf_greek[H_SM] = "<#11>H";
	ileaf_greek[H_RO] = "<#14>H";
	ileaf_greek[H_CI] = "<#0e>H";
	ileaf_greek[h_SM_AC] = "<F47><#08><F46>";
	ileaf_greek[h_SM_GR] = "<F47>J<F46>";
	ileaf_greek[h_SM_CI] = "<F47>K<F46>";
	ileaf_greek[h_RO_AC] = "<F47>j<F46>";
	ileaf_greek[h_RO_GR] = "<F47><#0a><F46>";
	ileaf_greek[h_RO_CI] = "<F47>k<F46>";
	ileaf_greek[h_AC] = "<F47>G<F46>";
	ileaf_greek[h_GR] = "<F47><#07><F46>";
	ileaf_greek[h_CI] = "<F47>H<F46>";
	ileaf_greek[h_SM] = "<F47>g<F46>";
	ileaf_greek[h_RO] = "<F47>h<F46>";
	ileaf_greek[h_SM_AC_IS] = "<F47><#1f><F46>";
	ileaf_greek[h_SM_GR_IS] = "<F47>~<F46>";
	ileaf_greek[h_SM_CI_IS] = "<F47>]<F46>";
	ileaf_greek[h_RO_AC_IS] = "<F47>\<F46>";
	ileaf_greek[h_RO_GR_IS] = "<F47>{<F46>";
	ileaf_greek[h_RO_CI_IS] = "<F47>[<F46>";
	ileaf_greek[h_AC_IS] = "<F47><#5f><F46>";
	ileaf_greek[h_GR_IS] = "<F47><#1e><F46>";
	ileaf_greek[h_CI_IS] = "<F47>+<F46>";
	ileaf_greek[h_SM_IS] = "<F47>-<F46>";
	ileaf_greek[h_RO_IS] = "<F47>=<F46>";
	ileaf_greek[h_IS] = "<#08>";
	ileaf_greek[zeta] = "z";
	ileaf_greek[ZETA] = "Z";
	ileaf_greek[qeta] = "u";
	ileaf_greek[QETA] = "U";
	ileaf_greek[iota] = "i";
	ileaf_greek[IOTA] = "I";
	ileaf_greek[i_SM_AC] = "<F47><#09><F46>";
	ileaf_greek[i_SM_GR] = "<F47>(<F46>";
	ileaf_greek[i_SM_CI] = "<F47>0<F46>";
	ileaf_greek[i_RO_AC] = "<F47>8<F46>";
	ileaf_greek[i_RO_GR] = "<F47>9<F46>";
	ileaf_greek[i_RO_CI] = "<F47>(<F46>";
	ileaf_greek[i_DI] = "<#0a>";
	ileaf_greek[i_AC_DI] = "<#0b>";
	ileaf_greek[i_GR_DI] = "<#0c>";
	ileaf_greek[i_AC] = "<F47>U<F46>";
	ileaf_greek[i_GR] = "<F47><#15><F46>";
	ileaf_greek[i_CI] = "<F47>I<F46>";
	ileaf_greek[i_SM] = "<F47>u<F46>";
	ileaf_greek[i_RO] = "<F47>i<F46>";
	ileaf_greek[I_SM_CI] = "<#12>I";
	ileaf_greek[I_SM_AC] = "<#17>I";
	ileaf_greek[I_SM_GR] = "<#05>I";
	ileaf_greek[I_RO_CI] = "<#09>I";
	ileaf_greek[I_RO_AC] = "<#19>I";
	ileaf_greek[I_RO_GR] = "<#15>I";
	ileaf_greek[I_SM] = "<#11>I";
	ileaf_greek[I_RO] = "<#14>I";
	ileaf_greek[I_CI] = "<#0e>I";
	ileaf_greek[I_AC] = "<#0f>I";
	ileaf_greek[I_GR] = "<#10>I";
	ileaf_greek[kappa] = "k";
	ileaf_greek[KAPPA] = "K";
	ileaf_greek[lambda] = "l";
	ileaf_greek[LAMBDA] = "L";
	ileaf_greek[mu] = "m";
	ileaf_greek[MU] = "M";
	ileaf_greek[nu] = "n";
	ileaf_greek[NU] = "N";
	ileaf_greek[ci] = "j";
	ileaf_greek[CI] = "J";
	ileaf_greek[omicron] = "o";
	ileaf_greek[OMICRON] = "O";
	ileaf_greek[o_SM_AC] = "<F47><#10><F46>";
	ileaf_greek[o_SM_GR] = "<F47>L<F46>";
	ileaf_greek[o_RO_AC] = "<F47>l<F46>";
	ileaf_greek[o_RO_GR] = "<F47><#0c><F46>";
	ileaf_greek[o_AC] = "<F47>O<F46>";
	ileaf_greek[o_GR] = "<F47><#0f><F46>";
	ileaf_greek[o_SM] = "<F47>o<F46>";
	ileaf_greek[o_RO] = "<F47>p<F46>";
	ileaf_greek[O_SM_AC] = "<#17>O";
	ileaf_greek[O_SM_GR] = "<#05>O";
	ileaf_greek[O_RO_AC] = "<#19>O";
	ileaf_greek[O_RO_GR] = "<#15>O";
	ileaf_greek[O_AC] = "<#0f>O";
	ileaf_greek[O_GR] = "<#10>O";
	ileaf_greek[O_SM] = "<#11>O";
	ileaf_greek[O_RO] = "<#14>O";
	ileaf_greek[pi] = "p";
	ileaf_greek[PI] = "P";
	ileaf_greek[RHO] = "R";
	ileaf_greek[R_SM] = "<#11>R";
	ileaf_greek[R_RO] = "<#14>R";
	ileaf_greek[rho] = "r";
	ileaf_greek[r_SM] = "<#11>r";
	ileaf_greek[r_RO] = "<#23>";
	ileaf_greek[SIGMA] = "S";
	ileaf_greek[sigma] = "!";
	ileaf_greek[tau] = "t";
	ileaf_greek[TAU] = "T";
	ileaf_greek[UPSILON] = "Y";
	ileaf_greek[U_SM_CI] = "<#12>Y";
	ileaf_greek[U_SM_AC] = "<#17>Y";
	ileaf_greek[U_SM_GR] = "<#05>Y";
	ileaf_greek[U_RO_CI] = "<#09>Y";
	ileaf_greek[U_RO_AC] = "<#19>Y";
	ileaf_greek[U_RO_GR] = "<#15>Y";
	ileaf_greek[U_SM] = "<#11>Y";
	ileaf_greek[U_RO] = "<#14>Y";
	ileaf_greek[U_CI] = "<#0e>Y";
	ileaf_greek[U_AC] = "<#0f>Y";
	ileaf_greek[U_GR] = "<#10>Y";
	ileaf_greek[upsilon] = "y";
	ileaf_greek[u_SM_AC] = "<F47><#19><F46>";
	ileaf_greek[u_SM_GR] = "<F47>^<F46>";
	ileaf_greek[u_SM_CI] = "<F47>*<F46>";
	ileaf_greek[u_RO_AC] = "<F47>6<F46>";
	ileaf_greek[u_RO_GR] = "<F47>7<F46>";
	ileaf_greek[u_RO_CI] = "<F47>&<F46>";
	ileaf_greek[u_DI] = "<#04>";
	ileaf_greek[u_AC_DI] = "<#06>";
	ileaf_greek[u_GR_DI] = "<#07>";
	ileaf_greek[u_AC] = "<F47>T<F46>";
	ileaf_greek[u_GR] = "<F47><#14><F46>";
	ileaf_greek[u_CI] = "<F47>Y<F46>";
	ileaf_greek[u_SM] = "<F47>t<F46>";
	ileaf_greek[u_RO] = "<F47>y<F46>";
	ileaf_greek[FI] = "F";
	ileaf_greek[fi] = "f";
	ileaf_greek[xi] = "x";
	ileaf_greek[XI] = "X";
	ileaf_greek[yi] = "c";
	ileaf_greek[YI] = "C";
	ileaf_greek[WMEGA] = "V";
	ileaf_greek[wmega] = "v";
	ileaf_greek[w_SM_AC] = "<F47><#18><F46>";
	ileaf_greek[w_SM_GR] = "<F47>C<F46>";
	ileaf_greek[w_SM_CI] = "<F47>V<F46>";
	ileaf_greek[w_RO_AC] = "<F47>c<F46>";
	ileaf_greek[w_RO_GR] = "<F47><#03><F46>";
	ileaf_greek[w_RO_CI] = "<F47>v<F46>";
	ileaf_greek[w_AC] = "<F47>Z<F46>";
	ileaf_greek[w_GR] = "<F47><#1a><F46>";
	ileaf_greek[w_CI] = "<F47>X<F46>";
	ileaf_greek[w_SM] = "<F47>z<F46>";
	ileaf_greek[w_RO] = "<F47>x<F46>";
	ileaf_greek[W_SM_CI] = "<#12>V";
	ileaf_greek[W_SM_AC] = "<#17>V";
	ileaf_greek[W_SM_GR] = "<#05>V";
	ileaf_greek[W_RO_CI] = "<#09>V";
	ileaf_greek[W_RO_AC] = "<#19>V";
	ileaf_greek[W_RO_GR] = "<#15>V";
	ileaf_greek[W_SM] = "<#11>V";
	ileaf_greek[W_RO] = "<#14>V";
	ileaf_greek[W_CI] = "<#0e>V";
	ileaf_greek[W_AC] = "<#0f>V";
	ileaf_greek[W_GR] = "<#10>V";
	ileaf_greek[w_IS] = "<#16>";
	ileaf_greek[w_SM_AC_IS] = "<F47><#0e><F46>";
	ileaf_greek[w_SM_GR_IS] = "<F47>M<F46>";
	ileaf_greek[w_SM_CI_IS] = "<F47><<<F46>";
	ileaf_greek[w_RO_AC_IS] = "<F47>m<F46>";
	ileaf_greek[w_RO_GR_IS] = "<F47><#0d><F46>";
	ileaf_greek[w_RO_CI_IS] = "<F47>,<F46>";
	ileaf_greek[w_AC_IS] = "<F47>B<F46>";
	ileaf_greek[w_GR_IS] = "<F47><#02><F46>";
	ileaf_greek[w_CI_IS] = "<F47>N<F46>";
	ileaf_greek[w_SM_IS] = "<F47>b<F46>";
	ileaf_greek[w_RO_IS] = "<F47>n<F46>";
	ileaf_greek[tsigma] = "w";
	ileaf_greek[ELLIPSIS] = ".";
	 
	ileaf_dgreek[alpha] = "a?";
	ileaf_dgreek[a_SM_AC] = "<F47><#13><F46>?";
	ileaf_dgreek[a_SM_GR] = "<F47>D<F46>?";
	ileaf_dgreek[a_SM_CI] = "<F47>F<F46>?";
	ileaf_dgreek[a_RO_AC] = "<F47>d<F46>?";
	ileaf_dgreek[a_RO_GR] = "<F47><#04><F46>?";
	ileaf_dgreek[a_RO_CI] = "<F47>f<F46>?";
	ileaf_dgreek[a_AC] = "<F47>A<F46>?";
	ileaf_dgreek[a_GR] = "<F47><#01><F46>?";
	ileaf_dgreek[a_CI] = "<F47>S<F46>?";
	ileaf_dgreek[a_SM] = "<F47>a<F46>?";
	ileaf_dgreek[a_RO] = "<F47>s<F46>?";
	ileaf_dgreek[a_SM_AC_IS] = "<F47>#<F46>?";
	ileaf_dgreek[a_SM_GR_IS] = "<F47>$<F46>?";
	ileaf_dgreek[a_SM_CI_IS] = "<F47>%<F46>?";
	ileaf_dgreek[a_RO_AC_IS] = "<F47>4<F46>?";
	ileaf_dgreek[a_RO_GR_IS] = "<F47><#1d><F46>?";
	ileaf_dgreek[a_RO_CI_IS] = "<F47>5<F46>?";
	ileaf_dgreek[a_AC_IS] = "<F47>!<F46>?";
	ileaf_dgreek[a_GR_IS] = "<F47>2<F46>?";
	ileaf_dgreek[a_CI_IS] = "<F47>3<F46>?";
	ileaf_dgreek[a_SM_IS] = "<F47>1<F46>?";
	ileaf_dgreek[a_RO_IS] = "<F47>@<F46>?";
	ileaf_dgreek[a_IS] = "<#01>?";
	ileaf_dgreek[ALPHA] = "A?";
	ileaf_dgreek[A_SM_CI] = "<#12>A?";
	ileaf_dgreek[A_SM_AC] = "<#17>A?";
	ileaf_dgreek[A_SM_GR] = "<#05>A?";
	ileaf_dgreek[A_RO_CI] = "<#09>A?";
	ileaf_dgreek[A_RO_AC] = "<#19>A?";
	ileaf_dgreek[A_RO_GR] = "<#15>A?";
	ileaf_dgreek[A_SM] = "<#11>A?";
	ileaf_dgreek[A_RO] = "<#14>A?";
	ileaf_dgreek[A_CI] = "<#0e>A?";
	ileaf_dgreek[beta] = "b?";
	ileaf_dgreek[BETA] = "B?";
	ileaf_dgreek[GAMMA] = "G?";
	ileaf_dgreek[gamma] = "g?";
	ileaf_dgreek[delta] = "d?";
	ileaf_dgreek[DELTA] = "D?";
	ileaf_dgreek[epsilon] = "e?";
	ileaf_dgreek[EPSILON] = "E?";
	ileaf_dgreek[e_SM_AC] = "<F47><#17><F46>?";
	ileaf_dgreek[e_SM_GR] = "<F47>E<F46>?";
	ileaf_dgreek[e_RO_AC] = "<F47>e<F46>?";
	ileaf_dgreek[e_RO_GR] = "<F47><#05><F46>?";
	ileaf_dgreek[e_AC] = "<F47>Q<F46>?";
	ileaf_dgreek[e_GR] = "<F47><#11><F46>?";
	ileaf_dgreek[e_SM] = "<F47>q<F46>?";
	ileaf_dgreek[e_RO] = "<F47>w<F46>?";
	ileaf_dgreek[E_SM_AC] = "<#17>E?";
	ileaf_dgreek[E_SM_GR] = "<#05>E?";
	ileaf_dgreek[E_RO_AC] = "<#19>E?";
	ileaf_dgreek[E_RO_GR] = "<#15>E?";
	ileaf_dgreek[E_SM] = "<#11>E?";
	ileaf_dgreek[E_RO] = "<#14>E?";
	ileaf_dgreek[hta] = "h?";
	ileaf_dgreek[HTA] = "H?";
	ileaf_dgreek[H_SM_CI] = "<#12>H?";
	ileaf_dgreek[H_SM_AC] = "<#17>H?";
	ileaf_dgreek[H_SM_GR] = "<#05>H?";
	ileaf_dgreek[H_RO_CI] = "<#09>H?";
	ileaf_dgreek[H_RO_AC] = "<#19>H?";
	ileaf_dgreek[H_RO_GR] = "<#15>H?";
	ileaf_dgreek[H_SM] = "<#11>H?";
	ileaf_dgreek[H_RO] = "<#14>H?";
	ileaf_dgreek[H_CI] = "<#0e>H?";
	ileaf_dgreek[h_SM_AC] = "<F47><#08><F46>?";
	ileaf_dgreek[h_SM_GR] = "<F47>J<F46>?";
	ileaf_dgreek[h_SM_CI] = "<F47>K<F46>?";
	ileaf_dgreek[h_RO_AC] = "<F47>j<F46>?";
	ileaf_dgreek[h_RO_GR] = "<F47><#0a><F46>?";
	ileaf_dgreek[h_RO_CI] = "<F47>k<F46>?";
	ileaf_dgreek[h_IS] = "hi?";
	ileaf_dgreek[h_AC] = "<F47>G<F46>?";
	ileaf_dgreek[h_GR] = "<F47><#07><F46>?";
	ileaf_dgreek[h_CI] = "<F47>H<F46>?";
	ileaf_dgreek[h_SM] = "<F47>g<F46>?";
	ileaf_dgreek[h_RO] = "<F47>h<F46>?";
	ileaf_dgreek[h_SM_AC_IS] = "<F47><#1f><F46>?";
	ileaf_dgreek[h_SM_GR_IS] = "<F47>~<F46>?";
	ileaf_dgreek[h_SM_CI_IS] = "<F47>]<F46>?";
	ileaf_dgreek[h_RO_AC_IS] = "<F47>\<F46>?";
	ileaf_dgreek[h_RO_GR_IS] = "<F47>{<F46>?";
	ileaf_dgreek[h_RO_CI_IS] = "<F47>[<F46>?";
	ileaf_dgreek[h_AC_IS] = "<F47><#5f><F46>?";
	ileaf_dgreek[h_GR_IS] = "<F47><#1e><F46>?";
	ileaf_dgreek[h_CI_IS] = "<F47>+<F46>?";
	ileaf_dgreek[h_SM_IS] = "<F47>-<F46>?";
	ileaf_dgreek[h_RO_IS] = "<F47>=<F46>?";
	ileaf_dgreek[zeta] = "z?";
	ileaf_dgreek[ZETA] = "Z?";
	ileaf_dgreek[qeta] = "u?";
	ileaf_dgreek[QETA] = "U?";
	ileaf_dgreek[iota] = "i?";
	ileaf_dgreek[IOTA] = "I?";
	ileaf_dgreek[i_SM_AC] = "<F47><#09><F46>?";
	ileaf_dgreek[i_SM_GR] = "<F47>(<F46>?";
	ileaf_dgreek[i_SM_CI] = "<F47>0<F46>?";
	ileaf_dgreek[i_RO_AC] = "<F47>8<F46>?";
	ileaf_dgreek[i_RO_GR] = "<F47>9<F46>?";
	ileaf_dgreek[i_RO_CI] = "<F47>(<F46>?";
	ileaf_dgreek[i_DI] = "<#0a>?";
	ileaf_dgreek[i_AC_DI] = "<#0b>?";
	ileaf_dgreek[i_GR_DI] = "<#0c>?";
	ileaf_dgreek[i_AC] = "<F47>U<F46>?";
	ileaf_dgreek[i_GR] = "<F47><#15><F46>?";
	ileaf_dgreek[i_CI] = "<F47>I<F46>?";
	ileaf_dgreek[i_SM] = "<F47>u<F46>?";
	ileaf_dgreek[i_RO] = "<F47>i<F46>?";
	ileaf_dgreek[I_SM_CI] = "<#12>I?";
	ileaf_dgreek[I_SM_AC] = "<#17>I?";
	ileaf_dgreek[I_SM_GR] = "<#05>I?";
	ileaf_dgreek[I_RO_CI] = "<#09>I?";
	ileaf_dgreek[I_RO_AC] = "<#19>I?";
	ileaf_dgreek[I_RO_GR] = "<#15>I?";
	ileaf_dgreek[I_SM] = "<#11>I?";
	ileaf_dgreek[I_RO] = "<#14>I?";
	ileaf_dgreek[I_CI] = "<#0e>I?";
	ileaf_dgreek[I_AC] = "<#0f>I?";
	ileaf_dgreek[I_GR] = "<#10>I?";
	ileaf_dgreek[kappa] = "k?";
	ileaf_dgreek[KAPPA] = "K?";
	ileaf_dgreek[lambda] = "l?";
	ileaf_dgreek[LAMBDA] = "L?";
	ileaf_dgreek[mu] = "m?";
	ileaf_dgreek[MU] = "M?";
	ileaf_dgreek[nu] = "n?";
	ileaf_dgreek[NU] = "N?";
	ileaf_dgreek[ci] = "j?";
	ileaf_dgreek[CI] = "J?";
	ileaf_dgreek[omicron] = "o?";
	ileaf_dgreek[OMICRON] = "O?";
	ileaf_dgreek[o_SM_AC] = "<F47><#10><F46>?";
	ileaf_dgreek[o_SM_GR] = "<F47>L<F46>?";
	ileaf_dgreek[o_RO_AC] = "<F47>l<F46>?";
	ileaf_dgreek[o_RO_GR] = "<F47><#0c><F46>?";
	ileaf_dgreek[o_AC] = "<F47>O<F46>?";
	ileaf_dgreek[o_GR] = "<F47><#0f><F46>?";
	ileaf_dgreek[o_SM] = "<F47>o<F46>?";
	ileaf_dgreek[o_RO] = "<F47>p<F46>?";
	ileaf_dgreek[O_SM_AC] = "<#17>O?";
	ileaf_dgreek[O_SM_GR] = "<#05>O?";
	ileaf_dgreek[O_RO_AC] = "<#19>O?";
	ileaf_dgreek[O_RO_GR] = "<#15>O?";
	ileaf_dgreek[O_AC] = "<#0f>O?";
	ileaf_dgreek[O_GR] = "<#10>O?";
	ileaf_dgreek[O_SM] = "<#11>O?";
	ileaf_dgreek[O_RO] = "<#14>O?";
	ileaf_dgreek[pi] = "p?";
	ileaf_dgreek[PI] = "P?";
	ileaf_dgreek[RHO] = "R?";
	ileaf_dgreek[R_SM] = "<#11>R?";
	ileaf_dgreek[R_RO] = "<#14>R?";
	ileaf_dgreek[rho] = "r?";
	ileaf_dgreek[r_SM] = "<#11>r?";
	ileaf_dgreek[r_RO] = "360r?";
	ileaf_dgreek[SIGMA] = "S?";
	ileaf_dgreek[sigma] = "!?";
	ileaf_dgreek[tau] = "t?";
	ileaf_dgreek[TAU] = "T?";
	ileaf_dgreek[UPSILON] = "Y?";
	ileaf_dgreek[U_SM_CI] = "<#12>Y?";
	ileaf_dgreek[U_SM_AC] = "<#17>Y?";
	ileaf_dgreek[U_SM_GR] = "<#05>Y?";
	ileaf_dgreek[U_RO_CI] = "<#09>Y?";
	ileaf_dgreek[U_RO_AC] = "<#19>Y?";
	ileaf_dgreek[U_RO_GR] = "<#15>Y?";
	ileaf_dgreek[U_SM] = "<#11>Y?";
	ileaf_dgreek[U_RO] = "<#14>Y?";
	ileaf_dgreek[U_CI] = "<#0e>Y?";
	ileaf_dgreek[U_AC] = "<#0f>Y?";
	ileaf_dgreek[U_GR] = "<#10>Y?";
	ileaf_dgreek[upsilon] = "y?";
	ileaf_dgreek[u_SM_AC] = "<F47><#19><F46>?";
	ileaf_dgreek[u_SM_GR] = "<F47>^<F46>?";
	ileaf_dgreek[u_SM_CI] = "<F47>*<F46>?";
	ileaf_dgreek[u_RO_AC] = "<F47>6<F46>?";
	ileaf_dgreek[u_RO_GR] = "<F47>7<F46>?";
	ileaf_dgreek[u_RO_CI] = "<F47>&<F46>?";
	ileaf_dgreek[u_DI] = "<#04>?";
	ileaf_dgreek[u_AC_DI] = "<#06>?";
	ileaf_dgreek[u_GR_DI] = "<#07>?";
	ileaf_dgreek[u_AC] = "<F47>T<F46>?";
	ileaf_dgreek[u_GR] = "<F47><#14><F46>?";
	ileaf_dgreek[u_CI] = "<F47>Y<F46>?";
	ileaf_dgreek[u_SM] = "<F47>t<F46>?";
	ileaf_dgreek[u_RO] = "<F47>y<F46>?";
	ileaf_dgreek[FI] = "F?";
	ileaf_dgreek[fi] = "f?";
	ileaf_dgreek[xi] = "x?";
	ileaf_dgreek[XI] = "X?";
	ileaf_dgreek[yi] = "c?";
	ileaf_dgreek[YI] = "C?";
	ileaf_dgreek[WMEGA] = "V?";
	ileaf_dgreek[wmega] = "v?";
	ileaf_dgreek[w_SM_AC] = "<F47><#18><F46>?";
	ileaf_dgreek[w_SM_GR] = "<F47>C<F46>?";
	ileaf_dgreek[w_SM_CI] = "<F47>V<F46>?";
	ileaf_dgreek[w_RO_AC] = "<F47>c<F46>?";
	ileaf_dgreek[w_RO_GR] = "<F47><#03><F46>?";
	ileaf_dgreek[w_RO_CI] = "<F47>v<F46>?";
	ileaf_dgreek[w_AC] = "<F47>Z<F46>?";
	ileaf_dgreek[w_GR] = "<F47><#1a><F46>?";
	ileaf_dgreek[w_CI] = "<F47>X<F46>?";
	ileaf_dgreek[w_SM] = "<F47>z<F46>?";
	ileaf_dgreek[w_RO] = "<F47>x<F46>?";
	ileaf_dgreek[W_SM_CI] = "<#12>V?";
	ileaf_dgreek[W_SM_AC] = "<#17>V?";
	ileaf_dgreek[W_SM_GR] = "<#05>V?";
	ileaf_dgreek[W_RO_CI] = "<#09>V?";
	ileaf_dgreek[W_RO_AC] = "<#19>V?";
	ileaf_dgreek[W_RO_GR] = "<#15>V?";
	ileaf_dgreek[W_SM] = "<#11>V?";
	ileaf_dgreek[W_RO] = "<#14>V?";
	ileaf_dgreek[W_CI] = "<#0e>V?";
	ileaf_dgreek[W_AC] = "<#0f>V?";
	ileaf_dgreek[W_GR] = "<#10>V?";
	ileaf_dgreek[w_IS] = "<#16>?";
	ileaf_dgreek[w_SM_AC_IS] = "<F47><#18><F46>?";
	ileaf_dgreek[w_SM_GR_IS] = "<F47>M<F46>?";
	ileaf_dgreek[w_SM_CI_IS] = "<F47><<<F46>?";
	ileaf_dgreek[w_RO_AC_IS] = "<F47>m<F46>?";
	ileaf_dgreek[w_RO_GR_IS] = "<F47><#0d><F46>?";
	ileaf_dgreek[w_RO_CI_IS] = "<F47>,<F46>?";
	ileaf_dgreek[w_AC_IS] = "<F47>B<F46>?";
	ileaf_dgreek[w_GR_IS] = "<F47><#02><F46>?";
	ileaf_dgreek[w_CI_IS] = "<F47>N<F46>?";
	ileaf_dgreek[w_SM_IS] = "<F47>b<F46>?";
	ileaf_dgreek[w_RO_IS] = "<F47>n<F46>?";
	ileaf_dgreek[tsigma] = "w?";
	ileaf_dgreek[ELLIPSIS] = ".?";
}

	char *ileaf_punct[] = {
		"<#5c>", /* 0 dagger */
		"?",		/* 1 */
		"*",		/* 2 */
		"/",		/* 3 */
		"!",		/* 4 */
		"|",		/* 5 */
		"=",		/* 6 */
		"+",		/* 7 */
		"%",		/* 8 '%' */
		"&",		/* 9 */
		":",		/* 10 */
		".",		/* 11 (should be) oversized period */
		"*",		/* 12 variant '*' */
		"<#0e>", /* 13 (should be) double dagger */
		"(Sect)", 	/* 14 paragraph sign */
		"|",		/* 15 should be short vertical bar */
		"|",		/* 16 should be broken vertical bar */
		"||",	/* 17 double vertical bar */
	};
		
char * ileaf_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"<<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"<#24>",	/* left double bracket */
		"<#5e>",	/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * ileaf_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"<#25>",	/* right double bracket */
		"<#26>",	/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * ileaf_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"\"",		/* 1 low double close quote */
		"\"",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *ileaf_tgreek = "<F46>";
char *ileaf_tbgreek = "";
char *ileaf_troman = "<F31>";

char * ileaf_newline = "<HR>\n";

fix_ileaf_save(fname)
char * fname;
{
	char tmp[256];

	sprintf(tmp,"ileaf %s\n", fname );
	system( tmp );
}

add_ileaf_header(f)
FILE * f;
{
}
