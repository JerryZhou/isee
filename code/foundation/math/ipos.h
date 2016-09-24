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
typedef struct ipos2 {
    ireal x, y;
}ipos2;

/* make type-def ipos2 */
typedef ipos2 ipos;

/* zero point */
extern const ipos2 kipos_zero;
extern const ipos2 kipos_x;
extern const ipos2 kipos_y;
extern const ipos2 kipos_xy;

/* distance pow 2 */
ireal idistancepow2(const ipos2 *p, const ipos2 *t);
    
/* almost equal */
int ipos2isequal(const ipos2 *l, const ipos2 *r);

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
    
/* almost equal */
int ipos3isequal(const ipos3 *l, const ipos3 *r);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif