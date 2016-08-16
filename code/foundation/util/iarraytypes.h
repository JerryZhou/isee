#ifndef _IARRAYTYPES_H_
#define _IARRAYTYPES_H_
#include "foundation/container/iarray.h"

/*************************************************************/
/* iarray: int, ireal, int64, char,                          */
/* iarray: iref                                              */
/*************************************************************/

/* array-int */
iarray* iarraymakeint(size_t capacity);

/* array-ireal */
iarray* iarraymakeireal(size_t capacity);

/* array-int64 */
iarray* iarraymakeint64(size_t capacity);

/* array-char */
iarray* iarraymakechar(size_t capacity);

/* get entry */
const iarrayentry* iarrayentryget(int type);

/* tracing the index change in array with ref */
typedef void (*irefarray_index_change) (iarray *arr, iref *ref, int index);

/* append to iarray with iref entry */
typedef struct irefarrayentry {
    irefarray_index_change indexchange;
} irefarrayentry;

/* array-iref */
iarray* iarraymakeiref(size_t capacity);

/* array-iref tracing the indexing change */
iarray* iarraymakeirefwithentry(size_t capacity, const irefarrayentry *refentry);

/* macro: indexing */
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