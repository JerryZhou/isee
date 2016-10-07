#include "foundation/math/iquat.h"
#include "foundation/math/imath.h"

SP_SUIT(iquat);

SP_CASE(iquat, iquatisidentity) {
    iquat quat;
    iquatidentity(&quat);
    SP_TRUE(iquatisidentity(&quat));
}

SP_CASE(iquat, iquatisequal) {
    iquat quat;
    __iscaler_fill_4(&quat, 0, 0, 0, 4);
    SP_FALSE(iquatisequal(&quat, &kiquat_identity));
    
    iquatidentity(&quat);
    SP_TRUE(iquatisequal(&quat, &kiquat_identity));
}

SP_CASE(iquat, iquatexp) {
    iquatexp(NULL, NULL);
    SP_TRUE(1);
}

SP_CASE(iquat, iquatln) {
    iquatln(NULL, NULL);
    SP_TRUE(1);
}

SP_CASE(iquat, end) {
    SP_TRUE(1);
}