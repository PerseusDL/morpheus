/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 *      routines that deal with the TLG reference system
 */

/*
 * this module contains the routines that keep track of the Beta code
 * reference in a TLG text. they interpret the various flags that are
 * set or incremented in the TLG texts.
 */

/*
 * to understand this module you have to understand something about the
 * way in which references are stored in TLG texts:
 *      each time a line of text is read, the line number should be
 * incremented.
 *      lines beginning with a '~' indicate some change in the reference
 * other than simply  incrementing the line counter.
 *      various flags indicate different levels of citation: the lowest
 * level of citation, the individual line, is designated by 'z', the
 * highest (often a book number) is designated by 'w'.
 *      the TLG, therefore, uses the letters of the alphabet, starting from
 * 'z' and working on down as far as 'w' to designate progressively higher
 * forms of reference. 
 */

/*
 *                      To print or not to print.....
 *
 *      this module keeps track of when it thinks you should print a reference
 * screen. normally, it will set "PrintFlag" whenever the line number is evenly
 * divisible by 5. it also checks for irregularities (such as a line number
 * like "36-37" or "176a" and will set "PrintFlag". also, anytime a register
 * higher than the 'z' level is changed, the PrintFlag is set.
 * the function:
 *      gotref()
 * returns the value of "PrintFlag".
 */


/*
 *      GetReference( ref )
 *      reference * ref;
 *
 *              given a reference "ref", set the registers in this module 
 *      to equal the values of the registers in "ref"
 */

/*
 *      SetReference( ref )
 *      reference * ref;
 *              
 *              store the current state of the reference registers in the
 *      data structure pointed to by "ref"
 */

/*
 *       ClrReference()
 *
 *              clear the values of the reference registers in this module
 */

/*
 *      NextTlgLine( s , len , authname )
 *      char * s;
 *      int len;
 *      char * authname;
 *      
 *      read in the next *printing* line in the author.tlg file.
 *      this means that if NextTlgLine() sees 
 *              "~y10z3"
 *      it parses the reference, stores the results, and then reads another line
 *      of text.
 */

/*
 *      get_textoffset()
 *
 *      returns the value of "textoffset". this register records the pointer
 *      to the actual *text* line. when NextTlgLine is first called, textoffset
 *      is set to the ftell(fin). NextTlgLine() then calls TxtFgets().
 *      if NextTlgLine() first sees that it has got a reference such as
 *              "~y10z3"
 *      "textoffset" is set to the new value of ftell(fin).
 *
 *      reason for this: a user points at a character on the screen. you want
 *      to be able to reconstruct the offset in the file at which the user
 *      points. therefore, you want to be able to add "the number of bytes into
 *      the line at the point selected" together with "the initial offset of
 *      this text line".
 */

/*
 * PrintLab( print_ref )
 * char * print_ref;
 *
 *      creates a readable reference out of the reference registers and
 *      places the result in the string print_ref.
 *      
 *      it calls prnt_gkfield() on the successive gkfield-s.
 */

/*
 * prnt_gkfield( S , s )
 * gkfield * S;
 * char * s;
 *
 *      Takes the *gkfield* pointed to by S and turns it into a readable
 *      reference. this readable reference is *appended* to s.
 */

/*
 * tlg_label( std_ref )
 * char * std_ref;
 *
 *      creates a standard ASCII TLG reference string
 *      out of the reference registers and
 *      places the result in the string print_ref.
 *      
 *      it calls tlg_gkfield() on the successive gkfield-s.
 */


/*
 * tlg_gkfield(S, s )
 * gkfield * S;
 * char * s;
 *
 *      turns the gkfield pointed to by S into its ASCII TLG standard 
 *      equivalent
 */

/*
 * parse_refline(s)
 * char * s;
 *
 * given a Tlg reference line, it parses the individual fields, storing the
 * results in s.
 */
 
#include "defcons.h"
#include "tlg.h"

    static gkfield w_field;
    static gkfield x_field;
    static gkfield y_field;
    static gkfield z_field;
    static int worknumber = 0;

    static long textOffset;

    static int prevline = 0;
    static int prevchl = 0;
    static int PrintFlag = 0;
    static int hyphflag = 0;
    static int delimc = ' ';

    char shortlab[SHORTLAB];
    static char cur_textline[MAXLIN];
    static char cur_label[MAXLIN];
    static char cur_std_ref[MAXLIN];

    reference Cur_ref;
    static reference SaveRef;
    static reference * TmpR = NULL;
    static reference * CloseRef = NULL;
    static reference * CurRef = NULL;
    static reference * tmpRef = NULL;


