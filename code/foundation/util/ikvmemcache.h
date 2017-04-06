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
struct iarray;

/* forwrad the envicted-block */
typedef void (*ikvcache_envicted)(struct ikvmemcache* cache, struct idict* values);

/* the weight-block */
typedef size_t (*ikvcache_weight)(struct ikvmemcache* cache, const struct ivar *key, struct ivar *value);

/* the control flag in kv-cache */
typedef enum EnumKvMemCacheFlag {
    EnumKvMemCacheFlag_NotTrimTheRetained = 1,      /* do not trime the retained object */
    
    EnumKvMemCacheFlag_AutoTrimToCountCapacity = 1<<1,   /* auto trim the cache when add object */
    EnumKvMemCacheFlag_AutoTrimToWeightCapacity = 1<<2,   /* auto trim the cache when add object */
    
    EnumKvMemCacheFlag_SkipEnvicted = 1<<4,         /* do not care about the envicted-behavior */
    
    EnumKvMemCacheFlag_Weighted = 1<<8,             /* should we care about the value weight */
    
} EnumKvMemCacheFlag;

/* the const lru-memory-cache */
typedef struct ikvmemcache {
    irefdeclare;
    
    int flag;                           /* @see EnumKvCacheFlag */
    
    struct idict *dict;                 /* the key-value */
    struct ireflist *lru;               /* the lru node list */
    
    ikvcache_envicted fnenvicted;       /* the call-back */
    ikvcache_weight fnweight;           /* the weight-block */
    
    size_t capacitycount;               /* the max-count of cache-object */
    size_t capacityweight;              /* the weight-capacity of cache-object */
    
    size_t weight;                      /* current weight */
    
} ikvmemcache;

/* make a cache */
ikvmemcache* ikvmemcachemake(size_t capacity);

/* destructor */
void ikvmemcache_destructor(const struct imeta*, iptr o);

/* get the cache-size */
size_t ikvmemcachesize(const ikvmemcache *cache);

/* trim the cache to right count, return the trimed object counts */
size_t ikvmemcachetrimcount(ikvmemcache* cache, size_t count);
    
/* trim the cache to right weight, return the trimed object counts */
size_t ikvmemcachetrimweight(ikvmemcache* cache, size_t weight);

/* get the value of cache, not need to release for ivar */
struct ivar * ikvmemcacheget(const ikvmemcache* cache, const struct ivar* key);

/* put the ivar in key, if the new key return iiok, if exits already return iino */
int ikvmemcacheput(struct ikvmemcache* cache, const struct ivar *key, struct ivar *value);

/* remove the cache for key */
int ikvmemcacheremove(ikvmemcache* cache, const struct ivar *key);
    
/* clear all the node in the cache*/
void ikvmemcacheclear(ikvmemcache* cache);
   
/* all keys in LRU-order returned in @param keys<ivar*>, return the keys-count */
size_t ikvmemcachekeys(const ikvmemcache* cache, struct iarray *keys);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IKVCACHE_H_ */
