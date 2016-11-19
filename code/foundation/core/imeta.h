#ifndef _IMETA_H_
#define _IMETA_H_

#include "foundation/itype.h"
#include "foundation/platform/imutex.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward declares */
struct imeta;
struct iobj;
    
/* tracing the iobj alloc: i default point to struct imetafuncs  */
typedef void (*ientryobjconstructor)(iptr i, struct iobj *obj);
/* tracing the iobj free: i default point to struct imetafuncs */
typedef void (*ientryobjdestructor)(iptr i, struct iobj *obj);
    
/* make all iobj has the hash values: i default point to struct imetafuncs */
typedef int (*ientryobjhash)(iptr i, struct iobj *obj);
/* make all iobj can be compare with each other: i default point to struct imetafuncs  */
typedef int (*ientryobjcompare)(iptr i, struct iobj *lfs, struct iobj *rfs);
    
/* entry for calloc iobj: i default point to struct iobjcache */
typedef void* (*ientryobjcalloc)(iptr i, const struct imeta *meta); /* alloc the iobj */
/* entry for free iobj: i default point to struct iobjcache */
typedef void (*ientryobjfree)(iptr i, void *ptr); /* free the iobj */
    
/* all internal meta-config informations */
typedef struct imetaconfig {
    const char* name;       /* config the type name */
    size_t size;            /* config the type size in bytes */
    size_t capacity;        /* config the type cache in count */
    iptr mthis;            /* config the type-meta-mthis */
    
    ientryobjconstructor constructor;   /* config the type-constructor */
    ientryobjdestructor destructor;     /* config the type-destructor */
    ientryobjhash hash;                 /* config the type-hash */
    ientryobjcompare compare;           /* config the type-compare */
}imetaconfig;

/* type meta functions */
typedef struct imetafuncs {
    ientryobjconstructor constructor;       /* trace all obj calloc */
    ientryobjdestructor destructor;         /* trace all obj free */
    
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
    EnumMetaFlag_MemoryAligned = 1, /* memory-alignment */
} EnumMetaFlag;
    
/* type-meta-information */
typedef struct imeta {
    const char* name;           /* type name */
    size_t size;                /* type size in bytes */
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

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
