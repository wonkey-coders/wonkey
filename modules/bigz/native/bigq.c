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
 * @file bigq.c
 * @brief provides an implementation of "unlimited-precision"
 * arithmetic for signed rational.
 *
 * Several conventions are used in the commentary:
 * - A "BigQ" is the name for an arbitrary-precision signed rational.
 * - Capital letters (e.g., "Q") are used to refer to the value of BigQs.
 *
 * Rational numbers are stored in their canonical form a/b where a and
 * b are coprime integers (i.e. the only positive integer that
 * divides both of them is 1), and b > 0.
 *
 * @note If any BigQ parameter is passed as BZNULL, function returns BZNULL
 * which should be considered as an error.
 * @version 2.1.0
 * @copyright Eligis, 1992-2023
 * @author C. Jullien
 * $Revision: 394 $
 * $Date: 2023-02-04 15:29:09 +0000 (Sat, 04 Feb 2023) $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if !defined(__BIGQ_H)
#include "./bigq.h"
#endif

/** @cond */
typedef enum {
        BQ_COPY,
        BQ_SET
} BqCreateMode;
/** @endcond */

static BigQ BqCanonicalize(BigQ q);
static BigQ BqCreateInternal(const BigZ n, const BigZ d, BqCreateMode mode);

/**
 * BqCreateInternal. Internally create new BigQ using two BigZ for
 * numerator and denominator.
 * @param [in] n numerator.
 * @param [in] d denominator.
 * @param [in] mode creation mode. BQ_SET uses n and d to build the new BigZ.
 * BZ_COPY makes a copy of n and d.
 * @return a new BigQ.
 * @pre
 * - n in Z
 * - d in (N \ {0})
 */
static BigQ
BqCreateInternal(const BigZ n, const BigZ d, BqCreateMode mode) {
        BigQ  q;
        BigZ cn;
        BigZ cd;

        if ((n == BZNULL) || (d == BZNULL)) {
                return BQNULL;
        }

#if !defined(BQ_NEGATIVE_DENOMINATOR)
        /*
         * By default, when BQ_NEGATIVE_DENOMINATOR is *not* defined,
         * bigq module only accepts strictly positive denominator.
         */
        if (BzGetSign(d) != BZ_PLUS) {
                if (mode == BQ_SET) {
                        BzFree(d);
                        BzFree(n);
                }
                return BQNULL;
        }
#else
        /*
         * Allow denominator to be negative.
         */
        if (BzGetSign(d) == BZ_ZERO) {
                if (mode == BQ_SET) {
                        BzFree(d);
                        BzFree(n);
                }
                return BQNULL;
        }
#endif

        if ((q = (BigQ)BqAlloc()) == 0) {
                return BQNULL;
        }

        BqSetNumerator(q, BZNULL);
        BqSetDenominator(q, BZNULL);

        if (BzGetSign(n) == BZ_ZERO) {
                BigZ zero;
                BigZ one;

                if (mode == BQ_SET) {
                        if (BzToInteger(d) == (BzInt)1) {
                                /*
                                 * n=0, d=1. Already normalised as 0/1.
                                 */
                                BqSetNumerator(q, n);
                                BqSetDenominator(q, d);
                                return q;
                        }
                        /*
                         * Only free denominator as numerator is already 0.
                         */
                        BzFree(d);
                        zero = n;
                } else if ((zero = BzFromInteger((BzInt)0)) == BZNULL) {
                        BqFree(q);
                        return BQNULL;
                }

                if ((one = BzFromInteger((BzInt)1)) == BZNULL) {
                        BzFree(zero);
                        BqFree(q);
                        return BQNULL;
                }

                BqSetNumerator(q, zero);
                BqSetDenominator(q, one);
                return q;
        } else if (mode == BQ_COPY) {
                if ((cn = BzCopy(n)) == BZNULL) {
                        BqFree(q);
                        return BQNULL;
                }

                if ((cd = BzAbs(d)) == BZNULL) {
                        BzFree(cn);
                        BqFree(q);
                        return BQNULL;
                }

                if (BzGetSign(n) != BzGetSign(d)) {
                        BzSetSign(cn, BZ_MINUS);
                }
        } else {
                cn = n;
                cd = d;

                if (BzGetSign(n) != BzGetSign(d)) {
                        BzSetSign(cn, BZ_MINUS);
                }

                BzSetSign(cd, BZ_PLUS);
        }

        if (BzGetSign(n) != BzGetSign(d)) {
                BzSetSign(cn, BZ_MINUS);
        } else {
                BzSetSign(cn, BZ_PLUS);
        }

        BqSetNumerator(q, cn);
        BqSetDenominator(q, cd);

        if (BzLength(cd) != (BigNumLength)1) {
                q = BqCanonicalize(q);
        }

        return q;
}

