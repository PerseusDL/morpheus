static char  SCCSID[] = "@(#)gk_sprint.c	2.1  9/26/87";
/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 * Gregory Crane
 * Harvard Classics Computer Project
 * Fall 1985
 * 
 * this module takes greek in beta code format and outputs it in a variety of
 * other formats.
 *
 * it calls the finite state automaton written by jud harward at cincinnati.
 *
 * all possible Greek characters in beta translit 
 * are (or should be, anyway) stored
 * in "beta_tab.c". the char strings in that module are compiled 
 * into a tree, and the automaton uses this tree
 * to segment the input. tkparse() returns the value associated with the
 * string that has been matched (see "beta_tab.c").
 *
 * NOTE: the automaton does *not* look for beta escape sequences. all 
 * escape sequence of the form "$2" or "[5" or "%9" are caught by a
 * switch that examines each character before passing it off to the
 * automaton. if this switch finds a beta code escape sequence, it traps
 * the input. this switch is found in filt_line().
 *
 * IF YOU WANT TO ADD A NEW CHARACTER, you must give it a name and value in
 * "filttab.h". then you must add the input token associated with this character
 * to "beta_tab.c". you must then add the appropriate entry to
 * the XXXX_greek.c files, so that the print routine will output some
 * suitable string when it sees this input string.
 *	NOTE: this will not work if the character is represented
 * by an escape sequence that is trapped in filt_line(). if this is the case,
 * you must simply hack the routine that filt_line() calls when it sees
 * that particular escape sequence.
 *
 * NOTE: if you are writing to a window (ie., using curses, for now), you
 * must set the variable "to_window". if you are writing to a file, you must
 * clear this variable.
 *
 * LIMITATIONS: doubtless many. No attempt is made to parse non-greek input.
 * thus, the name "Wilamowitz", which is stored "*wilamowitz" in beta format,
 * is also printed "*wilamowitz". this should be fixed, but there is not
 * that much non-greek text in the TLG and we have let this slide for now...
 *
 */

#include  <usual.h>
#include  <ctype.h>
#include  <token.h>
#include "filttab.h"
#include "devices.h"
#include <stdio.h>
#define MAX_CELLS 512
#define  MAXKEY  100
#define NOTHING 0

FILE * fout = stdout;
static TKtree  Tree;
int ret;
int lastret = 0;
static int lastlen = 0;
int match_val = 0;
extern filt_tab beta_tab[];

/* 
 * external tables for various devices
 * 
 * if you are adding a new device to this module, you can use one of these 
 * as a template.
 */

/*
 *	SMK Greek Keys tables (entry in "devices.h": GREEK_KEYS)
 */
extern char *gkkey_greek[];	/* all combinations of greek char and accent */
extern char *gkkey_dgreek[];	/* all combinations of greek char, accent and
					underline dot */
/*
 * these tables generally correspond to tables of beta escape sequences 
 * they are arrays of char strings. if you want to get the appropriate output
 * string for "[5" when using Greek Keys, the trap routine for "[" escapes
 * will ultimately access gkkey_lbrackets[5].
 */

extern char *gkkey_punct[];	/* punctuation */
extern char *gkkey_quotes[];	/* quotes */
extern char *gkkey_lbrackets[];	/* left brackets */
extern char *gkkey_rbrackets[];	/* right brackets */

/*
 * very rudimentary escape sequences 
 */
extern char *gkkey_tgreek;	/* escape into greek */
extern char *gkkey_tbgreek;	/* escape into bold greek */
extern char *gkkey_troman;	/* escape into roman */
extern char *gkkey_newline;	/* newline sequence */
int fix_gkkey_save();
int add_gkkey_header();

/*
 *	SUNTOOLS format (entry in "devices.h": SUNW)
 */
#ifdef SUNTOOL
extern char *sun_greek[];	/* all combinations of greek char and accent */
extern char *sun_dgreek[];	/* all combinations of greek char, accent and
					underline dot */
extern char *sun_punct[];	/* punctuation */
extern char *sun_quotes[];	/* quotes */
extern char *sun_lbrackets[];	/* left brackets */
extern char *sun_rbrackets[];	/* right brackets */

/*
 * very rudimentary escape sequences 
 */
extern char *sun_tgreek;	/* escape into greek */
extern char *sun_tbgreek;	/* escape into bold greek */
extern char *sun_troman;	/* escape into roman */
extern char *sun_newline;	/* newline sequence */
int fix_sun_save();
int add_sun_header();

#endif SUNTOOL

/*
 *	MS RTF using SMK Greek Keys (entry in "devices.h": MS_RTF)
 */
extern char *rtf_greek[];	/* all combinations of greek char and accent */
extern char *rtf_dgreek[];	/* all combinations of greek char, accent and
					underline dot */
/*
 * these tables generally correspond to tables of beta escape sequences 
 * they are arrays of char strings. if you want to get the appropriate output
 * string for "[5" when using Greek Keys, the trap routine for "[" escapes
 * will ultimately access rtf_lbrackets[5].
 */

extern char *rtf_punct[];	/* punctuation */
extern char *rtf_quotes[];	/* quotes */
extern char *rtf_lbrackets[];	/* left brackets */
extern char *rtf_rbrackets[];	/* right brackets */

/*
 * very rudimentary escape sequences 
 */
extern char *rtf_tgreek;	/* escape into greek */
extern char *rtf_tbgreek;	/* escape into bold greek */
extern char *rtf_troman;	/* escape into roman */
extern char *rtf_newline;	/* newline sequence */
int fix_rtf_save();
int add_rtf_header();


/*
 * tables for the Interleaf format (entry in "devices.h": INTERLEAF)
 */
