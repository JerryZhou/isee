#include "foundation/math/irect.h"

SP_SUIT(irect);


SP_CASE(irect, irectcontainsTHEself) {
    irect r = {{0,0}, {1,1}};
    
    SP_EQUAL(irectcontains(&r, &r), 1);
}

SP_CASE(irect, irectcontainsTHEsub) {
    irect r = {{0,0}, {2,2}};
    
    irect r0 = {{0,0}, {0,0}};
    
    SP_EQUAL(irectcontains(&r, &r0), 1);
}

SP_CASE(irect, irectcontainsTHEsubNo) {
    irect r = {{0,0}, {2,2}};
    
    irect r0 = {{0,0}, {3,3}};
    
    SP_EQUAL(irectcontains(&r, &r0), 0);
}

SP_CASE(irect, irectcontainsTHEsubNo2) {
    irect r = {{0,0}, {2,2}};
    
    irect r0 = {{1,1}, {2,2}};
    
    SP_EQUAL(irectcontains(&r, &r0), 0);
}

SP_CASE(irect, irectcontainsTHEsubNo3) {
    irect r = {{0,0}, {2,2}};
    
    irect r0 = {{-1,-1}, {2,2}};
    
    SP_EQUAL(irectcontains(&r, &r0), 0);
}

SP_CASE(irect, irectcontainsTHEsubNo4) {
    irect r = {{0,0}, {2,2}};
    
    irect r0 = {{-1,-1}, {5,5}};
    
    SP_EQUAL(irectcontains(&r, &r0), 0);
}

SP_CASE(irect, irectcontainspoint) {
    irect r = {{0,0}, {2,2}};
    ipos p = {0, 0};
    
    SP_EQUAL(irectcontainspoint(&r, &p), iiok);
    p.x = 2, p.y = 2;
    SP_EQUAL(irectcontainspoint(&r, &p), iiok);
    p.x = 2, p.y = 0;
    SP_EQUAL(irectcontainspoint(&r, &p), iiok);
    p.x = 0, p.y = 2;
    SP_EQUAL(irectcontainspoint(&r, &p), iiok);
    p.x = 1, p.y = 1;
    SP_EQUAL(irectcontainspoint(&r, &p), iiok);
    
    p.x = 2, p.y = -1;
    SP_EQUAL(irectcontainspoint(&r, &p), iino);
    p.x = 3, p.y = -1;
    SP_EQUAL(irectcontainspoint(&r, &p), iino);
    p.x = -1, p.y = -1;
    SP_EQUAL(irectcontainspoint(&r, &p), iino);
    
    p.x = -1, p.y = 1;
    SP_EQUAL(irectcontainspoint(&r, &p), iino);
    p.x = -1, p.y = 2;
    SP_EQUAL(irectcontainspoint(&r, &p), iino);
    p.x = -1, p.y = 3;
    SP_EQUAL(irectcontainspoint(&r, &p), iino);
}

SP_CASE(irect, irectintersect) {
    irect r = {{0,0}, {2,2}};
    icircle c = {{0, 0}, 1};
    
    SP_EQUAL(irectintersect(&r, &c), iiok);
    
    c.pos.x = 3;
    c.pos.y = 3;
    SP_EQUAL(irectintersect(&r, &c), iino);
    
    c.pos.x = 2.5;
    c.pos.y = 2.5;
    SP_EQUAL(irectintersect(&r, &c), iiok);
    
    c.pos.x = 1;
    c.pos.y = 3;
    SP_EQUAL(irectintersect(&r, &c), iino);
    
    c.pos.x = 1;
    c.pos.y = 3.5;
    SP_EQUAL(irectintersect(&r, &c), iino);
    
    c.pos.x = 1;
    c.pos.y = 2.5;
    SP_EQUAL(irectintersect(&r, &c), iiok);
    
    c.pos.x = 1;
    c.pos.y = 1;
    SP_EQUAL(irectintersect(&r, &c), iiok);
}

SP_CASE(irect, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
