#include "foundation/memory/imemory.h"
#include "foundation/itype.h"

/*
* http://stackoverflow.com/questions/227897/how-to-allocate-aligned-memory-only-using-the-standard-library
* http://stackoverflow.com/questions/1919183/how-to-allocate-and-free-aligned-memory-in-c
* // cache line
* #define ALIGN 64
* void *aligned_malloc(int size) {
*    void *mem = malloc(size+ALIGN+sizeof(void*));
*    void **ptr = (void**)((uintptr_t)(mem+ALIGN+sizeof(void*)) & ~(ALIGN-1));
*    ptr[-1] = mem;
*    return ptr;
* }
* void aligned_free(void *ptr) {
*       free(((void**)ptr)[-1]);
* }
* */

/*http://www.cplusplus.com/reference/cstdlib/calloc/*/
void *icalloc(size_t num, size_t size) {
    return calloc(num, size);
}

/*http://www.cplusplus.com/reference/cstdlib/realloc/*/
void *irealloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

/*http://www.cplusplus.com/reference/cstdlib/free/*/
void ifree(void *ptr) {
    free(ptr);
}