/**
 * BqCanonicalize q which is physically modified.
 * This function is only called by BqCreateInternal.
 * @param [in,out] q BigQ
 * @return normalized rational.
 * @pre q != BZNULL.
 */
static BigQ
BqCanonicalize(BigQ q) {
        const BigZ n = BqGetNumerator(q);
        const BigZ d = BqGetDenominator(q);
        BigZ       gcd;

        if ((gcd = BzGcd(n, d)) == BZNULL) {
                BqDelete(q);
                return BQNULL;
        }

        if (BzToInteger(gcd) != (BzInt)1) {
                BigZ nn;
                BigZ nd;

                if ((nn = BzDiv(n, gcd)) == BZNULL) {
                        BzFree(gcd);
                        BqDelete(q);
                        return BQNULL;
                }

                if ((nd = BzDiv(d, gcd)) == BZNULL) {
                        BzFree(nn);
                        BzFree(gcd);
                        BqDelete(q);
                        return BQNULL;
                }

                BzFree(d);
                BzFree(n);

                BqSetNumerator(q, nn);
                BqSetDenominator(q, nd);
        }

        BzFree(gcd);

        return q;
}

/*
 * Public interface
 */

/**
 * BqCreate a new rational number.
 * @param [in] n const BigZ numerator.
 * @param [in] d const BigZ
 * @return BigQ
 */
BigQ
BqCreate(const BigZ n, const BigZ d) {
        return BqCreateInternal(n, d, BQ_COPY);
}

/**
 * BqDelete q. It does nothing if q == BQNULL.
 * @param [in] q BigQ
 */
void
BqDelete(BigQ q) {
        if (q == BQNULL) {
                return;
        } else {
                const BigZ n = BqGetNumerator(q);
                const BigZ d = BqGetDenominator(q);

                if (n != BZNULL) {
                        BzFree(n);
                }
                if (d != BZNULL) {
                        BzFree(d);
                }
                BqFree(q);
        }
}

/**
 * BqAdd.
 * Create a new canonicalized BigQ: a + b.
 * @param [in] a left hand side BigQ
 * @param [in] b right hand side BigQ
 * @return BigQ. If either a or b is BQNULL, returns BQNULL.
 */
BigQ
BqAdd(BigQ a, BigQ b) {
        if (a == BQNULL || b == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an = BqGetNumerator(a);
                const BigZ ad = BqGetDenominator(a);
                const BigZ bn = BqGetNumerator(b);
                const BigZ bd = BqGetDenominator(b);
                BigZ n;
                BigZ d;

                if (BzCompare(ad, bd) == BZ_EQ) {
                        /*
                         * Easy, same denominator. Only add numerators.
                         */
                        if ((n = BzAdd(an, bn)) == BZNULL) {
                                return BQNULL;
                        }

                        if ((d = BzCopy(ad)) == BZNULL) {
                                BzFree(n);
                                return BQNULL;
                        }

                        return BqCreateInternal(n, d, BQ_SET);
                } else {
                        BigZ tmp1;
                        BigZ tmp2;

                        if ((tmp1 = BzMultiply(an, bd)) == BZNULL) {
                                return BQNULL;
                        }

                        if ((tmp2 = BzMultiply(ad, bn)) == BZNULL) {
                                BzFree(tmp1);
                                return BQNULL;
                        }

                        n = BzAdd(tmp1, tmp2);

                        BzFree(tmp1);
                        BzFree(tmp2);

                        if (n == BZNULL) {
                                return BQNULL;
                        }

                        if ((d = BzMultiply(ad, bd)) == BZNULL) {
                                BzFree(n);
                                return BQNULL;
                        }

                        return BqCreateInternal(n, d, BQ_SET);
                }
        }
}

