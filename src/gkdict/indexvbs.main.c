#include <gkstring.h>

#include "indexstems.main.proto.h"
int verbose = 0;


main(argc,argv)
int argc;
char * argv[];
{
        int c, errflg = 0;

        while (!errflg && (c = getopt(argc,argv,"L")) != -1) {
                switch (c) {
                        case 'L':
                                set_lang(LATIN);
                                break;
                        default:
                                break;
                }
        }

	index_vbs(3,0,0,0);

}
