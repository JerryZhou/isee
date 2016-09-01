#include "foundation/container/irefcache.h"

SP_SUIT(irefcache);

static int _t_x_refcachenew_cnt = 0;
static int _t_x_refcacheadd_cnt = 0;
static int _t_x_refcacheenvicted_cnt = 0;

static void _t_x_refcache_reset() {
    _t_x_refcachenew_cnt = 0;
    _t_x_refcacheadd_cnt = 0;
    _t_x_refcacheenvicted_cnt = 0;
}

static iref *_t_x_newref() {
    ++_t_x_refcachenew_cnt;
    return irefnew(iref);
}

void _t_x_icacheaddentry(iref *ref) {
    ++_t_x_refcacheadd_cnt;
}

void _t_x_icacheenvictedentry(iref *ref) {
    ++_t_x_refcacheenvicted_cnt;
}

irefcache * _t_x_refcache() {
    irefcache *cache = irefcachemake(2, _t_x_newref);
    cache->envicted = _t_x_icacheenvictedentry;
    cache->whenadd = _t_x_icacheaddentry;
    _t_x_refcache_reset();
    return cache;
}

SP_CASE(irefcache, irefcachemake) {
    irefcache *cache = _t_x_refcache();
    irelease(cache);
}

SP_CASE(irefcache, irefcachepoll) {
    irefcache *cache = _t_x_refcache();
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    iref * ref = irefcachepoll(cache);
    iref * ref_origin = ref;
    irelease(ref);
    SP_EQUAL(_t_x_refcachenew_cnt, 1);
    SP_EQUAL(_t_x_refcacheadd_cnt, 1);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==1);
    
    iref * ref0 = irefcachepoll(cache);
    SP_EQUAL(ref_origin, ref0);
    irelease(ref0);
    SP_EQUAL(_t_x_refcachenew_cnt, 1);
    SP_EQUAL(_t_x_refcacheadd_cnt, 2);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==1);
    
    iref *ref_x = irefcachepoll(cache);
    SP_TRUE(irefcachesize(cache)==0);
    SP_EQUAL(_t_x_refcachenew_cnt, 1);
    iref *ref_y = irefcachepoll(cache);
    SP_TRUE(irefcachesize(cache)==0);
    SP_EQUAL(_t_x_refcachenew_cnt, 2);
    iref *ref_z = irefcachepoll(cache);
    SP_EQUAL(_t_x_refcachenew_cnt, 3);
    SP_EQUAL(_t_x_refcacheadd_cnt, 2);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    
    irelease(ref_x);
    SP_TRUE(irefcachesize(cache)==1);
    SP_EQUAL(_t_x_refcacheadd_cnt, 3);
    SP_EQUAL(_t_x_refcachenew_cnt, 3);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    
    irelease(ref_y);
    SP_TRUE(irefcachesize(cache)==2);
    SP_EQUAL(_t_x_refcacheadd_cnt, 4);
    SP_EQUAL(_t_x_refcachenew_cnt, 3);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    
    irelease(ref_z);
    SP_TRUE(irefcachesize(cache)==2);
    SP_EQUAL(_t_x_refcacheadd_cnt, 4);
    SP_EQUAL(_t_x_refcachenew_cnt, 3);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 1);
    
    irelease(cache);
}

SP_CASE(irefcache, irefcachepush) {
    irefcache *cache = _t_x_refcache();
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    irefcachepush(cache, NULL);
    /* nothing happend */
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    iref *ref = irefnew(iref);
    irefcachepush(cache, ref);
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 1);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==1);
    
    irelease(cache);
}

SP_CASE(irefcache, irefcacheclear) {
    irefcache *cache = _t_x_refcache();
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    irefcachepush(cache, NULL);
    /* nothing happend */
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    iref *ref = irefnew(iref);
    irefcachepush(cache, ref);
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 1);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==1);
    
    irefcacheclear(cache);
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 1);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 1);
    SP_TRUE(irefcachesize(cache)==0);
    
    irelease(cache);
}

SP_CASE(irefcache, irefcachesize) {
    irefcache *cache = _t_x_refcache();
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    irefcachepush(cache, NULL);
    /* nothing happend */
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 0);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==0);
    
    iref *ref = irefnew(iref);
    irefcachepush(cache, ref);
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 1);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 0);
    SP_TRUE(irefcachesize(cache)==1);
    
    irefcacheclear(cache);
    SP_EQUAL(_t_x_refcachenew_cnt, 0);
    SP_EQUAL(_t_x_refcacheadd_cnt, 1);
    SP_EQUAL(_t_x_refcacheenvicted_cnt, 1);
    SP_TRUE(irefcachesize(cache)==0);
    
    irelease(cache);
}

SP_CASE(irefcache, end) {
    SP_TRUE(1);
}