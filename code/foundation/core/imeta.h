#ifndef _IMETA_H_
#define _IMETA_H_

#include "foundation/itype.h"
#include "foundation/platform/imutex.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*
 * todos:  
 *      meta-flag: support-the-rawtypes: ref and pod
 *      memory-alignment
 */

/* forward declares */
struct imeta;
struct iobj;
   
/* entry for calloc : i default point to struct iobjcache */
typedef iptr (*ientryobjcalloc)(const struct imeta *meta); /* alloc the default iobj */
/* entry for free : i default point to struct iobjcache */
typedef void (*ientryobjfree)(const struct imeta *meta, iptr ptr); /* free the value */
    
/* tracing the alloc: i default point to struct imetafuncs  */
typedef void (*ientryobjconstructor)(const struct imeta *meta, iptr ptr);
/* tracing the free: i default point to struct imetafuncs */
typedef void (*ientryobjdestructor)(const struct imeta *meta, iptr ptr);
    
/* make all has the hash values: i default point to struct imetafuncs */
typedef uint64_t (*ientryobjhash)(const struct imeta *meta, iconstptr ptr);
/* make all can be compare with each other: i default point to struct imetafuncs  */
typedef int (*ientryobjcompare)(const struct imeta *meta, iconstptr lfs, iconstptr rfs);
    
/* entry for free : i default point to struct iobjcache */
typedef void (*ientryobjassign)(const struct imeta *meta, iptr dst, iconstptr src); /* copy the value */
    
/* all internal meta-config informations */
typedef struct imetaconfig {
    const char* name;       /* config the type name */
    size_t size;            /* config the type size in bytes */
    size_t align;           /* config the type align in bytes */
    size_t capacity;        /* config the type cache in count */
    int32_t flag;           /* config the type flag */
    
    iptr mthis;             /* config the type-meta-mthis */
    
    ientryobjconstructor constructor;   /* config the type-constructor */
    ientryobjdestructor destructor;     /* config the type-destructor */
    ientryobjassign assign;             /* config the type-assign */
    
    ientryobjhash hash;                 /* config the type-hash */
    ientryobjcompare compare;           /* config the type-compare */
}imetaconfig;

/* type meta functions */
typedef struct imetafuncs {
    ientryobjconstructor constructor;       /* trace all obj calloc */
    ientryobjdestructor destructor;         /* trace all obj free */
    ientryobjassign assign;                 /* all iobj can be do copy */
    
    ientryobjhash hash;                     /* all iobj can be do hash */
    ientryobjcompare compare;               /* all iobj can be do compare */
    
    /* should we add anthor contructor and destructor here ?? */
}imetafuncs;

/* should be register with funcs */
typedef imetafuncs* (*ientrymake_funcs)(struct imeta* meta, iptr i);
    
/* declare the meta-allocator */
#define ideclaremetaallocator ientryobjcalloc fcalloc; ientryobjfree ffree
    
/* type meta allocator */
typedef struct imetaallocator {
    ideclaremetaallocator; /* should imp the calloc */
} imetaallocator;

/* should be register with allocator */
typedef imetaallocator* (*ientrymake_allocator)(const struct imeta* meta, iptr i);
 
/* * * */
/* todos: */
/* alloc-flag-alignment */
/* * * */
    
typedef enum EnumMetaFlag {
    /* memory bit */
    EnumMetaFlag_MemoryAligned = 1, /* memory-alignment */
    
    /* type-kind-bit [2-4]*/
    EnumMetaFlag_Ref = 1<<1,    /* ref-type value: sub-class of iref */
    EnumMetaFlag_POD = 1<<2,    /* the value: plain-of-data */
    EnumMetaFlag_Complex = 1<<3,
} EnumMetaFlag;
    
/* type-meta-information */
typedef struct imeta {
    const char* name;           /* type name */
    size_t size;                /* type size in bytes */
    size_t align;               /* type align in bytes */
    int32_t flag;               /* type flag mark the meta state */

    imetafuncs *funcs;          /* type meta-funcs */
    imetaallocator *allocator;  /* type allocator */
    
    /* support thread safe for meta system */
#if iithreadsafe
    imutex mutex; /*will never release resouce until program ended */
#endif
    int index;                  /* global meta index */
    iptr mthis;                /* store the self-explan meta-mthis meanings */
}imeta;
    
/*Hepler Macro for log*/
#define __imeta_format "Meta-Obj: (%15.15s, %5lu) Cache: ("__iobjcache_format")"
#define __imeta_value(meta) (meta)->name,(meta)->size,__iobjcache_value(iobjcacheget(meta))
    
/* type-meta-flag */
typedef enum IMetaFlag {
    IMetaFlag_Init = 1<<1,
    IMetaFlag_Invalid = 1<<2,
} IMetaFlag;

/* get meta information by meta-index */
const imeta *imetaget(int idx);
    
/* get meta-index */
int imetaindexof(const imeta *meta);

/* register a type with cache, return the meta-index */
int imetaregister(const char* name, size_t size);

/* register a type with details */
int imetaregisterwithdetails(const char *name, size_t size,
                             size_t capacity,
                             ientryobjconstructor constructor,
                             ientryobjconstructor destructor);
    
/* register a type with capacity, return the meta-index */
int imetaregisterwithcapacity(const char *name, size_t size, size_t capacity);

/* register a type with config, return the meta-index */
int imetaregisterwithconfig(const imetaconfig *config);

/* register a type with cache, return the meta-index */
int imetaregisterwith(const char* name, size_t size,
                      ientrymake_funcs funs, iptr funsthis,
                      ientrymake_allocator allocator, iptr allocatorthis,
                      iptr mthis);

/* calloc a obj by meta-system */
void *imetacalloc(const imeta *meta);

/* free the object to right meta-system */
void imetafree(void *p);

/* log all the memory state in meta-system */
void imetamemorystate();

/* return current max meta-index */
int imetaindexcur();

/* meta-index */
#define imetaindex(type)    imeta_##type##_index
/* meta-get by meta-index */
#define imetaof(type) imetaget(imetaindex(type))
    
/* meta-call */
#define imetacall(meta, fun, ...) do { if( (meta) && (meta)->funcs && (meta)->funcs->##fun ) { (meta)->funcs->##fun##((meta), __VA_ARGS__) } while(0)

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
