/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#include "tlgwind.h"


 fput_com( f , srch , combuf )
  FILE * f;
  srch_state * srch;
  char * combuf;
{
        register char * s;

        s = combuf;
        while( *s != '\t' )
                s++;
        s++;
        fprintf(f,":%s", s );
        fadd_newline(f);
        if( f != stdout )
                fclose( f );
}


 fput_ind_word( f , srch , ptr )
  FILE * f;
  srch_state * srch;
  long ptr;
{
        static long freq;
        static long prec;

        GetFreqP2( srch->sname , ptr , &freq , &prec );
        fprintf(f,":sn:%s\twd:%s\taf:%ld\tpA:%ld ",
                        srch->sname , srch->gotstr , freq , prec );

        fadd_newline(f);
        return( 1 );
}

#define PREC    1       /* pointer to a list of pointers for a word */
#define PWORD   2       /* pointer to a word in the text */
#define P2WORDS 4       /* pointers to two words or phrases */
#define PSTEND  010     /* pointers for start and end of pass */


 fput_rec( f , srch , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        checkdel( del );
        fputc(  ':' , f  );
        fput_sname( f , srch  , del );
        fput_ptr( f , srch  , del );
        fput_wd( f , srch  , del );
/*
        if( srch->pword ) {
*/
        if( srch->pword || srch->pstart ) {
                fput_wknum( f , srch  , del );
                fput_tit( f , srch  , del );
                fput_Ref( f , srch , del );
        }
        fadd_newline(f);
        fflush( stdout );

}

 fput_tit( f , srch  , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        if( srch->pword && ! srch->recwknum ) 
                workbyoff( srch , srch->pword );
        fprintf(f, "ti:%s%s", srch->title , del );
}

 fput_wknum( f , srch  , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        if( srch->pword && ! srch->recwknum ) 
                workbyoff( srch , srch->pword );
        fprintf(f, "wk:%d%s", srch->recwknum , del );
}


 fput_ptr( f , srch  , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        if( srch->pw2 > 0 ) {
                fprintf(f,"p1:%ld p2:%ld%s", srch->pword , srch->pw2 , del );
                return( P2WORDS );
        }

        if( srch->pword > 0 ) {
                fprintf(f,"pW:%ld%s", srch->pword , del );
                return( PWORD );
        }

        if( srch->p2 > 0 ) {
                fprintf(f,"pA:%ld%s", srch->p2 , del );
                fprintf(f,"af:%ld%s", srch->freq , del );
                return( PREC );
        }


        if( srch->pstart > 0 ) {
                fprintf(f,"pS:%ld%s", srch->pstart , del );
                if( srch->pend > 0 ) {
                        fprintf(f,"pE:%ld%s", srch->pend , del );
                }
                return( PSTEND );
        }
        return( -1 );
}

 fput_sname( f , srch  , del ) 
  FILE * f;
  srch_state * srch;
  char * del;
{
        fprintf(f,"sn:%s%s", srch->sname , del );
}

 fput_fname( f , srch  , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        if( srch->fname[0] ) {
                fprintf(f,"fn:%s%s", srch->fname , del );
                return( 1 );
        } else {
                fprintf(f,"fn:%s" , del );
                return( 0 );
        }
        
}

 fput_wd( f , srch  , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        char * w1 = NULL;
        char * w2 = NULL;

        if( srch->gotstr[0] ) w1 = srch->gotstr; else w1 = srch->key;

        if( srch->key2[0] ) w2 = srch->key2;
        else if( srch->gotstr2[0] ) w2 = srch->gotstr2;

        if( w1 ) {
                if( w2 ) {
                        fprintf(f,"wd:%s%sw2:%s%s", w1 , del , w2 , del );
                        return;
                }
/*
                        fprintf(f,"wd:%s%s", w1 , del );
*/
                if( *w1 )
                        fprintf(f,"wd:%s%s", w1 , del );
                return;
        }
}

 fput_Ref( f , srch , del )
  FILE * f;
  srch_state * srch;
  char * del;
{
        if( srch->Print_ref[0] ) {
                fprintf(f,"re:\"%s\"%s", srch->Print_ref , del );
                return;
        }
        if( srch->endref[0] ) {
                fprintf(f,"r1:\"%s\"%s", srch->Print_ref , del );
                fprintf(f,"r2:\"%s\"%s", srch->endref , del );
                return;
        }
}

#define DEFDEL "\t"

 checkdel( s )
  char * s;
{
        if( *s == 0 )
                s = DEFDEL;
}

 fdump_ref( f , srch )
  FILE * f;
  srch_state * srch;
{
        fprintf(f,"%s %s", srch->title , srch->Print_ref );
        fadd_newline(f);
}

 fdump_c( c , f )
  int c;
  FILE * f;
{
        fputc( c , f );
}


SaveFromTo(srch, start, end, foutfile )
srch_state * srch;
long start;
long end;
FILE * foutfile;
{
	char tmp[256];
	char cur_line[256];
	int index;
	char * a;
	char * b;
	int i;

	tlg_seek( srch->sname , start );
	/* copy current line into cur_line */
	strcpy( cur_line , tlg_cur_textline() );


	index = (int)(start - (get_textoffset()));
	if( index > 0 ) 
		GkPartOfLine(foutfile,cur_line,index,2);
	else
		gk_sprint( cur_line , PRINTFLAG );

	for(;;) {
		NextTlgLine( cur_line , sizeof cur_line , srch->sname );
		if( TxtFtell(srch->sname) > end )
			break;
		if( gotref() ) {
			fprintf(foutfile,"~%s", tlg_cur_label(' ') );
			fadd_newline(foutfile);
		}
		gk_sprint( cur_line , PRINTFLAG );
	}
	
	/* get fragment of last line */
	/* if you use a string to delineate a passage, end points to
	   the beginning of that string--but you want to see the
	   passage up to and including the string.
		if, however, no string was specified, just read up to
	   the pointer, which, in this case, indicates the beginning of
	   of a new section.
	*/

	if( gotref() ) {
		fprintf(foutfile,"~%s", tlg_cur_label(' ') );
		fadd_newline(foutfile);
	}
	/*
	 * this is not the right way to do it: the routine that converts
	 * a reference into a start and a stop offset, should set the end
	 * offset to the end of the second string. this routine should just
	 * mindlessly copy to the stop offset!
	 */
	if( srch->key[0]) {
		a = tmp; b = cur_line;
		for(i=0;i<end-get_textoffset();i++)
			*a++ = *b++;
		while( !isalpha( *b ) && *b ) 
			*a++ = *b++;
		while( *b != ' ' && *b != '\n' && *b )
			*a++ = *b++;
		*a = 0;
		gk_sprint(tmp  , PRINTFLAG );
		fadd_newline(foutfile);
	} else if (get_textoffset() < end ) {
		index = (int)(end - get_textoffset());
		GkPartOfLine(foutfile,cur_line , index + 1 , 1 );
		fadd_newline(foutfile);
	}
		
	fadd_newline(foutfile);
	
	C_devpop(srch->savefile);
}

GkPartOfLine(f,s,index,part)
FILE *f;
char *s;
int index;
int part;
{
	char tmp[256];
	int i;

	if( index < 0 ) 
		return(-1);
	if( part == 1 ) {
		strcpy(tmp,s);
		*(s+index) = 0;
		gk_sprint(s,PRINTFLAG);
		fadd_newline(f);
		return(1);
	}
	if( part == 2 ) {	
		for(i=0;i<index;i++) 
			fputc( ' ', f );
		gk_sprint(s+index,PRINTFLAG);
		return(1);
	}
	return(-1);
}