/*
 * functions
 */
    long TxtFtell();
    reference * tlg_cur_ref();
    char * TxtFgets();
    long   TxtFseek();

 GetReference( ref )
  reference * ref;
{

        if( worknumber )
                ref->refwknum = worknumber;
        ref->w_field = w_field;
        ref->x_field = x_field;
        ref->y_field = y_field;
        ref->z_field = z_field;
}

 SetReference( ref )
  reference * ref;
{

        worknumber = ref->refwknum;
        w_field = ref->w_field;
        x_field = ref->x_field;
        y_field = ref->y_field;
        z_field = ref->z_field;
}

 ClrReference()
{
        worknumber = 0;
        w_field.num = 0; w_field.ch = 0;
        x_field = w_field;
        y_field = w_field;
        z_field = w_field;
}

long
 get_textoffset()
{
        return( textOffset );
}

 set_textoffset(off)
  long off;
{
        textOffset = off;
}

 NextTlgLine( s , len , authname )
  register char * s;
  int len;
  char * authname;
{
        char * getarg();
        register char * starts = s;
	reference PrevRef, NewRef;

        set_textoffset(TxtFtell(authname));
        PrintFlag = 0;
        if( ! TxtFgets(s, len ,authname ) ) {
                return( 0 );
        }

        if( *s == '~' ) {
                ++s;
		GetReference(&PrevRef);
                parse_refline(s);
		/*
		 * this checks to see if a reference is out of place
	 	 * (e.g. 444,446,445). if it is, then make sure you
		 * print a reference.
		 */
		GetReference(&NewRef);
		if( RefEqual(&PrevRef,&NewRef) ) {
			PrintFlag++;
		}
		/*
		 * or if you skip more than one line ...
		 */
		if( NewRef.z_field.num - PrevRef.z_field.num > 1 )
			PrintFlag++;

                set_textoffset(TxtFtell(authname));
                if( ! TxtFgets(starts, len , authname ) ) {
                        return( 0 );
                }
        } else {
                if( z_field.ch )
                        z_field.ch++;
                else
                        z_field.num++; 
                if( z_field.num % 5 == 0 )
                        PrintFlag++;
        }

        if( z_field.num % 5 == 0 )
                PrintFlag++;    
        return( 1 );
                
}

 gotref()
{
        return( PrintFlag );
}

