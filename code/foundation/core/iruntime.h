#ifndef _IRUNTIME_H_
#define _IRUNTIME_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward declares */
struct itype;
struct iinstance;
struct imethod;
struct ifield;
struct ispecs;
   
/* raw-type-definition */
typedef struct itype {
    const char *name;
    struct ifield *fields;
    struct imethod *methods;
} itype;
    
/* raw-instance-definition */
typedef struct iinstance {
    itype *type;
    void *value;
}iinstance;
    
/* raw-specs-definition */
typedef struct ispecs {
    const char *name;
    struct imethod *methods;
} ispecs;
    
/* raw-canon-definition */
typedef struct icanon {
    struct iinstance *instance;
    struct ispecs *specs;
} icanon;

/* raw-method-definition */
typedef struct imethod {
    const char *name;
} imethod;

/* raw-field-definition */
typedef struct ifield {
    const char *name;
    struct itype *type;
    size_t offset;
} ifield;
    
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IRUNTIME_H_ */