#ifndef MACINTOSH
#ifndef SUNTOOL
extern char *ileaf_greek[];
extern char *ileaf_dgreek[];
extern char *ileaf_punct[];
extern char *ileaf_quotes[];
extern char *ileaf_lbrackets[];
extern char *ileaf_rbrackets[];
extern char *ileaf_tgreek;
extern char *ileaf_tbgreek;
extern char *ileaf_troman;
extern char *ileaf_newline;
int fix_ileaf_save();
int add_ileaf_header();
#endif SUNTOOL
#endif

/*
 * tables for the Nota Bene format (entry in "devices.h": NOTA_BENE)
 */
#ifndef MACINTOSH
#ifndef SUNTOOL
extern char *nb_greek[];
extern char *nb_dgreek[];
extern char *nb_punct[];
extern char *nb_quotes[];
extern char *nb_lbrackets[];
extern char *nb_rbrackets[];
extern char *nb_tgreek;
extern char *nb_tbgreek;
extern char *nb_troman;
extern char *nb_newline;
int fix_nb_save();
int add_nb_header();
#endif SUNTOOL
#endif

/*
 * tables for the Signifier format (entry in "devices.h": SIGNIFIER)
 */

/*
 * leave this out if compiling for a mac
 */
#ifndef MACINTOSH
#ifndef SUNTOOL
extern char *signf_greek[];
extern char *signf_dgreek[];
extern char *signf_punct[];
extern char *signf_quotes[];
extern char *signf_lbrackets[];
extern char *signf_rbrackets[];
extern char *signf_tgreek;
extern char *signf_tbgreek;
extern char *signf_troman;
extern char *signf_newline;
int fix_signf_save();
int add_signf_header();
#endif SUNTOOL

/*
 * tables for pseudo-troff output format (entry in "devices.h": FILEFORMAT)
 */
extern char *troff_greek[];
extern char *troff_dgreek[];
extern char *troff_punct[];
extern char *troff_quotes[];
extern char *troff_lbrackets[];
extern char *troff_rbrackets[];
extern char *troff_tgreek;
extern char *troff_tbgreek;
extern char *troff_troman;
extern char *troff_newline;
int fix_troff_save();
int add_troff_header();

/*
 * tables for macintalk output format (entry in "devices.h": FILEFORMAT)
 */
extern char *macint_greek[];
extern char *macint_dgreek[];
extern char *macint_punct[];
extern char *macint_quotes[];
extern char *macint_lbrackets[];
extern char *macint_rbrackets[];
extern char *macint_tgreek;
extern char *macint_tbgreek;
extern char *macint_troman;
extern char *macint_newline;
int fix_macint_save();
int add_macint_header();

/*
 * tables for mac terminal greek output format (entry in "devices.h": VT100)
 */
#ifndef SUNTOOL
extern char *mact_greek[];
extern char *mact_dgreek[];
extern char *mact_punct[];
extern char *mact_quotes[];
extern char *mact_lbrackets[];
extern char *mact_rbrackets[];
extern char *mact_tgreek;
extern char *mact_tbgreek;
extern char *mact_troman;
extern char *mact_newline;
int fix_mact_save();
int add_mact_header();

/*
 * tables for ibm apa8 greek output format (entry in "devices.h": IBM_HFT)
 */
extern char *hft_greek[];
extern char *hft_dgreek[];
extern char *hft_punct[];
extern char *hft_quotes[];
extern char *hft_lbrackets[];
extern char *hft_rbrackets[];
extern char *hft_tgreek;
extern char *hft_tbgreek;
extern char *hft_troman;
extern char *hft_newline;
int fix_hft_save();
int add_hft_header();

/*
 * tables for the Human Designed Systems, Concept Avt terminal
 * that has been modified to display greek (entry in "devices.h": AVT).
 */
extern char *avt_greek[];
extern char *avt_dgreek[];
extern char *avt_punct[];
extern char *avt_quotes[];
extern char *avt_lbrackets[];
extern char *avt_rbrackets[];
extern char *avt_tgreek;
extern char *avt_tbgreek;
extern char *avt_troman;
extern char *avt_newline;
int fix_avt_save();
int add_avt_header();
#endif SUNTOOL
#endif

/*
 * these static variables contain the current values for various tables.
 * when initializing for a new device, these pointers are set to the appropriate
 * tables in the groups above. e.g., if you are generating output for 
 * an avt, cur_greek is set to avt_greek, udot_greek to avt_dgreek etc.
 */
static char ** cur_greek;
static char ** udot_greek;
static char ** lbrack_tab;
static char ** rbrack_tab;
static char ** quote_tab;
static char ** cur_punct;
static char * esc_tgreek;
static char * esc_tbgreek;
static char * esc_troman;
static char * newline;
int (*fix_savefile)();
int (*add_header)();

static int cur_device = 0;
static int prev_device = 0;
static int cur_font = GREEK;
static int to_window = 0;
static nchars = 0;
static rev_vid_point = -1;
static in_rev_vid = 0;
static int troff_flag = 0;	/* flag to force ``troff'' style format for save files */
static int greek_keys = 0;	/* save in greek keys format */
static int started = 0;

static char * Cp;	/* pointer to current spot in input stream */

/* buffer for input line */
char source_buf[MAX_CELLS * 2]; 
/* buffer for input line when converted into new format */
char gk_lbuf[MAX_CELLS * 4];
/*
 * this array correlates the printing chars with chars in the input stream. 
 * if you want to see what part of source_buf[] corresponds to Column X
 * on the screen, you look at "&source_buf[pos_in_source[X]]".
 */
int pos_in_source[MAX_CELLS]; 

int read_chars = 0; /* number of chars in input line processed so far */
static char * source_line; /* pointer to cur position in source_line */
char cur_char[MAX_CELLS]; /* output string for current char--note a single
				char represented as a string! */
int cur_len = 0; /* number of input chars consumed in the current token */
static int screen_pos = 1; /* current Column Number on screen--ie., num of
			printing chars */

char text_buf[MAX_CELLS];
char match_buf[MAX_CELLS];

static char  *keys[MAX_GK_CHARS+1];