/**
 * BqSubtract.
 * Create a new canonicalized BigQ: a - b.
 * @param [in] a left hand side BigQ
 * @param [in] b right hand side BigQ
 * @return BigQ. If either a or b is BQNULL, returns BQNULL.
 */
BigQ
BqSubtract(BigQ a, BigQ b) {
        if (a == BQNULL || b == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an = BqGetNumerator(a);
                const BigZ ad = BqGetDenominator(a);
                const BigZ bn = BqGetNumerator(b);
                const BigZ bd = BqGetDenominator(b);
                BigZ n;
                BigZ d;

                if (BzCompare(ad, bd) == BZ_EQ) {
                        /*
                         * Easy, same denominator. Only subtract numerators.
                         */
                        if ((n = BzSubtract(an, bn)) == BZNULL) {
                                return BQNULL;
                        }

                        if ((d = BzCopy(ad)) == BZNULL) {
                                BzFree(n);
                                return BQNULL;
                        }

                        return BqCreateInternal(n, d, BQ_SET);
                } else {
                        BigZ tmp1;
                        BigZ tmp2;

                        if ((tmp1 = BzMultiply(an, bd)) == BZNULL) {
                                return BQNULL;
                        }

                        if ((tmp2 = BzMultiply(ad, bn)) == BZNULL) {
                                BzFree(tmp1);
                                return BQNULL;
                        }

                        if ((n = BzSubtract(tmp1, tmp2)) == BZNULL) {
                                BzFree(tmp2);
                                BzFree(tmp1);
                                return BQNULL;
                        }

                        d = BzMultiply(ad, bd);

                        BzFree(tmp2);
                        BzFree(tmp1);

                        if (d == BZNULL) {
                                BzFree(n);
                                return BQNULL;
                        }

                        return BqCreateInternal(n, d, BQ_SET);
                }
        }
}

/**
 * BqMultiply.
 * Create a new canonicalized BigQ: a * b.
 * @param [in] a left hand side BigQ
 * @param [in] b right hand side BigQ
 * @return BigQ. If either a or b is BQNULL, returns BQNULL.
 */
BigQ
BqMultiply(BigQ a, BigQ b) {
        if (a == BQNULL || b == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an = BqGetNumerator(a);
                const BigZ ad = BqGetDenominator(a);
                const BigZ bn = BqGetNumerator(b);
                const BigZ bd = BqGetDenominator(b);
                BigZ n;
                BigZ d;

                if ((n = BzMultiply(an, bn)) == BZNULL) {
                        return BQNULL;
                }

                if ((d = BzMultiply(ad, bd)) == BZNULL) {
                        BzFree(n);
                        return BQNULL;
                }

                return BqCreateInternal(n, d, BQ_SET);
        }
}

/**
 * BqDiv.
 * Create a new canonicalized BigQ: a / b.
 * @param [in] a left hand side BigQ
 * @param [in] b right hand side BigQ
 * @return BigQ. If either a or b is BQNULL, returns BQNULL.
 */
BigQ
BqDiv(BigQ a, BigQ b) {
        if (a == BQNULL || b == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an = BqGetNumerator(a);
                const BigZ ad = BqGetDenominator(a);
                const BigZ bn = BqGetNumerator(b);
                const BigZ bd = BqGetDenominator(b);
                BigZ n;
                BigZ d;

                if ((n = BzMultiply(an, bd)) == BZNULL) {
                        return BQNULL;
                }

                if ((d = BzMultiply(ad, bn)) == BZNULL) {
                        BzFree(n);
                        return BQNULL;
                }

                if (BzGetSign(n) != BzGetSign(d)) {
                        BzSetSign(n, BZ_MINUS);
                } else {
                        BzSetSign(n, BZ_PLUS);
                }

                BzSetSign(d, BZ_PLUS);

                return BqCreateInternal(n, d, BQ_SET);
        }
}

