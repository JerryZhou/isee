#ifndef _IQUORUM_H_
#define _IQUORUM_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* forward declares */
struct iarray;

/*
 * http://www.cnblogs.com/jzhlin/archive/2012/07/23/Quorum.html
 * https://en.wikipedia.org/wiki/Quorum_(distributed_computing)
 * V(r) + V(w) > V
 * V(w) > V/2
 * */
typedef struct iquorum {
    size_t q;
    size_t qr;
    size_t qw;
} iquorum;

typedef struct iquorumvalue {
    uint32_t version;
    struct iarray *data;
} iquorumvalue;

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IQUORUM_H_ */
