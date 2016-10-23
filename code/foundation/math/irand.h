#ifndef _IRAND_H_
#define _IRAND_H_ 

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* George Marsaglia's The mother of all random number generators
 * ftp://ftp.forth.org/pub/C/mother.c   
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/index.html */
typedef struct irand {
    short mother1[10];
    short mother2[10];
    short mStart; /* default 1 */
} irand;

/* initialization rand struct */
void irandinit(irand *rand, unsigned long seed);
    
/* generated the rand value [0, 1] */
double irandf(irand *rand);
    
/* generated the rand value [0, 0xffffffff] */
unsigned long irandn(irand *rand);

/* generated the rand value [0, maxn] */
unsigned long irandN(irand *rand, unsigned long maxn);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /*_IRAND_H_ */