/*
 *			!!!!!!!!!
 * 			NOTA BENE
 *			!!!!!!!!!
 *
 *	all of the following routines may need to be modified if you add
 *	a new device type.
 * 	
 *	device  independent routines currently begin with def_startup().
 * 	there is a note in the text after the last device dependent routine.
 */

/*
 * this routine must be called to set up buffers, automata etc. otherwise,
 * you are guaranteed a segmentation fault!
 */
gk_startup(device)
int device;
{
	char line[128];
	
	if( started )
		return;
	started;
	cur_device = device;

	cur_font = GREEK;
	if (( Tree = tkpcreate()) == NULL )  {
	    printf("Can't create Tree\n");
	    exit(1);
	}
/* 
 * if you are looking at a VT100, you are probably on a mac and want to
 * save text Greek Keys format. this flag tends to force that if you are
 * using C_devpush(). this is meaningless if you use C_devforce().
 */
	if( device == VT100 )
		greek_keys++;
/*
 * FOR NEW DEVICES, you need to add an appropriate setup_XXXX_greek()
 * routine
 *
 * Note that for the Sun workstation, the setup routine is called out of the
 * window handling package (gktl.c).
 */
	setup_gkkey_greek();
	setup_rtf_greek();
	
#ifndef MACINTOSH
	setup_troff_greek();
#ifndef SUNTOOL
	setup_macint_greek();
	setup_avt_greek();
	setup_mact_greek();
	setup_hft_greek();
	setup_signf_greek();
 	setup_ileaf_greek();
 	setup_nb_greek();
#endif SUNTOOL
#endif

	init_table( beta_tab , beta_length( beta_tab ) );
#ifdef MACINTOSH
	init_char_tabs(GREEK_KEYS);
#else
	init_char_tabs(device);
#endif

}

/*
 * this allows a user to force troff output format.
 * it is ignored if your routines call C_devforce()
 */
save_troff_format()
{
	troff_flag++;
}

/*
 * here, set up your output tables. note that you can put in
 * some printf() or other routines here to initialize your
 * device, if that is necessary
 */
init_char_tabs(device)
int device;
{
	switch( device ) {
#ifndef MACINTOSH
#ifndef SUNTOOL
		case  VT100:
			to_window = 1;	/* this is a window */
			cur_greek = mact_greek;
			udot_greek = mact_dgreek;
			cur_punct = mact_punct;
			lbrack_tab = mact_lbrackets;
			rbrack_tab = mact_rbrackets;
			quote_tab = mact_quotes;
			esc_tgreek = mact_tgreek;
			esc_tbgreek = mact_tbgreek;
			esc_troman = mact_troman;
			newline = mact_newline;
			fix_savefile = fix_mact_save;
			add_header = add_mact_header;

			/* define 'ascii' as normal cset */
			fprintf(stdout,"\033(b");
			fprintf(stdout,"\033)0");
			fflush(stdout);
			break;	
		case MACINTALK:
			to_window = 0; /* this is a text file */
			cur_greek = macint_greek;
			udot_greek = macint_dgreek;
			cur_punct = macint_punct;
			lbrack_tab = macint_lbrackets;
			rbrack_tab = macint_rbrackets;
			quote_tab = macint_quotes;
			esc_tgreek = macint_tgreek;
			esc_tbgreek = macint_tbgreek;
			esc_troman = macint_troman;
			newline = macint_newline;
			fix_savefile = fix_macint_save;
			add_header = add_macint_header;
			break;

		case  IBM_HFT:
			to_window = 1;	/* this is a window */
			cur_greek = hft_greek;
			udot_greek = hft_dgreek;
			cur_punct = hft_punct;
			lbrack_tab = hft_lbrackets;
			rbrack_tab = hft_rbrackets;
			quote_tab = hft_quotes;
			esc_tgreek = hft_tgreek;
			esc_tbgreek = hft_tbgreek;
			esc_troman = hft_troman;
			newline = hft_newline;
			fix_savefile = fix_hft_save;
			add_header = add_hft_header;
			break;	
		case  AVT:
			to_window = 1;	/* this is a window */
			/* 
			 * define alternate char set as vt108 graphics 
			 *
			fprintf(stdout,"\033)0");
			*/

			/* define 'ascii' as normal cset */
			fprintf(stdout,"\033(B");
			fprintf(stdout,"\033[=122l");
			fflush(stdout);
			/* define 'apl' cset as alternate cset */
			fprintf(stdout,"\033)2");
			fflush(stdout);

			cur_greek = avt_greek;
			udot_greek = avt_dgreek;
			cur_punct = avt_punct;
			lbrack_tab = avt_lbrackets;
			rbrack_tab = avt_rbrackets;
			quote_tab = avt_quotes;
			esc_tgreek = avt_tgreek;
			esc_tbgreek = avt_tbgreek;
			esc_troman = avt_troman;
			newline = avt_newline;
			fix_savefile = fix_avt_save;
			add_header = add_avt_header;
			break;	
#endif SUNTOOL
		case FILEFORMAT:
			to_window = 0; /* this is a text file */
			cur_greek = troff_greek;
			udot_greek = troff_dgreek;
			cur_punct = troff_punct;
			lbrack_tab = troff_lbrackets;
			rbrack_tab = troff_rbrackets;
			quote_tab = troff_quotes;
			esc_tgreek = troff_tgreek;
			esc_tbgreek = troff_tbgreek;
			esc_troman = troff_troman;
			newline = troff_newline;
			fix_savefile = fix_troff_save;
			add_header = add_troff_header;
			break;
#ifndef SUNTOOL
  		case INTERLEAF:
			to_window = 0; /* this is a text file */
 			cur_greek = ileaf_greek;
 			udot_greek = ileaf_dgreek;
 			cur_punct = ileaf_punct;
 			lbrack_tab = ileaf_lbrackets;
 			rbrack_tab = ileaf_rbrackets;
 			quote_tab = ileaf_quotes;
 			esc_tgreek = ileaf_tgreek;
 			esc_tbgreek = ileaf_tbgreek;
 			esc_troman = ileaf_troman;
 			newline = ileaf_newline;
			fix_savefile = fix_ileaf_save;
			add_header = add_ileaf_header;
 			break;
  		case NOTA_BENE:
			to_window = 0; /* this is a text file */
 			cur_greek = nb_greek;
 			udot_greek = nb_dgreek;
 			cur_punct = nb_punct;
 			lbrack_tab = nb_lbrackets;
 			rbrack_tab = nb_rbrackets;
 			quote_tab = nb_quotes;
 			esc_tgreek = nb_tgreek;
 			esc_tbgreek = nb_tbgreek;
 			esc_troman = nb_troman;
 			newline = nb_newline;
			fix_savefile = fix_nb_save;
			add_header = add_nb_header;
 			break;
		case SIGNIFIER:
			to_window = 0; /* this is a text file */
			cur_greek = signf_greek;
			udot_greek = signf_dgreek;
			cur_punct = signf_punct;
			lbrack_tab = signf_lbrackets;
			rbrack_tab = signf_rbrackets;
			quote_tab = signf_quotes;
			esc_tgreek = signf_tgreek;
			esc_tbgreek = signf_tbgreek;
			esc_troman = signf_troman;
			newline = signf_newline;
			fix_savefile = fix_signf_save;
			add_header = add_signf_header;
			break;
#endif SUNTOOL
#endif

#ifdef MACINTOSH
		default:
#endif
		case GREEK_KEYS:
			to_window = 0; /* this is a text file */
			cur_greek = gkkey_greek;
			udot_greek = gkkey_dgreek;
			cur_punct = gkkey_punct;
			lbrack_tab = gkkey_lbrackets;
			rbrack_tab = gkkey_rbrackets;
			quote_tab = gkkey_quotes;
			esc_tgreek = gkkey_tgreek;
			esc_tbgreek = gkkey_tbgreek;
			esc_troman = gkkey_troman;
			newline = gkkey_newline;
			fix_savefile = fix_gkkey_save;
			add_header = add_gkkey_header;
			break;
		case MS_RTF:
			to_window = 0; /* this is a text file */
			cur_greek = rtf_greek;
			udot_greek = rtf_dgreek;
			cur_punct = rtf_punct;
			lbrack_tab = rtf_lbrackets;
			rbrack_tab = rtf_rbrackets;
			quote_tab = rtf_quotes;
			esc_tgreek = rtf_tgreek;
			esc_tbgreek = rtf_tbgreek;
			esc_troman = rtf_troman;
			newline = rtf_newline;
			fix_savefile = fix_rtf_save;
			add_header = add_rtf_header;
			break;
			
#ifdef SUNTOOL
		case SUNW:
			to_window = 1;	/* this is a window */
			cur_greek = sun_greek;
			udot_greek = sun_dgreek;
			cur_punct = sun_punct;
			lbrack_tab = sun_lbrackets;
			rbrack_tab = sun_rbrackets;
			quote_tab = sun_quotes;
			esc_tgreek = sun_tgreek;
			esc_tbgreek = sun_tbgreek;
			esc_troman = sun_troman;
			newline = sun_newline;
			fix_savefile = fix_sun_save;
			add_header = add_sun_header;
			break;
#endif SUNTOOL

#ifndef MACINTOSH
		default:
			break;
#endif
	}
}

