/* declare all the types for user defines */
#include "foundation/core/imetatypes.h"

/* for foundation types */
#undef __ideclaremeta
/* name, size, capacity, mthis, constructor, destructor, hash, compare */
#define __ideclaremeta(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xassign) {\
    .name=#type, .size=xsize, .align=xalign, .flag=xflag, .capacity=xcapacity, .mthis=xmptr, .constructor=xconstructor, .destructor=xdestructor, .hash=xhash, .compare=xcompare, .assign=xassign}

/* for user types */
#undef __iudeclaremeta
#define __iudeclaremeta(type) irealdeclareregister(type)
