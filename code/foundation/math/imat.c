#include "foundation/math/imat.h"
#include "foundation/math/imath.h"


/* imat4 copy */
#define __imat4_copy(dst, src) __iscaler_copy(imat4, dst, src)

/* imat4 indexing */
#define __imat4_v(m, i, j) ((m)->values[i+j*4])

/* iiyes, iino */
int imat4isidentity(const imat4 *mat) {
    static ireal identity [] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return (memcmp(identity, mat->values, sizeof(identity)) == 0);
}

/* iiyes, iino */
int imat4isequal(const imat4 *a, const imat4 *b) {
    int i=0;
    for (; i<16; ++i) {
        if (!ireal_equal(a->values[i], a->values[i])) {
            return iino;
        }
    }
    return iiyes;
}

/* matrix copy */
void imat4copy(__iout imat4 *dst, __iin const imat4 *src) {
    __imat4_copy(dst, src);
}

/* matrix operator: identity */
void imat4identity(__ioutin imat4 *mat) {
    memset(mat->values, 0, sizeof(imat4));
    mat->values[0] = mat->values[5] = mat->values[10] = mat->values[15] = 1.0f;
}

int imat4invert(__ioutin imat4 *mat) {
    float s[6];
    float c[6];
    float idet;
    imat4 tmp;

#define __M(i, j) __imat4_v(mat, i, j)
#define __T(i, j) __imat4_v(&tmp, i, j)
    
    s[0] = __M(0,0)*__M(1,1) - __M(1,0)*__M(0,1);
    s[1] = __M(0,0)*__M(1,2) - __M(1,0)*__M(0,2);
    s[2] = __M(0,0)*__M(1,3) - __M(1,0)*__M(0,3);
    s[3] = __M(0,1)*__M(1,2) - __M(1,1)*__M(0,2);
    s[4] = __M(0,1)*__M(1,3) - __M(1,1)*__M(0,3);
    s[5] = __M(0,2)*__M(1,3) - __M(1,2)*__M(0,3);
    
    c[0] = __M(2,0)*__M(3,1) - __M(3,0)*__M(2,1);
    c[1] = __M(2,0)*__M(3,2) - __M(3,0)*__M(2,2);
    c[2] = __M(2,0)*__M(3,3) - __M(3,0)*__M(2,3);
    c[3] = __M(2,1)*__M(3,2) - __M(3,1)*__M(2,2);
    c[4] = __M(2,1)*__M(3,3) - __M(3,1)*__M(2,3);
    c[5] = __M(2,2)*__M(3,3) - __M(3,2)*__M(2,3);
    
    /* Assumes it is invertible */
    idet = ( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );
    if (ireal_equal_zero(idet)) {
        return iino;
    }
    idet = 1.0f/idet;
    
    __T(0,0) = ( __M(1,1) * c[5] - __M(1,2) * c[4] + __M(1,3) * c[3]) * idet;
    __T(0,1) = (-__M(0,1) * c[5] + __M(0,2) * c[4] - __M(0,3) * c[3]) * idet;
    __T(0,2) = ( __M(3,1) * s[5] - __M(3,2) * s[4] + __M(3,3) * s[3]) * idet;
    __T(0,3) = (-__M(2,1) * s[5] + __M(2,2) * s[4] - __M(2,3) * s[3]) * idet;
    
    __T(1,0) = (-__M(1,0) * c[5] + __M(1,2) * c[2] - __M(1,3) * c[1]) * idet;
    __T(1,1) = ( __M(0,0) * c[5] - __M(0,2) * c[2] + __M(0,3) * c[1]) * idet;
    __T(1,2) = (-__M(3,0) * s[5] + __M(3,2) * s[2] - __M(3,3) * s[1]) * idet;
    __T(1,3) = ( __M(2,0) * s[5] - __M(2,2) * s[2] + __M(2,3) * s[1]) * idet;
    
    __T(2,0) = ( __M(1,0) * c[4] - __M(1,1) * c[2] + __M(1,3) * c[0]) * idet;
    __T(2,1) = (-__M(0,0) * c[4] + __M(0,1) * c[2] - __M(0,3) * c[0]) * idet;
    __T(2,2) = ( __M(3,0) * s[4] - __M(3,1) * s[2] + __M(3,3) * s[0]) * idet;
    __T(2,3) = (-__M(2,0) * s[4] + __M(2,1) * s[2] - __M(2,3) * s[0]) * idet;
    
    __T(3,0) = (-__M(1,0) * c[3] + __M(1,1) * c[1] - __M(1,2) * c[0]) * idet;
    __T(3,1) = ( __M(0,0) * c[3] - __M(0,1) * c[1] + __M(0,2) * c[0]) * idet;
    __T(3,2) = (-__M(3,0) * s[3] + __M(3,1) * s[1] - __M(3,2) * s[0]) * idet;
    __T(3,3) = ( __M(2,0) * s[3] - __M(2,1) * s[1] + __M(2,2) * s[0]) * idet;
    
    __imat4_copy(mat, &tmp);
    return iiyes;
}

