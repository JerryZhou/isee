#ifndef _ICONSISTENT_H_
#define _ICONSISTENT_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"

#include "foundation/util/istring.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*
 * https://github.com/stathat/consistent/blob/master/consistent.go
 * https://en.wikipedia.org/wiki/Consistent_hashing */
    
struct idict;
   
/* the consistent hash-circle 
 * add numberofreplicas of fake-hash in circle with averge of span in range
 * */
typedef struct iconsistent {
    irefdeclare;
    
    struct idict *circle;   /* idict<uint64_t, istring*> */
    struct idict *elems;    /* idict<istring*, ibool> */
    
    size_t numberofreplicas;/* number of replicas */
    
} iconsistent;

/* the consistent destructor */
void iconsistent_destructor(const struct imeta *meta, iptr o);
    
/* make a empty iconsistent */
iconsistent *iconsistentmake(size_t capacity, size_t replicas);
    
/* the element-size in circle */
size_t iconsistentsize(const iconsistent *c);
   
/* add ele to c in span: replicasspan with numberofreplicas */
void iconsistentadd(iconsistent *c, istring *ele);

/* remove ele from c in span */
void iconsistentremove(iconsistent *c, istring *ele);

/* set the circle to elems: remove all not in elems, add all in elems*/
void iconsistentset(iconsistent *c, iarray* elems); /* iarray<istring*> */

/* closed ele for key */
istring* iconsistentindexingof(const iconsistent *c, istring *key);

/* closed index for key */
int iconsistentindexing(const iconsistent *c, istring *key);

/* closed index for key then next n key will return */
iarray* iconsistentsearch(const iconsistent *c, istring *key, size_t n);

/* the hash-code-for key */
uint64_t iconsistenthashof(const iconsistent *c, istring *key);
    
/* the circle-size */
size_t iconsistentcount(const iconsistent *c);
/* the circle-hashcode at */
uint64_t iconsistentcodeat(const iconsistent *c, int index);
/* the circle-value at */
istring *iconsistentvalueat(const iconsistent *c, int index);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _ICONSISTENT_H_ */
