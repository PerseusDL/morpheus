/*
 * Copyright Gregory Crane
 * April 1987
 */

static char  SCCS_ID[] = "betaform.c  1.5  8/25/85";

/*
 *      Character translation table and escape routine to drive the
 *      ssearch package for the TLG database in beta format.
 *
 *      Written by Jud Harward and Michael Lennon
 *                 Department of Classics
 *                 University of Cincinnati
 *                 21 August 1985
 */
#include "srchstate.h"
#if MACINTOSH
#include  "godzilla_1:lightspeed:automaton:ssearch.h"
#else
#include "../auto/ssearch.h"
#endif

#define  CENTRY( CX, CF )       { CX, CF }

Centry  betatab[ 128 ] =  {
    CENTRY( NUL, CF_NORM ),             /* \000 (NUL)                   */
    CENTRY( NUL, CF_NORM ),             /* \001                         */
    CENTRY( NUL, CF_NORM ),             /* \002                         */
    CENTRY( NUL, CF_NORM ),             /* \003                         */
    CENTRY( NUL, CF_NORM ),             /* \004                         */
    CENTRY( NUL, CF_NORM ),             /* \005                         */
    CENTRY( NUL, CF_NORM ),             /* \006                         */
    CENTRY( NUL, CF_NORM ),             /* \007                         */
    CENTRY( NUL, CF_NORM ),             /* \010                         */
    CENTRY( WBC, CF_NORM ),             /* \011 (TAB)                   */
    CENTRY( WBC, CF_NORM ),             /* \012 (NL)                    */
    CENTRY( NUL, CF_NORM ),             /* \013                         */
    CENTRY( NUL, CF_NORM ),             /* \014                         */
    CENTRY( NUL, CF_NORM ),             /* \015 (CR)                    */
    CENTRY( NUL, CF_NORM ),             /* \016                         */
    CENTRY( NUL, CF_NORM ),             /* \017                         */
    CENTRY( NUL, CF_NORM ),             /* \020                         */
    CENTRY( NUL, CF_NORM ),             /* \021                         */
    CENTRY( NUL, CF_NORM ),             /* \022                         */
    CENTRY( NUL, CF_NORM ),             /* \023                         */
    CENTRY( NUL, CF_NORM ),             /* \024                         */
    CENTRY( NUL, CF_NORM ),             /* \025                         */
    CENTRY( NUL, CF_NORM ),             /* \026                         */
    CENTRY( NUL, CF_NORM ),             /* \027                         */
    CENTRY( NUL, CF_NORM ),             /* \030                         */
    CENTRY( NUL, CF_NORM ),             /* \031                         */
    CENTRY( NUL, CF_NORM ),             /* \032                         */
    CENTRY( NUL, CF_NORM ),             /* \033                         */
    CENTRY( NUL, CF_NORM ),             /* \034                         */
    CENTRY( NUL, CF_NORM ),             /* \035                         */
    CENTRY( NUL, CF_NORM ),             /* \036                         */
    CENTRY( NUL, CF_NORM ),             /* \037                         */
    CENTRY( WBC, CF_NORM ),             /* \040 (SPACE)                 */
    CENTRY( NUL, CF_ESC  ),             /* \041 '!', "alternate" chars  */
    CENTRY( NUL, CF_NORM ),             /* \042 '"'                     */
    CENTRY( NUL, CF_NORM ),             /* \043 '#'                     */
    CENTRY( NUL, CF_NORM ),             /* \044 '$', Begin Greek        */
    CENTRY( NUL, CF_NORM ),             /* \045 '%', Punctuation        */
    CENTRY( NUL, CF_ESC  ),             /* \046 '&', Begin Roman        */
    CENTRY( '\'', CF_MSG ),             /* \047 '\'', apostrophe        */
    CENTRY( NUL, CF_MSG  ),             /* \050 '(', rough breathing    */
    CENTRY( NUL, CF_MSG  ),             /* \051 ')', smooth breathing   */
    CENTRY( NUL, CF_MSG  ),             /* \052 '*', capitalization     */
    CENTRY( NUL, CF_MSG  ),             /* \053 '+', diaeresis          */
    CENTRY( NUL, CF_NORM ),             /* \054 ','                     */
    CENTRY( NUL, CF_ESC  ),             /* \055 '-', hyphenization      */
    CENTRY( NUL, CF_NORM ),             /* \056 '.'                     */
    CENTRY( NUL, CF_MSG  ),             /* \057 '/', acute              */
    CENTRY( NUL, CF_NORM ),             /* \060 '0'                     */
    CENTRY( NUL, CF_NORM ),             /* \061 '1'                     */
    CENTRY( NUL, CF_NORM ),             /* \062 '2'                     */
    CENTRY( NUL, CF_NORM ),             /* \063 '3'                     */
    CENTRY( NUL, CF_NORM ),             /* \064 '4'                     */
    CENTRY( NUL, CF_NORM ),             /* \065 '5'                     */
    CENTRY( NUL, CF_NORM ),             /* \066 '6'                     */
    CENTRY( NUL, CF_NORM ),             /* \067 '7'                     */
    CENTRY( NUL, CF_NORM ),             /* \070 '8'                     */
    CENTRY( NUL, CF_NORM ),             /* \071 '9'                     */
    CENTRY( NUL, CF_NORM ),             /* \072 ':'                     */
    CENTRY( NUL, CF_NORM ),             /* \073 ';'                     */
    CENTRY( NUL, CF_NORM ),             /* \074 '<', expanded Greek     */
/*
    CENTRY( NUL, CF_ESC  ),             /* \074 '<', expanded Greek     *
*/
    CENTRY( NUL, CF_MSG  ),             /* \075 '=', circumflex         */
    CENTRY( NUL, CF_NORM ),             /* \076 '>', expanded Greek     */
/*
    CENTRY( NUL, CF_NORM ),             /* \076 '>'                     *
*/
    CENTRY( NUL, CF_MSG  ),             /* \077 '?', subscript dot      */
    CENTRY( NUL, CF_NORM ),             /* \100 '@', page formatting    */
    CENTRY( 'a', CF_MSG  ),             /* \101 'A', alpha              */
    CENTRY( 'b', CF_MSG  ),             /* \102 'B', beta               */
    CENTRY( 'c', CF_MSG  ),             /* \103 'C', xi                 */
    CENTRY( 'd', CF_MSG  ),             /* \104 'D', delta              */
    CENTRY( 'e', CF_MSG  ),             /* \105 'E', epsilon            */
    CENTRY( 'f', CF_MSG  ),             /* \106 'F', phi                */
    CENTRY( 'g', CF_MSG  ),             /* \107 'G', gamma              */
    CENTRY( 'h', CF_MSG  ),             /* \110 'H', eta                */
    CENTRY( 'i', CF_MSG  ),             /* \111 'I', iota               */
    CENTRY( NUL, CF_MSG  ),             /* \112 'J'                     */
    CENTRY( 'k', CF_MSG  ),             /* \113 'K', kappa              */
    CENTRY( 'l', CF_MSG  ),             /* \114 'L', lambda             */
    CENTRY( 'm', CF_MSG  ),             /* \115 'M', mu                 */
    CENTRY( 'n', CF_MSG  ),             /* \116 'N', nu                 */
    CENTRY( 'o', CF_MSG  ),             /* \117 'O', omicron            */
    CENTRY( 'p', CF_MSG  ),             /* \120 'P', pi                 */
    CENTRY( 'q', CF_MSG  ),             /* \121 'Q', theta              */
    CENTRY( 'r', CF_MSG  ),             /* \122 'R', rho                */
    CENTRY( 's', CF_MSG  ),             /* \123 'S', sigma              */
    CENTRY( 't', CF_MSG  ),             /* \124 'T', tau                */
    CENTRY( 'u', CF_MSG  ),             /* \125 'U', upsilon            */
    CENTRY( 'v', CF_MSG  ),             /* \126 'V', digamma            */
    CENTRY( 'w', CF_MSG  ),             /* \127 'W', omega              */
    CENTRY( 'x', CF_MSG  ),             /* \130 'X', chi                */
    CENTRY( 'y', CF_MSG  ),             /* \131 'Y', psi                */
    CENTRY( 'z', CF_MSG  ),             /* \132 'Z', zeta               */
    CENTRY( NUL, CF_NORM ),             /* \133 '[', brackets           */
    CENTRY( NUL, CF_MSG  ),             /* \134 '\', grave              */
    CENTRY( NUL, CF_NORM ),             /* \135 ']', brackets           */
    CENTRY( NUL, CF_NORM ),             /* \136 '^', leading            */
    CENTRY( WBC, CF_NORM ),             /* \137 '_', dash               */
    CENTRY( NUL, CF_NORM ),             /* \140 '`'                     */
    CENTRY( 'a', CF_MSG  ),             /* \141 'a', alpha              */
    CENTRY( 'b', CF_MSG  ),             /* \142 'b', beta               */
    CENTRY( 'c', CF_MSG  ),             /* \143 'c', xi                 */
    CENTRY( 'd', CF_MSG  ),             /* \144 'd', delta              */
    CENTRY( 'e', CF_MSG  ),             /* \145 'e', epsilon            */
    CENTRY( 'f', CF_MSG  ),             /* \146 'f', phi                */
    CENTRY( 'g', CF_MSG  ),             /* \147 'g', gamma              */
    CENTRY( 'h', CF_MSG  ),             /* \150 'h', eta                */
    CENTRY( 'i', CF_MSG  ),             /* \151 'i', iota               */
    CENTRY( NUL, CF_MSG  ),             /* \152 'j'                     */
    CENTRY( 'k', CF_MSG  ),             /* \153 'k', kappa              */
    CENTRY( 'l', CF_MSG  ),             /* \154 'l', lambda             */
    CENTRY( 'm', CF_MSG  ),             /* \155 'm', mu                 */
    CENTRY( 'n', CF_MSG  ),             /* \156 'n', nu                 */
    CENTRY( 'o', CF_MSG  ),             /* \157 'o', omicron            */
    CENTRY( 'p', CF_MSG  ),             /* \160 'p', pi                 */
    CENTRY( 'q', CF_MSG  ),             /* \161 'q', theta              */
    CENTRY( 'r', CF_MSG  ),             /* \162 'r', rho                */
    CENTRY( 's', CF_MSG  ),             /* \163 's', sigma              */
    CENTRY( 't', CF_MSG  ),             /* \164 't', tau                */
    CENTRY( 'u', CF_MSG  ),             /* \165 'u', upsilon            */
    CENTRY( 'v', CF_MSG  ),             /* \166 'v', digamma            */
    CENTRY( 'w', CF_MSG  ),             /* \167 'w', omega              */
    CENTRY( 'x', CF_MSG  ),             /* \170 'x', chi                */
    CENTRY( 'y', CF_MSG  ),             /* \171 'y', psi                */
    CENTRY( 'z', CF_MSG  ),             /* \172 'z', zeta               */
    CENTRY( NUL, CF_ESC  ),             /* \173 '{', marginalia         */
    CENTRY( NUL, CF_MSG  ),             /* \174 '|', iota subscript     */
    CENTRY( NUL, CF_NORM ),             /* \175 '}'                     */
    CENTRY( NUL, CF_ESC  ),             /* \176 '~', citation record    */
    CENTRY( NUL, CF_NORM ),             /* \177 (DEL)                   */
};


uchar *
betaesc( escc )
uchar  escc;
{
    register short  c;

        switch ( escc )  {

        case  '~':              /* CITATION RECORD                      */
            while ((( c = ssgetc()) != EOF) && ( c != '\n' )) ;
            return( NULL );

        case  '&':              /* BEGIN ROMAN                          */
            while ((( c = ssgetc()) != EOF) && ( c != '$' )) ;
            return( NULL );

        case  '{':              /* MARGINALIA                           */
            while ((( c = ssgetc()) != EOF) && ( c != '}' )) ;
            return( NULL );

        case  '!':              /* SPECIAL CHARS AND LIGATURES          */
            switch( ssgetc() )  {
                case  '1':
                    return( (uchar *) "b" );
                case  '6':
                    return( (uchar *) "ou" );
                default:
                    return( (uchar *) " " );
            }

        case  '-':              /* HYPHENIZATION                        */
            if ( isalpha( c = ssgetc() ))  {
                ssungetc();
                return( (uchar *) "-" );
            }
            else if ( c == '\n' )  return( NULL );
            else  {
                while ((( c = ssgetc()) != EOF) && ( c != '\n' )) ;
                return( NULL );
            }
        }
}
