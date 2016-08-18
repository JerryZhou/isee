#ifndef _ISIZE_H_
#define _ISIZE_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* size ireal */
typedef struct isize {
    ireal w, h;
}isize;

/* size int */
typedef struct isizei {
    int w, h;
}isizei;
    
/* isize change to isizei */
isizei isize2i(isize s);

/* isize change to isizei */
isize isizei2(isizei s);
    
/* scale */
isize isizescale(isize s, ireal scale);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _ISIZE_H_ */