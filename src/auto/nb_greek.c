/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
*** The octal codes are on the right.
*** scroll through looking for comments - marked ***
*** By the way, i included the diaeresis combinations that you
*** mark as not having - you can get rid of them if you want.
*** signf_greek.c modified for nota bene 2.0 format
*** look at line 103 and 336, why are these numbers repeated??
*/
     
#include "filttab.h"

char * nb_greek[MAX_GK_CHARS];
char * nb_dgreek[MAX_GK_CHARS];

setup_nb_greek()
{
	nb_greek[alpha] = "a";
	nb_greek[a_SM_AC] = "\210";
	nb_greek[a_SM_GR] = "\215";
	nb_greek[a_SM_CI] = "\044";
	nb_greek[a_RO_AC] = "\211";
	nb_greek[a_RO_GR] = "\214";
	nb_greek[a_RO_CI] = "\023";
	nb_greek[a_AC] = "\336";
	nb_greek[a_GR] = "\350";
	nb_greek[a_CI] = "\362";
	nb_greek[a_SM] = "\266";
	nb_greek[a_RO] = "\322";
	nb_greek[a_SM_AC_IS] = "\207";
	nb_greek[a_SM_GR_IS] = "\216";
	nb_greek[a_SM_CI_IS] = "\273";
	nb_greek[a_RO_AC_IS] = "\212";
	nb_greek[a_RO_GR_IS] = "\213";
	nb_greek[a_RO_CI_IS] = "\171";
	nb_greek[a_AC_IS] = "\337";
	nb_greek[a_GR_IS] = "\351";
	nb_greek[a_CI_IS] = "\363";
	nb_greek[a_SM_IS] = "\267";
	nb_greek[a_RO_IS] = "\323";
	nb_greek[a_IS] = "261";
	nb_greek[ALPHA] = "A";
	nb_greek[A_SM_CI] = "\035A";
	nb_greek[A_SM_AC] = "\017A";
	nb_greek[A_SM_GR] = "\022A";
	nb_greek[A_RO_CI] = "\001A";
	nb_greek[A_RO_AC] = "\027A";
	nb_greek[A_RO_GR] = "\034A";
	nb_greek[A_SM] = "\013A";
	nb_greek[A_RO] = "\016A";
	nb_greek[A_CI] = "\006A";
	nb_greek[beta] = "b";
	nb_greek[BETA] = "B";
	nb_greek[GAMMA] = "G";
	nb_greek[gamma] = "g";
	nb_greek[delta] = "d";
	nb_greek[DELTA] = "D";
	nb_greek[epsilon] = "e";
	nb_greek[EPSILON] = "E";
	nb_greek[e_SM_AC] = "\364";
	nb_greek[e_SM_GR] = "\217";
	nb_greek[e_RO_AC] = "\221";
	nb_greek[e_RO_GR] = "\220";
	nb_greek[e_AC] = "\340";
	nb_greek[e_GR] = "\352";
	nb_greek[e_SM] = "\266";
	nb_greek[e_RO] = "\324";
	nb_greek[E_SM_AC] = "\017E";
	nb_greek[E_SM_GR] = "\022E";
	nb_greek[E_RO_AC] = "\027E";
	nb_greek[E_RO_GR] = "\034E";
	nb_greek[E_SM] = "\013E";
	nb_greek[E_RO] = "\016E";
	nb_greek[hta] = "h";
	nb_greek[HTA] = "H";
	nb_greek[H_SM_CI] = "\035H";
	nb_greek[H_SM_AC] = "\017H";
	nb_greek[H_SM_GR] = "\022H";
	nb_greek[H_RO_CI] = "\001H";
	nb_greek[H_RO_AC] = "\027H";
	nb_greek[H_RO_GR] = "\034H";
	nb_greek[H_SM] = "\013H";
	nb_greek[H_RO] = "\016H";
	nb_greek[H_CI] = "\006H";
	nb_greek[h_SM_AC] = "\222";
	nb_greek[h_SM_GR] = "\223";
	nb_greek[h_SM_CI] = "\316";
	nb_greek[h_RO_AC] = "\226";
	nb_greek[h_RO_GR] = "\231";
	nb_greek[h_RO_CI] = "\274";
	nb_greek[h_AC] = "\341";
	nb_greek[h_GR] = "\354";
	nb_greek[h_CI] = "\365";
	nb_greek[h_SM] = "\275";
	nb_greek[h_RO] = "\325";
	nb_greek[h_SM_AC_IS] = "\224";
	nb_greek[h_SM_GR_IS] = "\225";
	nb_greek[h_SM_CI_IS] = "\272";
	nb_greek[h_RO_AC_IS] = "\227";
	nb_greek[h_RO_GR_IS] = "\230";
	nb_greek[h_RO_CI_IS] = "\271";
	nb_greek[h_AC_IS] = "\342";
	nb_greek[h_GR_IS] = "\354";
	nb_greek[h_CI_IS] = "\366";
	nb_greek[h_SM_IS] = "\272";
	nb_greek[h_RO_IS] = "\271";
	nb_greek[zeta] = "z";
	nb_greek[ZETA] = "Z";
	nb_greek[qeta] = "u";
	nb_greek[QETA] = "U";
	nb_greek[iota] = "i";
	nb_greek[IOTA] = "I";
	nb_greek[i_SM_AC] = "\234";
	nb_greek[i_SM_GR] = "\235";
	nb_greek[i_SM_CI] = "\315";
	nb_greek[i_RO_AC] = "\232";
	nb_greek[i_RO_GR] = "\233";
	nb_greek[i_RO_CI] = "\314";
	nb_greek[i_DI] = "\204";
	nb_greek[i_AC_DI] = "\205";
	nb_greek[i_GR_DI] = "\030";
	nb_greek[i_AC] = "\343";
	nb_greek[i_GR] = "\355";
	nb_greek[i_CI] = "\367";
	nb_greek[i_SM] = "\306";
	nb_greek[i_RO] = "\327";
	nb_greek[I_SM_CI] = "\035I";
	nb_greek[I_SM_AC] = "\017I";
	nb_greek[I_SM_GR] = "\022I";
	nb_greek[I_RO_CI] = "\001I";
	nb_greek[I_RO_AC] = "\027I";
	nb_greek[I_RO_GR] = "\034I";
	nb_greek[I_SM] = "\013I";
	nb_greek[I_RO] = "\016I";
	nb_greek[I_CI] = "\006I";
	nb_greek[I_AC] = "\002I";
	nb_greek[I_GR] = "\005I";
	nb_greek[kappa] = "k";
	nb_greek[KAPPA] = "K";
	nb_greek[lambda] = "l";
	nb_greek[LAMBDA] = "L";
	nb_greek[mu] = "m";
	nb_greek[MU] = "M";
	nb_greek[nu] = "n";
	nb_greek[NU] = "N";
	nb_greek[ci] = "q";
	nb_greek[CI] = "Q";
	nb_greek[omicron] = "o";
	nb_greek[OMICRON] = "O";
	nb_greek[o_SM_AC] = "\370";
	nb_greek[o_SM_GR] = "\240";
	nb_greek[o_RO_AC] = "\237";
	nb_greek[o_RO_GR] = "\241";
	nb_greek[o_AC] = "\334";
	nb_greek[o_GR] = "\356";
	nb_greek[o_SM] = "\307";
	nb_greek[o_RO] = "\330";
	nb_greek[O_SM_AC] = "\017O";
	nb_greek[O_SM_GR] = "\022O";
	nb_greek[O_RO_AC] = "\027O";
	nb_greek[O_RO_GR] = "\034O";
	nb_greek[O_AC] = "\002O";
	nb_greek[O_GR] = "\005O";
	nb_greek[O_SM] = "\013O";
	nb_greek[O_RO] = "\016O";
	nb_greek[pi] = "p";
	nb_greek[PI] = "P";
	nb_greek[RHO] = "R";
	nb_greek[R_SM] = "\013R";
	nb_greek[R_RO] = "\016R";
	nb_greek[rho] = "r";
	nb_greek[r_SM] = "\201";
	nb_greek[r_RO] = "\200";
	nb_greek[SIGMA] = "S";
	nb_greek[sigma] = "s";
	nb_greek[tau] = "t";
	nb_greek[TAU] = "T";
	nb_greek[UPSILON] = "Y";
	nb_greek[U_SM_CI] = "\035Y";
	nb_greek[U_SM_AC] = "\017Y";
	nb_greek[U_SM_GR] = "\022Y";
	nb_greek[U_RO_CI] = "\001Y";
	nb_greek[U_RO_AC] = "\027Y";
	nb_greek[U_RO_GR] = "\034Y";
	nb_greek[U_SM] = "\013Y";
	nb_greek[U_RO] = "\016Y";
	nb_greek[U_CI] = "\006Y";
	nb_greek[U_AC] = "\002Y";
	nb_greek[U_GR] = "\005Y";
	nb_greek[upsilon] = "y";
	nb_greek[u_SM_AC] = "\242";
	nb_greek[u_SM_GR] = "\004";
	nb_greek[u_SM_CI] = "\312";
	nb_greek[u_RO_AC] = "\245";
	nb_greek[u_RO_GR] = "\244";
	nb_greek[u_RO_CI] = "\313";
	nb_greek[u_DI] = "\202";
	nb_greek[u_AC_DI] = "\203";
	nb_greek[u_GR_DI] = "\020";
	nb_greek[u_AC] = "\345";
	nb_greek[u_GR] = "\357";
	nb_greek[u_CI] = "\371";
	nb_greek[u_SM] = "\317";
	nb_greek[u_RO] = "\333";
	nb_greek[FI] = "F";
	nb_greek[fi] = "f";
	nb_greek[xi] = "x";
	nb_greek[XI] = "X";
	nb_greek[yi] = "c";
	nb_greek[YI] = "C";
	nb_greek[WMEGA] = "V";
	nb_greek[wmega] = "v";
	nb_greek[w_SM_AC] = "\037";
	nb_greek[w_SM_GR] = "\014";
	nb_greek[w_SM_CI] = "\260";
	nb_greek[w_RO_AC] = "\246";
	nb_greek[w_RO_GR] = "\021";
	nb_greek[w_RO_CI] = "\310";
	nb_greek[w_AC] = "\346";
	nb_greek[w_GR] = "\360";
	nb_greek[w_CI] = "\206";
	nb_greek[w_SM] = "\320";
	nb_greek[w_RO] = "\334";
	nb_greek[W_SM_CI] = "\035V";
	nb_greek[W_SM_AC] = "\017V";
	nb_greek[W_SM_GR] = "\022V";
	nb_greek[W_RO_CI] = "\001V";
	nb_greek[W_RO_AC] = "\027V";
	nb_greek[W_RO_GR] = "\034V";
	nb_greek[W_SM] = "\013V";
	nb_greek[W_RO] = "\016V";
	nb_greek[W_CI] = "\006V";
	nb_greek[W_AC] = "\002V";
	nb_greek[W_GR] = "\005V";
	nb_greek[w_IS] = "265";
	nb_greek[w_SM_AC_IS] = "\243";
	nb_greek[w_SM_GR_IS] = "\026";
	nb_greek[w_SM_CI_IS] = "\374";
	nb_greek[w_RO_AC_IS] = "\247";
	nb_greek[w_RO_GR_IS] = "\236";
	nb_greek[w_RO_CI_IS] = "\311";
	nb_greek[w_AC_IS] = "\347";
	nb_greek[w_GR_IS] = "\361";
	nb_greek[w_CI_IS] = "\373";
	nb_greek[w_SM_IS] = "\321";
	nb_greek[w_RO_IS] = "\335";
	nb_greek[tsigma] = "163";
	nb_greek[ELLIPSIS] = ".";

	nb_dgreek[alpha] = "a?";
	nb_dgreek[a_SM_AC] = "\210?";
	nb_dgreek[a_SM_GR] = "\215?";
	nb_dgreek[a_SM_CI] = "\044?";
	nb_dgreek[a_RO_AC] = "\211?";
	nb_dgreek[a_RO_GR] = "\214?";
	nb_dgreek[a_RO_CI] = "\023?";
	nb_dgreek[a_AC] = "\336?";
	nb_dgreek[a_GR] = "\350?";
	nb_dgreek[a_CI] = "\362?";
	nb_dgreek[a_SM] = "\266?";
	nb_dgreek[a_RO] = "\322?";
	nb_dgreek[a_SM_AC_IS] = "\207?";
	nb_dgreek[a_SM_GR_IS] = "\216?";
	nb_dgreek[a_SM_CI_IS] = "\273?";
	nb_dgreek[a_RO_AC_IS] = "\212?";
	nb_dgreek[a_RO_GR_IS] = "\213?";
	nb_dgreek[a_RO_CI_IS] = "\171?";
	nb_dgreek[a_AC_IS] = "\337?";
	nb_dgreek[a_GR_IS] = "\351?";
	nb_dgreek[a_CI_IS] = "\363?";
	nb_dgreek[a_SM_IS] = "\267?";
	nb_dgreek[a_RO_IS] = "\323?";
	nb_dgreek[a_IS] = "261?";
	nb_dgreek[ALPHA] = "A?";
	nb_dgreek[A_SM_CI] = "\035A?";
	nb_dgreek[A_SM_AC] = "\017A?";
	nb_dgreek[A_SM_GR] = "\022A?";
	nb_dgreek[A_RO_CI] = "\001A?";
	nb_dgreek[A_RO_AC] = "\027A?";
	nb_dgreek[A_RO_GR] = "\034A?";
	nb_dgreek[A_SM] = "\013A?";
	nb_dgreek[A_RO] = "\016A?";
	nb_dgreek[A_CI] = "\006A?";
	nb_dgreek[beta] = "b?";
	nb_dgreek[BETA] = "B?";
	nb_dgreek[GAMMA] = "G?";
	nb_dgreek[gamma] = "g?";
	nb_dgreek[delta] = "d?";
	nb_dgreek[DELTA] = "D?";
	nb_dgreek[epsilon] = "e?";
	nb_dgreek[EPSILON] = "E?";
	nb_dgreek[e_SM_AC] = "\364?";
	nb_dgreek[e_SM_GR] = "\217?";
	nb_dgreek[e_RO_AC] = "\221?";
	nb_dgreek[e_RO_GR] = "\220?";
	nb_dgreek[e_AC] = "\340?";
	nb_dgreek[e_GR] = "\352?";
	nb_dgreek[e_SM] = "\266?";
	nb_dgreek[e_RO] = "\324?";
	nb_dgreek[E_SM_AC] = "\017E?";
	nb_dgreek[E_SM_GR] = "\022E?";
	nb_dgreek[E_RO_AC] = "\027E?";
	nb_dgreek[E_RO_GR] = "\034E?";
	nb_dgreek[E_SM] = "\013E?";
	nb_dgreek[E_RO] = "\016E?";
	nb_dgreek[hta] = "h?";
	nb_dgreek[HTA] = "H?";
	nb_dgreek[H_SM_CI] = "\035H?";
	nb_dgreek[H_SM_AC] = "\017H?";
	nb_dgreek[H_SM_GR] = "\022H?";
	nb_dgreek[H_RO_CI] = "\001H?";
	nb_dgreek[H_RO_AC] = "\027H?";
	nb_dgreek[H_RO_GR] = "\034H?";
	nb_dgreek[H_SM] = "\013H?";
	nb_dgreek[H_RO] = "\016H?";
	nb_dgreek[H_CI] = "\006H?";
	nb_dgreek[h_SM_AC] = "\222?";
	nb_dgreek[h_SM_GR] = "\223?";
	nb_dgreek[h_SM_CI] = "\316?";
	nb_dgreek[h_RO_AC] = "\226?";
	nb_dgreek[h_RO_GR] = "\231?";
	nb_dgreek[h_RO_CI] = "\274?";
	nb_dgreek[h_AC] = "\341?";
	nb_dgreek[h_GR] = "\354?";
	nb_dgreek[h_CI] = "\365?";
	nb_dgreek[h_SM] = "\275?";
	nb_dgreek[h_RO] = "\325?";
	nb_dgreek[h_SM_AC_IS] = "\224?";
	nb_dgreek[h_SM_GR_IS] = "\225?";
	nb_dgreek[h_SM_CI_IS] = "\272?";
	nb_dgreek[h_RO_AC_IS] = "\227?";
	nb_dgreek[h_RO_GR_IS] = "\230?";
	nb_dgreek[h_RO_CI_IS] = "\271?";
	nb_dgreek[h_AC_IS] = "\342?";
	nb_dgreek[h_GR_IS] = "\354?";
	nb_dgreek[h_CI_IS] = "\366?";
	nb_dgreek[h_SM_IS] = "\272?";
	nb_dgreek[h_RO_IS] = "\271?";
	nb_dgreek[zeta] = "z?";
	nb_dgreek[ZETA] = "Z?";
	nb_dgreek[qeta] = "u?";
	nb_dgreek[QETA] = "U?";
	nb_dgreek[iota] = "i?";
	nb_dgreek[IOTA] = "I?";
	nb_dgreek[i_SM_AC] = "\234?";
	nb_dgreek[i_SM_GR] = "\235?";
	nb_dgreek[i_SM_CI] = "\315?";
	nb_dgreek[i_RO_AC] = "\232?";
	nb_dgreek[i_RO_GR] = "\233?";
	nb_dgreek[i_RO_CI] = "\314?";
	nb_dgreek[i_DI] = "\204?";
	nb_dgreek[i_AC_DI] = "\205?";
	nb_dgreek[i_GR_DI] = "\030?";
	nb_dgreek[i_AC] = "\343?";
	nb_dgreek[i_GR] = "\355?";
	nb_dgreek[i_CI] = "\367?";
	nb_dgreek[i_SM] = "\306?";
	nb_dgreek[i_RO] = "\327?";
	nb_dgreek[I_SM_CI] = "\035I?";
	nb_dgreek[I_SM_AC] = "\017I?";
	nb_dgreek[I_SM_GR] = "\022I?";
	nb_dgreek[I_RO_CI] = "\001I?";
	nb_dgreek[I_RO_AC] = "\027I?";
	nb_dgreek[I_RO_GR] = "\034I?";
	nb_dgreek[I_SM] = "\013I?";
	nb_dgreek[I_RO] = "\016I?";
	nb_dgreek[I_CI] = "\006I?";
	nb_dgreek[I_AC] = "\002I?";
	nb_dgreek[I_GR] = "\005I?";
	nb_dgreek[kappa] = "k?";
	nb_dgreek[KAPPA] = "K?";
	nb_dgreek[lambda] = "l?";
	nb_dgreek[LAMBDA] = "L?";
	nb_dgreek[mu] = "m?";
	nb_dgreek[MU] = "M?";
	nb_dgreek[nu] = "n?";
	nb_dgreek[NU] = "N?";
	nb_dgreek[ci] = "q?";
	nb_dgreek[CI] = "Q?";
	nb_dgreek[omicron] = "o?";
	nb_dgreek[OMICRON] = "O?";
	nb_dgreek[o_SM_AC] = "\370?";
	nb_dgreek[o_SM_GR] = "\240?";
	nb_dgreek[o_RO_AC] = "\237?";
	nb_dgreek[o_RO_GR] = "\241?";
	nb_dgreek[o_AC] = "\334?";
	nb_dgreek[o_GR] = "\356?";
	nb_dgreek[o_SM] = "\307?";
	nb_dgreek[o_RO] = "\330?";
	nb_dgreek[O_SM_AC] = "\017O?";
	nb_dgreek[O_SM_GR] = "\022O?";
	nb_dgreek[O_RO_AC] = "\027O?";
	nb_dgreek[O_RO_GR] = "\034O?";
	nb_dgreek[O_AC] = "\002O?";
	nb_dgreek[O_GR] = "\005O?";
	nb_dgreek[O_SM] = "\013O?";
	nb_dgreek[O_RO] = "\016O?";
	nb_dgreek[pi] = "p?";
	nb_dgreek[PI] = "P?";
	nb_dgreek[RHO] = "R?";
	nb_dgreek[R_SM] = "\013R?";
	nb_dgreek[R_RO] = "\016R?";
	nb_dgreek[rho] = "r?";
	nb_dgreek[r_SM] = "\201?";
	nb_dgreek[r_RO] = "\200?";
	nb_dgreek[SIGMA] = "S?";
	nb_dgreek[sigma] = "s?";
	nb_dgreek[tau] = "t?";
	nb_dgreek[TAU] = "T?";
	nb_dgreek[UPSILON] = "Y?";
	nb_dgreek[U_SM_CI] = "\035Y?";
	nb_dgreek[U_SM_AC] = "\017Y?";
	nb_dgreek[U_SM_GR] = "\022Y?";
	nb_dgreek[U_RO_CI] = "\001Y?";
	nb_dgreek[U_RO_AC] = "\027Y?";
	nb_dgreek[U_RO_GR] = "\034Y?";
	nb_dgreek[U_SM] = "\013Y?";
	nb_dgreek[U_RO] = "\016Y?";
	nb_dgreek[U_CI] = "\006Y?";
	nb_dgreek[U_AC] = "\002Y?";
	nb_dgreek[U_GR] = "\005Y?";
	nb_dgreek[upsilon] = "y?";
	nb_dgreek[u_SM_AC] = "\242?";
	nb_dgreek[u_SM_GR] = "\004?";
	nb_dgreek[u_SM_CI] = "\312?";
	nb_dgreek[u_RO_AC] = "\245?";
	nb_dgreek[u_RO_GR] = "\244?";
	nb_dgreek[u_RO_CI] = "\313?";
	nb_dgreek[u_DI] = "\202?";
	nb_dgreek[u_AC_DI] = "\203?";
	nb_dgreek[u_GR_DI] = "\020?";
	nb_dgreek[u_AC] = "\345?";
	nb_dgreek[u_GR] = "\357?";
	nb_dgreek[u_CI] = "\371?";
	nb_dgreek[u_SM] = "\317?";
	nb_dgreek[u_RO] = "\333?";
	nb_dgreek[FI] = "F?";
	nb_dgreek[fi] = "f?";
	nb_dgreek[xi] = "x?";
	nb_dgreek[XI] = "X?";
	nb_dgreek[yi] = "c?";
	nb_dgreek[YI] = "C?";
	nb_dgreek[WMEGA] = "V?";
	nb_dgreek[wmega] = "v?";
	nb_dgreek[w_SM_AC] = "\037?";
	nb_dgreek[w_SM_GR] = "\014?";
	nb_dgreek[w_SM_CI] = "\260?";
	nb_dgreek[w_RO_AC] = "\246?";
	nb_dgreek[w_RO_GR] = "\021?";
	nb_dgreek[w_RO_CI] = "\310?";
	nb_dgreek[w_AC] = "\346?";
	nb_dgreek[w_GR] = "\360?";
	nb_dgreek[w_CI] = "\206?";
	nb_dgreek[w_SM] = "\320?";
	nb_dgreek[w_RO] = "\334?";
	nb_dgreek[W_SM_CI] = "\035V?";
	nb_dgreek[W_SM_AC] = "\017V?";
	nb_dgreek[W_SM_GR] = "\022V?";
	nb_dgreek[W_RO_CI] = "\001V?";
	nb_dgreek[W_RO_AC] = "\027V?";
	nb_dgreek[W_RO_GR] = "\034V?";
	nb_dgreek[W_SM] = "\013V?";
	nb_dgreek[W_RO] = "\016V?";
	nb_dgreek[W_CI] = "\006V?";
	nb_dgreek[W_AC] = "\002V?";
	nb_dgreek[W_GR] = "\005V?";
	nb_dgreek[w_IS] = "265?";
	nb_dgreek[w_SM_AC_IS] = "\243?";
	nb_dgreek[w_SM_GR_IS] = "\026?";
	nb_dgreek[w_SM_CI_IS] = "\374?";
	nb_dgreek[w_RO_AC_IS] = "\247?";
	nb_dgreek[w_RO_GR_IS] = "\236?";
	nb_dgreek[w_RO_CI_IS] = "\311?";
	nb_dgreek[w_AC_IS] = "\347?";
	nb_dgreek[w_GR_IS] = "\361?";
	nb_dgreek[w_CI_IS] = "\373?";
	nb_dgreek[w_SM_IS] = "\321?";
	nb_dgreek[w_RO_IS] = "\335?";
	nb_dgreek[tsigma] = "163?";
	nb_dgreek[ELLIPSIS] = ".?";
}

	char *nb_punct[] = {
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
		
char * nb_lbrackets[] = {
		"[",	/* left square bracket */
		"(",	/* left parenthesis */
		"<",	/* left angle bracket */
		"{",	/* left curly bracket */
		"[[",	/* left double bracket */
		"|_",	/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * nb_rbrackets[] = {
		"]",	/* right square bracket */
		")",	/* right parenthesis */
		">",	/* right angle bracket */
		"}",	/* right curly bracket */
		"]]",	/* right double bracket */
		"|_",	/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * nb_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"''",		/* 1 low double close quote */
		"''",		/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"'",		/* 5 */
		"\"",		/* 6 */
};

char *nb_tgreek = "";
char *nb_tbgreek = "";
char *nb_troman = "";

char * nb_newline = "\n";

fix_nb_save(fname)
char * fname;
{
	char tmp[256];

	sprintf(tmp,"nota_bene %s\n", fname );
	system( tmp );
}

add_nb_header(f)
FILE * f;
{
}
