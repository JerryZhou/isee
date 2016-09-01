#include "foundation/core/iwref.h"
#include "foundation/core/iref.h"
#include "foundation/core/imetatypes.h"

/* zero wref */
static iwref kzero_wref = {1, NULL};

/* make a weak iref by ref */
iwref *iwrefmake(iref *ref) {
    volatile iwref *wref = NULL;
    if (ref == NULL) {
        wref = (iwref*)(&kzero_wref);
    } else if (ref->_wref == NULL) {
        /* total new wref */
        ref->_wref = iobjmalloc(iwref);
        ref->_wref->_wref = icast(iwref, ref);
        wref = ref->_wref;
    } else {
        /* extis */
        wref = ref->_wref;
    }
    
    iretain(wref);
    return (iwref*)wref;
}

/* make a weak iref by wref */
iwref *iwrefmakeby(iwref *wref) {
    icheckret(wref, NULL);
    return iwrefmake(irefcast(wref->_wref));
}

/* make strong ref: need call irelease */
iref *iwrefstrong(iwref *wref) {
    return irefassistretain(iwrefunsafestrong(wref));
}

/* make strong ref: unneed call irelease */
iref *iwrefunsafestrong(iwref *wref) {
    icheckret(wref, NULL);
    icheckret(wref != &kzero_wref, NULL);
    
    return icast(iref, wref->_wref);
}