/*
 * Copyright Gregory Crane
 * April 1987
 */

#include "sysinc.h"
#include "tlgwind.h"

 tlg_error(s1,s2)
  char *s1;
  char *s2;
{
#ifdef CURSES
        wprintw(w_stat,"%s%s--hit any key to continue", s1 , s2 );
#else
        fprintf(stdout,"%s%s--hit any key to continue", s1 , s2 );
        fflush(stdout);
#endif
        getchar();
}

 prerror(s)
  char * s;
{
        printf("%s--hit any key to continue", s );
        getchar();
}


