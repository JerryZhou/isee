#ifndef _IOBJCACHE_H_
#define _IOBJCACHE_H_

#include "foundation/platform/imutex.h"
#include "foundation/memory/imemorystatistics.h"
#include "foundation/core/imeta.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward declares */
struct iobj;

/* object-cache */
typedef struct iobjcache {
    ideclaremetaallocator; /* should imp the calloc */
    
    struct iobj *root;
    size_t capacity;
    size_t num;
    size_t flag;
    
    imemorystatistics statis; /* mutex */
}iobjcache;
    
#define __iobjcache_format "cache: %lu/%lu, statis:("__istatis_format")"
#define __iobjcache_value(cache) (cache)->num,(cache)->capacity,__istatis_value(&((cache)->statis))
   
/* make a cache able allocator */
imetaallocator *imakecacheableallocator(imeta *meta, size_t capacity);
    
/* free the memory taken by allocator */
void iobjcachefree(imetaallocator *allocator);
    
/* get a objcache from the meta-system */
iobjcache* iobjcacheget(const imeta *meta);
    
/* set the obj cache capacity */
void iobjcachesetcapacity(iobjcache *cache, size_t capacity);
    
/* get the memory for objcache, if meta is null then return the global-memory-statis */
imemorystatistics *iobjcachestatis(imeta *meta);
    
/* free all the cached object in the meta-system with the right meta */
void iobjcacheclear(imeta *meta);

/* Trace the memory size */
typedef enum EnumObjCacheMemoerySizeKind {
    EnumObjCacheMemoerySizeKind_Alloced,
    EnumObjCacheMemoerySizeKind_Freed,
    EnumObjCacheMemoerySizeKind_Hold,
} EnumAoiMemoerySizeKind;
    
/* calculating the memory size taking by meta in what we want kind */
int64_t iobjcachememorysize(const void *meta, int kind);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
