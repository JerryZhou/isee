#include "foundation/core/irefcache.h"
#include "foundation/core/iwref.h"
#include "foundation/core/imetatypes.h"

/* the call back for ref change */
static void _ientrywatch_cache(irefwatcher *watcher, iref *ref) {
    irefcache *cache = icast(irefcache, watcher);
    int len = 0;
    icheck(ref->_ref == 0);
    
    /* only move ref to live cache */
    len = ireflistlen(cache->cache);
    if (len < cache->capacity) {
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
    irefcache *cache = iobjmalloc(irefcache);
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
        ireflistremovejoint(cache->cache, joint);
        
        iassign(ref, joint->value);
        
        irefjointfree(joint);
        
        if (ref->_ref != 1) {
            ilog("[IMAP-RefCache] Poll - %d\n", ref->_ref);
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
    int oldcapacity = 0;
    icheck(cache);
    oldcapacity = cache->capacity;
    cache->capacity = 0;
    ireflistremoveall(cache->cache);
    cache->capacity = oldcapacity;
}

/* clear the cache refs and release the cache self */
void irefcachefree(irefcache *cache) {
    icheck(cache);
    /* should clear the capacity before remove all cached refs */
    cache->capacity = 0;
    /* release all cached object */
    irelease(cache->cache);
    /* release self */
    irelease(cache);
}

/* get num of ref in the cache */
size_t irefcachesize(irefcache *cache) {
    return ireflistlen(cache->cache);
}
