
#include "simpletest.h"
#include "foundation/core/iobj.h"
#include "foundation/core/imetatypes.h"

// **********************************************************************************
// iobj
SP_SUIT(iobj);

SP_CASE(iobj, begin) {
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(iobj, iobjgetmeta) {
    iobj *obj = iobjmalloc(iobj);
    SP_TRUE(obj != NULL);
    
    const imeta *meta = iobjgetmeta(obj);
    SP_TRUE(meta != NULL);
    SP_EQUAL(meta, imetaof(iobj));
    
    iobjfree(obj);
}

SP_CASE(iobj, iobjistype) {
    iobj *obj = iobjmalloc(iobj);
    SP_TRUE(obj != NULL);
    SP_TRUE(iobjistype(obj, "iobj"));
    
    iobjfree(obj);
}

SP_CASE(iobj, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

