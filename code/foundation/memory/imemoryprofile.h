
#ifndef _IMEMORYPROFILE_H
#define _IMEMORYPROFILE_H

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* clear all the cached-memory */
void imemoryglobalclear();

/* current global memory alloced */
int64_t imemoryglobalalloc();

/* current global memory freed */
int64_t imemoryglobalfree();
    
/* current global memory used */
int64_t imemoryglobaluse();

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* imemoryprofile_h */