char * 
 getarg( lpoint , S )
  register char * lpoint;
  register gkfield * S ;
{
        S->oddlabel[0] = 0;
        if( isdigit( *lpoint ) ) {
                S->ch = 0;
                S->num = 0;
                while( isdigit( *lpoint ) )
                        S->num = (*lpoint++ - '0') + ( 10 * S->num );
                return( lpoint );
        }
        if( *lpoint == '"' ) {
                register char * a;
                char tmp[MAXLIN];

                S->num = S->ch = 0;
                a = tmp;
                lpoint++;
                while( *lpoint != '"' && *lpoint )
                        *a++ = *lpoint++;
                *a = 0;

                a = tmp;
                while( *a ) {
                        if( *a == '-' ) {
                                hyphflag++;
                                break;
                        }
                        a++;
                }
                if( hyphflag ) {
                        hyphflag = 0;
                        strncpy( S->oddlabel , tmp , sizeof S->oddlabel );
                        return( ++lpoint );
                }
                a = tmp;
                while( !isdigit( *a ) && !isalpha( *a ) )
                        a++;
                while( isdigit( *a ) )
                        S->num = (*a++ - '0') + ( S->num * 10 );
                if( isalpha( *a ) && *a < 'm' )
                        S->ch = *a++;
                return( ++lpoint );
        }

        if( S->ch ) {
                S->ch++;
                return( lpoint );
        }       
        S->num++;
        return( lpoint );
}

 tlg_label( tlg_ref )
  register char * tlg_ref;
{

        int printed = 0;

        tlg_ref[0] = '~';
        tlg_ref[1] = 0;
        tlg_gkfield( &w_field , tlg_ref );
        tlg_gkfield( &x_field , tlg_ref );
        tlg_gkfield( &y_field , tlg_ref );
        if( z_field.ch >= 'p' )
                return;
        tlg_gkfield( &z_field , tlg_ref );
        if( z_field.num == prevline && prevchl == z_field.ch )
                PrintFlag = 0;
        if( !z_field.oddlabel[0] ) {
                prevchl = z_field.ch;
                prevline = z_field.num;
        } else
                PrintFlag++;
}

 PrintLab( print_ref )
  register char * print_ref;
{

        int printed = 0;

        print_ref[0] = 0;
        if( prnt_gkfield( &w_field , print_ref ) ) {
                strcat( print_ref , "." );
        }
        if( prnt_gkfield( &x_field , print_ref ) ) {
                if( y_field.num )
                        strcat( print_ref , "." );
        }
        if( prnt_gkfield( &y_field , print_ref ) )
                printed++;
        if( printed )
                sprintf( print_ref , "%s%c", print_ref, delimc );
        if( z_field.ch >= 'p' )
                return;
        prnt_gkfield( &z_field , print_ref );
        if( z_field.num == prevline && prevchl == z_field.ch )
                PrintFlag = 0;
        if( !z_field.oddlabel[0] ) {
                prevchl = z_field.ch;
                prevline = z_field.num;
        } else
                PrintFlag++;
}

 beta_lab( beta_ref )
  register char * beta_ref;
{

        int printed = 0;

        beta_ref[0] = 0;
        beta_gkfield( &w_field , 'w' , beta_ref );
        beta_gkfield( &x_field , 'x' , beta_ref );
        beta_gkfield( &y_field , 'y' , beta_ref );
        beta_gkfield( &z_field , 'z' , beta_ref );
}

 beta_gkfield( Gk , field , s )
  gkfield * Gk;
  int field;
  char * s;
{
        char tmp[64];

        if( Gk->oddlabel[0] ) {
                sprintf(tmp,"%c:\"%s\"", field, Gk->oddlabel );
                strcat( s , tmp );
                return;
        }
        if( Gk->ch ) {
                if( Gk->num ) 
                        sprintf(tmp,"%c\"%d%c\"", field , Gk->num , Gk->ch );
                else
                        sprintf(tmp,"%c\"%c\"", field , Gk->ch );
                strcat( s , tmp );
                return;
        }
        if( Gk->num ) {
                sprintf(tmp,"%c%d", field , Gk->num );
                strcat( s , tmp );
                return;
        }
                
}

/*
 * this routine fits a normal reference to a template
 * it assumes that the data structures w_field,x_field, y_field and line
 * have been initialized, and will try to match the sequence of 
 * numbers and characters to the implied form. thus
 * it knows that "48e 1" becomes "x:48 y:e" in plato, but "y:48e" in
 * aristotle.
 */
 query_reference( print_ref , targref , endref )
  register char * print_ref;
  reference * targref;
  reference * endref;
{
        char * p;
        char rest_of_ref[128];

#define usedref( X ) ( (X).num || (X).ch || (X).oddlabel[0] )

        
/*
 * trim off any trailing blanks
 */
	p = print_ref;
	while(*p) p++; p--;
	while(*p == ' ' || *p == '\t' || *p == '\n' )
		*p-- = 0;

        p = print_ref;
        if( usedref( w_field ) ) {
	    match_printref( &w_field , &(targref->w_field), p , rest_of_ref );
	    if( ! rest_of_ref[0] ) {
                        (targref->x_field).num = 1;
                        (targref->y_field).num = 1;
                        (targref->z_field).num = 1;
			*endref = *targref; 
			FieldIncrement(&(endref->w_field));
                        return( 1 );
	    }
	    p = rest_of_ref;
        }
        if( usedref( x_field ) ) {
	    match_printref( &x_field , &(targref->x_field), p , rest_of_ref );
	    if( ! rest_of_ref[0] ) {
                        (targref->y_field).num = 1;
                        (targref->z_field).num = 1;
			*endref = *targref; 
			FieldIncrement(&(endref->x_field));
                        return( 1 );
	    }
	    p = rest_of_ref;
        }
        if( usedref( y_field ) ) {
	    match_printref( &y_field , &(targref->y_field), p , rest_of_ref );
	    if( ! rest_of_ref[0] ) {
                        (targref->z_field).num = 1;
			*endref = *targref; 
			FieldIncrement(&(endref->y_field));
                        return( 1 );
	    }
                p = rest_of_ref;
        }
        if( usedref( z_field ) ) {
	    match_printref( &z_field , &(targref->z_field), p , rest_of_ref );
	    *endref = *targref; 
	    FieldIncrement(&(endref->z_field));
	}
	return(1);
}

