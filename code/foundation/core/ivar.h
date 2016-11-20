#ifndef _IVAR_H_
#define _IVAR_H_

#include "foundation/itype.h"
#include "foundation/core/iref.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward -declares */
struct imeta;
   
/* the ivar wrap all couldbeable */
typedef struct ivar {
    irefdeclare;
    union {
        int i;
        int64_t i64;
        uint64_t u64;
        ireal real;
        iref *ref;
        void *ptr;
        ipod pod;
    } v ;
    const struct imeta *meta; /* type-meta */
} ivar;
    
/* ivar type: meta-index */
int ivartype(const ivar *var);
/* ivar type: meta */
const struct imeta *ivarmeta(const ivar *var);
    
/* simple ivar */
int ivarissimple(const ivar *var);
    
/* ivar is right-meta-type */
ibool ivaris(const ivar *var, const struct imeta *meta);
    
/* ivar copy */
ivar *ivardup(const ivar *var);
  
/* ivar hash code */
uint64_t ivarhashcode(const ivar *var);

/* ivar make functions  */
ivar *ivarmakeint(int i);
ivar *ivarmakei64(int64_t i64);
ivar *ivarmakeu64(uint64_t u64);
ivar *ivarmakereal(ireal real);
ivar *ivarmakeptr(iptr *ptr);
ivar *ivarmakepod(ipod pod);
ivar *ivarmakeref(iref *ref);
    
/* ivar destructor */
void ivar_destructor(iptr x, iobj *o);

/* ivar meta-funcs: hashcode */
uint64_t ivar_hash(iptr x, iobj *o);

/* ivar meta-funcs: compare */
int ivar_compare(iptr x, iobj *lfs, iobj *rfs);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IVAR_H_ */