/*
 * this routine prints simple, non-Greek chars.
 * it deals with some idiosyncracies of various devices.
 */
simple_chars(s)
char *s;
{
	while( *s ) {
		/*
		 * the avt greek font, for example, has no ','.
		 * we therefore must call it up from the ascii.
		 * this ugly little switch handles such problems.
		 *
		 * ugh...
		 */
		switch(*s) {
			/*
			 * these chars must be escaped if with a '\'
			 * if we are using pseudo-TROFF transliteration.
			 * without the '\' they are treated as an
			 * accent on the preceding syllable.
			 */
			case '`':
			case '\'':
			case '<':
			case '>':
			case '|':
			case '~':
			case '+':
			case '?':
				if( cur_device != FILEFORMAT || cur_font != GREEK )
					break;
				sprintf(cur_char,"\\%c", *s );
				add_cur_char(1);
				sync_source(1);
				s++;
				continue;
			case '_':	 /* em dash */
				sprintf(cur_char,"--");
				add_non_alph(-1);
				sync_source(1);
				s++;
				continue;
#ifndef SUNTOOL
			case ':':	/* raised dot */
 				if( cur_device == INTERLEAF && cur_font == GREEK ) {
 					strcpy(cur_char,"<#1b>");
 					add_cur_char(-1);
 					sync_source();
 					s++;
 					continue;
 				}
				if( cur_device == AVT && cur_font == GREEK) {
					sprintf(cur_char,".\b;");
					add_cur_char(-1);
					sync_source(1);
					s++;
					continue;
				}
				if( cur_device == VT100 && cur_font == GREEK) {
					sprintf(cur_char, "~");
					add_cur_char(-1);
					sync_source(1);
					s++;
					continue;
				}
				break;
#endif SUNTOOL
			default:
				break;
		}
		sprintf(cur_char,"%c", *s );
		if( !isalpha( *s ) && cur_font == GREEK /* && 
			(cur_device == AVT || cur_device == VT100 ) */ ) {

			add_non_alph(1);
		} else
			add_cur_char(1);
		sync_source(1);
		s++;
	}
}

/*
 * the following routines toggle the output tables. they deal with the
 * fact that there are usually two output formats that a user will invoke:
 * the format that drives a screen and the format in which the data
 * will be saved in a file for word processing.
 * C_devpush()/C_devforce() changes the file format to "device", 
 * but saves cur_device.
 *
 * C_devpop() restores the old value of cur_device that was present
 * the last time C_devpush() was called with a new value.
 */

