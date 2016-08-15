#ifndef _IMEMORY_H_
#define _IMEMORY_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/*Allocates a block of memory for an array of num elements, each of them size bytes long, and initializes all its bits to zero.
 *
 * The effective result is the allocation of a zero-initialized memory block of (num*size) bytes.
 *
 * If size is zero, the return value depends on the particular library implementation (it may or may not be a null pointer), but the returned pointer shall not be dereferenced.
 * */
void *icalloc(size_t num, size_t size);

/*Changes the size of the memory block pointed to by ptr.
 *
 * The function may move the memory block to a new location (whose address is returned by the function).
 *
 * The content of the memory block is preserved up to the lesser of the new and old sizes, even if the block is moved to a new location. If the new size is larger, the value of the newly allocated portion is indeterminate.
 *
 * In case that ptr is a null pointer, the function behaves like malloc, assigning a new block of size bytes and returning a pointer to its beginning.*/
void *irealloc(void *ptr, size_t size);

/*A block of memory previously allocated by a call to malloc, calloc or realloc is deallocated, making it available again for further allocations.
 *
 * If ptr does not point to a block of memory allocated with the above functions, it causes undefined behavior.
 *
 * If ptr is a null pointer, the function does nothing.
 *
 * Notice that this function does not change the value of ptr itself, hence it still points to the same (now invalid) location.*/
void ifree(void *ptr);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
