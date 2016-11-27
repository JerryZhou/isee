#include "foundation/algorithm/iconsistent.h"

SP_SUIT(iconsistent);

SP_CASE(iconsistent, make) {
    iconsistent *c = iconsistentmake(20, 30);
    SP_TRUE(iconsistentsize(c) == 0);
    irefdelete(c);
}

SP_CASE(iconsistent, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
