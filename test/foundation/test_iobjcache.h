#include "simpletest.h"
#include "foundation/core/iobjcache.h"
#include "foundation/core/imetatypes.h"

// **********************************************************************************
// iobjcache
SP_SUIT(iobjcache);

SP_CASE(iobjcache, imakecacheableallocator) {
    imetaallocator *allocator = imakecacheableallocator(imetaof(iobj), 100);
    SP_TRUE(allocator != NULL);
    iobjcachefree(allocator);
}

SP_CASE(iobjcache, iobjcache) {
    imetaallocator *allocator = imakecacheableallocator(imetaof(iobj), 100);
    SP_TRUE(allocator != NULL);
    iobjcachefree(allocator);
}

SP_CASE(iobjcache, iobjcacheget) {
    iobjcache *cache = iobjcacheget(imetaof(iobj));
    SP_TRUE(cache != NULL);
}

SP_CASE(iobjcache, iobjcachestatis) {
    imemorystatistics *statis = iobjcachestatis(imetaof(iobj));
    SP_TRUE(statis != NULL);
    imemorystatistics *globalstatis = iobjcachestatis(NULL);
    SP_TRUE(globalstatis != NULL);
}

SP_CASE(iobjcache, iobjcacheclearANDiobjcachesetcapacity) {
    iobjcache *cache = iobjcacheget(imetaof(iobj));
    iobjcachesetcapacity(cache, 1);
    iobj *obj = iobjmalloc(iobj);
    iobjfree(obj);
    SP_TRUE(cache->num != 0);
    
    iobjcacheclear(imetaof(iobj));
    SP_TRUE(cache->num == 0);
    iobjcachesetcapacity(cache, 0);
}

SP_CASE(iobjcache, iobjcachememorysize) {
    // should be cache with zero
    int64_t kind_alloc = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Alloced);
    int64_t kind_freed = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Freed);
    int64_t kind_current = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Hold);
    
    iobj *obj = iobjmalloc(iobj);
    int64_t kind_alloc_n = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Alloced);
    int64_t kind_freed_n = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Freed);
    int64_t kind_current_n = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Hold);
    size_t newsize = sizeof(iobj)*2;
    
    SP_TRUE((kind_alloc + newsize) == kind_alloc_n);
    SP_TRUE(kind_freed == kind_freed_n);
    SP_TRUE((kind_current + newsize) == kind_current_n);
    
    iobjfree(obj);
    kind_alloc_n = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Alloced);
    kind_freed_n = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Freed);
    kind_current_n = iobjcachememorysize(imetaof(iobj), EnumObjCacheMemoerySizeKind_Hold);
    
    SP_TRUE((kind_alloc + newsize) == kind_alloc_n);
    SP_TRUE((kind_freed + newsize) == kind_freed_n);
    SP_TRUE(kind_current == kind_current_n);
}

SP_CASE(iobjcache, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
