/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "filttab.h"

char * mact_greek[MAX_GK_CHARS];
char * mact_dgreek[MAX_GK_CHARS];

setup_mact_greek()
{
	mact_greek[alpha] = "a";
	mact_greek[a_SM_AC] = "&";
	mact_greek[a_SM_GR] = "(";
	mact_greek[a_SM_CI] = "*";
	mact_greek[a_RO_AC] = "'";
	mact_greek[a_RO_GR] = ")";
	mact_greek[a_RO_CI] = "+";
	mact_greek[a_AC] = "!";
	mact_greek[a_GR] = "\"";
	mact_greek[a_CI] = "#";
	mact_greek[a_SM] = "$";
	mact_greek[a_RO] = "%";
	mact_greek[a_SM_AC_IS] = "&i";
	mact_greek[a_SM_GR_IS] = "(i";
	mact_greek[a_SM_CI_IS] = "*i";
	mact_greek[a_RO_AC_IS] = "'i";
	mact_greek[a_RO_GR_IS] = ")i";
	mact_greek[a_RO_CI_IS] = "+i";
	mact_greek[a_IS] = "ai";
	mact_greek[a_AC_IS] = "!i";
	mact_greek[a_GR_IS] = "\"i";
	mact_greek[a_CI_IS] = "#i";
	mact_greek[a_SM_IS] = "$i";
	mact_greek[a_RO_IS] = "%i";
	mact_greek[ALPHA] = "A";
	mact_greek[A_SM_CI] = "{A";
	mact_greek[A_SM_AC] = "^A";
	mact_greek[A_SM_GR] = "`A";
	mact_greek[A_RO_CI] = "|A";
	mact_greek[A_RO_AC] = "_A";
	mact_greek[A_RO_GR] = "]@A";
	mact_greek[A_SM] = "\\A";
	mact_greek[A_RO] = "]A";
	mact_greek[A_CI] = "[A";
	mact_greek[beta] = "b";
	mact_greek[BETA] = "B";
	mact_greek[GAMMA] = "G";
	mact_greek[gamma] = "g";
	mact_greek[delta] = "d";
	mact_greek[DELTA] = "D";
	mact_greek[epsilon] = "e";
	mact_greek[EPSILON] = "E";
	mact_greek[e_SM_AC] = "0";
	mact_greek[e_SM_GR] = "2";
	mact_greek[e_RO_AC] = "1";
	mact_greek[e_RO_GR] = "3";
	mact_greek[e_AC] = ",";
	mact_greek[e_GR] = "-";
	mact_greek[e_SM] = ".";
	mact_greek[e_RO] = "/";
	mact_greek[E_SM_AC] = "^E";
	mact_greek[E_SM_GR] = "`E";
	mact_greek[E_RO_AC] = "_E";
	mact_greek[E_RO_GR] = "]@E";
	mact_greek[E_SM] = "\\E";
	mact_greek[E_RO] = "]E";
	mact_greek[hta] = "h";
	mact_greek[HTA] = "H";
	mact_greek[h_SM_AC] = "q";
	mact_greek[h_SM_GR] = "s";
	mact_greek[h_SM_CI] = "u";
	mact_greek[h_RO_AC] = "r";
	mact_greek[h_RO_GR] = "t";
	mact_greek[h_RO_CI] = "v";
	mact_greek[h_AC] = "l";
	mact_greek[h_GR] = "m";
	mact_greek[h_CI] = "n";
	mact_greek[h_SM] = "o";
	mact_greek[h_RO] = "p";
	mact_greek[H_SM_CI] = "{H";
	mact_greek[H_SM_AC] = "^H";
	mact_greek[H_SM_GR] = "`H";
	mact_greek[H_RO_CI] = "|H";
	mact_greek[H_RO_AC] = "_H";
	mact_greek[H_RO_GR] = "]@H";
	mact_greek[H_SM] = "\\H";
	mact_greek[H_RO] = "]H";
	mact_greek[H_AC] = "\033[m?\033[0;1mH";
	mact_greek[H_GR] = "@H";
	mact_greek[H_CI] = "[H";
	mact_greek[h_SM_AC_IS] = "qi";
	mact_greek[h_SM_GR_IS] = "si";
	mact_greek[h_SM_CI_IS] = "ui";
	mact_greek[h_RO_AC_IS] = "ri";
	mact_greek[h_RO_GR_IS] = "ti";
	mact_greek[h_RO_CI_IS] = "vi";
	mact_greek[h_IS] = "hi";
	mact_greek[h_AC_IS] = "li";
	mact_greek[h_GR_IS] = "mi";
	mact_greek[h_CI_IS] = "ni";
	mact_greek[h_SM_IS] = "oi";
	mact_greek[h_RO_IS] = "pi";
	mact_greek[zeta] = "z";
	mact_greek[ZETA] = "Z";
	mact_greek[qeta] = "q";
	mact_greek[QETA] = "Q";
	mact_greek[iota] = "i";
	mact_greek[IOTA] = "I";
	mact_greek[i_SM_AC] = "9";
	mact_greek[i_SM_GR] = ";";
	mact_greek[i_SM_CI] = "=";
	mact_greek[i_RO_AC] = ":";
	mact_greek[i_RO_GR] = "<";
	mact_greek[i_RO_CI] = ">";
	mact_greek[i_DI] = "i";
	mact_greek[i_AC_DI] = "4";	/* diaereses not available here*/
	mact_greek[i_GR_DI] = "5";
	mact_greek[i_AC] = "4";
	mact_greek[i_GR] = "5";
	mact_greek[i_CI] = "6";
	mact_greek[i_SM] = "7";
	mact_greek[i_RO] = "8";
	mact_greek[I_SM_CI] = "{I";
	mact_greek[I_SM_AC] = "^I";
	mact_greek[I_SM_GR] = "`I";
	mact_greek[I_RO_CI] = "|I";
	mact_greek[I_RO_AC] = "_I";
	mact_greek[I_RO_GR] = "]@I";
	mact_greek[I_SM] = "\\I";
	mact_greek[I_RO] = "]I";
	mact_greek[I_AC] = "\033[m?\033[0;1mI";
	mact_greek[I_GR] = "@I";
	mact_greek[I_CI] = "[I";
	mact_greek[kappa] = "k";
	mact_greek[KAPPA] = "K";
	mact_greek[lambda] = "l";
	mact_greek[LAMBDA] = "L";
	mact_greek[mu] = "m";
	mact_greek[MU] = "M";
	mact_greek[nu] = "n";
	mact_greek[NU] = "N";
	mact_greek[ci] = "c";
	mact_greek[CI] = "C";
	mact_greek[omicron] = "o";
	mact_greek[OMICRON] = "O";
	mact_greek[o_SM_AC] = "|";
	mact_greek[o_SM_GR] = "y";
	mact_greek[o_RO_AC] = "g";
	mact_greek[o_RO_GR] = "z";
	mact_greek[o_AC] = "}";
	mact_greek[o_GR] = "~";
	mact_greek[o_SM] = "f";
	mact_greek[o_RO] = "}";
	mact_greek[O_SM_AC] = "^O";
	mact_greek[O_SM_GR] = "`O";
	mact_greek[O_RO_AC] = "_O";
	mact_greek[O_RO_GR] = "]@O";
	mact_greek[O_SM] = "\\O";
	mact_greek[O_RO] = "]O";
	mact_greek[O_AC] = "\033[m?\033[0;1mO";
	mact_greek[O_GR] = "@O";
	mact_greek[pi] = "p";
	mact_greek[PI] = "P";
	mact_greek[RHO] = "R";
	mact_greek[R_SM] = "\\R";
	mact_greek[R_RO] = "]R";
	mact_greek[rho] = "r";
	mact_greek[r_RO] = "\033[0mb\033[1m";
	mact_greek[r_SM] = "\033[0mc\033[1m";
	mact_greek[SIGMA] = "S";
	mact_greek[sigma] = "s";
	mact_greek[tau] = "t";
	mact_greek[TAU] = "T";
	mact_greek[UPSILON] = "U";
	mact_greek[U_SM_CI] = "{U";
	mact_greek[U_SM_AC] = "^U";
	mact_greek[U_SM_GR] = "`U";
	mact_greek[U_RO_CI] = "|U";
	mact_greek[U_RO_AC] = "_U";
	mact_greek[U_RO_GR] = "]@U";
	mact_greek[U_SM] = "\\U";
	mact_greek[U_RO] = "]U";
	mact_greek[U_AC] = "\033[m?\033[0;1mU";
	mact_greek[U_GR] = "@U";
	mact_greek[U_CI] = "[U";
	mact_greek[upsilon] = "u";
	mact_greek[u_SM_AC] = "d";
	mact_greek[u_SM_GR] = "z";
	mact_greek[u_SM_CI] = "j";
	mact_greek[u_RO_AC] = "e";
	mact_greek[u_RO_GR] = "{";
	mact_greek[u_RO_CI] = "k";
	mact_greek[u_DI] = "u";		/* diaereses not available */
	mact_greek[u_AC_DI] = "{";
	mact_greek[u_GR_DI] = "`";
	mact_greek[u_AC] = "{";
	mact_greek[u_GR] = "`";
	mact_greek[u_CI] = "a";
	mact_greek[u_SM] = "b";
	mact_greek[u_RO] = "c";
	mact_greek[FI] = "F";
	mact_greek[fi] = "f";
	mact_greek[xi] = "x";
	mact_greek[XI] = "X";
	mact_greek[yi] = "y";
	mact_greek[YI] = "Y";
	mact_greek[wmega] = "w";
	mact_greek[WMEGA] = "W";
	mact_greek[w_SM_AC] = "\033[0mg\033[1m";
	mact_greek[w_SM_GR] = "\033[0mz\033[1m";
	mact_greek[w_SM_CI] = "\033[0m`\033[1m";
	mact_greek[w_RO_AC] = "\033[0my\033[1m";
	mact_greek[w_RO_GR] = "\033[0m{\033[1m";
	mact_greek[w_RO_CI] = "\033[0ma\033[1m";
	mact_greek[w_AC] = "w";
	mact_greek[w_GR] = "x";
	mact_greek[w_CI] = "\033[0mf\033[1m";
	mact_greek[w_SM] = "\033[0m}\033[1m";
	mact_greek[w_RO] = "\033[0m|\033[1m";
	mact_greek[W_SM_CI] = "{W";
	mact_greek[W_SM_AC] = "^W";
	mact_greek[W_SM_GR] = "`W";
	mact_greek[W_RO_CI] = "|W";
	mact_greek[W_RO_AC] = "_W";
	mact_greek[W_RO_GR] = "]@W";
	mact_greek[W_SM] = "\\W";
	mact_greek[W_RO] = "]W";
	mact_greek[W_AC] = "\033[m?\033[0;1mW";
	mact_greek[W_GR] = "@W";
	mact_greek[W_CI] = "[W";
	mact_greek[w_SM_AC_IS] = "\033[0mg\033[1mi";
	mact_greek[w_SM_GR_IS] = "\033[0mz\033[1mi";
	mact_greek[w_SM_CI_IS] = "\033[0m`\033[1mi";
	mact_greek[w_RO_AC_IS] = "\033[0my\033[1mi";
	mact_greek[w_RO_GR_IS] = "\033[0m{\033[1mi";
	mact_greek[w_RO_CI_IS] = "\033[0ma\033[1mi";
	mact_greek[w_IS] = "wi";
	mact_greek[w_AC_IS] = "wi";
	mact_greek[w_GR_IS] = "xi";
	mact_greek[w_CI_IS] = "\033[0mf\033[1mi";
	mact_greek[w_SM_IS] = "\033[0m}\033[1mi";
	mact_greek[w_RO_IS] = "\033[0m|\033[1mi";
	mact_greek[ELLIPSIS] = "\033[m.\033[0;1m";
	mact_dgreek[alpha] = "a\033[m?\033[0;1m";
	mact_dgreek[a_SM_AC] = "&\033[m?\033[0;1m";
	mact_dgreek[a_SM_GR] = "(\033[m?\033[0;1m";
	mact_dgreek[a_SM_CI] = "*\033[m?\033[0;1m";
	mact_dgreek[a_RO_AC] = "'\033[m?\033[0;1m";
	mact_dgreek[a_RO_GR] = ")\033[m?\033[0;1m";
	mact_dgreek[a_RO_CI] = "+\033[m?\033[0;1m";
	mact_dgreek[a_AC] = "!\033[m?\033[0;1m";
	mact_dgreek[a_GR] = "\"\033[m?\033[0;1m";
	mact_dgreek[a_CI] = "#\033[m?\033[0;1m";
	mact_dgreek[a_SM] = "$\033[m?\033[0;1m";
	mact_dgreek[a_RO] = "%\033[m?\033[0;1m";
	mact_dgreek[a_SM_GR_IS] = "(i\033[m?\033[0;1m";
	mact_dgreek[a_SM_CI_IS] = "*i\033[m?\033[0;1m";
	mact_dgreek[a_RO_AC_IS] = "'i\033[m?\033[0;1m";
	mact_dgreek[a_RO_GR_IS] = ")i\033[m?\033[0;1m";
	mact_dgreek[a_RO_CI_IS] = "+i\033[m?\033[0;1m";
	mact_dgreek[a_IS] = "a?i";
	mact_dgreek[a_AC_IS] = "!i\033[m?\033[0;1m";
	mact_dgreek[a_GR_IS] = "\"i\033[m?\033[0;1m";
	mact_dgreek[a_CI_IS] = "#i\033[m?\033[0;1m";
	mact_dgreek[a_SM_IS] = "$i\033[m?\033[0;1m";
	mact_dgreek[a_RO_IS] = "%i\033[m?\033[0;1m";
	mact_dgreek[A_SM_CI] = "{A";
	mact_dgreek[A_SM_AC] = "^A";
	mact_dgreek[A_SM_GR] = "`A\033[m?\033[0;1m";
	mact_dgreek[A_RO_CI] = "|A";
	mact_dgreek[A_RO_AC] = "_A";
	mact_dgreek[A_RO_GR] = "]@A\033[m?\033[0;1m";
	mact_dgreek[A_SM] = "\\A";
	mact_dgreek[A_RO] = "]A\033[m?\033[0;1m";
	mact_dgreek[A_CI] = "[A";
	mact_dgreek[beta] = "b\033[m?\033[0;1m";
	mact_dgreek[BETA] = "B\033[m?\033[0;1m";
	mact_dgreek[gamma] = "g\033[m?\033[0;1m";
	mact_dgreek[delta] = "d\033[m?\033[0;1m";
	mact_dgreek[DELTA] = "D\033[m?\033[0;1m";
	mact_dgreek[epsilon] = "e\033[m?\033[0;1m";
	mact_dgreek[EPSILON] = "E\033[m?\033[0;1m";
	mact_dgreek[e_SM_AC] = "0\033[m?\033[0;1m";
	mact_dgreek[e_SM_GR] = "2\033[m?\033[0;1m";
	mact_dgreek[e_RO_AC] = "1\033[m?\033[0;1m";
	mact_dgreek[e_RO_GR] = "3\033[m?\033[0;1m";
	mact_dgreek[e_AC] = ",\033[m?\033[0;1m";
	mact_dgreek[e_GR] = "-\033[m?\033[0;1m";
	mact_dgreek[e_SM] = ".\033[m?\033[0;1m";
	mact_dgreek[e_RO] = "/\033[m?\033[0;1m";
	mact_dgreek[E_SM_AC] = "^E";
	mact_dgreek[E_SM_GR] = "`E\033[m?\033[0;1m";
	mact_dgreek[E_RO_AC] = "_E";
	mact_dgreek[E_RO_GR] = "]@E\033[m?\033[0;1m";
	mact_dgreek[E_SM] = "\\E";
	mact_dgreek[E_RO] = "]E\033[m?\033[0;1m";
	mact_dgreek[hta] = "h\033[m?\033[0;1m";
	mact_dgreek[HTA] = "H\033[m?\033[0;1m";
	mact_dgreek[h_SM_AC] = "q\033[m?\033[0;1m";
	mact_dgreek[h_SM_GR] = "s\033[m?\033[0;1m";
	mact_dgreek[h_SM_CI] = "u\033[m?\033[0;1m";
	mact_dgreek[h_RO_AC] = "r\033[m?\033[0;1m";
	mact_dgreek[h_RO_GR] = "t\033[m?\033[0;1m";
	mact_dgreek[h_RO_CI] = "v\033[m?\033[0;1m";
	mact_dgreek[h_AC] = "l\033[m?\033[0;1m";
	mact_dgreek[h_GR] = "m\033[m?\033[0;1m";
	mact_dgreek[h_CI] = "n\033[m?\033[0;1m";
	mact_dgreek[h_SM] = "o\033[m?\033[0;1m";
	mact_dgreek[h_RO] = "p\033[m?\033[0;1m";
	mact_dgreek[H_SM_CI] = "{H";
	mact_dgreek[H_SM_AC] = "^H";
	mact_dgreek[H_SM_GR] = "`H\033[m?\033[0;1m";
	mact_dgreek[H_RO_CI] = "|H";
	mact_dgreek[H_RO_AC] = "_H";
	mact_dgreek[H_RO_GR] = "]@H\033[m?\033[0;1m";
	mact_dgreek[H_SM] = "\\H";
	mact_dgreek[H_RO] = "]H\033[m?\033[0;1m";
	mact_dgreek[H_AC] = "\033[m?\033[0;1mH";
	mact_dgreek[H_GR] = "@H";
	mact_dgreek[H_CI] = "[H";
	mact_dgreek[h_SM_AC_IS] = "qi\033[m?\033[0;1m";
	mact_dgreek[h_SM_GR_IS] = "si\033[m?\033[0;1m";
	mact_dgreek[h_SM_CI_IS] = "ui\033[m?\033[0;1m";
	mact_dgreek[h_RO_AC_IS] = "ri\033[m?\033[0;1m";
	mact_dgreek[h_RO_GR_IS] = "ti\033[m?\033[0;1m";
	mact_dgreek[h_RO_CI_IS] = "vi\033[m?\033[0;1m";
	mact_dgreek[h_AC_IS] = "li\033[m?\033[0;1m";
	mact_dgreek[h_IS] = "h?i";
	mact_dgreek[h_GR_IS] = "mi\033[m?\033[0;1m";
	mact_dgreek[h_CI_IS] = "ni\033[m?\033[0;1m";
	mact_dgreek[h_SM_IS] = "oi\033[m?\033[0;1m";
	mact_dgreek[h_RO_IS] = "pi\033[m?\033[0;1m";
	mact_dgreek[zeta] = "z\033[m?\033[0;1m";
	mact_dgreek[ZETA] = "Z\033[m?\033[0;1m";
	mact_dgreek[qeta] = "q\033[m?\033[0;1m";
	mact_dgreek[QETA] = "Q\033[m?\033[0;1m";
	mact_dgreek[iota] = "i\033[m?\033[0;1m";
	mact_dgreek[IOTA] = "I\033[m?\033[0;1m";
	mact_dgreek[i_SM_AC] = "9\033[m?\033[0;1m";
	mact_dgreek[i_SM_GR] = ";\033[m?\033[0;1m";
	mact_dgreek[i_SM_CI] = "=\033[m?\033[0;1m";
	mact_dgreek[i_RO_AC] = ":\033[m?\033[0;1m";
	mact_dgreek[i_RO_GR] = "<\033[m?\033[0;1m";
	mact_dgreek[i_RO_CI] = ">\033[m?\033[0;1m";
	mact_dgreek[i_AC] = "4\033[m?\033[0;1m";
	mact_dgreek[i_GR] = "5\033[m?\033[0;1m";
	mact_dgreek[i_CI] = "6\033[m?\033[0;1m";
	mact_dgreek[i_SM] = "7\033[m?\033[0;1m";
	mact_dgreek[i_RO] = "8\033[m?\033[0;1m";
	mact_dgreek[I_SM_CI] = "{I";
	mact_dgreek[I_SM_AC] = "^I";
	mact_dgreek[I_SM_GR] = "`I\033[m?\033[0;1m";
	mact_dgreek[I_RO_CI] = "|I";
	mact_dgreek[I_RO_AC] = "_I";
	mact_dgreek[I_RO_GR] = "]@I\033[m?\033[0;1m";
	mact_dgreek[I_SM] = "\\I";
	mact_dgreek[I_RO] = "]I\033[m?\033[0;1m";
	mact_dgreek[I_AC] = "\033[m?\033[0;1mI";
	mact_dgreek[I_GR] = "@I";
	mact_dgreek[I_CI] = "[I";
	mact_dgreek[kappa] = "k\033[m?\033[0;1m";
	mact_dgreek[KAPPA] = "K\033[m?\033[0;1m";
	mact_dgreek[lambda] = "l\033[m?\033[0;1m";
	mact_dgreek[LAMBDA] = "L\033[m?\033[0;1m";
	mact_dgreek[mu] = "m\033[m?\033[0;1m";
	mact_dgreek[MU] = "M\033[m?\033[0;1m";
	mact_dgreek[nu] = "n\033[m?\033[0;1m";
	mact_dgreek[NU] = "N\033[m?\033[0;1m";
	mact_dgreek[ci] = "c\033[m?\033[0;1m";
	mact_dgreek[CI] = "C\033[m?\033[0;1m";
	mact_dgreek[omicron] = "o\033[m?\033[0;1m";
	mact_dgreek[OMICRON] = "O\033[m?\033[0;1m";
	mact_dgreek[o_SM_AC] = "|\033[m?\033[0;1m";
	mact_dgreek[o_SM_GR] = "y\033[m?\033[0;1m";
	mact_dgreek[o_RO_AC] = "g\033[m?\033[0;1m";
	mact_dgreek[o_RO_GR] = "z\033[m?\033[0;1m";
	mact_dgreek[o_AC] = "}\033[m?\033[0;1m";
	mact_dgreek[o_GR] = "~\033[m?\033[0;1m";
	mact_dgreek[o_SM] = "f\033[m?\033[0;1m";
	mact_dgreek[o_RO] = "}\033[m?\033[0;1m";
	mact_dgreek[O_SM_AC] = "^O";
	mact_dgreek[O_SM_GR] = "`O\033[m?\033[0;1m";
	mact_dgreek[O_RO_AC] = "_O";
	mact_dgreek[O_RO_GR] = "]@O\033[m?\033[0;1m";
	mact_dgreek[O_SM] = "\\O";
	mact_dgreek[O_RO] = "]O\033[m?\033[0;1m";
	mact_dgreek[O_AC] = "\033[m?\033[0;1mO";
	mact_dgreek[O_GR] = "@O";
	mact_dgreek[pi] = "p\033[m?\033[0;1m";
	mact_dgreek[PI] = "P\033[m?\033[0;1m";
	mact_dgreek[RHO] = "R\033[m?\033[0;1m";
	mact_dgreek[R_SM] = "\\R\033[m?\033[0;1m";
	mact_dgreek[R_RO] = "]R\033[m?\033[0;1m";
	mact_dgreek[rho] = "r\033[m?\033[0;1m";
	mact_dgreek[r_RO] = "\033[0mb\033[1m\033[m?\033[0;1m";
	mact_dgreek[r_SM] = "\033[0mc\033[1m\033[m?\033[0;1m";
	mact_dgreek[SIGMA] = "S\033[m?\033[0;1m";
	mact_dgreek[sigma] = "s\033[m?\033[0;1m";
	mact_dgreek[tau] = "t\033[m?\033[0;1m";
	mact_dgreek[TAU] = "T\033[m?\033[0;1m";
	mact_dgreek[UPSILON] = "U\033[m?\033[0;1m";
	mact_dgreek[U_SM_CI] = "{U\033[m?\033[0;1m";
	mact_dgreek[U_SM_AC] = "^U\033[m?\033[0;1m";
	mact_dgreek[U_SM_GR] = "`U\033[m?\033[0;1m";
	mact_dgreek[U_RO_CI] = "|U\033[m?\033[0;1m";
	mact_dgreek[U_RO_AC] = "_U\033[m?\033[0;1m";
	mact_dgreek[U_RO_GR] = "]@U\033[m?\033[0;1m";
	mact_dgreek[U_SM] = "\\U\033[m?\033[0;1m";
	mact_dgreek[U_RO] = "]U\033[m?\033[0;1m";
	mact_dgreek[U_AC] = "\033[m?\033[0;1mU\033[m?\033[0;1m";
	mact_dgreek[U_GR] = "@U\033[m?\033[0;1m";
	mact_dgreek[U_CI] = "[U\033[m?\033[0;1m";
	mact_dgreek[upsilon] = "u\033[m?\033[0;1m";
	mact_dgreek[u_SM_AC] = "d\033[m?\033[0;1m";
	mact_dgreek[u_SM_GR] = "z\033[m?\033[0;1m";
	mact_dgreek[u_SM_CI] = "j\033[m?\033[0;1m";
	mact_dgreek[u_RO_AC] = "e\033[m?\033[0;1m";
	mact_dgreek[u_RO_GR] = "{\033[m?\033[0;1m";
	mact_dgreek[u_RO_CI] = "k\033[m?\033[0;1m";
	mact_dgreek[u_AC] = "{\033[m?\033[0;1m";
	mact_dgreek[u_GR] = "`\033[m?\033[0;1m";
	mact_dgreek[u_CI] = "a\033[m?\033[0;1m";
	mact_dgreek[u_SM] = "b\033[m?\033[0;1m";
	mact_dgreek[u_RO] = "c\033[m?\033[0;1m";
	mact_dgreek[FI] = "F\033[m?\033[0;1m";
	mact_dgreek[fi] = "f\033[m?\033[0;1m";
	mact_dgreek[xi] = "x\033[m?\033[0;1m";
	mact_dgreek[XI] = "X\033[m?\033[0;1m";
	mact_dgreek[yi] = "y\033[m?\033[0;1m";
	mact_dgreek[YI] = "Y\033[m?\033[0;1m";
	mact_dgreek[wmega] = "w\033[m?\033[0;1m";
	mact_dgreek[WMEGA] = "W\033[m?\033[0;1m";
	mact_dgreek[w_SM_AC] = "\033[0mg\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_SM_GR] = "\033[0mz\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_SM_CI] = "\033[0m`\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_RO_AC] = "\033[0my\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_RO_GR] = "\033[0m{\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_RO_CI] = "\033[0ma\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_AC] = "w\033[m?\033[0;1m";
	mact_dgreek[w_GR] = "x\033[m?\033[0;1m";
	mact_dgreek[w_CI] = "\033[0mf\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_SM] = "\033[0m}\033[1m\033[m?\033[0;1m";
	mact_dgreek[w_RO] = "\033[0m|\033[1m\033[m?\033[0;1m";
	mact_dgreek[W_SM_CI] = "{w";
	mact_dgreek[W_SM_AC] = "^w";
	mact_dgreek[W_SM_GR] = "`w\033[m?\033[0;1m";
	mact_dgreek[W_RO_CI] = "|w";
	mact_dgreek[W_RO_AC] = "_w";
	mact_dgreek[W_RO_GR] = "]@w\033[m?\033[0;1m";
	mact_dgreek[W_SM] = "\\w";
	mact_dgreek[W_RO] = "]w\033[m?\033[0;1m";
	mact_dgreek[W_AC] = "\033[m?\033[0;1mw";
	mact_dgreek[W_GR] = "@w";
	mact_dgreek[W_CI] = "[w";
	mact_dgreek[w_SM_AC_IS] = "\033[0mg\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_SM_GR_IS] = "\033[0mz\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_SM_CI_IS] = "\033[0m`\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_RO_AC_IS] = "\033[0my\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_RO_GR_IS] = "\033[0m{\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_RO_CI_IS] = "\033[0ma\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_AC_IS] = "wi\033[m?\033[0;1m";
	mact_dgreek[w_GR_IS] = "xi\033[m?\033[0;1m";
	mact_dgreek[w_CI_IS] = "\033[0mf\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_SM_IS] = "\033[0m}\033[1mi\033[m?\033[0;1m";
	mact_dgreek[w_RO_IS] = "\033[0m|\033[1mi\033[m?\033[0;1m";
	mact_dgreek[ELLIPSIS] = "\033[m.\033[0;1m";
}

	char *mact_punct[] = {
		"\033[0mn\033[1m", /* 0 dagger */
		"\033[m?\033[0;1m",		/* 1 */
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
		"\033[0mn\033[1m", /* 13 (should be) double dagger */
		"\033[0m(Sect)\033[1m", 	/* 14 paragraph sign */
		"|",		/* 15 should be short vertical bar */
		"|",		/* 16 should be broken vertical bar */
		"||",	/* 17 double vertical bar */
	};
		
char * mact_lbrackets[] = {
		"[",	/* left square bracket */
		"(", 	/* left paren */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double brackets */
		"|_",	/* left half brackets */
};

char * mact_rbrackets[] = {
		"]",	/* right square bracket */
		")", 	/* right paren */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double brackets */
		"_|",	/* right half brackets */
};

char * mact_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"''",		/* 1 low double close quote */
		"''",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *mact_tgreek = "\033[0;1m";
char *mact_tbgreek = "\033[7m";
char *mact_troman = "\033[m\17";

char * mact_newline = "\n";

fix_mact_save(fname)
char * fname;
{
}

add_mact_header(f)
FILE * f;
{
}
