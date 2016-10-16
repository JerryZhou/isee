#ifndef _IWREF_H_
#define _IWREF_H_

#include "foundation/itype.h"
#include "foundation/core/iref.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* weak reference: we can do operators as iref: iretain; irelease; iassign */
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
#define iwassign(dst, src) do {  \
    if (dst && src && (iref*)(dst->_wref) == (iref*)(src)) { \
        break; \
    }\
    irelease(dst);\
    if (src) {\
        dst = iwrefmake((iref*)(src)); \
    } else {\
        dst = NULL;\
    }\
} while(0)

/* wrap iwrefmake */
#define iwrefnew(ref) iwrefmake(irefcast(ref))
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif
