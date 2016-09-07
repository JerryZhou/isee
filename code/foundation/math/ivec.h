#ifndef _IVEC_H_
#define _IVEC_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/math/ipos.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*************************************************************/
/* ivec2                                                     */
/*************************************************************/

/* vector,  match-operators:
 *  add ; sub ; mul ; dot; len
 * */
typedef union ivec2 {
    ireal values[2];
    struct {
        ireal x, y;
    } v;
}ivec2;

/* const useful vectors  */
extern const ivec2 kivec2_zero;
extern const ivec2 kivec2_axis_x;
extern const ivec2 kivec2_axis_y;
extern const ivec2 kivec2_axis_xy;

/* ipos2 ==> ivec2 */
ivec2 ivec2subtractpoint(const struct ipos *p0, const struct ipos *p1);

/* move dir the dist */
ipos ivec2movepoint(const ivec2 *dir, ireal dist, const ipos *p);

/* add */
ivec2 ivec2add(const ivec2 *l, const ivec2 *r);

/* sub */
ivec2 ivec2subtract(const ivec2 *l, const ivec2 *r);

/* mul */
ivec2 ivec2multipy(const ivec2 *l, const ireal a);

/* dot */
ireal ivec2dot(const ivec2 *l, const ivec2 *r);

/* lengthsqr */
ireal ivec2lengthsqr(const ivec2 *l);

/* len */
ireal ivec2length(const ivec2 *l);

/* abs */
ivec2 ivec2abs(const ivec2* l);

/* normalize */
ivec2 ivec2normalize(const ivec2 *l);

/* parallel, besure r have been normalized */
ivec2 ivec2parallel(const ivec2 *l, const ivec2 *r);

/* perpendicular, besure r have been normalized */
ivec2 ivec2perpendicular(const ivec2 *l, const ivec2 *r);

/*************************************************************/
/* ivec3                                                     */
/*************************************************************/

/* math-operators:
 * add ; sub ; mul ; dot; cross, len
 */
typedef union ivec3 {
    ireal values[3];
    struct {
        ireal x, y, z;
    }v;
}ivec3;

/* extern const */
extern const ivec3 kivec3_axis_x;
extern const ivec3 kivec3_axis_y;
extern const ivec3 kivec3_axis_z;
extern const ivec3 kivec3_axis_neg_z;
extern const ivec3 kivec3_zero;

/* almost equal */
int ivec3isequal(const ivec3 *l, const ivec3 *r);
    
/* move dir the dist */
ipos3 ivec3movepoint(const ivec3 *dir, ireal dist, const ipos3 *p);
    
/* ipos3 ==> ivec3 */
ivec3 ivec3subtractpoint(const struct ipos3 *p0, const struct ipos3 *p1);

/* add */
ivec3 ivec3add(const ivec3 *l, const ivec3 *r);

/* sub */
ivec3 ivec3subtract(const ivec3 *l, const ivec3 *r);

/* mul */
ivec3 ivec3scale(const ivec3 *l, const ireal a);

/* dot */
ireal ivec3dot(const ivec3 *l, const ivec3 *r);

/* cross */
ivec3 ivec3cross(const ivec3 *l, const ivec3 *r);

/* length square */
ireal ivec3lengthsqr(const ivec3 *l);

/* length */
ireal ivec3length(const ivec3 *l);

/* abs */
ivec3 ivec3abs(const ivec3* l);

/* normalized */
ivec3 ivec3normalize(const ivec3 *l);

/* parallel, besure r have been normalized */
ivec3 ivec3parallel(const ivec3 *l, const ivec3 *r);

/* perpendicular, besure r have been normalized */
ivec3 ivec3perpendicular(const ivec3 *l, const ivec3 *r);
    
/*************************************************************/
/* ivec4                                                     */
/*************************************************************/
typedef union ivec4 {
    ireal values[4];
    struct {
        ireal x, y, z, w;
    }v;
}ivec4;
    
/* scaler type copy */
#define __iscaler_copy(type, dst, src) memcpy((dst)->values, (src)->values, sizeof(type))
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /*_IVEC_H_ */