#ifndef _IREF_H_
#define _IREF_H_

#include "foundation/itype.h"
#include "foundation/core/iobj.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* declare the iref-sub struct */
#define irefdeclare \
    volatile uint32_t _ref; \
    volatile struct iwref * _wref;\
    ithis _rthis; \
    struct iwref * _watcher

/* iref cast target */
#define icast(type, v) ((type*)(v))
/* cast to iref */
#define irefcast(v) icast(iref, v)
/* iobj cast to iref */
#define __iref(o) irefcast(__irobj(o))
    
/* forward declares */
struct iref;
struct iwref;
struct irefwatcher;
    
/* iref watcher: call when deref */
typedef void (*ientrywatch)(struct irefwatcher *watcher, struct iref *ref);

/* declare the watcher */
#define irefwatcherdeclare \
    irefdeclare;\
    ientrywatch watch
    
/* watch the iref */
typedef struct irefwatcher {
    irefwatcherdeclare;
}irefwatcher;
   

/* basic iref-struct */
typedef struct iref {
    irefdeclare;
}iref;

/* make a new iref with meta-index */
iref* irefmalloc(int index);

/* retain the reference */
int irefretain(iref *ref);

/* release the reference */
void irefrelease(iref *ref);
    
/* return the ref self and retain it */
iref *irefassistretain(iref *ref);

/* macro wrap for irefretain */
#define iretain(p) do { if(p) irefretain((iref*)(p)); } while(0)

/* macro wrap for irefrelease */
#define irelease(p) do { if(p) irefrelease((iref*)(p)); } while(0)

/* macro wrap for irefretain and irefrelease */
#define iassign(dst, src) do { if(src != dst) { irelease(dst); iretain(src); dst = src; } } while(0)
   
/* macro wrap a ref-sub-type new: will retain it */
#define irefnew(type) ((type*)irefmalloc(imetaindex(type)))
    
/* get the private pointer */
#define irefthis(type, ref) icast(type, (ref)->_rthis)
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif
 
    