#define LOGFILE 0
#define PROFILE 0
#define FILTERS 1
/*
	DumbEdit - Multiple-window TransEdit Demonstration.

	The project should include DumbEdit.c (this file), TransEdit.c,
	FakeAlert.c, TransSkel.c (or a project made from TransSkel.c)
	and MacTraps.

	28 October 1986		Paul DuBois
*/
#include <stdio.h>
#include <strings.h>
#include <dialect.h>
#include <prntflags.h>

# include	<MenuMgr.h>
# include	<FontMgr.h>
# include   <SegmentLdr.h>
# include	"TransEdit.h"


# define	locmaxSize		8		/* no. font sizes made available */
/*# define	hSize		300		/* horiz, vert size of new windows */
/* horizontal size increased so that the default window will show
 * 80 column lines easily -- grc 6/27/87 */
# define	hSize		400		/* horiz, vert size of new windows */
# define	vSize		205
# define	aboutAlrt	1000

static int is_dumpform = 0;
extern int Use_hqdict;

typedef enum		/* File menu item numbers */
{
	new = 1,		/* begin new window */
	open,			/* open existing file */
	close,			/* close file */
	/* --- */
	save = 5,		/* save file */
	saveAs,			/* save under another name */
	saveCopy,		/* save a copy w/o switching file binding */
	revert,			/* revert to version on disk */
	/* --- */
	quit = 10,
	dumpform
};


typedef enum			/* Edit menu item numbers */
{
	undo = 1,
	/* --- */
	cut = 3,
	copy,
	paste,
	clear
};



typedef enum		/* Format menu item numbers */
{
	wordWrap = 1,
	noWrap,
	/* --- */
	leftJust = 4,
	centerJust,
	rightJust
};

typedef enum		/* Dictionary menu item numbers */
{
	AnalSelection = 1,
	AnalDocument,
	AnalClipboard,
	/* --- */
	AnyDialect = 5,
	Attic,
	Ionic,
	Doric,
	Epic,
	Aeolic,
	Prose,
	Paradigm,
	/* --- */
	QuickSearch = 14
	/* CheckPreverb grc 6/7/88 */
};


typedef enum 	/* various filter options */
{
	Beta2Smarta = 1,
	Beta2SMK
};

int quickflag = 0;
PrntFlags prntflags/* = CHECK_PREVERB grc 6/7/88 */;
Dialect GetWindowDialect(), GetWantDialect();

typedef struct {
	WindowPtr  aWindowPtr;
	Dialect    WindowDialect;
} DialectMap;

#define MAXGKWINDOWS 16

#include "MorphWind.proto.h"
DialectMap dial_map[MAXGKWINDOWS];

WindowPtr	lastFront = nil;	/* keeps track of front window */
WindowPtr	ErrWindow = nil;
WindowPtr DictWindow;
char ErrMess[256];
MenuHandle	fileMenu;
MenuHandle	editMenu;
MenuHandle	fontMenu;
MenuHandle	sizeMenu;
MenuHandle	formatMenu;

/* beginning of mods */
MenuHandle	dictMenu;
MenuHandle	filtMenu;
int smarta_font;
/* end of mods */

int		sizes[locmaxSize] = { 9, 10, 12, 14, 18, 20, 24, 48 };


/*
	Uncheck all the items in a menu
*/

UncheckMenu (MenuHandle theMenu)
{
register int	i, nItems;

	nItems = CountMItems (theMenu);

	for (i = 1; i <= nItems; ++i)
	{
		CheckItem (theMenu, i, false);
		SetItemStyle (theMenu, i, 0);
	}
}


/*
	Set the Font, Size and Format menus so that the items corresponding
	to the text characteristics of the window are checked.  If the
	window isn't an edit window, dim all three menus.
*/

