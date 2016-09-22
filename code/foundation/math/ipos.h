#ifndef _IPOS_H_
#define _IPOS_H_

#include "foundation/itype.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*************************************************************/
/* ipos2                                                      */
/*************************************************************/
typedef struct ipos {
    ireal x, y;
}ipos;

/* zero point */
extern const ipos kipos_zero;
extern const ipos kipos_x;
extern const ipos kipos_y;
extern const ipos kipos_xy;

/* distance pow 2 */
ireal idistancepow2(const ipos *p, const ipos *t);

/*************************************************************/
/* ipos3                                                      */
/*************************************************************/
typedef struct ipos3 {
    ireal x, y, z;
}ipos3;

/* zero of ipos3 */
extern const ipos3 kipos3_zero;
extern const ipos3 kipos3_x;
extern const ipos3 kipos3_y;
extern const ipos3 kipos3_z;
extern const ipos3 kipos3_xz;

/* distance pow2 */
ireal idistancepow3(const ipos3 *p, const ipos3 *t);

/* get the xy from the p with xz */
void ipos3takexz(const ipos3 *p, ipos *to);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif