static char  SCCSID[] = "@(#)token.c	2.2  8/31/87";
/*
 * Copyright Jud Harward
 * June 1987
 */
/*
 *	#include  <token.h>
 *
 *	TKtree  tkcreate()
 *
 *	TKtree  tkpcreate()
 *
 *	TKtree  tkcopy( Tree )
 *	TKtree  Tree;
 *
 *	tkcheck( Tree )
 *	TKtree  Tree;
 *
 *	tkenter( Tree, string, svalue )
 *	TKtree  Tree;
 *	unsigned char  *string;
 *	short  svalue;
 *
 *	tkcompile( Tree )
 *	TKtree  Tree;
 *
 *	short tkmatch( Tree, c )
 *	TKtree  Tree;
 *	unsigned char  c;
 *
 *	short tknext( Tree )
 *	TKtree  Tree;
 *
 *	short tkparse( Tree, c )
 *	TKtree  Tree;
 *	unsigned char  c;
 *
 *	short tkpnext( Tree )
 *	TKtree  Tree;
 *
 *	short tkflush( Tree )
 *	TKtree  Tree;
 *
 *	tkreset( Tree )
 *	TKtree  Tree;
 *
 *	tkdestroy( Tree )
 *	TKtree  Tree;
 *
 *	These routines create and manage the transitions of finite state
 *	pattern matching machines that recognize a set of possibly
 *	overlapping keywords.
 *
 *	tkcreate() creates and initializes the machine.  tkenter()
 *	enters a keyword in the machine for later recognition.
 *	After all keywords have been entered, the failure function must
 *	be calculated by calling tkcompile().  tkcheck() determines
 *	whether a pointer points to a valid but uncompiled machine tree
 *	(return = TKVALID), to a valid machine tree with failure
 *	function (return = TKSET), or to something else (TKYUK).
 *	It is intended mainly for debugging purposes.  Note keywords
 *	can only be entered before the machine is compiled.
 *
 *	The user associates a keyword with a positive integer svalue
 *	when the keyword is submitted via tkenter().  tkmatch() reads
 *	an input stream character by character and will return this
 *	value if the keyword is recognized.  Otherwise, it returns
 *	PENDING.  The external variable TKfail can be queried after
 *	a call to tkmatch().  If it is true, the machine performed
 *	a failure or wild card transition on the most recent call,
 *	indicating that it was unable to recognize a character
 *	(but probably not the most recent one) in the input
 *	string.  FAILURE and PENDING are defined in token.h 
 *	along with the structures for building the machine.
 *
 *	tkmatch() can only operate with compiled machines.  If a
 *	transition on a given input character leads to the recognition of
 *	more than one keyword (e.g., keywords = {she, he}, input="she"),
 *	tkmatch() will return the svalue of the longest keyword first.
 *	The user can check for additional matches by calling
 *	tknext() until it returns PENDING.  NUL and WCARD
 *	('\0' and '\377') are reserved characters and should
 *	never occur in key strings or be submitted to tkmatch()
 *	(or tkparse()).
 *
 *	tkreset() returns the machine to the start state.  tkdestroy()
 *	destroys the machine and frees the storage it occupied.
 *
 *	tkparse() is similar to tkmatch() but it reports maximal
 *	string matches and resets the automaton after each match.
 *	For example, if "sort" and "sorting" are keywords entered
 *	by tkenter(), and the input string consists of "do sorting now",
 *	tkmatch() would recognize "sort" when it sees the 't' and
 *	"sorting" when it sees the 'g', while tkparse() would only
 *	recognize "sorting", and that only after reaching the space
 *	after the 'g'.  tkparse() is more suitable for recognizing
 *	input tokens of a command language.  In connection with TKfail,
 *	for instance, it can be used to parse cursor control and
 *	command strings from a terminal.
 *
 *	An automaton to be used with tkparse() must be created by a
 *	call to tkpcreate(), but it should be compiled by a call to
 *	the regular routine tkcompile().  tkcheck() can be used to
 *	distinguish between tkmatch and tkparse automata.  When
 *	called with a pointer to a tkparse automaton, tkcheck()
 *	returns TKPVALID or TKPSET depending on whether the automaton
 *	is compiled or not.  Because tkparse() searches for maximal
 *	key strings before it reports a match, it can return an svalue
 *	only upon recognition of a failure transition.  Thus, tkparse()
 *	is always at least "a character behind".  This requires two
 *	special techniques.  The first is identical to tkmatch().
 *	After a successful match, the user should call tkpnext() to
 *	check for any further matches in the input queue until he receives
 *	a return of PENDING.  Secondly, upon end of input or at any
 *	point that the user wishes to flush the input stream, he may
 *	call tkflush() to force reporting of pending tokens.  tkflush(),
 *	like tkpnext(), should be called repeatedly until it returns
 *	PENDING.  The difference between tkpnext() and tkflush() is that
 *	tkpnext() neither forces the recognition of a pending token nor
 *	does it flush trailing unmatched characters from the input queue.
 *
 *	This implementation is based on the algorithm given in A. V.
 *	Aho and M. J. Corasick, "Efficient String Matching: An Aid to
 *	Bibliographic Search," CACM 18:6 (June 1975) 333 - 340,
 *	modified to incorporate the output function in the goto tree
 *	and to allow the maximal matches of tkparse().
 *
 *	tkcopy() spawns a copy of the automaton that shares the
 *	the fixed data tree of the original.  This enables multiple
 *	applications to use the same automaton with minimal storage
 *	requirements.  tkdestroy() can be used to release a copy
 *	as well as an original machine since the automaton tree
 *	structure is reference counted.  tkcopy() will duplicate
 *	automata initialized by both tkcreate() and tkpcreate().
 *	It does not preserve the state of the copied automaton,
 *	however.  The returned automaton is in its initial or
 *	reset state.  tkcopy() can only copy a compiled automaton.
 *
 *	Written by	Jud Harward, University of Cincinnati, 15 July 1985
 *	Modified by	Jud Harward, 5 August, 1985
 *	Modified by	Jud Harward, August, 1987
 */

