#include "foundation/util/iradix.h"


/* calculating the radix-changing elements
 * return: iarray<uint64_t> */
iarray *iradixcalc(const iarray *radixs, uint64_t value, size_t depth) {
    unsigned short idx = 0;
    iarray* sizes = iarraymakeuint64(iarraylen(radixs));
    iarrayadd(sizes, &value);
    
    ilog("total-size %llu\n", value);
    
    /* calc size */
    if (value) do {
        value = iarrayof(sizes, uint64_t, idx) / iarrayof(radixs, iradixunit, idx).radix;
        iarrayappend(sizes, &value, 1); /*idx+1*/
        value = iarrayof(sizes, uint64_t, idx) % iarrayof(radixs, iradixunit, idx).radix;
        iarrayset(sizes, idx, &value);  /*idx*/
        
        ilog("offset[%d] = %llu\n", idx, iarrayof(sizes, uint64_t, idx));
        ilog("offset[%d] = %llu\n", idx+1, iarrayof(sizes, uint64_t, idx+1));
    } while(++idx<iarraylen(radixs) && iarrayof(sizes, uint64_t, idx) > 0 && --depth>0);
    
    /* max unit */
    value = iarrayof(sizes, uint64_t, idx);
    if (value > 0 ) {
        value = (iarrayof(sizes, uint64_t, idx) * iarrayof(radixs, iradixunit, idx-1).radix
                 + iarrayof(sizes, uint64_t, idx-1));
        iarrayset(sizes, idx-1, &value);
    } else if (value == 0) {
        iarrayremove(sizes, iarraylen(sizes)-1); /* remove the last zero */
    }
    return sizes;
}

/* make a composing string */
istring *iradixcalccompose(const iarray *radixs, const iarray* sizes) {
    /* build the size unit string */
    size_t idx = iarraylen(sizes);
    iarray *buf = iarraymakechar(256);
    
    /* calculating */
    if (idx) do {
        if (iarrayof(sizes, uint64_t, idx-1) == 0) {
            continue;
        }
        /* formats */
        istringrawformat(buf, "%I%S", iarrayof(sizes, uint64_t, idx-1),
                         iarrayof(radixs, iradixunit, idx-1));
    } while(--idx>0);
    
    return istringfromraw(buf);
}

/* calcualting the radix-diff-chaning elements with sign at end of sizes
 * sign: 0 == -1, 1 ==> 0, 2 ==> 1
 * return: iarray<uint64_t> */
iarray *iradixdiff(const iarray *radixs, uint64_t lfs, uint64_t rfs, size_t depth) {
    uint64_t sign = lfs > rfs ? 2 : (lfs == rfs ? 1 : 0);
    uint64_t diff = sign > 1 ? lfs - rfs : rfs - lfs;
    iarray *sizes = iradixcalc(radixs, diff, depth);
    iarrayappend(sizes, &sign, 1); /* append the sign to ssize */
    return sizes;
}

/* make a composing string with suffixs */
istring *iradixdiffcompose(const iarray *radixs, const iarray *sizes, const iarray *suffixs) {
    /* build the size unit string */
    size_t idx = iarraylen(sizes);
    iarray *buf = iarraymakechar(256);
    istring *s;
    uint64_t sign = iarrayoflast(sizes, uint64_t);
    icheckretassert(idx>=1, NULL);
    
    /* calculating */
    if (--idx) do {
        if (iarrayof(sizes, uint64_t, idx-1) == 0) {
            continue;
        }
        /* formats */
        istringrawformat(buf, "%I%S", iarrayof(sizes, uint64_t, idx-1),
                         iarrayof(radixs, iradixunit, idx-1));
    } while(--idx>0);
    
    /* suffix */
    if (suffixs) {
        s = iarrayof(suffixs, istring*, sign);
        istringrawformat(buf, "%V", s);
    }
    
    /* raw-to-string */
    return istringfromraw(buf);
}