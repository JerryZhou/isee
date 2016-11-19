#include "foundation/core/ivar.h"

SP_SUIT(ivar);

SP_CASE(ivar, ivaris) {
    ivar *var = irefnew(ivar);
    SP_TRUE(ivaris(var, NULL));
    SP_TRUE(ivaris(var, imetaof(inull)));
    irefdelete(var);
}

SP_CASE(ivar, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
