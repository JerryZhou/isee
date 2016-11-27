#include "foundation/math/iline.h"

SP_SUIT(iline2d);

SP_CASE(iline2d, nothing) {
    SP_TRUE(1);
}

SP_CASE(iline2d, iline2ddirection) {
    iline2d line;
    line.start.x = 1;
    line.start.y = 1;
    
    line.end.x = 2;
    line.end.y = 3;
    
    ivec2 dir = iline2ddirection(&line);
    ireal len = iline2dlength(&line);
    
    SP_TRUE(ireal_equal(dir.v.x, 1/len));
    SP_TRUE(ireal_equal(dir.v.y, 2/len));
}

SP_CASE(iline2d, iline2dnormal) {
    iline2d line;
    line.start.x = 0;
    line.start.y = 0;
    
    line.end.x = 3;
    line.end.y = 4;
    
    /*direction: (0.6, 0.8)*/
    /*direction: (0.8, -0.6)*/
    ivec2 normal = iline2dnormal(&line);
    SP_TRUE(ireal_equal(normal.v.x, 0.8));
    SP_TRUE(ireal_equal(normal.v.y, -0.6));
}

SP_CASE(iline2d, iline2dlength) {
    iline2d line;
    line.start.x = 0;
    line.start.y = 0;
    
    line.end.x = 3;
    line.end.y = 4;
    
    /*direction: (0.6, 0.8)*/
    /*direction: (0.8, -0.6)*/
    ivec2 normal = iline2dnormal(&line);
    SP_TRUE(ireal_equal(normal.v.x, 0.8));
    SP_TRUE(ireal_equal(normal.v.y, -0.6));
    
    ireal len = iline2dlength(&line);
    SP_TRUE(ireal_equal(len, 5));
}

SP_CASE(iline2d, iline2dsigneddistance) {
    iline2d line;
    line.start.x = 0;
    line.start.y = 0;
    
    line.end.x = 3;
    line.end.y = 0;
    
    ipos p0 = {1, 1};
    
    ireal d0 = iline2dsigneddistance(&line, &p0);
    SP_TRUE(ireal_less_zero(d0));
    SP_TRUE(ireal_equal(d0, -1));
    
    ipos p1 = {1, -1};
    ireal d1 = iline2dsigneddistance(&line, &p1);
    SP_TRUE(ireal_greater_zero(d1));
    SP_TRUE(ireal_equal(d1, 1));
}

SP_CASE(iline2d, iline2dclassifypoint) {
    iline2d line;
    line.start.x = 0;
    line.start.y = 0;
    
    line.end.x = 3;
    line.end.y = 0;
    
    ipos p0 = {1, 1};
    
    ireal d0 = iline2dsigneddistance(&line, &p0);
    SP_TRUE(ireal_less_zero(d0));
    SP_TRUE(ireal_equal(d0, -1));
    
    int c0 = iline2dclassifypoint(&line, &p0, iepsilon);
    SP_EQUAL(c0, EnumPointClass_Left);
    
    ipos p1 = {1, -1};
    ireal d1 = iline2dsigneddistance(&line, &p1);
    SP_TRUE(ireal_greater_zero(d1));
    SP_TRUE(ireal_equal(d1, 1));
    
    int c1 = iline2dclassifypoint(&line, &p1, iepsilon);
    SP_EQUAL(c1, EnumPointClass_Right);
    
    ipos pz = {1, 0};
    
    ireal dz = iline2dsigneddistance(&line, &pz);
    SP_TRUE(ireal_equal_zero(dz));
    SP_TRUE(ireal_equal(dz, 0));
    
    int cz = iline2dclassifypoint(&line, &pz, iepsilon);
    SP_EQUAL(cz, EnumPointClass_On);
}

SP_CASE(iline2d, iline2dintersection) {
    iline2d line0;
    line0.start.x = 0;
    line0.start.y = 0;
    line0.end.x = 3;
    line0.end.y = 0;
    
    iline2d line1;
    line1.start.x = 1;
    line1.start.y = 1;
    line1.end.x = 1;
    line1.end.y = -1;
    
    ipos p;
    int pr = iline2dintersection(&line0, &line1, &p);
    SP_EQUAL(pr, EnumLineClass_Segments_Intersect);
    SP_TRUE(ireal_equal(p.x, 1));
    SP_TRUE(ireal_equal(p.y, 0));
    
    iline2d line2;
    line2.start.x = 0;
    line2.start.y = 1;
    line2.end.x = 3;
    line2.end.y = 1;
    pr = iline2dintersection(&line0, &line2, &p);
    SP_EQUAL(pr, EnumLineClass_Paralell);
    
    
    iline2d line3;
    line3.start.x = 0;
    line3.start.y = 0;
    line3.end.x = 3;
    line3.end.y = 0;
    pr = iline2dintersection(&line0, &line3, &p);
    SP_EQUAL(pr, EnumLineClass_Collinear);
    
    {
        iline2d line;
        line.start.x = 4;
        line.start.y = 0;
        line.end.x = 6;
        line.end.y = 0;
        pr = iline2dintersection(&line0, &line, &p);
        SP_EQUAL(pr, EnumLineClass_Collinear);
    }
    
    {
        iline2d line;
        line.start.x = 0;
        line.start.y = 5;
        line.end.x = 4;
        line.end.y = 1;
        pr = iline2dintersection(&line0, &line, &p);
        SP_EQUAL(pr, EnumLineClass_Lines_Intersect);
    }
    
    {
        iline2d line;
        line.start.x = 0;
        line.start.y = 5;
        line.end.x = 1;
        line.end.y = 1;
        pr = iline2dintersection(&line0, &line, &p);
        SP_EQUAL(pr, EnumLineClass_B_Bisects_A);
    }
    
    {
        iline2d line;
        line.start.x = 5;
        line.start.y = 5;
        line.end.x = 5;
        line.end.y = -1;
        pr = iline2dintersection(&line0, &line, &p);
        SP_EQUAL(pr, EnumLineClass_A_Bisects_B);
    }
}

