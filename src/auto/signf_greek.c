/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
*** The octal codes are on the right.
*** scroll through looking for comments - marked ***
*** eta with iota subscript added 9/22/86 by PDK ***
*/
     
#include "filttab.h"

char * signf_greek[MAX_GK_CHARS];
char * signf_dgreek[MAX_GK_CHARS];

setup_signf_greek()
{
	signf_greek[alpha] = "a";
	signf_greek[a_SM_AC] = "\201";
	signf_greek[a_SM_GR] = "\202";
	signf_greek[a_SM_CI] = "\357";
	signf_greek[a_RO_AC] = "\206";
	signf_greek[a_RO_GR] = "\205";
	signf_greek[a_RO_CI] = "\356";
	signf_greek[a_AC] = "\207";
	signf_greek[a_GR] = "\210";
	signf_greek[a_CI] = "\213";
	signf_greek[a_SM] = "\200";
	signf_greek[a_RO] = "\177";
	signf_greek[a_SM_AC_IS] = "\201i";
	signf_greek[a_SM_GR_IS] = "\202i";
	signf_greek[a_SM_CI_IS] = "\357i";
	signf_greek[a_RO_AC_IS] = "\206i";
	signf_greek[a_RO_GR_IS] = "\205i";
	signf_greek[a_RO_CI_IS] = "\356i";
	signf_greek[a_AC_IS] = "\207i";
	signf_greek[a_GR_IS] = "\210i";
	signf_greek[a_CI_IS] = "\213i";
	signf_greek[a_SM_IS] = "\200i";
	signf_greek[a_RO_IS] = "\177i";
	signf_greek[a_IS] = "ai";
	signf_greek[ALPHA] = "A";
	signf_greek[A_SM_CI] = "\252A";
	signf_greek[A_SM_AC] = "\244A";
	signf_greek[A_SM_GR] = "\242A";
	signf_greek[A_RO_CI] = "\243A";
	signf_greek[A_RO_AC] = "\246A";
	signf_greek[A_RO_GR] = "\301A";
	signf_greek[A_SM] = "\260A";
	signf_greek[A_RO] = "\273A";
	signf_greek[A_CI] = "\176A";
	signf_greek[beta] = "b";
	signf_greek[BETA] = "B";
	signf_greek[GAMMA] = "G";
	signf_greek[gamma] = "g";
	signf_greek[delta] = "d";
	signf_greek[DELTA] = "D";
	signf_greek[epsilon] = "e";
	signf_greek[EPSILON] = "E";
	signf_greek[e_SM_AC] = "\220";
	signf_greek[e_SM_GR] = "\221";
	signf_greek[e_RO_AC] = "\334";
	signf_greek[e_RO_GR] = "\313";
	signf_greek[e_AC] = "\216";
	signf_greek[e_GR] = "\217";
	signf_greek[e_SM] = "\212";
	signf_greek[e_RO] = "\211";
	signf_greek[E_SM_AC] = "\244E";
	signf_greek[E_SM_GR] = "\242E";
	signf_greek[E_RO_AC] = "\246E";
	signf_greek[E_RO_GR] = "\301E";
	signf_greek[E_SM] = "\260E";
	signf_greek[E_RO] = "\273E";
	signf_greek[hta] = "h";
	signf_greek[HTA] = "H";
	signf_greek[H_SM_CI] = "\252H";
	signf_greek[H_SM_AC] = "\244H";
	signf_greek[H_SM_GR] = "\242H";
	signf_greek[H_RO_CI] = "\243H";
	signf_greek[H_RO_AC] = "\246H";
	signf_greek[H_RO_GR] = "\301H";
	signf_greek[H_SM] = "\260H";
	signf_greek[H_RO] = "\273H";
	signf_greek[H_CI] = "\176H";
	signf_greek[h_SM_AC] = "\251";
	signf_greek[h_SM_GR] = "\261";
	signf_greek[h_SM_CI] = "\312";
	signf_greek[h_RO_AC] = "\250";
	signf_greek[h_RO_GR] = "\237";
	signf_greek[h_RO_CI] = "\351";
	signf_greek[h_AC] = "\262";
	signf_greek[h_GR] = "\236";
	signf_greek[h_CI] = "\204";
	signf_greek[h_SM] = "\263";
	signf_greek[h_RO] = "\241";
	signf_greek[h_SM_AC_IS] = "\251i";
	signf_greek[h_SM_GR_IS] = "\261i";
	signf_greek[h_SM_CI_IS] = "\312i";
	signf_greek[h_RO_AC_IS] = "\250i";
	signf_greek[h_RO_GR_IS] = "\237i";
	signf_greek[h_RO_CI_IS] = "\351i";
	signf_greek[h_AC_IS] = "\262i";
	signf_greek[h_GR_IS] = "\236i";
	signf_greek[h_CI_IS] = "\204i";
	signf_greek[h_SM_IS] = "\263i";
	signf_greek[h_RO_IS] = "\241i";
	signf_greek[h_IS] = "\374";
	signf_greek[zeta] = "z";
	signf_greek[ZETA] = "Z";
	signf_greek[qeta] = "u";
	signf_greek[QETA] = "U";
	signf_greek[iota] = "i";
	signf_greek[IOTA] = "I";
	signf_greek[i_SM_AC] = "\267";
	signf_greek[i_SM_GR] = "\240";
	signf_greek[i_SM_CI] = "\235";
	signf_greek[i_RO_AC] = "\231";
	signf_greek[i_RO_GR] = "\265";
	signf_greek[i_RO_CI] = "\336";
	signf_greek[i_DI] = "\277";
	signf_greek[i_AC_DI] = "\315";
	signf_greek[i_GR_DI] = "\136";
	signf_greek[i_AC] = "\222";
	signf_greek[i_GR] = "\223";
	signf_greek[i_CI] = "\330";
	signf_greek[i_SM] = "\226";
	signf_greek[i_RO] = "\224";
	signf_greek[I_SM_CI] = "\252I";
	signf_greek[I_SM_AC] = "\244I";
	signf_greek[I_SM_GR] = "\242I";
	signf_greek[I_RO_CI] = "\243I";
	signf_greek[I_RO_AC] = "\246I";
	signf_greek[I_RO_GR] = "\301I";
	signf_greek[I_SM] = "\260I";
	signf_greek[I_RO] = "\273I";
	signf_greek[I_CI] = "\176I";
	signf_greek[I_AC] = "\253I";
	signf_greek[I_GR] = "\140I";
	signf_greek[kappa] = "k";
	signf_greek[KAPPA] = "K";
	signf_greek[lambda] = "l";
	signf_greek[LAMBDA] = "L";
	signf_greek[mu] = "m";
	signf_greek[MU] = "M";
	signf_greek[nu] = "n";
	signf_greek[NU] = "N";
	signf_greek[ci] = "j";
	signf_greek[CI] = "J";
	signf_greek[omicron] = "o";
	signf_greek[OMICRON] = "O";
	signf_greek[o_SM_AC] = "\344";
	signf_greek[o_SM_GR] = "\343";
	signf_greek[o_RO_AC] = "\345";
	signf_greek[o_RO_GR] = "\270";
	signf_greek[o_AC] = "\227";
	signf_greek[o_GR] = "\230";
	signf_greek[o_SM] = "\234";
	signf_greek[o_RO] = "\257";
	signf_greek[O_SM_AC] = "\244O";
	signf_greek[O_SM_GR] = "\242O";
	signf_greek[O_RO_AC] = "\246O";
	signf_greek[O_RO_GR] = "\301O";
	signf_greek[O_AC] = "\253O";
	signf_greek[O_GR] = "\140O";
	signf_greek[O_SM] = "\260O";
	signf_greek[O_RO] = "\273O";
	signf_greek[pi] = "p";
	signf_greek[PI] = "P";
	signf_greek[RHO] = "R";
	signf_greek[R_SM] = "\260R";
	signf_greek[R_RO] = "\273R";
	signf_greek[rho] = "r";
	signf_greek[r_SM] = "\260r";
	signf_greek[r_RO] = "\360";
	signf_greek[SIGMA] = "S";
	signf_greek[sigma] = "s";
	signf_greek[tau] = "t";
	signf_greek[TAU] = "T";
	signf_greek[UPSILON] = "Y";
	signf_greek[U_SM_CI] = "\252Y";
	signf_greek[U_SM_AC] = "\244Y";
	signf_greek[U_SM_GR] = "\242Y";
	signf_greek[U_RO_CI] = "\243Y";
	signf_greek[U_RO_AC] = "\246Y";
	signf_greek[U_RO_GR] = "\301Y";
	signf_greek[U_SM] = "\260Y";
	signf_greek[U_RO] = "\273Y";
	signf_greek[U_CI] = "\176Y";
	signf_greek[U_AC] = "\253Y";
	signf_greek[U_GR] = "\140Y";
	signf_greek[upsilon] = "y";
	signf_greek[u_SM_AC] = "\302";
	signf_greek[u_SM_GR] = "\307";
	signf_greek[u_SM_CI] = "\342";
	signf_greek[u_RO_AC] = "\300";
	signf_greek[u_RO_GR] = "\335";
	signf_greek[u_RO_CI] = "\341";
	signf_greek[u_DI] = "\264";
	signf_greek[u_AC_DI] = "\254";
	signf_greek[u_GR_DI] = "\314";
	signf_greek[u_AC] = "\256";
	signf_greek[u_GR] = "\353";
	signf_greek[u_CI] = "\276";
	signf_greek[u_SM] = "\275";
	signf_greek[u_RO] = "\274";
	signf_greek[FI] = "F";
	signf_greek[fi] = "f";
	signf_greek[xi] = "x";
	signf_greek[XI] = "X";
	signf_greek[yi] = "c";
	signf_greek[YI] = "C";
	signf_greek[WMEGA] = "V";
	signf_greek[wmega] = "v";
	signf_greek[w_SM_AC] = "\364";
	signf_greek[w_SM_GR] = "\363";
	signf_greek[w_SM_CI] = "\362";
	signf_greek[w_RO_AC] = "\366";
	signf_greek[w_RO_GR] = "\365";
	signf_greek[w_RO_CI] = "\361";
	signf_greek[w_AC] = "\371";
	signf_greek[w_GR] = "\370";
	signf_greek[w_CI] = "\367";
	signf_greek[w_SM] = "\311";
	signf_greek[w_RO] = "\376";
	signf_greek[W_SM_CI] = "\252V";
	signf_greek[W_SM_AC] = "\244V";
	signf_greek[W_SM_GR] = "\242V";
	signf_greek[W_RO_CI] = "\243V";
	signf_greek[W_RO_AC] = "\246V";
	signf_greek[W_RO_GR] = "\301V";
	signf_greek[W_SM] = "\260V";
	signf_greek[W_RO] = "\273V";
	signf_greek[W_CI] = "\176V";
	signf_greek[W_AC] = "\253V";
	signf_greek[W_GR] = "\140V";
	signf_greek[w_IS] = "vi";
	signf_greek[w_SM_AC_IS] = "\364i";
	signf_greek[w_SM_GR_IS] = "\363i";
	signf_greek[w_SM_CI_IS] = "\362i";
	signf_greek[w_RO_AC_IS] = "\366i";
	signf_greek[w_RO_GR_IS] = "\365i";
	signf_greek[w_RO_CI_IS] = "\361i";
	signf_greek[w_AC_IS] = "\371i";
	signf_greek[w_GR_IS] = "\370i";
	signf_greek[w_CI_IS] = "\367i";
	signf_greek[w_SM_IS] = "\311i";
	signf_greek[w_RO_IS] = "\376i";
	signf_greek[tsigma] = "w";
	signf_greek[ELLIPSIS] = ".";
	 
	signf_dgreek[alpha] = "a?";
	signf_dgreek[a_SM_AC] = "\201?";
	signf_dgreek[a_SM_GR] = "\202?";
	signf_dgreek[a_SM_CI] = "\357?";
	signf_dgreek[a_RO_AC] = "\206?";
	signf_dgreek[a_RO_GR] = "\205?";
	signf_dgreek[a_RO_CI] = "\356?";
	signf_dgreek[a_AC] = "\207?";
	signf_dgreek[a_GR] = "\210?";
	signf_dgreek[a_CI] = "\213?";
	signf_dgreek[a_SM] = "\200?";
	signf_dgreek[a_RO] = "\177?";
	signf_dgreek[a_SM_AC_IS] = "\201i?";
	signf_dgreek[a_SM_GR_IS] = "\202i?";
	signf_dgreek[a_SM_CI_IS] = "\357i?";
	signf_dgreek[a_RO_AC_IS] = "\206i?";
	signf_dgreek[a_RO_GR_IS] = "\205i?";
	signf_dgreek[a_RO_CI_IS] = "\356i?";
	signf_dgreek[a_AC_IS] = "\207i?";
	signf_dgreek[a_GR_IS] = "\210i?";
	signf_dgreek[a_CI_IS] = "\213i?";
	signf_dgreek[a_SM_IS] = "\200i?";
	signf_dgreek[a_RO_IS] = "\177i?";
	signf_dgreek[a_IS] = "ai?";
	signf_dgreek[ALPHA] = "A?";
	signf_dgreek[A_SM_CI] = "\252A?";
	signf_dgreek[A_SM_AC] = "\244A?";
	signf_dgreek[A_SM_GR] = "\242A?";
	signf_dgreek[A_RO_CI] = "\243A?";
	signf_dgreek[A_RO_AC] = "\246A?";
	signf_dgreek[A_RO_GR] = "\301A?";
	signf_dgreek[A_SM] = "\260A?";
	signf_dgreek[A_RO] = "\273A?";
	signf_dgreek[A_CI] = "\176A?";
	signf_dgreek[beta] = "b?";
	signf_dgreek[BETA] = "B?";
	signf_dgreek[GAMMA] = "G?";
	signf_dgreek[gamma] = "g?";
	signf_dgreek[delta] = "d?";
	signf_dgreek[DELTA] = "D?";
	signf_dgreek[epsilon] = "e?";
	signf_dgreek[EPSILON] = "E?";
	signf_dgreek[e_SM_AC] = "\220?";
	signf_dgreek[e_SM_GR] = "\221?";
	signf_dgreek[e_RO_AC] = "\334?";
	signf_dgreek[e_RO_GR] = "\313?";
	signf_dgreek[e_AC] = "\216?";
	signf_dgreek[e_GR] = "\217?";
	signf_dgreek[e_SM] = "\212?";
	signf_dgreek[e_RO] = "\211?";
	signf_dgreek[E_SM_AC] = "\244E?";
	signf_dgreek[E_SM_GR] = "\242E?";
	signf_dgreek[E_RO_AC] = "\246E?";
	signf_dgreek[E_RO_GR] = "\301E?";
	signf_dgreek[E_SM] = "\260E?";
	signf_dgreek[E_RO] = "\273E?";
	signf_dgreek[hta] = "h?";
	signf_dgreek[HTA] = "H?";
	signf_dgreek[H_SM_CI] = "\252H?";
	signf_dgreek[H_SM_AC] = "\244H?";
	signf_dgreek[H_SM_GR] = "\242H?";
	signf_dgreek[H_RO_CI] = "\243H?";
	signf_dgreek[H_RO_AC] = "\246H?";
	signf_dgreek[H_RO_GR] = "\301H?";
	signf_dgreek[H_SM] = "\260H?";
	signf_dgreek[H_RO] = "\273H?";
	signf_dgreek[H_CI] = "\176H?";
	signf_dgreek[h_SM_AC] = "\251?";
	signf_dgreek[h_SM_GR] = "\261?";
	signf_dgreek[h_SM_CI] = "\312?";
	signf_dgreek[h_RO_AC] = "\250?";
	signf_dgreek[h_RO_GR] = "\237?";
	signf_dgreek[h_RO_CI] = "\351?";
	signf_dgreek[h_AC] = "\262?";
	signf_dgreek[h_GR] = "\236?";
	signf_dgreek[h_CI] = "\204?";
	signf_dgreek[h_SM] = "\263?";
	signf_dgreek[h_RO] = "\241?";
	signf_dgreek[h_SM_AC_IS] = "\251i?";
	signf_dgreek[h_SM_GR_IS] = "\261i?";
	signf_dgreek[h_SM_CI_IS] = "\312i?";
	signf_dgreek[h_RO_AC_IS] = "\250i?";
	signf_dgreek[h_RO_GR_IS] = "\237i?";
	signf_dgreek[h_RO_CI_IS] = "\351i?";
	signf_dgreek[h_AC_IS] = "\262i?";
	signf_dgreek[h_GR_IS] = "\236i?";
	signf_dgreek[h_CI_IS] = "\204i?";
	signf_dgreek[h_SM_IS] = "\263i?";
	signf_dgreek[h_RO_IS] = "\241i?";
	signf_dgreek[zeta] = "z?";
	signf_dgreek[ZETA] = "Z?";
	signf_dgreek[qeta] = "u?";
	signf_dgreek[QETA] = "U?";
	signf_dgreek[iota] = "i?";
	signf_dgreek[IOTA] = "I?";
	signf_dgreek[i_SM_AC] = "\267?";
	signf_dgreek[i_SM_GR] = "\240?";
	signf_dgreek[i_SM_CI] = "\235?";
	signf_dgreek[i_RO_AC] = "\231?";
	signf_dgreek[i_RO_GR] = "\265?";
	signf_dgreek[i_RO_CI] = "\336?";
	signf_dgreek[i_DI] = "\277?";
	signf_dgreek[i_AC_DI] = "\315?";
	signf_dgreek[i_GR_DI] = "\136?";
	signf_dgreek[i_AC] = "\222?";
	signf_dgreek[i_GR] = "\223?";
	signf_dgreek[i_CI] = "\330?";
	signf_dgreek[i_SM] = "\226?";
	signf_dgreek[i_RO] = "\224?";
	signf_dgreek[I_SM_CI] = "\252I?";
	signf_dgreek[I_SM_AC] = "\244I?";
	signf_dgreek[I_SM_GR] = "\242I?";
	signf_dgreek[I_RO_CI] = "\243I?";
	signf_dgreek[I_RO_AC] = "\246I?";
	signf_dgreek[I_RO_GR] = "\301I?";
	signf_dgreek[I_SM] = "\260I?";
	signf_dgreek[I_RO] = "\273I?";
	signf_dgreek[I_CI] = "\176I?";
	signf_dgreek[I_AC] = "\253I?";
	signf_dgreek[I_GR] = "\140I?";
	signf_dgreek[kappa] = "k?";
	signf_dgreek[KAPPA] = "K?";
	signf_dgreek[lambda] = "l?";
	signf_dgreek[LAMBDA] = "L?";
	signf_dgreek[mu] = "m?";
	signf_dgreek[MU] = "M?";
	signf_dgreek[nu] = "n?";
	signf_dgreek[NU] = "N?";
	signf_dgreek[ci] = "j?";
	signf_dgreek[CI] = "J?";
	signf_dgreek[omicron] = "o?";
	signf_dgreek[OMICRON] = "O?";
	signf_dgreek[o_SM_AC] = "\344?";
	signf_dgreek[o_SM_GR] = "\343?";
	signf_dgreek[o_RO_AC] = "\345?";
	signf_dgreek[o_RO_GR] = "\270?";
	signf_dgreek[o_AC] = "\227?";
	signf_dgreek[o_GR] = "\230?";
	signf_dgreek[o_SM] = "\234?";
	signf_dgreek[o_RO] = "\257?";
	signf_dgreek[O_SM_AC] = "\244O?";
	signf_dgreek[O_SM_GR] = "\242O?";
	signf_dgreek[O_RO_AC] = "\246O?";
	signf_dgreek[O_RO_GR] = "\301O?";
	signf_dgreek[O_AC] = "\253O?";
	signf_dgreek[O_GR] = "\140O?";
	signf_dgreek[O_SM] = "\260O?";
	signf_dgreek[O_RO] = "\273O?";
	signf_dgreek[pi] = "p?";
	signf_dgreek[PI] = "P?";
	signf_dgreek[RHO] = "R?";
	signf_dgreek[R_SM] = "\260R?";
	signf_dgreek[R_RO] = "\273R?";
	signf_dgreek[rho] = "r?";
	signf_dgreek[r_SM] = "\260r?";
	signf_dgreek[r_RO] = "\360r?";
	signf_dgreek[SIGMA] = "S?";
	signf_dgreek[sigma] = "s?";
	signf_dgreek[tau] = "t?";
	signf_dgreek[TAU] = "T?";
	signf_dgreek[UPSILON] = "Y?";
	signf_dgreek[U_SM_CI] = "\252Y?";
	signf_dgreek[U_SM_AC] = "\244Y?";
	signf_dgreek[U_SM_GR] = "\242Y?";
	signf_dgreek[U_RO_CI] = "\243Y?";
	signf_dgreek[U_RO_AC] = "\246Y?";
	signf_dgreek[U_RO_GR] = "\301Y?";
	signf_dgreek[U_SM] = "\260Y?";
	signf_dgreek[U_RO] = "\273Y?";
	signf_dgreek[U_CI] = "\176Y?";
	signf_dgreek[U_AC] = "\253Y?";
	signf_dgreek[U_GR] = "\140Y?";
	signf_dgreek[upsilon] = "y?";
	signf_dgreek[u_SM_AC] = "\302?";
	signf_dgreek[u_SM_GR] = "\307?";
	signf_dgreek[u_SM_CI] = "\342?";
	signf_dgreek[u_RO_AC] = "\300?";
	signf_dgreek[u_RO_GR] = "\335?";
	signf_dgreek[u_RO_CI] = "\341?";
	signf_dgreek[u_DI] = "\264?";
	signf_dgreek[u_AC_DI] = "\254?";
	signf_dgreek[u_GR_DI] = "\314?";
	signf_dgreek[u_AC] = "\256?";
	signf_dgreek[u_GR] = "\353?";
	signf_dgreek[u_CI] = "\276?";
	signf_dgreek[u_SM] = "\275?";
	signf_dgreek[u_RO] = "\274?";
	signf_dgreek[FI] = "F?";
	signf_dgreek[fi] = "f?";
	signf_dgreek[xi] = "x?";
	signf_dgreek[XI] = "X?";
	signf_dgreek[yi] = "c?";
	signf_dgreek[YI] = "C?";
	signf_dgreek[WMEGA] = "V?";
	signf_dgreek[wmega] = "v?";
	signf_dgreek[w_SM_AC] = "\364?";
	signf_dgreek[w_SM_GR] = "\363?";
	signf_dgreek[w_SM_CI] = "\362?";
	signf_dgreek[w_RO_AC] = "\366?";
	signf_dgreek[w_RO_GR] = "\365?";
	signf_dgreek[w_RO_CI] = "\361?";
	signf_dgreek[w_AC] = "\371?";
	signf_dgreek[w_GR] = "\370?";
	signf_dgreek[w_CI] = "\367?";
	signf_dgreek[w_SM] = "\311?";
	signf_dgreek[w_RO] = "\376?";
	signf_dgreek[W_SM_CI] = "\252V?";
	signf_dgreek[W_SM_AC] = "\244V?";
	signf_dgreek[W_SM_GR] = "\242V?";
	signf_dgreek[W_RO_CI] = "\243V?";
	signf_dgreek[W_RO_AC] = "\246V?";
	signf_dgreek[W_RO_GR] = "\301V?";
	signf_dgreek[W_SM] = "\260V?";
	signf_dgreek[W_RO] = "\273V?";
	signf_dgreek[W_CI] = "\176V?";
	signf_dgreek[W_AC] = "\253V?";
	signf_dgreek[W_GR] = "\140V?";
	signf_dgreek[w_IS] = "vi?";
	signf_dgreek[w_SM_AC_IS] = "\364i?";
	signf_dgreek[w_SM_GR_IS] = "\363i?";
	signf_dgreek[w_SM_CI_IS] = "\362i?";
	signf_dgreek[w_RO_AC_IS] = "\366i?";
	signf_dgreek[w_RO_GR_IS] = "\365i?";
	signf_dgreek[w_RO_CI_IS] = "\361i?";
	signf_dgreek[w_AC_IS] = "\371i?";
	signf_dgreek[w_GR_IS] = "\370i?";
	signf_dgreek[w_CI_IS] = "\367i?";
	signf_dgreek[w_SM_IS] = "\311i?";
	signf_dgreek[w_RO_IS] = "\376i?";
	signf_dgreek[tsigma] = "w?";
	signf_dgreek[ELLIPSIS] = ".?";
}

	char *signf_punct[] = {
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
		
char * signf_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double bracket */
		"|_",	/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * signf_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double bracket */
		"|_",	/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * signf_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"''",		/* 1 low double close quote */
		"''",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *signf_tgreek = "";
char *signf_tbgreek = "";
char *signf_troman = "";

char * signf_newline = "\r";

fix_signf_save(fname)
char * fname;
{
}

add_signf_header(f)
FILE * f;
{
}
