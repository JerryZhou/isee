#ifndef _IQUAT_H_
#define _IQUAT_H_ 

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/math/ivec.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* forward declares */
union imat3;
union imat4;
    
/* quat vec4 */
/* q = [qv, qs] = [a*sin(ø/2), cons(ø/2)]
 * the rotate axis normalized vector
 * ø is the roated angle
 * */
typedef ivec4 iquat;

/* quat indentity */
extern const iquat kiquat_identity;

/* quaternion: is equal */
int iquatisequal(__iin const iquat *a, __iin const iquat *b);
/* quaternion: is identity */
int iquatisidentity(__iin const iquat *quat);

/* quaternion: exp */
void iquatexp(__iout iquat *quat, __iin const iquat *q);
/* quaternion: ln */
void iquatln(__iout iquat *quat, __iin const iquat *q);


/* quaternion: identity */
void iquatidentity(__ioutin iquat *quat);
/* quaternion: invert */
void iquatinvert(__ioutin iquat *quat);
/* quaternion: dot */
ireal iquatdot(__iin const iquat *a, __iin const iquat *b);

/* quaternion: length */
ireal iquatlength(__iin const iquat *quat);

/* quaternion: length square */
ireal iquatlengthsqr(__iin const iquat *quat);

/* quaternion: multiply */
void iquatmultipy(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2);
/* quaternion: normalize */
void iquatnormalize(__ioutin iquat *quat);

/* make a quaternion by axis and degree */
void iquatrotateaxisangle(__iout iquat *quat, const ivec3 *axis, const ireal radians);

/* quaternion slerp with t; q1 + (q2-q1) * t */
void iquatslerp(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2, ireal t);

/* extract the quaternion's axis and rotating angle */
void iquatextractaxisangle(__iin const iquat *quat, __iout ivec3 *axis, __iout ireal *radians);

/* extract the quaternion's angle by rotating axis */
void iquatextractrotatearoundaxis(__iin const iquat *quat, __iin const ivec3 *axis, __iout iquat *q);


/* quaternion: scale */
void iquatscale(__iout iquat *quat, __iin const iquat *q, __iin ireal scale);
/* quaternion: copy */
void iquatassign(__iout iquat *quat, __iin const iquat *q);
/* quaternion: add */
void iquatadd(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2);
/* quaternion: subtract */
void iquatsubtract(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2);

/* quaternion: multiply with a vec3*/
void iquatmultipyvec3(__iout ivec3 *vout, __iin const iquat *q, __iin const ivec3 *v);

/* quaternion: rotating between */
void iquatrotatebetweenvec3(__iout iquat *quat,
                            __iin const ivec3 *v1,
                            __iin const ivec3 *v2,
                            __iin const ivec3 *fallback);
/* quaternion: between */
void iquatbetweenvec3(__iout iquat *quat, __iin const ivec3 *v1, __iin const ivec3 *v2);

/* the rotating of behavior */
void iquatlookrotate(__iout iquat *quat, __iin const ivec3 *direction, __iin const ivec3 *up);
    
/* make a quaternion from roate matrix */
void iquatfromrotatemat3(__iout iquat *quat, __iin const union imat3 *rot);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IQUAT_H_ */
