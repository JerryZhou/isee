#include "foundation/container/iarray.h"
#include "foundation/memory/imemory.h"
#include "foundation/core/imetatypes.h"
#include "foundation/container/iheap.h"

/*invalid index */
const int kindex_invalid = -1;

/* release all resources hold by the array */
void iarray_destructor(const struct imeta *meta, iptr o) {
    iarray *array = icast(iarray, o);
    iarrayentry *entry = (iarrayentry*)array->entry;
    
    /* unset the autoshirnk flag */
    iarrayunsetflag(array, EnumArrayFlagAutoShirk);
    /* unset the sliced flag */
    iarrayunsetflag(array, EnumArrayFlagSliced);
    
    /* release all element */
    iarraytruncate(array, 0);
    /* release the raw buffer */
    ifree(array->buffer);
    /* for dynamic array */
    if (array->entry && iflag_is(array->entry->flag, EnumArrayFlagNeedFreeEntry)) {
        iobjfree(entry);
    }
    /* for dynamic user-data */
    if (array->userdata && array->entry && iflag_is(array->entry->flag, EnumArrayFlagNeedFreeUserData)) {
        iobjfree(array->userdata);
    }
    /*
     array->buffer = NULL;
     array->len = 0;
     array->capacity = 0;
     array->entry = NULL;
     array->free = NULL;
     array->flag = 0;
     */
}

/* make array */
iarray *iarraymake(size_t capacity, const iarrayentry *entry) {
    iarray *array = irefnew(iarray);
    array->capacity = capacity;
    array->len = 0;
    array->buffer = capacity > 0 ? (char*)icalloc(capacity, entry->size) : NULL;
    array->entry = entry;
    array->flag = entry->flag;
    array->cmp = entry->cmp;
    
    return array;
}

/* length */
size_t iarraylen(const iarray *arr) {
    icheckret(arr, 0);
    return arr->len;
}

/* capacity*/
size_t iarraycapacity(const iarray *arr) {
    icheckret(arr, 0);
    return arr->capacity;
}

/* indexing */
const void* iarrayat(const iarray *arr, int index) {
    icheckret(arr, NULL);
    icheckret(index>=0 && index<arr->len, NULL);
    
    return  __arr_i(arr, index);
}

/* element indexing */
const void* iarraylast(const iarray *arr) {
    icheckret(arr, NULL);
    icheckret(arr->len>0, NULL);
    
    return  __arr_i(arr, arr->len-1);
}

/* element indexing */
const void* iarrayfirst(const iarray *arr) {
    return iarrayat(arr, 0);
}

/* the raw buffer */
void* iarraybuffer(iarray *arr) {
    return arr->buffer;
}

/* set flag */
int iarraysetflag(iarray *arr, int flag) {
    int old = arr->flag;
    arr->flag |= flag;
    return old;
}

/* clear flag */
int iarrayunsetflag(iarray *arr, int flag){
    int old = arr->flag;
    arr->flag &= (~flag);
    return old;
}

/* have flag ?? */
int iarrayisflag(const iarray *arr, int flag) {
    return arr->flag & flag;
}

/* operators: remove */
int iarrayremove(iarray *arr, int index) {
    int i;
    
    icheckret(arr, iino);
    icheckret(index>=0 && index<arr->len, iino);
    /* sliced array can not be removed */
    icheckret(!iarrayisflag(arr, EnumArrayFlagSliced), iino);
    /* const array */
    icheckret(!iarrayisflag(arr, EnumArrayConst), iino);
    
    if (!(arr->entry->flag & EnumArrayFlagSimple)) {
        arr->entry->swap(arr, index, kindex_invalid);
    }
    
    if (arr->flag & EnumArrayFlagKeepOrder) {
        /* move element before */
        for(i=index; i<arr->len-1; ++i) {
            arr->entry->swap(arr, i, i+1);
        }
    } else if (arr->len-1 != index){
        /* directly swap the last element */
        arr->entry->swap(arr, index, arr->len-1);
    }
    --arr->len;
    return iiok;
}