/* matrix operator: transpose */
void imat4transpose(__ioutin imat4 *mat) {
    int x, z;
    imat4 tmp;
    
    for (z = 0; z < 4; ++z) {
        for (x = 0; x < 4; ++x) {
            tmp.values[(z * 4) + x] = mat->values[(x * 4) + z];
        }
    }
    __imat4_copy(mat, &tmp);
}

/* matrix operator: multiply */
void imat4multiply(__iout imat4 *mat, const imat4 *a, const imat4 *b) {
    imat4 tmp;
    int k, r, c;
    
    for(c=0; c<4; ++c) for(r=0; r<4; ++r) {
        __imat4_v(&tmp, r, c) = 0.f;
        for(k=0; k<4; ++k) {
            __imat4_v(&tmp, r, c) += __imat4_v(a, r, k) * __imat4_v(b, k, c);
        }
    }
    __imat4_copy(mat, &tmp);
}

/* Matrix Rotation https://en.wikipedia.org/wiki/Rotation_matrix */

/* a rotate matrix: rotate by x aixs */
void imat4rotationx(__iout imat4 *mat, ireal radians) {
    ireal s = sinf(radians);
    ireal c = cosf(radians);
    imat4 R = {{
        {{1.f, 0.f, 0.f, 0.f}},
        {{0.f,   c,   s, 0.f}},
        {{0.f,  -s,   c, 0.f}},
        {{0.f, 0.f, 0.f, 1.f}}
    }};
    imat4multiply(mat, &R, mat);
}

/* a rotate matrix: rotate by y aixs */
void imat4rotationy(__iout imat4 *mat, ireal radians) {
    ireal s = sinf(radians);
    ireal c = cosf(radians);
    imat4 R = {{
        {{   c, 0.f,  -s, 0.f}},
        {{ 0.f, 1.f, 0.f, 0.f}},
        {{   s, 0.f,   c, 0.f}},
        {{ 0.f, 0.f, 0.f, 1.f}}
    }};
    imat4multiply(mat, &R, mat);
}

/* a rotate matrix: rotate by z aixs */
void imat4rotationz(__iout imat4 *mat, ireal radians) {
    ireal s = sinf(radians);
    ireal c = cosf(radians);
    imat4 R = {{
        {{   c,   s, 0.f, 0.f}},
        {{  -s,   c, 0.f, 0.f}},
        {{ 0.f, 0.f, 1.f, 0.f}},
        {{ 0.f, 0.f, 0.f, 1.f}}
    }};
    imat4multiply(mat, &R, mat);
}

void imat4yawrollpitch(__iout imat4 *mat, ireal yaw, ireal roll, ireal pitch) {
    imat4 yawmat, rollmat, pitchmat;
    /* y axis : yaw */
    imat4rotationy(&yawmat, yaw);
    /* z axis : roll */
    imat4rotationy(&rollmat, roll);
    /* x axis : pitch */
    imat4rotationy(&pitchmat, pitch);
    
    imat4multiply(mat, &yawmat, &rollmat);
    imat4multiply(mat, mat, &pitchmat);
}

/* matrix operator: scale */
void imat4scale(__iout imat4 *mat, ireal sx, ireal sy, ireal sz) {
    imat4 S = {{
        {{ sx,  0.f, 0.f, 0.f}},
        {{0.f,   sy, 0.f, 0.f}},
        {{0.f,  0.f,  sz, 0.f}},
        {{0.f,  0.f, 0.f, 1.f}}
    }};
    __imat4_copy(mat, &S);
}

/* matrix operator: translation */
void imat4translation(__iout imat4 *mat, ireal tx, ireal ty, ireal tz) {
    imat4 T = {{
        {{1.f,  0.f,  0.f, 0.f}},
        {{0.f,  1.f,  0.f, 0.f}},
        {{0.f,  0.f,  1.f, 0.f}},
        {{ tx,   ty,   tz, 1.f}}
    }};
    __imat4_copy(mat, &T);
}

/* extract the up vector */
void imat4upvec3(__iin imat4 *mat, __iout ivec3 *vec) {
    ivec3 v = kivec3_axis_y;
    imat4transformvec3(mat, &v);
    v = ivec3normalize(&v);
    __iscaler_copy(ivec3, vec, &v);
}

/* extract the right vector */
void imat4rightvec3(__iin imat4 *mat, __iout ivec3 *vec) {
    ivec3 v = kivec3_axis_x;
    imat4transformvec3(mat, &v);
    v = ivec3normalize(&v);
    __iscaler_copy(ivec3, vec, &v);
}

/* extract the forward vector in right-hand coordinate */
void imat4forwardvec3RH(__iin imat4 *mat, __iout ivec3 *vec) {
    ivec3 v = kivec3_axis_neg_z;
    imat4transformvec3(mat, &v);
    v = ivec3normalize(&v);
    __iscaler_copy(ivec3, vec, &v);
}

/* extract the forward vector in left-hand coordinate */
void imat4forwardvec3LH(__iin imat4 *mat, __iout ivec4 *vec) {
    ivec3 v = kivec3_axis_z;
    imat4transformvec3(mat, &v);
    v = ivec3normalize(&v);
    __iscaler_copy(ivec3, vec, &v);
}