#define DELIMITER( X ) (! isalpha( X ) && ! (isdigit( X ) ) )

/*
 * try to match the chars in source with the template implied in template
 * and store the value in targfield. store remainder of string in remains.
 */
 
 match_printref( template , targfield , source , remainder )
  register gkfield * template;
  register gkfield * targfield;
  register char * source;
  register char *remainder;
{
        int n;
        char * s;

        s = source;

        while( DELIMITER( *s ) && *s )
                s++;

        if( template->num ) {
/*
                if( ! isdigit( *s ) && *s ) {
                        return( ERROR );
                }
*/
                targfield->num = atoi(s);
                while( isdigit( *s ) )
                        s++;
                while( DELIMITER( *s ) && *s )
                        s++;
        }
/*
 * if you are expecting an alphabetic reference (e.g. a stephanus
 * page a la "334c" or you unexpectedly get one (e.g. Aesch. Suppl. 176c).
 */
        if( template->ch  ) {
/*
                if( *s && ! (isalpha( *s ) ) ) {
                        return(ERROR);
                }
*/
                if( ! *s ) {
                        targfield->ch = 'a';
                } else
                        targfield->ch = *s;
                while( isalpha( *s ) )
                        s++;
                while( DELIMITER( *s ) && *s )
                        s++;
        }
        strcpy( remainder , s );
	return(1);
}

 prnt_gkfield( S , s )
  register gkfield * S;
  register char * s;
{
        if( S->oddlabel[0] ) {
                strcat( s , S->oddlabel );
                return( 1 );
        }
        if( S->num ) {
                sprintf(s,"%s%d", s , S->num );
                if( S->ch ) {
                        sprintf(s,"%s%c", s , S->ch );
                        return( 1 );
                }

                return( 1 );
        }
        if( S->ch ) {
                sprintf(s,"%s%c", s , S->ch );
                return( 1 );
        }
        return( 0 );
}

 tlg_gkfield( S , s )
  register gkfield * S;
  register char * s;
{
        if( ! S->oddlabel[0] && ! S->num && ! S->ch ) 
                return(0);
        if( S == &w_field ) {
                strcat(s,"w");
        } else if ( S == &x_field ) {
                strcat(s , "x" );
        } else if ( S == &y_field) {
                strcat(s , "y" );
        } else if ( S == &z_field) {
                strcat(s, "z" );
        }

        if( S->oddlabel[0] ) {
                sprintf( s , "%s\"%s\"", s , S->oddlabel );
                return( 1 );
        }
                
        if( S->num ) {
                if( S->ch ) {
                        sprintf(s,"%s\"%d%c\"", s , S->num , S->ch );
                        return( 1 );
                }
                sprintf(s,"%s%d", s , S->num );
                return( 1 );
        }
        if( S->ch ) {
                sprintf(s,"%s\"%c\"", s , S->ch );
                return( 1 );
        }
        return( 0 );
}

 parse_refline(s)
  register char *s;
{
        char * a;

        if( *s == '~' ) s++;

        while( *s && *s != '\n' ) {
                switch( *s ) {
                        case ' ':
                                s++;
                                break;
                        case 'a':
                        case 'b':
                                x_field.num = x_field.ch = 0;
                                y_field.num = y_field.ch = 0;
                                shortlab[0] = 0;
                                ++s; ++s;
                                worknumber = atoi( s );
                                while( *s != '"' && *s )
                                        s++;
                                s++;
                                break;
                        case 'c':
                                a = shortlab;
                                ++s; ++s;
                                while( *s != '"' && *s )
                                        *a++ = *s++;
                                *a = 0;
                                s++;
                                break;
        
                        case 'w':
                                x_field.num = 1;
                                y_field.num = 1;
                                z_field.num = 1;
                                z_field.ch = 0;
                                prevline = 0;
                                prevchl = 0;
                                s = getarg( ++s , &w_field );
                                PrintFlag++;
                                break;
                        case 'x':
                                y_field.num = 1;
                                z_field.num = 1;
                                z_field.ch = 0;
                                prevline = 0;
                                prevchl = 0;
                                s = getarg( ++s , &x_field );
                                PrintFlag++;
                                break;
                        case 'y':
                                z_field.num = 1;
                                z_field.ch = 0;
                                prevline = 0;
                                prevchl = 0;
                                s = getarg( ++s , &y_field );
                                PrintFlag++;
                                break;
                        case 'z':
                                s = getarg( ++s , &z_field );
                                if(z_field.num == 0 && z_field.ch == 0 )
                                        z_field.num = 1;
                                break;
                        default:
                                tlg_error("unexpected case in switch: ", s );
                                break;
                }
        }
}

