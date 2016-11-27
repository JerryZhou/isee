#include "foundation/math/iplane.h"

SP_SUIT(iplane);

SP_CASE(iplane, iplaneset) {
    iplane p;
    bzero(&p, sizeof(p));
    
    //clockwise
    iplaneset(&p, &kipos3_zero, &kipos3_z, &kipos3_x);
    
    ireal ix = iplanesolveforx(&p, 0, 1);
    SP_TRUE(ireal_equal(ix, 0));
    ireal iy = iplanesolvefory(&p, 1, 1);
    SP_TRUE(ireal_equal(iy, 0));
    ireal iz = iplanesolveforz(&p, 1, 1);
    SP_TRUE(ireal_equal(iz, 0));
}

SP_CASE(iplane, iplanesigneddistance) {
    iplane p;
    bzero(&p, sizeof(p));
    
    //clockwise
    iplaneset(&p, &kipos3_y, &kipos3_z, &kipos3_x);
    
    ivec3 v = {{1,1,1}};
    v = ivec3normalize(&v);
    
    SP_TRUE(ivec3isequal(&v, &p.normal));
    
    ipos3 cp = {0,0,0};
    
    ireal d = iplanesigneddistance(&p, &cp);
    SP_TRUE(ireal_equal_zero(d + p.distance));
}

SP_CASE(iplane, iplanesolveforXYZ) {
    iplane p;
    bzero(&p, sizeof(p));
    
    //clockwise
    iplaneset(&p, &kipos3_y, &kipos3_z, &kipos3_x);
    
    ivec3 v = {{1,1,1}};
    v = ivec3normalize(&v);
    
    SP_TRUE(ivec3isequal(&v, &p.normal));
    /* 0.57x + 0.57y + 0.57z = 0.57 */
    
    ipos3 ixp= {0, 0, 1};
    ixp.x = iplanesolveforx(&p, ixp.y, ixp.z);
    ireal ixd = iplanesigneddistance(&p, &ixp);
    SP_TRUE(ireal_equal_zero(ixd));
    
    ipos3 iyp = {0, 0, 0};
    iyp.y = iplanesolvefory(&p, iyp.x, iyp.z);
    ireal iyd = iplanesigneddistance(&p, &iyp);
    SP_TRUE(ireal_equal_zero(iyd));
    
    ipos3 izp = {0, 0, 0};
    izp.y = iplanesolvefory(&p, iyp.x, iyp.z);
    ireal izd = iplanesigneddistance(&p, &izp);
    SP_TRUE(ireal_equal_zero(izd));
    
}

SP_CASE(iplane, end) {
    SP_TRUE(1);
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
