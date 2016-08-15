#include "foundation/iatomic.h"

#ifdef WIN32
#include <windows.h>
#endif

/* compare the store with expected, than store the value with desired */
uint32_t iatomiccompareexchange(volatile uint32_t *store, uint32_t expected, uint32_t desired) {
#ifdef WIN32
    return _InterlockedCompareExchange((volatile LONG*)store, expected, desired);
#else
    return __sync_val_compare_and_swap_4(store, expected, desired);
#endif
}

/* fetch the old value and store the with add*/
uint32_t iatomicadd(volatile uint32_t *store, uint32_t add) {
#ifdef WIN32
    return _InterlockedExchangeAdd((volatile LONG*)store, add);
#else
    return __sync_add_and_fetch_4(store, add);
#endif
}

/* fetch the old value, than do exchange operator */
uint32_t iatomicexchange(volatile uint32_t *store, uint32_t value) {
#ifdef WIN32
    return _InterlockedExchange((volatile LONG*)store, value);
#else
    return __sync_lock_test_and_set_4(store, value);
#endif
}

/* atomic increment, return the new value */
uint32_t iatomicincrement(volatile uint32_t *store) {
#ifdef WIN32
    return _InterlockedIncrement((volatile LONG*)store);
#else
    return __sync_add_and_fetch_4(store, 1);
#endif
}

uint32_t iatomicdecrement(volatile uint32_t *store) {
#ifdef WIN32
    return _InterlockedDecrement((volatile LONG*)store);
#else
    return __sync_sub_and_fetch_4(store, 1);
#endif
}