#include  <usual.h>
#include  <token.h>

/*
 *	tkcreate() returns a pointer to a new machine to be used with
 *	tkmatch(); NULL on error
 */

TKtree
tkcreate()
{
    TKtree          Tree;
    char           *malloc();
    TKtrans         tknode();

    if ((Tree = (TKtree) malloc(sizeof(TKhead))) == NULL)
	return (NULL);
    Tree->magic = (long) Tree ^ TMVALID;
    Tree->nkey = 0;
    Tree->tflags = TF_NORM;
    Tree->refct = NULL;
    if ((Tree->link = tknode(NUL, PENDING, SF_NORM)) == NULL) {
	tkdestroy(Tree);
	return (NULL);
    } else {
	Tree->cstate = Tree->link;
	Tree->ostate = NULL;
	Tree->odepth = 0;
	Tree->cqueue = NULL;
    }
    if ((Tree->refct = (int *) malloc(sizeof(int))) == NULL) {
	tkdestroy(Tree);
	return (NULL);
    } else {
	*Tree->refct = 1;
	return (Tree);
    }
}


/*
 *	tkpcreate() returns a pointer to a new machine to be used with
 *	tkparse(); NULL on error
 */

TKtree
tkpcreate()
{
    TKtree  Tree;

	if (( Tree = tkcreate()) == NULL ) return( NULL );
	if (( Tree->cqueue = qcreate( CHAR, LOOKAHEAD )) == NULL )  {
	    tkdestroy( Tree );
	    return( NULL );
	}
	else  return( Tree );
}


/*
 *	tkcopy() returns a pointer to an initialized copy of the original
 *	automaton supplied as an argument.
 */
 
TKtree
tkcopy(Tree)
TKtree          Tree;
{
    TKtree          Duptree;
    char           *malloc();

    if (TM(Tree) != TMSET)
	tkdie("tkcopy: bad automaton");
    if ((Duptree = (TKtree) malloc(sizeof(TKhead))) == NULL)
	return (NULL);
    (*Tree->refct)++;
    *Duptree = *Tree;
    Duptree->magic = (long) Duptree ^ TMSET;
    if (Duptree->cqueue) {
	if ((Duptree->cqueue = qcreate(CHAR, LOOKAHEAD)) == NULL) {
	    tkdestroy(Duptree);
	    return (NULL);
	}
    }
    tkreset(Duptree);
    return (Duptree);
}


tkcheck( Tree )
TKtree  Tree;
{
    switch ( TM( Tree ) )  {
	case TMVALID:
	    return( (Tree->cqueue == NULL) ? TKVALID : TKPVALID );
	case TMSET:
	    return( (Tree->cqueue == NULL) ? TKSET : TKPSET );
	default:
	    return( TKYUK );
    }
}


/*
 *	tkenter() enters keyword string in goto tree pointed to by Tree 
 *	so that tkmatch() will return svalue>0 on recognition of string.
 *
 *	Returns FAILURE if storage not available for new nodes;
 *	otherwise SUCCESS.
 *
 *	The goto tree is stored with node->child pointing to the
 *	an order linked list of possible transitions linked via
 *	sibling.
 */

tkenter( Tree, string, svalue )
TKtree  Tree;
register unsigned char  *string;
short   svalue;
{
    TKtrans  Trans;	/* ptr to search down current goto tree	*/
    TKtrans  Ntrans;	/* temp state ptr			*/
    TKtrans  tklist();

	if ( TM( Tree ) != TMVALID )
	    tkdie( "tkenter: bad automaton" );
	if ( svalue <= 0 )
	    tkdie( "tkenter: bad svalue" );
	if ( *string == NUL )
	    return( FAILURE );  /* empty keywd  */
	Tree->nkey++;		/* need number of keywords to set size
				/*  of queue used by failure function	*/

	Ntrans = Trans = Tree->link;

	while ( *string != NUL )  {

	    if ( tkgoto( &Ntrans, *string ) == SUCCESS )  {
		string++;
		Trans = Ntrans;
		continue;
	    }
	    else if ( Ntrans == NULL )  {
		if (( Ntrans = tklist( string, svalue )) == NULL )
		    return( FAILURE );	/* link to child of Trans */
		Ntrans->sibling = Trans->child;
		Trans->child = Ntrans;
		return( SUCCESS );
	    }
	    else  {
		Trans = Ntrans->sibling;	/* link to sibling of Trans */
		if (( Ntrans->sibling = tklist( string, svalue )) == NULL )
		    return( FAILURE );
		Ntrans->sibling->sibling = Trans;
		return( SUCCESS );
	    }
	}

	/* fall through if string is a substring of a previous keyword */
	if ( Trans->sflags & SF_OUTPUT )
	    return( FAILURE );			/* duplicate key string	*/
	else  {
	    Trans->sflags |= SF_OUTPUT;
	    Trans->sval = svalue;
	    return( SUCCESS );
	}
}


/*
 *	tkcompile() computes the failure function for the goto tree
 *	and prepares the machine to accept input via tkmatch() or tkparse().
 *	It returns FAILURE if no keywords have been entered or if
 *	storage is unavailable, otherwise SUCCESS.
 *
 *	The algorithm works by conducting a breadth first traversal
 *	of the goto tree;  the failure transitions for each successive
 *	level are calculated from those of the parent level.  Note that
 *	a state's failure transition is assigned after the state is
 *	enqueued to generate the next level.  Failure transitions for
 *	null output states are a special case.
 *
 *	WCARD is a special character defined as a default 
 *	transition necessary so that the initial state has a transition 
 *	on every character.  Otherwise failure can become a very tight loop.
 *
 *	A few definitions will make the algorithm clearer.  Given
 *	a keyword, it can be recognized in any of a number of
 *	"output states".  Each keyword, however, has only one
 *	"receiving state", which is the state that contains its sval.
 *	The "token" of an output state or taken as a pair, an
 *	"output token", is defined to be the longest key string that
 *	terminates at that output state.  The tkparse output function
 *	computed during tkcompile() is used to point from each output
 *	state to the receiving state (rstate) of its token.  Null
 *	pointers indicate that there is no output.  The failure function
 *	is computed according to the standard Aho and Corasick algortihm
 *	for both tkmatch() and tkparse().  The depth of all
 *	states is computed during tkcompile() from Tree->link, which
 *	has depth 0.  A token's length is the number of characters it
 *	contains, which is the same as the depth of its receiving state.
 *	An output token's "start depth" is defined to be the depth of
 *	the transition in the path from the tree root to the output state
 *	at which the token begins.  It is equal to
 *	
 *		output state depth - token length + 1.
 *
 *	This is used to find the maximal matches of tkparse().
 */
		
