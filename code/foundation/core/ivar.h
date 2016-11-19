#ifndef _IVAR_H_
#define _IVAR_H_

#include "foundation/itype.h"
#include "foundation/core/iref.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward -declares */
struct imeta;
   
/* enum -type -index */
typedef enum EnumIvarType {
    EnumIvarType_Int,
    EnumIvarType_I64,
    EnumIvarType_U64,
    EnumIvarType_Real,
    EnumIvarType_Ref,
    EnumIvarType_Ptr,
    EnumIvarType_POD,
} EnumIvarType;
   
/* the ivar wrap all couldbeable */
typedef struct ivar {
    irefdeclare;
    union {
        int i;
        int64_t i64;
        uint64_t u64;
        ireal real;
        iref *ref;
        void *ptr;
    } v ;
    struct imeta *meta; /* type-meta */
} ivar;
    
/* ivar type */
int ivartype(const ivar *var);
    
ibool ivaris(const ivar *var, const struct imeta *meta);
    
/* ivar destructor */
void ivar_destructor(iptr x, iobj *o);
   

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IVAR_H_ */
