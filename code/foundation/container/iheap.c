#include "foundation/container/iheap.h"


/* heap-sort */
static void _iarray_heap_shift(iarray *arr,
                               int ind, int end, int offset) {
    
    int i = ind - offset;
    int offend = end - offset;
    int c = 2 * i + 1;
    
    while(c <= offend) {
        if (c+1 <=offend && arr->cmp(arr, c+offset, c+1+offset) < 0 ) {
            c++;
        }
        if (arr->cmp(arr, i+offset, c+offset) > 0) {
            break;
        } else {
            arr->entry->swap(arr, i+offset, c+offset);
            
            i = c;
            c = 2*i + 1;
        }
    }
}

/* build heap betwween [start, end] */
static void _iarray_heap_build(iarray *arr, int start, int end) {
    int i;
    for (i=(end-start-1)/2; i>=0; i--) {
        _iarray_heap_shift(arr, i+start, end, start);
    }
}

/* sort heap */
void iarraysortheap(iarray *arr, int start, int end) {
    int i;
    icheck(iarraylen(arr) > 0);
    icheckassert(start>=0 && start<=end && end <=(iarraylen(arr)-1));
    
    /* build heap */
    _iarray_heap_build(arr, start, end);
    
    for (i=0; i<=end-start; ++i) {
        /* minisize the heap: swap the biggest to last */
        arr->entry->swap(arr, start, end-i);
        /* adjust the heap to find the biggest one */
        _iarray_heap_shift(arr, start, end - i - 1, start);
    }
}

/* build heap */
void iheapbuild(iheap *heap) {
    _iarray_heap_build(heap, 0, iarraylen(heap));
}

/* heap-size */
size_t iheapsize(const iheap *heap) {
    return iarraylen(heap);
}

/* adjust heap down-side */
static void _iheapadjustup(iheap *heap, int start, int index) {
    int parent;
    while(index > start) {
        parent = (index-1) / 2;
        if ( heap->cmp(heap, index, parent) > 0) {
            heap->entry->swap(heap, index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

/* adjust heap donw-side */
static void _iheapadjustdown(iheap *heap, int index, int end) {
    _iarray_heap_shift(heap, index, end, 0);
}

/* heap-operators: add element */
void iheapadd(iheap *heap, const void *value) {
    int index = iarraylen(heap);
    iarrayadd(heap, value);
    
    /*adjust up*/
    _iheapadjustup(heap, 0, index);
}

/* heap-operators: just element at index */
void iheapadjust(iheap *heap, int index) {
    int i = index;
    int c = 2*i + 1;
    int start = 0;
    int end = (int)iheapsize(heap);
    
    if (c+1<=end && heap->cmp(heap, c, c+1) < 0) {
        c++;
    }
    if (c <= end && heap->cmp(heap, c, i) > 0) {
        _iheapadjustdown(heap, index, end);
    } else {
        _iheapadjustup(heap, start, index);
    }
}

/* heap-operators: peek the heap-top-element */
const void *iheappeek(const iheap *heap) {
    icheckret(iarraylen(heap) > 0, NULL);
    return iarrayat(heap, 0);
}

/* heap-operators: remove the heap-top-element */
void iheappop(iheap *heap) {
    iheapdelete(heap, 0);
}

/* heap-operators: remove the heap-lement at index, and keep the heap order */
void iheapdelete(iheap *heap, int index) {
    icheck(index>=0 && index<iarraylen(heap));
    
    /*swap last one*/
    heap->entry->swap(heap, index, iarraylen(heap)-1);
    /*array remove it*/
    iarrayremove(heap, iarraylen(heap)-1);
    
    /*adjust the heap to be still on*/
    if (iarraylen(heap) > 0 ) {
        _iarray_heap_shift(heap, index, iarraylen(heap)-1, 0);
    }
}