static Myctr = 0;
tkcompile( Tree )
TKtree  Tree;
{
    Queue  *queue;
    TKtrans  Tstart;
    TKtrans  Trans;
    TKtrans  Tfail;
    TKtrans  Ntrans;
    register TKtrans  Pfail;
    TKtrans  tknode();

	if( TM( Tree ) != TMVALID )
	    tkdie( "tkcompile: bad automaton" );
	if ( Tree->nkey == 0 )  return( FAILURE );

	if (( queue = qcreate( POINTER, Tree->nkey ))  == NULL ) {
	    return( FAILURE );
	}

	Tstart = Tree->link;
	Trans = Tstart->child;

    /* Add a default transition from the initial state to backstop
    /* the failure function;  nb. WCARD transition must be first	*/
	if (( Tstart->child = tknode( WCARD, PENDING, SF_NORM )) == NULL ) {
	    return( FAILURE );
	}
	Ntrans = Tstart->child;
	Ntrans->sdepth = 0;
	Ntrans->fail = Ntrans->child = Ntrans;	/* default transition	*/
	Ntrans->sibling = Trans;		/*  points to itself	*/
	
    /* Tree has at least one child because nkey > 0;
    /*  set failure function and receive state for states of depth 1.	*/
	do  {
	    Trans->fail = Ntrans;
	    Trans->sdepth = 1;
	    if ( Trans->sval > 0 )  Trans->rstate = Trans;
	    qadd( &Trans, queue );
	}  while (( Trans = Trans->sibling) != NULL );

	while ( qremove( &Trans, queue ) == SUCCESS )  {
	    if ( Trans->cval == WCARD )  continue;

	    for ( Ntrans = Trans->child;
		    Ntrans != NULL;
		    Ntrans = Ntrans->sibling )  {
			Ntrans->sdepth = Trans->sdepth + 1;
			if ( Ntrans->cval == WCARD )  continue;
			qadd( &Ntrans, queue );
			Pfail = Tfail = Trans->fail;
			while ( tkgoto( &Tfail, Ntrans->cval ) == FAILURE )  {
			    Tfail = Pfail->fail;
			    Pfail = Tfail;
			}
			Ntrans->fail = Tfail;
    /* Set the output flag if appropriate;  if the output flag is set for
    /*   the failure state, then the failing state has output on a substring */
			if ( (Tfail->sflags & SF_OUTPUT)  ||
			      Ntrans->sval != PENDING )  {
				Ntrans->sflags |= SF_OUTPUT;
				for ( Pfail = Ntrans;
				      Pfail->sval == PENDING;
				      Pfail = Pfail->fail ) ;
				Ntrans->rstate = Pfail;
			}
	    }
	}

	qdestroy( queue );
	Tree->magic = (long) Tree ^ TMSET;
	return( SUCCESS );
}


/*
 *	tklist() creates a vertical ( parent -> child -> child ) chain
 *	of nodes to hold the transition states for the remainder of the
 *	string pointed to by cstr.  It inserts the recognition value sv
 *	at the end of the chain, and returns a pointer to the head
 *	of the chain or NULL on failure.
 */

static TKtrans
tklist( cstr, sv )
unsigned char  *cstr;
int             sv;
{
    register TKtrans  Plp;
    TKstate  Plk;
    TKtrans  tknode();
    char    *malloc();

	Plp = &Plk;
	do  {
	    if (( Plp->child = tknode( *cstr, PENDING, SF_NORM )) == NULL )
		return( NULL );
	    Plp = Plp->child;
	}  while ( *++cstr != NULL );

	Plp->sflags |= SF_OUTPUT;
	Plp->sval = sv;
	return( Plk.child );
}


