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

/* get the cache-size */
size_t ikvmemcachesize(const ikvmemcache *cache) {
    icheckret(cache, 0);
    return idictsize(cache->dict);
}

/* should update the weight */
static void _ikvmemcacheweight_change(ikvmemcache* cache, const ivar *key, ivar *oldvalue, ivar *newvalue) {
    icheck(cache && oldvalue != newvalue);
    icheck(cache->fnweight);
    icheck(iflag_is(cache->flag, EnumKvMemCacheFlag_Weighted));
    
    if (oldvalue) {
        cache->weight -= cache->fnweight(cache, key, oldvalue);
    }
    
    if (newvalue) {
        cache->weight += cache->fnweight(cache, key, newvalue);
    }
}

/* basic remove-entry */
void _ikvmemcache_remove_entry(ikvmemcache* cache, idictentry *entry) {
    /* remove from the lru */
    irefjoint* joint = icast(irefjoint, entry->u);
    ireflistremovejoint(cache->lru, joint);
    
    /* update the weight */
    _ikvmemcacheweight_change(cache, entry->key, entry->value, NULL);
    
    /* remove from the dict */
    idictremoveentry(cache->dict, entry, NULL);
}

/* typedef the range-trim */
typedef int (*_ikv_range_end) (ikvmemcache* cache, size_t size);
typedef void (*_ikv_range_eval) (ikvmemcache*cache, idictentry *entry);

static size_t _ikvmemcache_trim_to(ikvmemcache* cache, size_t size, _ikv_range_end end, _ikv_range_eval eval) {
    icheckret(end(cache, size), 0);
    
    /*double-linked-list in circle */
    irefjoint* node = ireflistlast(cache->lru);
    irefjoint* pre = NULL;
    int rangelimit = idictsize(cache->dict);
    idictentry* entry = NULL;
    size_t count = 0;
    
    /* the trimed-cache */
    idict* toremoved = NULL;
    if (cache->fnenvicted && !iflag_is(cache->flag, EnumKvMemCacheFlag_SkipEnvicted)) {
        toremoved = idictmake(8);
    }
    
    /* reverse the lru-list */
    while (end(cache, size) && rangelimit > 0) {
        if (node) {
            pre = node->pre;
            if (!iflag_is(cache->flag, EnumKvMemCacheFlag_NotTrimTheRetained) || // no need to track the retain
                (entry = icast(idictentry, node->value) &&                       // track the retain-count is less equal than 1
                 (entry == NULL || entry->value == NULL || entry->value->_ref == 1))) {
                    /* the eval */
                    if (eval) {
                        eval(cache, entry);
                    }
                    
                     /* remove from the cache */
                    _ikvmemcache_remove_entry(cache, entry);
                    
                    /* the count ++ */
                    ++count;
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
        cache->fnenvicted(cache, toremoved);
        irefdelete(toremoved);
    }
    
    return count;
}

/* end the count of kv */
static int _ikv_end_count(ikvmemcache *cache, size_t size) {
    return idictsize(cache->dict) > size;
}

/* trim the cache to right size, return the trimed object counts */
size_t ikvmemcachetrim(ikvmemcache* cache, size_t trim) {
    return _ikvmemcache_trim_to(cache, trim, _ikv_end_count, NULL);
}

/* end the weight of kv */
static int _ikv_end_weight(ikvmemcache *cache, size_t size) {
    return cache->weight > size;
}

/* the weight-val */
static size_t ikvmemcachetrimweight(ikvmemcache* cache, size_t weight) {
    return _ikvmemcache_trim_to(cache, weight, _ikv_end_weight, NULL);
}

/* update the joint in lru */
static void _ikvmemcacheupdateentry(ikvmemcache* cache, idictentry *entry) {
    irefjoint* joint = icast(irefjoint, entry->u);
    iretain(joint);
    ireflistremovejoint(cache->lru, joint);
    ireflistaddjoint(cache->lru, joint);
    irelease(joint);
}

/* should update the weight */
static void _ikvmemcacheweighteval(ikvmemcache* cache, const ivar *key, ivar *oldvalue, ivar *newvalue) {
    /* the truly weight cacl */
    _ikvmemcacheweight_change(cache, key, oldvalue, newvalue);
    
    /* the weight eval-trim */
    if (cache->weight >= cache->capacityweight) {
        ikvmemcachetrimweight(cache, cache->capacityweight);
    }
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
        
        /* update the weight */
        _ikvmemcacheweighteval(cache, key, NULL, value);
    } else {
        exits = iiok;
        /* update the weight */
        _ikvmemcacheweighteval(cache, key, entry->value, value);
        /* set the value*/
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
        _ikvmemcache_remove_entry(cache, entry);
    }
    
    return entry != NULL;
}

