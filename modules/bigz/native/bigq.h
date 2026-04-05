/*
 * Simplified BSD License
 *
 * Copyright (c) 1992-2023, Eligis
 * All rights reserved.
 *
 * Redistribution and  use in  source and binary  forms, with  or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * o Redistributions  of  source  code must  retain  the  above copyright
 *   notice, this list of conditions and the following disclaimer.
 * o Redistributions  in  binary form  must reproduce the above copyright
 *   notice, this list of conditions and  the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE  IS PROVIDED BY  THE COPYRIGHT HOLDERS  AND CONTRIBUTORS
 * "AS  IS" AND  ANY EXPRESS  OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE  ARE DISCLAIMED. IN NO EVENT  SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES (INCLUDING,  BUT  NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS  INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF  LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY,  OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING  IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file bigq.h
 * @brief Types and structures for clients of BigQ.
 * @version 2.1.0
 * @copyright Eligis, 1992-2023
 * @author C. Jullien
 * $Revision: 394 $
 * $Date: 2023-02-04 15:29:09 +0000 (Sat, 04 Feb 2023) $
 */

#if !defined(__BIGQ_H)
#define __BIGQ_H

#if !defined(__BIGZ_H)
#include "./bigz.h"
#endif

#if defined(__cplusplus)
extern  "C"     {
#endif

/** @cond */
#define BQ_PURE_FUNCTION                BN_PURE_FUNCTION
#define BQ_CONST_FUNCTION               BN_CONST_FUNCTION
/** @endcond */

/*
 * BigQ.h: Types and structures for clients of BigQ
 */

/**
 * BqToString and related functions add sign only when number is negative ('-').
 */
#define BQ_DEFAULT_SIGN                 BZ_DEFAULT_SIGN

/**
 * Force BqToString to always add a sign [+/-] when number is not 0.
 */
#define BQ_FORCE_SIGN                   BZ_FORCE_SIGN

/**
 * BigQ compare result
 */
typedef enum {
        /** Less than value (-1). */
        BQ_LT    = BN_LT,
        /** Equal than == value (0). */
        BQ_EQ    = BN_EQ,
        /** Greater than comparison value (1). */
        BQ_GT    = BN_GT,
        /** Rerror */
        BQ_ERR   = 100
} BqCmp;

/** @cond */
/**
 * BigQ number is a pair of two bignums (numerator / denominator).
 * The BigQ sign is the sign of numerator, denominator is always greater than
 * 0.
 */
typedef struct {
        /** numerator, a signed BigZ. */
        BigZ N;
        /** denumerator, a strictly positive unsigned BigZ. */
        BigZ D;
} BigQStruct;

typedef BigQStruct *                    __BigQ;

#if !defined(BQ_RATIONAL_TYPE)
#define BQ_RATIONAL_TYPE
typedef const BigQStruct *              BigQ;
#endif
/** @endcond */

#if !defined(__EXTERNAL_BIGQ_MEMORY)
/**
 * User overloadable macro that gets native BigQ implementation from
 * a high level object (for example managed in C++ or Lisp).
 */
#define __toBqObj(q)                    ((__BigQ)q)
/**
 * NULL BigQ.
 */
#define BQNULL                          ((BigQ)0)
/**
 * User overloadable macro called to allocate size bytes to store a BigQ.
 */
#define BqAlloc()                       malloc(sizeof(BigQStruct))
/**
 * User overloadable macro called to free a BigQ allocated by BqAlloc.
 */
#define BqFree(q)                       free((void *)q) /* free(__toBqObj(q)) */
/**
 * Get BigQ numerator.
 */
#define BqGetNumerator(q)               (__toBqObj(q)->N)
/**
 * Get BigQ denominator.
 */
#define BqGetDenominator(q)             (__toBqObj(q)->D)
/**
 * Set BigQ numerator.
 */
#define BqSetNumerator(q, n)            (__toBqObj(q)->N = (n))
/**
 * Set BigQ denominator.
 */
#define BqSetDenominator(q, d)          (__toBqObj(q)->D = (d))
#endif

/*
 * functions of bigq.c
 */

extern BqCmp     BqCompare(BigQ a, BigQ b) BQ_PURE_FUNCTION;
extern BzChar *  BqToString(BigQ q, int sign);
extern BzChar *  BqToStringBuffer(BigQ q, BigNumDigit base, int sign, /*@null@*/ BzChar *buf, /*@null@*/ size_t *buflen);
extern BzChar *  BqToStringBufferExt(BigQ q, BigNumDigit base, int sign, /*@null@*/ BzChar *buf, /*@null@*/ size_t *buflen, /*@null@*/ size_t *slen);
extern BigQ      BqCreate(const BigZ n, const BigZ d);
extern BigQ      BqFromDouble(double num, BzInt maxd);
extern BigQ      BqFromLongDouble(BzLDouble num, BzInt maxd);
extern BigQ      BqFromString(const BzChar *s, int base);
extern double    BqToDouble(BigQ a);
extern BzLDouble BqToLongDouble(BigQ a);
extern void      BqDelete(BigQ a);

extern BigQ   BqAbs(BigQ a);
extern BigQ   BqAdd(BigQ a, BigQ b);
extern BigQ   BqDiv(BigQ a, BigQ b);
extern BigQ   BqInverse(BigQ a);
extern BigQ   BqMultiply(BigQ a, BigQ b);
extern BigQ   BqNegate(BigQ a);
extern BigQ   BqSubtract(BigQ a, BigQ b);
extern BzUInt BqHash(BigQ z);

#if 0
extern BzChar * BqToStringBuffer(BigQ q, int sign, BzChar *buf, size_t *len);
#endif

#if defined(__cplusplus)
}
#endif

#endif  /* __BIGQ_H */
