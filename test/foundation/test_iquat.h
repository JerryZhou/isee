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
    
    ireal lensrc = iquatlengthsqr(&quat);
    iquat quatinvert;
    __iscaler_fill_4(&quatinvert, -1/lensrc, -2/lensrc, -3/lensrc, 4/lensrc);
    
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

SP_CASE(iquat, iquatrotateaxisangle) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatslerp) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatextractaxisangle) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatextractrotatearoundaxis) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatscale) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatassign) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatadd) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatsubtract) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatmultipyvec3) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatrotatebetweenvec3) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatlookrotate) {
    SP_TRUE(1);
}

SP_CASE(iquat, iquatfromrotatemat3) {
    iquat quat;
    iquatrotateaxisangle(&quat, &kivec3_axis_x, idegreestoradians(30));
   
    imat4 mat;
    imat4identity(&mat);
    imat4rotationx(&mat, idegreestoradians(30));
    
    imat3 rotmat;
    imat4extractrotateimat3(&mat, &rotmat);
    
    iquat rotquat;
    iquatfromrotatemat3(&rotquat, &rotmat);
    
    SP_TRUE(iquatisequal(&quat, &rotquat));
}

SP_CASE(iquat, end) {
    SP_TRUE(1);
}
