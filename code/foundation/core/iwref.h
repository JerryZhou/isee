#ifndef _IWREF_H_
#define _IWREF_H_

#include "foundation/itype.h"
#include "foundation/core/iref.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* 弱引用: we can do operators as iref: iretain; irelease; iassign */
/* the iwref not thread safe: only use iwref in one thread context */
typedef struct iwref {
    irefdeclare;
}iwref;

/* make a weak iref by ref */
iwref *iwrefmake(iref *ref);

/* make a weak iref by wref */
iwref *iwrefmakeby(iwref *wref);

/* make strong ref: need call irelease */
iref *iwrefstrong(iwref *wref);

/* make strong ref: unneed call irelease */
iref *iwrefunsafestrong(iwref *wref);

/* ref assign to weak ref */
#define iwassign(dst, src) do { if (dst && (iref*)(dst->wref) == (iref*)(src)) { \
break; } irelease(dst); dst = iwrefmake((iref*)(src)); } while(0)

    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif
