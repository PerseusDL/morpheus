/* token.h	2.1  8/31/87 */
/*
 * Copyright Jud Harward
 * August 1985
 */

#include  <datatypes.h>

#define  PENDING	-1

typedef struct  tkstate {
    unsigned char   cval;	/* char causing transition to state	*/
    unsigned char   sflags;	/* state flags				*/
    short           sval;	/* value returned when token recognized	*/
    struct tkstate *child;	/* ptr to tree for subsequent letters	*/
    struct tkstate *sibling;	/* ptr to alternate transitions from	*/
				/*    parent state			*/
    struct tkstate *fail;	/* ptr to next state on failure 	*/
    struct tkstate *rstate;	/* ptr to receiving state of output	*/
				/*  token for tkparse			*/
    short           sdepth;	/* depth of state			*/
}  TKstate, *TKtrans;

typedef struct {
    long            magic;	/* magic key to unlock machine		 */
    short           nkey;	/* count of key strings			 */
    unsigned char   tflags;	/* tree flags				 */
    TKtrans         link;	/* ptr to initial state of automaton	 */
    TKtrans         cstate;	/* ptr to current state of automaton	 */
    TKtrans         ostate;	/* ptr to pending output state		 */
    short           odepth;	/* start depth of pending output state	 */
    Queue          *cqueue;	/* input queue				 */
    int            *refct;	/* ref count for tkcopy/tkdestroy	 */
}               TKhead, *TKtree;

#define  TMVALID  0xB38F0F83	/* unusual value for key to tree 	*/
				/*  without failure function		*/
#define  TMSET    0xD2214080	/* another for compiled machine		*/
#define  TM( Tree )  ((long) Tree ^ Tree->magic)
#define  TKVALID  -1
#define  TKPVALID -2
#define  TKSET    -3
#define  TKPSET   -4
#define  TKYUK    -5

#define  SF_NORM    00
#define  SF_OUTPUT  01
#define  TF_NORM    00
#define  TF_QREAD   01
#define  TF_FLUSH   02
#define  TF_FOUND   04

#define  WCARD	(unsigned char) '\377'

#define  LOOKAHEAD  120		/* maximum lookahead for tkparse tokens	*/

TKtree tkcreate();
TKtree tkpcreate();
TKtree tkcopy();
short  tkmatch();
short  tknext();
short  tkparse();
short  tkpnext();
short  tkflush();

extern short  TKfail;
