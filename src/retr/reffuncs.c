/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 * routines to perform operation on reference type structures
 */

#include "srchstate.h"
#include "tlg.h"

/*
 * return whether or not R1 is greater than R2:
 *      1       if R1 > R2
 *      0       if R1 == R2
 *     -1       if R1 < R2
 */
 RefEqual( R1, R2 )
  reference * R1;
  reference * R2;
{
	int rval;

        if( R1->refwknum != R2->refwknum ) {
                return( R1->refwknum - R2->refwknum );
        }

 	if( (rval=GkfEqual(&(R1->w_field),&(R2->w_field),1)))
		return(rval);
 	if( (rval=GkfEqual(&(R1->x_field),&(R2->x_field),2)))
		return(rval);
 	if( (rval=GkfEqual(&(R1->y_field),&(R2->y_field),3)))
		return(rval);
 	if( (rval=GkfEqual(&(R1->z_field),&(R2->z_field),4)))
		return(rval);

        return( 0 );
        
}

 GkfEqual(gkf1,gkf2,prt)
  gkfield * gkf1;
  gkfield * gkf2;
  int prt;
{
	int rval;


	if( gkf1->oddlabel[0] && my_index(gkf1->oddlabel,'-') ) {
/*
 * if we have a range, like "71-72" or "80-83"
 */
		char rest_of_label[64];
		gkfield StrtGkfield, EndGkfield, CurGkfield;
		char * p = gkf1->oddlabel;

		EndGkfield.oddlabel[0] = StrtGkfield.oddlabel[0] = 0;
		match_printref( gkf1 , &StrtGkfield , p , rest_of_label );
		p = rest_of_label;
		match_printref( gkf1 , &EndGkfield , p , rest_of_label );

		for(CurGkfield=StrtGkfield;
		   GkfEqual(&CurGkfield,&EndGkfield)<=0;
		   FieldIncrement(&CurGkfield) ) {
			   rval=GkfEqual(&CurGkfield,gkf2,1);
			   if( !rval ) return(0);
		}
		return((rval=GkfEqual(&EndGkfield,gkf2,1)));
	}
        if( gkf1->num != gkf2->num ) {
                return( gkf1->num - gkf2->num );
        }
        if( gkf1->ch != gkf2->ch )
                return( gkf1->ch - gkf2->ch );
	return(0);
}

 printsect( ref , flag )
  reference * ref;
  int flag;
{
                putsect( "w:" , &(ref->w_field) );
                putsect( "x:" , &(ref->x_field) );
                putsect( "y:" , &(ref->y_field) );
                putsect( "z:" , &(ref->z_field) );
                if( flag )
                        putchar( '\n' );
                fflush( stdout );
}

 putsect( s , S )
  char * s;
  gkfield * S;
{
        if( ! S->num && !S->ch )
                return;
        printf( "%s",s );
        if( S->num )
                printf("%d", S->num );
        if( S->ch )
                printf("%c", S->ch );
        putchar( ' ' );
}


FieldIncrement(Gkfield)
gkfield * Gkfield;
{
	if( Gkfield->ch ) {
		Gkfield->ch++;
		return;
	}
	if( Gkfield->num ) {
		Gkfield->num++;
		return;
	}
}

SetRefFromString(srch)
srch_state * srch;
{
	long FindRef();
	reference * targref;
	reference * endref;
	int i;
	
	if( ! strncmp( srch->Print_ref , "end" , strlen("end") ) ) {
		srch->pword = srch->recwkend;
		return( OK );
	}

	targref = (reference *)calloc(1, sizeof * targref );
	endref = (reference *)calloc(1, sizeof * endref );

	/*
	 * read a couple of lines in from the start of work, and
	 * get a sample reference 
	 */
	OpTxtFile(srch->sname);
	tlg_seek(srch->sname,srch->recwkstart);
	for(i=0;i<10;i++){
		char tmp[128];

		if( ! NextTlgLine(tmp,sizeof tmp,srch->sname) ) break;
	}
	ClTxtFile(srch->sname);
	

	if( query_reference(srch->Print_ref,targref,endref) < 0 )
		printf("");
	endref->refwknum = targref->refwknum = srch->recwknum;
	endref->Offset = targref->Offset = srch->recwkstart;
	endref->wrkend = targref->wrkend = srch->recwkend;
	srch->pstart = srch->pword = FindRef(srch->sname,targref,endref,1);
	srch->pend = endref->Offset;

	free(targref);
	free(endref);
	return( ADVANCE );
}