/*
 * this does some thinking about what terminal you are on and decides 
 * automatically what output format you want. this is now generally
 * superseded by C_devforce().
 */
C_devpush(device,outf)
int device;
FILE * outf;
{
	fout = outf;
	if( cur_device == device ) 
		return;
	prev_device = cur_device;
 
	if( troff_flag ){
		cur_device = FILEFORMAT;
		troff_flag = 0;
	} else if( greek_keys && device == FILEFORMAT ) {
		cur_device = GREEK_KEYS;
	} else
	  	cur_device = device;
	init_char_tabs(cur_device);
}

C_devforce(device,outf)
int device;
FILE * outf;
{
	fout = outf;
	if( cur_device == device ) 
		return;
	prev_device = cur_device;
	cur_device = device;
	init_char_tabs(cur_device);
}

C_devpop(fname)
char * fname;
{
	fflush(fout);
	fout = stdout;
	fix_savefile(fname);
	cur_device = prev_device;
	init_char_tabs(cur_device);
}

/*
 * this routine handles european accents and is not so elegantly table
 * driven. escape sequences above %19 tend to be european handling and
 * require special handling on some output devices.
 *
 * european accents can be ignored by most people, at least 
 * initially, as 99% of the TLG is Greek.
 * however ....
 */
#define MAX_PUNCT 20
tlg_punct()
{
	int n;

	if( ret <= 0 ) 
		my_trim( text_buf );
	dump_bufs();

	n = atoi(Cp+1);
	skip_num_arg();

	if( n < MAX_PUNCT  ) {
	 	strcpy(cur_char, cur_punct[n] );
	} else {
	    switch( n ) {
/*
 * the logic of this is simple (if dubious). FILEFORMAT simply defines
 * a european accent as an escape (for the accent) followed by *any* char.
 *
 *   e.g. \*ua \*uu \*uo are umlauts over 'a', 'u' and 'o' respectively.
 * a \*ur would put an umlaut on top of an 'r'.
 *
 *   the AVT format (like most formats) has a separate escape sequence for
 * o umlaut, a umlaut, u umlaut etc. you cannot express umlaut on top of an
 * 'r' in the AVT.
 */
		case 20:
			if( cur_device == FILEFORMAT )
				sprintf(cur_char,"\\*a%c", *Cp++ );
			if( cur_device == AVT ) {
			    switch( *Cp++ ) {
				case 'a':
				    sprintf(cur_char,"\016\033Q\7\033R\b'\017");
				    break;
				case 'e':
				    sprintf(cur_char,"\016e\b'\017");
				    break;
				default:
				    sprintf(cur_char,"%%20%c", *(Cp-1) );
				    break;
			    }
			} else /* give up and spit out the beta code you saw */
				    sprintf(cur_char,"%%20%c", *(Cp-1) );
			break;
		case 21:
/* follow same pattern as above, for following drops in the switch */
			if( cur_device == FILEFORMAT )
				sprintf(cur_char,"\\*g%c", *Cp++ );
			if( cur_device == AVT ) {
			     switch( *Cp++ ) {
				case 'a':
				     sprintf(cur_char,"\016A\b`\017");
				     break;
				case 'e':
				     sprintf(cur_char,"\016e\b`\017");
				     break;
				default:
				     sprintf(cur_char,"%%21%c", *(Cp-1) );
				     break;
			    }
			} else
				    sprintf(cur_char,"%%21%c", *(Cp-1) );
			break;
		case 22:
/* french circumflex */
			if( cur_device == FILEFORMAT ) 
				strcpy(cur_char,"\\*^");
			if( cur_device == AVT ) {
				if( *Cp == 'e' )
					sprintf(cur_char,"\016e\b>\017");
				else {	
				    sprintf(cur_char,"%%22%c", *Cp++);
				}
			} else
				    sprintf(cur_char,"%%22%c", *(Cp-1) );
			break;
		case 23:
/* umlauts */
			if( cur_device == FILEFORMAT )
				sprintf(cur_char,"\\*u%c", *Cp++ );
			if( cur_device == AVT ) {
			     switch( *Cp++ ) {
				case 'a':
				     sprintf(cur_char,"\016\033Q\7\033R\b!\017");
				     break;
				case 'o':
				     sprintf(cur_char,"\016o\b!\017");
				     break;
				case 'u':
				     sprintf(cur_char,"\016\033Q\010\033R\b!\017");
				     break;
				default:
				     sprintf(cur_char,"%%23%c", *(Cp-1) );
				     break;
			    }
			} else
				    sprintf(cur_char,"%%23%c", *(Cp-1) );
			break;
		case 24:
/* the hell with "~" on an n etc., for now at any rate */
		 	strcpy(cur_char,"~");
			break;
		case 25:
/* c cedila */
			if( cur_device == FILEFORMAT )
				sprintf(cur_char,"\\*c%c", *Cp++ );
			if( cur_device == AVT ) {
			     switch( *Cp++ ) {
				case 'c':
				     sprintf(cur_char,"\016.\bL\017");
				     break;
				default:
				     sprintf(cur_char,"%%25%c", *(Cp-1) );
				     break;
			    }
			} else
				    sprintf(cur_char,"%%25%c", *(Cp-1) );
			break;
		default:
			cur_char[0] = 0;
			break;
	    }
	}
		
	add_non_alph(-1);
	sync_source(cur_len);

}

/*
 * add non alphabetic char -- switch out of greek font if necessary
 *
 * this routine should deals with the fact that your current font (e.g.
 * Greek), may not have room for all normal ascii chars. you may have to
 * go back to ascii to print a '.' or similar char. 
 *
 * this routine also switches off bolding/reverse video if this is set.
 * we do this, because bolding should only appear on a single word in
 * the current scheme of things--its purpose is to outline a word that
 * the search routine has found so that this word will stand out in a
 * window of greek.
 */

