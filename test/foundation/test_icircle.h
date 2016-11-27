#include "foundation/math/icircle.h"

// **********************************************************************************
// icircle
SP_SUIT(icircle);

SP_CASE(icircle, icircleintersect) {
    icircle c = {{0, 0}, 1.0};
    
    SP_EQUAL(c.radius, 1.0);
    
    icircle c0 = {{0, 0}, 2.0};
    
    SP_EQUAL(icircleintersect(&c, &c0), 1);
}

SP_CASE(icircle, icircleintersectYES) {
    icircle c = {{0, 0}, 1.0};
    
    SP_EQUAL(c.radius, 1.0);
    
    icircle c0 = {{0, 3}, 2.0};
    
    SP_EQUAL(icircleintersect(&c, &c0), 1);
}

SP_CASE(icircle, icircleintersectNo) {
    icircle c = {{0, 0}, 1.0};
    
    SP_EQUAL(c.radius, 1.0);
    
    icircle c0 = {{3, 3}, 2.0};
    
    SP_EQUAL(icircleintersect(&c, &c0), 0);
}

SP_CASE(icircle, icirclecontains) {
    icircle c = {{0, 0}, 2.0};
    
    SP_EQUAL(icirclecontains(&c, &c), 1);
}

SP_CASE(icircle, icirclecontainsYES) {
    icircle c = {{0, 0}, 2.0};
    
    icircle c0 = {{0, 0}, 1.0};
    
    SP_EQUAL(icirclecontains(&c, &c0), 1);
}

SP_CASE(icircle, icirclecontainsYES1) {
    icircle c = {{0, 0}, 2.0};
    
    SP_EQUAL(icirclecontains(&c, NULL), 1);
}

SP_CASE(icircle, icirclecontainsNO) {
    icircle c = {{0, 0}, 2.0};
    
    SP_EQUAL(icirclecontains(NULL, &c), 0);
}

SP_CASE(icircle, icirclecontainsNO1) {
    icircle c = {{0, 0}, 2.0};
    icircle c0 = {{0, 0}, 3.0};
    
    SP_EQUAL(icirclecontains(&c, &c0), 0);
}

SP_CASE(icircle, icirclecontainsNO2) {
    icircle c = {{0, 0}, 2.0};
    icircle c0 = {{1, 1}, 2.0};
    
    SP_EQUAL(icirclecontains(&c, &c0), 0);
}

SP_CASE(icircle, icirclecontainsNO3) {
    icircle c = {{0, 0}, 2.0};
    icircle c0 = {{5, 5}, 2.0};
    
    SP_EQUAL(icirclecontains(&c, &c0), 0);
}

SP_CASE(icircle, icirclerelation) {
    icircle c = {{0, 0}, 2.0};
    icircle c0 = {{0, 0}, 1.0};
    icircle c1 = {{1, 0}, 1.0};
    icircle c2 = {{3, 0}, 1.0};
    
    SP_EQUAL(icirclerelation(&c, &c), EnumCircleRelationAContainsB);
    SP_EQUAL(icirclerelation(&c, &c0), EnumCircleRelationAContainsB);
    SP_EQUAL(icirclerelation(&c0, &c), EnumCircleRelationBContainsA);
    SP_EQUAL(icirclerelation(&c0, &c1), EnumCircleRelationIntersect);
    SP_EQUAL(icirclerelation(&c0, &c2), EnumCircleRelationNoIntersect);
}

SP_CASE(icircle, icirclecontainspoint) {
    icircle c = {{0, 0}, 2.0};
    ipos p = {0, 0};
    
    SP_EQUAL(icirclecontainspoint(&c, &p), iiok);
    
    p.x = 2, p.y = 0;
    SP_EQUAL(icirclecontainspoint(&c, &p), iiok);
    
    p.x = 3, p.y = 0;
    SP_EQUAL(icirclecontainspoint(&c, &p), iino);
}

SP_CASE(icircle, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
