#include "foundation/container/islice.h"
#include "foundation/core/imetatypes.h"

/* free slice and slice-array */
void islice_destructor(iptr x, iptr o ) {
    islice *slice = icast(islice, o);
    irelease(slice->array);
}

/* half-open range [begin, end) */
islice *islicemake(iarray *arr, int begin, int end, int capacity) {
    islice* slice;
    int difflen = imax(end-begin, 0);
    int diffcap = imax(capacity-begin, 0);
    icheckret(arr, NULL);
    
    /*begin = [0, arr->len] */
    begin = imax(0, begin);
    begin = imin(begin, (arr->len));
    /*end = [begin, arr->len] */
    end = begin + difflen;
    end = imin(end, arr->len);
    /*capacity = [end, arr->capacity] */
    capacity = imax(end, begin + diffcap);
    capacity = imin(capacity, arr->capacity);
    
    /* arr marked sliced,
     * the array will become the const array with capacity
     * can not do operators: iarrayremove, iarrayshirnkcapacity, iarraytruncate
     * */
    iarraysetflag(arr, EnumArrayFlagSliced);
    
    slice = irefnew(islice);
    slice->begin = begin;
    slice->end = end;
    slice->capacity = capacity;
    iassign(slice->array, arr);
    
    return slice;
}

/* section [begin, end) */
islice *islicemakeby(islice *sli, int begin, int end, int capacity) {
    icheckret(sli, NULL);
    /* real slice */
    return islicemake(sli->array,
                      sli->begin + begin,
                      sli->begin + end,
                      sli->begin + capacity);
}


/* make by brief args "begin:end:capacity"
 * islicemakearg(arr, ":")
 * islicemakearg(arr, ":1")
 * islicemakearg(arr, ":1:5")
 * islicemakearg(arr, "3:1:5")
 * islicemakearg(arr, "3:")
 */
islice *islicemakearg(iarray *arr, const char* args) {
    int params[3] = {0, (int)iarraylen(arr), (int)iarraycapacity(arr)};
    isliceparamsparse(params, args, ':');
    return islicemake(arr, params[0], params[1], params[2]);
}

/* make by brief args "begin:end:capacity"
 * islicemakeargby(arr, ":")
 * islicemakeargby(arr, ":1")
 * islicemakeargby(arr, ":1:5")
 * islicemakeargby(arr, "3:1:5")
 * islicemakeargby(arr, "3:")
 */
islice *islicemakeargby(islice *slice, const char* args) {
    int params[3] = {0, (int)islicelen(slice), (int)islicecapacity(slice)};
    isliceparamsparse(params, args, ':');
    return islicemakeby(slice, params[0], params[1], params[2]);
}

/* args parse */
void isliceparamsparse(int *params, const char* args, const char delim) {
    int n=0;
    int m=0;
    int i=0;
    int len=0;
    char buffer[256]= {0};
    char *arg;
    if (args == NULL || strlen(args) == 0) {
        return;
    }
    len = strlen(args);
    if (len > 256) {
        arg = (char*)calloc(1, len);
    } else {
        arg = buffer;
    }
    strcpy(arg, args);
    
    for (m=0; m<len; ++m) {
        if (args[m] == delim) {
            /* found
             * [n, m) */
            if (m > n) {
                params[i] = atoi(arg+n);
            }
            n = m+1;
            ++i;
        }
    }
    if (m > n) {
        params[i] = atoi(args+n);
    }
    
    if (arg != buffer) {
        free(arg);
    }
}

/* length */
size_t islicelen(const islice *slice) {
    icheckret(slice, 0);
    icheckret(slice->end > slice->begin, 0);
    return slice->end - slice->begin;
}

/* capacity */
size_t islicecapacity(const islice *slice) {
    icheckret(slice, 0);
    icheckret(slice->array, 0);
    icheckret(slice->capacity > slice->begin, 0);
    return slice->capacity - slice->begin;
}

/* append
 * usage: slice = isliceappendvalues(slice, values, count); */
islice* isliceappendvalues(islice* slice, const void *values, int count) {
    int appendcount = count;
    int needcapacity = (slice->end+appendcount-1);
    int index = slice->end;
    int indexappend = 0;
    size_t newcapacity = 0;
    islice *newslice;
    iarray * newarray;
    icheckret(values, slice);
    
#define __value_i(values, i, size) (const void *)((char*)values + i * size)
    
    /* if we got enough space*/
    if (needcapacity < slice->capacity) {
        /* set */
        while (index < slice->array->len
               && indexappend < appendcount) {
            iarrayset(slice->array, index,
                      __value_i(values, indexappend, slice->array->entry->size));
            ++index;
            ++indexappend;
        }
        /* append */
        if (indexappend < appendcount) {
            iarrayinsert(slice->array, index,
                         __value_i(values, indexappend, slice->array->entry->size),
                         appendcount - indexappend);
        }
        /* update the slice end cursor */
        slice->end += appendcount;
    } else {
        newcapacity = islicecapacity(slice);
        newcapacity = imax(newcapacity, 4);
        needcapacity = islicelen(slice) + appendcount;
        
        /* caculate the new capacity*/
        while (newcapacity < needcapacity) {
            if (newcapacity < 1000) {
                newcapacity = (size_t)(newcapacity * 2);
            } else {
                newcapacity = (size_t)(newcapacity * 6 / 5);
            }
        }
        /*new array*/
        newarray = iarraymake(newcapacity, slice->array->entry);
        /*copy from old slice*/
        iarrayinsert(newarray, 0, __arr_i(slice->array, slice->begin), islicelen(slice));
        /*add new values*/
        iarrayinsert(newarray, newarray->len, values, appendcount);
        /*make new slice*/
        newslice = islicemake(newarray, 0, needcapacity, newcapacity);
        
        /* set slice to return*/
        /* free the old slice*/
        iassign(slice, newslice);
        
        /* free the new array ref*/
        irelease(newarray);
        /* free the new slice */
        irelease(newslice);
    }
    return slice;
}

/* append */
islice* isliceappend(islice *slice, const islice *append) {
    /* should be the same slice entry */
    icheckret(slice, NULL);
    icheckret(append, slice);
    icheckret(slice->array->entry == slice->array->entry, slice);
    return isliceappendvalues(slice,
                              __arr_i(append->array, append->begin),
                              islicelen(append));
}

/* add element */
islice* isliceadd(islice *slice, const void *value) {
    return isliceappendvalues(slice, value, 1);
}

/* set value at index */
int isliceset(islice *slice, int index, const void *value) {
    icheckret(slice, iino);
    icheckret(slice->array, iino);
    icheckret(index>=0 && index<islicelen(slice), iino);
    
    return iarrayset(slice->array, slice->begin + index, value);
}

/* indexing */
const void* isliceat(const islice *slice, int index) {
    /* can not read more than slice can reached */
    icheckret(index>=0 && index<islicelen(slice), NULL);
    /* read from array */
    return iarrayat(slice->array, slice->begin+index);
}

/* foreach */
void isliceforeach(const islice *slice, islice_entry_visitor visitor) {
    size_t size = islicelen(slice);
    size_t idx = 0;
    for (; idx<size; ++idx) {
        visitor(slice, idx, isliceat(slice, idx));
    }
}
