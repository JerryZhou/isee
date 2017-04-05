#ifndef _IKVCACHE_H_
#define _IKVCACHE_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"

	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
    /* forward declares */
    struct idict;
    struct ireflist;
    struct ivar;
    struct ikvmemcache;
    
    /* forwrad the envicted-block */
    typedef void (*ikvcache_envicted)(struct ikvmemcache* cache, struct idict* values);
    
    /* the control flag in kv-cache */
    typedef enum EnumKvMemCacheFlag {
        EnumKvMemCacheFlag_NotTrimTheRetained = 1,      /* do not trime the retained object */
        
        EnumKvMemCacheFlag_AutoTrimToCapacity = 1<<1,   /* auto trim the cache when add object */
        
    } EnumKvMemCacheFlag;
    
    /* the const lru-memory-cache */
    typedef struct ikvmemcache {
        irefdeclare;
        
        int flag;                       /* @see EnumKvCacheFlag */
        
        struct idict *dict;             /* the key-value */
        struct ireflist *lru;           /* the lru node list */
        
        ikvcache_envicted envicted;     /* the call-back */
        
        size_t capacity;                /* the max-count of cache-object */
        
    } ikvmemcache;
    
    /* make a cache */
    ikvmemcache* ikvmemcachemake(size_t capacity);
    
    /* destructor */
    void ikvmemcache_destructor(const struct imeta*, iptr o);
    
    /* clear all the node in the cache*/
    void ikvmemcacheclear(ikvmemcache* cache);
    
    /* trim the cache to right size, return the trimed object counts */
    size_t ikvmemcachetrim(ikvmemcache* cache, size_t trim);
    
    /* get the value of cache, not need to release for ivar */
    struct ivar * ikvmemcacheget(const ikvmemcache* cache, const struct ivar* key);
    
    /* put the ivar in key, if the new key return iiok, if exits already return iino */
    int ikvmemcacheput(struct ikvmemcache* cache, const struct ivar *key, struct ivar *value);
    
    /* remove the cache for key */
    int ikvmemcacheremove(ikvmemcache* cache, const struct ivar *key);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IKVCACHE_H_ */
