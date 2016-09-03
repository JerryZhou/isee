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

SP_CASE(iarraytypes, end) {
    SP_TRUE(1);
}