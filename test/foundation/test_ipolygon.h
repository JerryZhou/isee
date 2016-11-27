#include "foundation/math/ipolygon.h"

SP_SUIT(ipolygon);

SP_CASE(ipolygon, end) {
    SP_TRUE(1);
}

SP_SUIT(ipolygon2d);

SP_CASE(ipolygon2d, ipolygon2dmake) {
    ipolygon2d *poly = ipolygon2dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon2dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    irefdelete(poly);
    
    
}

SP_CASE(ipolygon2d, ipolygon2dadd) {
    ipolygon2d *poly = ipolygon2dmake(10);
    ipos2 pos[]={{0,0},{0, 1},{1, 1},{1,0}};
    ipolygon2dadd(poly, pos, 4);
    SP_TRUE(ipolygon2dsize(poly) == 4);
    ipos2 xpos={0.5f, 0.5f};
    SP_TRUE(ipos2isequal(&xpos, &poly->center));
    SP_TRUE(ipos2isequal(pos, &poly->min));
    SP_TRUE(ipos2isequal(pos+2, &poly->max));
    
    irefdelete(poly);
    SP_TRUE(1);
}

SP_CASE(ipolygon2d, ipolygon2dcontains) {
    ipolygon2d *poly = ipolygon2dmake(10);
    ipos2 pos[]={{0,0},{0, 1},{1, 1},{1,0}};
    ipolygon2dadd(poly, pos, 4);
    SP_TRUE(ipolygon2dsize(poly) == 4);
    
    SP_TRUE(ipolygon2dcontains(poly, pos));
    //SP_TRUE(ipolygon2dcontains(poly, pos+1));
    //SP_TRUE(ipolygon2dcontains(poly, pos+2));
    //SP_TRUE(ipolygon2dcontains(poly, pos+3));
    
    SP_TRUE(ipolygon2dcontains(poly, &poly->center));
    
    ipos2 xpos[]={{-1,-1},{2,2},{0,4}};
    SP_FALSE(ipolygon2dcontains(poly, xpos));
    SP_FALSE(ipolygon2dcontains(poly, xpos+1));
    SP_FALSE(ipolygon2dcontains(poly, xpos+2));
    
    irefdelete(poly);
    SP_TRUE(1);
}

SP_CASE(ipolygon2d, ipolygon2dfinish) {
    ipolygon2d *poly = ipolygon2dmake(10);
    ipos2 pos[]={{0,0},{0, 1},{1, 1},{1,0}};
    ipolygon2dadd(poly, pos, 4);
    SP_TRUE(ipolygon2dsize(poly) == 4);
    
    ipolygon2dfinish(poly);
    
    SP_TRUE(ireal_equal(poly->center.x, 0.5f));
    SP_TRUE(ireal_equal(poly->center.y, 0.5f));
    
    irefdelete(poly);
}

SP_CASE(ipolygon2d, end) {
    SP_TRUE(1);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_SUIT(ipolygon3d);

SP_CASE(ipolygon3d, ipolygon3dmake) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    irefdelete(poly);
}