/*
 *	tknode() creates a new tree node with cvalue, cv, and svalue,
 *	sv.  Pointers child, sibling, and fail are initialized to NULL.
 *	Returns a pointer to the new node or NULL if storage is not
 *	available.
 */

static TKtrans
tknode( cv, sv, flags )
unsigned char  cv;
short  sv;
unsigned char  flags;
{
    register TKtrans  Pnode;
    char  *malloc();

	if (( Pnode = (TKtrans) malloc( sizeof( TKstate ))) == NULL )
	    return( NULL );
	Pnode->cval = cv;
	Pnode->sval = sv;
	Pnode->sflags = flags;
	Pnode->child = Pnode->sibling = Pnode->fail = Pnode->rstate = NULL;
	Pnode->sdepth = 0;
	return( Pnode );
}


/*
 *	tkgoto( &Tr, cv )
 *	TKtrans  Tr;
 *	unsigned char  cv;
 *
 *	tkgoto() searches for a transition on the character cv
 *	out of the state pointed to by Tr.  If there is one, it
 *	returns SUCCESS and Tr is set to point to the state resulting from
 *	the transition.  Otherwise, tkgoto() returns FAILURE and Tr is set
 *	to point to the transition out of Tr in the ordered list
 *	Tr->child(->sibling->...) that precedes the insertion point for
 *	cv.  If Tr has no transitions or if the transition on
 *	cv precedes all other transitions out, Tr is set to NULL.
 */

static
tkgoto( Ptr, cv )
register TKtrans  *Ptr;
unsigned char  cv;
{
    register TKtrans  Tr;
    TKtrans  Twild = NULL;
	
	Tr = (*Ptr)->child;
	*Ptr = NULL;

	while ( Tr != NULL )  {
	    if ( Tr->cval == cv )  {
		*Ptr = Tr;
		return( SUCCESS );	
	    }
	    else if ( Tr->cval == WCARD )
		Twild = Tr;	/* there may be a real transition later   */
	    else if ( Tr->cval > cv )  break;

	    *Ptr = Tr;		/* fall through to cycle */
	    Tr = Tr->sibling;
	}
	if ( Twild )  {
	    *Ptr = Twild;
	    return( SUCCESS );
	}
	else  return( FAILURE );
}


/*
 *	tkmatch() advances the machine pointed to by Tree from its current
 *	state to a new state on the transition specified by c.  It returns
 *	an sval > 0 on recognition of a keyword established in the machine
 *	by tkenter(), otherwise PENDING (0).  TKfail is set to YES (>0)
 *	if tkmatch() performs a failure or wildcard transition.  tknext()
 *	should be called after a successful match to recognize multiple
 *	key strings on the same letter (e.g., "please", "lease", "ease").
 */

short  TKfail;

short
tkmatch( Tree, c )
register TKtree  Tree;
unsigned char  c;
{
    register TKtrans  Trans;
    register TKtrans  Tfail;

	TKfail = 0;

	if ( Tree->cqueue )  tkdie( "tkmatch: tkparse automaton" );

	Tfail = Tree->cstate;
	Trans = Tfail->child;
	Tree->cstate = NULL;

mfail:  if ( Trans != NULL && Trans->cval == WCARD )  {
	    Tree->cstate = Trans;
	    Trans = Trans->sibling;
	}
	while ( Trans != NULL )  {
	    if ( Trans->cval > c )  break;
	    else if ( Trans->cval == c )  {
		Tree->cstate = Trans;
		if ( Trans->sflags & SF_OUTPUT )  {
		    Tree->ostate = Trans;
		    return( tknext( Tree ));
		}
		else  return( PENDING );
	    }
	    else  Trans = Trans->sibling;
	}
	if ( Tree->cstate == NULL )  {
	    Tfail = Tfail->fail;		/* failure transition	*/
	    Trans = Tfail->child;
	    TKfail++;
	    goto  mfail;
	}
	else   {
	    TKfail++;
	    return( PENDING );			/* wildcard transition	*/
	}
}


