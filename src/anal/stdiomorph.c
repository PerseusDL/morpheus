#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <prntflags.h>
#include "stdiomorph.proto.h"
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC  1000000         /* ANSI C clock ticks per sec */
#endif

#include <time.h>
int quickflag = 0;
char * anal_buf();
long prevmemory = 0;
time_t start_time = 0;
time_t prev_time = 0;
time_t end_time = 0;
double avg_time = 0;
double long_time = 0;
double string_time = 0;
char long_string[BUFSIZ];
int timeit = 1;

#define ARGS "ILalmnbckidsxSVpPeTo:"
#define PATH_SEP '/'

main(argc,argv)
int argc;
char *argv[];
{
  FILE * finput, *foutput, *ffailed, *fstats;

	finput = foutput = ffailed = fstats = NULL;
  char line[BUFSIZ*4];
  char fname[BUFSIZ],inpname[BUFSIZ], outname[BUFSIZ], failedname[BUFSIZ], statsname[BUFSIZ];
  char destPath[BUFSIZ];
  
  PrntFlags flags = (PERSEUS_FORMAT|STRICT_CASE);
  int rval;
  long freemem = 0;
  long nwords = 0;
  long nhits = 0;
  char * p;
  int c, errflg = 0;

  outname[0] = '\0';

  while (!errflg && (c = getopt(argc,argv,ARGS)) != -1) {
    switch (c) {
    case 'a':
      flags |= SHOW_ANAL;
      break;
    case 'l':
      flags |= SHOW_LEMMA;
      break;
    case 'm':
      flags |= SHOW_MISSES;
      break;
    case 'b':
      flags |= BUFFER_ANALS;
      break;
    case 'c':
      flags |= CHECK_PREVERB;
      break;
    case 'I':
      set_lang(ITALIAN);
      break;
    case 'L':
      set_lang(LATIN);
      break;
    case 'k':
      flags |= KEEP_BETA;
      break;
    case 'i':
      flags |= SHOW_FULL_INFO;
      break;
    case 'd':
      flags &= ~(PERSEUS_FORMAT);
      flags &= ~(LEXICON_OUTPUT);
      flags |= DBASEFORMAT;
      break;
    case 's':
      flags |= DBASESHORT;
      break;
    case 'n':
      flags |= IGNORE_ACCENTS;
      break;
    case 'x':
      flags |= LEXICON_OUTPUT;
      break;
    case 'V':
      flags |= VERBS_ONLY;
      break;
    case 'S':
      flags &= ~(STRICT_CASE);
      break;
    case 'p':
      flags |= PARSE_FORMAT;
      break;
    case 'P':
      flags &= ~(PERSEUS_FORMAT);
      break;
    case 'e':
      flags |= ENDING_INDEX;
      break;
    case 'T':
      timeit = 0;
      break;
    case 'o':
      if (!strcmp(optarg,"-")) {
	foutput = stdout;
	fstats = ffailed = stderr;
      } else {
	strcpy(outname,optarg);
	sprintf(failedname,"%s.failed",outname);
	sprintf(statsname,"%s.stats",outname);
printf("outname [%s]\n", outname );
      }
      break;
    default:
      errflg++;
    }
  }
  
  if (optind >= argc) {
    finput = stdin;
    foutput = stdout;

    fstats = ffailed = stderr;
  } else {
    strcpy(fname,argv[optind++]);
    strcpy(inpname,fname);
    strcat(inpname,".words");
    
    if (optind >= argc) {
      if (outname[0] == '\0') {
	sprintf(outname,"%s.morph",fname);
	sprintf(failedname,"%s.failed",fname);
	sprintf(statsname,"%s.stats",fname);
      }
fprintf(stdout,"files: [%s] [%s]\n", outname, failedname);
    } else {
      strcpy(destPath,argv[optind]);
      sprintf(outname,"%s%c%s.morph",destPath, PATH_SEP, fname);
    }
    
    fprintf(stderr,"Input: %s\nOutput: %s\n",inpname,outname);
    
    if((finput=fopen(inpname,"r")) == NULL) {
      fprintf(stderr,"cannot find [%s]!\n", inpname);
      exit(-1);
    }
  }

  if( foutput != stdout && ((foutput=fopen(outname,"w")) == NULL)) {
    fprintf(stderr,"cannot find [%s]!\n", outname);
    exit(-1);
  }
  
  if( ffailed != stderr && ((ffailed=fopen(failedname,"w")) == NULL)) {
    fprintf(stderr,"cannot open [%s]!\n", failedname);
    exit(-1);
  }
  
  if( fstats != stderr && ((fstats=fopen(statsname,"w")) == NULL)) {
    fprintf(stderr,"cannot open [%s]!\n", statsname);
    exit(-1);
  }
  
  while(fgets(line,(size_t)sizeof line,finput)) {
    /*
       char * t;
       t = line;
       while(*t&&!isspace(*t)) t++;
       *t = 0;
       rval = chckcmpvb(line,destPath);
       if( ! rval ) {
       printf("failed on [%s]\n", line );
       }
       */
    /*
       printf("%s %s %d\n", line, prevl , dictstrcmp(line,prevl) );
       strcpy(prevl,line);
       continue;
       */		
    
    
    trimwhite(line);

    if( isspace(line[0]) && ! line[0] ) continue;
    if( line[0] == '#' ) {
	fprintf(foutput,"%s\n", line );
	continue;
    }

    trimdigit(line);
    p = line;
    while(*p&&!isspace(*p)) p++;
    if( p == line ) continue;
    if(*p) *p = 0;
    
    if (timeit) {
      prev_time = clock();
      if( start_time == 0 ) start_time = prev_time;
    }
    /*setatticprose();*/
    /*set_nocrasis();*/

    rval = checkstring(line,flags,foutput);
    if( cur_lang() != LATIN && ! rval && (flags & IGNORE_ACCENTS) ) {
	char tmpform[BUFSIZ];

	strcpy(tmpform,line);
	stripbreath(tmpform);
	addbreath(tmpform,')');
        rval = checkstring(tmpform,flags,foutput);
	if( ! rval ) {
		stripbreath(tmpform);
		addbreath(tmpform,'(');
		rval = checkstring(tmpform,flags,foutput);
	}
    }
    
    if( timeit ) {
      end_time = clock();
      string_time = (double) (end_time - prev_time)/ CLOCKS_PER_SEC ;
      if( string_time >= long_time && nwords > 0 && rval ) {
	
	long_time = string_time;
	strcpy(long_string,line);
	fprintf(stderr,":longtime\t%.2f\t%s\n", long_time, long_string );
      }
    }
    
    nwords++;
    if( rval ) {
      nhits++;
      fprintf(foutput,"%s",anal_buf() );
    } else {
      /*	printf("%s\t:failed\n", line );*/
      if( flags & SHOW_LEMMA && flags & IGNORE_ACCENTS ) fprintf(ffailed,"form:", line );
      fprintf(ffailed,"%s\n", line );
      fflush(ffailed);
    }
    
    if(! ( nwords % 1000) ) {
      if( timeit ) {
	avg_time = (double)(end_time - start_time)/(CLOCKS_PER_SEC * (double)nwords) ;
	
	fprintf(stderr,":time %.2f %.2f\n", avg_time , string_time );
      }
      fprintf(stderr,"%ld %ld %0.2f %s %d\n", nwords , nhits, 100* ((float)nhits/(float)nwords) , line , rval  );
    }
  }
  if( finput != stdin )
    fclose(finput);
  fclose(foutput);
  fclose(ffailed);
  if(nwords) {
    fprintf(fstats,"FINAL:  words %ld, analyzed %ld (%0.2f pct), %d\n", 
	    nwords , nhits, 100* ((float)nhits/(float)nwords) , rval  );
    fprintf(stderr,"FINAL:  words %ld, analyzed %ld (%0.2f pct), %d\n", 
	    nwords , nhits, 100* ((float)nhits/(float)nwords) , rval  );
    }

  if( nhits ) {
	fprintf(fstats,":nhits %ld anals %ld anals/hit %0.2f lems %d lems/hit %0.2f\n",
		nhits, show_totanals() , 
		((float)show_totanals()/(float)nhits),
		show_totlems(),
		((float)show_totlems()/(float)nhits) );
  }		

    if( timeit ) {
      fprintf(fstats,":avg time %.2f; long time [%.2f] for [%s]\n", avg_time , long_time, long_string );
      fprintf(stderr,":avg time %.2f; long time [%.2f] for [%s]\n", avg_time , long_time, long_string );
     }
  
  fclose(fstats);
  exit(0);
}

trimdigit(char *s)
{
  char * p = s;
  while(*s) s++;
  s--;
  while(isdigit(*s)&&s>p) *s-- = 0;
}