SetTextMenus (Boolean drawBar)
{
WindowPtr	theWind;
Str255		wFontName;
Str255		mFontName;
register int	i, nItems;
register TEHandle	te;

	theWind = FrontWindow ();
	UncheckMenu (fontMenu);				/* toss current check marks */
	UncheckMenu (sizeMenu);
	UncheckMenu (formatMenu);
	UncheckMenu (dictMenu);
	UncheckMenu (filtMenu);

	if (!IsEWindow (theWind))			/* disable the menus */
	{
		DisableItem (fontMenu, 0);
		DisableItem (sizeMenu, 0);
		DisableItem (formatMenu, 0);
		DisableItem (dictMenu, 0);
		DisableItem (filtMenu, 0);
	}
	else
	{
		EnableItem (fontMenu, 0);
		EnableItem (sizeMenu, 0);
		EnableItem (formatMenu, 0);
		EnableItem (dictMenu, 0);
		EnableItem (filtMenu, 0);

		te = GetEWindowTE (theWind);

/*
	Check appropriate word wrap item
*/

		CheckItem (formatMenu, (**te).crOnly < 0 ? noWrap : wordWrap, true);

/*
	Check appropriate justification item
*/

		switch ((**te).just)
		{

		case teJustLeft:
			CheckItem (formatMenu, leftJust, true);
			break;

		case teJustRight:
			CheckItem (formatMenu, rightJust, true);
			break;

		case teJustCenter:
			CheckItem (formatMenu, centerJust, true);
			break;

		}

/*
	Check appropriate font size item, and outline items for sizes
	present in resource files
*/

		for (i = 0; i < locmaxSize; ++i)
		{
			if ((**te).txSize == sizes[i])
				CheckItem (sizeMenu, i + 1, true);

			if (RealFont ((**te).txFont, sizes[i]))
				SetItemStyle (sizeMenu, i + 1, outline);
			else
				SetItemStyle (sizeMenu, i + 1, 0);		/* plain */
		}

/*
	Check appropriate font name item
*/
		
		GetFontName ((**te).txFont, wFontName);	/* name of window font */
		nItems = CountMItems (fontMenu);		/* # fonts in menu */
		for (i = 1; i <= nItems; ++i)
		{
			GetItem (fontMenu, i, mFontName);	/* get font name */
			if (EqualString (wFontName, mFontName, false, true))
			{
				CheckItem (fontMenu, i, true);
				break;
			}
		}

	}

	if (drawBar)
		DrawMenuBar ();
}



/*
	Set File/Edit menu items according to type of front window.

	The general behavior is:

	New and Open always enabled, since a new edit window can always be
	opened.

	Close enabled when an edit or DA window in front (i.e., when there's
	a window at all).

	Save enabled for edit windows not bound to a file, and edit windows
	bound to a file when they're dirty (typed into, Edit menu used to
	do something to them).

	Save As and Save a Copy As enabled for edit windows.

	Revert enabled for edit windows bound to a file when they're dirty.

	Undo disabled when there's an edit window in front.
*/

SetNonTextMenus (void)
{
WindowPtr	theWind;
int			theKind;

	DisableItem (fileMenu, close);	/* assume no window at all */
	DisableItem (fileMenu, save);
	DisableItem (fileMenu, saveAs);
	DisableItem (fileMenu, saveCopy);
	DisableItem (fileMenu, revert);
	EnableItem (editMenu, undo);

	theKind = 0;
	if ((theWind = FrontWindow ()) != nil)
		theKind = ((WindowPeek) theWind)->windowKind;

	if (theKind < 0)						/* DA in front */
	{
		EnableItem (fileMenu, close);
	}
	else if (IsEWindow (theWind))			/* edit window in front */
	{
		EnableItem (fileMenu, close);
		EnableItem (fileMenu, saveAs);
		EnableItem (fileMenu, saveCopy);
		if (GetEWindowFile (theWind, nil) == false)	/* not bound to file */
		{
			EnableItem (fileMenu, save);
		}
		else if (IsEWindowDirty (theWind))	/* bound - is it dirty? */
		{
			EnableItem (fileMenu, save);
			EnableItem (fileMenu, revert);
		}
		DisableItem (editMenu, undo);
	}
}


/*
	Got an activate or deactivate.  It doesn't matter which, really.
	Set the text menus appropriately for the front window, and draw
	the menu bar, as these menus might change state from enabled to
	disabled or vice-versa.
*/

Activate (Boolean active)
{
	CheckFront ();
}


/*
	Got a keyclick in an edit window.
*/

Key (void)
{
	SetNonTextMenus ();
}


