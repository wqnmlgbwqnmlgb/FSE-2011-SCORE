/* 
 * This file is part of SCORE, which is distributed under the revised
 * BSD license.  A copy of this license can be found in the file LICENSE.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See LICENSE
 * for details.
 */

#ifndef LIBSCORE_SCORE_H__
#define LIBSCORE_SCORE_H__

#include <stdlib.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

/*
 * Type definitions.
 *
 * These macros must be kept in sync with the definitions in base/basic_types.h.
 * We use these obscure MACRO's rather than the definitions in basic_types.h
 * in an attempt to avoid clashing with names in instrumented programs
 * (and also because C does not support namespaces).
 */
#define __SCORE_ID int
#define __SCORE_BRANCH_ID int
#define __SCORE_FUNCTION_ID unsigned int
#define __SCORE_VALUE long long int
#define __SCORE_ADDR unsigned long int

#define __SCORE_OP int
#define __SCORE_TYPE int
#define __SCORE_BOOL unsigned char

/*
 * Constants representing possible C operators.
 */
enum {
  /* binary arithmetic */
  __SCORE_ADD        =  0,
  __SCORE_SUBTRACT   =  1,
  __SCORE_MULTIPLY   =  2,
  __SCORE_DIVIDE     =  3,
  __SCORE_S_DIVIDE   =  4,
  __SCORE_MOD        =  5,
  __SCORE_S_MOD      =  6,
  /* binary bitwise operators */
  __SCORE_SHIFT_L    =  7,
  __SCORE_SHIFT_R    =  8,
  __SCORE_S_SHIFT_R  =  9,
  __SCORE_AND        = 10,
  __SCORE_OR         = 11,
  __SCORE_XOR        = 12,
  /* binary comparison */
  __SCORE_EQ         = 13,
  __SCORE_NEQ        = 14,
  __SCORE_GT         = 15,
  __SCORE_S_GT       = 16,
  __SCORE_LEQ        = 17,
  __SCORE_S_LEQ      = 18,
  __SCORE_LT         = 19,
  __SCORE_S_LT       = 20,
  __SCORE_GEQ        = 21,
  __SCORE_S_GEQ      = 22,
  /* unhandled binary operators */
  __SCORE_CONCRETE   = 23,
  /* unary operators */
  __SCORE_NEGATE     = 24,
  __SCORE_NOT        = 25,
  __SCORE_L_NOT      = 26,
  /* cast */
  __SCORE_CAST       = 27,
  __SCORE_S_CAST     = 28,
};

enum {
  __SCORE_U_CHAR = 0,       __SCORE_CHAR = 1,
  __SCORE_U_SHORT = 2,      __SCORE_SHORT = 3,
  __SCORE_U_INT = 4,        __SCORE_INT = 5,
  __SCORE_U_LONG = 6,       __SCORE_LONG = 7,
  __SCORE_U_LONG_LONG = 8,  __SCORE_LONG_LONG = 9,
  __SCORE_STRUCT = 10,
};

/*
 * Short-cut to indicate that a function should be skipped during
 * instrumentation.
 */
#define __SKIP __attribute__((score_skip))

/*
 * Instrumentation functions.
 *
 * (Could also clone these for each type: uint8, int8, ..., uint64, int64.)
 */
EXTERN void __ScoreInit(__SCORE_ID) __SKIP;
EXTERN void __ScoreLoad(__SCORE_ID, __SCORE_ADDR, __SCORE_TYPE, __SCORE_VALUE) __SKIP;
EXTERN void __ScoreStore(__SCORE_ID, __SCORE_ADDR) __SKIP;
EXTERN void __ScoreClearStack(__SCORE_ID) __SKIP;
EXTERN void __ScoreApply1(__SCORE_ID, __SCORE_OP, __SCORE_TYPE, __SCORE_VALUE) __SKIP;
EXTERN void __ScoreApply2(__SCORE_ID, __SCORE_OP, __SCORE_TYPE, __SCORE_VALUE) __SKIP;
EXTERN void __ScoreBranch(__SCORE_ID, __SCORE_BRANCH_ID, __SCORE_BOOL) __SKIP;
EXTERN void __ScoreCall(__SCORE_ID, __SCORE_FUNCTION_ID) __SKIP;
EXTERN void __ScoreReturn(__SCORE_ID) __SKIP;
EXTERN void __ScoreHandleReturn(__SCORE_ID,  __SCORE_TYPE, __SCORE_VALUE) __SKIP;

/*
 * Functions (macros) for obtaining symbolic inputs.
 */
#define SCORE_unsigned_char(x, name) __ScoreUChar(&x, name)
#define SCORE_unsigned_short(x, name) __ScoreUShort(&x, name)
#define SCORE_unsigned_int(x, name) __ScoreUInt(&x, name)
#define SCORE_char(x, name) __ScoreChar(&x, name)
#define SCORE_short(x, name) __ScoreShort(&x, name)
#define SCORE_int(x, name) __ScoreInt(&x, name)


EXTERN void __ScoreUChar(unsigned char* x, const char *name) __SKIP;
EXTERN void __ScoreUShort(unsigned short* x, const char *name) __SKIP;
EXTERN void __ScoreUInt(unsigned int* x, const char *name) __SKIP;
EXTERN void __ScoreChar(char* x, const char *name) __SKIP;
EXTERN void __ScoreShort(short* x, const char *name) __SKIP;
EXTERN void __ScoreInt(int* x, const char *name) __SKIP;

#endif  /* LIBSCORE_SCORE_H__ */
