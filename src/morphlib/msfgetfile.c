# include	<ControlMgr.h>	/* includes WindowMgr.h, QuickDraw.h, MacTypes.h */
#ifdef MACINTOSH
# include	<StdFilePkg.h>
# include	<FileMgr.h>
# include	<ToolBoxUtil.h>
#include <transedit.h>
#include <string.h>

#include "msfgetfile.proto.h"
static SFReply			editFile;		/* file information             */
static Point	dlogWhere = { 70, 100 };	/* GetFile/PutFile location */

mySFGetFile(char *filename)
{
	char volName[64];
	int vRefNum;
	OSType		type = 'TEXT';
	
	SFGetFile (dlogWhere, "\p", nil, 1, &type, nil, &editFile);
	if (!editFile.good) {
			filename[0] = 0;
			return (0);
	}
	GetVol(volName,&vRefNum);
	PtoCstr(volName);
	printf("volName [%s]\n", volName );
	strcpy(filename,editFile.fName);
	PtoCstr(filename);
	return(1);
}
#endif