/*
	Close selected from File menu, or close box of edit window
	clicked.
*/

Close (void)
{
WindowPtr	theWind;

	GetPort (&theWind);
	if( theWind == DictWindow ) {
		(void) EWindowClose (theWind);
		DictWindow = NULL;
	}
	else 
		(void) EWindowClose (theWind);
	CheckFront ();
}


MakeWind (Boolean bindToFile, StringPtr title, AppFile *theFile)
{
Rect		r;
static int	windCount = 0;
int			offset;
WindowPtr	theWind;
char		theFontName[256];
int			font;
Ptr			CtoPstr();

	if (FrontWindow () == nil)
		windCount = 0;
	
	SetRect (&r, 0, 0, hSize, vSize);
	offset = 50 + 25 * (windCount++ % 4);
	OffsetRect (&r, offset, offset);
	Xstrncpy(theFontName,"Sparta"	,sizeof theFontName);
	(char *) CtoPstr(theFontName);
	GetFNum (theFontName, &font);
	SetEWindowStyle (nil, font, 10, 0, teJustLeft);
	(void) NewEWindow (&r, title, true, -1L, true, 0L, bindToFile , theFile);
	SetWindowDialect(FrontWindow(),(Dialect)(ATTIC|PROSE));

}

MakeDWindow (Boolean bindToFile)
{
Rect		r;
static int windCount = 0;
int			offset;
	if (FrontWindow () == nil)
		windCount = 0;

	SetRect (&r, 0, 0, hSize, vSize);
	offset = 50 + 25 * (windCount++ % 4);
	OffsetRect (&r, offset, offset);
/*	ErrWindow = */ NewDWindow (&r, nil, true, -1L, true, 0L);
}

/*
	File menu handler
*/

DoFileMenu (int item)
{
WindowPtr	theWind;

	theWind = FrontWindow ();
	switch (item)
	{

	case new:
		MakeWind (false,nil,nil);
		break;

	case open:
		MakeWind (true,nil,nil);
		break;

	case close:
		if (IsEWindow (theWind))
			Close();
			/*(void) EWindowClose (theWind);*/
		else
			CloseDeskAcc (((WindowPeek) theWind)->windowKind);	/* DA in front */
		break;

	case save:
		(void) EWindowSave (theWind);
		break;

	case saveAs:
		(void) EWindowSaveAs (theWind);
		break;

	case saveCopy:
		(void) EWindowSaveCopy (theWind);
		break;

	case revert:
		(void) EWindowRevert (theWind);
		break;

	case quit:
		if (ClobberEWindows () == true)
			SkelWhoa ();
		break;
case dumpform:
	if( is_dumpform == 0 ) {
	CheckItem(dictMenu,dumpform,is_dumpform ? true : false );
		is_dumpform = 1;
	} else {
		is_dumpform = 0;
	}
		break;
	}
	SetNonTextMenus ();

}


/*
	Handle Font menu items
*/

DoFontMenu (int item)
{
int			font;
TEHandle	te;
WindowPtr	theWind;
Str255		theFontName;

	theWind = FrontWindow ();
	if ((te = GetEWindowTE (theWind)) == nil)
		return;				/* not an edit window */
	GetItem (fontMenu, item, theFontName);
	GetFNum (theFontName, &font);
	SetEWindowStyle (theWind, font, (**te).txSize, (**te).crOnly, (**te).just);
	SetTextMenus (false);

}


/*
	Handle Size menu items
*/

DoSizeMenu (int item)
{
TEHandle	te;
WindowPtr	theWind;

	theWind = FrontWindow ();
	if ((te = GetEWindowTE (theWind)) == nil)
		return;				/* not an edit window */
	SetEWindowStyle (theWind, (**te).txFont, sizes[item-1], (**te).crOnly, (**te).just);
	SetTextMenus (false);
}


/*
	Handle Format menu items
*/

