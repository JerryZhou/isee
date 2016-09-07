#include "foundation/math/ipos.h"

// ipos
SP_SUIT(ipos);

SP_CASE(ipos, idistancepow2) {
    ipos pos1 = {0, 0};
    ipos pos2 = {3, 4};
    
    SP_EQUAL(25.0, idistancepow2(&pos1, &pos2));
}

SP_CASE(ipos, constcheck) {
    SP_EQUAL(kipos_zero.x, 0);
    SP_EQUAL(kipos_zero.y, 0);
}

SP_SUIT(ipos3);

SP_CASE(ipos3, idistancepow2) {
    ipos3 p0 = {0, 0, 0};
    ipos3 p1 = {0, 3, 4};
    SP_EQUAL(25.0, idistancepow3(&p0, &p1));
    
    ipos3 p2 = {3, 0, 4};
    SP_EQUAL(25.0, idistancepow3(&p0, &p2));
    ipos3 p3 = {3, 4, 0};
    SP_EQUAL(25.0, idistancepow3(&p0, &p3));
}

SP_CASE(ipos3, ipostake) {
    ipos3 p = {1, 2, 3};
    ipos p2;
    ipos3takexz(&p, &p2);
    SP_EQUAL(p2.x, 1);
    SP_EQUAL(p2.y, 3);
}

SP_CASE(ipos3, constcheck) {
    SP_EQUAL(kipos3_zero.x, 0);
    SP_EQUAL(kipos3_zero.y, 0);
    SP_EQUAL(kipos3_zero.z, 0);
}

SP_CASE(ipos3, end) {
    SP_TRUE(1);
}

