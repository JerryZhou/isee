#ifndef _IMATH_H_
#define _IMATH_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* matrix and quaternion aticles 
 * http://www.j3d.org/matrix_faq/matrfaq_latest.html */
    
/* mathmatics consts */
#define __iPI 3.14159265358979323846f
#define __iPIOver180  (__iPI / 180.0f)
#define __iPIUnder180 (180.0 / __iPI)   
    
/* square */
ireal iSQR(ireal v);
/* degrees to randians */
ireal idegreestoradians(ireal degrees);
/* randians to degrees */
ireal irandianstodegrees(ireal randians);
/* clamp the value to [min max] */
ireal iclamp(ireal v, ireal min, ireal max);
/* lerp the x and y ==> (x * (1-t) + y * t) ==> (x + (y-x) * t )*/
ireal ilerp(ireal x, ireal y, ireal t);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IMATH_H_ */
