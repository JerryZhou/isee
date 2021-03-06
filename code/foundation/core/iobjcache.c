#include "foundation/core/iobjcache.h"
#include "foundation/core/iobj.h"
#include "foundation/memory/imemory.h"

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
#define _imeta_lock imutexlock((imutex*)&meta->mutex)
#define _imeta_unlock imutexunlock((imutex*)&meta->mutex)
#else
#define _imeta_global_lock (void)0
#define _imeta_global_unlock (void)0
#define _imeta_lock (void)meta
#define _imeta_unlock (void)meta
#endif

/* statics-for-global: alloc and free */
static imemorystatistics _g_global_statis;

/* * * */
/* todos: */
/* alloc-flag-alignment */
/* * * */

/* iobj: direct alloc */
static iobj *_imetadirectalloc(iobjcache *xthis, const imeta *meta) {
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
    
    return obj;
}

/* iobj: direct free */
static void _imetadirectfree(iobjcache *xthis, iobj *obj) {
    const imeta *meta = obj->meta;
    size_t newsize = obj->meta->size + sizeof(iobj);
    
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
 * try to allocate the obj from cache first */
static iobj *_icachepoll(iobjcache *cache, const imeta *meta) {
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
    
    /* tracing */
    if (meta->funcs && meta->funcs->constructor) {
        meta->funcs->constructor((iptr)cache, __irobj(obj));
    }
    
    return obj;
}

/* Meta -Cache: Managing */
static void _icachepush(iobjcache *cache, iobj *obj) {
    const imeta *meta = obj->meta;
    
    /* tracing the free */
    if (meta->funcs && meta->funcs->destructor) {
        meta->funcs->destructor((iptr)cache, __irobj(obj));
    }
    
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
static void* _iobjcache_ientryobjcalloc(const struct imeta *meta) {
    iobjcache *xthis = (iobjcache*)(meta->allocator);
    iobj *obj = _icachepoll(xthis, meta);
    return obj->addr;
}


/* cache-allocator: free to obj-cache */
static void _iobjcache_ientryobjfree(const struct imeta *meta, iptr ptr) {
    iobjcache *xthis = (iobjcache*)(meta->allocator);
    _icachepush(xthis, __iobj(ptr));
}

/* cache-allocator: make one */
imetaallocator *imakecacheableallocator(const imeta *meta, size_t capacity) {
    iobjcache *cache = (iobjcache*)icalloc(1, sizeof(iobjcache));
    cache->fcalloc = _iobjcache_ientryobjcalloc;
    cache->ffree = _iobjcache_ientryobjfree;
    cache->capacity = capacity;
    cache->flag = _IOBJCACHE_CLS_SALT;
    return (imetaallocator*)(cache);
}

/* free the memory taken by allocator */
void iobjcachefree(imetaallocator *allocator) {
    iobjcache *cache = (iobjcache*)allocator;
    icheck(cache);
    cache->flag = 0; /* clear salt */
    ifree(cache);
}

/* get a objcache from the meta-system */
iobjcache* iobjcacheget(const imeta *meta) {
    iobjcache *cache = meta ? (iobjcache*)meta->allocator : NULL;
    icheckret(cache && cache->flag==_IOBJCACHE_CLS_SALT, NULL);
    return cache;
}

/* set the obj cache capacity */
void iobjcachesetcapacity(iobjcache *cache, size_t capacity) {
    cache->capacity = capacity;
}

/* get the memory for objcache, if meta is null then return the global-memory-statis */
imemorystatistics *iobjcachestatis(const imeta *meta) {
    iobjcache *cache = iobjcacheget(meta);
    return cache ? &cache->statis : &_g_global_statis;
}

/* free all the cached object in the meta-system with the right meta */
void iobjcacheclear(const imeta *meta) {
    iobjcache *cache = iobjcacheget(meta);
    iobj *next = NULL;
    iobj *cur = NULL;
    icheck(cache);
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
    imemorystatistics *statis = iobjcachestatis((imeta*)meta);
    switch (kind) {
        case EnumObjCacheMemoerySizeKind_Alloced:
            return statis->alloced;
            break;
        case EnumObjCacheMemoerySizeKind_Freed:
            return statis->freed;
            break;
        case EnumObjCacheMemoerySizeKind_Hold:
            return statis->current;
            break;
        default:
            break;
    }
    return 0;
}
