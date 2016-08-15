#ifndef _IPLATFORM_H_
#define _IPLATFORM_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* get current microseconds */
int64_t igetcurmicro();

/* get next unique microseconds */
int64_t igetnextmicro();

/* get current milliseconds  */
int64_t igetcurtick();
    
/* sleeping the current thread */
void isleep(unsigned int milliseconds);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /*end of _IPLATFORM_H_*/
