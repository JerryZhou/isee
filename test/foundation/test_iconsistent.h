#include "foundation/algorithm/iconsistent.h"

SP_SUIT(iconsistent);

SP_CASE(iconsistent, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
