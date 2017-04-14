#ifndef _IOBJ_H_
#define _IOBJ_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* forward declares */
struct imeta;

/* basic memory-obj */
typedef struct iobj {
    const struct imeta *meta;     /* description of iobj */
    struct iobj *next;      /* next object in cache */
    iptr othis;            /* store the self-explain instance, values extends danymics */
    
    char addr[];            /* the address of sub object*/
}iobj;
    
/* caculating the offset of real iobj */
#define __iobj(p) ((p) ? (iobj*)((char*)(p) - sizeof(iobj)) : NULL)
#define __irobj(o) ((o) ? (o)->addr : NULL)

/* get the meta of obj */
const struct imeta *iobjgetmeta(iconstptr p);
/* if the obj is what we required */
int iobjistype(iconstptr p, const char* name);
    
/* include imetatypes.h */
#define iobjmalloc(type) ((type*)imetacalloc(imetaof(type)))
#define iobjfree(p) do { imetafree(p); p = NULL; } while(0)
/* quickly type-compare */
#define iistype(p, type) (iobjgetmeta(p) == imetaof(type))
    
/* the obj assign */
void iobjassign(const struct imeta *, iptr dst, iconstptr src);
    
/* the hash code */
uint64_t iobjhash(const struct imeta *, iconstptr obj);
    
/* the compare */
int iobjcompare(const struct imeta *, iconstptr lfs, iconstptr rfs);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif


