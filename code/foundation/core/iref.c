#include "foundation/core/iref.h"
#include "foundation/core/iwref.h"
#include "foundation/core/iobj.h"
#include "foundation/core/imeta.h"
#include "foundation/platform/iatomic.h"
#include "foundation/core/iobjcache.h"

/* inner destructor */
enum {
    __iRef_Flag_InDestructor = 1<<5,
};

/* make a new iref with meta-index */
iref* irefmalloc(int index) {
    const imeta *meta = imetaget(index);
    iref *ref = (iref*)(imetacalloc(meta));
    return irefassistretain(ref);
}

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
    irefwatcher *watcher = NULL;
    const imeta *meta = iobjgetmeta(ref);
    
#if iithreadsafe
    if (iatomicdecrement(&ref->_ref) == 0) {
#else
    if (--ref->_ref == 0) {
#endif
        while (true) {
            /* for - loop: destructor */
            if (iflag_is(ref->_flag, __iRef_Flag_InDestructor)) {
                ilog("##[iref]## Loop Destructor-Happend-For: "__imeta_format"\n", __imeta_value(meta));
                break;
            }
            while ( iatomiccompareexchange(&ref->_flag, 0, __iRef_Flag_InDestructor) != 0) {
                ilog("##[iref]## Loop Setting Flag-Destructor : "__imeta_format"\n", __imeta_value(meta));
            }
            /* printf("atomic-after-decrement %p - %d \n", (void*)ref, ref->ref); */
            /* release the hold by wref and ref */
            if (ref->_wref) {
                ref->_wref->_wref = NULL;
                ref->_wref = NULL;
            }
            /* notify the watcher */
            watcher = icast(irefwatcher, iwrefstrong(ref->_watcher));
            if (watcher) {
                /* watch ref change */
                watcher->watch(watcher, ref);
                /* release the watcher */
                irelease(watcher);
            }
            if (ref->_ref != 0) {
                /* restore the default flag to zero */
                iatomicexchange(&ref->_flag, 0);
                break;
            }
            /* release the _watcher */
            iwassign(ref->_watcher, NULL);
            
            /*call constructor and release the memory */
            iobjfree(ref);
            break;
        }
    }
}

/* return the ref self and retain it */
iref *irefassistretain(iref *ref) {
    iretain(ref);
    return ref;
}
    
/* ref-assign: dst ==> iref**; src ==> iref** */
void iref_assign(const struct imeta* meta, iptr dst, const iptr src) {
    iref **reff = icast(iref*, dst);
    iref **reff_src = icast(iref*, src);
    icheck(dst);
    icheck(src);
    iassign(reff[0], reff_src[0]);
}