DoFormatMenu (int item)
{
int			font, size, just, wrap;
TEHandle	te;
WindowPtr	theWind;

	theWind = FrontWindow ();
	if ((te = GetEWindowTE (theWind)) == nil)
		return;				/* not an edit window */
	font = (**te).txFont;
	size = (**te).txSize;
	just = (**te).just;
	wrap = (**te).crOnly;

	switch (item)
	{

	case wordWrap:
		wrap = 0;
		break;

	case noWrap:
		wrap = -1;
		break;

	case leftJust:
		just = teJustLeft;
		break;

	case centerJust:
		just = teJustCenter;
		break;

	case rightJust:
		just = teJustRight;
		break;
	}
	SetEWindowStyle (theWind, font, size, wrap, just);
	SetTextMenus (false);
}

#if LOGFILE
FILE * flog = NULL;
#endif

DoFiltMenu (int item)
{
TEHandle	te;
WindowPtr	theWind;
char * locbuf = NULL;
char * smkbuf = NULL;
char  *malloc();
int len;

	theWind = FrontWindow ();
	if ((te = GetEWindowTE (theWind)) == nil)
		return;				/* not an edit window */	


	switch(item) {
		case Beta2Smarta:
			len = (**te).teLength;
			locbuf = malloc(len+1);
			smkbuf = malloc(len+1);
			
			strncpy(locbuf,*(TEGetText(te)),len);
			locbuf[len] = 0;
			GetDictWindow();
			te = GetEWindowTE (DictWindow);
			beta2smarta(locbuf,smkbuf);
			TEInsert(smkbuf,(long)strlen(smkbuf),te);
			xFree(locbuf,"locbuf");
			xFree(smkbuf,"smkbuf");
			locbuf = smkbuf = NULL;
			return;
		case Beta2SMK:
			len = (**te).teLength;
			locbuf = malloc(len+1);
			smkbuf = malloc(len+1);
			
			strncpy(locbuf,*(TEGetText(te)),len);
			locbuf[len] = 0;
			GetDictWindow();
			te = GetEWindowTE (DictWindow);
			beta2smk(locbuf,smkbuf);
			TEInsert(smkbuf,(long)strlen(smkbuf),te);
			xFree(locbuf,"locbuf");
			xFree(smkbuf,"smkbuf");
			locbuf = smkbuf = NULL;
			return;
		default:
			return;
	}
}

DoDictMenu (int item)
{
int			font, size, just, wrap;
TEHandle	te;
WindowPtr	theWind;
char * locbuf = NULL;
char  * smkbuf = NULL;
char * malloc();
char * NextGkWord();
char betastring[128];
char * bp = NULL;
char * anal_buf();
long off = 0;
int sa, sb;
int len;
int nwords = 0;
int nhits = 0;
char tmp[128];
Ptr CtoPstr();
char * strncpy();
char * curp;
Handle hdest;


	theWind = FrontWindow ();
	if ((te = GetEWindowTE (theWind)) == nil)
		return;				/* not an edit window */	

	switch (item)
	{

		case AnalSelection:

			sa = (**te).selStart;
			sb = (**te).selEnd;
			len = sb - sa;
			locbuf = malloc(len+1);	
			GetSelection(locbuf,te,len);
			locbuf[len] = 0;
			break;
			
		case AnalDocument:
			len = (**te).teLength;
			locbuf = malloc(len+1);
			strncpy(locbuf,*(TEGetText(te)),len);
			locbuf[len] = 0;
			break;
			
		case AnalClipboard:
			hdest = NewHandle(0);
			len = (int) GetScrap(hdest,'TEXT',&off);
			locbuf = malloc(len+1);
			strncpy(locbuf,*hdest,len);
			locbuf[len] = 0;
			break;
			
		case AnyDialect:
		case Attic:
		case Ionic:
		case Doric:
		case Epic:
		case Aeolic:
		case Prose:
		case Paradigm:
			SetNewDialect(item);
			return;
		case QuickSearch:
			toggle_quickflag();
			return;
/* grc 6/6/88
		case CheckPreverb:
			toggle_checkpreverb();
			return;
*/
		default:
			return;
	}

	GetDictWindow();

	te = GetEWindowTE (DictWindow);

/*	(**te).txFont = monaco;*/
	if( smarta_font == 0 ){
		char theFontName[256];
		
		Xstrncpy(theFontName,"Smarta"	,sizeof theFontName);
		CtoPstr(theFontName);
		GetFNum (theFontName, &smarta_font);
	}
	(**te).txFont = smarta_font;
	(**te).txSize = 10;
	curp = locbuf;
	
#if LOGFILE
fprintf(flog,"len %d strlen %d s [%s]\n", len, strlen(locbuf), locbuf);
fflush(flog);
#endif

	while(curp=NextGkWord(curp,betastring)) {
		if( want_to_quit() )
			break;
#if LOGFILE
fprintf(flog,"b [%s]\n", betastring );
fflush(flog);
#endif

		if( (**te).teLength > 30000 ) {
			sprintf(tmp,"Hey! This window almost full. Save contents and start a new one!\r");
			TEInsert(tmp,(long)strlen(tmp),te);
		}

		if( checkstring(betastring,prntflags) ) {
#if LOGFILE
fprintf(flog,"a hit!\n");
fflush(flog);
#endif
			bp = anal_buf();
			if( is_dumpform ) {
				printf("%d %d %s %2.2f\n", ++nwords, ++nhits, betastring , 
				(float)nhits/(float)nwords);
				printdump(bp);
			} else {
			
#if LOGFILE
fprintf(flog,"%s", bp);
fflush(flog);
#endif

				TEInsert(bp,(long)strlen(bp),te);
			}
		} else {
			char failmess[80];
			char tmpfail[80];	

			if( is_dumpform ) {
				
				printf("%d %d %s X %2.2f\n", ++nwords, nhits, betastring ,
				(float)nhits/(float)nwords);
				sprintf(failmess,"&Could not understand $[%s]& \r\r", betastring);
				beta2smarta(failmess,tmpfail);
				printdump(tmpfail);
			} else {
				sprintf(failmess,"&Could not understand $[%s]& \r\r", betastring);
				beta2smarta(failmess,tmpfail);
				TEInsert(tmpfail,(long)strlen(tmpfail),te);
			}
		}
		EWindowOverhaul(DictWindow,true,true,true);
	}
	xFree(locbuf,"locbuf");
	locbuf = NULL;

}

#if LOGFILE
LOGFILE(char *s)
{
	if( flog ) {
		fprintf(flog,"%s", s);
		fflush(flog);
	}
}
#endif

EnableDialects(void)
{
	EnableItem(dictMenu,AnyDialect);
	EnableItem(dictMenu,Attic);
	EnableItem(dictMenu,Ionic);
	EnableItem(dictMenu,Doric);
	EnableItem(dictMenu,Epic);
	EnableItem(dictMenu,Aeolic);
	EnableItem(dictMenu,Prose);
	EnableItem(dictMenu,Paradigm);
}


DisableDialects(void)
{
	DisableItem(dictMenu,AnyDialect);
	DisableItem(dictMenu,Attic);
	DisableItem(dictMenu,Ionic);
	DisableItem(dictMenu,Doric);
	DisableItem(dictMenu,Epic);
	DisableItem(dictMenu,Aeolic);
	DisableItem(dictMenu,Prose);
	DisableItem(dictMenu,Paradigm);
}
			
toggle_quickflag(void)
{
	if( quickflag ) quickflag = 0;
	else quickflag = 1;
	
	CheckQuickFlag();
}

CheckQuickFlag(void)
{
	CheckItem(dictMenu,QuickSearch,quickflag ? true : false );
}

/*
toggle_checkpreverb()
{
	if( prntflags & CHECK_PREVERB ) prntflags &= (~CHECK_PREVERB);
	else prntflags |= CHECK_PREVERB;
	
	CheckCheckPreverb();
}
*/

/* grc 6/6/88
CheckCheckPreverb()
{
	CheckItem(dictMenu,CheckPreverb,(prntflags & CHECK_PREVERB) ? true : false );
}
*/

ZapWindowDialect(WindowPtr curWind)
{
	int i;
	
	for(i=0;i<MAXGKWINDOWS;i++) {
		if( dial_map[i].aWindowPtr == curWind ) {
			dial_map[i].aWindowPtr = NULL;
			dial_map[i].WindowDialect = 0;
			return;
		}
	}
}

