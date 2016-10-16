
#include "simpletest.h"
#include "foundation/memory/imemory.h"

// **********************************************************************************
// imemory
SP_SUIT(imemory);

SP_CASE(imemory, icallocANDifree) {
    int *i = (int*)icalloc(1, sizeof(int));
    SP_EQUAL(*i, 0);
    ifree(i);
}

SP_CASE(imemory, irealloc) {
    int *i = (int*)icalloc(2, sizeof(int));
    SP_EQUAL(i[0], 0);
    SP_EQUAL(i[1], 0);
    i[1] = 5;
    SP_EQUAL(i[1], 5);
    i = (int*)irealloc(i, sizeof(int)*3);
    SP_EQUAL(i[0], 0);
    SP_EQUAL(i[1], 5);
    SP_EQUAL(i[2], 0);
    ifree(i);
}

SP_CASE(imemory, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
