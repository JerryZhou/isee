
#include "imemoryprofile.h"
#include "foundation/core/imeta.h"
#include "foundation/core/iobjcache.h"
#include "foundation/memory/imemorystatistics.h"

/* clear all the cached-memory */
void imemoryglobalclear() {
    int cur = imetaindexcur()-1;
    imeta *meta;
    for (; cur>=0; --cur) {
        meta = imetaget(cur);
        iobjcacheclear(meta);
    }
}

/* current global memory alloced */
int64_t imemoryglobalalloc() {
    return iobjcachememorysize(NULL, EnumObjCacheMemoerySizeKind_Alloced);
}

/* current global memory freed */
int64_t imemoryglobalfree() {
    return iobjcachememorysize(NULL, EnumObjCacheMemoerySizeKind_Freed);
}

/* current global memory used */
int64_t imemoryglobaluse() {
    return iobjcachememorysize(NULL, EnumObjCacheMemoerySizeKind_Hold);
}
