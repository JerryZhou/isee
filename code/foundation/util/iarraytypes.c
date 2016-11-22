#include "foundation/util/iarraytypes.h"
#include "foundation/memory/imemory.h"

#include "foundation/math/ivec.h"
#include "foundation/math/ipos.h"
#include "foundation/math/isize.h"
#include "foundation/math/irect.h"
#include "foundation/math/icircle.h"
#include "foundation/math/iline.h"
#include "foundation/math/iplane.h"
#include "foundation/math/imat.h"


/* array-assign */
static void _iarray_entry_assign_copy(struct iarray *arr,
                                      int i, const void *value, int nums) {
    memmove(arr->buffer + i * arr->entry->size,
            value,
            nums * arr->entry->size);
}

/* array-swap */
static void _iarray_entry_swap_copy(struct iarray *arr,
                                    int i, int j) {
    /* only read: empty element */
    static char buffer[256];
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
    
    /* free the tmp */
    if (tmp != buffer) {
        ifree(tmp);
    }
}

/* the copyable array */
iarray* iarraymakecopyable(size_t capacity, size_t size) {
    return iarraymakecopyablewith(capacity, size, NULL);
}

/* the copyable array with cmp */
iarray* iarraymakecopyablewith(size_t capacity, size_t size, iarray_entry_cmp cmp) {
    iarrayentry *entry = iobjmalloc(iarrayentry);
    entry->flag = EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero |
    EnumArrayFlagNeedFreeEntry;
    entry->size = size;
    entry->swap = _iarray_entry_swap_copy;
    entry->assign = _iarray_entry_assign_copy;
    entry->cmp = cmp;
    return iarraymake(capacity, entry);
}

/* with meta in array-entry */
static int _iarray_entry_copy_cmp(struct iarray *arr, int i, int j) {
    return arr->entry->elemeta->funcs->compare(arr->entry->elemeta->funcs,
                                               __arr_i(arr, i),
                                               __arr_i(arr, j));
}

/* the copyable array with meta */
iarray* iarraymakecopyablewithmeta(size_t capacity, const struct imeta *elem) {
    iarrayentry *entry = iobjmalloc(iarrayentry);
    entry->flag = EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero |
    EnumArrayFlagNeedFreeEntry;
    entry->size = elem->size;
    entry->swap = _iarray_entry_swap_copy;
    entry->assign = _iarray_entry_assign_copy;
    entry->cmp = _iarray_entry_copy_cmp;
    return iarraymake(capacity, entry);
}

/* compare */
static int _iarray_entry_cmp_int(struct iarray *arr,
                                 int i, int j) {
    int *arr_int = (int *)arr->buffer;
    return arr_int[i] - arr_int[j];
}

/* array-int config */
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

/* array-int */
iarray* iarraymakeint(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_int);
}

/* compare ireal */
static int _iarray_entry_cmp_ireal(struct iarray *arr,
                                   int i, int j) {
    ireal *arrs = (ireal *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* array-ireal config */
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

/* array-ireal */
iarray* iarraymakeireal(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_ireal);
}

/* compare int64 */
static int _iarray_entry_cmp_int64(struct iarray *arr,
                                   int i, int j) {
    int64_t *arrs = (int64_t *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* array-int64 config */
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

/* array-int64 */
iarray* iarraymakeint64(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_int64);
}

/* compare uint64 */
static int _iarray_entry_cmp_uint64(struct iarray *arr,
                                   int i, int j) {
    uint64_t *arrs = (uint64_t *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* array-uint64 config */
static const iarrayentry _arr_entry_uint64 = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagSimple |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(uint64_t),
    _iarray_entry_swap_copy,
    _iarray_entry_assign_copy,
    _iarray_entry_cmp_uint64,
};

/* array-uint64 */
iarray* iarraymakeuint64(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_uint64);
}

/* compare char */
static int _iarray_entry_cmp_char(struct iarray *arr,
                                  int i, int j) {
    char *arrs = (char *)arr->buffer;
    return arrs[i] - arrs[j];
}

/* array-char config */
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

/* array-char */
iarray* iarraymakechar(size_t capacity) {
    return iarraymake(capacity, &_arr_entry_char);
}


/*************************************************************/
/* iarray - iref                                             */
/*************************************************************/

/* array-iref assign */
static void _iarray_entry_assign_iref(struct iarray *arr,
                                      int i, const void *value, int nums) {
    iref* *arrs = (iref* *)arr->buffer;
    iref* *refvalue = (iref* *)value;
    iref* ref = NULL;
    int j = 0;
    irefarrayentry *entry = (irefarrayentry*)arr->userdata;
    
    /* for nums */
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
            entry->indexchange(entry, arr, arrs[i], kindex_invalid);
        }
        
        iassign(arrs[i], ref);
        
        /* watch the index change */
        if (ref && entry && entry->indexchange) {
            entry->indexchange(entry, arr, ref, i);
        }
        ++j;
        ++i;
    }
}

