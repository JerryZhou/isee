#include "foundation/container/islice.h"
#include "foundation/util/iarraytypes.h"

SP_SUIT(islice);

#define __Sn_be_1(s, n, i1) SP_TRUE(isliceof((s), int, (n)) == i1)
#define __Sn_be_2(s, n, i1, i2) SP_TRUE((isliceof((s), int, (n)) == i1) && (isliceof((s), int, (n)+1) == i2 ))
#define __Sn_be_5(s, n, i1, i2, i3, i4, i5) __Sn_be_2(s, n, i1, i2); __Sn_be_2(s, n+2, i3, i4); __Sn_be_1(s, n+4, i5)

#define __Sn_be_3(s, n, i1, i2, i3) __Sn_be_2(s, n, i1, i2); __Sn_be_1(s, n+2, i3)
#define __Sn_be_4(s, n, i1, i2, i3, i4) __Sn_be_3(s, n, i1, i2, i3); __Sn_be_1(s, n+3, i4)
#define __Sn_be_6(s, n, i1, i2, i3, i4, i5, i6) __Sn_be_3(s, n, i1, i2, i3); __Sn_be_3(s, n+3, i4, i5, i6)
#define __Sn_be_7(s, n, i1, i2, i3, i4, i5, i6, i7) __Sn_be_6(s, n, i1, i2, i3, i4, i5, i6); __Sn_be_1(s, n+6, i7)

SP_CASE(islice, islicemake) {
    
    iarray *arr = iarraymakeint(8);
    int values[] = {0, 1, 2};
    iarrayinsert(arr, 0, values, 3);
    
    {
        islice *slice = islicemake(arr, 0, 0, 0);
        SP_EQUAL(islicelen(slice), 0);
        SP_EQUAL(islicecapacity(slice), 0);
        
        irelease(slice);
    }
    
    {
        islice *slice = islicemake(arr, 0, 1, 1);
        SP_EQUAL(islicelen(slice), 1);
        SP_EQUAL(islicecapacity(slice), 1);
        
        irelease(slice);
    }
    
    {
        islice *slice = islicemake(arr, 0, 1, 0);
        SP_EQUAL(islicelen(slice), 1);
        SP_EQUAL(islicecapacity(slice), 1);
        
        irelease(slice);
    }
    
    
    {
        islice *slice = islicemake(arr, 0, 1, 2);
        SP_EQUAL(islicelen(slice), 1);
        SP_EQUAL(islicecapacity(slice), 2);
        
        irelease(slice);
    }
    
    
    {
        islice *slice = islicemake(arr, 1, 3, 9);
        SP_EQUAL(islicelen(slice), 2);
        SP_EQUAL(islicecapacity(slice), 7);
        
        irelease(slice);
    }
    
    irelease(arr);
}

