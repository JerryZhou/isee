#include "foundation/imemorystatistics.h"

/* memory-behavior: alloc */
void imemorystatisbehavior_alloc(imemorystatistics *statis, size_t size) {
    statis->alloced += size;
    statis->current += size;
}

/* memory-behavior: free */
void imemorystatisbehavior_free(imemorystatistics *statis, size_t size) {
    statis->freed += size;
    statis->current -= size;
}