/**
 * BqCompare.
 * Compare a and b. It returns BQ_EQ (0) if a == b, BQ_LZ (-1) if a < b and
 * BQ_GT (1) if a > b. When a and b have a different denominator, two BigZ
 * are internally created which may fail. In this case BQ_ERR (100) is returned.
 * This may fool functions like qsort waiting for negative, 0 or positive value.
 * @param [in] a left hand side BigQ
 * @param [in] b right hand side BigQ
 * @return BqCmp. If either a or b is BQNULL, returns BQ_ERR.
 */
BqCmp
BqCompare(BigQ a, BigQ b) {
        if (a == BQNULL || b == BQNULL) {
                return BQ_ERR;
        } else {
                const BigZ an = BqGetNumerator(a);
                const BigZ ad = BqGetDenominator(a);
                const BigZ bn = BqGetNumerator(b);
                const BigZ bd = BqGetDenominator(b);
                BigZ tmp1;
                BigZ tmp2;
                BzCmp cmp;

                if (BzGetSign(an) != BzGetSign(bn)) {
                        /*
                         * Sign differs, easy case!
                         */
                        if (BzGetSign(an) == BZ_MINUS) {
                                return BQ_LT;
                        } else if (BzGetSign(an) == BZ_ZERO
                                    && BzGetSign(bn) == BZ_PLUS) {
                                return BQ_LT;
                        } else {
                                return BQ_GT;
                        }
                } else if (BzCompare(ad, bd) == BZ_EQ) {
                        /*
                         * Easy, same denominator. Only compare numerators.
                         * This works also if a == b == 0 because a and b
                         * are canonicalized and their denominator is 1.
                         */
                        cmp = BzCompare(an, bn);
                } else {
                        if ((tmp1 = BzMultiply(an, bd)) == BZNULL) {
                                return BQ_ERR;
                        }

                        if ((tmp2 = BzMultiply(ad, bn)) == BZNULL) {
                                BzFree(tmp1);
                                return BQ_ERR;
                        }

                        cmp = BzCompare(tmp1, tmp2);

                        BzFree(tmp2);
                        BzFree(tmp1);
                }

                switch (cmp) {
                case BZ_LT:
                        return BQ_LT;
                case BZ_GT:
                        return BQ_GT;
                case BZ_EQ:
                default:
                        return BQ_EQ;
                }
        }
}

/**
 * BqNegate.
 * Create a new canonicalized BigQ: -a.
 * @param [in] a BigQ
 * @return BigQ. If a is BQNULL, returns BQNULL.
 */
BigQ
BqNegate(BigQ a) {
        if (a == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an  = BqGetNumerator(a);
                const BigZ ad  = BqGetDenominator(a);
                BigQ       res = BqCreateInternal(an, ad, BQ_COPY);

                if (res == BQNULL) {
                        return res;
                }

                switch (BzGetSign(an)) {
                case BZ_MINUS:
                        BzSetSign(BqGetNumerator(res), BZ_PLUS);
                        return res;
                case BZ_PLUS:
                        BzSetSign(BqGetNumerator(res), BZ_MINUS);
                        return res;
                case BZ_ZERO:
                default:
                        return res;
                }
        }
}

/**
 * BqAbs.
 * Create a new canonicalized BigQ: |a|.
 * @param [in] a BigQ
 * @return BigQ
 */
BigQ
BqAbs(BigQ a) {
        if (a == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an  = BqGetNumerator(a);
                const BigZ ad  = BqGetDenominator(a);
                BigQ       res = BqCreateInternal(an, ad, BQ_COPY);

                if (res == BQNULL) {
                        return res;
                }

                if (BzGetSign(BqGetNumerator(res)) == BZ_MINUS) {
                        /*
                         * Force positive sign only when a res is negative.
                         */
                        BzSetSign(BqGetNumerator(res), BZ_PLUS);
                }

                return res;
        }
}

/**
 * BqInverse.
 * Create a new canonicalized BigQ: an/ad => ad/an. The result sign is the sign
 * of an.
 * @param [in] a BigQ
 * @return BigQ. If a is BQNULL, returns BQNULL.
 */
BigQ
BqInverse(BigQ a) {
        if (a == BQNULL) {
                return BQNULL;
        } else {
                const BigZ an = BqGetNumerator(a);
                const BigZ ad = BqGetDenominator(a);

                return BqCreateInternal(ad, an, BQ_COPY);
        }
}

