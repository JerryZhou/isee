#include "foundation/util/ikvmemcache.h"
#include "foundation/container/idict.h"
#include "foundation/container/ireflist.h"

/* make a cache */
ikvmemcache* ikvmemcachemake(size_t capacity) {
    ikvmemcache *cache = irefnew(ikvmemcache);
    cache->dict = idictmake(capacity>>3);
    cache->lru = ireflistmake();
    return cache;
}

/* destructor */
void ikvmemcache_destructor(const struct imeta* meta, iptr o) {
    ikvmemcache* cache = icast(ikvmemcache, o);
    ikvmemcacheclear(cache);
    
    iassign(cache->lru, NULL);
    iassign(cache->dict, NULL);
}

/* clear all the node in the cache*/
void ikvmemcacheclear(ikvmemcache* cache) {
    ireflistremoveall(cache->lru);
    idictremoveall(cache->dict);
}

/* trim the cache to right size, return the trimed object counts */
size_t ikvmemcachetrim(ikvmemcache* cache, size_t trim) {
    icheckret(ireflistlen(cache->lru) > trim, 0);
    
    /*TODO: double-linked-list in circle */
    
    return 0;
}

/* get the value of cache, not need to release for ivar */
struct ivar * ikvmemcacheget(const ikvmemcache* cache, const struct ivar* key) {
    return NULL;
}

/* put the ivar in key */
void ikvmemcacheput(struct ikvmemcache* cache, const struct ivar *key, struct ivar *value) {
    
}