/*
 * skip to the line in file "f" that contains offset "off" 
 *
 * the beta source string for the line containing "off" is left in 
 * cur_textline. calling tlg_cur_textlin() returns a pointer to this
 * array.
 */
 tlg_seek( authname , off )
  char * authname;
  long off;
{
        char * tlg_cur_textline();
        int rval = NEXTREC;

/* VICIOUS BUG! note the commented out Calloc allocates 4 bytes for a large 
   structure!!!
        TmpR = (reference *) Calloc(1,sizeof TmpR );
*/
        if( ! TmpR )
                /*TmpR = (reference *) Calloc(1,sizeof * TmpR );*/
                TmpR = &SaveRef;

        SetRefForOffset(TmpR,authname,off);
        SetReference(TmpR);
        TxtFseek( authname,TmpR->Offset );

/*
 * don't scan forward if you are pointing at the very opening of
 * a file. if you do, then you will pass (and probably forget)
 * the first line of the file later on.
 */

	if( off > 0 ) {
            for(;;) {
                NextTlgLine( cur_textline , sizeof cur_textline , authname );
                if( off < TxtFtell(authname) )
                        break;
	    }
        }

        finish:
                
                return( rval );
}

char * 
 tlg_cur_textline()
{
        return( cur_textline );
}

reference * 
 tlg_cur_ref()
{
        Cur_ref.w_field = w_field;
        Cur_ref.x_field = x_field;
        Cur_ref.y_field = y_field;
        Cur_ref.z_field = z_field;
        return(&Cur_ref);
}

char *
 tlg_cur_label(c)
  int c;
{
        if( c ) delimc = c;
        PrintLab( cur_label );
        delimc = ' ';
        return( cur_label );
}

char *
 get_Print_ref(ref)
  reference * ref;
{
        char * tlg_cur_label();
        w_field = ref->w_field;
        x_field = ref->x_field;
        y_field = ref->y_field;
        z_field = ref->z_field;
        return(tlg_cur_label(' '));
}

char *
 tlg_std_ref(ref)
  reference * ref;
{
        w_field = ref->w_field;
        x_field = ref->x_field;
        y_field = ref->y_field;
        z_field = ref->z_field;
        tlg_label( cur_std_ref );
        return( cur_std_ref );
}


/*
 * given a target reference in an author, return the offset in the author at
 * which this reference begins 
 *
 */

long
 FindRef(authname,targref,endref,singlework)
  char * authname;
  reference * targref;
  reference * endref;
  int singlework;
{
        char raw_ref[128];
        char curline[MAXLIN];
	int rval;
        long curptr = 0;
	long endptr = 0;

        if( CloseRef == NULL ) {
             if( (CloseRef = 
                (reference *)Calloc(1 , sizeof * CloseRef )) == NULL ) {
                        prerror("FindRef:could not initalize CloseRef");
                        return(-1);
             }
        }

        if( tmpRef == NULL ) {
             if( (tmpRef = 
                (reference *)Calloc(1 , sizeof * tmpRef )) == NULL ) {
                        prerror("FindRef:could not initalize tmpRef");
                        return(-1);
             }
        }

        if( CurRef == NULL ) {
             if( (CurRef = 
                (reference *)Calloc(1 , sizeof * CurRef )) == NULL ) {
                        prerror("FindRef:could not initalize CurRef");
                        return(-1);
             }
        }

        OpTxtFile(authname);



        /* go to starting point for this work in author.point */
        SetRefForRef(targref,CloseRef,targref->Offset,authname);
        SetReference(CloseRef);
        TxtFseek(authname,CloseRef->Offset);

        /* 
         * now scan the text file itself, line by line until you come to a
         * reference that is *greater* than the target reference.
         *
	 * this routine can cope, more or less, with lines that have
	 * been rearranged by a text editor:
	 *	a) it demands exact equality for its target line, ie.
	 *		if you want "444" it looks exactly for line 444.
	 *	b) when it wants to figure out where line 444 ends,
	 *		it basically looks for line 445, but
	 *		what happens when 444 has been moved so that 
	 *		445 is not the next line?
	 *
	 *		In a sequence such as 445,444,446, you just
	 *		check to see that 446 is bigger than 445, so
	 *		you figure you have gone too far, and don't
	 *		worry about the fact that you never actually
	 *		saw 445.
	 *
	 *		But in a sequence such as 446,448,447,449, 
	 *		where you wanted to get 448 and wanted to find
         * 		out where 449 was so that you could chop off the
	 *		end of 448, you would accidentally include line
	 *		447. we therefore check to see if references have
	 * 		suddenly started to decrease (ie. we have a line
	 *		pushed forward by an editor). so we keep going
	 *		until 
	 *			current_ref > endref || targref > current_ref
	 *
	 *
	 * if singlework is set and you ask for 
	 * "Aesch Suppl. 1078" (which doesn't exist), the system will
	 * complain when it gets to the end of that play.
         *
 	 * on the other hand, how many people know to which work in
	 * Plutarch's Moralia stephanus page 887c belongs?
	 *
         * thus, if singlework is 0, then in plutarch, 
	 * the user does not need to know to what specific
         * work a stephanus number belongs. the user only needs to start the
         * routine looking in the first of the moralia, and the routine will
         * continue on till it finds the proper reference or an end of file
	 * it finds a line 1078.
         */

        while(1) {
                curptr = TxtFtell(authname);
                if( ! NextTlgLine(curline , sizeof curline , authname ) )
			break;
                GetReference( tmpRef );
/*
                if( (rval=RefEqual( tmpRef , targref )) >= 0 ) {
*/
                if( ! (rval=RefEqual( tmpRef , targref ))  ) {
                                break;
                }

		if( (curptr > targref->wrkend) && singlework ) {
	/*
	 * no such reference in this work!
	 */
printf("failure: no such reference\n");		
		curptr = -1;
		goto finish;
		}
        }
/*
printf("rval:%d in comparing ", rval ); printsect(tmpRef,0); printf(" and ");printsect(targref ,1);
*/

        while(1) {
                endptr = TxtFtell(authname) - 1;
                if( ! NextTlgLine(curline , sizeof curline , authname ) ) 
			break;
                GetReference( tmpRef );
		if( RefEqual( tmpRef , endref ) >= 0 
			|| RefEqual( targref, tmpRef ) > 0 ) {
                                break;
                }
        }
	endref->Offset = endptr;

    finish:
        ClrReference();
        ClTxtFile(authname);
        
        return(curptr);
}

/*
 * this function compares a list of wordoffsets to a line of greek.
 * if any of the word offsets falls within the line, then the word is
 * preceded by an escape that turns boldface on and followed by an escape
 * that turns the bold off.
 */

 markwords(startoff,line,wordoffs)
  long startoff;
  char * line;
  long * wordoffs;
{
        long * offlist = wordoffs;
        long endoff = startoff + strlen(line);

        /*
         * scan wordoffs *backwards*, because each time you insert
         * escape sequences, you alter the offset of all succeeding
         * chars in the line.
         */


        while(*offlist) offlist++; offlist--;

        while(offlist>=wordoffs) {
                if( *offlist >= startoff && *offlist < endoff ) {
                        MarkWord((int)(*offlist - startoff),line);
                }
                offlist--;
        }
        
}

 MarkWord(index,s)
  int index;
  char * s;
{
        char part1[256], part2[256];
        char * p2 = part2;
        strcpy(part2,s+index);
        strcpy(s+index,"$1");
        while(*s) s++;

        while(!WHITE(*p2)) 
                *s++ = *p2++;
        *s++ = '$';
        strcpy(s,p2);
}