SP_CASE(iline2d, iline2dclosestpoint) {
    iline2d line0;
    line0.start.x = 0;
    line0.start.y = 0;
    line0.end.x = 3;
    line0.end.y = 0;
    
    {
        ipos center;
        center.x = -1;
        center.y = 1;
        
        ipos v = iline2dclosestpoint(&line0, &center, iepsilon);
        SP_TRUE(ireal_equal(v.x, 0));
        SP_TRUE(ireal_equal(v.y, 0));
    }
    
    {
        ipos center;
        center.x = 1;
        center.y = 1;
        
        ipos v = iline2dclosestpoint(&line0, &center, iepsilon);
        SP_TRUE(ireal_equal(v.x, 1));
        SP_TRUE(ireal_equal(v.y, 0));
    }
    
    {
        ipos center;
        center.x = 4;
        center.y = 1;
        
        ipos v = iline2dclosestpoint(&line0, &center, iepsilon);
        SP_TRUE(ireal_equal(v.x, 3));
        SP_TRUE(ireal_equal(v.y, 0));
    }
}

SP_SUIT(iline3d);

SP_CASE(iline3d, iline3ddirection) {
    iline3d line = {{0,0,0},{1,1,1}};
    SP_TRUE(line.start.x == 0);
    SP_TRUE(line.start.y == 0);
    SP_TRUE(line.start.z == 0);
    
    SP_TRUE(line.end.x == 1);
    SP_TRUE(line.end.y == 1);
    SP_TRUE(line.end.z == 1);
    
    ivec3 dir = iline3ddirection(&line);
    ivec3 xdir = {{1, 1, 1}};
    xdir = ivec3normalize(&xdir);
    
    SP_TRUE(dir.v.x == xdir.v.x);
    SP_TRUE(dir.v.y == xdir.v.y);
    SP_TRUE(dir.v.z == xdir.v.z);
}

SP_CASE(iline3d, iline3dlength) {
    iline3d line = {{0,0,0},{1,1,1}};
    SP_TRUE(line.start.x == 0);
    SP_TRUE(line.start.y == 0);
    SP_TRUE(line.start.z == 0);
    
    SP_TRUE(line.end.x == 1);
    SP_TRUE(line.end.y == 1);
    SP_TRUE(line.end.z == 1);
    
    ireal len = iline3dlength(&line);
    SP_TRUE(ireal_equal(len, sqrt(3)));
}

SP_CASE(iline3d, iline3dclosestpoint) {
    iline3d line = {{0,0,0},{1,1,1}};
    SP_TRUE(line.start.x == 0);
    SP_TRUE(line.start.y == 0);
    SP_TRUE(line.start.z == 0);
    
    SP_TRUE(line.end.x == 1);
    SP_TRUE(line.end.y == 1);
    SP_TRUE(line.end.z == 1);
    
    ipos3 center = {0, 0, 0};
    ipos3 pos0 = iline3dclosestpoint(&line, &center, iepsilon);
    SP_TRUE(pos0.x == 0);
    SP_TRUE(pos0.y == 0);
    SP_TRUE(pos0.z == 0);
    
    center.x = 1; center.y = 1, center.z = 1;
    pos0 = iline3dclosestpoint(&line, &center, iepsilon);
    SP_TRUE(ireal_equal(pos0.x, 1));
    SP_TRUE(ireal_equal(pos0.y, 1));
    SP_TRUE(ireal_equal(pos0.z, 1));
    
    line.end.z = 0;
    line.end.x = 0;
    
    ipos3 px = {1, 0.5f, 1};
    
    pos0 = iline3dclosestpoint(&line, &px, iepsilon);
    
    SP_TRUE(ireal_equal(pos0.x, 0.0f));
    SP_TRUE(ireal_equal(pos0.y, 0.5f));
    SP_TRUE(ireal_equal(pos0.z, 0.0f));
    
}

SP_CASE(iline3d, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

