#ifndef _ILAMPORT_H_
#define _ILAMPORT_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
 
/* the forward declares */
struct iarray;
    
/* https://en.wikipedia.org/wiki/Lamport%27s_bakery_algorithm */
typedef struct ilamport {
    irefdeclare;
    
    struct iarray* entering;
    struct iarray* number;
    
} ilamport;
    
/*
 Thread(integer i) {
     while (true) {
         lock(i);
         // The critical section goes here...
         unlock(i);
         // non-critical section...
     }
 }
 */
   
/* the lamport algorithm for hardcode-capacity */
ilamport* ilamportmake(size_t capacity);

/* the lamport algorithm for lock */
void ilamportlock(ilamport *l, int i);

/* the lamport algorithm for unlock */
void ilamportunlock(ilamport *l, int i);

/* the meta destructor func */
void ilamport_destructor(const struct imeta* , iptr o);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _ILAMPORT_H_ */