Dialect
GetWindowDialect(WindowPtr curWind)
{
	int i;
	
	for(i=0;i<MAXGKWINDOWS;i++) {
		if( dial_map[i].aWindowPtr == curWind ) {
			return( dial_map[i].WindowDialect);
		}
	}
	return((Dialect)0);
}

SetWindowDialect(WindowPtr curWind, Dialect dial)
{
	int i;
	
	for(i=0;i<MAXGKWINDOWS;i++) {
		if( dial_map[i].aWindowPtr == curWind ) {
			dial_map[i].WindowDialect = dial;
/*printf("a) i %d dial %lo\n", i , dial );*/
			return;
		}
		if( dial_map[i].aWindowPtr == NULL ) {
			dial_map[i].aWindowPtr = curWind;
			dial_map[i].WindowDialect = dial;
/*printf("b) i %d dial %lo\n", i , dial );*/
			return;
		}
	}
/*printf("failing on SetWindowDialect\n");*/
}

SetDialectMenu(WindowPtr curWind)
{

	updateDialect((Dialect)0);
	updateDialect(GetWindowDialect(curWind));
	CheckDialects(GetWantDialect());

}

SetNewDialect(int item)
{
	
	switch(item) {
		case AnyDialect:
			updateDialect((Dialect)0);
			break;
		case Attic:
			updateDialect((Dialect)ATTIC);
			break;
		case Ionic:
			updateDialect((Dialect)IONIC);
			break;
		case Epic:
			updateDialect((Dialect)EPIC);
			break;
		case Aeolic:
			updateDialect((Dialect)AEOLIC);
			break;
		case Doric:
			updateDialect((Dialect)DORIC);
			break;
		case Prose:
			updateDialect((Dialect)PROSE);
			break;
		case Paradigm:
			updateDialect((Dialect)PARADIGM);
			break;
		
		default:
			break;
	}
	SetWindowDialect(FrontWindow(),GetWantDialect());
	CheckDialects(GetWantDialect());
}

CheckDialects(Dialect dial)
{


/*
printf("dial [%lo]\n", dial );
*/

/*	if( dial == 0 )
		CheckItem(dictMenu,AnyDialect, true  );
	else
		CheckItem(dictMenu,AnyDialect, false );
*/

	CheckItem(dictMenu,AnyDialect, (dial == 0) ? true : false );
	CheckItem(dictMenu,Attic, (dial & ATTIC) ? true : false );
	CheckItem(dictMenu,Ionic, (dial & IONIC) ? true : false );
	CheckItem(dictMenu,Doric, (dial & DORIC) ? true : false );
	CheckItem(dictMenu,Prose, (dial & PROSE) ? true : false );
	CheckItem(dictMenu,Epic, (dial & EPIC) ? true : false );
	CheckItem(dictMenu,Aeolic, (dial & AEOLIC) ? true : false );
	CheckItem(dictMenu,Paradigm, (dial & PARADIGM) ? true : false );
}

GetDictWindow(void)
{
	if( ! DictWindow ) {
		MakeWind (false,"\pResult Window",nil);
		DictWindow = FrontWindow();

#if LOGFILE
flog = fopen("logfile", "w");
#endif

	} else {
		(void) SelectWindow(DictWindow);
		ShowWindow (DictWindow);
		EWindowOverhaul (DictWindow, false, false, IsEWindowDirty (DictWindow));
		SetPort (DictWindow);
		ValidRect (&DictWindow->portRect);
	}
}

/*
	Handle selection of About… item from Apple menu
*/

DoAbout (void)
{
/*
	(void) Alert (aboutAlrt, nil);
*/
	ErrMesg("\pMorpheus was written by Gregory Crane, Joshua Kosman, and Neel Smith");
}


/*
	Background procedure.  Check front window, reset menus if it
	changes.  The menu bar doesn't need redrawing by SetTextMenus
	if the previous and current front window are either both edit
	windows or both not edit windows.  This check eliminates some
	needless menu flashing.
*/

CheckFront (void)
{
	if (FrontWindow () != lastFront )
	{
		SetNonTextMenus ();
		if (IsEWindow (FrontWindow ()) == IsEWindow (lastFront)) 
			SetTextMenus (false);
		else {
			SetTextMenus (true);
		}
		if( FrontWindow() != DictWindow ) {
			EnableDialects();
			SetDialectMenu(FrontWindow());
/* grc 6/6/88
			CheckCheckPreverb();
*/
			CheckQuickFlag();
		} else
			DisableDialects();
		lastFront = FrontWindow ();
	}
}

