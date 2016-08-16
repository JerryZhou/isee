#ifndef _IREF_H_
#define _IREF_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* declare the iref-sub struct */
#define irefdeclare \
    volatile uint32_t _ref; \
    volatile struct iwref * _wref; \
    struct irefcache* _cache; \
    ientryconstructor _constructor; \
    ientrydestructor _destructor; \
    ientrywatch _watch
    
/* iref cast target */
#define icast(type, v) ((type*)(v))
/* cast to iref */
#define irefcast(v) icast(iref, v)
    
/* forward declares */
struct iref;
struct irefcache;
struct iwref;
    
/* iref constructor */
typedef void (*ientryconstructor)(struct iref* ref);

/* iref destructor */
typedef void (*ientrydestructor)(struct iref* ref);

/* iref watcher: call when deref */
typedef void (*ientrywatch)(struct iref* ref);

/* basic iref-struct */
typedef struct iref {
    irefdeclare;
}iref;

/* store details in imeta xthis */
typedef struct irefmeta {
    struct irefcache *cache;
    ientrywatch watch;
}irefmeta;

/* retain the reference */
int irefretain(iref *ref);

/* release the reference */
void irefrelease(iref *ref);

/* macro wrap for irefretain */
#define iretain(p) do { if(p) irefretain((iref*)(p)); } while(0)

/* macro wrap for irefrelease */
#define irelease(p) do { if(p) irefrelease((iref*)(p)); } while(0)

/* macro wrap for irefretain and irefrelease */
#define iassign(dst, src) do { if(src != dst) { irelease(dst); iretain(src); dst = src; } } while(0)
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif
 
    