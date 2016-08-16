#include "foundation/util/iarraytypes.h"
#include "foundation/memory/imemory.h"


/* 赋值 */
static void _iarray_entry_assign_copy(struct iarray *arr,
                                      int i, const void *value, int nums) {
    memmove(arr->buffer + i * arr->entry->size,
            value,
            nums * arr->entry->size);
}

/* 交换两个对象 */
static void _iarray_entry_swap_copy(struct iarray *arr,
                                    int i, int j) {
    /* 空对象 */
    char buffer[256];
    char *tmp;
    if (arr->entry->size > 256) {
        tmp = icalloc(1, arr->entry->size);
    } else {
        tmp = buffer;
    }
    
    if (j == kindex_invalid) {
        /* arr_int[i] = 0;
         may call assign */
        _iarray_entry_assign_copy(arr, i, tmp, 1);
    } else if (i == kindex_invalid) {
        /* arr_int[j] = 0;
         may call assign */
        _iarray_entry_assign_copy(arr, j, tmp, 1);
    } else {
        memmove(tmp, __arr_i(arr, i), arr->entry->size);
        memmove(__arr_i(arr, i), __arr_i(arr, j), arr->entry->size);
        memmove(__arr_i(arr, j), tmp, arr->entry->size);
    }
}

/* 比较两个对象 */
static int _iarray_entry_cmp_int(struct iarray *arr,
                                 int i, int j) {
    int *arr_int = (int *)arr->buffer;
    return arr_int[i] - arr_int[j];
}

/* 定义int 数组 */
static const iarrayentry _arr_entry_int = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(int),
    _iarray_entry_swap_copy,
    _iarray_entry_assign_copy,
    _iarray_entry_cmp_int,
};

/* 内置的整数数组 */
iarray* iarraymakeint(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_int);
}

/* 比较两个对象 */
static int _iarray_entry_cmp_ireal(struct iarray *arr,
                                   int i, int j) {
    ireal *arrs = (ireal *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* 定义ireal 数组 */
static const iarrayentry _arr_entry_ireal = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(ireal),
    _iarray_entry_swap_copy,
    _iarray_entry_assign_copy,
    _iarray_entry_cmp_ireal,
};

/* 浮点数组 */
iarray* iarraymakeireal(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_ireal);
}

/* 比较两个对象 */
static int _iarray_entry_cmp_int64(struct iarray *arr,
                                   int i, int j) {
    int64_t *arrs = (int64_t *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* 定义int64 数组 */
static const iarrayentry _arr_entry_int64 = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(int64_t),
    _iarray_entry_swap_copy,
    _iarray_entry_assign_copy,
    _iarray_entry_cmp_int64,
};

/* int64 数组*/
iarray* iarraymakeint64(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_int64);
}

/* 比较两个对象 */
static int _iarray_entry_cmp_char(struct iarray *arr,
                                  int i, int j) {
    char *arrs = (char *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* 定义char 数组 */
static const iarrayentry _arr_entry_char = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(char),
    _iarray_entry_swap_copy,
    _iarray_entry_assign_copy,
    _iarray_entry_cmp_char,
};

/* char 数组*/
iarray* iarraymakechar(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_char);
}

/* get entry */
const iarrayentry* iarrayentryget(int type) {
    return &_arr_entry_char;
}

/*************************************************************/
/* iarray - iref                                             */
/*************************************************************/

/* 赋值 */
static void _iarray_entry_assign_iref(struct iarray *arr,
                                      int i, const void *value, int nums) {
    iref* *arrs = (iref* *)arr->buffer;
    iref* *refvalue = (iref* *)value;
    iref* ref = NULL;
    int j = 0;
    irefarrayentry *entry = (irefarrayentry*)arr->userdata;
    
    /* 附加很多个 */
    while (j < nums) {
        /* realloc not set zero to pending memory */
        if (i >= arr->len) {
            arrs[i] = NULL;
        }
        if (refvalue) {
            ref = refvalue[j];
        }
        
        /* watch the index change */
        if (arrs[i] && entry && entry->indexchange) {
            entry->indexchange(arr, arrs[i], kindex_invalid);
        }
        
        iassign(arrs[i], ref);
        
        /* watch the index change */
        if (ref && entry && entry->indexchange) {
            entry->indexchange(arr, ref, i);
        }
        ++j;
        ++i;
    }
}

/* 交换两个对象 */
static void _iarray_entry_swap_iref(struct iarray *arr,
                                    int i, int j) {
    iref* tmp;
    iref* *arrs = (iref* *)arr->buffer;
    irefarrayentry *entry = (irefarrayentry*)arr->userdata;
    
    if (j == kindex_invalid) {
        /* arr_int[i] = 0;
         * may call assign */
        _iarray_entry_assign_iref(arr, i, 0, 1);
    } else if (i == kindex_invalid) {
        /* arr_int[j] = 0;
         * may call assign */
        _iarray_entry_assign_iref(arr, j, 0, 1);
    } else {
        tmp = arrs[i];
        arrs[i] = arrs[j];
        arrs[j] = tmp;
        
        /* watch the index change */
        if (entry && entry->indexchange) {
            entry->indexchange(arr, arrs[i], i);
            entry->indexchange(arr, arrs[j], j);
        }
    }
}

/* 比较两个对象 */
static int _iarray_entry_cmp_iref(struct iarray *arr,
                                  int i, int j) {
    iref* *arrs = (iref* *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* 定义iref 数组 */
static const iarrayentry _arr_entry_iref = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(iref*),
    _iarray_entry_swap_iref,
    _iarray_entry_assign_iref,
    _iarray_entry_cmp_iref,
};

/* 内置的引用数组 */
iarray* iarraymakeiref(size_t capacity) {
    return iarraymakeirefwithentry(capacity, NULL);
}

/* 内置的引用数组 */
iarray* iarraymakeirefwithentry(size_t capacity, const irefarrayentry *refentry) {
    iarray*  arr = iarraymake(capacity, &_arr_entry_iref);
    arr->userdata = (void*)refentry;
    return arr;
}