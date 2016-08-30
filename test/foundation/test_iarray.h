#include "simpletest.h"
#include "foundation/container/iarray.h"
#include "foundation/util/iarraytypes.h"

SP_SUIT(iarray);

SP_CASE(iarray, end) {
    SP_TRUE(1);
}

typedef struct TChar {
  char chars[4];
}TChar;

/* swap i, j */
static void _t_x_iarray_entry_swap(struct iarray *arr, int i, int j) {
    TChar tmp = {{0}};
    TChar *tchars = (TChar *)arr->buffer;
    if (j == kindex_invalid) {
        tchars[i] = tmp;
    } else if(i == kindex_invalid) {
        tchars[j] = tmp;
    } else {
        tmp = tchars[i];
        tchars[i] =tchars[j];
        tchars[j] = tmp;
    }
}
/* compare i, j */
static int _t_x_iarray_entry_cmp(struct iarray *arr, int i, int j) {
    TChar *tchars = (TChar *)arr->buffer;
    return strncmp(tchars[i].chars, tchars[j].chars, 4);
}

/* assign values to [i, i+num)  */
static void _t_x_iarray_entry_assign(struct iarray *arr, int i, const void *value, int nums) {
    TChar *tchars_dst = (TChar*)arr->buffer;
    TChar *tchars_src = (TChar*)value;
    int n=0;
    for (n=0; n<nums; ++n) {
        tchars_dst[i+n] = tchars_src[n];
    }
}

/* foreach visitor */
static void _t_x_iarray_entry_visitor(const struct iarray *arr, int i, const void *value) {
    TChar *tchars = (TChar*)value;
    char tmp[5] = {tchars[0].chars[0], tchars[0].chars[1], tchars[0].chars[2], tchars[0].chars[3], 0};
    printf("arr[%d]=%s\n", i, tmp);
}

static iarrayentry _t_x_array_entry = {
    EnumArrayFlagSimple | EnumArrayFlagKeepOrder | EnumArrayFlagAutoShirk,
    sizeof(TChar),
    _t_x_iarray_entry_swap,
    _t_x_iarray_entry_assign,
    _t_x_iarray_entry_cmp
};

SP_CASE(iarray, iarraymake) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    
    irelease(arr);
}

SP_CASE(iarray, iarraylen) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 0);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayat) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 0);
    
    TChar chars = {{'a', 'b', 'c', 'd'}};
    iarrayadd(arr, &chars);
    SP_TRUE(iarraylen(arr) == 1);
    
    SP_TRUE(iarrayat(arr, 1) == NULL);
    
    TChar *charsp = (TChar*)iarrayat(arr, 0);
    SP_EQUAL(charsp->chars[0], chars.chars[0]);
    SP_EQUAL(charsp->chars[1], chars.chars[1]);
    SP_EQUAL(charsp->chars[2], chars.chars[2]);
    SP_EQUAL(charsp->chars[3], chars.chars[3]);
    
    TChar charsarr[] = {chars, chars, chars, chars};
    iarrayappend(arr, charsarr, 4);
    
    irelease(arr);
}

SP_CASE(iarray, iarraylastANDiarrayfirst) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    TChar chars = {{'a', 'b', 'c', 'd'}};
    iarrayadd(arr, &chars);
    
    TChar *last = (TChar*)iarraylast(arr);
    TChar *first = (TChar*)iarrayfirst(arr);
    SP_EQUAL(last, first);
    
    iarrayadd(arr, &chars);
    SP_TRUE(iarraylast(arr) != iarrayfirst(arr));
}

SP_CASE(iarray, iarraybuffer) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    
    SP_TRUE(iarraybuffer(arr) == NULL);
    
    TChar chars = {{'a', 'b', 'c', 'd'}};
    iarrayadd(arr, &chars);
    
    SP_TRUE(iarraybuffer(arr) != NULL);
 
    irelease(arr);
}

SP_CASE(iarray, iarraysetflagANDiarrayunsetflagANDiarrayisflag) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    SP_TRUE(iarrayisflag(arr, EnumArrayFlagSimple));
    
    iarraysetflag(arr, EnumArrayFlagAutoShirk);
    SP_TRUE(iarrayisflag(arr, EnumArrayFlagAutoShirk));
    
    iarrayunsetflag(arr, EnumArrayFlagAutoShirk);
    SP_TRUE(!iarrayisflag(arr, EnumArrayFlagAutoShirk));
    
    irelease(arr);
}

SP_CASE(iarray, iarrayadd) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    TChar chars = {{'a', 'b', 'c', 'd'}};
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 0);
    
    iarrayadd(arr, &chars);
    
    SP_TRUE(iarraylen(arr) == 1);
    SP_TRUE(iarraycapacity(arr) == 2);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayremove) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    TChar chars = {{'a', 'b', 'c', 'd'}};
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 0);
    
    iarrayadd(arr, &chars);
    
    SP_TRUE(iarraylen(arr) == 1);
    SP_TRUE(iarraycapacity(arr) == 2);
    
    iarrayremove(arr, 0);
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 2);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayappend) {
    iarray * arr = iarraymake(0, &_t_x_array_entry);
    TChar chars[] = { {{'a', 'b', 'c', 'd'}}, {{'a', 'b', 'c', 'd'}},{{'a', 'b', 'c', 'd'}}};
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 0);
    
    iarrayappend(arr, chars, icountof(chars));
    
    SP_TRUE(iarraylen(arr) == 3);
    SP_TRUE(iarraycapacity(arr) == 4);
    
    irelease(arr);
}

static iarray *_iarray_make_int(size_t size) {
    iarray *arr = iarraymakeint(size);
    iarrayunsetflag(arr, EnumArrayFlagKeepOrder);
    return arr;
}

static void _iarrayaddint(iarray *arr, int i) {
    iarrayadd(arr, &i);
}

SP_CASE(iarray, iarrayinsert) {
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3};
    
    SP_TRUE(iarrayinsert(arr, 1, values, icountof(values)) == iino);
    
    SP_TRUE(iarraylen(arr) == 0);
    SP_TRUE(iarraycapacity(arr) == 0);
    
    SP_TRUE(iarrayinsert(arr, 0, values, icountof(values)) == iiok);
    
    SP_TRUE(iarraylen(arr) == 4);
    SP_TRUE(iarraycapacity(arr) == 4);
    
    _iarrayaddint(arr, 4);
    
    SP_TRUE(iarraylen(arr) == 5);
    SP_TRUE(iarraycapacity(arr) == 8);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayset) {
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3};
    
    iarrayappend(arr, values, icountof(values));
    
    values[0] = 10;
    iarrayset(arr, 0, values);
    SP_TRUE(iarrayset(arr, 8, values) == iino);
    
    irelease(arr);
}

SP_CASE(iarray, iarraytruncate) {
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3};
    
    iarrayappend(arr, values, icountof(values));
    
    values[0] = 10;
    iarrayset(arr, 0, values);
    SP_TRUE(iarrayset(arr, 8, values) == iino);
    
    iarraytruncate(arr, 8);
    SP_TRUE(iarraylen(arr) == 4);
    
    iarraytruncate(arr, 2);
    
    SP_TRUE(iarraylen(arr) == 2);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayremoveall) {
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3};
    
    iarrayappend(arr, values, icountof(values));
    
    values[0] = 10;
    iarrayset(arr, 0, values);
    SP_TRUE(iarrayset(arr, 8, values) == iino);
    
    iarrayremoveall(arr);
    
    SP_TRUE(iarraylen(arr) == 0);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayshrinkcapacity) {
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3, 4};
    
    iarrayappend(arr, values, icountof(values));
    
    SP_TRUE(iarraycapacity(arr) == 8);
    
    iarrayshrinkcapacity(arr, 6);
    
    SP_TRUE(iarraycapacity(arr) == 6);
    
    iarrayshrinkcapacity(arr, 9);
    
    SP_TRUE(iarraycapacity(arr) == 6);
    
    iarrayshrinkcapacity(arr, 3);
    
    SP_TRUE(iarraycapacity(arr) == iarraylen(arr));
    
    SP_EQUAL(iarrayof(arr, int, 0), 0);
    SP_EQUAL(iarrayof(arr, int, 1), 1);
    SP_EQUAL(iarrayof(arr, int, 2), 2);
    SP_EQUAL(iarrayof(arr, int, 3), 3);
    SP_EQUAL(iarrayof(arr, int, 4), 4);
    
    irelease(arr);
}

SP_CASE(iarray, iarrayexpandcapacity) {
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3, 4};
    
    iarrayappend(arr, values, icountof(values));
   
    SP_TRUE(iarraycapacity(arr) == 8);
    
    iarrayexpandcapacity(arr, 4);
    
    SP_TRUE(iarraycapacity(arr) == 8);
    
    iarrayexpandcapacity(arr, 12);
    
    SP_TRUE(iarraycapacity(arr) == 12);
    
    SP_EQUAL(iarrayof(arr, int, 0), 0);
    SP_EQUAL(iarrayof(arr, int, 1), 1);
    SP_EQUAL(iarrayof(arr, int, 2), 2);
    SP_EQUAL(iarrayof(arr, int, 3), 3);
    SP_EQUAL(iarrayof(arr, int, 4), 4);
    
    irelease(arr);
}

int _v_x_z_i = 0;
void _t_int_iarray_entry_visitor(const struct iarray *arr, int i, const void *value) {
    if (iarrayof(arr, int, i) == *((int*)value)) {
        ++_v_x_z_i;
    }
}

SP_CASE(iarray, iarrayforeach) {
    
    iarray* arr = _iarray_make_int(0);
    int values[] = {0, 1, 2, 3, 4};
    
    iarrayappend(arr, values, icountof(values));
    
    iarrayforeach(arr, _t_int_iarray_entry_visitor);
    
    SP_TRUE(_v_x_z_i == 5);
    
    irelease(arr);
}



