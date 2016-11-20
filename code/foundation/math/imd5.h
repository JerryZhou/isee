#ifndef _IMD5_H_
#define _IMD5_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* the md5 calc */
typedef struct imd5 {
    irefdeclare;
    
    uint32_t s[4];
    uint8_t x[64];
    int nx;
    uint64_t len;
} imd5;
    
/**/
void imd5reset(imd5 *);
/**/
void imd5write(imd5 *, unsigned char *, size_t);
/**/
uint64_t imd5sum(imd5 *);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IMD5_H_ */
