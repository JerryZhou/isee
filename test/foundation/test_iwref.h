#include "simpletest.h"
#include "foundation/core/iobj.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iwref.h"

// **********************************************************************************
// iwref
SP_SUIT(iwref);

SP_CASE(iwref, begin) {
    SP_TRUE(1);
    
    /*no memory leak about iwref */
    SP_TRUE(iobjcachestatis(imetaof(iwref))->current == 0)
}

SP_CASE(iwref, iwrefmake) {
    iref *ref = irefnew(iref);
    
    iwref *wref0 = iwrefmake(ref);
    SP_EQUAL(irefcast(wref0->_wref), ref);
    iref *strongref = iwrefstrong(wref0);
    SP_EQUAL(strongref, ref);
    irelease(strongref);
    SP_EQUAL(irefcast(wref0->_wref), ref);
    
    irelease(ref);
    SP_EQUAL(wref0->_wref, NULL);
    strongref = iwrefstrong(wref0);
    SP_EQUAL(strongref, NULL);
    
    irelease(wref0);
}

SP_CASE(iwref, iwrefmakeby) {
    
    iref *ref = iobjmalloc(iref);
    iretain(ref);
    
    iwref *wref0 = iwrefmake(ref);
    SP_EQUAL(irefcast(wref0->_wref), ref);
    iref *strongref = iwrefstrong(wref0);
    SP_EQUAL(strongref, ref);
    irelease(strongref);
    SP_EQUAL(irefcast(wref0->_wref), ref);
    
    iwref *wref1 = iwrefmakeby(wref0);
    SP_EQUAL(irefcast(wref1->_wref), ref);
    SP_EQUAL(wref0, wref1);
    iref *strongref1 = iwrefstrong(wref1);
    SP_EQUAL(strongref1, ref);
    irelease(strongref1);
    SP_EQUAL(irefcast(wref1->_wref), ref);
    SP_EQUAL(wref0, wref1);
    
    irelease(ref);
    SP_EQUAL(wref0->_wref, NULL);
    strongref = iwrefstrong(wref0);
    SP_EQUAL(strongref, NULL);
    
    SP_EQUAL(wref1->_wref, NULL);
    strongref = iwrefstrong(wref1);
    SP_EQUAL(strongref, NULL);
    
    irelease(wref0);
    irelease(wref1);
}

SP_CASE(iwref, makenull) {
    iwref *wref0 = iwrefmake(NULL);
    iwref *wref1 = iwrefmake(NULL);
    
    SP_EQUAL(wref0, wref1);
    
    iref *strong = iwrefstrong(wref0);
    SP_EQUAL(strong, NULL);
    
    irelease(wref0);
    irelease(wref1);
    
    iwref *wrefzero = iwrefmakeby(NULL);
    SP_EQUAL(wrefzero, NULL);
    irelease(wrefzero);
}

SP_CASE(iwref, iwrefunsafestrong) {
    iref *ref = irefnew(iref);
    iwref *wref = iwrefmake(ref);
    SP_TRUE(iwrefunsafestrong(wref) == ref);
    irelease(ref);
    irelease(wref);
}

SP_CASE(iwref, end) {
    SP_TRUE(1);
    
    
    /*no memory leak about iwref */
    SP_TRUE(iobjcachestatis(imetaof(iwref))->current == 0)
}