/* NB!! should besure the redundant element have been destruct before call this */
static size_t _iarray_just_capacity(iarray *arr, size_t newcapacity) {
    char* newbuffer;
    newbuffer = irealloc(arr->buffer, newcapacity * arr->entry->size);
    icheckret(newbuffer, arr->capacity);
    /* 清理新加的内存 */
    if (arr->flag & EnumArrayFlagMemsetZero && newcapacity > arr->capacity) {
        memset(newbuffer + arr->capacity * arr->entry->size,
               0,
               (newcapacity-arr->capacity) * arr->entry->size);
    }
    
    arr->buffer = newbuffer;
    arr->capacity = newcapacity;
    return arr->capacity;
}

/* besure arr->capacity >= capacity, return the new capacity */
static size_t _iarray_be_capacity(iarray *arr, size_t capacity) {
    size_t newcapacity;
    
    icheckret(arr->capacity < capacity, arr->capacity);
    
    /* new capacity */
    newcapacity = imax(arr->capacity, 1);
    do {
        if (newcapacity < 1024) {
            newcapacity = newcapacity * 2;
        } else if (newcapacity < 1024*1024) {
            newcapacity = (size_t)(newcapacity  * 1.1f);
        } else {
            newcapacity = (size_t)(newcapacity * 1.01f);
        }
    } while(newcapacity < capacity);
    
    return _iarray_just_capacity(arr, newcapacity);
}

/* auto shrink the array capacity */
static void _iarrayautoshrink(iarray *arr) {
    size_t suppose = imax(arr->len * 2, 8);
    if (arr->capacity > suppose) {
        iarrayshrinkcapacity(arr, suppose);
    }
}

/* operators: add */
int iarrayadd(iarray *arr, const void* value) {
    return iarrayinsert(arr, arr->len, value, 1);
}

/* append values after */
int iarrayappend(iarray *arr, const void *value, int nums) {
    return iarrayinsert(arr, arr->len, value, nums);
}

/* operators: insert */
int iarrayinsert(iarray *arr, int index, const void *value, int nums) {
    int i;
    
    /* const array */
    icheckret(!iarrayisflag(arr, EnumArrayConst), iino);
    /* check if we need do insert */
    icheckret(nums > 0, iiok);
    /* check if the index belong to [0, arr->len] */
    icheckret(index>=0 && index<=arr->len, iino);
    /* the sliced array can not extend capacity */
    icheckret(!iarrayisflag(arr, EnumArrayFlagSliced)
              || (arr->len + nums) <= arr->capacity, iino);
    /* be sure the capacity is enough */
    _iarray_be_capacity(arr, arr->len + nums);
    /* check if we have been got enough space to do inserting*/
    icheckret(arr->capacity >= arr->len + nums, iino);
    
    /*swap after*/
    if (index != arr->len) {
        /* if the array is simple one, we can just do memove */
        /* simple flag is only for inner use */
        if (arr->entry->flag & EnumArrayFlagSimple) {
            arr->entry->assign(arr, index + nums,
                               __arr_i(arr, index),
                               arr->len - index);
        } else {
            /* swap one by one */
            i = arr->len - 1;
            while (i >= index) {
                arr->entry->swap(arr, i, i+nums);
                --i;
            }
        }
    }
    /* assign it */
    arr->entry->assign(arr, index, value, nums);
    arr->len += nums;
    return iiok;
}

/* operators: set value at index */
int iarrayset(iarray *arr, int index, const void *value) {
    /* length-rang-check */
    icheckret(index >=0 && index<arr->len, iino);
    /* const array */
    icheckret(!iarrayisflag(arr, EnumArrayConst), iino);
    
    arr->entry->assign(arr, index, value, 1);
    return iiok;
}

/* remove all elements */
void iarrayremoveall(iarray *arr) {
    iarraytruncate(arr, 0);
}

/* truncating the array to len */
void iarraytruncate(iarray *arr, size_t len) {
    int i;
    
    icheck(arr);
    icheck(arr->len > len);
    /* sliced array can not be truncate */
    icheck(!iarrayisflag(arr, EnumArrayFlagSliced));
    /* const array */
    icheck(!iarrayisflag(arr, EnumArrayConst));
    
    if (arr->entry->flag & EnumArrayFlagSimple) {
        /* direct set the length*/
        arr->len = len;
        /* auto shirk */
        if (arr->flag & EnumArrayFlagAutoShirk) {
            _iarrayautoshrink(arr);
        }
    } else {
        /* remove one by one*/
        for(i=arr->len; i>len; i--) {
            iarrayremove(arr, i-1);
        }
    }
}

