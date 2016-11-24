#ifndef _ISLICE_H_
#define _ISLICE_H_

#include "foundation/container/iarray.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*make the slice be a string or heap*/
typedef enum EnumSliceFlag {
    EnumSliceFlag_String = 1<<3,
}EnumSliceFlag;

/*
 * the slice source is a const array
 * any array have been sliced will become the const array, 
 * that means the array can not change the capacity any more
 **/
typedef struct islice {
    irefdeclare;
    
    iarray *array;
    
    /*
     * len = end - begin
     * real.capacity = capacity - begin
     **/
    int begin;
    int end;
    int capacity;
    
    /* special flags */
    int flag;
}islice;

/* visitor */
typedef void (*islice_entry_visitor)(const islice *slice,
int i, const void *value);

/* destructor */
void islice_destructor(const struct imeta*, iptr o);

/* the section [begin, end) */
islice *islicemake(iarray *arr, int begin, int end, int capacity);

/* the section [begin, end) */
islice *islicemakeby(islice *slice, int begin, int end, int capacity);

/* make slice by brief args "begin:end:capacity"
 * islicemakearg(arr, ":")
 * islicemakearg(arr, ":1")
 * islicemakearg(arr, ":1:5")
 * islicemakearg(arr, "3:1:5")
 * islicemakearg(arr, "3:")
 */
islice *islicemakearg(iarray *arr, const char* args);

/* make slice by brief args "begin:end:capacity"
 * islicemakeargby(arr, ":")
 * islicemakeargby(arr, ":1")
 * islicemakeargby(arr, ":1:5")
 * islicemakeargby(arr, "3:1:5")
 * islicemakeargby(arr, "3:")
 */
islice *islicemakeargby(islice *slice, const char* args);

/* make slice from array, all slice make by array shared the capacity */
#define isliced(arr, begin, end) islicemake((arr), (begin), (end), (int)((arr)->capacity))
/* make slice from slice, all slice make by array shared the capacity */
#define islicedby(slice, begin, end) islicemakeby((slice), (begin), (end), islicecapacity(slice))

/* parse the args */
void isliceparamsparse(int *params, const char* args, const char delim);

/* length */
size_t islicelen(const islice *slice);

/* capacity */
size_t islicecapacity(const islice *slice);

/* append
 * usage: slice = isliceappendvalues(slice, values, count); */
islice* isliceappendvalues(islice* slice, const void *values, int count);

/* append
 * usage: slice = isliceappend(slice, append); */
islice* isliceappend(islice *slice, const islice *append);

/*
 * add value
 * usage : slice = isliceadd(slice, i); */
islice* isliceadd(islice *slice, const void *value);

/* set value at index */
int isliceset(islice *slice, int index, const void *value);

/* slice indexing */
const void* isliceat(const islice *slice, int index);

/* foreach */
void isliceforeach(const islice *slice, islice_entry_visitor visitor);

/* macro: indexing */
#define isliceof(slice, type, i) (((type *)isliceat(slice, i))[0])

/* Helper-Macro: For-Earch in c89 */
#define irangeslicecin(arr, type, begin, end, key, value, wrap) \
do { \
    for(key=begin; key<end; ++key) {\
        value = isliceof(arr, type, key);\
        wrap;\
    }\
} while(0)

/* Helper-Macro: For-Each in c89*/
#define irangeslicec(slice, type, key, value, wrap) \
irangeslicecin(slice, type, 0, islicelen(slice), key, value, wrap)

/* Helper-Macro: For-Each in cplusplus*/
#define irangeslicein(slice, type, begin, end, wrap) \
do {\
    int __key;\
    type __value;\
    irangeslicecin(slice, type, begin, end, __key, __value, wrap);\
} while(0)

/* Helper-Macro: For-Each in cplusplus*/
#define irangeslice(slice, type, wrap) \
    irangeslicein(slice, type, 0, islicelen(slice), wrap)
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