SP_CASE(islice, islicemakeby) {
    /* arr[0:8] */
    iarray *arr = iarraymakeint(8);
    int values[] = {0, 1, 2};
    iarrayinsert(arr, 0, values, 3);
    
    /* output array */
    irangearray(arr, int,
           printf("arr[%d]=%d\n", __key, __value);
           );
    
    /* slice = arr[0:3:8]  */
    islice *slice_0_3_8 = isliced(arr, 0, 3);
    SP_EQUAL(islicelen(slice_0_3_8), 3);
    SP_EQUAL(islicecapacity(slice_0_3_8), 8);
    SP_EQUAL(isliceof(slice_0_3_8, int, 0), 0);
    SP_EQUAL(isliceof(slice_0_3_8, int, 1), 1);
    SP_EQUAL(isliceof(slice_0_3_8, int, 2), 2);
    
    /* output slice */
    irangeslice(slice_0_3_8, int,
           printf("slice_0_3_8-arr[0:3][%d]=%d\n", __key, __value);
           );
    
    /* child = slice[1:2:8] */
    islice *child = islicedby(slice_0_3_8, 1, 2);
    SP_EQUAL(islicelen(child), 1);
    SP_EQUAL(islicecapacity(child), 7);
    SP_EQUAL(isliceof(child, int, 0), 1);
    SP_EQUAL(isliceat(child, 1), NULL);
    
    /*output slice child*/
    irangeslice(child, int,
           printf("slice_0_3_8-child[1:2][%d]=%d\n", __key, __value);
           );
    
    /* sub = child[1:1:7] */
    islice* sub = islicedby(child, 1, 1);
    SP_EQUAL(islicelen(sub), 0);
    SP_EQUAL(islicecapacity(sub), 6);
    SP_EQUAL(isliceat(sub, 0), NULL);
    
    /*output slice child sub*/
    irangeslice(sub, int,
           printf("slice_0_3_8-child[1:2]-sub[1:1][%d]=%d\n", __key, __value);
           );
    
    /* xslice = slice[8:8]
     */
    islice *xslice = isliced(arr, 8, 8);
    
    /*output xslice*/
    irangeslice(xslice, int,
           printf("xslice-arr[8:8][%d]=%d\n", __key, __value);
           );
    
    SP_EQUAL(islicelen(xslice), 0);
    SP_EQUAL(islicecapacity(xslice), 0);
    
    islice *yslice = isliced(arr, 5, 5);
    
    /*output yslice*/
    irangeslice(yslice, int,
           printf("yslice-arr[5:5][%d]=%d\n", __key, __value);
           );
    
    SP_EQUAL(islicelen(yslice), 0);
    SP_EQUAL(islicecapacity(yslice), 3);
    
    /**/
    int aps[] = {100, 200};
    isliceadd(yslice, aps);
    
    SP_EQUAL(islicelen(yslice), 1);
    SP_EQUAL(islicecapacity(yslice), 3);
    SP_EQUAL(isliceof(yslice, int, 0), 100);
    
    /*output yslice*/
    irangeslice(yslice, int,
           printf("yslice-arr[5:5]-add{100} [%d]=%d\n", __key, __value);
           );
    
    SP_EQUAL(iarraylen(arr), 4);
    SP_EQUAL(iarrayof(arr, int, 3), 100);
    
    /* output array */
    irangearray(arr, int,
           printf("arr-after-yslice-add[%d]=%d\n", __key, __value);
           );
    
    irelease(yslice);
    
    irelease(xslice);
    
    irelease(child);
    
    irelease(sub);
    
    irelease(slice_0_3_8);
    
    irelease(arr);
}

#define __slice_arr(arr, ...) islicemakearg(arr, #__VA_ARGS__)

void __slice_print(islice *s) {
    printf("[");
    for (int i=0; i <islicelen(s); ++i) {
        int v = isliceof(s, int, i);
        printf("%d%s", v, i==islicelen(s)-1 ? "" : ", ");
    }
    printf("]");
}

void __slice_println(islice *s) {
    __slice_print(s);
    printf("%s", "\n");
}

SP_CASE(islice, islicelen_islicecapacity) {
    /* arr[0:8] */
    iarray *arr = iarraymakeint(8);
    int values[] = {0, 1, 2};
    iarrayinsert(arr, 0, values, 3);
    
    islice *slice0 = __slice_arr(arr);
    __slice_println(slice0);
    SP_EQUAL(islicelen(slice0), 3);
    SP_EQUAL(islicecapacity(slice0), 8);
    irelease(slice0);
    
    islice *slice1 = __slice_arr(arr, 2:);
    __slice_println(slice1);
    SP_EQUAL(islicelen(slice1), 1);
    SP_EQUAL(islicecapacity(slice1), 6);
    irelease(slice1);
    
    islice *slice2 = __slice_arr(arr, :1);
    __slice_println(slice2);
    SP_EQUAL(islicelen(slice2), 1);
    SP_EQUAL(islicecapacity(slice2), 8);
    irelease(slice2);
    
    islice *slice3 = __slice_arr(arr, :1:5);
    __slice_println(slice3);
    SP_EQUAL(islicelen(slice3), 1);
    SP_EQUAL(islicecapacity(slice3), 5);
    irelease(slice3);
    
    islice *slice4 = __slice_arr(arr, :0:5);
    __slice_println(slice4);
    SP_EQUAL(islicelen(slice4), 0);
    SP_EQUAL(islicecapacity(slice4), 5);
    irelease(slice4);
    
    irelease(arr);
}

