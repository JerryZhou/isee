/* declare all the types for user defines */
#include "foundation/core/imetatypes.h"

/* for user types */
#undef __iudeclaremeta

#define __iudeclaremeta(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xcopy) irealimplementregisterfull(type, xsize, xalign, xflag, xcapacity,  xmptr, xconstructor, xdestructor, xhash, xcompare, xcopy) 

#define __iudeclare imetaconfig config
