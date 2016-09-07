#include "foundation/math/ivec.h"

SP_SUIT(ivec2);

SP_CASE(ivec2, ivec2subtractpoint) {
    ipos p0 = {1, 1};
    ivec2 v = ivec2subtractpoint(&kipos_zero, &p0);
    SP_TRUE(v.values[0] == -1);
    SP_TRUE(v.values[1] == -1);
}

SP_CASE(ivec2, ivec2movepoint) {
    ipos p0 = {1, 1};
    ipos p1 = ivec2movepoint(&kivec2_axis_x, 1, &p0);
    SP_TRUE(p1.x == 2);
    SP_TRUE(p1.y == 1);
}

SP_CASE(ivec2, basic_funcs) {
    // ivec2add
    //
    {
    ivec2 v0 = ivec2add(&kivec2_axis_x, &kivec2_axis_y);
    SP_TRUE(v0.v.x == 1);
    SP_TRUE(v0.v.y == 1);
    }
    {
        ivec2 v0 = ivec2subtract(&kivec2_axis_x, &kivec2_axis_y);
        SP_TRUE(v0.v.x == 1);
        SP_TRUE(v0.v.y == -1);
    }
    {
        ivec2 v0 = ivec2multipy(&kivec2_axis_xy, 2);
        SP_TRUE(v0.v.x == 2);
        SP_TRUE(v0.v.y == 2);
    }
    {
        ireal v0 = ivec2dot(&kivec2_axis_x, &kivec2_axis_y);
        SP_TRUE(v0 == 0);
    }
    {
        ireal v = ivec2lengthsqr(&kivec2_axis_xy);
        SP_TRUE(v == 2);
        ireal vx = ivec2length(&kivec2_axis_xy);
        vx *= vx;
        SP_TRUE(ireal_equal(vx, v));
    }
    {
        ivec2 v = ivec2abs(&kivec2_axis_xy);
        SP_TRUE(v.v.x == 1);
        SP_TRUE(v.v.y == 1);
        v = ivec2multipy(&v, -1);
        SP_TRUE(v.v.x == -1);
        SP_TRUE(v.v.y == -1);
        v = ivec2abs(&v);
        SP_TRUE(v.v.x == 1);
        SP_TRUE(v.v.y == 1);
    }
    {
        ivec2 v = ivec2normalize(&kivec2_axis_xy);
        ireal len = ivec2length(&kivec2_axis_xy);
        ireal vx = 1.0f/len;
        SP_TRUE(ireal_equal(v.v.x , vx));
        SP_TRUE(ireal_equal(v.v.y , vx));
    }
    
    {
        ivec2 p = ivec2parallel(&kivec2_axis_xy, &kivec2_axis_x);
        SP_TRUE(ireal_equal(p.v.x, 1));
        SP_TRUE(ireal_equal(p.v.y, 0));
        
        ivec2 per = ivec2perpendicular(&kivec2_axis_xy, &kivec2_axis_x);
        SP_TRUE(ireal_equal(per.v.x, 0));
        SP_TRUE(ireal_equal(per.v.y, 1));
        
    }
}

SP_CASE(ivec2, end) {
    SP_TRUE(1);
}