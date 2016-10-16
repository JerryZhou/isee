#include "simpletest.h"
#include "foundation/core/iobj.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iref.h"
#include "foundation/core/iwref.h"

// **********************************************************************************
// iref
SP_SUIT(iref);

SP_CASE(iref, iretainANDirelease) {
    iref *ref = iobjmalloc(iref);
    SP_EQUAL(ref->_ref, 0);
    
    iretain(ref);
    
    SP_EQUAL(ref->_ref, 1);
    
    iretain(ref);
    
    SP_EQUAL(ref->_ref, 2);
    
    irelease(ref);
    
    SP_EQUAL(ref->_ref, 1);
    
    irelease(ref);
}

static int facereffreecc = 0;
typedef struct simple_refwatcher {
    irefwatcherdeclare;
}simple_refwatcher;
irealdeclareregister(simple_refwatcher);

static void iref_watcher(irefwatcher *watcher, iref *ref) {
    ++facereffreecc;
}

SP_CASE(iref, register_watcher) {
    irealimplementregister(simple_refwatcher, 0);
    SP_TRUE(imetaindex(simple_refwatcher) > 0);
}

SP_CASE(iref, irelease) {
    simple_refwatcher *watcher = irefnew(simple_refwatcher);
    watcher->watch = iref_watcher;
    
    iref *ref = iobjmalloc(iref);
    ref->_watcher = iwrefnew(watcher);
    
    SP_EQUAL(ref->_ref, 0);
    
    iretain(ref);
    
    SP_EQUAL(ref->_ref, 1);
    
    iretain(ref);
    
    SP_EQUAL(ref->_ref, 2);
    
    irelease(ref);
    
    SP_EQUAL(ref->_ref, 1);
    
    SP_EQUAL(facereffreecc, 0);
    irelease(ref);
    SP_EQUAL(facereffreecc, 1);
    
    irelease(watcher);
}

SP_CASE(iref, iassign) {
    iref *ref = irefnew(iref);
    
    SP_EQUAL(ref->_ref, 1);
    
    iref *ref0 = NULL, *ref1 = NULL;
    
    iassign(ref0, ref);
    iassign(ref1, ref);
    
    SP_EQUAL(ref->_ref, 3);
    
    iassign(ref0, ref1);
    
    SP_EQUAL(ref->_ref, 3);
    
    iassign(ref0, NULL);
    
    SP_EQUAL(ref->_ref, 2);
    
    iassign(ref1, NULL);
    
    SP_EQUAL(ref->_ref, 1);
    
    irelease(ref);
}

SP_CASE(iref, irefthis) {
    iref *ref = irefnew(iref);
    iref *xthis = irefthis(iref, ref);
    SP_TRUE(xthis == NULL);
    irelease(ref);
}

SP_CASE(iref, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

