/* declare all the types for user defines */
#include "foundation/core/imetatypes.h"

/* for user types */
#undef __iudeclaremeta

#define __iudeclaremeta(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xassign) irealimplementregisterfull(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xassign) 

#define __iudeclare imetaconfig config
