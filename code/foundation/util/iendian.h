#ifndef _IENDIAN_H_
#define _IENDIAN_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* check bigendian */
ibool iendianlittle();

/* check bigendian */
ibool iendianbig();

/* the edndian swapping */
void iendianswapi32(int32_t *i);
void iendianswapi64(int64_t *i64);
void iendianswapi16(int16_t *i16);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IENDIAN_H_ */