SP_CASE(islice, isliceparamsparse) {
    
#define __I3_be(v, i1, i2, i3) SP_TRUE(v[0] == i1 && v[1] == i2 && v[2] == i3)
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, "", ':');
        __I3_be(values, -1, -1, -1);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, NULL, ':');
        __I3_be(values, -1, -1, -1);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, ":", ':');
        __I3_be(values, -1, -1, -1);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, "0:", ':');
        __I3_be(values, 0, -1, -1);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, "0:1", ':');
        __I3_be(values, 0, 1, -1);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, "0:1:2", ':');
        __I3_be(values, 0, 1, 2);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, ":1:2", ':');
        __I3_be(values, -1, 1, 2);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, "::2", ':');
        __I3_be(values, -1, -1, 2);
    }
    {
        int values[3] = {-1, -1, -1};
        isliceparamsparse(values, "1::2", ':');
        __I3_be(values, 1, -1, 2);
    }
}

SP_CASE(islice, isliceappendvalues) {
    /* arr[0:8] */
    iarray *arr = iarraymakeint(8);
    int values[] = {0, 1, 2};
    iarrayinsert(arr, 0, values, 3);
    
    islice *slice = islicemakearg(arr, "2:");
    SP_TRUE(islicelen(slice) == 1);
    SP_TRUE(islicecapacity(slice) == 6);
    
    __Sn_be_1(slice, 0, 2);
    
    islice *slicenew = isliceappendvalues(slice, values, icountof(values));
    SP_TRUE(islicelen(slice) == 4);
    SP_TRUE(islicecapacity(slice) == 6);
    SP_TRUE(slice == slicenew);
    
    __Sn_be_4(slice, 0, 2, 0, 1, 2);
    
    islice *slicenew1 = isliceappendvalues(slicenew, values, icountof(values));
    SP_TRUE(islicelen(slicenew1) == 7);
    SP_TRUE(islicecapacity(slicenew1) == 12);
    SP_TRUE(slice != slicenew1);
    
    __Sn_be_7(slicenew1, 0, 2, 0, 1, 2, 0, 1, 2);
   
    irelease(slicenew1);
    irelease(arr);
}

SP_CASE(islice, isliceset) {
    /* arr[0:8] */
    iarray *arr = iarraymakeint(8);
    int values[] = {0, 1, 2};
    iarrayinsert(arr, 0, values, 3);
    
    islice *slice = islicemakearg(arr, "2:");
    SP_TRUE(islicelen(slice) == 1);
    SP_TRUE(islicecapacity(slice) == 6);
    
    __Sn_be_1(slice, 0, 2);
    
    islice *slicenew = isliceappendvalues(slice, values, icountof(values));
    SP_TRUE(islicelen(slice) == 4);
    SP_TRUE(islicecapacity(slice) == 6);
    SP_TRUE(slice == slicenew);
    
    __Sn_be_4(slice, 0, 2, 0, 1, 2);
    
    islice *slicenew1 = isliceappendvalues(slicenew, values, icountof(values));
    SP_TRUE(islicelen(slicenew1) == 7);
    SP_TRUE(islicecapacity(slicenew1) == 12);
    SP_TRUE(slice != slicenew1);
    
    __Sn_be_7(slicenew1, 0, 2, 0, 1, 2, 0, 1, 2);
    
    int value = 9;
    SP_TRUE(isliceset(slicenew1, 0, &value) == iiok);
    __Sn_be_7(slicenew1, 0, 9, 0, 1, 2, 0, 1, 2);
    
    SP_TRUE(isliceset(slicenew1, 6, &value) == iiok);
    __Sn_be_7(slicenew1, 0, 9, 0, 1, 2, 0, 1, 9);
    SP_TRUE(isliceset(slicenew1, 7, &value) == iino);
    __Sn_be_7(slicenew1, 0, 9, 0, 1, 2, 0, 1, 9);
    
    irelease(slicenew1);
    irelease(arr);
}

