/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
*** The octal codes are on the right.
*** scroll through looking for comments - marked ***
*** By the way, i included the diaeresis combinations that you
*** mark as not having - you can get rid of them if you want.
*** By the way, what should i do about the punctation?
*/
     
#include "filttab.h"

char * hft_greek[MAX_GK_CHARS];
char * hft_dgreek[MAX_GK_CHARS];

setup_hft_greek()
{
	hft_greek[alpha] = "a";
	hft_greek[a_SM_AC] = "\201";
	hft_greek[a_SM_GR] = "\202";
	hft_greek[a_SM_CI] = "\357";
	hft_greek[a_RO_AC] = "\206";
	hft_greek[a_RO_GR] = "\205";
	hft_greek[a_RO_CI] = "\356";
	hft_greek[a_AC] = "\207";
	hft_greek[a_GR] = "\210";
	hft_greek[a_CI] = "\213";
	hft_greek[a_SM] = "\200";
	hft_greek[a_RO] = "\177";
	hft_greek[a_SM_AC_IS] = "\201i";
	hft_greek[a_SM_GR_IS] = "\202i";
	hft_greek[a_SM_CI_IS] = "\357i";
	hft_greek[a_RO_AC_IS] = "\206i";
	hft_greek[a_RO_GR_IS] = "\205i";
	hft_greek[a_RO_CI_IS] = "\356i";
	hft_greek[a_AC_IS] = "\207i";
	hft_greek[a_GR_IS] = "\210i";
	hft_greek[a_CI_IS] = "\213i";
	hft_greek[a_SM_IS] = "\200i";
	hft_greek[a_RO_IS] = "\177i";
	hft_greek[a_IS] = "ai";
	hft_greek[ALPHA] = "A";
	hft_greek[A_SM_CI] = "\252A";
	hft_greek[A_SM_AC] = "\244A";
	hft_greek[A_SM_GR] = "\242A";
	hft_greek[A_RO_CI] = "\243A";
	hft_greek[A_RO_AC] = "\246A";
	hft_greek[A_RO_GR] = "\301A";
	hft_greek[A_SM] = "\260A";
	hft_greek[A_RO] = "\273A";
	hft_greek[A_CI] = "\176A";
	hft_greek[beta] = "b";
	hft_greek[BETA] = "B";
	hft_greek[GAMMA] = "G";
	hft_greek[gamma] = "g";
	hft_greek[delta] = "d";
	hft_greek[DELTA] = "D";
	hft_greek[epsilon] = "e";
	hft_greek[EPSILON] = "E";
	hft_greek[e_SM_AC] = "\220";
	hft_greek[e_SM_GR] = "\221";
	hft_greek[e_RO_AC] = "\334";
	hft_greek[e_RO_GR] = "\313";
	hft_greek[e_AC] = "\216";
	hft_greek[e_GR] = "\217";
	hft_greek[e_SM] = "\212";
	hft_greek[e_RO] = "\211";
	hft_greek[E_SM_AC] = "\244E";
	hft_greek[E_SM_GR] = "\242E";
	hft_greek[E_RO_AC] = "\246E";
	hft_greek[E_RO_GR] = "\301E";
	hft_greek[E_SM] = "\260E";
	hft_greek[E_RO] = "\273E";
	hft_greek[hta] = "h";
	hft_greek[HTA] = "H";
	hft_greek[H_SM_CI] = "\252H";
	hft_greek[H_SM_AC] = "\244H";
	hft_greek[H_SM_GR] = "\242H";
	hft_greek[H_RO_CI] = "\243H";
	hft_greek[H_RO_AC] = "\246H";
	hft_greek[H_RO_GR] = "\301H";
	hft_greek[H_SM] = "\260H";
	hft_greek[H_RO] = "\273H";
	hft_greek[H_CI] = "\176H";
	hft_greek[h_SM_AC] = "\251";
	hft_greek[h_SM_GR] = "\261";
	hft_greek[h_SM_CI] = "\312";
	hft_greek[h_RO_AC] = "\250";
	hft_greek[h_RO_GR] = "\237";
	hft_greek[h_RO_CI] = "\351";
	hft_greek[h_AC] = "\262";
	hft_greek[h_GR] = "\236";
	hft_greek[h_CI] = "\204";
	hft_greek[h_SM] = "\263";
	hft_greek[h_RO] = "\241";
	hft_greek[h_SM_AC_IS] = "\251i";
	hft_greek[h_SM_GR_IS] = "\261i";
	hft_greek[h_SM_CI_IS] = "\312i";
	hft_greek[h_RO_AC_IS] = "\250i";
	hft_greek[h_RO_GR_IS] = "\237i";
	hft_greek[h_RO_CI_IS] = "\351i";
	hft_greek[h_AC_IS] = "\262i";
	hft_greek[h_GR_IS] = "\236i";
	hft_greek[h_CI_IS] = "\204i";
	hft_greek[h_SM_IS] = "\263i";
	hft_greek[h_RO_IS] = "\241i";
	hft_greek[zeta] = "z";
	hft_greek[ZETA] = "Z";
	hft_greek[qeta] = "u";
	hft_greek[QETA] = "U";
	hft_greek[iota] = "i";
	hft_greek[IOTA] = "I";
	hft_greek[i_SM_AC] = "\267";
	hft_greek[i_SM_GR] = "\240";
	hft_greek[i_SM_CI] = "\235";
	hft_greek[i_RO_AC] = "\231";
	hft_greek[i_RO_GR] = "\265";
	hft_greek[i_RO_CI] = "\336";
	hft_greek[i_DI] = "\277";
	hft_greek[i_AC_DI] = "\315";
	hft_greek[i_GR_DI] = "\136";
	hft_greek[i_AC] = "\222";
	hft_greek[i_GR] = "\223";
	hft_greek[i_CI] = "\330";
	hft_greek[i_SM] = "\226";
	hft_greek[i_RO] = "\224";
	hft_greek[I_SM_CI] = "\252I";
	hft_greek[I_SM_AC] = "\244I";
	hft_greek[I_SM_GR] = "\242I";
	hft_greek[I_RO_CI] = "\243I";
	hft_greek[I_RO_AC] = "\246I";
	hft_greek[I_RO_GR] = "\301I";
	hft_greek[I_SM] = "\260I";
	hft_greek[I_RO] = "\273I";
	hft_greek[I_CI] = "\176I";
	hft_greek[I_AC] = "\253I";
	hft_greek[I_GR] = "\140I";
	hft_greek[kappa] = "k";
	hft_greek[KAPPA] = "K";
	hft_greek[lambda] = "l";
	hft_greek[LAMBDA] = "L";
	hft_greek[mu] = "m";
	hft_greek[MU] = "M";
	hft_greek[nu] = "n";
	hft_greek[NU] = "N";
	hft_greek[ci] = "j";
	hft_greek[CI] = "J";
	hft_greek[omicron] = "o";
	hft_greek[OMICRON] = "O";
	hft_greek[o_SM_AC] = "\344";
	hft_greek[o_SM_GR] = "\343";
	hft_greek[o_RO_AC] = "\345";
	hft_greek[o_RO_GR] = "\270";
	hft_greek[o_AC] = "\227";
	hft_greek[o_GR] = "\230";
	hft_greek[o_SM] = "\234";
	hft_greek[o_RO] = "\257";
	hft_greek[O_SM_AC] = "\244O";
	hft_greek[O_SM_GR] = "\242O";
	hft_greek[O_RO_AC] = "\246O";
	hft_greek[O_RO_GR] = "\301O";
	hft_greek[O_AC] = "\253O";
	hft_greek[O_GR] = "\140O";
	hft_greek[O_SM] = "\260O";
	hft_greek[O_RO] = "\273O";
	hft_greek[pi] = "p";
	hft_greek[PI] = "P";
	hft_greek[RHO] = "R";
	hft_greek[R_SM] = "\260R";
	hft_greek[R_RO] = "\273R";
	hft_greek[rho] = "r";
	hft_greek[r_SM] = "\260r";
	hft_greek[r_RO] = "\360";
	hft_greek[SIGMA] = "S";
	hft_greek[sigma] = "\247";
	hft_greek[tau] = "t";
	hft_greek[TAU] = "T";
	hft_greek[UPSILON] = "Y";
	hft_greek[U_SM_CI] = "\252Y";
	hft_greek[U_SM_AC] = "\244Y";
	hft_greek[U_SM_GR] = "\242Y";
	hft_greek[U_RO_CI] = "\243Y";
	hft_greek[U_RO_AC] = "\246Y";
	hft_greek[U_RO_GR] = "\301Y";
	hft_greek[U_SM] = "\260Y";
	hft_greek[U_RO] = "\273Y";
	hft_greek[U_CI] = "\176Y";
	hft_greek[U_AC] = "\253Y";
	hft_greek[U_GR] = "\140Y";
	hft_greek[upsilon] = "y";
	hft_greek[u_SM_AC] = "\302";
	hft_greek[u_SM_GR] = "\307";
	hft_greek[u_SM_CI] = "\342";
	hft_greek[u_RO_AC] = "\300";
	hft_greek[u_RO_GR] = "\335";
	hft_greek[u_RO_CI] = "\341";
	hft_greek[u_DI] = "\264";
	hft_greek[u_AC_DI] = "\254";
	hft_greek[u_GR_DI] = "\314";
	hft_greek[u_AC] = "\256";
	hft_greek[u_GR] = "\353";
	hft_greek[u_CI] = "\276";
	hft_greek[u_SM] = "\275";
	hft_greek[u_RO] = "\274";
	hft_greek[FI] = "F";
	hft_greek[fi] = "f";
	hft_greek[xi] = "x";
	hft_greek[XI] = "X";
	hft_greek[yi] = "c";
	hft_greek[YI] = "C";
	hft_greek[WMEGA] = "V";
	hft_greek[wmega] = "v";
	hft_greek[w_SM_AC] = "\364";
	hft_greek[w_SM_GR] = "\363";
	hft_greek[w_SM_CI] = "\362";
	hft_greek[w_RO_AC] = "\366";
	hft_greek[w_RO_GR] = "\365";
	hft_greek[w_RO_CI] = "\361";
	hft_greek[w_AC] = "\371";
	hft_greek[w_GR] = "\370";
	hft_greek[w_CI] = "\367";
	hft_greek[w_SM] = "\311";
	hft_greek[w_RO] = "\376";
	hft_greek[W_SM_CI] = "\252V";
	hft_greek[W_SM_AC] = "\244V";
	hft_greek[W_SM_GR] = "\242V";
	hft_greek[W_RO_CI] = "\243V";
	hft_greek[W_RO_AC] = "\246V";
	hft_greek[W_RO_GR] = "\301V";
	hft_greek[W_SM] = "\260V";
	hft_greek[W_RO] = "\273V";
	hft_greek[W_CI] = "\176V";
	hft_greek[W_AC] = "\253V";
	hft_greek[W_GR] = "\140V";
	hft_greek[w_IS] = "vi";
	hft_greek[w_SM_AC_IS] = "\364i";
	hft_greek[w_SM_GR_IS] = "\363i";
	hft_greek[w_SM_CI_IS] = "\362i";
	hft_greek[w_RO_AC_IS] = "\366i";
	hft_greek[w_RO_GR_IS] = "\365i";
	hft_greek[w_RO_CI_IS] = "\361i";
	hft_greek[w_AC_IS] = "\371i";
	hft_greek[w_GR_IS] = "\370i";
	hft_greek[w_CI_IS] = "\367i";
	hft_greek[w_SM_IS] = "\311i";
	hft_greek[w_RO_IS] = "\376i";
	hft_greek[tsigma] = "w";
	hft_greek[ELLIPSIS] = ".";
	 
	hft_dgreek[alpha] = "a?";
	hft_dgreek[a_SM_AC] = "\201?";
	hft_dgreek[a_SM_GR] = "\202?";
	hft_dgreek[a_SM_CI] = "\357?";
	hft_dgreek[a_RO_AC] = "\206?";
	hft_dgreek[a_RO_GR] = "\205?";
	hft_dgreek[a_RO_CI] = "\356?";
	hft_dgreek[a_AC] = "\207?";
	hft_dgreek[a_GR] = "\210?";
	hft_dgreek[a_CI] = "\213?";
	hft_dgreek[a_SM] = "\200?";
	hft_dgreek[a_RO] = "\177?";
	hft_dgreek[a_SM_AC_IS] = "\201i?";
	hft_dgreek[a_SM_GR_IS] = "\202i?";
	hft_dgreek[a_SM_CI_IS] = "\357i?";
	hft_dgreek[a_RO_AC_IS] = "\206i?";
	hft_dgreek[a_RO_GR_IS] = "\205i?";
	hft_dgreek[a_RO_CI_IS] = "\356i?";
	hft_dgreek[a_AC_IS] = "\207i?";
	hft_dgreek[a_GR_IS] = "\210i?";
	hft_dgreek[a_CI_IS] = "\213i?";
	hft_dgreek[a_SM_IS] = "\200i?";
	hft_dgreek[a_RO_IS] = "\177i?";
	hft_dgreek[a_IS] = "ai?";
	hft_dgreek[ALPHA] = "A?";
	hft_dgreek[A_SM_CI] = "\252A?";
	hft_dgreek[A_SM_AC] = "\244A?";
	hft_dgreek[A_SM_GR] = "\242A?";
	hft_dgreek[A_RO_CI] = "\243A?";
	hft_dgreek[A_RO_AC] = "\246A?";
	hft_dgreek[A_RO_GR] = "\301A?";
	hft_dgreek[A_SM] = "\260A?";
	hft_dgreek[A_RO] = "\273A?";
	hft_dgreek[A_CI] = "\176A?";
	hft_dgreek[beta] = "b?";
	hft_dgreek[BETA] = "B?";
	hft_dgreek[GAMMA] = "G?";
	hft_dgreek[gamma] = "g?";
	hft_dgreek[delta] = "d?";
	hft_dgreek[DELTA] = "D?";
	hft_dgreek[epsilon] = "e?";
	hft_dgreek[EPSILON] = "E?";
	hft_dgreek[e_SM_AC] = "\220?";
	hft_dgreek[e_SM_GR] = "\221?";
	hft_dgreek[e_RO_AC] = "\334?";
	hft_dgreek[e_RO_GR] = "\313?";
	hft_dgreek[e_AC] = "\216?";
	hft_dgreek[e_GR] = "\217?";
	hft_dgreek[e_SM] = "\212?";
	hft_dgreek[e_RO] = "\211?";
	hft_dgreek[E_SM_AC] = "\244E?";
	hft_dgreek[E_SM_GR] = "\242E?";
	hft_dgreek[E_RO_AC] = "\246E?";
	hft_dgreek[E_RO_GR] = "\301E?";
	hft_dgreek[E_SM] = "\260E?";
	hft_dgreek[E_RO] = "\273E?";
	hft_dgreek[hta] = "h?";
	hft_dgreek[HTA] = "H?";
	hft_dgreek[H_SM_CI] = "\252H?";
	hft_dgreek[H_SM_AC] = "\244H?";
	hft_dgreek[H_SM_GR] = "\242H?";
	hft_dgreek[H_RO_CI] = "\243H?";
	hft_dgreek[H_RO_AC] = "\246H?";
	hft_dgreek[H_RO_GR] = "\301H?";
	hft_dgreek[H_SM] = "\260H?";
	hft_dgreek[H_RO] = "\273H?";
	hft_dgreek[H_CI] = "\176H?";
	hft_dgreek[h_SM_AC] = "\251?";
	hft_dgreek[h_SM_GR] = "\261?";
	hft_dgreek[h_SM_CI] = "\312?";
	hft_dgreek[h_RO_AC] = "\250?";
	hft_dgreek[h_RO_GR] = "\237?";
	hft_dgreek[h_RO_CI] = "\351?";
	hft_dgreek[h_AC] = "\262?";
	hft_dgreek[h_GR] = "\236?";
	hft_dgreek[h_CI] = "\204?";
	hft_dgreek[h_SM] = "\263?";
	hft_dgreek[h_RO] = "\241?";
	hft_dgreek[h_SM_AC_IS] = "\251i?";
	hft_dgreek[h_SM_GR_IS] = "\261i?";
	hft_dgreek[h_SM_CI_IS] = "\312i?";
	hft_dgreek[h_RO_AC_IS] = "\250i?";
	hft_dgreek[h_RO_GR_IS] = "\237i?";
	hft_dgreek[h_RO_CI_IS] = "\351i?";
	hft_dgreek[h_AC_IS] = "\262i?";
	hft_dgreek[h_GR_IS] = "\236i?";
	hft_dgreek[h_CI_IS] = "\204i?";
	hft_dgreek[h_SM_IS] = "\263i?";
	hft_dgreek[h_RO_IS] = "\241i?";
	hft_dgreek[zeta] = "z?";
	hft_dgreek[ZETA] = "Z?";
	hft_dgreek[qeta] = "u?";
	hft_dgreek[QETA] = "U?";
	hft_dgreek[iota] = "i?";
	hft_dgreek[IOTA] = "I?";
	hft_dgreek[i_SM_AC] = "\267?";
	hft_dgreek[i_SM_GR] = "\240?";
	hft_dgreek[i_SM_CI] = "\235?";
	hft_dgreek[i_RO_AC] = "\231?";
	hft_dgreek[i_RO_GR] = "\265?";
	hft_dgreek[i_RO_CI] = "\336?";
	hft_dgreek[i_DI] = "\277?";
	hft_dgreek[i_AC_DI] = "\315?";
	hft_dgreek[i_GR_DI] = "\136?";
	hft_dgreek[i_AC] = "\222?";
	hft_dgreek[i_GR] = "\223?";
	hft_dgreek[i_CI] = "\330?";
	hft_dgreek[i_SM] = "\226?";
	hft_dgreek[i_RO] = "\224?";
	hft_dgreek[I_SM_CI] = "\252I?";
	hft_dgreek[I_SM_AC] = "\244I?";
	hft_dgreek[I_SM_GR] = "\242I?";
	hft_dgreek[I_RO_CI] = "\243I?";
	hft_dgreek[I_RO_AC] = "\246I?";
	hft_dgreek[I_RO_GR] = "\301I?";
	hft_dgreek[I_SM] = "\260I?";
	hft_dgreek[I_RO] = "\273I?";
	hft_dgreek[I_CI] = "\176I?";
	hft_dgreek[I_AC] = "\253I?";
	hft_dgreek[I_GR] = "\140I?";
	hft_dgreek[kappa] = "k?";
	hft_dgreek[KAPPA] = "K?";
	hft_dgreek[lambda] = "l?";
	hft_dgreek[LAMBDA] = "L?";
	hft_dgreek[mu] = "m?";
	hft_dgreek[MU] = "M?";
	hft_dgreek[nu] = "n?";
	hft_dgreek[NU] = "N?";
	hft_dgreek[ci] = "j?";
	hft_dgreek[CI] = "J?";
	hft_dgreek[omicron] = "o?";
	hft_dgreek[OMICRON] = "O?";
	hft_dgreek[o_SM_AC] = "\344?";
	hft_dgreek[o_SM_GR] = "\343?";
	hft_dgreek[o_RO_AC] = "\345?";
	hft_dgreek[o_RO_GR] = "\270?";
	hft_dgreek[o_AC] = "\227?";
	hft_dgreek[o_GR] = "\230?";
	hft_dgreek[o_SM] = "\234?";
	hft_dgreek[o_RO] = "\257?";
	hft_dgreek[O_SM_AC] = "\244O?";
	hft_dgreek[O_SM_GR] = "\242O?";
	hft_dgreek[O_RO_AC] = "\246O?";
	hft_dgreek[O_RO_GR] = "\301O?";
	hft_dgreek[O_AC] = "\253O?";
	hft_dgreek[O_GR] = "\140O?";
	hft_dgreek[O_SM] = "\260O?";
	hft_dgreek[O_RO] = "\273O?";
	hft_dgreek[pi] = "p?";
	hft_dgreek[PI] = "P?";
	hft_dgreek[RHO] = "R?";
	hft_dgreek[R_SM] = "\260R?";
	hft_dgreek[R_RO] = "\273R?";
	hft_dgreek[rho] = "r?";
	hft_dgreek[r_SM] = "\260r?";
	hft_dgreek[r_RO] = "\360r?";
	hft_dgreek[SIGMA] = "S?";
	hft_dgreek[sigma] = "\247?";
	hft_dgreek[tau] = "t?";
	hft_dgreek[TAU] = "T?";
	hft_dgreek[UPSILON] = "Y?";
	hft_dgreek[U_SM_CI] = "\252Y?";
	hft_dgreek[U_SM_AC] = "\244Y?";
	hft_dgreek[U_SM_GR] = "\242Y?";
	hft_dgreek[U_RO_CI] = "\243Y?";
	hft_dgreek[U_RO_AC] = "\246Y?";
	hft_dgreek[U_RO_GR] = "\301Y?";
	hft_dgreek[U_SM] = "\260Y?";
	hft_dgreek[U_RO] = "\273Y?";
	hft_dgreek[U_CI] = "\176Y?";
	hft_dgreek[U_AC] = "\253Y?";
	hft_dgreek[U_GR] = "\140Y?";
	hft_dgreek[upsilon] = "y?";
	hft_dgreek[u_SM_AC] = "\302?";
	hft_dgreek[u_SM_GR] = "\307?";
	hft_dgreek[u_SM_CI] = "\342?";
	hft_dgreek[u_RO_AC] = "\300?";
	hft_dgreek[u_RO_GR] = "\335?";
	hft_dgreek[u_RO_CI] = "\341?";
	hft_dgreek[u_DI] = "\264?";
	hft_dgreek[u_AC_DI] = "\254?";
	hft_dgreek[u_GR_DI] = "\314?";
	hft_dgreek[u_AC] = "\256?";
	hft_dgreek[u_GR] = "\353?";
	hft_dgreek[u_CI] = "\276?";
	hft_dgreek[u_SM] = "\275?";
	hft_dgreek[u_RO] = "\274?";
	hft_dgreek[FI] = "F?";
	hft_dgreek[fi] = "f?";
	hft_dgreek[xi] = "x?";
	hft_dgreek[XI] = "X?";
	hft_dgreek[yi] = "c?";
	hft_dgreek[YI] = "C?";
	hft_dgreek[WMEGA] = "V?";
	hft_dgreek[wmega] = "v?";
	hft_dgreek[w_SM_AC] = "\364?";
	hft_dgreek[w_SM_GR] = "\363?";
	hft_dgreek[w_SM_CI] = "\362?";
	hft_dgreek[w_RO_AC] = "\366?";
	hft_dgreek[w_RO_GR] = "\365?";
	hft_dgreek[w_RO_CI] = "\361?";
	hft_dgreek[w_AC] = "\371?";
	hft_dgreek[w_GR] = "\370?";
	hft_dgreek[w_CI] = "\367?";
	hft_dgreek[w_SM] = "\311?";
	hft_dgreek[w_RO] = "\376?";
	hft_dgreek[W_SM_CI] = "\252V?";
	hft_dgreek[W_SM_AC] = "\244V?";
	hft_dgreek[W_SM_GR] = "\242V?";
	hft_dgreek[W_RO_CI] = "\243V?";
	hft_dgreek[W_RO_AC] = "\246V?";
	hft_dgreek[W_RO_GR] = "\301V?";
	hft_dgreek[W_SM] = "\260V?";
	hft_dgreek[W_RO] = "\273V?";
	hft_dgreek[W_CI] = "\176V?";
	hft_dgreek[W_AC] = "\253V?";
	hft_dgreek[W_GR] = "\140V?";
	hft_dgreek[w_IS] = "vi?";
	hft_dgreek[w_SM_AC_IS] = "\364i?";
	hft_dgreek[w_SM_GR_IS] = "\363i?";
	hft_dgreek[w_SM_CI_IS] = "\362i?";
	hft_dgreek[w_RO_AC_IS] = "\366i?";
	hft_dgreek[w_RO_GR_IS] = "\365i?";
	hft_dgreek[w_RO_CI_IS] = "\361i?";
	hft_dgreek[w_AC_IS] = "\371i?";
	hft_dgreek[w_GR_IS] = "\370i?";
	hft_dgreek[w_CI_IS] = "\367i?";
	hft_dgreek[w_SM_IS] = "\311i?";
	hft_dgreek[w_RO_IS] = "\376i?";
	hft_dgreek[tsigma] = "w?";
	hft_dgreek[ELLIPSIS] = ".?";
}

	char *hft_punct[] = {
		"\255", /* 0 dagger */
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
		"\255", /* 13 (should be) double dagger */
		"(Sect)", 	/* 14 paragraph sign */
		"|",		/* 15 should be short vertical bar */
		"|",		/* 16 should be broken vertical bar */
		"||",	/* 17 double vertical bar */
	};
		
char * hft_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double bracket */
		"|_",	/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * hft_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double bracket */
		"|_",	/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * hft_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"''",		/* 1 low double close quote */
		"''",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *hft_tgreek = "\016";
char *hft_tbgreek = "";
char *hft_troman = "\017";

char * hft_newline = "\n";



fix_hft_save(fname)
char * fname;
{
}

add_hft_header(f)
FILE * f;
{
}
