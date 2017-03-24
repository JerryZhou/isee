#include "foundation/util/iregex.h"
#include "foundation/core/imetatypes.h"

// NFA (non-deterministic finite automata)
// DFA (deterministic finite automaton)
/*******************************************************/
/*
 * https://swtch.com/~rsc/regexp/regexp1.html
 * e1|e2
 * e1e2
 * e1*
 * e1+
 * e1?
 */
typedef struct iexpression {
    istring *expression;
} iexpression;

typedef struct imachine {
    struct imachine *parent;
} imachine;


/* destructor */
void iregex_destructor(const struct imeta* x, iptr o) {
    
}

/**/
iregex* iregexcompile(const istring *reg) {
    return irefnew(iregex);
}

/**/
ibool iregexmatch(iregex* reg, const istring *s) {
    return iino;
}

/**/
iarray* iregexmatchall(iregex* reg, const istring *s) {
    return NULL;
}
