/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "filttab.h"

char * troff_greek[MAX_GK_CHARS];
char * troff_dgreek[MAX_GK_CHARS];

setup_troff_greek()
{

	troff_greek[alpha] = "a";
	troff_greek[a_AC] = "'a";
	troff_greek[a_GR] = "`a";
	troff_greek[a_CI] = "~a";
	troff_greek[a_SM] = ">a";
	troff_greek[a_SM_AC] = ">'a";
	troff_greek[a_SM_GR] = ">`a";
	troff_greek[a_SM_CI] = ">~a";
	troff_greek[a_RO] = "<a";
	troff_greek[a_RO_AC] = "<'a";
	troff_greek[a_RO_GR] = "<`a";
	troff_greek[a_RO_CI] = "<~a";
	troff_greek[ALPHA] = "A";
	troff_greek[A_CI] = "~A";
	troff_greek[A_SM] = ">A";
	troff_greek[A_SM_AC] = ">'A";
	troff_greek[A_SM_GR] = ">`A";
	troff_greek[A_SM_CI] = ">~A";
	troff_greek[A_RO] = "<A";
	troff_greek[A_RO_AC] = "<'A";
	troff_greek[A_RO_GR] = "<`A";
	troff_greek[A_RO_CI] = "<~A";
	troff_greek[a_IS] = "|a";
	troff_greek[a_AC_IS] = "'|a";
	troff_greek[a_GR_IS] = "`|a";
	troff_greek[a_CI_IS] = "~|a";
	troff_greek[a_SM_IS] = ">|a";
	troff_greek[a_SM_AC_IS] = ">'|a";
	troff_greek[a_SM_GR_IS] = ">`|a";
	troff_greek[a_SM_CI_IS] = ">~|a";
	troff_greek[a_RO_IS] = "<|a";
	troff_greek[a_RO_AC_IS] = "<'|a";
	troff_greek[a_RO_GR_IS] = "<`|a";
	troff_greek[a_RO_CI_IS] = "<~|a";
	troff_greek[BETA] = "B";
	troff_greek[beta] = "b";
	troff_greek[GAMMA] = "G";
	troff_greek[gamma] = "g";
	troff_greek[DELTA] = "D";
	troff_greek[delta] = "d";
	troff_greek[EPSILON] = "E";
	troff_greek[epsilon] = "e";
	troff_greek[E_SM] = ">E";
	troff_greek[E_SM_AC] = ">'E";
	troff_greek[E_SM_GR] = ">`E";
	troff_greek[E_RO] = "<E";
	troff_greek[E_RO_AC] = "<'E";
	troff_greek[E_RO_GR] = "<`E";
	troff_greek[e_AC] = "'e";
	troff_greek[e_GR] = "`e";
	troff_greek[e_SM] = ">e";
	troff_greek[e_SM_AC] = ">'e";
	troff_greek[e_SM_GR] = ">`e";
	troff_greek[e_RO] = "<e";
	troff_greek[e_RO_AC] = "<'e";
	troff_greek[e_RO_GR] = "<`e";
	troff_greek[ZETA] = "Z";
	troff_greek[zeta] = "z";
	troff_greek[HTA] = "H";
	troff_greek[hta] = "h";
	troff_greek[H_AC] = "'H";
	troff_greek[H_GR] = "`H";
	troff_greek[H_CI] = "~H";
	troff_greek[H_SM] = ">H";
	troff_greek[H_SM_AC] = ">'H";
	troff_greek[H_SM_GR] = ">`H";
	troff_greek[H_SM_CI] = ">~H";
	troff_greek[H_RO] = "<H";
	troff_greek[H_RO_AC] = "<'H";
	troff_greek[H_RO_GR] = "<`H";
	troff_greek[H_RO_CI] = "<~H";
	troff_greek[h_AC] = "'h";
	troff_greek[h_GR] = "`h";
	troff_greek[h_CI] = "~h";
	troff_greek[h_SM] = ">h";
	troff_greek[h_SM_AC] = ">'h";
	troff_greek[h_SM_GR] = ">`h";
	troff_greek[h_SM_CI] = ">~h";
	troff_greek[h_RO] = "<h";
	troff_greek[h_RO_AC] = "<'h";
	troff_greek[h_RO_GR] = "<`h";
	troff_greek[h_RO_CI] = "<~h";
	troff_greek[h_IS] = "|h";
	troff_greek[h_AC_IS] = "'|h";
	troff_greek[h_GR_IS] = "`|h";
	troff_greek[h_CI_IS] = "~|h";
	troff_greek[h_SM_IS] = ">|h";
	troff_greek[h_SM_AC_IS] = ">'|h";
	troff_greek[h_SM_GR_IS] = ">`|h";
	troff_greek[h_SM_CI_IS] = ">~|h";
	troff_greek[h_RO_IS] = "<|h";
	troff_greek[h_RO_AC_IS] = "<'|h";
	troff_greek[h_RO_GR_IS] = "<`|h";
	troff_greek[h_RO_CI_IS] = "<~|h";
	troff_greek[QETA] = "Q";
	troff_greek[qeta] = "q";
	troff_greek[IOTA] = "I";
	troff_greek[iota] = "i";
	troff_greek[I_AC] = "'I";
	troff_greek[I_GR] = "`I";
	troff_greek[I_CI] = "~I";
	troff_greek[I_SM] = ">I";
	troff_greek[I_SM_AC] = ">'I";
	troff_greek[I_SM_GR] = ">`I";
	troff_greek[I_SM_CI] = ">~I";
	troff_greek[I_RO] = "<I";
	troff_greek[I_RO_AC] = "<'I";
	troff_greek[I_RO_GR] = "<`I";
	troff_greek[I_RO_CI] = "<~I";
	troff_greek[i_AC] = "'i";
	troff_greek[i_GR] = "`i";
	troff_greek[i_DI] = "+i";
	troff_greek[i_AC_DI] = "'+i";
	troff_greek[i_GR_DI] = "`+i";
	troff_greek[i_CI] = "~i";
	troff_greek[i_SM] = ">i";
	troff_greek[i_SM_AC] = ">'i";
	troff_greek[i_SM_GR] = ">`i";
	troff_greek[i_SM_CI] = ">~i";
	troff_greek[i_RO] = "<i";
	troff_greek[i_RO_AC] = "<'i";
	troff_greek[i_RO_GR] = "<`i";
	troff_greek[i_RO_CI] = "<~i";
	troff_greek[KAPPA] = "K";
	troff_greek[kappa] = "k";
	troff_greek[LAMBDA] = "L";
	troff_greek[lambda] = "l";
	troff_greek[MU] = "M";
	troff_greek[mu] = "m";
	troff_greek[NU] = "N";
	troff_greek[nu] = "n";
	troff_greek[CI] = "C";
	troff_greek[ci] = "c";
	troff_greek[OMICRON] = "O";
	troff_greek[omicron] = "o";
	troff_greek[o_AC] = "'o";
	troff_greek[o_GR] = "`o";
	troff_greek[o_SM] = ">o";
	troff_greek[o_SM_AC] = ">'o";
	troff_greek[o_SM_GR] = ">`o";
	troff_greek[o_RO] = "<o";
	troff_greek[o_RO_AC] = "<'o";
	troff_greek[o_RO_GR] = "<`o";
	troff_greek[O_AC] = "'O";
	troff_greek[O_GR] = "`O";
	troff_greek[O_SM] = ">O";
	troff_greek[O_SM_AC] = ">'O";
	troff_greek[O_SM_GR] = ">`O";
	troff_greek[O_RO] = "<O";
	troff_greek[O_RO_AC] = "<'O";
	troff_greek[O_RO_GR] = "<`O";
	troff_greek[PI] = "P";
	troff_greek[pi] = "p";
	troff_greek[RHO] = "R";
	troff_greek[R_SM] = ">R";
	troff_greek[R_RO] = "<R";
	troff_greek[rho] = "r";
	troff_greek[r_SM] = ">r";
	troff_greek[r_RO] = "<r";
	troff_greek[sigma] = "s";
	troff_greek[SIGMA] = "S";
	troff_greek[TAU] = "T";
	troff_greek[tau] = "t";
	troff_greek[UPSILON] = "U";
	troff_greek[upsilon] = "u";
	troff_greek[U_AC] = "'U";
	troff_greek[U_GR] = "`U";
	troff_greek[U_CI] = "~U";
	troff_greek[U_SM] = ">U";
	troff_greek[U_SM_AC] = ">'U";
	troff_greek[U_SM_GR] = ">`U";
	troff_greek[U_SM_CI] = ">~U";
	troff_greek[U_RO] = "<U";
	troff_greek[U_RO_AC] = "<'U";
	troff_greek[U_RO_GR] = "<`U";
	troff_greek[U_RO_CI] = "<~U";
	troff_greek[u_AC] = "'u";
	troff_greek[u_GR] = "`u";
	troff_greek[u_DI] = "+u";
	troff_greek[u_AC_DI] = "'+u";
	troff_greek[u_GR_DI] = "`+u";
	troff_greek[u_CI] = "~u";
	troff_greek[u_SM] = ">u";
	troff_greek[u_SM_AC] = ">'u";
	troff_greek[u_SM_GR] = ">`u";
	troff_greek[u_SM_CI] = ">~u";
	troff_greek[u_RO] = "<u";
	troff_greek[u_RO_AC] = "<'u";
	troff_greek[u_RO_GR] = "<`u";
	troff_greek[u_RO_CI] = "<~u";
	troff_greek[FI] = "F";
	troff_greek[fi] = "f";
	troff_greek[XI] = "X";
	troff_greek[xi] = "x";
	troff_greek[YI] = "Y";
	troff_greek[yi] = "y";
	troff_greek[WMEGA] = "W";
	troff_greek[wmega] = "w";
	troff_greek[W_AC] = "'W";
	troff_greek[W_GR] = "`W";
	troff_greek[W_CI] = "~W";
	troff_greek[W_SM] = ">W";
	troff_greek[W_SM_AC] = ">'W";
	troff_greek[W_SM_GR] = ">`W";
	troff_greek[W_SM_CI] = ">~W";
	troff_greek[W_RO] = "<W";
	troff_greek[W_RO_AC] = "<'W";
	troff_greek[W_RO_GR] = "<`W";
	troff_greek[W_RO_CI] = "<~W";
	troff_greek[w_AC] = "'w";
	troff_greek[w_GR] = "`w";
	troff_greek[w_CI] = "~w";
	troff_greek[w_SM] = ">w";
	troff_greek[w_SM_AC] = ">'w";
	troff_greek[w_SM_GR] = ">`w";
	troff_greek[w_SM_CI] = ">~w";
	troff_greek[w_RO] = "<w";
	troff_greek[w_RO_AC] = "<'w";
	troff_greek[w_RO_GR] = "<`w";
	troff_greek[w_RO_CI] = "<~w";
	troff_greek[w_IS] = "|w";
	troff_greek[w_AC_IS] = "'|w";
	troff_greek[w_GR_IS] = "`|a";
	troff_greek[w_CI_IS] = "~|w";
	troff_greek[w_SM_IS] = ">|w";
	troff_greek[w_SM_AC_IS] = ">'|w";
	troff_greek[w_SM_GR_IS] = ">`|w";
	troff_greek[w_SM_CI_IS] = ">~|w";
	troff_greek[w_RO_IS] = "<|w";
	troff_greek[w_RO_AC_IS] = "<'|w";
	troff_greek[w_RO_GR_IS] = "<`|w";
	troff_greek[w_RO_CI_IS] = "<~|w";

	troff_dgreek[a_AC] = "?'a";
	troff_dgreek[a_GR] = "?`a";
	troff_dgreek[a_CI] = "?~a";
	troff_dgreek[a_SM] = "?>a";
	troff_dgreek[a_SM_AC] = "?>'a";
	troff_dgreek[a_SM_GR] = "?>`a";
	troff_dgreek[a_SM_CI] = "?>~a";
	troff_dgreek[a_RO] = "?<a";
	troff_dgreek[a_RO_AC] = "?<'a";
	troff_dgreek[a_RO_GR] = "?<`a";
	troff_dgreek[a_RO_CI] = "?<~a";
	troff_dgreek[alpha] = "?a";
	troff_dgreek[ALPHA] = "?A";
	troff_dgreek[A_CI] = "?~A";
	troff_dgreek[A_SM] = "?>A";
	troff_dgreek[A_SM_AC] = "?>'A";
	troff_dgreek[A_SM_GR] = "?>`A";
	troff_dgreek[A_SM_CI] = "?>~A";
	troff_dgreek[A_RO] = "?<A";
	troff_dgreek[A_RO_AC] = "?<'A";
	troff_dgreek[A_RO_GR] = "?<`A";
	troff_dgreek[A_RO_CI] = "?<~A";
	troff_dgreek[a_IS] = "?|a";
	troff_dgreek[a_AC_IS] = "?'|a";
	troff_dgreek[a_GR_IS] = "?`|a";
	troff_dgreek[a_CI_IS] = "?~|a";
	troff_dgreek[a_SM_IS] = "?>|a";
	troff_dgreek[a_SM_AC_IS] = "?>'|a";
	troff_dgreek[a_SM_GR_IS] = "?>`|a";
	troff_dgreek[a_SM_CI_IS] = "?>~|a";
	troff_dgreek[a_RO_IS] = "?<|a";
	troff_dgreek[a_RO_AC_IS] = "?<'|a";
	troff_dgreek[a_RO_GR_IS] = "?<`|a";
	troff_dgreek[a_RO_CI_IS] = "?<~|a";
	troff_dgreek[beta] = "?b";
	troff_dgreek[BETA] = "?B";
	troff_dgreek[gamma] = "?g";
	troff_dgreek[GAMMA] = "?G";
	troff_dgreek[DELTA] = "?D";
	troff_dgreek[delta] = "?d";
	troff_dgreek[EPSILON] = "?E";
	troff_dgreek[epsilon] = "?e";
	troff_dgreek[E_SM] = "?>E";
	troff_dgreek[E_SM_AC] = "?>'E";
	troff_dgreek[E_SM_GR] = "?>`E";
	troff_dgreek[E_RO] = "?<E";
	troff_dgreek[E_RO_AC] = "?<'E";
	troff_dgreek[E_RO_GR] = "?<`E";
	troff_dgreek[e_AC] = "?'e";
	troff_dgreek[e_GR] = "?`e";
	troff_dgreek[e_SM] = "?>e";
	troff_dgreek[e_SM_AC] = "?>'e";
	troff_dgreek[e_SM_GR] = "?>`e";
	troff_dgreek[e_RO] = "?<e";
	troff_dgreek[e_RO_AC] = "?<'e";
	troff_dgreek[e_RO_GR] = "?<`e";
	troff_dgreek[ZETA] = "?Z";
	troff_dgreek[zeta] = "?z";
	troff_dgreek[HTA] = "?H";
	troff_dgreek[hta] = "?h";
	troff_dgreek[H_AC] = "?'H";
	troff_dgreek[H_GR] = "?`H";
	troff_dgreek[H_CI] = "?~H";
	troff_dgreek[H_SM] = "?>H";
	troff_dgreek[H_SM_AC] = "?>'H";
	troff_dgreek[H_SM_GR] = "?>`H";
	troff_dgreek[H_SM_CI] = "?>~H";
	troff_dgreek[H_RO] = "?<H";
	troff_dgreek[H_RO_AC] = "?<'H";
	troff_dgreek[H_RO_GR] = "?<`H";
	troff_dgreek[H_RO_CI] = "?<~H";
	troff_dgreek[h_AC] = "?'h";
	troff_dgreek[h_GR] = "?`h";
	troff_dgreek[h_CI] = "?~h";
	troff_dgreek[h_SM] = "?>h";
	troff_dgreek[h_SM_AC] = "?>'h";
	troff_dgreek[h_SM_GR] = "?>`h";
	troff_dgreek[h_SM_CI] = "?>~h";
	troff_dgreek[h_RO] = "?<h";
	troff_dgreek[h_RO_AC] = "?<'h";
	troff_dgreek[h_RO_GR] = "?<`h";
	troff_dgreek[h_RO_CI] = "?<~h";
	troff_dgreek[h_IS] = "?|h";
	troff_dgreek[h_AC_IS] = "?'|h";
	troff_dgreek[h_GR_IS] = "?`|h";
	troff_dgreek[h_CI_IS] = "?~|h";
	troff_dgreek[h_SM_IS] = "?>|h";
	troff_dgreek[h_SM_AC_IS] = "?>'|h";
	troff_dgreek[h_SM_GR_IS] = "?>`|h";
	troff_dgreek[h_SM_CI_IS] = "?>~|h";
	troff_dgreek[h_RO_IS] = "?<|h";
	troff_dgreek[h_RO_AC_IS] = "?<'|h";
	troff_dgreek[h_RO_GR_IS] = "?<`|h";
	troff_dgreek[h_RO_CI_IS] = "?<~|h";
	troff_dgreek[QETA] = "?Q";
	troff_dgreek[qeta] = "?q";
	troff_dgreek[IOTA] = "?I";
	troff_dgreek[iota] = "?i";
	troff_dgreek[I_AC] = "?'I";
	troff_dgreek[I_GR] = "?`I";
	troff_dgreek[I_CI] = "?~I";
	troff_dgreek[I_SM] = "?>I";
	troff_dgreek[I_SM_AC] = "?>'I";
	troff_dgreek[I_SM_GR] = "?>`I";
	troff_dgreek[I_SM_CI] = "?>~I";
	troff_dgreek[I_RO] = "?<I";
	troff_dgreek[I_RO_AC] = "?<'I";
	troff_dgreek[I_RO_GR] = "?<`I";
	troff_dgreek[I_RO_CI] = "?<~I";
	troff_dgreek[i_AC] = "?'i";
	troff_dgreek[i_GR] = "?`i";
	troff_dgreek[i_DI] = "?+i";
	troff_dgreek[i_AC_DI] = "?'+i";
	troff_dgreek[i_GR_DI] = "?`+i";
	troff_dgreek[i_CI] = "?~i";
	troff_dgreek[i_SM] = "?>i";
	troff_dgreek[i_SM_AC] = "?>'i";
	troff_dgreek[i_SM_GR] = "?>`i";
	troff_dgreek[i_SM_CI] = "?>~i";
	troff_dgreek[i_RO] = "?<i";
	troff_dgreek[i_RO_AC] = "?<'i";
	troff_dgreek[i_RO_GR] = "?<`i";
	troff_dgreek[i_RO_CI] = "?<~i";
	troff_dgreek[KAPPA] = "?K";
	troff_dgreek[kappa] = "?k";
	troff_dgreek[LAMBDA] = "?L";
	troff_dgreek[lambda] = "?l";
	troff_dgreek[MU] = "?M";
	troff_dgreek[mu] = "?m";
	troff_dgreek[NU] = "?N";
	troff_dgreek[nu] = "?n";
	troff_dgreek[CI] = "?C";
	troff_dgreek[ci] = "?c";
	troff_dgreek[OMICRON] = "?O";
	troff_dgreek[omicron] = "?o";
	troff_dgreek[o_AC] = "?'o";
	troff_dgreek[o_GR] = "?`o";
	troff_dgreek[o_SM] = "?>o";
	troff_dgreek[o_SM_AC] = "?>'o";
	troff_dgreek[o_SM_GR] = "?>`o";
	troff_dgreek[o_RO] = "?<o";
	troff_dgreek[o_RO_AC] = "?<'o";
	troff_dgreek[o_RO_GR] = "?<`o";
	troff_dgreek[O_AC] = "?'O";
	troff_dgreek[O_GR] = "?`O";
	troff_dgreek[O_SM] = "?>O";
	troff_dgreek[O_SM_AC] = "?>'O";
	troff_dgreek[O_SM_GR] = "?>`O";
	troff_dgreek[O_RO] = "?<O";
	troff_dgreek[O_RO_AC] = "?<'O";
	troff_dgreek[O_RO_GR] = "?<`O";
	troff_dgreek[PI] = "?P";
	troff_dgreek[pi] = "?p";
	troff_dgreek[RHO] = "?R";
	troff_dgreek[R_SM] = ">?R";
	troff_dgreek[R_RO] = "<?R";
	troff_dgreek[rho] = "?r";
	troff_dgreek[r_SM] = ">?r";
	troff_dgreek[r_RO] = "<?r";
	troff_dgreek[sigma] = "?s";
	troff_dgreek[SIGMA] = "?S";
	troff_dgreek[TAU] = "?T";
	troff_dgreek[tau] = "?t";
	troff_dgreek[UPSILON] = "?U";
	troff_dgreek[upsilon] = "?u";
	troff_dgreek[U_AC] = "?'U";
	troff_dgreek[U_GR] = "?`U";
	troff_dgreek[U_CI] = "?~U";
	troff_dgreek[U_SM] = "?>U";
	troff_dgreek[U_SM_AC] = "?>'U";
	troff_dgreek[U_SM_GR] = "?>`U";
	troff_dgreek[U_SM_CI] = "?>~U";
	troff_dgreek[U_RO] = "?<U";
	troff_dgreek[U_RO_AC] = "?<'U";
	troff_dgreek[U_RO_GR] = "?<`U";
	troff_dgreek[U_RO_CI] = "?<~U";
	troff_dgreek[u_AC] = "?'u";
	troff_dgreek[u_GR] = "?`u";
	troff_dgreek[u_DI] = "?+u";
	troff_dgreek[u_AC_DI] = "?'+u";
	troff_dgreek[u_GR_DI] = "?`+u";
	troff_dgreek[u_CI] = "?~u";
	troff_dgreek[u_SM] = "?>u";
	troff_dgreek[u_SM_AC] = "?>'u";
	troff_dgreek[u_SM_GR] = "?>`u";
	troff_dgreek[u_SM_CI] = "?>~u";
	troff_dgreek[u_RO] = "?<u";
	troff_dgreek[u_RO_AC] = "?<'u";
	troff_dgreek[u_RO_GR] = "?<`u";
	troff_dgreek[u_RO_CI] = "?<~u";
	troff_dgreek[FI] = "?F";
	troff_dgreek[fi] = "?f";
	troff_dgreek[XI] = "?X";
	troff_dgreek[xi] = "?x";
	troff_dgreek[YI] = "?Y";
	troff_dgreek[yi] = "?y";
	troff_dgreek[WMEGA] = "?W";
	troff_dgreek[wmega] = "?w";
	troff_dgreek[W_AC] = "?'W";
	troff_dgreek[W_GR] = "?`W";
	troff_dgreek[W_CI] = "?~W";
	troff_dgreek[W_SM] = "?>W";
	troff_dgreek[W_SM_AC] = "?>'W";
	troff_dgreek[W_SM_GR] = "?>`W";
	troff_dgreek[W_SM_CI] = "?>~W";
	troff_dgreek[W_RO] = "?<W";
	troff_dgreek[W_RO_AC] = "?<'W";
	troff_dgreek[W_RO_GR] = "?<`W";
	troff_dgreek[W_RO_CI] = "?<~W";
	troff_dgreek[w_AC] = "?'w";
	troff_dgreek[w_GR] = "?`w";
	troff_dgreek[w_CI] = "?~w";
	troff_dgreek[w_SM] = "?>w";
	troff_dgreek[w_SM_AC] = "?>'w";
	troff_dgreek[w_SM_GR] = "?>`w";
	troff_dgreek[w_SM_CI] = "?>~w";
	troff_dgreek[w_RO] = "?<w";
	troff_dgreek[w_RO_AC] = "?<'w";
	troff_dgreek[w_RO_GR] = "?<`w";
	troff_dgreek[w_RO_CI] = "?<~w";
	troff_dgreek[w_IS] = "?|w";
	troff_dgreek[w_AC_IS] = "?'|w";
	troff_dgreek[w_GR_IS] = "?`|a";
	troff_dgreek[w_CI_IS] = "?~|w";
	troff_dgreek[w_SM_IS] = "?>|w";
	troff_dgreek[w_SM_AC_IS] = "?>'|w";
	troff_dgreek[w_SM_GR_IS] = "?>`|w";
	troff_dgreek[w_SM_CI_IS] = "?>~|w";
	troff_dgreek[w_RO_IS] = "?<|w";
	troff_dgreek[w_RO_AC_IS] = "?<'|w";
	troff_dgreek[w_RO_GR_IS] = "?<`|w";
	troff_dgreek[w_RO_CI_IS] = "?<~|w";
	troff_dgreek[ELLIPSIS] = ".";
}

	char *troff_punct[] = {
		"\\(dg",	/* 0 dagger */
		"?",		/* 1 */
		"*",		/* 2 */
		"/",		/* 3 */
		"!",		/* 4 */
		"\\|",		/* 5 */
		"=",		/* 6 */
		"\\+",		/* 7 */
		"%%",		/* 8 '%' */
		"&",		/* 9 */
		":",		/* 10 */
		".",		/* 11 (should be) oversized period */
		"*",		/* 12 variant '*' */
		"\\(dg",	/* 13 should be double dagger */
		"\\(sc", 	/* 14 paragraph sign */
		"\\|",		/* 15 should be short vertical bar */
		"\\|",		/* 16 should be broken vertical bar */
		"\\|\\|",		/* 17 double vertical bar */
	};

char * troff_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"\\<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double bracket */
		"\\(Hb",/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * troff_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		"\\>",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double bracket */
		"\\(hb",/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * troff_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"\\'\\'",	/* 1 low double close quote */
		"\\'\\'",	/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"\\'",		/* 5 */
		"\"",		/* 6 */
};

char *troff_tgreek = "\\fg";
char *troff_tbgreek = "\\fg\\fD";
char *troff_troman = "\\fR";

char * troff_newline = "\n";

fix_troff_save(fname)
char * fname;
{
}

add_troff_header(f)
FILE * f;
{
}
