#include "foundation/container/irefcache.h"
#include "foundation/core/iwref.h"
#include "foundation/core/imetatypes.h"

/* destructor for flag */
void irefcache_destructor(const imeta* meta, iptr o) {
    irefcache *cache = icast(irefcache, o);
    irefcacheclear(cache);
    irefdelete(cache->cache);
}

/* cache-flag */
enum {
    __iRefCacheFlag_Invalid = 1,
};

/* the call back for ref change */
static void _ientrywatch_cache(irefwatcher *watcher, iref *ref) {
    irefcache *cache = icast(irefcache, watcher);
    int len = 0;
    icheck(ref->_ref == 0);
    
    /* only move ref to live cache */
    len = ireflistlen(cache->cache);
    if (len < cache->capacity && !iflag_is(cache->flag, __iRefCacheFlag_Invalid)) {
        /* may release some resource hold by ref */
        if (cache->whenadd) {
            cache->whenadd(ref);
        }
        /* entry the cache */
        ireflistadd(cache->cache, ref);
    }else if (cache->envicted){
        /* the cache is full, may expand the capacity */
        cache->envicted(ref);
    }
}

/* make a ref cache with capacity */
irefcache *irefcachemake(size_t capacity, icachenewentry newentry) {
    irefcache *cache = irefnew(irefcache);
    cache->cache = ireflistmake();
    cache->capacity = capacity;
    cache->newentry = newentry;
    cache->watch = _ientrywatch_cache;
    return cache;
}

/* poll one ref from the cache */
iref *irefcachepoll(irefcache *cache) {
    iref *ref = NULL;
    irefjoint* joint = ireflistfirst(cache->cache);
    if (joint) {
        /* got the ref-value */
        iassign(ref, joint->value);
       
        /* remove from the cache list */
        ireflistremovejoint(cache->cache, joint);
       
        if (ref->_ref != 1) {
            ilog("##IMAP-RefCache## Poll - %d\n", ref->_ref);
        }
        return ref;
    }
    
    ref = cache->newentry();
    ref->_watcher = iwrefmake(irefcast(cache)); /* remember the watcher */
    return ref;
}

/* release the ref to cache */
void irefcachepush(irefcache *cache, iref *ref) {
    icheck(ref);
    /* just make sure we should be cacheable */
    if (iwrefunsafestrong(ref->_watcher) != irefcast(cache)) {
        ref->_watcher = iwrefmake(irefcast(cache)); /* remember the watcher */
    }
    /* release the ref */
    irelease(ref);
}

/* clear the cache refs */
void irefcacheclear(irefcache *cache) {
    icheck(cache);
    iflag_add(cache->flag, __iRefCacheFlag_Invalid);
    ireflistremoveall(cache->cache);
    iflag_remove(cache->flag, __iRefCacheFlag_Invalid);
}

/* get num of ref in the cache */
size_t irefcachesize(irefcache *cache) {
    return ireflistlen(cache->cache);
}
