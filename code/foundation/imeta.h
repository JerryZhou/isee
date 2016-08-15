#ifndef _IMETA_H_
#define _IMETA_H_

#include "foundation/itype.h"
#include "foundation/imutex.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward declares */
struct imeta;
struct iobj;
    
/* tracing the iobj alloc */
typedef void (*ientryobjcalloctrace)(ithis i, struct imeta *meta, struct iobj *obj);
/* tracing the iobj free */
typedef void (*ientryobjfreetrace)(ithis i, struct imeta *meta, struct iobj *obj);
/* make all iobj has the hash values */
typedef int (*ientryobjhash)(ithis i, struct imeta *meta, struct iobj *obj);
/* make all iobj can be compare with each other */
typedef int (*ientryobjcompare)(ithis i, struct imeta *meta, struct iobj *lfs, struct iobj *rfs);
/* entry for calloc iobj */
typedef void* (*ientryobjcalloc)(ithis i, struct imeta *meta); /* alloc the iobj */
/* entry for free iobj */
typedef void (*ientryobjfree)(ithis i, void *ptr); /* free the iobj */

/* type meta functions */
typedef struct imetafuncs {
    ientryobjcalloctrace tracecalloc; /* trace all obj calloc */
    ientryobjfreetrace tracefree; /* trace all obj free */
    
    ientryobjhash _hash; /* all iobj can be do hash */
    ientryobjcompare _compare; /* all iobj can be do compare */
}imetafuncs;
    
/* type meta allocator */
typedef struct imetaallocator {
    ientryobjcalloc fcalloc;    /* should imp the calloc */
    ientryobjfree ffree;
} imetaallocator;
    
/* type-meta-information */
typedef struct imeta {
    const char* name;           /* type name */
    size_t size;                /* type size in bytes */
    size_t capacity;            /* type capacity */
    int32_t flag;               /* type flag mark the meta state */

    imetafuncs *funcs;          /* type meta-funcs */
    imetaallocator *allocator;  /* type allocator */
    
    /* support thread safe for meta system */
#if iithreadsafe
    imutex mutex; /*will never release resouce until program ended */
#endif
}imeta;
    
/*Hepler Macro for log*/
#define __imeta_format "Meta-Obj: (%15.15s, %5lu, %5lu) Cache: ("__iobjcache_format")"
#define __imeta_value(meta) (meta)->name,(meta)->size,(meta)->capacity,__iobjcache_value(iobjcacheget(meta))
    
/* type-meta-flag */
typedef enum IMetaFlag {
    IMetaFlag_Init = 1<<1,
    IMetaFlag_Invalid = 1<<2,
} IMetaFlag;

/* get meta information by meta-index */
imeta *imetaget(int idx);

/* regist a type with cache, return the meta-index */
int imetaregister(const char* name, size_t size, size_t capacity);

/* calloc a obj by meta-system */
void *imetacalloc(imeta *meta);

/* free the object to right meta-system */
void imetafree(void *p);

/* log all the memory state in meta-system */
void imetamemorystate();

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
