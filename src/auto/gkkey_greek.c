/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "filttab.h"

char * gkkey_greek[MAX_GK_CHARS];
char * gkkey_dgreek[MAX_GK_CHARS];

setup_gkkey_greek()
{
	gkkey_greek[alpha] = "a";
	gkkey_greek[a_SM_AC] = "\220";
	gkkey_greek[a_SM_GR] = "\222";
	gkkey_greek[a_SM_CI] = "\224";
	gkkey_greek[a_RO_AC] = "\221";
	gkkey_greek[a_RO_GR] = "\223";
	gkkey_greek[a_RO_CI] = "\225";
	gkkey_greek[a_AC] = "\213";
	gkkey_greek[a_GR] = "\214";
	gkkey_greek[a_CI] = "\215";
	gkkey_greek[a_SM] = "\216";
	gkkey_greek[a_RO] = "\217";
	gkkey_greek[a_SM_AC_IS] = "\220i";
	gkkey_greek[a_SM_GR_IS] = "\222i";
	gkkey_greek[a_SM_CI_IS] = "\224i";
	gkkey_greek[a_RO_AC_IS] = "\221i";
	gkkey_greek[a_RO_GR_IS] = "\223i";
	gkkey_greek[a_RO_CI_IS] = "\225i";
	gkkey_greek[a_AC_IS] = "\213i";
	gkkey_greek[a_GR_IS] = "\214i";
	gkkey_greek[a_CI_IS] = "\215i";
	gkkey_greek[a_SM_IS] = "\216i";
	gkkey_greek[a_RO_IS] = "\217i";
	gkkey_greek[a_IS] = "ai";
	gkkey_greek[ALPHA] = "A";
	gkkey_greek[A_SM_CI] = "\211A";
	gkkey_greek[A_SM_AC] = "\205A";
	gkkey_greek[A_SM_GR] = "\207A";
	gkkey_greek[A_RO_CI] = "\212A";
	gkkey_greek[A_RO_AC] = "\206A";
	gkkey_greek[A_RO_GR] = "\210A";
	gkkey_greek[A_SM] = "\203A";
	gkkey_greek[A_RO] = "\204A";
	gkkey_greek[A_CI] = "\202A";
	gkkey_greek[beta] = "b";
	gkkey_greek[BETA] = "B";
	gkkey_greek[GAMMA] = "G";
	gkkey_greek[gamma] = "g";
	gkkey_greek[delta] = "d";
	gkkey_greek[DELTA] = "D";
	gkkey_greek[epsilon] = "e";
	gkkey_greek[EPSILON] = "E";
	gkkey_greek[e_SM_AC] = "\246";
	gkkey_greek[e_SM_GR] = "\250";
	gkkey_greek[e_RO_AC] = "\247";
	gkkey_greek[e_RO_GR] = "\251";
	gkkey_greek[e_AC] = "\241";
	gkkey_greek[e_GR] = "\242";
	gkkey_greek[e_SM] = "\244";
	gkkey_greek[e_RO] = "\245";
	gkkey_greek[E_SM_AC] = "\205E";
	gkkey_greek[E_SM_GR] = "\207E";
	gkkey_greek[E_RO_AC] = "\206E";
	gkkey_greek[E_RO_GR] = "\210E";
	gkkey_greek[E_SM] = "\203E";
	gkkey_greek[E_RO] = "\204E";
	gkkey_greek[hta] = "h";
	gkkey_greek[HTA] = "H";
	gkkey_greek[H_SM_CI] = "\211H";
	gkkey_greek[H_SM_AC] = "\205H";
	gkkey_greek[H_SM_GR] = "\207H";
	gkkey_greek[H_RO_CI] = "\212H";
	gkkey_greek[H_RO_AC] = "\206H";
	gkkey_greek[H_RO_GR] = "\210H";
	gkkey_greek[H_SM] = "\203H";
	gkkey_greek[H_RO] = "\204H";
	gkkey_greek[H_CI] = "\202H";
	gkkey_greek[h_SM_AC] = "\263";
	gkkey_greek[h_SM_GR] = "\265";
	gkkey_greek[h_SM_CI] = "\267";
	gkkey_greek[h_RO_AC] = "\264";
	gkkey_greek[h_RO_GR] = "\266";
	gkkey_greek[h_RO_CI] = "\270";
	gkkey_greek[h_AC] = "\256";
	gkkey_greek[h_GR] = "\257";
	gkkey_greek[h_CI] = "\260";
	gkkey_greek[h_SM] = "\261";
	gkkey_greek[h_RO] = "\262";
	gkkey_greek[h_SM_AC_IS] = "\263i";
	gkkey_greek[h_SM_GR_IS] = "\265i";
	gkkey_greek[h_SM_CI_IS] = "\267i";
	gkkey_greek[h_RO_AC_IS] = "\264i";
	gkkey_greek[h_RO_GR_IS] = "\266i";
	gkkey_greek[h_RO_CI_IS] = "\270i";
	gkkey_greek[h_AC_IS] = "\256i";
	gkkey_greek[h_GR_IS] = "\257i";
	gkkey_greek[h_CI_IS] = "\260i";
	gkkey_greek[h_SM_IS] = "\261i";
	gkkey_greek[h_RO_IS] = "\262i";
	gkkey_greek[h_IS] = "hi";
	gkkey_greek[zeta] = "z";
	gkkey_greek[ZETA] = "Z";
	gkkey_greek[qeta] = "y";
	gkkey_greek[QETA] = "Y";
	gkkey_greek[iota] = "i";
	gkkey_greek[IOTA] = "I";
	gkkey_greek[i_SM_AC] = "\340";
	gkkey_greek[i_SM_GR] = "\342";
	gkkey_greek[i_SM_CI] = "\344";
	gkkey_greek[i_RO_AC] = "\341";
	gkkey_greek[i_RO_GR] = "\343";
	gkkey_greek[i_RO_CI] = "\345";
	gkkey_greek[i_DI] = "\363";
	gkkey_greek[i_AC_DI] = "\375";	/* diaereses not available here*/
	gkkey_greek[i_GR_DI] = "\376";
	gkkey_greek[i_AC] = "\333";
	gkkey_greek[i_GR] = "\334";
	gkkey_greek[i_CI] = "\335";
	gkkey_greek[i_SM] = "\336";
	gkkey_greek[i_RO] = "\337";
	gkkey_greek[I_SM_CI] = "\211I";
	gkkey_greek[I_SM_AC] = "\205I";
	gkkey_greek[I_SM_GR] = "\207I";
	gkkey_greek[I_RO_CI] = "\212I";
	gkkey_greek[I_RO_AC] = "\206I";
	gkkey_greek[I_RO_GR] = "\210I";
	gkkey_greek[I_SM] = "\203I";
	gkkey_greek[I_RO] = "\204I";
	gkkey_greek[I_CI] = "\202I";
	gkkey_greek[I_AC] = "\200I";
	gkkey_greek[I_GR] = "\201I";
	gkkey_greek[kappa] = "k";
	gkkey_greek[KAPPA] = "K";
	gkkey_greek[lambda] = "l";
	gkkey_greek[LAMBDA] = "L";
	gkkey_greek[mu] = "m";
	gkkey_greek[MU] = "M";
	gkkey_greek[nu] = "n";
	gkkey_greek[NU] = "N";
	gkkey_greek[ci] = "j";
	gkkey_greek[CI] = "J";
	gkkey_greek[omicron] = "o";
	gkkey_greek[OMICRON] = "O";
	gkkey_greek[o_SM_AC] = "\366";
	gkkey_greek[o_SM_GR] = "\370";
	gkkey_greek[o_RO_AC] = "\367";
	gkkey_greek[o_RO_GR] = "\371";
	gkkey_greek[o_AC] = "\361";
	gkkey_greek[o_GR] = "\362";
	gkkey_greek[o_SM] = "\364";
	gkkey_greek[o_RO] = "\365";
	gkkey_greek[O_SM_AC] = "\205O";
	gkkey_greek[O_SM_GR] = "\207O";
	gkkey_greek[O_RO_AC] = "\206O";
	gkkey_greek[O_RO_GR] = "\210O";
	gkkey_greek[O_AC] = "\200O";
	gkkey_greek[O_GR] = "\201O";
	gkkey_greek[O_SM] = "\203O";
	gkkey_greek[O_RO] = "\204O";
	gkkey_greek[pi] = "p";
	gkkey_greek[PI] = "P";
	gkkey_greek[RHO] = "R";
	gkkey_greek[R_SM] = "\261R";
	gkkey_greek[R_RO] = "\262R";
	gkkey_greek[rho] = "r";
	gkkey_greek[r_RO] = "\75";
	gkkey_greek[r_SM] = "\261r";
	gkkey_greek[SIGMA] = "S";
	gkkey_greek[sigma] = "s";
	gkkey_greek[tau] = "t";
	gkkey_greek[TAU] = "T";
	gkkey_greek[UPSILON] = "U";
	gkkey_greek[U_SM_CI] = "\211U";
	gkkey_greek[U_SM_AC] = "\205U";
	gkkey_greek[U_SM_GR] = "\207U";
	gkkey_greek[U_RO_CI] = "\212U";
	gkkey_greek[U_RO_AC] = "\206U";
	gkkey_greek[U_RO_GR] = "\210U";
	gkkey_greek[U_SM] = "\203U";
	gkkey_greek[U_RO] = "\204U";
	gkkey_greek[U_CI] = "\202U";
	gkkey_greek[U_AC] = "\200U";
	gkkey_greek[U_GR] = "\201U";
	gkkey_greek[upsilon] = "u";
	gkkey_greek[u_SM_AC] = "\353";
	gkkey_greek[u_SM_GR] = "\355";
	gkkey_greek[u_SM_CI] = "\357";
	gkkey_greek[u_RO_AC] = "\354";
	gkkey_greek[u_RO_GR] = "\356";
	gkkey_greek[u_RO_CI] = "\360";
	gkkey_greek[u_DI] = "\43";
	gkkey_greek[u_AC_DI] = "\100";
	gkkey_greek[u_GR_DI] = "\347"; /* this diaeresis comb not available*/
	gkkey_greek[u_AC] = "\346";
	gkkey_greek[u_GR] = "\347";
	gkkey_greek[u_CI] = "\350";
	gkkey_greek[u_SM] = "\351";
	gkkey_greek[u_RO] = "\352";
	gkkey_greek[FI] = "F";
	gkkey_greek[fi] = "f";
	gkkey_greek[xi] = "x";
	gkkey_greek[XI] = "X";
	gkkey_greek[yi] = "c";
	gkkey_greek[YI] = "C";
	gkkey_greek[WMEGA] = "V";
	gkkey_greek[wmega] = "v";
	gkkey_greek[w_SM_AC] = "\312";
	gkkey_greek[w_SM_GR] = "\314";
	gkkey_greek[w_SM_CI] = "\316";
	gkkey_greek[w_RO_AC] = "\313";
	gkkey_greek[w_RO_GR] = "\315";
	gkkey_greek[w_RO_CI] = "\317";
	gkkey_greek[w_AC] = "\305";
	gkkey_greek[w_GR] = "\306";
	gkkey_greek[w_CI] = "\307";
	gkkey_greek[w_SM] = "\310";
	gkkey_greek[w_RO] = "\311";
	gkkey_greek[W_SM_CI] = "\211V";
	gkkey_greek[W_SM_AC] = "\205V";
	gkkey_greek[W_SM_GR] = "\207V";
	gkkey_greek[W_RO_CI] = "\212V";
	gkkey_greek[W_RO_AC] = "\206V";
	gkkey_greek[W_RO_GR] = "\210V";
	gkkey_greek[W_SM] = "\203V";
	gkkey_greek[W_RO] = "\204V";
	gkkey_greek[W_CI] = "\202V";
	gkkey_greek[W_AC] = "\200V";
	gkkey_greek[W_GR] = "\201V";
	gkkey_greek[w_IS] = "vi";
	gkkey_greek[w_SM_AC_IS] = "\312i";
	gkkey_greek[w_SM_GR_IS] = "\314i";
	gkkey_greek[w_SM_CI_IS] = "\316i";
	gkkey_greek[w_RO_AC_IS] = "\313i";
	gkkey_greek[w_RO_GR_IS] = "\315i";
	gkkey_greek[w_RO_CI_IS] = "\317i";
	gkkey_greek[w_AC_IS] = "\305i";
	gkkey_greek[w_GR_IS] = "\306i";
	gkkey_greek[w_CI_IS] = "\307i";
	gkkey_greek[w_SM_IS] = "\310i";
	gkkey_greek[w_RO_IS] = "\311i";
	gkkey_greek[tsigma] = "w";
	gkkey_greek[ELLIPSIS] = ".";

	gkkey_dgreek[alpha] = "a?";
	gkkey_dgreek[a_SM_AC] = "\220?";
	gkkey_dgreek[a_SM_GR] = "\222?";
	gkkey_dgreek[a_SM_CI] = "\224?";
	gkkey_dgreek[a_RO_AC] = "\221?";
	gkkey_dgreek[a_RO_GR] = "\223?";
	gkkey_dgreek[a_RO_CI] = "\225?";
	gkkey_dgreek[a_AC] = "\213?";
	gkkey_dgreek[a_GR] = "\214?";
	gkkey_dgreek[a_CI] = "\215?";
	gkkey_dgreek[a_SM] = "\216?";
	gkkey_dgreek[a_RO] = "\217?";
	gkkey_dgreek[a_SM_AC_IS] = "\220i?";
	gkkey_dgreek[a_SM_GR_IS] = "\222i?";
	gkkey_dgreek[a_SM_CI_IS] = "\224i?";
	gkkey_dgreek[a_RO_AC_IS] = "\221i?";
	gkkey_dgreek[a_RO_GR_IS] = "\223i?";
	gkkey_dgreek[a_RO_CI_IS] = "\225i?";
	gkkey_dgreek[a_AC_IS] = "\213i?";
	gkkey_dgreek[a_GR_IS] = "\214i?";
	gkkey_dgreek[a_CI_IS] = "\215i?";
	gkkey_dgreek[a_SM_IS] = "\216i?";
	gkkey_dgreek[a_RO_IS] = "\217i?";
	gkkey_dgreek[a_IS] = "ai?";
	gkkey_dgreek[ALPHA] = "A?";
	gkkey_dgreek[A_SM_CI] = "\211A?";
	gkkey_dgreek[A_SM_AC] = "\205A?";
	gkkey_dgreek[A_SM_GR] = "\207A?";
	gkkey_dgreek[A_RO_CI] = "\212A?";
	gkkey_dgreek[A_RO_AC] = "\206A?";
	gkkey_dgreek[A_RO_GR] = "\210A?";
	gkkey_dgreek[A_SM] = "\203A?";
	gkkey_dgreek[A_RO] = "\204A?";
	gkkey_dgreek[A_CI] = "\202A?";
	gkkey_dgreek[beta] = "b?";
	gkkey_dgreek[BETA] = "B?";
	gkkey_dgreek[GAMMA] = "G?";
	gkkey_dgreek[gamma] = "g?";
	gkkey_dgreek[delta] = "d?";
	gkkey_dgreek[DELTA] = "D?";
	gkkey_dgreek[epsilon] = "e?";
	gkkey_dgreek[EPSILON] = "E?";
	gkkey_dgreek[e_SM_AC] = "\246?";
	gkkey_dgreek[e_SM_GR] = "\250?";
	gkkey_dgreek[e_RO_AC] = "\247?";
	gkkey_dgreek[e_RO_GR] = "\251?";
	gkkey_dgreek[e_AC] = "\241?";
	gkkey_dgreek[e_GR] = "\242?";
	gkkey_dgreek[e_SM] = "\244?";
	gkkey_dgreek[e_RO] = "\245?";
	gkkey_dgreek[E_SM_AC] = "\205E?";
	gkkey_dgreek[E_SM_GR] = "\207E?";
	gkkey_dgreek[E_RO_AC] = "\206E?";
	gkkey_dgreek[E_RO_GR] = "\210E?";
	gkkey_dgreek[E_SM] = "\203E?";
	gkkey_dgreek[E_RO] = "\204E?";
	gkkey_dgreek[hta] = "h?";
	gkkey_dgreek[HTA] = "H?";
	gkkey_dgreek[H_SM_CI] = "\211H?";
	gkkey_dgreek[H_SM_AC] = "\205H?";
	gkkey_dgreek[H_SM_GR] = "\207H?";
	gkkey_dgreek[H_RO_CI] = "\212H?";
	gkkey_dgreek[H_RO_AC] = "\206H?";
	gkkey_dgreek[H_RO_GR] = "\210H?";
	gkkey_dgreek[H_SM] = "\203H?";
	gkkey_dgreek[H_RO] = "\204H?";
	gkkey_dgreek[H_CI] = "\202H?";
	gkkey_dgreek[h_SM_AC] = "\263?";
	gkkey_dgreek[h_SM_GR] = "\265?";
	gkkey_dgreek[h_SM_CI] = "\267?";
	gkkey_dgreek[h_RO_AC] = "\264?";
	gkkey_dgreek[h_RO_GR] = "\266?";
	gkkey_dgreek[h_RO_CI] = "\270?";
	gkkey_dgreek[h_AC] = "\256?";
	gkkey_dgreek[h_GR] = "\257?";
	gkkey_dgreek[h_CI] = "\260?";
	gkkey_dgreek[h_SM] = "\261?";
	gkkey_dgreek[h_RO] = "\262?";
	gkkey_dgreek[h_SM_AC_IS] = "\263i?";
	gkkey_dgreek[h_SM_GR_IS] = "\265i?";
	gkkey_dgreek[h_SM_CI_IS] = "\267i?";
	gkkey_dgreek[h_RO_AC_IS] = "\264i?";
	gkkey_dgreek[h_RO_GR_IS] = "\266i?";
	gkkey_dgreek[h_RO_CI_IS] = "\270i?";
	gkkey_dgreek[h_AC_IS] = "\256i?";
	gkkey_dgreek[h_GR_IS] = "\257i?";
	gkkey_dgreek[h_CI_IS] = "\260i?";
	gkkey_dgreek[h_SM_IS] = "\261i?";
	gkkey_dgreek[h_RO_IS] = "\262i?";
	gkkey_dgreek[h_IS] = "hi?";
	gkkey_dgreek[zeta] = "z?";
	gkkey_dgreek[ZETA] = "Z?";
	gkkey_dgreek[qeta] = "y?";
	gkkey_dgreek[QETA] = "Y?";
	gkkey_dgreek[iota] = "i?";
	gkkey_dgreek[IOTA] = "I?";
	gkkey_dgreek[i_SM_AC] = "\340?";
	gkkey_dgreek[i_SM_GR] = "\342?";
	gkkey_dgreek[i_SM_CI] = "\344?";
	gkkey_dgreek[i_RO_AC] = "\341?";
	gkkey_dgreek[i_RO_GR] = "\343?";
	gkkey_dgreek[i_RO_CI] = "\345?";
	gkkey_dgreek[i_DI] = "\363?";
	gkkey_dgreek[i_AC_DI] = "\375?";	/* diaereses not available here*/
	gkkey_dgreek[i_GR_DI] = "\376?";
	gkkey_dgreek[i_AC] = "\333?";
	gkkey_dgreek[i_GR] = "\334?";
	gkkey_dgreek[i_CI] = "\335?";
	gkkey_dgreek[i_SM] = "\336?";
	gkkey_dgreek[i_RO] = "\337?";
	gkkey_dgreek[I_SM_CI] = "\211I?";
	gkkey_dgreek[I_SM_AC] = "\205I?";
	gkkey_dgreek[I_SM_GR] = "\207I?";
	gkkey_dgreek[I_RO_CI] = "\212I?";
	gkkey_dgreek[I_RO_AC] = "\206I?";
	gkkey_dgreek[I_RO_GR] = "\210I?";
	gkkey_dgreek[I_SM] = "\203I?";
	gkkey_dgreek[I_RO] = "\204I?";
	gkkey_dgreek[I_CI] = "\202I?";
	gkkey_dgreek[I_AC] = "\200I?";
	gkkey_dgreek[I_GR] = "\201I?";
	gkkey_dgreek[kappa] = "k?";
	gkkey_dgreek[KAPPA] = "K?";
	gkkey_dgreek[lambda] = "l?";
	gkkey_dgreek[LAMBDA] = "L?";
	gkkey_dgreek[mu] = "m?";
	gkkey_dgreek[MU] = "M?";
	gkkey_dgreek[nu] = "n?";
	gkkey_dgreek[NU] = "N?";
	gkkey_dgreek[ci] = "j?";
	gkkey_dgreek[CI] = "J?";
	gkkey_dgreek[omicron] = "o?";
	gkkey_dgreek[OMICRON] = "O?";
	gkkey_dgreek[o_SM_AC] = "\366?";
	gkkey_dgreek[o_SM_GR] = "\370?";
	gkkey_dgreek[o_RO_AC] = "\367?";
	gkkey_dgreek[o_RO_GR] = "\371?";
	gkkey_dgreek[o_AC] = "\361?";
	gkkey_dgreek[o_GR] = "\362?";
	gkkey_dgreek[o_SM] = "\364?";
	gkkey_dgreek[o_RO] = "\365?";
	gkkey_dgreek[O_SM_AC] = "\205O?";
	gkkey_dgreek[O_SM_GR] = "\207O?";
	gkkey_dgreek[O_RO_AC] = "\206O?";
	gkkey_dgreek[O_RO_GR] = "\210O?";
	gkkey_dgreek[O_AC] = "\200O?";
	gkkey_dgreek[O_GR] = "\201O?";
	gkkey_dgreek[O_SM] = "\203O?";
	gkkey_dgreek[O_RO] = "\204O?";
	gkkey_dgreek[pi] = "p?";
	gkkey_dgreek[PI] = "P?";
	gkkey_dgreek[RHO] = "R?";
	gkkey_dgreek[R_SM] = "\\R?";
	gkkey_dgreek[R_RO] = "]R?";
	gkkey_dgreek[rho] = "r?";
	gkkey_dgreek[r_RO] = "\75?";
	gkkey_dgreek[r_SM] = "\261r?";
	gkkey_dgreek[SIGMA] = "S?";
	gkkey_dgreek[sigma] = "s?";
	gkkey_dgreek[tau] = "t?";
	gkkey_dgreek[TAU] = "T?";
	gkkey_dgreek[UPSILON] = "U?";
	gkkey_dgreek[U_SM_CI] = "\211U?";
	gkkey_dgreek[U_SM_AC] = "\205U?";
	gkkey_dgreek[U_SM_GR] = "\207U?";
	gkkey_dgreek[U_RO_CI] = "\212U?";
	gkkey_dgreek[U_RO_AC] = "\206U?";
	gkkey_dgreek[U_RO_GR] = "\210U?";
	gkkey_dgreek[U_SM] = "\203U?";
	gkkey_dgreek[U_RO] = "\204U?";
	gkkey_dgreek[U_CI] = "\202U?";
	gkkey_dgreek[U_AC] = "\200U?";
	gkkey_dgreek[U_GR] = "\201U?";
	gkkey_dgreek[upsilon] = "u?";
	gkkey_dgreek[u_SM_AC] = "\353?";
	gkkey_dgreek[u_SM_GR] = "\355?";
	gkkey_dgreek[u_SM_CI] = "\357?";
	gkkey_dgreek[u_RO_AC] = "\354?";
	gkkey_dgreek[u_RO_GR] = "\356?";
	gkkey_dgreek[u_RO_CI] = "\360?";
	gkkey_dgreek[u_DI] = "\43?";
	gkkey_dgreek[u_AC_DI] = "\100?";
	gkkey_dgreek[u_GR_DI] = "\347?"; /* this combo not available*/
	gkkey_dgreek[u_AC] = "\346?";
	gkkey_dgreek[u_GR] = "\347?";
	gkkey_dgreek[u_CI] = "\350?";
	gkkey_dgreek[u_SM] = "\351?";
	gkkey_dgreek[u_RO] = "\352?";
	gkkey_dgreek[FI] = "F?";
	gkkey_dgreek[fi] = "f?";
	gkkey_dgreek[xi] = "x?";
	gkkey_dgreek[XI] = "X?";
	gkkey_dgreek[yi] = "c?";
	gkkey_dgreek[YI] = "C?";
	gkkey_dgreek[WMEGA] = "V?";
	gkkey_dgreek[wmega] = "v?";
	gkkey_dgreek[w_SM_AC] = "\312?";
	gkkey_dgreek[w_SM_GR] = "\314?";
	gkkey_dgreek[w_SM_CI] = "\316?";
	gkkey_dgreek[w_RO_AC] = "\313?";
	gkkey_dgreek[w_RO_GR] = "\315?";
	gkkey_dgreek[w_RO_CI] = "\317?";
	gkkey_dgreek[w_AC] = "\305?";
	gkkey_dgreek[w_GR] = "\306?";
	gkkey_dgreek[w_CI] = "\307?";
	gkkey_dgreek[w_SM] = "\310?";
	gkkey_dgreek[w_RO] = "\311?";
	gkkey_dgreek[W_SM_CI] = "\211V?";
	gkkey_dgreek[W_SM_AC] = "\205V?";
	gkkey_dgreek[W_SM_GR] = "\207V?";
	gkkey_dgreek[W_RO_CI] = "\212V?";
	gkkey_dgreek[W_RO_AC] = "\206V?";
	gkkey_dgreek[W_RO_GR] = "\210V?";
	gkkey_dgreek[W_SM] = "\203V?";
	gkkey_dgreek[W_RO] = "\204V?";
	gkkey_dgreek[W_CI] = "\202V?";
	gkkey_dgreek[W_AC] = "\200V?";
	gkkey_dgreek[W_GR] = "\201V?";
	gkkey_dgreek[w_IS] = "vi?";
	gkkey_dgreek[w_SM_AC_IS] = "\312i?";
	gkkey_dgreek[w_SM_GR_IS] = "\314i?";
	gkkey_dgreek[w_SM_CI_IS] = "\316i?";
	gkkey_dgreek[w_RO_AC_IS] = "\313i?";
	gkkey_dgreek[w_RO_GR_IS] = "\315i?";
	gkkey_dgreek[w_RO_CI_IS] = "\317i?";
	gkkey_dgreek[w_AC_IS] = "\305i?";
	gkkey_dgreek[w_GR_IS] = "\306i?";
	gkkey_dgreek[w_CI_IS] = "\307i?";
	gkkey_dgreek[w_SM_IS] = "\310i?";
	gkkey_dgreek[w_RO_IS] = "\311i?";
	gkkey_dgreek[tsigma] = "w?";
	gkkey_dgreek[ELLIPSIS] = ".";
}

	char *gkkey_punct[] = {
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
		
char * gkkey_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double bracket */
		"|_",	/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * gkkey_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double bracket */
		"_|",	/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * gkkey_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"''",		/* 1 low double close quote */
		"''",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *gkkey_tgreek = "";
char *gkkey_tbgreek = "";
char *gkkey_troman = "";

char * gkkey_newline = "\n";

fix_gkkey_save(fname)
char * fname;
{
}

add_gkkey_header(f)
FILE * f;
{
}
