/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "filttab.h"

char * macint_greek[MAX_GK_CHARS];
char * macint_dgreek[MAX_GK_CHARS];

setup_macint_greek()
{

	macint_greek[alpha] = "AE";
	macint_greek[a_AC] = "1AE";
	macint_greek[a_GR] = "2AE";
	macint_greek[a_CI] = ">>1AE";
	macint_greek[a_SM] = "AE";
	macint_greek[a_SM_AC] = "1AE";
	macint_greek[a_SM_GR] = "2AE";
	macint_greek[a_SM_CI] = ">>1AE";
	macint_greek[a_RO] = "hAE";
	macint_greek[a_RO_AC] = "h1AE";
	macint_greek[a_RO_GR] = "h2AE";
	macint_greek[a_RO_CI] = "h>>1AE";

	macint_greek[ALPHA] = "AE";
	macint_greek[A_CI] = ">>1AE";
	macint_greek[A_SM] = "AE";
	macint_greek[A_SM_AC] = "1AE";
	macint_greek[A_SM_GR] = "2AE";
	macint_greek[A_SM_CI] = ">>1AE";
	macint_greek[A_RO] = "hAE";
	macint_greek[A_RO_AC] = "h1AE";
	macint_greek[A_RO_GR] = "h2AE";
	macint_greek[A_RO_CI] = "h>>1AE";

	macint_greek[a_IS] = "AEIH";
	macint_greek[a_AC_IS] = "1AEIH";
	macint_greek[a_GR_IS] = "2AEIH";
	macint_greek[a_CI_IS] = ">>1AEIH";
	macint_greek[a_SM_IS] = "AEIH";
	macint_greek[a_SM_AC_IS] = "1AEIH";
	macint_greek[a_SM_GR_IS] = "2AEIH";
	macint_greek[a_SM_CI_IS] = ">>1AEIH";
	macint_greek[a_RO_IS] = "hAEIH";
	macint_greek[a_RO_AC_IS] = "h1AEIH";
	macint_greek[a_RO_GR_IS] = "h2AEIH";
	macint_greek[a_RO_CI_IS] = "h>>1AEIH";

	macint_greek[BETA] = "b";
	macint_greek[beta] = "b";
	macint_greek[GAMMA] = "g";
	macint_greek[gamma] = "g";
	macint_greek[DELTA] = "d";
	macint_greek[delta] = "d";
	
	macint_greek[alpha] = "AE";
	macint_greek[a_AC] = "1AE";
	macint_greek[a_GR] = "2AE";
	macint_greek[a_CI] = ">>1AE";
	macint_greek[a_SM] = "AE";
	macint_greek[a_SM_AC] = "1AE";
	macint_greek[a_SM_GR] = "2AE";
	macint_greek[a_SM_CI] = ">>1AE";
	macint_greek[a_RO] = "hAE";
	macint_greek[a_RO_AC] = "h1AE";
	macint_greek[a_RO_GR] = "h2AE";
	macint_greek[a_RO_CI] = "h>>1AE";

	macint_greek[epsilon] = "EH";
	macint_greek[e_SM] = "1EH";
	macint_greek[e_AC] = "1EH";
	macint_greek[e_GR] = "2EH";
	macint_greek[e_SM_AC] = "1EH";
	macint_greek[e_SM_GR] = "2EH";
	macint_greek[e_RO] = "hEH";
	macint_greek[e_RO_AC] = "h1EH";
	macint_greek[e_RO_GR] = "h2EH";

	macint_greek[EPSILON] = "EH";
	macint_greek[E_SM] = "EH";
	macint_greek[E_SM_AC] = "1EH";
	macint_greek[E_SM_GR] = "2EH";
	macint_greek[E_RO] = "hEH";
	macint_greek[E_RO_AC] = "h1EH";
	macint_greek[E_RO_GR] = "h2EH";

	macint_greek[ZETA] = "z";
	macint_greek[zeta] = "z";

	macint_greek[hta] = "AY";
	macint_greek[h_AC] = "1AY";
	macint_greek[h_GR] = "2AY";
	macint_greek[h_CI] = ">>1AY";
	macint_greek[h_SM] = "AY";
	macint_greek[h_SM_AC] = "1AY";
	macint_greek[h_SM_GR] = "2AY";
	macint_greek[h_SM_CI] = ">>1AY";
	macint_greek[h_RO] = "hAY";
	macint_greek[h_RO_AC] = "h1AY";
	macint_greek[h_RO_GR] = "h2AY";
	macint_greek[h_RO_CI] = "h>>1AY";

	macint_greek[HTA] = "AY";
	macint_greek[H_AC] = "1AY";
	macint_greek[H_GR] = "2AY";
	macint_greek[H_CI] = ">>1AY";
	macint_greek[H_SM] = "AY";
	macint_greek[H_SM_AC] = "1AY";
	macint_greek[H_SM_GR] = "2AY";
	macint_greek[H_SM_CI] = ">>1AY";
	macint_greek[H_RO] = "hAY";
	macint_greek[H_RO_AC] = "h1AY";
	macint_greek[H_RO_GR] = "h2AY";
	macint_greek[H_RO_CI] = "h>>1AY";

	macint_greek[h_IS] = "AYIH";
	macint_greek[h_AC_IS] = "1AYIH";
	macint_greek[h_GR_IS] = "2AYIH";
	macint_greek[h_CI_IS] = ">>1AYIH";
	macint_greek[h_SM_IS] = "AYIH";
	macint_greek[h_SM_AC_IS] = "1AYIH";
	macint_greek[h_SM_GR_IS] = "2AYIH";
	macint_greek[h_SM_CI_IS] = ">>1AYIH";
	macint_greek[h_RO_IS] = "hAYIH";
	macint_greek[h_RO_AC_IS] = "h1AYIH";
	macint_greek[h_RO_GR_IS] = "h2AYIH";
	macint_greek[h_RO_CI_IS] = "h>>1AYIH";

	macint_greek[QETA] = "T";
	macint_greek[qeta] = "T";

	macint_greek[iota] = "IH";
	macint_greek[i_AC] = "1IH";
	macint_greek[i_GR] = "2IH";
	macint_greek[i_CI] = ">>1IH";
	macint_greek[i_SM] = "IH";
	macint_greek[i_SM_AC] = "1IH";
	macint_greek[i_SM_GR] = "2IH";
	macint_greek[i_SM_CI] = ">>1IH";
	macint_greek[i_RO] = "hIH";
	macint_greek[i_RO_AC] = "h1IH";
	macint_greek[i_RO_GR] = "h2IH";
	macint_greek[i_RO_CI] = "h>>1IH";

	macint_greek[IOTA] = "IH";
	macint_greek[I_AC] = "1IH";
	macint_greek[I_GR] = "2IH";
	macint_greek[I_CI] = ">>1IH";
	macint_greek[I_SM] = "IH";
	macint_greek[I_SM_AC] = "1IH";
	macint_greek[I_SM_GR] = "2IH";
	macint_greek[I_SM_CI] = ">>1IH";
	macint_greek[I_RO] = "hIH";
	macint_greek[I_RO_AC] = "h1IH";
	macint_greek[I_RO_GR] = "h2IH";
	macint_greek[I_RO_CI] = "h>>1IH";

	macint_greek[i_DI] = "%IH";
	macint_greek[i_AC_DI] = "%1IH";
	macint_greek[i_GR_DI] = "%2IH";

	macint_greek[KAPPA] = "k";
	macint_greek[kappa] = "k";
	macint_greek[LAMBDA] = "l";
	macint_greek[lambda] = "l";
	macint_greek[MU] = "m";
	macint_greek[mu] = "m";
	macint_greek[NU] = "n";
	macint_greek[nu] = "n";
	macint_greek[CI] = "ks";
	macint_greek[ci] = "ks";

	macint_greek[omicron] = "AO";
	macint_greek[o_AC] = "1AO";
	macint_greek[o_GR] = "2AO";
	macint_greek[o_SM] = "AO";
	macint_greek[o_SM_AC] = "1AO";
	macint_greek[o_SM_GR] = "2AO";
	macint_greek[o_RO] = "hAO";
	macint_greek[o_RO_AC] = "h1AO";
	macint_greek[o_RO_GR] = "h2AO";

	macint_greek[OMICRON] = "AO";
	macint_greek[O_AC] = "1AO";
	macint_greek[O_GR] = "2AO";
	macint_greek[O_SM] = "AO";
	macint_greek[O_SM_AC] = "1AO";
	macint_greek[O_SM_GR] = "2AO";
	macint_greek[O_RO] = "hAO";
	macint_greek[O_RO_AC] = "h1AO";
	macint_greek[O_RO_GR] = "h2AO";

	macint_greek[PI] = "p";
	macint_greek[pi] = "p";
	macint_greek[RHO] = "hr";
	macint_greek[R_SM] = "r";
	macint_greek[R_RO] = "hr";
	macint_greek[rho] = "hr";
	macint_greek[r_SM] = "r";
	macint_greek[r_RO] = "hr";

	macint_greek[sigma] = "s";
	macint_greek[SIGMA] = "s";
	macint_greek[TAU] = "t";
	macint_greek[tau] = "t";

	macint_greek[upsilon] = "UX";
	macint_greek[u_AC] = "1UX";
	macint_greek[u_GR] = "2UX";
	macint_greek[u_CI] = ">>1UX";
	macint_greek[u_SM] = "UX";
	macint_greek[u_SM_AC] = "1UX";
	macint_greek[u_SM_GR] = "2UX";
	macint_greek[u_SM_CI] = ">>1UW";
	macint_greek[u_RO] = "hUX";
	macint_greek[u_RO_AC] = "h1UX";
	macint_greek[u_RO_GR] = "h2UX";
	macint_greek[u_RO_CI] = "h>>1UW";

	macint_greek[UPSILON] = "UX";
	macint_greek[U_AC] = "1UX";
	macint_greek[U_GR] = "2UX";
	macint_greek[U_CI] = ">>1UX";
	macint_greek[U_SM] = "UX";
	macint_greek[U_SM_AC] = "1UX";
	macint_greek[U_SM_GR] = "2UX";
	macint_greek[U_SM_CI] = ">>1UW";
	macint_greek[U_RO] = "hUX";
	macint_greek[U_RO_AC] = "h1UX";
	macint_greek[U_RO_GR] = "h2UX";
	macint_greek[U_RO_CI] = "h>>1UW";

	macint_greek[u_DI] = "%UX";
	macint_greek[u_AC_DI] = "%1UX";
	macint_greek[u_GR_DI] = "%2UX";

	macint_greek[FI] = "f";
	macint_greek[fi] = "f";
	macint_greek[XI] = "C";
	macint_greek[xi] = "C";
	macint_greek[YI] = "ps";
	macint_greek[yi] = "ps";

	macint_greek[wmega] = "OW";
	macint_greek[w_AC] = "1OW";
	macint_greek[w_GR] = "2OW";
	macint_greek[w_CI] = ">>1OW";
	macint_greek[w_SM] = "OW";
	macint_greek[w_SM_AC] = "1OW";
	macint_greek[w_SM_GR] = "2OW";
	macint_greek[w_SM_CI] = ">>1UW";
	macint_greek[w_RO] = "hOW";
	macint_greek[w_RO_AC] = "h1OW";
	macint_greek[w_RO_GR] = "h2OW";
	macint_greek[w_RO_CI] = "h>>1UW";

	macint_greek[WMEGA] = "OW";
	macint_greek[W_AC] = "1OW";
	macint_greek[W_GR] = "2OW";
	macint_greek[W_CI] = ">>1OW";
	macint_greek[W_SM] = "OW";
	macint_greek[W_SM_AC] = "1OW";
	macint_greek[W_SM_GR] = "2OW";
	macint_greek[W_SM_CI] = ">>1UW";
	macint_greek[W_RO] = "hOW";
	macint_greek[W_RO_AC] = "h1OW";
	macint_greek[W_RO_GR] = "h2OW";
	macint_greek[W_RO_CI] = "h>>1UW";


	macint_greek[w_IS] = "OWIH";
	macint_greek[w_AC_IS] = "1OWIH";
	macint_greek[w_GR_IS] = "2OWIH";
	macint_greek[w_CI_IS] = ">>1OWIH";
	macint_greek[w_SM_IS] = "OWIH";
	macint_greek[w_SM_AC_IS] = "1OWIH";
	macint_greek[w_SM_GR_IS] = "2OWIH";
	macint_greek[w_SM_CI_IS] = ">>1OWIH";
	macint_greek[w_RO_IS] = "hOWIH";
	macint_greek[w_RO_AC_IS] = "h1OWIH";
	macint_greek[w_RO_GR_IS] = "h2OWIH";
	macint_greek[w_RO_CI_IS] = "h>>1OWIH";


}

	char *macint_punct[] = {
		"",	/* 0 dagger */
		"%%",		/* 1 */
		"",		/* 2 */
		"",		/* 3 */
		"",		/* 4 */
		"",		/* 5 */
		"",		/* 6 */
		"",		/* 7 */
		"",		/* 8 '%' */
		"",		/* 9 */
		"",		/* 10 */
		"",		/* 11 (should be) oversized period */
		"",		/* 12 variant '*' */
		"",	/* 13 should be double dagger */
		"", 	/* 14 paragraph sign */
		"",		/* 15 should be short vertical bar */
		"",		/* 16 should be broken vertical bar */
		"",		/* 17 double vertical bar */
	};

char * macint_lbrackets[] = {
		"",	/* left square bracket */
		"",	/* left parenthesis */
		"",	/* left angle bracket */
		"",	/* left curly bracket */
		"",	/* left double bracket */
		"",/* left half bracket */
			/* the hell with the rest of them for now*/
};

char * macint_rbrackets[] = {
		"",	/* right square bracket */
		"",	/* right parenthesis */
		"",	/* right angle bracket */
		"",	/* right curly bracket */
		"",	/* right double bracket */
		"",/* right half bracket */
			/* the hell with the rest of them for now*/
};

char * macint_quotes[] = {
		"\"",		/* 0 neutral double quote */
		"\\'\\'",	/* 1 low double close quote */
		"\\'\\'",	/* 2 normal double close quote */
		"\"",		/* 3 normal single close quote */
		",",		/* 4 */
		"\\'",		/* 5 */
		"\"",		/* 6 */
};

char *macint_tgreek = "";
char *macint_tbgreek = "";
char *macint_troman = "";

char * macint_newline = "\n";

fix_macint_save(fname)
char * fname;
{
}

add_macint_header(f)
FILE * f;
{
}
