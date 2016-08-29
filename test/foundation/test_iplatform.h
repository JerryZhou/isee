#include "foundation/platform/iplatform.h"
#include "simpletest.h"

SP_SUIT(iplatform);

SP_CASE(iplatform, igetcurmicro) {
    SP_TRUE(igetcurmicro() != 0)
    
    int64_t tick0 = igetcurmicro();
    int64_t tick1 = igetcurmicro();
    
    SP_TRUE(tick1 >= tick0);
}

SP_CASE(iplatform, igetnextmicro) {
    int64_t tick0 = igetnextmicro();
    int64_t tick1 = igetnextmicro();
    
    SP_TRUE(tick1 > tick0);
}

SP_CASE(iplatform, igetcurtick) {
    int64_t tick0 = igetcurtick();
    int64_t tick1 = igetcurtick();
    
    SP_TRUE(tick1 >= tick0);
}

SP_CASE(iplatform, isleep) {
    int64_t tick0 = igetcurtick();
    
    isleep(10);
    
    int64_t tick1 = igetcurtick();
    
    SP_TRUE((tick1-tick0)>=10);
}

SP_CASE(iplatform, end) {
    SP_TRUE(1);
}