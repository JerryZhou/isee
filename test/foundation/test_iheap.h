#include "simpletest.h"
#include "foundation/container/iheap.h"
#include "foundation/util/iarraytypes.h"

SP_SUIT(iheap);

SP_CASE(iheap, iheapbuild) {
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);
    
    irelease(heap);
}

SP_CASE(iheap, iheapsize) {
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);
    
    SP_EQUAL(iheapsize(heap), 7);
    
    irelease(heap);
}

SP_CASE(iheap, iheapadd) {
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);

    int top = 7;
    iheapadd(heap, &top);
    SP_EQUAL(iarrayof(heap, int, 0), 7);
    
    irelease(heap);
}

SP_CASE(iheap, iheapadjust) {
    
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);
    
    int top = 7;
    iarrayset(heap, 5, &top);
    iheapadjust(heap, 5);
    SP_EQUAL(iarrayof(heap, int, 0), 7)
    
    irelease(heap);
}

SP_CASE(iheap, iheappeek) {
    
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);
    SP_EQUAL(iheappeekof(heap, int), 6);
    
    int top = 7;
    iarrayset(heap, 5, &top);
    iheapadjust(heap, 5);
    SP_EQUAL(iarrayof(heap, int, 0), 7)
    SP_EQUAL(iheappeekof(heap, int), 7);
    
    irelease(heap);
}

SP_CASE(iheap, iheappop) {
    
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);
    SP_EQUAL(iheappeekof(heap, int), 6);
    
    int top = 7;
    iarrayset(heap, 5, &top);
    iheapadjust(heap, 5);
    SP_EQUAL(iarrayof(heap, int, 0), 7)
    SP_EQUAL(iheappeekof(heap, int), 7);
    
    iheappop(heap);
    SP_EQUAL(iheappeekof(heap, int), 6);
    
    irelease(heap);
}

SP_CASE(iheap, iheapdelete) {
    
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 2, 3, 4, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    
    iheapbuild(heap);
    SP_EQUAL(iarrayof(heap, int, 0), 6);
    SP_EQUAL(iheappeekof(heap, int), 6);
    
    int top = 7;
    iarrayset(heap, 5, &top);
    iheapadjust(heap, 5);
    SP_EQUAL(iarrayof(heap, int, 0), 7)
    SP_EQUAL(iheappeekof(heap, int), 7);
    
    iheappop(heap);
    SP_EQUAL(iheappeekof(heap, int), 6);
    
    iheapdelete(heap, 3);
    SP_EQUAL(iheappeekof(heap, int), 6);
    
    iheapdelete(heap, 0);
    SP_EQUAL(iheappeekof(heap, int), 5);
    
    irelease(heap);
}

SP_CASE(iheap, iarraysortheap) {
    
    iheap *heap = iarraymakeint(10);
    int heap_values[] = {0, 1, 4, 3, 2, 5, 6};
    
    iarrayappend(heap, heap_values, icountof(heap_values));
    /*
    irangearray(heap, int,
                ilog("%s%d%s", __key == 0 ? "arr=[" :"", __value, __key == 6 ? "]\n" :", ");
                );
     */
    
    iarraysortheap(heap, 2, 4);
    iarraysortheap(heap, 0, 6);
    
    SP_EQUAL(iarrayof(heap, int, 0), 0);
    SP_EQUAL(iarrayof(heap, int, 1), 1);
    SP_EQUAL(iarrayof(heap, int, 2), 2);
    SP_EQUAL(iarrayof(heap, int, 3), 3);
    SP_EQUAL(iarrayof(heap, int, 4), 4);
    SP_EQUAL(iarrayof(heap, int, 5), 5);
    SP_EQUAL(iarrayof(heap, int, 6), 6);
    
    irelease(heap);
}

SP_CASE(iheap, end) {
    SP_TRUE(1);
}