/*
 * Copyright Gregory Crane
 * April 1987
 */

/*
 * return vals for gk_strcmp(), gk_strncmp()
 *
 * if you call gk_sprint(a,b),
 * all values express the relationship of string a and string b from
 * the perspective of string a
 */

/*
 * if the two strings differ in alphabetic characters
 * the normal case for two different strings
 */
#define LEXGREATER       1      /* string a is greater */
#define LEXLESS         -1      /* string b is greater */

/*
 * one string is a subset of the other
 * e.g. "pe/mpe" and "pe/mpetai"
 */
#define LEXLONGER        2      /* string a is longer */
#define LEXSHORTER      -2      /* string b is longer */

/* 
 * the strings differ in case
 */
#define CASEGREATER      4      /* string a is upper case, string b lower*/
#define CASELESS        -4      /* string b is upper case, string a lower*/

/*
 * the strings have the same alphabetic characters, but differ in accent
 * 
 * note: accents are compared according to their simple ascii values.
 * no attempt has been made to decide the abstract sort weights of greek
 * diacritics.
 */
#define ACCGREATER       010    /* accent of string a is greater */
#define ACCLESS         -010    /* accent of string b is greater */
