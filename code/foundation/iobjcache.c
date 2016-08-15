#include "foundation/iobjcache.h"
#include "foundation/imemory.h"
#include "foundation/iobj.h"

/* make some salt in objcache */
#define _IOBJCACHE_CLS_SALT 0xefeefe

/* wrap the thread safe-policy */
#if iithreadsafe
static imutex *_imeta_mutex() {
    static imutex realmutex;
    static imutex *mutex = NULL;
    if (mutex == NULL) {
        mutex = &realmutex;
        imutexinit(mutex);
    }
    return mutex;
}
#define _imeta_global_lock imutexlock(_imeta_mutex())
#define _imeta_global_unlock imutexunlock(_imeta_mutex())
#define _imeta_lock imutexlock(&meta->mutex)
#define _imeta_unlock imutexunlock(&meta->mutex)
#else
#define _imeta_global_lock (void)0
#define _imeta_global_unlock (void)0
#define _imeta_lock (void)meta
#define _imeta_unlock (void)meta
#endif

/* statics-for-global: alloc and free */
static imemorystatistics _g_global_statis;

/* iobj: direct alloc */
iobj *_imetadirectalloc(iobjcache *xthis, imeta *meta) {
    size_t newsize = sizeof(struct iobj) + meta->size;
    iobj *obj = (iobj*)icalloc(1, newsize);
    obj->meta = meta;
    
    /* meta-statis */
    _imeta_lock;
    imemorystatisbehavior_alloc(&xthis->statis, newsize);
    _imeta_unlock;
    
    /* global-statis */
    _imeta_global_lock;
    imemorystatisbehavior_alloc(&_g_global_statis, newsize);
    _imeta_global_unlock;
    
    /* tracing */
    if (meta->funcs && meta->funcs->tracecalloc) {
        meta->funcs->tracecalloc((ithis)xthis, meta, obj);
    }
    
    return obj;
}

/* iobj: direct free */
void _imetadirectfree(iobjcache *xthis, iobj *obj) {
    imeta *meta = obj->meta;
    size_t newsize = obj->meta->size + sizeof(iobj);
    
    /* tracing the free */
    if (meta->funcs && meta->funcs->tracefree) {
        meta->funcs->tracefree((ithis)xthis, meta, obj);
    }
    
    /* meta-statis */
    _imeta_lock;
    imemorystatisbehavior_free(&xthis->statis, newsize);
    _imeta_unlock;
    
    /* global-statis */
    _imeta_global_lock;
    imemorystatisbehavior_free(&_g_global_statis, newsize);
    _imeta_global_unlock;
    
    ifree(obj);
}

/**
 * 尝试从缓冲区拿对象
 */
static iobj *_icachepoll(iobjcache *cache, imeta *meta) {
    iobj *obj = NULL;
    
    _imeta_lock;
    if (cache->num) {
        obj = cache->root;
        cache->root = cache->root->next;
        obj->next = NULL;
        --cache->num;
        memset(obj->addr, 0, meta->size);
        _imeta_unlock;
    } else {
        _imeta_unlock;
        
        obj = _imetadirectalloc(cache, meta);
    }
    
    return obj;
}

/* Meta 的缓冲区管理 */
void _icachepush(iobjcache *cache, iobj *obj) {
    imeta *meta = obj->meta;
    
    _imeta_lock;
    if (cache->num < cache->capacity) {
        obj->next = cache->root;
        cache->root = obj;
        ++cache->num;
        _imeta_unlock;
    } else {
        _imeta_unlock;
        
        _imetadirectfree(cache, obj);
    }
}

/* cache-allocator: allocate from obj-cache */
static void* _iobjcache_ientryobjcalloc(ithis i, struct imeta *meta) {
    iobjcache *xthis = (iobjcache*)(i);
    iobj *obj = _icachepoll(xthis, meta);
    return obj->addr;
}


/* cache-allocator: free to obj-cache */
static void _iobjcache_ientryobjfree(ithis i, void *ptr) {
    iobjcache *xthis = (iobjcache*)(i);
    _icachepush(xthis, __iobj(ptr));
}

/* cache-allocator: make one */
imetaallocator *imakecacheableallocator(imeta *meta, size_t capacity) {
    iobjcache *cache = (iobjcache*)icalloc(1, sizeof(iobjcache));
    cache->fcalloc = _iobjcache_ientryobjcalloc;
    cache->ffree = _iobjcache_ientryobjfree;
    cache->capacity = capacity;
    cache->flag = _IOBJCACHE_CLS_SALT;
    return (imetaallocator*)(cache);
}

/* get a objcache from the meta-system */
iobjcache* iobjcacheget(imeta *meta) {
    iobjcache *cache = (iobjcache*)meta->allocator;
    icheckret(cache && cache->flag==_IOBJCACHE_CLS_SALT, NULL);
    return cache;
}

/* get the memory for objcache, if meta is null then return the global-memory-statis */
imemorystatistics *iobjcachestatis(imeta *meta) {
    iobjcache *cache = iobjcacheget(meta);
    return cache ? &cache->statis : &_g_global_statis;
}

/* free all the cached object in the meta-system with the right meta */
void iobjcacheclear(imeta *meta) {
    iobjcache *cache = iobjcacheget(meta);
    iobj *next = NULL;
    iobj *cur = NULL;
    icheck(cache->num);
    
    _imeta_lock;
    cur = cache->root;
    while (cur) {
        next = cur->next;
        _imetadirectfree(cache, cur);
        cur = next;
    }
    cache->root = NULL;
    cache->num = 0;
    _imeta_unlock;
}

/* calculating the memory size taking by meta in what we want kind */
int64_t iobjcachememorysize(const void *meta, int kind) {
    iobjcache *cache = meta ? (iobjcache*)((imeta*)meta)->allocator:NULL;
    icheckret(!cache || (cache && cache->flag == _IOBJCACHE_CLS_SALT), 0);
    switch (kind) {
        case EnumObjCacheMemoerySizeKind_Alloced:
            return cache ? cache->statis.alloced : _g_global_statis.alloced;
            break;
        case EnumObjCacheMemoerySizeKind_Freed:
            return cache ? cache->statis.freed : _g_global_statis.freed;
            break;
        case EnumObjCacheMemoerySizeKind_Hold:
            return cache ? cache->statis.current : _g_global_statis.current;
            break;
        default:
            break;
    }
    return 0;
}