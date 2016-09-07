#include "foundation/math/ivec.h"

/* move point */
ipos ivec2movepoint(const ivec2 *dir, ireal dist, const ipos *p) {
    ipos to = *p;
    to.x += dir->v.x * dist;
    to.y += dir->v.y * dist;
    return to;
}

/* sub */
ivec2 ivec2subtractpoint(const ipos *p0, const ipos *p1) {
    ivec2 vec;
    vec.v.x = p0->x - p1->x;
    vec.v.y = p0->y - p1->y;
    return vec;
}

/* dot */
ireal ivec2dot(const ivec2 *l, const ivec2 *r) {
    icheckret(l, 0);
    icheckret(r, 0);
    return l->v.x * r->v.x + l->v.y * r->v.y;
}

/* sub */
ivec2 ivec2subtract(const ivec2 *l, const ivec2 *r) {
    ivec2 vec;
    vec.v.x = r->v.x - l->v.x;
    vec.v.y = r->v.y - l->v.y;
    return vec;
}

/* add */
ivec2 ivec2add(const ivec2 *l, const ivec2 *r) {
    ivec2 vec;
    vec.v.x = r->v.x + l->v.x;
    vec.v.y = r->v.y + l->v.y;
    return vec;
}

/* mul */
ivec2 ivec2multipy(const ivec2 *l, const ireal a) {
    ivec2 vec;
    vec.v.x = l->v.x * a;
    vec.v.y = l->v.y * a;
    return vec;
}

/* abs */
ivec2 ivec2abs(const ivec2* l) {
    ivec2 vec;
    vec.v.x = fabs(l->v.x);
    vec.v.y = fabs(l->v.y);
    return vec;
}

/* normalized */
ivec2 ivec2normalize(const ivec2 *l) {
    ireal len = ivec2length(l);
    return len > 0 ? ivec2multipy(l, 1.0/len) : *l;
}

/* length sqr */
ireal ivec2lengthsqr(const ivec2 *l) {
    return ivec2dot(l, l);
}

/* length */
ireal ivec2length(const ivec2 *l) {
    return sqrtf(ivec2dot(l, l));
}

/* parallel */
ivec2 ivec2parallel(const ivec2 *l, const ivec2 *r) {
    ireal projection = ivec2dot (l, r);
    return ivec2multipy(r, projection);
}

/* perpendicular */
ivec2 ivec2perpendicular(const ivec2 *l, const ivec2 *r) {
    ivec2 p = ivec2parallel(l, r);
    return ivec2subtract(l, &p);
}

/*************************************************************/
/* ivec3                                                     */
/*************************************************************/

/* extern const */
const ivec3 kVec3_Axis_X = {{1.f, 0.f, 0.f}};
const ivec3 kVec3_Axis_Y = {{0.f, 1.f, 0.f}};
const ivec3 kVec3_Axis_Z = {{0.f, 0.f, 1.f}};
const ivec3 kVec3_Axis_Neg_Z = {{0.f, 0.f, -1.f}};
const ivec3 kVec3_Zero = {{0.f, 0.f, 0.f}};

/* almost equal */
int ivec3isequal(const ivec3 *l, const ivec3 *r) {
    return ireal_equal(l->values[0], r->values[0]) &&
        ireal_equal(l->values[1], r->values[1]) &&
        ireal_equal(l->values[2], r->values[2]);
}

/* move dir the dist */
ipos3 ivec3movepoint(const ivec3 *dir, ireal dist, const ipos3 *p) {
    ipos3 to = *p;
    to.x += dir->v.x * dist;
    to.y += dir->v.y * dist;
    to.z += dir->v.z * dist;
    return to;
}

/* sub point */
ivec3 ivec3subtractpoint(const ipos3 *p0, const ipos3 *p1) {
    ivec3 v;
    v.v.x = p0->x - p1->x;
    v.v.y = p0->y - p1->y;
    v.v.z = p0->z - p1->z;
    return v;
}

/* vector add */
ivec3 ivec3add(const ivec3 *l, const ivec3 *r) {
    ivec3 vec;
    vec.v.x = r->v.x + l->v.x;
    vec.v.y = r->v.y + l->v.y;
    vec.v.z = r->v.z + l->v.z;
    return vec;
}

/* vector sub */
ivec3 ivec3subtract(const ivec3 *l, const ivec3 *r) {
    ivec3 vec;
    vec.v.x = r->v.x - l->v.x;
    vec.v.y = r->v.y - l->v.y;
    vec.v.z = r->v.z - l->v.z;
    return vec;
}

/* mul */
ivec3 ivec3scale(const ivec3 *l, ireal a) {
    ivec3 vec;
    vec.v.x = l->v.x * a;
    vec.v.y = l->v.y * a;
    vec.v.z = l->v.z * a;
    return vec;
}

/* dot
 * https://en.wikipedia.org/wiki/Dot_product
 * */
ireal ivec3dot(const ivec3 *l, const ivec3 *r) {
    return l->v.x * r->v.x
    + l->v.y * r->v.y
    + l->v.z * r->v.z;
}

/* cross
 * https://en.wikipedia.org/wiki/Cross_product
 * */
ivec3 ivec3cross(const ivec3 *l, const ivec3 *r) {
    ivec3 vec;
    vec.v.x = l->v.y * r->v.z - l->v.z * r->v.y;
    vec.v.y = l->v.z * r->v.x - l->v.x * r->v.z;
    vec.v.z = l->v.x * r->v.y - l->v.y * r->v.x;
    return vec;
}

/* length sqr */
ireal ivec3lengthsqr(const ivec3 *l) {
    return ivec3dot(l, l);
}

/* length */
ireal ivec3length(const ivec3 *l) {
    return sqrtf(ivec3dot(l, l));
}

/* abs */
ivec3 ivec3abs(const ivec3* l) {
    ivec3 vec;
    vec.v.x = fabs(l->v.x);
    vec.v.y = fabs(l->v.y);
    vec.v.z = fabs(l->v.z);
    return vec;
}

/* normalized */
ivec3 ivec3normalize(const ivec3 *l) {
    ireal len = ivec3length(l);
    return len > 0 ? ivec3scale(l, 1.0/len) : *l;
}

/* parallel */
ivec3 ivec3parallel(const ivec3 *l, const ivec3 *r) {
    ireal projection = ivec3dot (l, r);
    return ivec3scale(r, projection);
}

/* perpendicular */
ivec3 ivec3perpendicular(const ivec3 *l, const ivec3 *r) {
    ivec3 p = ivec3parallel(l, r);
    return ivec3subtract(l, &p);
}