/*
 * Define QNaN as an array (not a pointer!!!) to let sizeof returns
 * the null terminating string length (including '\000').
 */

static const char BqNaN[] = "#.QNaN"; /* it includes NUL terminated char */

/**
 * BqToStringBufferExt.
 * Returns a pointer to a string that represents Q number in the specified
 * base.  Assumes BZ_MIN_BASE <= base <= BZ_MAX_BASE.  If optional
 * buffer is supplied, len is a pointer of this buffer size.  If there
 * is enough room to print the number buf is used otherwise function
 * returns NULL and len contains the required size.  If buf is passed
 * as NULL, this string is allocated on the heap, so it must be
 * desallocated by the user.
 * @param [in] q BigQ
 * @param [in] base BigNumDigit
 * @param [in] sign flag. When set to BQ_FORCE_SIGN and q != 0,
 *             a sign +/- is always present.
 * @param [out] buf output buffer. When passed NULL, buffer is allocated.
 * @param [in, out] buflen on input it contains the maximal buffer length. When
 * buffer is too small to represent this BigQ number, function returns
 * NULL and buflen is set the the required buffer size.
 * @param [out] slen when not NULL, slen is a pointer of size_t which contains
 * the actual string length of q.
 * @return NUL terminated string
 */
BzChar *
BqToStringBufferExt(BigQ q,
                    BigNumDigit base,
                    int sign,
                    BzChar *buf,
                    size_t *buflen,
                    size_t *slen) {
        BzChar *n;
        BzChar *d;
        BzChar *res;
        size_t len;
        int    i;

        if ((buf != (BzChar *)NULL) && (buflen == (size_t *)NULL)) {
                /*
                 * A buffer is passed without its associated length.
                 */
                return (BzChar *)NULL;
        } else if (q == BQNULL) {
                len = sizeof(BqNaN); /* works because BqNaN is an array */

                if (buf != (BzChar *)NULL) {
                        if (*buflen >= len) {
                                res = buf;
                        } else {
                                res = (BzChar *)NULL;
                        }
                } else {
                        /*
                         * contract is to allocate a new string, even
                         * for #.QNaN error.
                         */
                        res = (BzChar *)BzStringAlloc(len);
                }

                if (slen != (size_t *)NULL) {
                        *slen = len;
                }

                if (res != (BzChar *)NULL) {
                        for (i = 0; BqNaN[i] != '\000'; ++i) {
                                res[i] = (BzChar)BqNaN[i];
                        }
                        res[i] = (BzChar)'\000';
                }

                return res;
        } else if (BzLength(BqGetDenominator(q)) == (BigNumLength)1) {
                /*
                 * n/1 is printed just n
                 */
                return BzToStringBufferExt(BqGetNumerator(q),
                                           base,
                                           sign,
                                           buf,
                                           buflen,
                                           slen);
        } else if (buf != (BzChar *)NULL) {
                /*
                 * Get numerator string.
                 */
                n = BzToString(BqGetNumerator(q), base, sign);

                if (n == (BzChar *)NULL) {
                        return n;
                }

                /*
                 * Get denominator string.
                 */
                d = BzToString(BqGetDenominator(q), base, BZ_DEFAULT_SIGN);

                if (d == (BzChar *)NULL) {
                        BzFreeString(n);
                        return d;
                }

                /*
                 * Compute total length
                 */
                len = BzStrLen(n) + BzStrLen(d) + 1; /* +1 for '/' */

                if (slen != (size_t *)NULL) {
                        *slen = len;
                }

                res = &buf[0];

                /*
                 * catenate n/d in return buffer.
                 */

                for (i = 0; n[i] != (BzChar)'\000'; ++i) {
                        *res++ = n[i];
                }

                *res++ = (BzChar)'/';

                for (i = 0; d[i] != (BzChar)'\000'; ++i) {
                        *res++ = d[i];
                }

                *res++ = (BzChar)'\000';

                BzFreeString(d);
                BzFreeString(n);

                return &buf[0];
        } else {
                /*
                 * Get numerator string.
                 */
                n = BzToString(BqGetNumerator(q), base, sign);

                if (n == (BzChar *)NULL) {
                        return n;
                }

               /*
                 * Get denominator string.
                 */
                d = BzToString(BqGetDenominator(q), base, BQ_DEFAULT_SIGN);

                if (d == (BzChar *)NULL) {
                        BzFreeString(n);
                        return d;
                }

                /*
                 * Compute total length
                 */
                len = BzStrLen(n) + BzStrLen(d) + 1; /* +1 for '/' */

                /*
                 * Alloc result string.
                 */
                res = (BzChar *)BzStringAlloc(len + 1); /* +1 for nul */

                if (slen != (size_t *)NULL) {
                        *slen = len;
                }

                /*
                 * catenate n/d in return buffer.
                 */

                if (res != (BzChar *)NULL) {
                        int pos = 0;

                        for (i = 0; n[i] != (BzChar)'\000'; ++i) {
                                res[pos++] = n[i];
                        }

                        res[pos++] = (BzChar)'/';

                        for (i = 0; d[i] != (BzChar)'\000'; ++i) {
                                res[pos++] = d[i];
                        }

                        res[pos] = (BzChar)'\000';
                }

                BzFreeString(d);
                BzFreeString(n);

                return res;
        }
}

