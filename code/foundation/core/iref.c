#include "foundation/core/iref.h"
#include "foundation/core/iwref.h"
#include "foundation/core/iobj.h"
#include "foundation/core/imeta.h"
#include "foundation/platform/iatomic.h"

/* add reference */
int irefretain(iref *ref) {
#if iithreadsafe
    return iatomicincrement(&ref->_ref);
#else
    return ++ref->ref;
#endif
}

/* release reference */
void irefrelease(iref *ref) {
    /* no any ref, do destrctor */
#if iithreadsafe
    if (iatomicdecrement(&ref->_ref) == 0) {
#else
    if (--ref->_ref == 0) {
#endif
        while (true) {
            /* printf("atomic-after-decrement %p - %d \n", (void*)ref, ref->ref); */
            /* release the hold by wref and ref */
            if (ref->_wref) {
                ref->_wref->_wref = NULL;
                ref->_wref = NULL;
            }
            /* notify the watcher */
            if (ref->_watch) {
                ref->_watch(ref);
            }
            if (ref->_ref != 0) {
                break;
            }
            /* release resources */
            if (ref->_destructor) {
                ref->_destructor(ref);
            }else {
                /* just release memory */
                iobjfree(ref);
            }
            break;
        }
    }
}