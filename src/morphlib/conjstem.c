#include <ctype.h>
#include <gkstring.h>

#include "conjstem.proto.h"


fixcontr(char *stem, char *verb)
/* expand stem for contract verbs */
{
	if (A_CONTR(verb) || E_CONTR(verb))
		Xstrncat(stem,"h",MAXWORDSIZE);
	if (O_CONTR(verb))
		Xstrncat(stem,"w",MAXWORDSIZE);
}

makeperf(char *s)
{
	register char *p;

	p = lastn(s,1);
	if (Is_dental(*p) || *p == 'z')
		*p = 'k';	 /* Smyth 560 */
	else if (Is_labial(*p) && *p != 'f')
		*p = 'f';			/* Smyth 569 */
	else if (Is_palatal(*p) && *p != 'x')
		*p = 'x';
	else if (*p == 'f' || *p == 'x')
		;		/* leave aspirated stops alone */
	else if (Is_liquid(*p) || Is_nasal(*p))
		;	/* Smyth 562 */
	else
		conjoin(s,"k");
}

fixperf(char *s)
{
	register char *p;

	if( *(lastn(s,1)) != 'k' ) 
		return;
		
	p = lastn(s,2);
	if (Is_dental(*p) || *p == 'z') {
		*p = 'k';	 /* Smyth 560 */
		*(p+1) = 0;
	}
	else if (Is_labial(*p) && *p != 'f') {
		*p = 'f';			/* Smyth 569 */
		*(p+1) = 0;
	}
	else if (Is_palatal(*p) && *p != 'x') {
		*p = 'x';
		*(p+1) = 0;
	}
	else if (*p == 'f' || *p == 'x') {
		*(p+1) = 0;
	}		/* leave aspirated stops alone */
/*
 * grc 8/29/94
 *
 * no! leave as is
 * otherwise we get e)fqar-ka --> e)fa-ka
 */
	else if (/*Is_liquid(*p) ||*/ Is_nasal(*p)) {
		*(p+1) = 0; /* Smyth 562 */
	}
}

conjstem(char *stem, char *e)
{
	register char *p;
	char ending[MAXWORDSIZE];

	p = lastn(stem,1);
	Xstrncpy(ending,e,MAXWORDSIZE);

	/* quick and dirty implementation of Smyth 405 */
	if (Is_cons(*p)) {
		if (0 == strcmp(ending,"ntai") )
			Xstrncpy(ending,"me/noi ei)si/{n}",MAXWORDSIZE);
		if (0 == strcmp(ending,"nto") ) {
			Xstrncpy(ending,"me/noi h)=san",MAXWORDSIZE);
			if (0 == Xstrncmp(stem,"e)",2)) {
				strsqz(stem,2);
				p -= 2;
				}
			}
		}

	if (0 == strcmp(ending,"hqi") && (*p == 'q'))	/* Smyth 125b */
		ending[1] = 't';

	conjoin(stem,ending);
}

conjoin(char *stem, char *e)
{
	/* observe the laws of euphony, if you please... */
	register char *p;
	char ending[MAXWORDSIZE];
	int changed;

	p = lastn(stem,1);
	Xstrncpy(ending,e,MAXWORDSIZE);
/*
 * this has got to be fixed if it is going to work at all well with
 * dialects!
 */
 
 /*
  * grc 4/21/89
  * an unbelievable kludge to allow me to generate plass- from plat-ss so that
  * i can get the epic form pla/ssa.  unbelievable! ugh.
  */
 	if( (Is_dental(*p) || *p == 'z' || *p == 'n' ) && !Xstrncmp(e,"ss",2) ) {
 		Xstrncpy(p,e,MAXWORDSIZE-(int)(p-stem));
 		return;
 	}
 	
	do {
		changed = NO;
		switch(ending[0]) {
			case 's':
				changed = do_sigma(p,ending);
				break;
			case 'q':
				changed = do_theta(p);
				break;
			case 'm':
				changed = do_mu(p);
				break;
			case 't':
				changed = do_tau(p);
				break;
			}
		} while (changed);
	Xstrncat(stem,ending,MAXWORDSIZE);
}

do_sigma(char *s, char *ending)
{
	/* Smyth 537,545 */
	register char *p;
	int changed;

	p = lastn(s,1);
	changed = YES;

	if (*p == 'q' && ! strncmp(ending,"sk",2)) {
		*p = 's'; /* grc 9/3/94:  paq-skw --> pasxw */
		ending[1] = 'x';
	}
	if (Is_cons(*p) && Is_cons(ending[1]))
		strsqz(ending,1);	/* s between consonants drops out */
	else if (Is_labial(*p)) {
		*p = 'y';
		strsqz(ending,1);
		}
	else if (Is_palatal(*p)) {
		*p = 'c';
		strsqz(ending,1);
		}
/*
 * grc 9/12/88
 *
 * don't punt the 'r' or 'l' for two reasons:
 *
 *  a) a trashed 's' tends to lengthen the preceding syllable, e.g.
 *			estelsa --> esteila
 *
 *  b) this rule causes *amerdsa --> a)mesa, rather than --> a)mersa
 */ 
	else if (Is_dental(*p) || /*Is_liquid(*p) ||*/ Is_nasal(*p) || *p == 'z')
		*p = 0;	/* stops, liquids, etc. drop out Smyth 544*/
	else if (*p == 's' && *ending == 's')
		*p = 0; /* don't add 2nd s */
	else
		changed = NO;

	return (changed);
}

int do_theta(char *s)
{
	/* Smyth 587 */
	register char *p;
	int changed;

	changed = YES;
	p = lastn(s,1);
	if (Is_labial(*p) && *p != 'f')
		*p = 'f';
	else if (Is_palatal(*p) && *p != 'x')
		*p = 'x';
	else if (Is_dental(*p) || *p == 'z')
		*p = 's';
	else
		changed = NO;
	return (changed);
}

int do_mu(char *s)
{
	/* Smyth 85 */
	register char *p;
	int changed;

	changed = YES;
	p = lastn(s,1);
	if (Is_labial(*p)) {
		if (*(p-1) == 'm')
			*p = 0;
		else
			*p = 'm';
		}
	else if (Is_palatal(*p) && *p != 'g')
		*p = 'g';
	else if (Is_dental(*p) || *p == 'z')
		*p = 's';
	else
		changed = NO;
	return (changed);
}

int do_tau(char *s)
{
	/* Smyth 82-83 */
	register char *p;
	int changed;

	changed = YES;
	p = lastn(s,1);
	if (Is_labial(*p) && *p != 'p')
		*p = 'p';
	else if (Is_palatal(*p) && *p != 'k')
		*p = 'k';
	else if (Is_dental(*p) || *p == 'z')
		*p = 's';
	else
		changed = NO;
	return (changed);
}