/*
 *	tknext() returns the svalue of the pending output state if
 *	there is one, otherwise PENDING.  It also advances Tree->ostate
 *	to point to the next output state or resets it to NULL if
 *	there isn't one.
 */

short
tknext( Tree )
TKtree  Tree;
{
    short  svalue;
    register TKtrans  Ostate;

	if (( Ostate = Tree->ostate ) == NULL )  return( PENDING );
	else  {
	    Ostate = Ostate->rstate;
	    svalue = Ostate->sval;
	    Ostate = Ostate->fail;
	    if ( !(Ostate->sflags & SF_OUTPUT) )
		Tree->ostate = NULL;
	    else  Tree->ostate = Ostate;
	    return( svalue );
	}
}


/*
 *	tkparse() advances the machine pointed to by Tree from its current
 *	state to a new state on the transition specified by c.  It returns
 *	an sval > 0 on recognition of a maximal keyword established in the
 *	machine by tkenter(), otherwise PENDING.  TKfail is set to YES
 *	(>0) if tkparse() discards any input (fails to associate it with
 *	a key string).  This amounts to returning an svalue only
 *	upon recognition of a subsequent failure transition.  Thus, tkparse()
 *	is always a character behind, and tkflush() must be call to guarantee
 *	that the last token has been recognized.
 *
 *	If tkparse() is called by the user, Tree->tflags will not have
 *	the QREAD bit set;  if by tkpnext() it will.  In the latter case
 *	tkpnext() is reviewing that portion of the input stream that
 *	was queued for lookahead.
 */

short
tkparse( Tree, c )
register TKtree  Tree;
unsigned char  c;
{
    register TKtrans  Trans;
    register TKtrans  Tfail;
    TKtrans           Ostate;
    short             svalue;
    short             cdepth;
    unsigned char     from_queue;

	if ( !Tree->cqueue )
	    tkdie( "tkparse: tkmatch automaton" );
	if ( (Tree->tflags & TF_FOUND) && !(Tree->tflags & TF_QREAD) )
	    tkdie( "tkparse: tkpnext not called" );
	Tfail = Tree->cstate;
	Trans = Tfail->child;
	svalue = PENDING;
	TKfail = 0;
    /*  if not called from tkpnext(), add char to input queue		*/
	if ( !(Tree->tflags & TF_QREAD) )
	    if ( qadd( &c, Tree->cqueue ) == FAILURE )
		tkdie( "tkparse: lookahead queue overflow");

	Tree->cstate = NULL;

pfail:  if ( Trans != NULL && Trans->cval == WCARD )  {
	    Tree->cstate = Trans;
	    Trans = Trans->sibling;
	}
	while ( Trans != NULL )  {
	    if ( Trans->cval > c )  break;
	    else if ( Trans->cval == c )  {

    /* normal transition made on current character			*/
		Tree->cstate = Trans;
    /*  if new transition is an output state, calculate the start depth
    /*    of the output token;  if there is no pending output state, or
    /*    if the start depth of the new output token is less than or
    /*    equal to that of the pending output token, replace the pending
    /*    output state with the current output token.			*/
		if ( Trans->sflags & SF_OUTPUT )  {
		    cdepth = Trans->sdepth - Trans->rstate->sdepth + 1;
		    if ( !Tree->ostate || cdepth <= Tree->odepth )  {
			Tree->ostate = Trans;
			Tree->odepth = cdepth;
		    }
		}
		return( PENDING );
	    }

	    else  Trans = Trans->sibling;
	}

	if ( Tree->cstate == NULL )  {
    /* failure transition:						*/
    /*   if there is no pending output state, perform a normal failure
    /*     transition, and delete number by which depths of current 
    /*     and failure states differ from input queue			*/
	    if ( !Tree->ostate )  {
		qdelete( Tfail->sdepth - Tfail->fail->sdepth, Tree->cqueue );
		Tfail = Tfail->fail;
		Trans = Tfail->child;
		TKfail++;
		goto  pfail;
	    }
	    else  {
    /*   else remove depth of last char of pending output token from
    /*       input queue;						*/
		qdelete( Tree->ostate->sdepth, Tree->cqueue );
    /*     start depth of pending output token > 1 ==> unmatched chars
    /*       in the input stream: set TKfail;				*/
		if ( Tree->odepth > 1 )  TKfail++;
    /*     reset the automaton to initial state with no pending output
    /*       token and report match					*/
		Ostate = Tree->ostate;
		Tree->ostate = NULL;
		Tree->cstate = Tree->link;
		Tree->tflags |= TF_FOUND;
		return( Ostate->rstate->sval );
	    }
	}

	else   {
    /* wildcard transition:						*/
    /*   set TKfail and if called from tkpnext(), delete lead char from
    /*     input queue since with wildcard transitions currently limited
    /*     to a default from the initial state, this must be the char
    /*     that caused the transition.					*/
	    TKfail++;
	    qdelete( 1, Tree->cqueue );
	    return( PENDING );
	}
}