add_non_alph(len)
int len;
{
	
	if( cur_font == GREEK && in_rev_vid ) {
		char tmp[128];
		strcpy( tmp , cur_char );
		cur_char[0] = 0;
		in_rev_vid = 0;
		to_greek();
		strcpy( cur_char , tmp );
	}

#ifndef SUNTOOL
	if( (cur_device == AVT || cur_device == VT100) && cur_font == GREEK ) {
		char tmp[256];	

	/* don't do anything if the first char is already control char */
		if( cur_char[0] > ' ' ) {
			strcpy(tmp,cur_char);
			to_roman();
			strcpy(cur_char,tmp);
			add_cur_char(len);
			to_greek();
/*
			if( cur_device == VT100 )
				sprintf(cur_char, "\033[m%s\033[0;1m" , tmp );
			else
				sprintf(cur_char,"\17%s\16", tmp );
*/
			return;
		}
	}
#endif SUNTOOL

	add_cur_char(len);
}

/* 
 * NOTE !!!
 * END OF ROUTINES THAT NEED TO BE MODIFIED WHEN ADDING NEW FORMATS
 */

def_startup()
{
	gk_startup(FILEFORMAT);
}

gk_sprint(line,print_flag)
char *line;
int print_flag;
{
	int has_newline = 0;
	char *s;

	cur_char[0] = gk_lbuf[0] = 0;
	in_rev_vid = 0;
	screen_pos = 1;
	read_chars = 0;

	if( cur_device == BETAFORMAT ) {
		if( print_flag ) {
			fprintf(fout,"%s", line );
			return(0);
		}
		strcpy(gk_lbuf , line );
		return( strlen(gk_lbuf) );
	}
	strcpy(source_buf,line);
	s = source_buf;
	if( *s == '~' ) {
/*
if( line[ strlen( line ) - 1 ] == '\n'  ) {
	line[ strlen( line ) - 1 ] = 0;
	has_newline++;
}
*/
		if( * ( s + strlen(s) - 1) == '\n' ) {
			my_trim(s);
			has_newline++;
		}
		to_roman();
		if( print_flag ) {
			fprintf(fout,"%s", s+1 );
			if( has_newline ) {
/*
fprintf(fout,"%s", newline );
*/
				fprintf(fout,"%s",newline);
			}
			return(0);
		} else {
			strcpy( gk_lbuf , s+1 );
			return( strlen(gk_lbuf) );
		}
	}
	if( * ( s + strlen(s) - 1) == '\n' ) {
		my_trim(s);
		has_newline++;
	}
	to_greek();
	filt_line(s);
	to_roman();

	if( has_newline ) {
		add_newline();
/*
		sprintf(cur_char,newline);
*/
		add_cur_char(0);
	}
	if( print_flag )
		fprintf(fout,"%s", gk_lbuf);
	lastlen = screen_pos;
	rev_vid_point = -1;
	return( screen_pos - 1);
}

add_newline()
{
	if (newline) 
		sprintf( cur_char , "%s", newline  );
	else
		sprintf( cur_char , "\n" );
	add_cur_char(0);
}

fadd_newline(f)
FILE * f;
{
	if( newline )
		fprintf(f,"%s", newline );
	else
		fputc('\n' , f);
}


char *
get_gk_pr_line()
{
	return( gk_lbuf );
}

gk_free()
{
	tkdestroy(Tree);
}

/*
 * if len is < 0, then the width of the cur_char is Strlen( cur_char ).
 * otherwise, len passes the length of printing positions that cur_char will
 * take up.
 */

add_cur_char(len)
int len;
{
	int i;

	if( len < 0 )
		len = Strlen( cur_char );

	/*
	 * fill in current position in source line for all columns that
	 * cur_char will fill on the screen
	 */

	strcat( gk_lbuf , cur_char );

/*
printf("col %d len %d cur_char [%s] linked to %d [%s]\n", 
	screen_pos , len , cur_char, read_chars , (source_line + read_chars) );
*/
	for(i=screen_pos;i<screen_pos+len;i++) {
/*
printf("%d ", i );
*/
		pos_in_source[i] = read_chars;
	}
/*
printf("\n");
*/
	pos_in_source[i] = -1;
	if( read_chars >= rev_vid_point - 1 && rev_vid_point >= 0 ) {
			rev_vid_point = -1;
			in_rev_vid = 1;
			to_bold_greek();
	}
	screen_pos += len;
	cur_char[0] = 0;
}

sync_source(len)
int len;
{
	read_chars += len;
}

Strlen(s)
register char * s;
{
	int n = 0;

	while(*s) {
		/* "\\" prints as a single char */
		if( *s == '\\' && *(s+1) == '\\' )
			s++;
		/* a backspace trashes the last char and has no width */
		if( *s == '\b' ) {
			n--;
			s++;
			continue;
		}
		/* "%%" prints as a single char '%' */
		if( *s == '%' && *(s+1) == '%' ) {
			n++;
			s++;
			continue;
		}
		/* look for \033[ARGSm */
		if( *s == 033 && *(s+1) == '[' ) {
			while( !isalpha( *s ) ) 
				s++;
			s++;
			continue;
		}
		/* control chars do not print */
		if( *s < ' ' ) {
			s++;
			continue;
		}
	
		n++;
		s++;
	}
	return( n );
}



/*
 * this module takes care of underline dots.
 *
 * in an edition of a fragmentary text, such as a papyrus, the underline dot
 * indicates that the given letter is a reconstruction because the text is
 * damaged.
 *
 * it may be combined with any combination of character and accent--except
 *	iota subscripts. in case of an underline dot, the iota adscript is
 *	used.
 */
