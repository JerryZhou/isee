#include "foundation/imemory.h"
#include "foundation/itype.h"

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
