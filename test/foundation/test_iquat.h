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

SP_CASE(iquat, iquatinvert) {
    iquat quat;
    __iscaler_fill_4(&quat, 1, 2, 3, 4);
    
    iquat quatinvert;
    __iscaler_fill_4(&quatinvert, -1, -2, -3, -4);
    
    iquatinvert(&quat);
    SP_TRUE(iquatisequal(&quat, &quatinvert));
}

SP_CASE(iquat, iquatdot) {
    iquat quat;
    __iscaler_fill_4(&quat, 1, 2, 3, 4);
    
    ireal dot = iquatdot(&quat, &quat);
    SP_TRUE(ireal_equal(dot, 30));
}

SP_CASE(iquat, iquatlength) {
    iquat quat;
    __iscaler_fill_4(&quat, 0, 0, 3, 4);
    
    ireal lensqr = iquatlengthsqr(&quat);
    SP_TRUE(ireal_equal(lensqr, 25));
    ireal len = iquatlength(&quat);
    SP_TRUE(ireal_equal(len, 5));
}

SP_CASE(iquat, iquatmultipy) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatnormalize) {
    iquat quat;
    __iscaler_fill_4(&quat, 0, 0, 3, 4);
    
    iquat quatn;
    __iscaler_fill_4(&quatn, 0, 0, 0.6, 0.8);
    
    iquatnormalize(&quat);
    SP_TRUE(iquatisequal(&quat, &quatn));
    
    ireal len = iquatlength(&quat);
    SP_TRUE(ireal_equal(len, 1));
}

SP_CASE(iquat, end) {
    SP_TRUE(1);
}