greek_char(index)
int index;
{
/*
 * there are two beta code templates for chars with underline dots:
 *
 *    "*ACC?CHAR"	e.g.  	"*?p" for capital pi with underline dot
 *			or	"*)/?a" for capital alpha with uderline dot
 *					and smooth acute
 *
 *    "<CHAR><ACC>?"    e.g.	"a)/?" for alpha with smooth acute and underdot
 *
 */

	/*
	 * if font not GREEK, just dump the matched chars
	 */

	if( cur_font != GREEK ) {
		simple_chars(beta_tab[match_val-1].look_for);
		return;
	}
	if( has_udot( match_buf ) ) 
		new_greek_char( udot_greek , index  );
	else if( index == ELLIPSIS ) 
		new_greek_char( udot_greek , index  );
	else
		new_greek_char( cur_greek , index  );
	add_cur_char(-1);
	sync_source(cur_len);
}

new_greek_char( tab , ind )
char ** tab;
int ind;
{
	/*
	 * kludge to determine whether to use medial or terminal sigma
	 * when using Greek Keys (which seems not to have a lunate sigma).
	 */
	if( (cur_device == GREEK_KEYS || cur_device == SIGNIFIER || cur_device == MS_RTF) && ind == sigma ) {
		if( end_of_word( Cp )  )
			ind = tsigma;
	}

	sprintf(cur_char,"%s", tab[ind]  );
}

end_of_word( s )
char * s;
{
	/* if not followed by an alphabetic char or a hyphen,
	  	assume terminal sigma
	   NOTE THIS WON'T WORK WHERE PART OF A WORD IS SUPPLEMENTED
	   AND A > OR < BREAKS THE WORD. MUST BE OTHER SUCH BUGS
	*/
	if( !isalpha( *s ) && *s != '-' && *s != '\'' )
		return( 1 );
	else
		return( 0 );
}

/* 
 * look for a pattern with upper case marker ('*') and underline dot ('?')
 */
has_udot(s)
char *s;
{

	if( ! my_index(s,'?') )
		return( 0 );
	return(1);
}
my_index(s,c)
char *s;
int c;
{
	while(*s) {
		if( *s == c ) 
			return(1);
		s++;
	}
	return(0);
}


/*
 * show greek in inverse video on tty or emboldened on printer
 */

to_bold_greek()
{
	sprintf(cur_char, esc_tbgreek );
	add_cur_char(0);
	cur_font = GREEK;
}

to_greek()
{
	strcpy(cur_char, esc_tgreek );
	add_cur_char(0);
	cur_font = GREEK;
}


to_roman()
{
	strcpy(cur_char, esc_troman );
	add_cur_char(0);
	cur_font = ROMAN;
}

my_trim(s)
char *s;
{
	while(*s) s++;
	s--;
	*s = 0;
}

greek_font()
{
	int n;

	if( ret <= 0 ) 
		my_trim( text_buf );
	dump_bufs();

	n = atoi(Cp+1);

	to_greek();
	skip_num_arg();
	sync_source(cur_len);

}

roman_font()
{
	if( ret <= 0 ) 
		my_trim( text_buf );
	dump_bufs();
	to_roman();
	skip_num_arg();
	sync_source(cur_len);

}

/*
 * just skip these escape sequences for now 
 */
angle_brack_escapes()
{
	if( ret <= 0 )
		my_trim( text_buf );
	dump_bufs();
	skip_num_arg();
	sync_source(cur_len);
}

non_text_markers()
{
	if( ret <= 0 )
		my_trim( text_buf );
	dump_bufs();
	skip_num_arg();
	sync_source(cur_len);
}

text_symbol()
{
	if( ret <= 0 )
		my_trim( text_buf );
	dump_bufs();
	sprintf(cur_char," "); /* just print a blank space */
	add_cur_char(-1);
	skip_num_arg();
	sync_source(cur_len);
}

tab_nquarter_spaces()
{
	int len;
	int i;

	if( ret <= 0 )
		my_trim( text_buf );
	dump_bufs();
	
	len = atoi( Cp + 1) / 4;

/* "len" refers to the *absolute* position vis-a-vis the left margin */
	skip_num_arg();
	sync_source(cur_len);

	for(i=screen_pos;i<len;i++) {
		sprintf(cur_char," ");
		add_cur_char(1);
	}
	
}

skip_num_arg()
{
/*
 * *Cp is pointing to first char of escape sequence 
 */
	if( ! isdigit( * Cp ) )
		Cp++;

/*
 * now skip the optional numeric argument
 * also keep track of cur_len: assume cur_len = 1 Byte esc seq + digits
 */
	cur_len = 1;
	while( isdigit(*Cp) ) {
		cur_len++;
		Cp++;
	}
	/* start off the automaton with a clean slate */
	tkreset(Tree);
}


filt_line(s)
char * s;
{
	
	Cp = s;
	tkreset(Tree);
	text_buf[0] = match_buf[0] = 0;
	match_val = 0;

	while ( *Cp!=NUL )  {
		ret = tkparse( Tree, *Cp);
		ret_val_is(*Cp,ret);

/* if *Cp is last char after a patt and also first char of a new patt,
	it has to go through twice */
		if( ret >  0 ) {
			text_buf[0] = 0;
			tkreset(Tree);
		}
/* look for various Beta code escape sequences here */
		switch( *Cp ) {
			case '$':
				greek_font();
				continue;
			case '&':
				roman_font();
				continue;
			case '@':
				tlg_page_formats();
				continue;
			case '<':
			case '>':
				angle_brack_escapes();
				continue;
			case '{':
			case '}':
				non_text_markers();
				continue;
			case '^':
				tab_nquarter_spaces();
				continue;
			case '#':
				text_symbol();
				continue;
			case '\"':
				tlg_quote();
				continue;
			case '[':
			case ']':
				tlg_brackets();
				continue;
			case '%':
				tlg_punct();
				continue;
			case '\n':
				Cp++;
				break;
			default:
				break;
		}
		if( ret <= 0 ) {
			Cp++;
		}
	}

	if( ! ( ret > 0 ) ) {
		ret = tkflush(Tree);
		ret_val_is(0,ret);
	} else {
		dump_bufs();
	}
}

