#include "foundation/container/ireflist.h"
#include "simpletest.h"

SP_SUIT(ireflist);

SP_CASE(ireflist, ireflistmake) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    irelease(list);
}

#define __TX(name) _t_x_##name

static int __TX(ientryrefjointresrelease_cnt) = 0;
static void __TX(ientryrefjointresrelease)(irefjoint *joint) {
    ++__TX(ientryrefjointresrelease_cnt);
}

static void __TX(ientryrefjointresrelease_reset)() {
    __TX(ientryrefjointresrelease_cnt) = 0;
}

SP_CASE(ireflist, ireflistmakeentry) {
    __TX(ientryrefjointresrelease_reset)();
    
    ireflist *list = ireflistmakeentry(__TX(ientryrefjointresrelease));
    
    iref *ref0 = irefnew(iref);
    ireflistadd(list, ref0);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(__TX(ientryrefjointresrelease_cnt) == 0);
    
    irefjoint *next = ireflistremove(list, ref0);
    SP_TRUE(next == NULL);
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(__TX(ientryrefjointresrelease_cnt) == 1);
    
    irefjoint *joint = ireflistaddres(list, ref0, 0);
    irefjoint *joint1 = ireflistfind(list, ref0);
    SP_TRUE(joint == joint1);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(__TX(ientryrefjointresrelease_cnt) == 1);
    
    next = ireflistremovejoint(list, joint);
    SP_TRUE(next == NULL);
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(__TX(ientryrefjointresrelease_cnt) == 2);
    
    ireflistadd(list, ref0);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(__TX(ientryrefjointresrelease_cnt) == 2);
    
    ireflistremoveall(list);
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(__TX(ientryrefjointresrelease_cnt) == 3);
    
    irefdelete(ref0);
    irelease(list);
}

SP_CASE(ireflist, ireflistlen) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    iref *ref0 = irefnew(iref);
    iref *ref1 = irefnew(iref);
    iref *ref2 = irefnew(iref);
    iref *ref3 = irefnew(iref);
    
    irefjoint *joint0 = ireflistadd(list, ref0);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(ireflistfirst(list) == joint0);
    
    irefjoint *joint1 = ireflistadd(list, ref1);
    SP_TRUE(ireflistlen(list) == 2);
    SP_TRUE(ireflistfirst(list) == joint1);
    
    irefjoint *joint2 = ireflistadd(list, ref2);
    SP_TRUE(ireflistlen(list) == 3);
    SP_TRUE(ireflistfirst(list) == joint2);
    
    irefjoint *joint3 = ireflistadd(list, ref3);
    SP_TRUE(ireflistlen(list) == 4);
    SP_TRUE(ireflistfirst(list) == joint3);
    
    iref *refx = irefnew(iref);
    irefjoint * jointx = ireflistfind(list, refx);
    SP_TRUE(jointx == NULL);
    
    irefjoint * jointx0 = ireflistfind(list, ref0);
    SP_TRUE(joint0 == jointx0);
    
    SP_TRUE(joint3->next == joint2);
    SP_TRUE(joint2->next == joint1);
    SP_TRUE(joint1->next == joint0);
    SP_TRUE(joint0->next == NULL);
    
    irelease(refx);
    
    irelease(ref0);
    irelease(ref1);
    irelease(ref2);
    irelease(ref3);
    irelease(list);
}

SP_CASE(ireflist, ireflistfirst) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    iref *ref = irefnew(iref);
    irefjoint *joint = ireflistadd(list, ref);
    SP_TRUE(ireflistfirst(list) == joint);
    
    ireflistremovejoint(list, joint);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    ireflistremove(list, ref);
    
    irelease(ref);
    irelease(list);
}

SP_CASE(ireflist, end) {
    SP_TRUE(1);
}