/* make a perspective projection */
void imat4perspectiveprojection(__iout imat4 *mat,
                                ireal fovy, ireal aspect, ireal znear, ireal zfar) {
    ireal r = idegreestoradians(fovy / 2);
    ireal deltaZ = zfar - znear;
    ireal s = sin(r);
    ireal cotangent = 0;
    
    if (deltaZ == 0 || s == 0 || aspect == 0) {
        return ;
    }
    
    /*cos(r) / sin(r) = cot(r)*/
    cotangent = cos(r) / s;
    
    imat4identity(mat);
    __M(0, 0) = cotangent / aspect;
    __M(1, 1) = cotangent;
    __M(2, 2) = -(zfar + znear) / deltaZ;
    __M(3, 2) = -1.f;
    __M(2, 3) = -2 * znear * zfar / deltaZ;
    __M(3, 3) = 0.f;
}

/* make a orthographic projection */
void imat4orthographicprojection(__iout imat4 *mat,
                                 ireal left, ireal right, ireal bottom, ireal top,
                                 ireal near, ireal far) {
    ireal tx = -((right + left) / (right - left));
    ireal ty = -((top + bottom) / (top - bottom));
    ireal tz = -((far + near) / (far - near));
    
    imat4identity(mat);
    __M(0, 0) = 2 / (right - left);
    __M(1, 1) = 2 / (top - bottom);
    __M(2, 2) = -2 / (far - near);
    __M(0, 3) = tx;
    __M(1, 3) = ty;
    __M(2, 3) = tz;
}

/* make a camera view matrix */
/* https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml 
 * https://www.opengl.org/wiki/GluLookAt_code */
void imat4lookat(__iout imat4 *mat, const ivec3 *eye, const ivec3 *at, const ivec3 *up) {
    ivec3 f, s, u;
    
    f = ivec3subtract(at, eye);
    f = ivec3normalize(&f);
    
    s = ivec3cross(&f, up);
    s = ivec3normalize(&s);
    
    u = ivec3cross(&s, &f);
    
    __M(0, 0) = s.v.x;
    __M(1, 0) = u.v.x;
    __M(2, 0) = -f.v.x;
    __M(3, 0) = 0.f;
    
    __M(0, 1) = s.v.y;
    __M(1, 1) = u.v.y;
    __M(2, 1) = -f.v.y;
    __M(3, 1) = 0.f;
    
    __M(0, 2) = s.v.z;
    __M(1, 2) = u.v.z;
    __M(2, 2) = -f.v.z;
    __M(3, 2) = 0.f;
    
    __M(0, 3) = -ivec3dot(&s, eye);
    __M(1, 3) = -ivec3dot(&u, eye);
    __M(2, 3) = ivec3dot(&f, eye);
    __M(3, 3) = 1.f;
}

/* make rotation with axis and angle */
void imat4rotationaxisangle(__iout imat4 *mat, const ivec3 *axis, ireal radians) {
    
}

/* extract the rotate */
void imat4extractrotateimat3(__iin imat4 *mat, __iout union imat3 * rotate) {
    
#define __M_n(a, n, i, j) (a)->values[i + j * n]
#define __M_3(a, i, j) __M_n(a, 3, i, j)
#define __M_4(a, i, j) __M_n(a, 4, i, j)
    
    __M_3(rotate, 0, 0) = __M_4(mat, 0, 0);
    __M_3(rotate, 1, 0) = __M_4(mat, 1, 0);
    __M_3(rotate, 2, 0) = __M_4(mat, 2, 0);
    
    __M_3(rotate, 0, 1) = __M_4(mat, 0, 1);
    __M_3(rotate, 1, 1) = __M_4(mat, 1, 1);
    __M_3(rotate, 2, 1) = __M_4(mat, 2, 1);
    
    __M_3(rotate, 0, 2) = __M_4(mat, 0, 2);
    __M_3(rotate, 1, 2) = __M_4(mat, 1, 2);
    __M_3(rotate, 2, 2) = __M_4(mat, 2, 2);
}

/* extract the translation */
void imat4extracttranslationvec3(__iin imat4 *mat, __iout ivec3 *translation) {
    translation->v.x = __M(0, 3);
    translation->v.y = __M(1, 3);
    translation->v.z = __M(2, 3);
}

/* transform vec3 */
void imat4transformvec3(const imat4 *mat, __ioutin ivec3 *v) {
    ivec3 tmp;
    int i=0;
    for (; i<3; ++i) {
        tmp.values[i] = __M(0, i) * v->values[i]
        + __M(1, i) * v->values[i]
        + __M(2, i) * v->values[i];
    }
}

/* transform vec4 */
void imat4transformvec4(const imat4 *mat, __ioutin ivec4 *v) {
    ivec3 tmp;
    int i=0;
    for (; i<4; ++i) {
        tmp.values[i] = __M(0, i) * v->values[i]
        + __M(1, i) * v->values[i]
        + __M(2, i) * v->values[i]
        + __M(3, i) * v->values[i];
    }
}