dump_bufs()
{
	exec_match();
	dump_text_buf();
}

dump_text_buf()
{
	if( text_buf[0] ) {
		simple_chars( text_buf );
	}
	text_buf[0] = 0;
}

ret_val_is(ch,rval)
int ch;
int rval;
{
	
		if( rval > 0 ) {
			got_match( rval , ch );
		} else switch( rval ) {
			case PENDING:
				pend_buf(ch);
				break;
			default:
				break;
		}
}

pend_buf(c)
int c;
{
	char * p;

	/* release matched chars */

	exec_match();

	if( c == 0 ) {
		dump_text_buf();
		return;
	}

	p = text_buf;
	while( *p ) 
		p++;
	*p++ = c; *p = 0;
}


got_match(val,curc)
int val;
int curc;
{
	strcpy( match_buf , text_buf );
	match_val = val;

	if( curc == 0 ) {
		exec_match();
		return;
	}

}

exec_match()
{
	int len;
	int i;
	char * a;
	char firsthalf[256];


	if( ! match_buf[0] )
		return;
	firsthalf[0] = 0;

	/* split the match buffer into the part that represents the match
		and the part that precedes the match */
	a = firsthalf;
	cur_len = strlen(beta_tab[match_val-1].look_for );
	len = strlen(match_buf) - cur_len;

	for(i=0;i<len;i++) {
		*a++ = match_buf[i];
	}
	*a = 0;
	simple_chars(firsthalf);
	greek_char( beta_tab[match_val-1].act_arg );
	match_buf[0] = 0;

}


init_table(tab_ptr,len)
filt_tab * tab_ptr;
int len;
{
	int sval = 0;
/* vjh 9/87 *** don't have to copy the beta code strings, tab_ptr->look_for
	char *tline;
	char *malloc();
*/
	int i;

/*
	fprintf(stderr,"sizeof beta_tab %d %d\n", beta_size( ),
		beta_length()  );
*/

	for(i=0;i<len;i++) {
		    sval++;
/*
		    tline = malloc( strlen(tab_ptr->look_for) + 1);
		    strcpy( tline, tab_ptr->look_for);
*/
		    keys[sval] = tab_ptr->look_for;
		    if ( tkenter( Tree, tab_ptr->look_for, sval ) == FAILURE )
			printf("Can't enter %s\n", tab_ptr->look_for);
#ifdef TEST
		    else printf("Entered %s\n", tab_ptr->look_for);
#endif
		tab_ptr++;
	}
	if ( tkcompile( Tree ) == FAILURE )  {
	    printf("could not compile Tree\n");
	    exit( -1 );
	}
#ifdef TEST
	printf("done\n");
#endif
}



long
C_getp(pos, s)
int pos;
char *s;
{
	gk_sprint(s , 0 );

	return( pos_in_source[pos] + 1 );
}

#define MAX_QUOTE 7
tlg_quote()
{
	int n;

	if( ret <= 0 ) 
		my_trim( text_buf );
	dump_bufs();

	n = atoi(Cp+1);

	
	/* if number is above MAX_QUOTE, simply print "default" bracket */
	if( n < MAX_QUOTE )
		strcpy( cur_char , *(quote_tab + n) );
	else
		strcpy( cur_char , *quote_tab );
	
	add_non_alph(-1);
	skip_num_arg();
	sync_source(cur_len);
}

#define MAX_BRACKET 6
tlg_brackets()
{
	int n;
	char ** brack_tab;

	if( ret <= 0 ) 
		my_trim( text_buf );
	dump_bufs();

	n = atoi(Cp+1);
	if( *Cp == '[' )
		brack_tab = lbrack_tab;
	else
		brack_tab = rbrack_tab;
	/* if number is above MAX_BRACKET, simply print "default" bracket */
	if( n < MAX_BRACKET )
		strcpy( cur_char , *(brack_tab + n) );
	else
		strcpy( cur_char , *brack_tab );
	
	add_non_alph(-1);
	skip_num_arg();
	sync_source(cur_len);
}

/* Beta Page formats -- only some actually used here */

tlg_page_formats()
{
	int n;
	int i;

	n = atoi(Cp+1);
	
	if( ret <= 0 ) 
		my_trim( text_buf );
	dump_bufs();

	cur_char[0] = 0;
	switch( n ) {
		case 0:	/* indentation marker */
		 	strcat(cur_char,"   "); /* three spaces */
			break;
		case 1: /* end of page in source doc */
			break;
		case 2: /* end  of column marker */
			break;
		case 3: /* graph or chart follows */
			break;
		case 4: /* tabular info follows */
			break;
		case 5: /* tabular info ends */
			break;
		case 6: /* blank line in source doc */
			break;
		case 7: /* draw a horizontal line across page */
			break;
		case 8: /* new reference starts in mid-line */
			for(i=0;i<lastlen;i++)
				strcat(cur_char, " " );
			break;
		default:
			break;
	}		
	add_cur_char(-1);
	skip_num_arg();
	sync_source(cur_len);
}


/*
 * the kludge machine rolls on....
 *
 * sets an index in the beta code source array where highlighting should
 * be turned on. allows search strings to be highlighted on the screen.
 *
 * this sets mark_point to an index.
 * add_cur_char() keeps track of how many ascii chars have been processed
 * from the line of beta source code.
 *
 * when this number is greater than or equal to mark_point, the escape
 * sequence for showing highlighted greek is added to the output string.
 * a flag is also set that indicates that we are now showing highlighted
 * greek.
 *
 * add_non_alph() checks to see if we are in inverse video. if so, it inserts
 * the escape sequence to get out of inverse video into the output string.
 */
addmark(n)
int n;
{
	rev_vid_point = n;
}
gk_add_header(fname)
char * fname;
{
	add_header(fname);
}