/**
 * BqToStringBuffer.
 * Returns a pointer to a string that represents Q number in the specified
 * base.  Assumes BZ_MIN_BASE <= base <= BZ_MAX_BASE.  If optional
 * buffer is supplied, len is a pointer of this buffer size.  If there
 * is enough room to print the number buf is used otherwise function
 * returns NULL and len contains the required size.  If buf is passed
 * as NULL, this string is allocated on the heap, so it must be
 * desallocated by the user.
 * @param [in] q BigQ
 * @param [in] base BigNumDigit
 * @param [in] sign flag. When set to BQ_FORCE_SIGN and q != 0,
 *             a sign +/- is always present.
 * @param [out] buf output buffer
 * @param [in, out] buflen buffer length
 * @return NUL terminated string
 */
BzChar *
BqToStringBuffer(BigQ q,
                 BigNumDigit base,
                 int sign,
                 BzChar *buf,
                 size_t *buflen) {
        return BqToStringBufferExt(q,
                                   base,
                                   sign,
                                   buf,
                                   buflen,
                                   (size_t *)0);
}

/**
 * BqToString.
 * Convert q to string. The result string is allocated by BzStringAlloc
 * and must be free by caller using BzFreeString.
 * When q is BQNULL, it returns "#.QNaN".
 * @param [in] q BigQ.
 * @param [in] sign flag. When set to BQ_FORCE_SIGN and q != 0,
 *             a sign +/- is always present.
 * @return BzChar string.
 * @see BqToStringBufferExt for more options.
 */
BzChar *
BqToString(BigQ q, int sign) {
        return BqToStringBufferExt(q,
                                   (BigNumDigit)10,
                                   sign,
                                   (BzChar *)NULL,
                                   (size_t *)NULL,
                                   (size_t *)NULL);
}

/**
 * BqFromString.
 * Create a new BigQ from string.
 * It returns BQNULL is s does not represent a valid rational number or if
 * denominator is not a strictly positive number. The new rational is
 * returned in its canonicalized form (e.g. "3/6" => 1/2).
 * @param [in] s const BzChar 
 * @param [in] base int in [1 .. 36].
 * @return BigQ. If s is NULL or the empty string "", returns BQNULL.
 */
