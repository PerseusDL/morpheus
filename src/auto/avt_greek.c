/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "filttab.h"

char * avt_greek[MAX_GK_CHARS];
char * avt_dgreek[MAX_GK_CHARS];

setup_avt_greek()
{
	avt_greek[alpha] = "a";
	avt_greek[a_AC] = "a\b'";
	avt_greek[a_GR] = "a\b`";
	avt_greek[a_CI] = "a\b~";
	avt_greek[a_SM] = "a\b)";
	avt_greek[a_SM_AC] = "a\b&";
	avt_greek[a_SM_GR] = "a\b*";
	avt_greek[a_SM_CI] = "a\b^";
	avt_greek[a_RO] = "a\b(";
	avt_greek[a_RO_AC] = "a\b$";
	avt_greek[a_RO_GR] = "a\b%";
	avt_greek[a_RO_CI] = "a\b#";
	avt_greek[ALPHA] = "A";
	avt_greek[A_CI] = ".\b~A";
	avt_greek[A_SM] = ".\b)A";
	avt_greek[A_SM_AC] = ".\b&A";
	avt_greek[A_SM_GR] = ".\b*A";
	avt_greek[A_SM_CI] = ".\b^A";
	avt_greek[A_RO] = ".\b(A";
	avt_greek[A_RO_AC] = ".\b$A";
	avt_greek[A_RO_GR] = ".\b%A";
	avt_greek[A_RO_CI] = ".\b#A";
	avt_greek[a_IS] = "{";
	avt_greek[a_AC_IS] = "{\b'";
	avt_greek[a_GR_IS] = "{\b`";
	avt_greek[a_CI_IS] = "{\b~";
	avt_greek[a_SM_IS] = "{\b)";
	avt_greek[a_SM_AC_IS] = "{\b&";
	avt_greek[a_SM_GR_IS] = "{\b*";
	avt_greek[a_SM_CI_IS] = "{\b^";
	avt_greek[a_RO_IS] = "{\b(";
	avt_greek[a_RO_AC_IS] = "{\b$";
	avt_greek[a_RO_GR_IS] = "{\b%";
	avt_greek[a_RO_CI_IS] = "{\b#";
	avt_greek[beta] = "b";
	avt_greek[BETA] = "B";
	avt_greek[GAMMA] = "G";
	avt_greek[gamma] = "g";
	avt_greek[DELTA] = "D";
	avt_greek[delta] = "d";
	avt_greek[EPSILON] = "E";
	avt_greek[epsilon] = "e";
	avt_greek[E_SM] = ".\b)E";
	avt_greek[E_SM_AC] = ".\b&E";
	avt_greek[E_SM_GR] = ".\b*E";
	avt_greek[E_RO] = ".\b(E";
	avt_greek[E_RO_AC] = ".\b$E";
	avt_greek[E_RO_GR] = ".\b%E";
	avt_greek[e_AC] = "e\b'";
	avt_greek[e_GR] = "e\b`";
	avt_greek[e_SM] = "e\b)";
	avt_greek[e_SM_AC] = "e\b&";
	avt_greek[e_SM_GR] = "e\b*";
	avt_greek[e_RO] = "e\b(";
	avt_greek[e_RO_AC] = "e\b$";
	avt_greek[e_RO_GR] = "e\b%";
	avt_greek[ZETA] = "Z";
	avt_greek[zeta] = "z";
	avt_greek[HTA] = "H";
	avt_greek[hta] = "h";
	avt_greek[H_AC] = ".\b'H";
	avt_greek[H_GR] = ".\b`H";
	avt_greek[H_CI] = ".\b~H";
	avt_greek[H_SM] = ".\b)H";
	avt_greek[H_SM_AC] = ".\b&H";
	avt_greek[H_SM_GR] = ".\b*H";
	avt_greek[H_SM_CI] = ".\b^H";
	avt_greek[H_RO] = ".\b(H";
	avt_greek[H_RO_AC] = ".\b$H";
	avt_greek[H_RO_GR] = ".\b%H";
	avt_greek[H_RO_CI] = ".\b#H";
	avt_greek[h_AC] = "h\b'";
	avt_greek[h_GR] = "h\b`";
	avt_greek[h_CI] = "h\b~";
	avt_greek[h_SM] = "h\b)";
	avt_greek[h_SM_AC] = "h\b&";
	avt_greek[h_SM_GR] = "h\b*";
	avt_greek[h_SM_CI] = "h\b^";
	avt_greek[h_RO] = "h\b(";
	avt_greek[h_RO_AC] = "h\b$";
	avt_greek[h_RO_GR] = "h\b%";
	avt_greek[h_RO_CI] = "h\b#";
	avt_greek[h_IS] = "|";
	avt_greek[h_AC_IS] = "|\b'";
	avt_greek[h_GR_IS] = "|\b`";
	avt_greek[h_CI_IS] = "|\b~";
	avt_greek[h_SM_IS] = "|\b)";
	avt_greek[h_SM_AC_IS] = "|\b&";
	avt_greek[h_SM_GR_IS] = "|\b*";
	avt_greek[h_SM_CI_IS] = "|\b^";
	avt_greek[h_RO_IS] = "|\b(";
	avt_greek[h_RO_AC_IS] = "|\b$";
	avt_greek[h_RO_GR_IS] = "|\b%";
	avt_greek[h_RO_CI_IS] = "|\b#";
	avt_greek[QETA] = "Q";
	avt_greek[qeta] = "q";
	avt_greek[IOTA] = "I";
	avt_greek[iota] = "i";
	avt_greek[I_AC] = ".\b'I";
	avt_greek[I_GR] = ".\b`I";
	avt_greek[I_CI] = ".\b~I";
	avt_greek[I_SM] = ".\b)I";
	avt_greek[I_SM_AC] = ".\b&I";
	avt_greek[I_SM_GR] = ".\b*I";
	avt_greek[I_SM_CI] = ".\b^I";
	avt_greek[I_RO] = ".\b(I";
	avt_greek[I_RO_AC] = ".\b$I";
	avt_greek[I_RO_GR] = ".\b%I";
	avt_greek[I_RO_CI] = ".\b#I";
	avt_greek[i_AC] = "i\b'";
	avt_greek[i_GR] = "i\b`";
	avt_greek[i_DI] = "i\b!";
	avt_greek[i_AC_DI] = "i\bA";
	avt_greek[i_GR_DI] = "i\bB";
	avt_greek[i_CI] = "i\b~";
	avt_greek[i_SM] = "i\b)";
	avt_greek[i_SM_AC] = "i\b&";
	avt_greek[i_SM_GR] = "i\b*";
	avt_greek[i_SM_CI] = "i\b^";
	avt_greek[i_RO] = "i\b(";
	avt_greek[i_RO_AC] = "i\b$";
	avt_greek[i_RO_GR] = "i\b%";
	avt_greek[i_RO_CI] = "i\b#";
	avt_greek[KAPPA] = "K";
	avt_greek[kappa] = "k";
	avt_greek[LAMBDA] = "L";
	avt_greek[lambda] = "l";
	avt_greek[MU] = "M";
	avt_greek[mu] = "m";
	avt_greek[NU] = "N";
	avt_greek[nu] = "n";
	avt_greek[CI] = "C";
	avt_greek[ci] = "c";
	avt_greek[OMICRON] = "O";
	avt_greek[omicron] = "o";
	avt_greek[o_AC] = "o\b'";
	avt_greek[o_GR] = "o\b`";
	avt_greek[o_SM] = "o\b)";
	avt_greek[o_SM_AC] = "o\b&";
	avt_greek[o_SM_GR] = "o\b*";
	avt_greek[o_RO] = "o\b(";
	avt_greek[o_RO_AC] = "o\b$";
	avt_greek[o_RO_GR] = "o\b%";
	avt_greek[O_AC] = ".\b'O";
	avt_greek[O_GR] = ".\b`O";
	avt_greek[O_SM] = ".\b)O";
	avt_greek[O_SM_AC] = ".\b&O";
	avt_greek[O_SM_GR] = ".\b*O";
	avt_greek[O_RO] = ".\b(O";
	avt_greek[O_RO_AC] = ".\b$O";
	avt_greek[O_RO_GR] = ".\b%O";
	avt_greek[pi] = "p";
	avt_greek[PI] = "P";
	avt_greek[RHO] = "R";
	avt_greek[R_SM] = ".\b)R";
	avt_greek[R_RO] = ".\b(R";
	avt_greek[rho] = "r";
	avt_greek[r_SM] = "r\b)";
	avt_greek[r_RO] = "r\b(";
	avt_greek[sigma] = "j";
	avt_greek[SIGMA] = "J";
	avt_greek[TAU] = "T";
	avt_greek[tau] = "t";
	avt_greek[UPSILON] = "U";
	avt_greek[upsilon] = "u";
	avt_greek[U_AC] = ".\b'U";
	avt_greek[U_GR] = ".\b`U";
	avt_greek[U_CI] = ".\b~U";
	avt_greek[U_SM] = ".\b)U";
	avt_greek[U_SM_AC] = ".\b&U";
	avt_greek[U_SM_GR] = ".\b*U";
	avt_greek[U_SM_CI] = ".\b^U";
	avt_greek[U_RO] = ".\b(U";
	avt_greek[U_RO_AC] = ".\b$U";
	avt_greek[U_RO_GR] = ".\b%U";
	avt_greek[U_RO_CI] = ".\b#U";
	avt_greek[u_AC] = "u\b'";
	avt_greek[u_GR] = "u\b`";
	avt_greek[u_DI] = "u\b!";
	avt_greek[u_AC_DI] = "u\bA";
	avt_greek[u_GR_DI] = "u\bB";
	avt_greek[u_CI] = "u\b~";
	avt_greek[u_SM] = "u\b)";
	avt_greek[u_SM_AC] = "u\b&";
	avt_greek[u_SM_GR] = "u\b*";
	avt_greek[u_SM_CI] = "u\b^";
	avt_greek[u_RO] = "u\b(";
	avt_greek[u_RO_AC] = "u\b$";
	avt_greek[u_RO_GR] = "u\b%";
	avt_greek[u_RO_CI] = "u\b#";
	avt_greek[FI] = "F";
	avt_greek[fi] = "f";
	avt_greek[XI] = "X";
	avt_greek[xi] = "x";
	avt_greek[YI] = "Y";
	avt_greek[yi] = "y";
	avt_greek[WMEGA] = "W";
	avt_greek[wmega] = "w";
	avt_greek[W_AC] = ".\b'W";
	avt_greek[W_GR] = ".\b`W";
	avt_greek[W_CI] = ".\b~W";
	avt_greek[W_SM] = ".\b)W";
	avt_greek[W_SM_AC] = ".\b&W";
	avt_greek[W_SM_GR] = ".\b*W";
	avt_greek[W_SM_CI] = ".\b^W";
	avt_greek[W_RO] = ".\b(W";
	avt_greek[W_RO_AC] = ".\b$W";
	avt_greek[W_RO_GR] = ".\b%W";
	avt_greek[W_RO_CI] = ".\b#W";
	avt_greek[w_AC] = "w\b'";
	avt_greek[w_GR] = "w\b`";
	avt_greek[w_CI] = "w\b~";
	avt_greek[w_SM] = "w\b)";
	avt_greek[w_SM_AC] = "w\b&";
	avt_greek[w_SM_GR] = "w\b*";
	avt_greek[w_SM_CI] = "w\b^";
	avt_greek[w_RO] = "w\b(";
	avt_greek[w_RO_AC] = "w\b$";
	avt_greek[w_RO_GR] = "w\b%";
	avt_greek[w_RO_CI] = "w\b#";
	avt_greek[w_IS] = "}";
	avt_greek[w_AC_IS] = "}\b'";
	avt_greek[w_GR_IS] = "}\b`";
	avt_greek[w_CI_IS] = "}\b~";
	avt_greek[w_SM_IS] = "}\b)";
	avt_greek[w_SM_AC_IS] = "}\b&";
	avt_greek[w_SM_GR_IS] = "}\b*";
	avt_greek[w_SM_CI_IS] = "}\b^";
	avt_greek[w_RO_IS] = "}\b(";
	avt_greek[w_RO_AC_IS] = "}\b$";
	avt_greek[w_RO_GR_IS] = "}\b%";
	avt_greek[w_RO_CI_IS] = "}\b#";
	avt_greek[ELLIPSIS] = "\17.\16";


	avt_dgreek[alpha] = "a\b.";
	avt_dgreek[a_AC] = "a\b\"";
	avt_dgreek[a_GR] = "a\b\\";
	avt_dgreek[a_CI] = "a\b|";
	avt_dgreek[a_SM] = "a\b0";
	avt_dgreek[a_SM_AC] = "a\b7";
	avt_dgreek[a_SM_GR] = "a\b8";
	avt_dgreek[a_SM_CI] = "a\b6";
	avt_dgreek[a_RO] = "a\b9";
	avt_dgreek[a_RO_AC] = "a\b4";
	avt_dgreek[a_RO_GR] = "a\b5";
	avt_dgreek[a_RO_CI] = "a\b3";
	avt_dgreek[ALPHA] = "A\b.";
	avt_dgreek[A_CI] = ".\b~A\b.";
	avt_dgreek[A_SM] = ".\b)A\b.";
	avt_dgreek[A_SM_AC] = ".\b&A\b.";
	avt_dgreek[A_SM_GR] = ".\b*A\b.";
	avt_dgreek[A_SM_CI] = ".\b^A\b.";
	avt_dgreek[A_RO] = ".\b(A\b.";
	avt_dgreek[A_RO_AC] = ".\b$A\b.";
	avt_dgreek[A_RO_GR] = ".\b%A\b.";
	avt_dgreek[A_RO_CI] = ".\b^A\b.";
	avt_dgreek[a_IS] = "{";
	avt_dgreek[a_AC_IS] = "{\b\"";
	avt_dgreek[a_GR_IS] = "{\b\\";
	avt_dgreek[a_CI_IS] = "{\b|";
	avt_dgreek[a_SM_IS] = "{\b0";
	avt_dgreek[a_SM_AC_IS] = "{\b7";
	avt_dgreek[a_SM_GR_IS] = "{\b8";
	avt_dgreek[a_SM_CI_IS] = "{\b6";
	avt_dgreek[a_RO_IS] = "{\b9";
	avt_dgreek[a_RO_AC_IS] = "{\b4";
	avt_dgreek[a_RO_GR_IS] = "{\b5";
	avt_dgreek[a_RO_CI_IS] = "{\b3";
	avt_dgreek[beta] = "b\b.";
	avt_dgreek[BETA] = "B\b.";
	avt_dgreek[gamma] = "\033Q\27\033R";
	avt_dgreek[GAMMA] = "G\b.";
	avt_dgreek[delta] = "d\b.";
	avt_dgreek[DELTA] = "D\b.";
	avt_dgreek[epsilon] = "e\b.";
	avt_dgreek[EPSILON] = "E\b.";
	avt_dgreek[E_SM] = ".\b)E\b.";
	avt_dgreek[E_SM_AC] = ".\b&E\b.";
	avt_dgreek[E_SM_GR] = ".\b*E\b.";
	avt_dgreek[E_RO] = ".\b(E\b.";
	avt_dgreek[E_RO_AC] = ".\b$E\b.";
	avt_dgreek[E_RO_GR] = ".\b%E\b.";
	avt_dgreek[e_AC] = "e\b\"";
	avt_dgreek[e_GR] = "e\b\\";
	avt_dgreek[e_SM] = "e\b0";
	avt_dgreek[e_SM_AC] = "e\b7";
	avt_dgreek[e_SM_GR] = "e\b8";
	avt_dgreek[e_RO] = "e\b9";
	avt_dgreek[e_RO_AC] = "e\b4";
	avt_dgreek[e_RO_GR] = "e\b5";
	avt_dgreek[ZETA] = "Z\b.";
	avt_dgreek[zeta] = "\033Q\32\033R";
	avt_dgreek[HTA] = "H\b.";
	avt_dgreek[hta] = "h\b.";
	avt_dgreek[H_AC] = ".\b'H\b.";
	avt_dgreek[H_GR] = ".\b`H\b.";
	avt_dgreek[H_CI] = ".\b~H\b.";
	avt_dgreek[H_SM] = ".\b)H\b.";
	avt_dgreek[H_SM_AC] = ".\b&H\b.";
	avt_dgreek[H_SM_GR] = ".\b*H\b.";
	avt_dgreek[H_SM_CI] = ".\b^H\b.";
	avt_dgreek[H_RO] = ".\b(H\b.";
	avt_dgreek[H_RO_AC] = ".\b$H\b.";
	avt_dgreek[H_RO_GR] = ".\b%H\b.";
	avt_dgreek[H_RO_CI] = ".\b#H\b.";
	avt_dgreek[h_AC] = "h\b\"";
	avt_dgreek[h_GR] = "h\b\\";
	avt_dgreek[h_CI] = "h\b|";
	avt_dgreek[h_SM] = "h\b0";
	avt_dgreek[h_SM_AC] = "h\b7";
	avt_dgreek[h_SM_GR] = "h\b8";
	avt_dgreek[h_SM_CI] = "h\b6";
	avt_dgreek[h_RO] = "h\b9";
	avt_dgreek[h_RO_AC] = "h\b4";
	avt_dgreek[h_RO_GR] = "h\b5";
	avt_dgreek[h_RO_CI] = "h\b3";
	avt_dgreek[h_IS] = "|";
	avt_dgreek[h_AC_IS] = "|\b\"";
	avt_dgreek[h_GR_IS] = "|\b\\";
	avt_dgreek[h_CI_IS] = "|\b|";
	avt_dgreek[h_SM_IS] = "|\b0";
	avt_dgreek[h_SM_AC_IS] = "|\b7";
	avt_dgreek[h_SM_GR_IS] = "|\b8";
	avt_dgreek[h_SM_CI_IS] = "|\b6";
	avt_dgreek[h_RO_IS] = "|\b9";
	avt_dgreek[h_RO_AC_IS] = "|\b4";
	avt_dgreek[h_RO_GR_IS] = "|\b5";
	avt_dgreek[h_RO_CI_IS] = "|\b3";
	avt_dgreek[QETA] = "Q\b.";
	avt_dgreek[qeta] = "q\b.";
	avt_dgreek[IOTA] = "I\b.";
	avt_dgreek[iota] = "i\b.";
	avt_dgreek[I_AC] = ".\b'I\b.";
	avt_dgreek[I_GR] = ".\b`I\b.";
	avt_dgreek[I_CI] = ".\b~I\b.";
	avt_dgreek[I_SM] = ".\b)I\b.";
	avt_dgreek[I_SM_AC] = ".\b&I\b.";
	avt_dgreek[I_SM_GR] = ".\b*I\b.";
	avt_dgreek[I_SM_CI] = ".\b^I\b.";
	avt_dgreek[I_RO] = ".\b(I\b.";
	avt_dgreek[I_RO_AC] = ".\b$I\b.";
	avt_dgreek[I_RO_GR] = ".\b%I\b.";
	avt_dgreek[I_RO_CI] = ".\b#I\b.";
	avt_dgreek[i_AC] = "i\b\"";
	avt_dgreek[i_GR] = "i\b\\";
	avt_dgreek[i_DI] = "i\b!";
	avt_dgreek[i_AC_DI] = "i\bA\b.";
	avt_dgreek[i_GR_DI] = "i\bB\b.";
	avt_dgreek[i_CI] = "i\b|";
	avt_dgreek[i_SM] = "i\b0";
	avt_dgreek[i_SM_AC] = "i\b7";
	avt_dgreek[i_SM_GR] = "i\b8";
	avt_dgreek[i_SM_CI] = "i\b6";
	avt_dgreek[i_RO] = "i\b9";
	avt_dgreek[i_RO_AC] = "i\b4";
	avt_dgreek[i_RO_GR] = "i\b5";
	avt_dgreek[i_RO_CI] = "i\b3";
	avt_dgreek[KAPPA] = "K\b.";
	avt_dgreek[kappa] = "k\b.";
	avt_dgreek[LAMBDA] = "L\b.";
	avt_dgreek[lambda] = "l\b.";
	avt_dgreek[MU] = "M\b.";
	avt_dgreek[mu] = "m\b.";
	avt_dgreek[NU] = "N\b.";
	avt_dgreek[nu] = "n\b.";
	avt_dgreek[CI] = "C\b.";
	avt_dgreek[ci] = "C\b.";
	avt_dgreek[OMICRON] = "O\b.";
	avt_dgreek[omicron] = "o\b.";
	avt_dgreek[o_AC] = "o\b\"";
	avt_dgreek[o_GR] = "o\b\\";
	avt_dgreek[o_SM] = "o\b0";
	avt_dgreek[o_SM_AC] = "o\b7";
	avt_dgreek[o_SM_GR] = "o\b8";
	avt_dgreek[o_RO] = "o\b9";
	avt_dgreek[o_RO_AC] = "o\b4";
	avt_dgreek[o_RO_GR] = "o\b5";
	avt_dgreek[O_AC] = ".\b'O\b.";
	avt_dgreek[O_GR] = ".\b`O\b.";
	avt_dgreek[O_SM] = ".\b)O\b.";
	avt_dgreek[O_SM_AC] = ".\b&O\b.";
	avt_dgreek[O_SM_GR] = ".\b*O\b.";
	avt_dgreek[O_RO] = ".\b(O\b.";
	avt_dgreek[O_RO_AC] = ".\b$O\b.";
	avt_dgreek[O_RO_GR] = ".\b%O\b.";
	avt_dgreek[PI] = "P\b.";
	avt_dgreek[pi] = "p\b.";
	avt_dgreek[RHO] = "R\b.";
	avt_dgreek[R_SM] = ".\b)R";
	avt_dgreek[R_RO] = ".\b(R";
	avt_dgreek[rho] = "r\b.";
	avt_dgreek[r_SM] = "r\b0";
	avt_dgreek[r_RO] = "r\b9";
	avt_dgreek[sigma] = "j\b.";
	avt_dgreek[SIGMA] = "J\b.";
	avt_dgreek[TAU] = "T\b.";
	avt_dgreek[tau] = "t\b.";
	avt_dgreek[UPSILON] = "U\b.";
	avt_dgreek[upsilon] = "u\b.";
	avt_dgreek[U_AC] = ".\b'U\b.";
	avt_dgreek[U_GR] = ".\b`U\b.";
	avt_dgreek[U_CI] = ".\b~U\b.";
	avt_dgreek[U_SM] = ".\b)U\b.";
	avt_dgreek[U_SM_AC] = ".\b&U\b.";
	avt_dgreek[U_SM_GR] = ".\b*U\b.";
	avt_dgreek[U_SM_CI] = ".\b^U\b.";
	avt_dgreek[U_RO] = ".\b(U\b.";
	avt_dgreek[U_RO_AC] = ".\b$U\b.";
	avt_dgreek[U_RO_GR] = ".\b%U\b.";
	avt_dgreek[U_RO_CI] = ".\b#U\b.";
	avt_dgreek[u_AC] = "u\b\"";
	avt_dgreek[u_GR] = "u\b\\";
	avt_dgreek[u_DI] = "u\b!";
	avt_dgreek[u_AC_DI] = "u\bA\b.";
	avt_dgreek[u_GR_DI] = "u\bB\b.";
	avt_dgreek[u_CI] = "u\b|";
	avt_dgreek[u_SM] = "u\b0";
	avt_dgreek[u_SM_AC] = "u\b7";
	avt_dgreek[u_SM_GR] = "u\b8";
	avt_dgreek[u_SM_CI] = "u\b6";
	avt_dgreek[u_RO] = "u\b9";
	avt_dgreek[u_RO_AC] = "u\b4";
	avt_dgreek[u_RO_GR] = "u\b5";
	avt_dgreek[u_RO_CI] = "u\b3";
	avt_dgreek[fi] = "\033Q\26\033R";
	avt_dgreek[FI] = "F\b.";
	avt_dgreek[xi] = "\033Q\25\033R";
	avt_dgreek[XI] = "X\b.";
	avt_dgreek[YI] = "Y\b.";
	avt_dgreek[yi] = "\033Q\31\033R";
	avt_dgreek[WMEGA] = "W\b.";
	avt_dgreek[wmega] = "w\b.";
	avt_dgreek[W_AC] = ".\b'W\b.";
	avt_dgreek[W_GR] = ".\b`W\b.";
	avt_dgreek[W_CI] = ".\b~W\b.";
	avt_dgreek[W_SM] = ".\b)W\b.";
	avt_dgreek[W_SM_AC] = ".\b&W\b.";
	avt_dgreek[W_SM_GR] = ".\b*W\b.";
	avt_dgreek[W_SM_CI] = ".\b^W\b.";
	avt_dgreek[W_RO] = ".\b(W\b.";
	avt_dgreek[W_RO_AC] = ".\b$W\b.";
	avt_dgreek[W_RO_GR] = ".\b%W\b.";
	avt_dgreek[W_RO_CI] = ".\b#W\b.";
	avt_dgreek[w_AC] = "w\b\"";
	avt_dgreek[w_GR] = "w\b\\";
	avt_dgreek[w_CI] = "w\b|";
	avt_dgreek[w_SM] = "w\b0";
	avt_dgreek[w_SM_AC] = "w\b7";
	avt_dgreek[w_SM_GR] = "w\b8";
	avt_dgreek[w_SM_CI] = "w\b6";
	avt_dgreek[w_RO] = "w\b9";
	avt_dgreek[w_RO_AC] = "w\b4";
	avt_dgreek[w_RO_GR] = "w\b5";
	avt_dgreek[w_RO_CI] = "w\b3";
	avt_dgreek[w_IS] = "}";
	avt_dgreek[w_AC_IS] = "}\b\"";
	avt_dgreek[w_GR_IS] = "}\b\\";
	avt_dgreek[w_CI_IS] = "}\b|";
	avt_dgreek[w_SM_IS] = "}\b0";
	avt_dgreek[w_SM_AC_IS] = "}\b7";
	avt_dgreek[w_SM_GR_IS] = "}\b8";
	avt_dgreek[w_SM_CI_IS] = "}\b6";
	avt_dgreek[w_RO_IS] = "}\b9";
	avt_dgreek[w_RO_AC_IS] = "}\b4";
	avt_dgreek[w_RO_GR_IS] = "}\b5";
	avt_dgreek[w_RO_CI_IS] = "}\b3";
	avt_dgreek[ELLIPSIS] = "\17.\16";
}
	char *avt_punct[] = {
		"\016.\b\033Q\05\033R",	/* 0 dagger */
		"?",		/* 1 */
		"*",		/* 2 */
		"/",		/* 3 */
		"!",		/* 4 */
		"|",		/* 5 */
		"=",		/* 6 */
		"+",		/* 7 */
		"%%",		/* 8 '%' */
		"&",		/* 9 */
		":",		/* 10 */
		".",		/* 11 (should be) oversized period */
		"*",		/* 12 variant '*' */
		"\016.\b\033Q\05\033R",	/* 13 (should be) double dagger */
		"\\(sc", 	/* 14 paragraph sign */
		"|",		/* 15 should be short vertical bar */
		"|",		/* 16 should be broken vertical bar */
		"\016.\bG",	/* 17 double vertical bar */
	};
		
char * avt_lbrackets[] = {
		"[",	/* left square bracket */
		"(", 	/* left paren */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"\016.\b\033Q\01\033R",	/* left double brackets */
		"\016.\b\033Q\07\033R",	/* left half brackets */
};

char * avt_rbrackets[] = {
		"]",	/* right square bracket */
		")", 	/* right paren */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"\016.\b\033Q\02\033R",	/* right double brackets */
		"\016.\b\033Q\010\033R",/* right half brackets */
};

char * avt_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"\"",		/* 1 low double close quote */
		"\"",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *avt_tgreek = "\033[m\016";
char *avt_tbgreek = "\033[7m\016";
char *avt_troman = "\033[m\017";

char * avt_newline = "\n";

fix_avt_save(fname)
char * fname;
{
}

add_avt_header(f)
FILE * f;
{
}