SP_CASE(ipolygon3d, ipolygon3dadd) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    
    ipos3 pos[]={{0,0,0},{0,1,0},{0,1,1},{0,0,1}};
    ipolygon3dadd(poly, pos, 4);
    SP_TRUE(ipolygon3dsize(poly) == 4);
    
    ipos3 xpos={0.f, 0.5, 0.5f};
    SP_TRUE(ipos3isequal(&xpos, &poly->center));
    SP_TRUE(ipos3isequal(pos, &poly->min));
    SP_TRUE(ipos3isequal(pos+2, &poly->max));
    
    irefdelete(poly);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(ipolygon3d, ipolygon3dfinish) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    
    ipos3 pos[]={{0,0,0},{0,1,0},{0,1,1},{0,0,1}};
    ipolygon3dadd(poly, pos, 4);
    SP_TRUE(ipolygon3dsize(poly) == 4);
    
    ipolygon3dfinish(poly);
    
    ipos3 xpos={0.f, 0.5f, 0.5f};
    SP_TRUE(ipos3isequal(&xpos, &poly->center));
    SP_TRUE(ipos3isequal(pos, &poly->min));
    SP_TRUE(ipos3isequal(pos+2, &poly->max));
    
    irefdelete(poly);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(ipolygon3d, ipolygon3dpos3) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    
    ipos3 pos[]={{0,0,0},{0,1,0},{0,1,1},{1,1,1},{1,1,0},{1,0,1}};
    ipolygon3dadd(poly, pos, 6);
    SP_TRUE(ipolygon3dsize(poly) == 6);
    
    SP_TRUE(ipos3isequal(pos, ipolygon3dpos3(poly, 0)));
    SP_TRUE(ipos3isequal(pos+1, ipolygon3dpos3(poly, 1)));
    SP_TRUE(ipos3isequal(pos+2, ipolygon3dpos3(poly, 2)));
    SP_TRUE(ipos3isequal(pos+3, ipolygon3dpos3(poly, 3)));
    SP_TRUE(ipos3isequal(pos+4, ipolygon3dpos3(poly, 4)));
    SP_TRUE(ipos3isequal(pos+5, ipolygon3dpos3(poly, 5)));
    SP_TRUE(ipos3isequal(pos, ipolygon3dpos3(poly, 6)));
    SP_TRUE(ipos3isequal(pos+1, ipolygon3dpos3(poly, 7)));
    
    irefdelete(poly);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(ipolygon3d, ipolygon3dposxz) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    
    ipos3 pos[]={{0,0,0},{0,1,0},{0,1,1},{1,1,1},{1,1,0},{1,0,1}};
    ipolygon3dadd(poly, pos, 6);
    SP_TRUE(ipolygon3dsize(poly) == 6);
    ipos2 posxz[]={{0,0},{0,0},{0,1},{1,1},{1,0},{1,1}};
    ipos xp =ipolygon3dposxz(poly, 0);
    SP_TRUE(ipos2isequal(posxz, &xp));
    xp =ipolygon3dposxz(poly, 1);
    SP_TRUE(ipos2isequal(posxz+1, &xp));
    xp =ipolygon3dposxz(poly, 2);
    SP_TRUE(ipos2isequal(posxz+2, &xp));
    xp =ipolygon3dposxz(poly, 3);
    SP_TRUE(ipos2isequal(posxz+3, &xp));
    xp =ipolygon3dposxz(poly, 4);
    SP_TRUE(ipos2isequal(posxz+4, &xp));
    xp =ipolygon3dposxz(poly, 5);
    SP_TRUE(ipos2isequal(posxz+5, &xp));
    
    irefdelete(poly);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(ipolygon3d, ipolygon3dincollum) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    
    ipos3 pos[]={{0,0,0},{1,0,0},{1,0,1},{0,0,1}};
    ipolygon3dadd(poly, pos, 4);
    SP_TRUE(ipolygon3dsize(poly) == 4);
    
    ipos3 xpos[]={{0.5,0.5},{1,2},{-2,-1}};
    SP_TRUE(ipolygon3dincollum(poly, xpos));
    SP_FALSE(ipolygon3dincollum(poly, xpos+1));
    SP_FALSE(ipolygon3dincollum(poly, xpos+2));
    
    irefdelete(poly);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(ipolygon3d, plane) {
    ipolygon3d *poly = ipolygon3dmake(10);
    SP_TRUE(poly->pos != NULL);
    SP_TRUE(ipolygon3dsize(poly) == 0);
    SP_TRUE(islicecapacity(poly->pos) == 10);
    
    ipos3 pos[]={{0,0,0},{1,0,0},{1,0,1},{0,0,1}};
    ipolygon3dadd(poly, pos, 4);
    SP_TRUE(ipolygon3dsize(poly) == 4);
    
    ipos3 xpos[]={{0.5,0.5},{1,2},{-2,-1}};
    SP_TRUE(ipolygon3dincollum(poly, xpos));
    SP_FALSE(ipolygon3dincollum(poly, xpos+1));
    SP_FALSE(ipolygon3dincollum(poly, xpos+2));
    
    ivec3 normal = {{0, -1, 0}};
    SP_TRUE(ivec3isequal(&normal, &poly->plane.normal));
    SP_TRUE(ipos3isequal(&kipos3_zero, &poly->plane.pos));
    SP_TRUE(ireal_equal(0, poly->plane.distance));
    
    irefdelete(poly);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

SP_CASE(ipolygon3d, end) {
    SP_TRUE(1);
    
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}

