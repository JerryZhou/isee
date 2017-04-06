//
//  test_ikvmemcache.h
//  isee
//
//  Created by jerry on 2017/4/6.
//
//

#ifndef test_ikvmemcache_h
#define test_ikvmemcache_h

#include "foundation/util/ikvmemcache.h"

SP_SUIT(ikvmemcache);

/* the convirement */
static void __x_cacheset(ikvmemcache *cache, int ikey, int ivalue) {
    ivar *key = ivarmakeint(ikey);
    ivar *value = ivarmakeint(ivalue);
    ikvmemcacheput(cache, key, value);
    irefdelete(key);
    irefdelete(value);
}

/* get the value from cache, if not exits just return 0 */
static int __x_cacheget(ikvmemcache *cache, int ikey) {
    ivar *key = ivarmakeint(ikey);
    ivar *value = ikvmemcacheget(cache, key);
    irefdelete(key);
    if (value) {
        return ivarcast(value, int);
    }
    return 0;
}

/* compare the lur-keys is equal to ikeys */
static int __x_cachelrukeysequal(ikvmemcache *cache, int *ikeys, int count) {
    iarray *keys = iarraymakeiref(0);
    int icompare = iino;
    if(ikvmemcachekeys(cache, keys) == count) {
        icompare = iiok;
        irangearray(keys, ivar*,
                    if (ivarcast(__value, int) != ikeys[__key]) {
                        icompare = iino;
                        break;
                    }
                    );
    }
    irefdelete(keys);
    return icompare;
}

SP_CASE(ikvmemcache, ikvmemcachemake) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    irefdelete(cache);
}

SP_CASE(ikvmemcache, ikvmemcacheclear) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    __x_cacheset(cache, 0, 100);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    ikvmemcacheclear(cache);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, ikvmemcachetrimcount) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        __x_cacheset(cache, 0, 100);
        __x_cacheset(cache, 1, 100);
        __x_cacheset(cache, 2, 100);
    }
    
    
    SP_TRUE(ikvmemcachesize(cache) == 3);
    ikvmemcachetrimcount(cache, 1);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}

static size_t _x_ikv_eg_weight(ikvmemcache* cache, const ivar *key, ivar *value) {
    int iv = ivarcast(value, int);
    return iv;
}

SP_CASE(ikvmemcache, ikvmemcachetrimweight) {
    ikvmemcache* cache = ikvmemcachemake(8);
    cache->flag |= EnumKvMemCacheFlag_Weighted;
    cache->fnweight = _x_ikv_eg_weight;
    
    //cache->flag |= EnumKvMemCacheFlag_AutoTrimToWeightCapacity;
    //cache->capacityweight = 5;
    
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        __x_cacheset(cache, 0, 100);
        __x_cacheset(cache, 1, 100);
        __x_cacheset(cache, 2, 100);
    }
    
    SP_TRUE(ikvmemcachesize(cache) == 3);
    ikvmemcachetrimweight(cache, 100);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, ikvmemcacheget) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        __x_cacheset(cache, 0, 0);
        __x_cacheset(cache, 1, 100);
        __x_cacheset(cache, 2, 200);
    }
    
    {
        SP_TRUE(__x_cacheget(cache, 0) == 0);
        SP_TRUE(__x_cacheget(cache, 1) == 100);
        SP_TRUE(__x_cacheget(cache, 2) == 200);
    }
    
    {
        ivar *key = ivarmakeint(3);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(value == NULL);
        irefdelete(key);
    }
    
    SP_TRUE(ikvmemcachesize(cache) == 3);
    ikvmemcachetrimcount(cache, 1);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}


