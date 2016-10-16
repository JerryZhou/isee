#ifndef _IARRAY_H_
#define _IARRAY_H_

#include "foundation/core/iref.h"


/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* forward declares */
struct iarray;

/* if swap with kindex_invalid, should reset element to zero */
/* invalid index */
extern const int kindex_invalid;

/* swap i, j */
typedef void (*iarray_entry_swap)(struct iarray *arr, int i, int j);
/* compare i, j */
typedef int (*iarray_entry_cmp)(struct iarray *arr, int i, int j);
/* assign values to [i, i+num)  */
typedef void (*iarray_entry_assign)(struct iarray *arr, int i, const void *value, int nums);
/* foreach visitor */
typedef void (*iarray_entry_visitor)(const struct iarray *arr, int i, const void *value);

/* array control flags */
typedef enum EnumArrayFlag {
    EnumArrayFlagNone = 0,
    
    /* when remove element in array,
     * we will swap the end element to removed positon * */
    EnumArrayFlagKeepOrder = 1<<1,  /* keep the array element order */
    
    /* simple array,
     * the element should be with raw memory, no need to destructor
     * when call truncate, we will set the array length directly.
     * the simple array's assign operators should imp the memmove behavior
     * as we known the memmove operating can handle the overlapping problem.
     * the flag should be set on the array's entry struct, and cannot change runtime*/
    EnumArrayFlagSimple = 1<<2,
    
    /* auto shink the memory taken by array*/
    EnumArrayFlagAutoShirk = 1<<3,
    
    /* MemSet Pennding Memory */
    EnumArrayFlagMemsetZero = 1<<4,
    
    /* the array have been sliced, then the array should not do any operators in shirk, remove, truncate
     * after sliced the insert operator will failed when the capacity need expanding */
    EnumArrayFlagSliced = 1<<5,
   
    /* the array entry is malloc by dynamic */
    EnumArrayFlagNeedFreeEntry = 1<<6,
    
    /* the array userdata is malloc by dynamic */
    EnumArrayFlagNeedFreeUserData = 1<<7,
    
    /* the array is the const-array */
    EnumArrayConst = 1<<8,
}EnumArrayFlag;

/* the array sencond-meta information */
typedef struct iarrayentry{
    int flag;
    size_t size;
    iarray_entry_swap swap;
    iarray_entry_assign assign;
    iarray_entry_cmp cmp;
} iarrayentry;

/* generated array */
typedef struct iarray {
    irefdeclare;
    
    size_t capacity;
    size_t len;
    char *buffer;
    int flag;
    iarray_entry_cmp cmp;
    
    /* the array-meta */
    const iarrayentry* entry;
    
    /* user data appending to array*/
    void *userdata;
}iarray;

/* array destructor */
void iarray_destructor(ithis x, iobj *o);
    
/* make array with type entry */
iarray *iarraymake(size_t capacity, const iarrayentry *entry);

/* length */
size_t iarraylen(const iarray *arr);

/* capacity */
size_t iarraycapacity(const iarray *arr);

/* element indexing */
const void* iarrayat(const iarray *arr, int index);
/* element indexing */
const void* iarraylast(const iarray *arr);
/* element indexing */
const void* iarrayfirst(const iarray *arr);

/* the array raw buffer */
void* iarraybuffer(iarray *arr);

/* set the runtime-flag */
int iarraysetflag(iarray *arr, int flag);

/* unset the runtime-flag, and return the old flag */
int iarrayunsetflag(iarray *arr, int flag);

/* if the array have flag */
int iarrayisflag(const iarray *arr, int flag);

/* operators: remove */
int iarrayremove(iarray *arr, int index);

/* operators: add */
int iarrayadd(iarray *arr, const void* value);
    
/* append values after */
int iarrayappend(iarray *arr, const void *value, int nums);

/* operators: insert */
int iarrayinsert(iarray *arr, int index, const void *value, int nums);

/* operators: set value at index */
int iarrayset(iarray *arr, int index, const void *value);

/* remove all element, then the array length will be zero */
void iarrayremoveall(iarray *arr);

/* truncating the array length */
void iarraytruncate(iarray *arr, size_t len);

/* operators: shrinking the capacity */
size_t iarrayshrinkcapacity(iarray *arr, size_t capacity);

/* operators: expanding the capacity */
size_t iarrayexpandcapacity(iarray *arr, size_t capacity);

/* sort array with cmp in entry */
void iarraysort(iarray *arr);

/* for each */
void iarrayforeach(const iarray *arr, iarray_entry_visitor visitor);
    
/* array entry of arr */
const iarrayentry *iarrayentryof(const iarray *arr);

/* macro: indexing */
#define __arr_i(arr, i) ((void*)((arr)->buffer + (i) * (arr)->entry->size))
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif