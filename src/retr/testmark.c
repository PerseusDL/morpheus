/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "srchstate.h"

    srch_state Srch;
    long offlist[3];

 main(argc,argv)
  int argc;
  char * argv[];
{
        char line[256];
        FILE * f;
        int i;


        if( argc != 2 ) {
                fprintf(stderr,"format: %s recfile\n", argv[0] );
                exit(-1);
        }
        if( !(f=fopen(argv[1],"r")) ) {
                fprintf(stderr,"Could not open %s\n", argv[1] );
                exit(-1);
        }
        while(getgrec(&Srch,f)) {
                offlist[0] = Srch.pword;
printf("Srch:pword %ld; sname %s; gotstr %s\n", Srch.pword , Srch.sname, Srch.gotstr );
                ShowWordAtOff(Srch.sname,offlist[0],offlist);
        }
        
}

