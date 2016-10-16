#ifndef _IRADIX_H_
#define _IRADIX_H_

#include "foundation/itype.h"
#include "foundation/util/iarraytypes.h"
#include "foundation/util/istring.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* radix unit config */
typedef struct iradixunit {
    const char* name;
    int radix;
}iradixunit;

/* calculating the radix-changing elements 
 * return: iarray<uint64_t> */
iarray *iradixcalc(const iarray *radixs, uint64_t value, size_t depth);
    
/* make a composing string */
istring *iradixcalccompose(const iarray *radixs, const iarray* sizes);
    
/* calcualting the radix-diff-chaning elements with sign at end of sizes
 * return: iarray<uint64_t> */
iarray *iradixdiff(const iarray *radixs, uint64_t lfs, uint64_t rfs, size_t depth);
    
/* make a composing string with suffixs */
istring *iradixdiffcompose(const iarray *radixs, const iarray *sizes, const iarray *suffixs);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IRADIX_H_ */