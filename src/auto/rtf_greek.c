/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "filttab.h"

char * rtf_greek[MAX_GK_CHARS];
char * rtf_dgreek[MAX_GK_CHARS];

setup_rtf_greek()
{
	rtf_greek[alpha] = "a";
	rtf_greek[a_SM_AC] = "\220";
	rtf_greek[a_SM_GR] = "\222";
	rtf_greek[a_SM_CI] = "\224";
	rtf_greek[a_RO_AC] = "\221";
	rtf_greek[a_RO_GR] = "\223";
	rtf_greek[a_RO_CI] = "\225";
	rtf_greek[a_AC] = "\213";
	rtf_greek[a_GR] = "\214";
	rtf_greek[a_CI] = "\215";
	rtf_greek[a_SM] = "\216";
	rtf_greek[a_RO] = "\217";
	rtf_greek[a_SM_AC_IS] = "\220i";
	rtf_greek[a_SM_GR_IS] = "\222i";
	rtf_greek[a_SM_CI_IS] = "\224i";
	rtf_greek[a_RO_AC_IS] = "\221i";
	rtf_greek[a_RO_GR_IS] = "\223i";
	rtf_greek[a_RO_CI_IS] = "\225i";
	rtf_greek[a_AC_IS] = "\213i";
	rtf_greek[a_GR_IS] = "\214i";
	rtf_greek[a_CI_IS] = "\215i";
	rtf_greek[a_SM_IS] = "\216i";
	rtf_greek[a_RO_IS] = "\217i";
	rtf_greek[a_IS] = "ai";
	rtf_greek[ALPHA] = "A";
	rtf_greek[A_SM_CI] = "\211A";
	rtf_greek[A_SM_AC] = "\205A";
	rtf_greek[A_SM_GR] = "\207A";
	rtf_greek[A_RO_CI] = "\212A";
	rtf_greek[A_RO_AC] = "\206A";
	rtf_greek[A_RO_GR] = "\210A";
	rtf_greek[A_SM] = "\203A";
	rtf_greek[A_RO] = "\204A";
	rtf_greek[A_CI] = "\202A";
	rtf_greek[beta] = "b";
	rtf_greek[BETA] = "B";
	rtf_greek[GAMMA] = "G";
	rtf_greek[gamma] = "g";
	rtf_greek[delta] = "d";
	rtf_greek[DELTA] = "D";
	rtf_greek[epsilon] = "e";
	rtf_greek[EPSILON] = "E";
	rtf_greek[e_SM_AC] = "\246";
	rtf_greek[e_SM_GR] = "\250";
	rtf_greek[e_RO_AC] = "\247";
	rtf_greek[e_RO_GR] = "\251";
	rtf_greek[e_AC] = "\241";
	rtf_greek[e_GR] = "\242";
	rtf_greek[e_SM] = "\244";
	rtf_greek[e_RO] = "\245";
	rtf_greek[E_SM_AC] = "\205E";
	rtf_greek[E_SM_GR] = "\207E";
	rtf_greek[E_RO_AC] = "\206E";
	rtf_greek[E_RO_GR] = "\210E";
	rtf_greek[E_SM] = "\203E";
	rtf_greek[E_RO] = "\204E";
	rtf_greek[hta] = "h";
	rtf_greek[HTA] = "H";
	rtf_greek[H_SM_CI] = "\211H";
	rtf_greek[H_SM_AC] = "\205H";
	rtf_greek[H_SM_GR] = "\207H";
	rtf_greek[H_RO_CI] = "\212H";
	rtf_greek[H_RO_AC] = "\206H";
	rtf_greek[H_RO_GR] = "\210H";
	rtf_greek[H_SM] = "\203H";
	rtf_greek[H_RO] = "\204H";
	rtf_greek[H_CI] = "\202H";
	rtf_greek[h_SM_AC] = "\263";
	rtf_greek[h_SM_GR] = "\265";
	rtf_greek[h_SM_CI] = "\267";
	rtf_greek[h_RO_AC] = "\264";
	rtf_greek[h_RO_GR] = "\266";
	rtf_greek[h_RO_CI] = "\270";
	rtf_greek[h_AC] = "\256";
	rtf_greek[h_GR] = "\257";
	rtf_greek[h_CI] = "\260";
	rtf_greek[h_SM] = "\261";
	rtf_greek[h_RO] = "\262";
	rtf_greek[h_SM_AC_IS] = "\263i";
	rtf_greek[h_SM_GR_IS] = "\265i";
	rtf_greek[h_SM_CI_IS] = "\267i";
	rtf_greek[h_RO_AC_IS] = "\264i";
	rtf_greek[h_RO_GR_IS] = "\266i";
	rtf_greek[h_RO_CI_IS] = "\270i";
	rtf_greek[h_AC_IS] = "\256i";
	rtf_greek[h_GR_IS] = "\257i";
	rtf_greek[h_CI_IS] = "\260i";
	rtf_greek[h_SM_IS] = "\261i";
	rtf_greek[h_RO_IS] = "\262i";
	rtf_greek[h_IS] = "hi";
	rtf_greek[zeta] = "z";
	rtf_greek[ZETA] = "Z";
	rtf_greek[qeta] = "y";
	rtf_greek[QETA] = "Y";
	rtf_greek[iota] = "i";
	rtf_greek[IOTA] = "I";
	rtf_greek[i_SM_AC] = "\340";
	rtf_greek[i_SM_GR] = "\342";
	rtf_greek[i_SM_CI] = "\344";
	rtf_greek[i_RO_AC] = "\341";
	rtf_greek[i_RO_GR] = "\343";
	rtf_greek[i_RO_CI] = "\345";
	rtf_greek[i_DI] = "\363";
	rtf_greek[i_AC_DI] = "\375";	/* diaereses not available here*/
	rtf_greek[i_GR_DI] = "\376";
	rtf_greek[i_AC] = "\333";
	rtf_greek[i_GR] = "\334";
	rtf_greek[i_CI] = "\335";
	rtf_greek[i_SM] = "\336";
	rtf_greek[i_RO] = "\337";
	rtf_greek[I_SM_CI] = "\211I";
	rtf_greek[I_SM_AC] = "\205I";
	rtf_greek[I_SM_GR] = "\207I";
	rtf_greek[I_RO_CI] = "\212I";
	rtf_greek[I_RO_AC] = "\206I";
	rtf_greek[I_RO_GR] = "\210I";
	rtf_greek[I_SM] = "\203I";
	rtf_greek[I_RO] = "\204I";
	rtf_greek[I_CI] = "\202I";
	rtf_greek[I_AC] = "\200I";
	rtf_greek[I_GR] = "\201I";
	rtf_greek[kappa] = "k";
	rtf_greek[KAPPA] = "K";
	rtf_greek[lambda] = "l";
	rtf_greek[LAMBDA] = "L";
	rtf_greek[mu] = "m";
	rtf_greek[MU] = "M";
	rtf_greek[nu] = "n";
	rtf_greek[NU] = "N";
	rtf_greek[ci] = "j";
	rtf_greek[CI] = "J";
	rtf_greek[omicron] = "o";
	rtf_greek[OMICRON] = "O";
	rtf_greek[o_SM_AC] = "\366";
	rtf_greek[o_SM_GR] = "\370";
	rtf_greek[o_RO_AC] = "\367";
	rtf_greek[o_RO_GR] = "\371";
	rtf_greek[o_AC] = "\361";
	rtf_greek[o_GR] = "\362";
	rtf_greek[o_SM] = "\364";
	rtf_greek[o_RO] = "\365";
	rtf_greek[O_SM_AC] = "\205O";
	rtf_greek[O_SM_GR] = "\207O";
	rtf_greek[O_RO_AC] = "\206O";
	rtf_greek[O_RO_GR] = "\210O";
	rtf_greek[O_AC] = "\200O";
	rtf_greek[O_GR] = "\201O";
	rtf_greek[O_SM] = "\203O";
	rtf_greek[O_RO] = "\204O";
	rtf_greek[pi] = "p";
	rtf_greek[PI] = "P";
	rtf_greek[RHO] = "R";
	rtf_greek[R_SM] = "\261R";
	rtf_greek[R_RO] = "\262R";
	rtf_greek[rho] = "r";
	rtf_greek[r_RO] = "\75";
	rtf_greek[r_SM] = "\261r";
	rtf_greek[SIGMA] = "S";
	rtf_greek[sigma] = "s";
	rtf_greek[tau] = "t";
	rtf_greek[TAU] = "T";
	rtf_greek[UPSILON] = "U";
	rtf_greek[U_SM_CI] = "\211U";
	rtf_greek[U_SM_AC] = "\205U";
	rtf_greek[U_SM_GR] = "\207U";
	rtf_greek[U_RO_CI] = "\212U";
	rtf_greek[U_RO_AC] = "\206U";
	rtf_greek[U_RO_GR] = "\210U";
	rtf_greek[U_SM] = "\203U";
	rtf_greek[U_RO] = "\204U";
	rtf_greek[U_CI] = "\202U";
	rtf_greek[U_AC] = "\200U";
	rtf_greek[U_GR] = "\201U";
	rtf_greek[upsilon] = "u";
	rtf_greek[u_SM_AC] = "\353";
	rtf_greek[u_SM_GR] = "\355";
	rtf_greek[u_SM_CI] = "\357";
	rtf_greek[u_RO_AC] = "\354";
	rtf_greek[u_RO_GR] = "\356";
	rtf_greek[u_RO_CI] = "\360";
	rtf_greek[u_DI] = "\43";
	rtf_greek[u_AC_DI] = "\100";
	rtf_greek[u_GR_DI] = "\347"; /* this diaeresis comb not available*/
	rtf_greek[u_AC] = "\346";
	rtf_greek[u_GR] = "\347";
	rtf_greek[u_CI] = "\350";
	rtf_greek[u_SM] = "\351";
	rtf_greek[u_RO] = "\352";
	rtf_greek[FI] = "F";
	rtf_greek[fi] = "f";
	rtf_greek[xi] = "x";
	rtf_greek[XI] = "X";
	rtf_greek[yi] = "c";
	rtf_greek[YI] = "C";
	rtf_greek[WMEGA] = "V";
	rtf_greek[wmega] = "v";
	rtf_greek[w_SM_AC] = "\312";
	rtf_greek[w_SM_GR] = "\314";
	rtf_greek[w_SM_CI] = "\316";
	rtf_greek[w_RO_AC] = "\313";
	rtf_greek[w_RO_GR] = "\315";
	rtf_greek[w_RO_CI] = "\317";
	rtf_greek[w_AC] = "\305";
	rtf_greek[w_GR] = "\306";
	rtf_greek[w_CI] = "\307";
	rtf_greek[w_SM] = "\310";
	rtf_greek[w_RO] = "\311";
	rtf_greek[W_SM_CI] = "\211V";
	rtf_greek[W_SM_AC] = "\205V";
	rtf_greek[W_SM_GR] = "\207V";
	rtf_greek[W_RO_CI] = "\212V";
	rtf_greek[W_RO_AC] = "\206V";
	rtf_greek[W_RO_GR] = "\210V";
	rtf_greek[W_SM] = "\203V";
	rtf_greek[W_RO] = "\204V";
	rtf_greek[W_CI] = "\202V";
	rtf_greek[W_AC] = "\200V";
	rtf_greek[W_GR] = "\201V";
	rtf_greek[w_IS] = "vi";
	rtf_greek[w_SM_AC_IS] = "\312i";
	rtf_greek[w_SM_GR_IS] = "\314i";
	rtf_greek[w_SM_CI_IS] = "\316i";
	rtf_greek[w_RO_AC_IS] = "\313i";
	rtf_greek[w_RO_GR_IS] = "\315i";
	rtf_greek[w_RO_CI_IS] = "\317i";
	rtf_greek[w_AC_IS] = "\305i";
	rtf_greek[w_GR_IS] = "\306i";
	rtf_greek[w_CI_IS] = "\307i";
	rtf_greek[w_SM_IS] = "\310i";
	rtf_greek[w_RO_IS] = "\311i";
	rtf_greek[tsigma] = "w";
	rtf_greek[ELLIPSIS] = ".";

	rtf_dgreek[alpha] = "a?";
	rtf_dgreek[a_SM_AC] = "\220?";
	rtf_dgreek[a_SM_GR] = "\222?";
	rtf_dgreek[a_SM_CI] = "\224?";
	rtf_dgreek[a_RO_AC] = "\221?";
	rtf_dgreek[a_RO_GR] = "\223?";
	rtf_dgreek[a_RO_CI] = "\225?";
	rtf_dgreek[a_AC] = "\213?";
	rtf_dgreek[a_GR] = "\214?";
	rtf_dgreek[a_CI] = "\215?";
	rtf_dgreek[a_SM] = "\216?";
	rtf_dgreek[a_RO] = "\217?";
	rtf_dgreek[a_SM_AC_IS] = "\220i?";
	rtf_dgreek[a_SM_GR_IS] = "\222i?";
	rtf_dgreek[a_SM_CI_IS] = "\224i?";
	rtf_dgreek[a_RO_AC_IS] = "\221i?";
	rtf_dgreek[a_RO_GR_IS] = "\223i?";
	rtf_dgreek[a_RO_CI_IS] = "\225i?";
	rtf_dgreek[a_AC_IS] = "\213i?";
	rtf_dgreek[a_GR_IS] = "\214i?";
	rtf_dgreek[a_CI_IS] = "\215i?";
	rtf_dgreek[a_SM_IS] = "\216i?";
	rtf_dgreek[a_RO_IS] = "\217i?";
	rtf_dgreek[a_IS] = "ai?";
	rtf_dgreek[ALPHA] = "A?";
	rtf_dgreek[A_SM_CI] = "\211A?";
	rtf_dgreek[A_SM_AC] = "\205A?";
	rtf_dgreek[A_SM_GR] = "\207A?";
	rtf_dgreek[A_RO_CI] = "\212A?";
	rtf_dgreek[A_RO_AC] = "\206A?";
	rtf_dgreek[A_RO_GR] = "\210A?";
	rtf_dgreek[A_SM] = "\203A?";
	rtf_dgreek[A_RO] = "\204A?";
	rtf_dgreek[A_CI] = "\202A?";
	rtf_dgreek[beta] = "b?";
	rtf_dgreek[BETA] = "B?";
	rtf_dgreek[GAMMA] = "G?";
	rtf_dgreek[gamma] = "g?";
	rtf_dgreek[delta] = "d?";
	rtf_dgreek[DELTA] = "D?";
	rtf_dgreek[epsilon] = "e?";
	rtf_dgreek[EPSILON] = "E?";
	rtf_dgreek[e_SM_AC] = "\246?";
	rtf_dgreek[e_SM_GR] = "\250?";
	rtf_dgreek[e_RO_AC] = "\247?";
	rtf_dgreek[e_RO_GR] = "\251?";
	rtf_dgreek[e_AC] = "\241?";
	rtf_dgreek[e_GR] = "\242?";
	rtf_dgreek[e_SM] = "\244?";
	rtf_dgreek[e_RO] = "\245?";
	rtf_dgreek[E_SM_AC] = "\205E?";
	rtf_dgreek[E_SM_GR] = "\207E?";
	rtf_dgreek[E_RO_AC] = "\206E?";
	rtf_dgreek[E_RO_GR] = "\210E?";
	rtf_dgreek[E_SM] = "\203E?";
	rtf_dgreek[E_RO] = "\204E?";
	rtf_dgreek[hta] = "h?";
	rtf_dgreek[HTA] = "H?";
	rtf_dgreek[H_SM_CI] = "\211H?";
	rtf_dgreek[H_SM_AC] = "\205H?";
	rtf_dgreek[H_SM_GR] = "\207H?";
	rtf_dgreek[H_RO_CI] = "\212H?";
	rtf_dgreek[H_RO_AC] = "\206H?";
	rtf_dgreek[H_RO_GR] = "\210H?";
	rtf_dgreek[H_SM] = "\203H?";
	rtf_dgreek[H_RO] = "\204H?";
	rtf_dgreek[H_CI] = "\202H?";
	rtf_dgreek[h_SM_AC] = "\263?";
	rtf_dgreek[h_SM_GR] = "\265?";
	rtf_dgreek[h_SM_CI] = "\267?";
	rtf_dgreek[h_RO_AC] = "\264?";
	rtf_dgreek[h_RO_GR] = "\266?";
	rtf_dgreek[h_RO_CI] = "\270?";
	rtf_dgreek[h_AC] = "\256?";
	rtf_dgreek[h_GR] = "\257?";
	rtf_dgreek[h_CI] = "\260?";
	rtf_dgreek[h_SM] = "\261?";
	rtf_dgreek[h_RO] = "\262?";
	rtf_dgreek[h_SM_AC_IS] = "\263i?";
	rtf_dgreek[h_SM_GR_IS] = "\265i?";
	rtf_dgreek[h_SM_CI_IS] = "\267i?";
	rtf_dgreek[h_RO_AC_IS] = "\264i?";
	rtf_dgreek[h_RO_GR_IS] = "\266i?";
	rtf_dgreek[h_RO_CI_IS] = "\270i?";
	rtf_dgreek[h_AC_IS] = "\256i?";
	rtf_dgreek[h_GR_IS] = "\257i?";
	rtf_dgreek[h_CI_IS] = "\260i?";
	rtf_dgreek[h_SM_IS] = "\261i?";
	rtf_dgreek[h_RO_IS] = "\262i?";
	rtf_dgreek[h_IS] = "hi?";
	rtf_dgreek[zeta] = "z?";
	rtf_dgreek[ZETA] = "Z?";
	rtf_dgreek[qeta] = "y?";
	rtf_dgreek[QETA] = "Y?";
	rtf_dgreek[iota] = "i?";
	rtf_dgreek[IOTA] = "I?";
	rtf_dgreek[i_SM_AC] = "\340?";
	rtf_dgreek[i_SM_GR] = "\342?";
	rtf_dgreek[i_SM_CI] = "\344?";
	rtf_dgreek[i_RO_AC] = "\341?";
	rtf_dgreek[i_RO_GR] = "\343?";
	rtf_dgreek[i_RO_CI] = "\345?";
	rtf_dgreek[i_DI] = "\363?";
	rtf_dgreek[i_AC_DI] = "\375?";	/* diaereses not available here*/
	rtf_dgreek[i_GR_DI] = "\376?";
	rtf_dgreek[i_AC] = "\333?";
	rtf_dgreek[i_GR] = "\334?";
	rtf_dgreek[i_CI] = "\335?";
	rtf_dgreek[i_SM] = "\336?";
	rtf_dgreek[i_RO] = "\337?";
	rtf_dgreek[I_SM_CI] = "\211I?";
	rtf_dgreek[I_SM_AC] = "\205I?";
	rtf_dgreek[I_SM_GR] = "\207I?";
	rtf_dgreek[I_RO_CI] = "\212I?";
	rtf_dgreek[I_RO_AC] = "\206I?";
	rtf_dgreek[I_RO_GR] = "\210I?";
	rtf_dgreek[I_SM] = "\203I?";
	rtf_dgreek[I_RO] = "\204I?";
	rtf_dgreek[I_CI] = "\202I?";
	rtf_dgreek[I_AC] = "\200I?";
	rtf_dgreek[I_GR] = "\201I?";
	rtf_dgreek[kappa] = "k?";
	rtf_dgreek[KAPPA] = "K?";
	rtf_dgreek[lambda] = "l?";
	rtf_dgreek[LAMBDA] = "L?";
	rtf_dgreek[mu] = "m?";
	rtf_dgreek[MU] = "M?";
	rtf_dgreek[nu] = "n?";
	rtf_dgreek[NU] = "N?";
	rtf_dgreek[ci] = "j?";
	rtf_dgreek[CI] = "J?";
	rtf_dgreek[omicron] = "o?";
	rtf_dgreek[OMICRON] = "O?";
	rtf_dgreek[o_SM_AC] = "\366?";
	rtf_dgreek[o_SM_GR] = "\370?";
	rtf_dgreek[o_RO_AC] = "\367?";
	rtf_dgreek[o_RO_GR] = "\371?";
	rtf_dgreek[o_AC] = "\361?";
	rtf_dgreek[o_GR] = "\362?";
	rtf_dgreek[o_SM] = "\364?";
	rtf_dgreek[o_RO] = "\365?";
	rtf_dgreek[O_SM_AC] = "\205O?";
	rtf_dgreek[O_SM_GR] = "\207O?";
	rtf_dgreek[O_RO_AC] = "\206O?";
	rtf_dgreek[O_RO_GR] = "\210O?";
	rtf_dgreek[O_AC] = "\200O?";
	rtf_dgreek[O_GR] = "\201O?";
	rtf_dgreek[O_SM] = "\203O?";
	rtf_dgreek[O_RO] = "\204O?";
	rtf_dgreek[pi] = "p?";
	rtf_dgreek[PI] = "P?";
	rtf_dgreek[RHO] = "R?";
	rtf_dgreek[R_SM] = "\\R?";
	rtf_dgreek[R_RO] = "]R?";
	rtf_dgreek[rho] = "r?";
	rtf_dgreek[r_RO] = "\75?";
	rtf_dgreek[r_SM] = "\261r?";
	rtf_dgreek[SIGMA] = "S?";
	rtf_dgreek[sigma] = "s?";
	rtf_dgreek[tau] = "t?";
	rtf_dgreek[TAU] = "T?";
	rtf_dgreek[UPSILON] = "U?";
	rtf_dgreek[U_SM_CI] = "\211U?";
	rtf_dgreek[U_SM_AC] = "\205U?";
	rtf_dgreek[U_SM_GR] = "\207U?";
	rtf_dgreek[U_RO_CI] = "\212U?";
	rtf_dgreek[U_RO_AC] = "\206U?";
	rtf_dgreek[U_RO_GR] = "\210U?";
	rtf_dgreek[U_SM] = "\203U?";
	rtf_dgreek[U_RO] = "\204U?";
	rtf_dgreek[U_CI] = "\202U?";
	rtf_dgreek[U_AC] = "\200U?";
	rtf_dgreek[U_GR] = "\201U?";
	rtf_dgreek[upsilon] = "u?";
	rtf_dgreek[u_SM_AC] = "\353?";
	rtf_dgreek[u_SM_GR] = "\355?";
	rtf_dgreek[u_SM_CI] = "\357?";
	rtf_dgreek[u_RO_AC] = "\354?";
	rtf_dgreek[u_RO_GR] = "\356?";
	rtf_dgreek[u_RO_CI] = "\360?";
	rtf_dgreek[u_DI] = "\43?";
	rtf_dgreek[u_AC_DI] = "\100?";
	rtf_dgreek[u_GR_DI] = "\347?"; /* this combo not available*/
	rtf_dgreek[u_AC] = "\346?";
	rtf_dgreek[u_GR] = "\347?";
	rtf_dgreek[u_CI] = "\350?";
	rtf_dgreek[u_SM] = "\351?";
	rtf_dgreek[u_RO] = "\352?";
	rtf_dgreek[FI] = "F?";
	rtf_dgreek[fi] = "f?";
	rtf_dgreek[xi] = "x?";
	rtf_dgreek[XI] = "X?";
	rtf_dgreek[yi] = "c?";
	rtf_dgreek[YI] = "C?";
	rtf_dgreek[WMEGA] = "V?";
	rtf_dgreek[wmega] = "v?";
	rtf_dgreek[w_SM_AC] = "\312?";
	rtf_dgreek[w_SM_GR] = "\314?";
	rtf_dgreek[w_SM_CI] = "\316?";
	rtf_dgreek[w_RO_AC] = "\313?";
	rtf_dgreek[w_RO_GR] = "\315?";
	rtf_dgreek[w_RO_CI] = "\317?";
	rtf_dgreek[w_AC] = "\305?";
	rtf_dgreek[w_GR] = "\306?";
	rtf_dgreek[w_CI] = "\307?";
	rtf_dgreek[w_SM] = "\310?";
	rtf_dgreek[w_RO] = "\311?";
	rtf_dgreek[W_SM_CI] = "\211V?";
	rtf_dgreek[W_SM_AC] = "\205V?";
	rtf_dgreek[W_SM_GR] = "\207V?";
	rtf_dgreek[W_RO_CI] = "\212V?";
	rtf_dgreek[W_RO_AC] = "\206V?";
	rtf_dgreek[W_RO_GR] = "\210V?";
	rtf_dgreek[W_SM] = "\203V?";
	rtf_dgreek[W_RO] = "\204V?";
	rtf_dgreek[W_CI] = "\202V?";
	rtf_dgreek[W_AC] = "\200V?";
	rtf_dgreek[W_GR] = "\201V?";
	rtf_dgreek[w_IS] = "vi?";
	rtf_dgreek[w_SM_AC_IS] = "\312i?";
	rtf_dgreek[w_SM_GR_IS] = "\314i?";
	rtf_dgreek[w_SM_CI_IS] = "\316i?";
	rtf_dgreek[w_RO_AC_IS] = "\313i?";
	rtf_dgreek[w_RO_GR_IS] = "\315i?";
	rtf_dgreek[w_RO_CI_IS] = "\317i?";
	rtf_dgreek[w_AC_IS] = "\305i?";
	rtf_dgreek[w_GR_IS] = "\306i?";
	rtf_dgreek[w_CI_IS] = "\307i?";
	rtf_dgreek[w_SM_IS] = "\310i?";
	rtf_dgreek[w_RO_IS] = "\311i?";
	rtf_dgreek[tsigma] = "w?";
	rtf_dgreek[ELLIPSIS] = ".";
}

	char *rtf_punct[] = {
		"\176", /* 0 dagger */
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
		"\176", /* 13 (should be) double dagger */
		"(Sect)", 	/* 14 paragraph sign */
		"|",		/* 15 should be short vertical bar */
		"|",		/* 16 should be broken vertical bar */
		"||",	/* 17 double vertical bar */
	};
		
char * rtf_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double bracket */
		"|_",	/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * rtf_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double bracket */
		"_|",	/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * rtf_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"''",		/* 1 low double close quote */
		"''",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *rtf_tgreek = "}{\\f132\\fs20 ";
char *rtf_tbgreek = "}{\\b\\f132\\fs20 ";
char *rtf_troman = "}{\\f3\\fs18 ";

char * rtf_newline = "\\par\n";

fix_rtf_save(fname)
char * fname;
{
	FILE * f;

	if( (f=fopen(fname,"a")) == NULL )
		return(-1);
	fprintf(f,"}\n");
	fclose(f);
}

#define RTF_TEMPLATE "/usr/lib/TLG/tlgsend/lib/template.rtf"
add_rtf_header(f)
FILE * f;
{
	FILE * finput;
	int c;

	if( (finput=fopen(RTF_TEMPLATE,"r")) == NULL ) {
		fprintf(stderr,"Could not open [%s]\n", RTF_TEMPLATE );
		fprintf(stderr," continue? "); getchar();
		return(-1);
	}
	while((c=fgetc(finput)) != EOF) 
		fputc(c,f);
	fclose(finput);
	return(1);
}