#if PROFILE
extern _profile;
#endif

main (void)
{
	AppFile theFile;
	Use_hqdict = 1;	
	Stdio_MacInit(true);
#if PROFILE
_profile = 1;
#endif 


/*
	Initialize TransSkel, create menus and install handlers.
*/

	SkelInit ();

	SkelApple ("\pAbout Morpheus…", DoAbout);

	fileMenu = NewMenu (1000, "\pFile");
	AppendMenu (fileMenu, "\pNew/N;Open.../O;Close/K;(-;Save/S;Save As...");
	AppendMenu (fileMenu, "\pSave a Copy As...;Revert/R;(-;Quit/Q;DumpForm");
	SkelMenu (fileMenu, DoFileMenu, nil);

	editMenu = NewMenu (1001, "\pEdit");
	AppendMenu (editMenu, "\pUndo/Z;(-;Cut/X;Copy/C;Paste/V;Clear");
	SkelMenu (editMenu, EWindowEditOp, nil);

	fontMenu = NewMenu (1002, "\pFont");
	DisableItem (fontMenu, 0);
	AddResMenu (fontMenu, 'FONT');
	SkelMenu (fontMenu, DoFontMenu, nil);

	sizeMenu = NewMenu (1003, "\pSize");
	DisableItem (sizeMenu, 0);
	AppendMenu (sizeMenu, "\p9 Point;10 Point;12 Point;14 Point");
	AppendMenu (sizeMenu, "\p18 Point;20 Point;24 Point; 48 Point");
	SkelMenu (sizeMenu, DoSizeMenu, nil);

	formatMenu = NewMenu (1004, "\pFormat");
	DisableItem (formatMenu, 0);
	AppendMenu (formatMenu, "\pWord Wrap;No Word Wrap;(-;Left;Center;Right");
	SkelMenu (formatMenu, DoFormatMenu, nil);

	dictMenu = NewMenu (1004, "\pParse");
	DisableItem (dictMenu, 0);
	AppendMenu (dictMenu, "\pParse Selection/L;Parse Document/A;Parse Clipboard;(-;Any Dialect;Attic;Ionic;Doric;Epic;Aeolic;Prose;Paradigm;(-;Quick and Dirty;Check Preverb");
	SkelMenu (dictMenu, DoDictMenu, nil);

#if FILTERS
	filtMenu = NewMenu (1005, "\pFilters");
	DisableItem (filtMenu, 0);
	AppendMenu (filtMenu, "\pBeta2Smarta;Beta2SMK");
	SkelMenu (filtMenu, DoFiltMenu, nil);
#endif
	SetNonTextMenus ();
	SetTextMenus (true);

/*
	Do TransEdit-specific setup:  set creator for any files created,
	set default text style and event notification procedures for
	new windows.
*/

	SetEWindowCreator ('MORF');
	SetEWindowStyle (nil, monaco, 9, 0, teJustLeft);
	SetEWindowProcs (nil, Key, Activate, Close);
	
	OpenResFile("\pMorpheus.rsrc");
	GetAppFiles(1,&theFile);
/*	PtoCstr(theFile.fName);*/
	if( ! (*theFile.fName) )
		MakeWind(false,nil,nil);
	else {
/*	printf("theFile.fName [%s]\n", theFile.fName);
	CtoPstr(theFile.fName);*/

		MakeWind(true,theFile.fName,&theFile);
	}
/*
	PtoCstr(theFile.fName);
	printf("theFile.fName [%s]\n", theFile.fName);
*/

/*
	Process events until user quits,
	then clean up and exit
*/
	SkelBackground (CheckFront);
	SkelMain ();
	SkelClobber ();
}


SKErrMess(void)
{
 	if( ErrWindow == nil) {
 		MakeDWindow();
		ErrWindow = FrontWindow();
	} else
		SelectWindow(ErrWindow);
		
	DisplayText(ErrMess,(long)strlen(ErrMess));
}