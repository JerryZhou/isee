#ifndef _IATOMIC_H_
#define _IATOMIC_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* [asf](https://svn.apache.org/repos/asf/avro/trunk/lang/c/src/avro/refcount.h) */
    
/* compare the store with expected, than store the value with desired */
uint32_t iatomiccompareexchange(volatile uint32_t *store, uint32_t expected, uint32_t desired);

/* fetch the old value and store the with add*/
uint32_t iatomicadd(volatile uint32_t *store, uint32_t value);

/* fetch the old value, than do exchange operator */
uint32_t iatomicexchange(volatile uint32_t *store, uint32_t value);

/* atomic increment, return the new value */
uint32_t iatomicincrement(volatile uint32_t *store);

/* atomic decrement, return the new value */
uint32_t iatomicdecrement(volatile uint32_t *store);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif