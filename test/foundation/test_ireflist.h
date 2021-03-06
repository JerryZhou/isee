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
    
    SP_TRUE(ireflistremove(list, ref) == NULL);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    irelease(ref);
    irelease(list);
}

SP_CASE(ireflist, ireflisttick) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    int64_t t0 = ireflisttick(list);
    SP_TRUE(t0 == 0);
    
    ireflistadd(list, NULL);
    int64_t t1 = ireflisttick(list);
    SP_TRUE(t1 > t0);
    
    ireflistadd(list, NULL);
    int64_t t2 = ireflisttick(list);
    SP_TRUE(t2 > t1);
    
    SP_TRUE(ireflistremove(list, NULL) != NULL);
    int64_t t3 = ireflisttick(list);
    SP_TRUE(t3 > t2);
    
    SP_TRUE(ireflistremove(list, NULL) == NULL);
    int64_t t4 = ireflisttick(list);
    SP_TRUE(t4 > t3);
    
    SP_TRUE(ireflistremove(list, NULL) == NULL);
    int64_t t5 = ireflisttick(list);
    SP_TRUE(t5 == t4);
    
    irelease(list);
}

SP_CASE(ireflist, ireflistfind) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    SP_TRUE(ireflistfind(list, NULL) == NULL);
    
    ireflistadd(list, NULL);
    SP_TRUE(ireflistfind(list, NULL) != NULL);
    
    irelease(list);
}

SP_CASE(ireflist, ireflistaddjoint) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    ireflistaddjoint(list, NULL);
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    irefjoint * joint = irefjointmake(NULL);
    ireflistaddjoint(list, joint);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(ireflistfirst(list) == joint);
    
    irelease(list);
    
    irelease(joint);
}

SP_CASE(ireflist, ireflistremovejoint) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    irefjoint * joint0 = irefjointmake(NULL);
    ireflistaddjoint(list, joint0);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(ireflistfirst(list) == joint0);
    
    irefjoint * joint1 = irefjointmake(NULL);
    ireflistaddjoint(list, joint1);
    SP_TRUE(ireflistlen(list) == 2);
    SP_TRUE(ireflistfirst(list) == joint1);
    
    irefjoint * joint2 = irefjointmake(NULL);
    ireflistaddjoint(list, joint2);
    SP_TRUE(ireflistlen(list) == 3);
    SP_TRUE(ireflistfirst(list) == joint2);
    
    SP_TRUE(ireflistremovejoint(list, joint1) == joint0);
    SP_TRUE(ireflistlen(list) == 2);
    SP_TRUE(ireflistfirst(list) == joint2);
    SP_TRUE(joint1->next == NULL);
    SP_TRUE(joint1->pre == NULL);
    
    SP_TRUE(ireflistremovejoint(list, joint0) == NULL);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(ireflistfirst(list) == joint2);
    SP_TRUE(joint0->next == NULL);
    SP_TRUE(joint0->pre == NULL);
    
    irelease(joint0);
    irelease(joint1);
    irelease(joint2);
    
    irelease(list);
}

SP_CASE(ireflist, ireflistremoveall) {
    ireflist *list = ireflistmake();
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    ireflistremoveall(list);
    SP_TRUE(ireflisttick(list) == 0);
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    ireflistadd(list, NULL);
    int64_t t0 = ireflisttick(list);
    SP_TRUE(t0 != 0);
    SP_TRUE(ireflistlen(list) == 1);
    SP_TRUE(ireflistfirst(list) != NULL);
    
    ireflistremoveall(list);
    int64_t t1 = ireflisttick(list);
    SP_TRUE(t1 > t0);
    SP_TRUE(ireflistlen(list) == 0);
    SP_TRUE(ireflistfirst(list) == NULL);
    
    irelease(list);
}

SP_CASE(ireflist, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
