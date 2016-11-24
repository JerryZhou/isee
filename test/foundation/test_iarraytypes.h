#include "foundation/util/iarraytypes.h"
#include "simpletest.h"


SP_SUIT(iarraytypes);

typedef struct _t_x_iarr_element {
    int x, y, z;
}_t_x_iarr_element;

int _t_x_types_iarray_entry_cmp(struct iarray *arr, int i, int j) {
    _t_x_iarr_element ai = iarrayof(arr, _t_x_iarr_element, i);
    _t_x_iarr_element aj = iarrayof(arr, _t_x_iarr_element, j);
    
    return ai.z - aj.z;
}

SP_CASE(iarraytypes, iarraymakecopyableANDiarraymakeint) {
    iarray * arr = iarraymakeint(6);
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 6);
    
    irelease(arr);
    
    {
        iarray * arrz = iarraymakecopyablewith(6, sizeof(_t_x_iarr_element), _t_x_types_iarray_entry_cmp);
        _t_x_iarr_element values[] = {{0, 0, 5}, {0, 0, 1}, {0, 0, 3}};
        iarrayappend(arrz, values, icountof(values));
        iarraysort(arrz);
        
        SP_TRUE(iarrayof(arrz, _t_x_iarr_element, 0).z == 1);
        SP_TRUE(iarrayof(arrz, _t_x_iarr_element, 1).z == 3);
        SP_TRUE(iarrayof(arrz, _t_x_iarr_element, 2).z == 5);
        
        irelease(arrz);
    }
}

typedef struct test_iref_st {
    irefdeclare;
    
    int xid;
    int x, y, z;
    int index;
}test_iref_st;
irealdeclareregister(test_iref_st);

int _t_x_y_iarray_entry_cmp (struct iarray *arr, int i, int j) {
    test_iref_st *st0 = iarrayof(arr, test_iref_st*, i);
    test_iref_st *st1 = iarrayof(arr, test_iref_st*, j);
    return st0->z - st1->z;
}

void test_iref_st_destructor(const imeta*meta, iptr o) {
    test_iref_st *st = icast(test_iref_st, o);
    ilog("##destructor##: %d\n", st->xid);
}

SP_CASE(iarraytypes, register_test_iref) {
    imetaconfig config = {0};
    config.name = "test_iref_st";
    config.size = sizeof(test_iref_st);
    config.destructor = test_iref_st_destructor;
    imetaindex(test_iref_st) = imetaregisterwithconfig(&config);
}

static void _t_x_irefarray_index_change (iptr x, iarray *arr, iref *ref, int index) {
    test_iref_st *st = icast(test_iref_st, ref);
    st->index = index;
}

irefarrayentry _t_x_test_array_entry = {_t_x_irefarray_index_change};

SP_CASE(iarraytypes, iarraymakeirefwithentryandcmp) {
    iarray *arr = iarraymakeirefwithentryandcmp(10, &_t_x_test_array_entry, _t_x_y_iarray_entry_cmp);
    
    SP_TRUE(arr);
    
    test_iref_st *st0 = irefnew(test_iref_st);
    test_iref_st *st1 = irefnew(test_iref_st);
    test_iref_st *st2 = irefnew(test_iref_st);
    
    st2->z = 2;st2->xid = 2;
    st1->z = 1;st1->xid = 1;
    st0->z = 0;st0->xid = 0;
    
    iarrayadd(arr, &st2);
    SP_TRUE(st2->index == 0);
    
    iarrayadd(arr, &st0);
    SP_TRUE(st0->index == 1);
    
    iarrayadd(arr, &st1);
    SP_TRUE(st1->index == 2);
    
    irangearray(arr, test_iref_st*,
                ilog("arr[%d]=(xid:%d,index:%d)\n", __key, __value->xid, __value->index));
    
    iarraysort(arr);
    
    irangearray(arr, test_iref_st*,
                ilog("arr[%d]=(xid:%d,index:%d)\n", __key, __value->xid, __value->index));
    
    SP_TRUE(st0->index == 0 && st1->index == 1 && st2->index == 2);
    
    
    irelease(st0);
    irelease(st1);
    irelease(st2);
    
    irelease(arr);
}

SP_CASE(iarraytypes, istringcompare) {
    iarray *arr = iarraymakeiref(5);
    istring *sa = istringmake("a");
    istring *sb = istringmake("b");
    istring *sc = istringmake("c");
    
    iarrayadd(arr, &sb);
    iarrayadd(arr, &sa);
    iarrayadd(arr, &sc);
    
    irangearray(arr, istring*,
                ilog("arr[%d]=%s\n", __key, istringbuf(__value));
                );
    
    SP_TRUE(iarrayof(arr, istring*, 0) == sb);
    SP_TRUE(iarrayof(arr, istring*, 1) == sa);
    SP_TRUE(iarrayof(arr, istring*, 2) == sc);
    
    iarraysort(arr);
    
    SP_TRUE(iarrayof(arr, istring*, 0) == sa);
    SP_TRUE(iarrayof(arr, istring*, 1) == sb);
    SP_TRUE(iarrayof(arr, istring*, 2) == sc);
    
    irangearray(arr, istring*,
                ilog("arr[%d]=%s\n", __key, istringbuf(__value));
                );
    
    irefdelete(sa);
    irefdelete(sb);
    irefdelete(sc);
    irefdelete(arr);
}

SP_CASE(iarraytypes, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
