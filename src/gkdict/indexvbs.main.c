#include <unistd.h>
#include <gkstring.h>
#include "../gkdict/indexstems.proto.h"
#include "../morphlib/setlang.proto.h"

#include "indexstems.main.proto.h"
int verbose = 0;


main(argc,argv)
int argc;
char * argv[];
{
        int c, errflg = 0;

        while (!errflg && (c = getopt(argc,argv,"IL")) != -1) {
                switch (c) {
                        case 'I':
                                set_lang(ITALIAN);
                                break;
                        case 'L':
                                set_lang(LATIN);
                                break;
                        default:
                                break;
                }
        }

	index_vbs(3,0,0);

}