BigQ
BqFromString(const BzChar *s, int base) {
        BigZ n;
        BigZ d;
        BigQ q;
        const BzChar *p;

        if (s == (const BzChar *)NULL || *s == (BzChar)0) {
                return BQNULL;
        }

        /*
         * Throw away any initial space
         */

        while ((*s == (BzChar)' ')
               || (*s == (BzChar)'\t')
               || (*s == (BzChar)'\n')
               || (*s == (BzChar)'\r')) {
                s++;
        }

        /*
         * search for '/'
         */

        p = s;

        if (*p == (BzChar)'+' || *p == (BzChar)'-') {
                ++p;
                if ((*p == (BzChar)'+') || (*p == (BzChar)'-')) {
                        /*
                         * optional + or - must be unique and already skipped.
                         */
                        return BQNULL;
                }
        }

        if (*p == (BzChar)0) {
                return BQNULL;
        }

        while (*p != (BzChar)'\000') {
                if (*p == (BzChar)'/') {
                        break;
                } else {
                        ++p;
                }
        }

        if (*p == (BzChar)'\000') {
                /*
                 * simply an integer in Z (no denominator).
                 */
                n = BzFromString(s, (BigNumDigit)base, BZ_UNTIL_SPACE);
                if (n == BZNULL) {
                        return BQNULL;
                }

                d = BzFromInteger((BzInt)1);
                if (d == BZNULL) {
                        BzFree(n);
                        return BQNULL;
                }

                q = BqCreateInternal(n, d, BQ_SET);
                return q;
        } else {
                ++p; /* skip slash */

                if ((*p == (BzChar)'+')
                    || (*p == (BzChar)'-')
                    || (*p == (BzChar)' ')) {
                        /*
                         * Denominator is always positive with no sign and
                         * must follow without spaces.
                         */
                        return BQNULL;
                }

                n = BzFromString(s, (BigNumDigit)base, BZ_UNTIL_SLASH);
                if (n == BZNULL) {
                        return BQNULL;
                }

                d = BzFromString(p, (BigNumDigit)base, BZ_UNTIL_SPACE);
                if (d == BZNULL) {
                        BzFree(n);
                        return BQNULL;
                }

                q = BqCreateInternal(n, d, BQ_SET);
                return q;
        }
}

/**
 * BqFromLongDouble.
 * Find rational approximation to given real number (Farey's method).
 * @param [in] num long double.
 * @param [in] maxd maximal denominator value.
 * @return BigQ approximation.
 */
BigQ
BqFromLongDouble(BzLDouble num, BzInt maxd) {
        BzInt   ln = (BzInt)0;  /* lower value = 0/1 */
        BzInt   ld = (BzInt)1;
        BzInt   un = (BzInt)1;  /* upper value = 1/0 = oo */
        BzInt   ud = (BzInt)0;
        BzInt   rn = (BzInt)1;
        BzInt   rd = (BzInt)0;
        BigZ    n;
        BigZ    d;
        BigQ    q;
        int     sign;

        /*
         * See: http://en.wikipedia.org/wiki/Farey_series
         *      http://wiki.cs.princeton.edu/index.php/Rational.ck
         */

        if (num < (BzLDouble)0.0) {
                sign = -1;
                num *= (BzLDouble)-1.0;
        } else {
                sign = 1;
        }

        for (;;) {
                const BzInt mn = ln + un;
                const BzInt md = ld + ud;

                if ((num * (BzLDouble)md) > (BzLDouble)mn) {
                        if (maxd < md) {
                                /*
                                 * return upper.
                                 */
                                rn = un;
                                rd = ud;
                                break;
                        } else {
                                /*
                                 * set lower to median and continue
                                 */
                                ln = mn;
                                ld = md;
                                continue;
                        }
                } else if ((num * (BzLDouble)md) == (BzLDouble)mn) {
                        if (maxd >= md) {
                                /*
                                 * return median.
                                 */
                                rn = mn;
                                rd = md;
                                break;
                        } else if (ld < ud) {
                                /*
                                 * return lower.
                                 */
                                rn = ln;
                                rd = ld;
                                break;
                        } else {
                                /*
                                 * return upper.
                                 */
                                rn = un;
                                rd = ud;
                                break;
                        }
                } else {
                        if (maxd < md) {
                                /*
                                 * return lower.
                                 */
                                rn = ln;
                                rd = ld;
                                break;
                        } else {
                                /*
                                 * set lower to median and continue
                                 */
                                un = mn;
                                ud = md;
                                continue;
                        }
                }
        }

        if ((n = BzFromInteger(sign * rn)) == BZNULL) {
                return BQNULL;
        }

        if ((d = BzFromInteger(rd)) == BZNULL) {
                BzFree(n);
                return BQNULL;
        }

        q = BqCreateInternal(n, d, BQ_SET);

        return q;
}

/**
 * BqFromDouble.
 * Find rational approximation to given real number (Farey's method).
 * @param [in] num double.
 * @param [in] maxd maximal denominator value.
 * @return BigQ approximation.
 */
