#ifndef _IMAT_H_
#define _IMAT_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/math/ivec.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct imat4 {
    ivec4 cols[4];
}imat4;
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IMAT_H_ */