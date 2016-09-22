#ifndef _IPLANE_H_
#define _IPLANE_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

#include "foundation/math/ipos.h"
#include "foundation/math/ivec.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*************************************************************/
/* iplane                                                    */
/*************************************************************/

/*
 * A Plane in 3D Space represented in point-normal form (Ax + By + Cz = D).
 * The convention for the distance constant D is:
 * D = (A, B, C) dot (X, Y, Z) */
typedef struct iplane {
    ivec3 normal;
    ipos3 pos;
    ireal distance;
}iplane;

/* Setup Plane object given a clockwise ordering of 3D points 
 https://en.wikipedia.org/wiki/Right-hand_rule 
 normal: ab X ac */
void iplaneset(iplane *plane, const ipos3 *a, const ipos3 *b, const ipos3 *c);

/* signed distance */
ireal iplanesigneddistance(const iplane *plane, const ipos3 *p);

/* Given Z and Y, Solve for X on the plane */
ireal iplanesolveforx(iplane *plane, ireal y, ireal z);

/* Given X and Z, Solve for Y on the plane */
ireal iplanesolvefory(iplane *plane, ireal x, ireal z);

/* Given X and Y, Solve for Z on the plane */
ireal iplanesolveforz(iplane *plane, ireal x, ireal y);
    
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IPLANE_H_ */