#include "foundation/util/idefer.h"
#include "foundation/util/iarraytypes.h"

// init the context
void ideferinit(idefercontext *context) {
    icheck(context && context->stack==NULL);
    context->stack = iarraymakecopyable(8, sizeof(ideferfnc));
}

// add fnc to defer-calling
void idefer(idefercontext *context, ideferfnc fnc) {
     iarrayadd(context->stack, &fnc);
}

// execauting the idefer-behavior
void ideferexec(idefercontext *context) {
    int i = 0;
    ideferfnc *fnc;
    icheck(context && context->stack);

    // reverse range the array
    i = iarraylen(context->stack);
    for(; i; i--) {
        fnc = (ideferfnc*)iarrayat(context->stack, i-1);
        if (*fnc) {
            (*fnc)(context);
        }
    }
    irefdelete(context->stack);
}


