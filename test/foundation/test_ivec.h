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


SP_SUIT(ivec3);

SP_CASE(ivec3, base_funcs) {
    SP_TRUE(iiyes == ivec3isequal(&kivec3_axis_x, &kivec3_axis_x));
    
    SP_TRUE(iino == ivec3isequal(&kivec3_axis_x, &kivec3_axis_y));
    
    {
        ipos3 p0 = ivec3movepoint(&kivec3_axis_x, 1, &kipos3_zero);
    
        SP_TRUE(ireal_equal(p0.x, 1));
        SP_TRUE(ireal_equal(p0.y, 0));
        SP_TRUE(ireal_equal(p0.z, 0));
    }
    
    {
        ipos3 p0 = {1, 0, 0};
        ivec3 v0 = ivec3subtractpoint(&p0, &kipos3_zero);
        SP_TRUE(iiyes == ivec3isequal(&kivec3_axis_x, &v0));
    }
    {
        ivec3 v0 = ivec3add(&kivec3_axis_x, &kivec3_axis_y);
        SP_TRUE(ireal_equal(v0.v.x, 1));
        SP_TRUE(ireal_equal(v0.v.y, 1));
        SP_TRUE(ireal_equal(v0.v.z, 0));
    }
    {
        ivec3 v0 = ivec3subtract(&kivec3_axis_y, &kivec3_axis_x);
        SP_TRUE(ireal_equal(v0.v.x, -1));
        SP_TRUE(ireal_equal(v0.v.y, 1));
        SP_TRUE(ireal_equal(v0.v.z, 0));
    }
    {
        ivec3 v0 = ivec3scale(&kivec3_axis_x, 2);
        SP_TRUE(ireal_equal(v0.v.x, 2));
        SP_TRUE(ireal_equal(v0.v.y, 0));
        SP_TRUE(ireal_equal(v0.v.z, 0));
    }
    {
        ireal v = ivec3dot(&kivec3_axis_x, &kivec3_axis_y);
        SP_TRUE(ireal_equal(v, 0));
    }
    {
        ivec3 v0 = ivec3cross(&kivec3_axis_x, &kivec3_axis_y);
        SP_TRUE(iiyes == ivec3isequal(&v0, &kivec3_axis_z));
        
    }
    {
        ivec3 d = {{1,1,0}};
        ireal v = ivec3lengthsqr(&d);
        SP_TRUE(ireal_equal(v, 2));
        ireal vx = ivec3length(&d);
        SP_TRUE(ireal_equal(vx*vx, v));
    }
    {
        ivec3 d = {{1,-1,0}};
        ivec3 v0 = ivec3abs(&d);
        SP_TRUE(ireal_equal(v0.v.x, 1));
        SP_TRUE(ireal_equal(v0.v.y, 1));
        SP_TRUE(ireal_equal(v0.v.z, 0));
    }
    {
        ivec3 d = {{1,-1,0}};
        ivec3 v0 = ivec3normalize(&d);
        ireal vx = ivec3length(&d);
        SP_TRUE(ireal_equal(v0.v.x, 1.0/vx));
        SP_TRUE(ireal_equal(v0.v.y, -1.0/vx));
        SP_TRUE(ireal_equal(v0.v.z, 0));
    }
    {
        ivec3 d = {{1,1,0}};
        ivec3 v0 = ivec3parallel(&d, &kivec3_axis_x);
        SP_TRUE(iiyes == ivec3isequal(&v0, &kivec3_axis_x));
        ivec3 v1 = ivec3perpendicular(&d, &kivec3_axis_x);
        SP_TRUE(iiyes == ivec3isequal(&v1, &kivec3_axis_y));
    }
}


SP_CASE(ivec3, end) {
    SP_TRUE(1);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
