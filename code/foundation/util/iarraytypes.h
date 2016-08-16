#ifndef _IARRAYTYPES_H_
#define _IARRAYTYPES_H_
#include "foundation/container/iarray.h"

/*************************************************************/
/* iarray: int, ireal, int64, char,                          */
/* iarray: iref                                              */
/*************************************************************/

/* 内置的整数数组 */
iarray* iarraymakeint(size_t capacity);

/* 浮点数组 */
iarray* iarraymakeireal(size_t capacity);

/* int64 数组*/
iarray* iarraymakeint64(size_t capacity);

/* char 数组*/
iarray* iarraymakechar(size_t capacity);

/* get entry */
const iarrayentry* iarrayentryget(int type);

/* 用来告知 对象的坐标发生变化 */
typedef void (*irefarray_index_change) (iarray *arr, iref *ref, int index);

/* append to iarray with iref entry */
typedef struct irefarrayentry {
    irefarray_index_change indexchange;
} irefarrayentry;

/* 内置的引用数组 */
iarray* iarraymakeiref(size_t capacity);

/* 内置的引用数组 */
iarray* iarraymakeirefwithentry(size_t capacity, const irefarrayentry *refentry);


/* 辅助宏，获取*/
#define iarrayof(arr, type, i) (((type *)iarrayat(arr, i))[0])

/* Helper-Macro: For-Earch in c89 */
#define irangearraycin(arr, type, begin, end, key, value, wrap) \
do { \
    for(key=begin; key<end; ++key) {\
        value = iarrayof(arr, type, key);\
        wrap;\
} } while(0)

/* Helper-Macro: For-Earch in c89 */
#define irangearrayc(arr, type, key, value, wrap) \
irangearraycin(arr, type, 0, iarraylen(arr), key, value, wrap)

/* Helper-Macro: For-Earch in cplusplus */
#define irangearrayin(arr, type, begin, end, wrap) \
do { \
    int __key; \
    type __value; \
    irangearraycin(arr, type, begin, end, __key, __value, wrap); \
} while(0)

/* Helper-Macro: For-Earch in cplusplus */
#define irangearray(arr, type, wrap) \
    irangearrayin(arr, type, 0, iarraylen(arr), wrap)

#endif