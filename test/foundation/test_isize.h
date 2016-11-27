#include "foundation/math/isize.h"

SP_SUIT(isize);

SP_CASE(isize, nothing) {
    SP_EQUAL(1, 1);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