BigQ
BqFromDouble(double num, BzInt maxd) {
        return BqFromLongDouble((BzLDouble)num, maxd);
}

#if defined(isnan)
/*
 * isnan exists since C99, otherwise (x != x) should work the same.
 * It is said that "NaN values never compare equal to themselves or to
 * other NaN values."
 */
#define BqIsNan(x) (x != x) /* isnan(x) */
#else
#define BqIsNan(x) (x != x)
#endif

/**
 * BqToLongDouble.
 * Convert q to a long double approximation.
 * @param [in] q BigQ
 * @return BigQ. If q == BQNULL and if the implementation supports quiet NaNs
 * it retruns NAN (as defined in math.h). Otherwise it returns 0.0.
 */
BzLDouble
BqToLongDouble(BigQ q) {
        if (q == BQNULL) {
#if defined(NAN)
                return (BzLDouble)NAN;
#else
                return ((BzLDouble)0/(BzLDouble)0);
#endif
        } else {
                BzLDouble res;

                res = BzToLongDouble(BqGetNumerator(q))
                       / BzToLongDouble(BqGetDenominator(q));

                if (BqIsNan(res)) {
                        /*
                         * Naive code above does not work because numerator
                         * and/or denominator is too big to be converted
                         * to (long?) double, try harder as the expected
                         * result may be well below max (long?) double.
                         * 
                         * (defun rational-to-float (x)
                         *    (let ((zdiv  (ash 1 52))
                         *          (zval  nil)
                         *          (qtmp  nil)
                         *          (ztmp  nil)
                         *          (dres  nil))
                         *         (setf zval (floor (numerator x)
                         *                           (denominator x)))
                         *         (setf qtmp (* (- x zval) zdiv))
                         *         (setf ztmp (floor (numerator qtmp)
                         *                           (denominator qtmp)))
                         *         (setf qtmp (/ ztmp zdiv))
                         *         (setf dres (+ (float zval) (float qtmp)))
                         *         dres))
                         */
                        BigZ zone;
                        BigZ zdiv;
                        BigQ qdiv;
                        BigQ qtmp1;

                        zone = BzFromInteger((BzInt)1);
                        zdiv = BzAsh(zone, 52); /* mantissa is on 53 bits */
                        qdiv = BqCreate(zdiv, zone);

                        {
                          BigZ zfloor;
                          BigQ qfloor;

                          zfloor = BzFloor(BqGetNumerator(q),
                                           BqGetDenominator(q));
                          qfloor = BqCreate(zfloor, zone);
                          res    = BzToLongDouble(zfloor);
                          qtmp1  = BqSubtract(q, qfloor);

                          BqFree(qfloor);
                          BzFree(zfloor);
                        }

                        {
                          BigQ qtmp2;

                          qtmp2 = BqMultiply(qtmp1, qdiv);
                          BqFree(qtmp1);
                          {
                            BigZ ztmp;

                            ztmp  = BzFloor(BqGetNumerator(qtmp2),
                                            BqGetDenominator(qtmp2));
                            qtmp1 = BqCreate(ztmp, zdiv);
                            res  += BqToLongDouble(qtmp1);

                            BqFree(qtmp1);
                            BzFree(ztmp);
                          }
                          BqFree(qtmp2);
                        }

                        BqFree(qdiv);
                        BzFree(zdiv);
                        BzFree(zone);
                }

                return res;
        }
}

/**
 * BqToDouble.
 * Convert q to a double approximation.
 * @param [in] q BigQ
 * @return BigQ. If q == BQNULL and if the implementation supports quiet NaNs
 * it retruns NAN (as defined in math.h). Otherwise it returns 0.0.
 */
double
BqToDouble(BigQ q) {
        return (double)BqToLongDouble(q);
}

/**
 * BqHash
 * The hash value of n/q is computed as hash(n) + ~hash(q).
 * @param [in] q BigQ
 * @return BzUint hash value
 */
BzUInt
BqHash(BigQ q) {
        const BigZ n = BqGetNumerator(q);
        const BigZ d = BqGetDenominator(q);

        return BzHash(n) + ~BzHash(d);
}
