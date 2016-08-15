#ifndef _IMEMORYSTATISTICS_H_
#define _IMEMORYSTATISTICS_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* memory statistics */
typedef struct imemorystatistics {
    int64_t current;
    int64_t alloced;
    int64_t freed;
}imemorystatistics;
    
/*Hepler Macro for log*/
#define __istatis_format "alloc: %9lld, free: %9lld, hold: %9lld"
#define __istatis_value(statis) (statis)->alloced,(statis)->freed,(statis)->current

/* memory-behavior: alloc */
void imemorystatisbehavior_alloc(imemorystatistics *statis, size_t size);
/* memory-behavior: free */
void imemorystatisbehavior_free(imemorystatistics *statis, size_t size);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
    
#endif /*end of _IMEMORYSTATISTICS_H_*/
