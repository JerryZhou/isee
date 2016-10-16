#include "foundation/platform/ientry.h"
#include "simpletest.h"

SP_SUIT(ientry);

SP_CASE(ientry, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

