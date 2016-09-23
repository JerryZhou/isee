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

SP_CASE(ipolygon2d, end) {
    SP_TRUE(1);
}