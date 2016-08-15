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
    struct imeta *meta;     /* description of iobj */
    struct iobj *next;      /* next object in cache */
    ithis xthis;            /* values extends danymics */
    
    char addr[];            /* the address of sub object*/
}iobj;
    
/* caculating the offset of real iobj */
#define __iobj(p) ((p) ? (iobj*)((char*)(p) - sizeof(iobj)) : NULL)

/* get the meta of obj */
struct imeta *iobjgetmeta(const void *p);
/* if the obj is what we required */
int iobjistype(const void *p, const char* name);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif


