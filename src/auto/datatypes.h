/*	datatypes.h 1.7 8/23/85	*/

#define  CHAR    0
#define  SHORT   1
#define  LONG    2
#define  POINTER 3
#define  FLOAT   4
#define  DOUBLE  5

#ifdef SOURCE
static short  typsiz[] = {
    sizeof( char ),
    sizeof( short ),
    sizeof( long ),
    sizeof( char * ),
    sizeof( float ),
    sizeof( double )
};
#endif


typedef struct {
    short stype;
    char  *sptr;
    char  *stop;
    char  *send;
} Stack;

Stack  *screate();


typedef struct  {
    short qtype;
    long  qitems;
    long  qsize;
    char *qptr;
    char *qend;
    char *qhead;
    char *qtail;
    char *qrptr;
}  Queue;

Queue  *qcreate();


typedef struct{
    short  rstype;
    char   *rfirst;	/* first data loc				*/
    char   *rlast;	/* last data loc				*/
    char   *rtop;	/* next data loc (last popped data loc )	*/
    char   *rbottom;	/* last data item				*/
    char   *rptr;	/* last read data loc				*/
    long   count;	/* items in rstack				*/
    long   rcount;	/* number of unpopped items read		*/
    long   items;	/* size of rstack in data items			*/
} Rstack;

Rstack  *rscreate();