/* swap the iref */
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
            entry->indexchange(entry, arr, arrs[i], i);
            entry->indexchange(entry, arr, arrs[j], j);
        }
    }
}

/* compare iref */
static int _iarray_entry_cmp_iref(struct iarray *arr,
                                  int i, int j) {
    iref* *arrs = (iref* *)arr->buffer;
    /* the meta compare-funcs */
    const imeta *lfsmeta = iobjgetmeta(arrs[i]);
    const imeta *rfsmeta = iobjgetmeta(arrs[j]);
    const imeta *meta = lfsmeta?lfsmeta:rfsmeta;
    if (meta->funcs && meta->funcs->compare) {
        return meta->funcs->compare(meta->funcs, arrs[i], arrs[j]);
    }
    /* raw the meta compare with pointer */
    return arrs[i] - arrs[j];
}

/* array-iref config */
static const iarrayentry _arr_entry_iref = {
    EnumArrayFlagAutoShirk |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero,
    sizeof(iref*),
    _iarray_entry_swap_iref,
    _iarray_entry_assign_iref,
    _iarray_entry_cmp_iref,
};

/* array-iref */
iarray* iarraymakeiref(size_t capacity) {
    return iarraymakeirefwithentry(capacity, NULL);
}

/* array-iref with user config, index the change */
iarray* iarraymakeirefwithentry(size_t capacity, const irefarrayentry *refentry) {
    iarray*  arr = iarraymake(capacity, &_arr_entry_iref);
    arr->userdata = (void*)refentry;
    return arr;
}

/* array-iref with anthor cmp */
iarray* iarraymakeirefwithcmp(size_t capacity, iarray_entry_cmp cmp) {
    return iarraymakeirefwithentryandcmp(capacity, NULL, cmp);
}

/* array-iref with entry anthor cmp */
iarray* iarraymakeirefwithentryandcmp(size_t capacity, const irefarrayentry *refentry, iarray_entry_cmp cmp) {
    iarray*  arr;
    iarrayentry *entry = iobjmalloc(iarrayentry);
    
    entry->flag = EnumArrayFlagAutoShirk |
    EnumArrayFlagKeepOrder |
    EnumArrayFlagMemsetZero |
    EnumArrayFlagNeedFreeEntry;
    entry->size = sizeof(iref*);
    entry->swap = _iarray_entry_swap_iref;
    entry->assign = _iarray_entry_assign_iref;
    entry->cmp = cmp;
    
    arr = iarraymake(capacity, entry);
    arr->userdata = (void*)refentry;
    return arr;
}

/* implement a copyable array type */
#define __iimplement_array(type) \
static const iarrayentry _arr_entry_##type = {\
    EnumArrayFlagAutoShirk |\
    EnumArrayFlagKeepOrder |\
    EnumArrayFlagMemsetZero,\
    sizeof(type),\
    _iarray_entry_swap_copy,\
    _iarray_entry_assign_copy,\
    NULL,\
};\
iarray * iarraymake##type(size_t capacity) {\
    return iarraymake(capacity, &_arr_entry_##type);\
}

/* all-array-copyable-types */
#undef __ideclare_array_copy_type
#define __ideclare_array_copy_type(type) __iimplement_array(type)
__iall_array_types

/* get entry */
const iarrayentry* iarrayentryget(int type) {
    switch (type) {
        case EnumArrayEntryType_Char:
            return &_arr_entry_char;
            break;
        case EnumArrayEntryType_Int:
            return &_arr_entry_int;
            break;
        case EnumArrayEntryType_Int64:
            return &_arr_entry_int64;
            break;
        case EnumArrayEntryType_UInt64:
            return &_arr_entry_uint64;
            break;
        case EnumArrayEntryType_Real:
            return &_arr_entry_ireal;
            break;
        default:
            break;
    }
    return NULL;
}
