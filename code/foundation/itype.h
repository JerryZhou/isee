#ifndef _ITYPE_H_
#define _ITYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdarg.h>
#include <assert.h>

/* Set up for C function definitions, even when using C++ */

#ifdef __cplusplus
extern "C" {
#endif
    
/* if we support thread safe in meta system and ref */
#define iithreadsafe (1)
    
/* this pointer */
typedef void* ithis;

/* default name with 32 bits */
typedef char iname[32];
    
/* flag operators */
#define iflag_add(value, state) value |= state
#define iflag_remove(value, state) value &= ~state
#define iflag_is(value, state) (value & state)

#ifdef _WIN32

#include <windows.h>
#define snprintf _snprintf

// TODO: figure out a multiplatform version of uint64_t
// - maybe: https://code.google.com/p/msinttypes/
// - or: http://www.azillionmonkeys.com/qed/pstdint.h
typedef _int64 int64_t;
typedef _uint64 uint64_t;
typedef _int32 int32_t;
typedef _uint32 uint32_t;

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif /* end of: offsetof */

#ifndef container_of
#define container_of(ptr, type, member) ({            \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);\
    (type *)( (char *)__mptr - offsetof(type,member) );})
#endif /* end of:container_of */

#else
#include <stdbool.h>
#include <inttypes.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#endif /* end of: _WIN32 */
   
/* type define */
typedef unsigned char ibyte;
typedef unsigned char ibool;
 
/* the foundation bool */
#define iiyes 1
#define iiok 1
#define iino 0
    
/* for params */
#define __iin
#define __iout
#define __ioutin

/* condition-check, without assert */
#define icheck(con) do { if(!(con)) return ; } while(0)
#define icheckret(con, ret) do { if(!(con)) return ret; } while(0)

/* condition-check, with assert */
#define icheckassert(con) do { if (!(con)) { assert(#con && 0); return ; } } while(0)
#define icheckretassert(con, ret) do { if(!(con)) { assert(#con && 0); return ret ; } } while(0)

/* flat array count */
#define icountof(arr) (sizeof(arr)/sizeof(arr[0]))
    
/* useful macros */
#define imax(a, b) ((a) > (b) ? (a) : (b))
#define imin(a, b) ((a) < (b) ? (a) : (b))
#define iunused(v) (void)(v)
#define ilog(...) printf(__VA_ARGS__)

/* the todos macro */
#define itodos(...) do { ilog("[ilog-todo](%s, %s, %d)==>   ", __FILE__, __FUNCTION__, __LINE__); ilog(__VA_ARGS__); ilog("\n"); } while(0)

/* 精度 */
typedef float ireal;
    
/* real default epsilon */
#define iepsilon 0.1e-4
    
/* compartor: equal-eps */
#define ireal_equal_in(a, b, eps) (fabs((a)-(b)) < (eps))
    
/*compartor: equal*/
#define ireal_equal(a, b) ireal_equal_in(a, b, iepsilon)
    
/*compartor: equal-zero*/
#define ireal_equal_zero(a) ireal_equal(a, 0)
    
/* compartor: less */
#define ireal_less_than(a, b, eps) ((a-b) < -eps)
#define ireal_less(a, b) ireal_less_than(a, b, iepsilon)
    
/* compartor: greater */
#define ireal_greater_than(a, b, eps) ((a-b) > eps)
#define ireal_greater(a, b) ireal_greater_than(a, b, iepsilon) 
    
/*less than 0*/
#define ireal_less_zero(a) ireal_less_than(a, 0, iepsilon)
    
/*greater than 0*/
#define ireal_greater_zero(a) ireal_greater_than(a, 0, iepsilon)
  
/* compare equal real vectors */
#define ireal_equal_2(a, b) (ireal_equal((a)[0], (b)[0]) && ireal_equal((a)[1], (b)[1]))

/* compare equal real vectors */
#define ireal_equal_3(a, b) (ireal_equal((a)[0], (b)[0]) \
    && ireal_equal((a)[1], (b)[1]) \
    && ireal_equal((a)[2], (b)[2]))
    
/* compare equal real vectors */
#define ireal_equal_4(a, b) (ireal_equal((a)[0], (b)[0]) \
    && ireal_equal((a)[1], (b)[1]) \
    && ireal_equal((a)[2], (b)[2]) \
    && ireal_equal((a)[3], (b)[3]))
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* end of _ITYPE_H_ */