SP_CASE(ikvmemcache, ikvmemcacheput) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        ivar *key = ivarmakeint(0);
        ivar *value = ivarmakeint(0);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ivarmakeint(100);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(2);
        ivar *value = ivarmakeint(200);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(0);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 0);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 100);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(2);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 200);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(3);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(value == NULL);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ivarmakeint(1000);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 1000);
        irefdelete(key);
    }
    
    SP_TRUE(ikvmemcachesize(cache) == 3);
    ikvmemcachetrimcount(cache, 1);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, ikvmemcacheremove) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        ivar *key = ivarmakeint(0);
        ivar *value = ivarmakeint(0);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ivarmakeint(100);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(2);
        ivar *value = ivarmakeint(200);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(0);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 0);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 100);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(2);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 200);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(3);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(value == NULL);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ivarmakeint(1000);
        ikvmemcacheput(cache, key, value);
        irefdelete(key);
        irefdelete(value);
    }
    
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(ivarcast(value, int) == 1000);
        irefdelete(key);
    }
    
    {
        ivar *key = ivarmakeint(1);
        SP_TRUE(ikvmemcacheremove(cache, key));
        irefdelete(key);
    }
    {
        ivar *key = ivarmakeint(1);
        ivar *value = ikvmemcacheget(cache, key);
        SP_TRUE(value == NULL);
        irefdelete(key);
    }
    
    SP_TRUE(ikvmemcachesize(cache) == 2);
    ikvmemcachetrimcount(cache, 1);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, ikvmemcachekeys) {
    ikvmemcache* cache = ikvmemcachemake(8);
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        __x_cacheset(cache, 1, 100);
        __x_cacheset(cache, 2, 200);
        __x_cacheset(cache, 3, 300);
    }
    
    {
        int ikeys[] = {3, 2, 1};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheget(cache, 2);
        int ikeys[] = {2, 3, 1};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheget(cache, 2);
        int ikeys[] = {2, 3, 1};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheget(cache, 1);
        int ikeys[] = {1, 2, 3};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheget(cache, 4);
        int ikeys[] = {1, 2, 3};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    SP_TRUE(ikvmemcachesize(cache) == 3);
    ikvmemcachetrimcount(cache, 1);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, lruBehaviorCount) {
    ikvmemcache* cache = ikvmemcachemake(8);
    cache->flag |= EnumKvMemCacheFlag_AutoTrimToCountCapacity;
    cache->capacitycount = 3;
    
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        __x_cacheset(cache, 1, 100);
        __x_cacheset(cache, 2, 200);
        __x_cacheset(cache, 3, 300);
    }
    
    {
        int ikeys[] = {3, 2, 1};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheset(cache, 4, 400);
        int ikeys[] = {4, 3, 2};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    SP_TRUE(ikvmemcachesize(cache) == 3);
    ikvmemcachetrimcount(cache, 1);
    SP_TRUE(ikvmemcachesize(cache) == 1);
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, lruBehaviorWeight) {
    ikvmemcache* cache = ikvmemcachemake(8);
    cache->flag |= EnumKvMemCacheFlag_Weighted;
    cache->fnweight = _x_ikv_eg_weight;
    
    cache->flag |= EnumKvMemCacheFlag_AutoTrimToWeightCapacity;
    cache->capacityweight = 60;
    
    SP_TRUE(ikvmemcachesize(cache) == 0);
    
    {
        __x_cacheset(cache, 1, 10);
        __x_cacheset(cache, 2, 20);
        __x_cacheset(cache, 3, 30);
    }
    
    {
        int ikeys[] = {3, 2, 1};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheset(cache, 4, 10);
        int ikeys[] = {4, 3, 2};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheset(cache, 4, 60);
        int ikeys[] = {4};
        SP_TRUE(__x_cachelrukeysequal(cache, ikeys, icountof(ikeys)));
    }
    
    {
        __x_cacheset(cache, 4, 80);
        SP_TRUE(ikvmemcachesize(cache) == 0);
    }
    
    irefdelete(cache);
}

SP_CASE(ikvmemcache, end) {
    SP_TRUE(1);
}


#endif /* test_ikvmemcache_h */
