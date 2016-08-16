#include "simpletest.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iobjcache.h"

// **********************************************************************************
// imeta
SP_SUIT(imeta);

SP_CASE(imeta, imetaget) {
    imeta *meta = imetaget(imetaindex(iobj));
    SP_TRUE(meta != NULL);
    SP_TRUE(strcmp(meta->name, "iobj") == 0);
    SP_TRUE(meta->size == sizeof(iobj));
}

int _buf_meta_index = 0;
SP_CASE(imeta, imetaregister) {
    _buf_meta_index = imetaregisterwithcapacity("--buf--", 100, 1);
    SP_TRUE(_buf_meta_index > 0);
    imeta *meta = imetaget(_buf_meta_index);
    SP_TRUE(meta != NULL);
    SP_TRUE(meta->size == 100);
    
    iobjcache *cache = iobjcacheget(meta);
    SP_TRUE(cache->capacity == 1);
}

SP_CASE(imeta, imetacallocANDimetafree) {
    imeta *meta = imetaget(_buf_meta_index);
    void *p = imetacalloc(meta);
    SP_TRUE(p != NULL);
    char *pbuf = (char*)p;
    pbuf[99] = 128; // [0,99] , we can reach all range of buffer
    size_t solosize = sizeof(iobj) + 100;
    
    iobjcache *cache = iobjcacheget(meta);
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 0);
    SP_TRUE(cache->statis.alloced == solosize);
    SP_TRUE(cache->statis.current == solosize);
    SP_TRUE(cache->statis.freed == 0);
    
    imetafree(p);
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 1);
    SP_TRUE(cache->statis.alloced == solosize);
    SP_TRUE(cache->statis.current == solosize);
    SP_TRUE(cache->statis.freed == 0);
    
    void *p2 = imetacalloc(meta);
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 0);
    SP_TRUE(cache->statis.alloced == solosize);
    SP_TRUE(cache->statis.current == solosize);
    SP_TRUE(cache->statis.freed == 0);
    SP_TRUE(p2 == p);
    
    void *p3 = imetacalloc(meta);
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 0);
    SP_TRUE(cache->statis.alloced == solosize*2);
    SP_TRUE(cache->statis.current == solosize*2);
    SP_TRUE(cache->statis.freed == 0);
    SP_TRUE(p3 != p);
    
    imetafree(p2);
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 1);
    SP_TRUE(cache->statis.alloced == solosize*2);
    SP_TRUE(cache->statis.current == solosize*2);
    SP_TRUE(cache->statis.freed == 0);
    
    imetafree(p3);
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 1);
    SP_TRUE(cache->statis.alloced == solosize*2);
    SP_TRUE(cache->statis.current == solosize*1);
    SP_TRUE(cache->statis.freed == solosize*1);
    
    iobjcacheclear(meta);
    
    SP_TRUE(cache->capacity == 1);
    SP_TRUE(cache->num == 0);
    SP_TRUE(cache->statis.alloced == solosize*2);
    SP_TRUE(cache->statis.current == 0);
    SP_TRUE(cache->statis.freed == solosize*2);
}

SP_CASE(imeta, imetamemorystate) {
    SP_TRUE(1);
    imetamemorystate(); // output logs
}