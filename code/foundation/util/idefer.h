#ifndef _IDEFER_H_
#define _IDEFER_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

// forward declares
struct idefercontext;
struct iarray;

// defer functions
typedef void (*ideferfnc)(struct idefercontext *);

// defer stack
typedef struct idefercontext  {
    struct iarray *stack;
} idefercontext;

// init the context
void ideferinit(idefercontext *context);

// add fnc to defer-calling
void idefer(idefercontext *context, ideferfnc fnc);

// execauting the idefer-behavior
void ideferexec(idefercontext *);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IDEFER_H_ */
