#include <gkstring.h>

add_morphflags(gk_string *gstr, MorphFlags * Flags)
{
	unsigned char * Mf = morphflags_of(gstr);
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		morphflags_of(gstr)[i] |= Flags[i];
}

set_morphflags(gk_string *gstr, MorphFlags *Flags)
{
	unsigned char * Mf = morphflags_of(gstr);
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		morphflags_of(gstr)[i] = Flags[i];
}


set_gwmorphflags(gk_word *gkword, MorphFlags *Flags)
{
	unsigned char * Mf = morphflags_of(gkword);
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		morphflags_of(gkword)[i] = Flags[i];
}


zap_morphflags(gk_string *gstr, MorphFlags *Flags)
{
	unsigned char * Mf = morphflags_of(gstr);
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		morphflags_of(gstr)[i] &= ~(Flags[i]);
}

has_morphflags(gk_string *gstr, MorphFlags *Flags)
{
	unsigned char * Mf = morphflags_of(gstr);
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		if( morphflags_of(gstr)[i] & Flags[i])
			return(1);
}

no_morphflags(gk_string *gstr)
{
	MorphFlags * Mf = morphflags_of(gstr);
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		if( morphflags_of(gstr)[i] )
			return(0);
	return(1);
}

add_morphflag(MorphFlags *Mf, int n)
{
	int index;
	int setbit;

	n = n & MORPHFLAG_MASK;
	mflag_num_to_bits(n,&index,&setbit);

	Mf[index] |= (setbit & 0377);
/*
fprintf(stderr,"n [%d] index [%d] setbit [%o] Mf[index] [%o]\n", n , index, setbit, Mf[index]) ;
*/
}

overlap_morphflags(MorphFlags *Mf1, MorphFlags *Mf2)
{
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		if( Mf1[i] & Mf2[i] ) return(1);
	return(0);
}

has_morphflag(MorphFlags *Mf, int n)
{
	int index;
	int setbit;

	n = n & MORPHFLAG_MASK;
	mflag_num_to_bits(n,&index,&setbit);
/*	
fprintf(stderr,"n %d , index %d setbit [%o] Mf[Index] %o anded [%o]\n", n,index, setbit,Mf[index],
Mf[index] & (setbit & 0377));
*/	
	return(Mf[index] & (setbit & 0377));
}


zap_morphflag(MorphFlags *Mf, int n)
{
	int index;
	int setbit;

	n = n & MORPHFLAG_MASK;
	mflag_num_to_bits(n,&index,&setbit);

	Mf[index] &= ~(setbit & 0377);
}

set_morphflag(MorphFlags *Mf, int n)
{
	int i;
	int index;
	int setbit;

	n = n & MORPHFLAG_MASK;
	mflag_num_to_bits(n,&index,&setbit);

	for(i=0;i<MORPHFLAG_BYTES;i++) Mf[i] = 0;
	if( n > 0 ) 
		Mf[index] = setbit& 0377;
}

no_morphflag(MorphFlags *mf)
{
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) 
		if( mf[i] )
			return(0);
	return(1);
}

mflag_num_to_bits(int n, int *ind, int *bitnum)
{
	if( (n % 8) == 0 ) {
		*ind = (n/8) - 1;
		*bitnum = 0200;
	} else {
		*ind = n/8;
		*bitnum = 1 << ((n % 8) - 1);
	}
/*
fprintf(stderr,"num to bits [%d] ind %o bit %o\n", n , *ind, *bitnum );
*/
}

mflag_bit_to_num(int ind, int bitnum)
{

	return( (ind*8) + bitnum );
}

Dump_morphflag(MorphFlags *mf)
{
	int i;
	
	for(i=0;i<MORPHFLAG_BYTES;i++ ) printf("byte %d [%o]\n", i , mf[i] );
}

#define TABSIZE MORPHFLAG_BYTES*8 
static char * ugly_tab = NULL;

is_pretty_morphflag(long mnum)
{
	if( ! ugly_tab ) 
		init_ugly_tab();
	return( ! ugly_tab[(int)mnum] );
}

init_ugly_tab(void)
{
	ugly_tab = (char *)calloc((size_t)TABSIZE+1,(size_t)sizeof * ugly_tab );
	
	ugly_tab[PERS_NAME] = 1;
	ugly_tab[SUFF_ACC] = 1;
	ugly_tab[STEM_ACC] = 1;
	ugly_tab[ANT_ACC] = 1;
	ugly_tab[NO_COMP] = 1;
	ugly_tab[SHORT_PEN] = 1;
	ugly_tab[LONG_PEN] = 1;
	ugly_tab[ACCENT_OPTIONAL] = 1;
	ugly_tab[NEEDS_ACCENT] = 1;
/*
	ugly_tab[R_E_I_ALPHA] = 1;
*/
	ugly_tab[NOT_IN_COMPOSITION] = 1;
	ugly_tab[HAS_PREVERB] = 1;
	ugly_tab[HAS_AUGMENT] = 1;
}


char * prvb_tab = NULL;
is_prvb_morphflag(long mnum)
{
	if( ! prvb_tab ) 
		init_prvb_tab();
	return( prvb_tab[(int)mnum] );
}
 

void * zogalloc(size_t, size_t);

init_prvb_tab(void)
{
	
	if( prvb_tab ) return;
	prvb_tab = (char *)calloc((size_t)(TABSIZE+1),(size_t)(sizeof * prvb_tab) );
		
	if (! prvb_tab) {
		fprintf(stderr,"Damn!\n");
		exit(-1);
	}	
	

	prvb_tab[DISSIMILATION] = 1;
	prvb_tab[PREVB_AUGMENT] = 1;
	prvb_tab[ELIDE_PREVERB] = 1;
	prvb_tab[ROOT_PREVERB] = 1;
	prvb_tab[RAW_PREVERB] = 1;
	prvb_tab[UNASP_PREVERB] = 1;
	prvb_tab[APOCOPE] = 1;
	prvb_tab[DOUBLED_CONS] = 1;

}

xfer_prvbflags(MorphFlags *word_mf, MorphFlags *prvb_mf)
{
	int i;
	
	for(i=0;i<TABSIZE;i++) {
		if( is_prvb_morphflag(i) && has_morphflag(word_mf,i) ) {
				zap_morphflag(word_mf,i);
				add_morphflag(prvb_mf,i);
		}
	}
}


 MorphNames(MorphFlags *mf, char *res, char *dels, int pretty)
{
	char * s, * NameOfMorphFlags();
	long i;
	long j;
	long curnum;
	int mask = 1;
	int hit = 0;

	*res = 0;
	
	for(i=0;i<MORPHFLAG_BYTES;i++) {
		mask = 1;
		for(j=0;j<8;j++) {
			
			if( mf[i] & mask ) {
					curnum = (long)mflag_bit_to_num((int)i,(int)j+1);
				if( ! pretty || is_pretty_morphflag(curnum) ) {
					/*(i*8) + j + 1;*/
	
					hit++;
					s=NameOfMorphFlags(curnum);

					if( *s ) {
						if(*res) strcat(res,dels);
						strcat(res,s);
					}
				}
			}
			mask = mask << 1;
		}
	}
	
/*
fprintf(stderr,"%o %o %o %o \n", mf[0] , mf[1], mf[2], mf[3] );
*/
}