/*
 *	tkpnext() checks for additional tkparse output tokens in the 
 *	lookahead queue.  It resets the queue and reports the svalue
 *	of the next token, or PENDING if there is none.
 */

short
tkpnext( Tree )
TKtree  Tree;
{
    unsigned char  qc;
    short          sv;
    short          fail;

	if ( !Tree->cqueue )  tkdie( "tkpnext: tkmatch automaton" );
	fail = 0;
	qreset( Tree->cqueue );
	Tree->tflags |= TF_QREAD;
	while ( qread( &qc, Tree->cqueue ) == SUCCESS )  {
	    sv = tkparse( Tree, qc );
	    fail += TKfail;
	    if ( sv != PENDING )  break;
	}
	Tree->tflags &= ~TF_QREAD;
	if ( sv == PENDING )  Tree->tflags &= ~TF_FOUND;
	TKfail = fail;
	return( sv );
}


/*
 *	tkflush() checks for an unreported token at end of input.
 *	See tkparse().
 */

short
tkflush( Tree )
TKtree  Tree;
{
    short  svalue;

	if ( TM( Tree ) != TMSET  ||  !Tree->cqueue )
	    tkdie( "tkflush: bad automaton" );

	svalue = (Tree->tflags & TF_FLUSH) ? tkpnext( Tree )
					   : tkparse( Tree, NUL );
	if ( svalue == PENDING )  {
	    tkreset( Tree );
	    return( PENDING );
	}
	else  {
	    Tree->tflags |= TF_FLUSH;
	    return( svalue );
	}
}


/*
 *	tkreset() returns the machine pointed to by Tree to its initial
 *	state and flushes the input queue.  
 */

tkreset( Tree )
register TKtree  Tree;
{
	if ( TM( Tree ) != TMSET )  tkdie( "tkreset: bad automaton" );
	Tree->tflags = TF_NORM;
	Tree->cstate = Tree->link;
	Tree->ostate = NULL;
	if ( Tree->cqueue )  qclear( Tree->cqueue );
}


/*
 *	tkdestroy() reclaims the storage used by the machine.
 */

tkdestroy(Tree)
TKtree          Tree;
{
    if (TM(Tree) != TMVALID && TM(Tree) != TMSET)
	tkdie("tkdestroy: bad automaton");
    if (Tree->cqueue)
	qdestroy(Tree->cqueue);
    if (Tree->refct) {
	if (*Tree->refct <= 1) {
	    free(Tree->refct);
	    if (Tree->link != NULL)
		tkcfree(Tree->link);
	} else {
	    (*Tree->refct)--;
	}
    }
    free(Tree);
}


static
tkcfree( Tr )
TKtrans  Tr;
{
    do  {
	if ( Tr->sibling != NULL )
	    tksfree( Tr->sibling );
	free( Tr );
	if ( Tr->child == Tr )  Tr = NULL;	/* WCARD case */
	else  Tr = Tr->child;
    }  while ( Tr != NULL );
}

static
tksfree( Tr )
TKtrans  Tr;
{
    do  {
	if ( Tr->child != NULL )
	    tkcfree( Tr->child );
	free( Tr );
	Tr = Tr->sibling;
    }  while (Tr != NULL );
}


static
tkdie( mess )
char  *mess;
{
    fprintf( stderr, "%s\n", mess );
    exit( 1 );
}