/* shrink the capacity  */
size_t iarrayshrinkcapacity(iarray *arr, size_t capacity) {
    icheckret(arr->capacity > capacity, arr->capacity);
    /* const array */
    icheckret(!iarrayisflag(arr, EnumArrayConst), arr->capacity);
    
    /* sliced array can not be shrink */
    icheckret(!iarrayisflag(arr, EnumArrayFlagSliced), arr->capacity);
    
    capacity = imax(arr->len, capacity);
    return _iarray_just_capacity(arr, capacity);
}

/* expand the capacity */
size_t iarrayexpandcapacity(iarray *arr, size_t capacity) {
    icheckret(arr->capacity < capacity, arr->capacity);
    /* const array */
    icheckret(!iarrayisflag(arr, EnumArrayConst), arr->capacity);
    
    return _iarray_just_capacity(arr, capacity);
}

/* sort */
void iarraysort(iarray *arr) {
    icheck(arr->len);
    /* const array */
    icheck(!iarrayisflag(arr, EnumArrayConst));
    
    /* algorithm: heap-sort */
    iarraysortheap(arr, 0, arr->len-1);
}

/* the binary-index */
typedef struct iarray_searchpair {
    int found;
    int index;
} iarray_searchpair;

static iarray_searchpair _iarraybinaryindexing(const iarray *arr, int start, int end, const void *value) {
    iarray_searchpair pair = {.found = iino, .index=0};
    
    icheckretassert(start >=0 && end <= arr->len, pair);
    const imeta *meta = arr->entry->elemeta;
    int low = start;
    int heigh = end-1;
    int mid;
    int cmp;
    while (low <= heigh) {
        mid = (heigh - low)/2 + low;
        cmp = meta->funcs->compare(meta, iarrayat(arr, mid), value);
        
        pair.index = mid;   /* the insert index */
        if (cmp == 0) {
            pair.found = iiok;
            break;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            heigh = mid - 1;
        }
    }
    return pair;
}

/* binary search in array */
int iarraybinarysearch(const iarray *arr, int start, int end, const void* value) {
    iarray_searchpair pair = _iarraybinaryindexing(arr, start, end, value);
    return pair.found ? pair.index : kindex_invalid;
}

/* binary indexing the value: insert-place */
int iarraybinaryindexing(const iarray *arr, int start, int end, const void *value) {
    iarray_searchpair pair = _iarraybinaryindexing(arr, start, end, value);
    const imeta *meta = arr->entry->elemeta;
    
    if (pair.found == iino) {
        return pair.index;
    } else {
        while (pair.index < end &&
               meta->funcs->compare(meta, iarrayat(arr, pair.index), value) <= 0) {
            ++pair.index;
        }
        return pair.index;
    }
}
 
/* binary search insert into array [start, end] */
int iarraybinaryinsert(iarray *arr, int start, int end, const void* value) {
    int index = iarraybinaryindexing(arr, start, end, value);
    iarrayinsert(arr, index, value, 1);
    return index;
}

/* for each */
void iarrayforeach(const iarray *arr, iarray_entry_visitor visitor) {
    size_t size = iarraylen(arr);
    size_t idx = 0;
    for (; idx < size; ++idx) {
        visitor(arr, idx, iarrayat(arr, idx));
    }
}

/* array entry of arr */
const iarrayentry *iarrayentryof(const iarray *arr) {
    icheckret(arr, NULL);
    return arr->entry;
}
 
/* array linking with right imeta */
int iarrayentryset(const iarrayentry *entry, const struct imeta *meta) {
    iarrayentry* nentry = (iarrayentry*)entry;
    icheckret(entry, iino);
    icheckret(entry->elemeta != meta, iino);
    
    nentry->elemeta = meta;
    return iiok;
}

/* get the array element meta */
const struct imeta *iarrayelementmeta(const iarray *arr) {
    icheckret(arr, imetaof(inull));
    return arr->entry->elemeta;
}


