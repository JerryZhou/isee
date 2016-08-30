#ifndef _IHEAP_H_
#define _IHEAP_H_

#include "foundation/container/iarray.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* a heap is a array */
/* BIG-HEAP */
typedef iarray iheap;

/* build heap */
void iheapbuild(iheap *heap);

/* heap-size */
size_t iheapsize(const iheap *heap);

/* heap-operators: add element */
void iheapadd(iheap *heap, const void *value);

/* heap-operators: just element at index */
void iheapadjust(iheap *heap, int index);

/* heap-operators: peek the heap-top-element */
const void *iheappeek(const iheap *heap);
#define iheappeekof(heap, type) iarrayof(heap, type, 0)

/* heap-operators: remove the heap-top-element */
void iheappop(iheap *heap);

/* heap-operators: remove the heap-lement at index, and keep the heap order */
void iheapdelete(iheap *heap, int index);

/* heap-sort: [2, 3, 0, 1] ==> [0, 1, 2, 3] */
void iarraysortheap(iarray *arr, int start, int end);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif


#endif