/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"
#define BYTERANGE 500


char * tlg_cur_label();
char * tlg_cur_textline();
long get_textoffset();
long TxtFtell();
static srch_state Srch;

/*
 * given a word starting at a given offset in an author,
 * put that word in bold and print it out, with some context
 */
ShowWordAtOff(sname,offset,offlist)
char * sname;
long offset;
long * offlist;
{
        long startout, end;
        char line[256];
        

        if( offset > BYTERANGE )
                startout = offset - BYTERANGE;
        else
                startout = 0;

        end = offset + BYTERANGE;

        if( ! OpTxtFile(sname) ) {
                fprintf(stderr,"Could not open %s\n", Srch.sname );
                return(-1);
        }



        tlg_seek(sname,startout);
        strcpy(line,tlg_cur_textline());
        markwords(get_textoffset(),line,offlist);

        strcpy(Srch.sname,sname);
        workbyoff(&Srch,TxtFtell(Srch.sname));
        printf("\n\n______");
        printf("%s %s\n", Srch.title,tlg_cur_label(' ') );              
        printf("%s", line );

        while(NextTlgLine(line,sizeof line,sname)) {
                if( TxtFtell(Srch.sname) > end )
                        break;
                markwords(get_textoffset(),line,offlist);
                workbyoff(&Srch,TxtFtell(Srch.sname));
                if( gotref() ) {
                        printf("%s %s\n", Srch.title,tlg_cur_label(' ') );         
                }
                printf("%s", line );
        }
        ClTxtFile(Srch.sname);
        return(1);
}
