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
    
    /*double-linked-list in circle */
    irefjoint* node = ireflistlast(cache->lru);
    irefjoint* pre = NULL;
    int rangelimit = idictsize(cache->dict);
    idictentry* entry = NULL;
    
    /* the trimed-cache */
    idict* toremoved = NULL;
    if (cache->envicted) {
        toremoved = idictmake(8);
    }
    
    /* reverse the lru-list */
    while (idictsize(cache->dict) > trim && rangelimit > 0) {
        if (node) {
            pre = node->pre;
            if (!iflag_is(cache->flag, EnumKvMemCacheFlag_NotTrimTheRetained) || // no need to track the retain
                (entry = icast(idictentry, node->value) &&                       // track the retain-count is less equal than 1
                 (entry == NULL || entry->value == NULL || entry->value->_ref == 1))) {
                    /* remove from the lru */
                    ireflistremovejoint(cache->lru, node);
                    /* remove from the dict */
                    if (entry && entry->key) {
                        /* the call-back datas */
                        if (toremoved) {
                            idictadd(toremoved, entry->key, entry->value);
                        }
                        idictremoveentry(cache->dict, entry, NULL);
                    }
            }
            /* pre-node */
            node = pre;
        } else {
            break;
        }
        --rangelimit;
    }
    
    /* the triming call-back */
    if (toremoved) {
        cache->envicted(cache, toremoved);
        irefdelete(toremoved);
    }
    
    return 0;
}

/* update the joint in lru */
static void _ikvmemcacheupdateentry(ikvmemcache* cache, idictentry *entry) {
    irefjoint* joint = icast(irefjoint, entry->u);
    iretain(joint);
    ireflistremovejoint(cache->lru, joint);
    ireflistaddjoint(cache->lru, joint);
    irelease(joint);
}

/* get the value of cache, not need to release for ivar */
struct ivar * ikvmemcacheget(const ikvmemcache* cache, const struct ivar* key) {
    idictentry* entry = idictentryof(cache->dict, key);
    if (entry) {
        _ikvmemcacheupdateentry((ikvmemcache*)cache, entry);
        return entry->value;
    }
    return NULL;
}

/* put the ivar in key */
int ikvmemcacheput(struct ikvmemcache* cache, const struct ivar *key, struct ivar *value) {
    idictentry* entry = idictentryof(cache->dict, key);
    int exits = iino;
    if (!entry) {
        entry = idictadd(cache->dict, key, value);
        entry->u = ireflistadd(cache->lru, irefcast(entry));
    } else {
        exits = iiok;
        idictentysetvalue(entry, value);
        
        /* update the joint in lru */
        _ikvmemcacheupdateentry((ikvmemcache*)cache, entry);
    }
    
    /* if add object and the flag is auto-triming */
    if (!exits && iflag_is(cache->flag, EnumKvMemCacheFlag_AutoTrimToCapacity)) {
        ikvmemcachetrim(cache, cache->capacity);
    }
    
    return exits;
}

/* remove the cache for key */
int ikvmemcacheremove(ikvmemcache* cache, const struct ivar *key) {
    idictentry* entry = idictentryof(cache->dict, key);
    if (entry) {
        /* remove from the lru */
        irefjoint* joint = icast(irefjoint, entry->u);
        ireflistremovejoint(cache->lru, joint);
        
        /* remove from the dict */
        idictremoveentry(cache->dict, entry, NULL);
    }
    
    return entry != NULL;
}

