#ifndef _IMAT_H_
#define _IMAT_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/math/ivec.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* forward declares */
union imat3;
   
/*
 * https://en.wikipedia.org/wiki/Pseudovector
 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm 
 * https://github.com/Kazade/kazmath
 
 * row-major vs column-major
 * https://fgiesen.wordpress.com/2012/02/12/row-major-vs-column-major-row-vectors-vs-column-vectors/
 *
 * Right-hand rule
 * https://en.wikipedia.org/wiki/Right-hand_rule
 * https://www.evl.uic.edu/ralph/508S98/coordinates.html
 *
 *******************************************************
 * NB!!
 * HERE WE USE THE LEFT-HANDLE-COORDINATE-SYSTEM
 *  1. the z pointer to the screen
 *  2. the rotate in clockwise
 *  3. the projection z-buffer: (z/w+1)/2
 *******************************************************
 *
 * column-major
 * col[0].x, col[1].x, col[2].x, col[3].x
 * col[0].y, col[1].y, col[2].y, col[3].y
 * col[0].z, col[1].z, col[2].z, col[3].z
 * col[0].w, col[1].w, col[2].w, col[3].w
 *
 *    A 4x4 matrix
 
 *            | 0   4   8  12 |
 *    Mat =   | 1   5   9  13 |
 *            | 2   6  10  14 |
 *            | 3   7  11  15 |
 * 
 *    __M(i, j) ==> values[i + j * 4]
 *
 *
 *    Mat4*4 (mul) mat4*1 ==> Mat4*4 (mul) Vec4
 *    Mat4*4 (mul) Vec4(x, y, z, 1) ==> (
 *          __M(0,0)*x + __M(0,1)*y + __M(0,2)*z + __M(0,3),
 *          __M(1,0)*x + __M(1,1)*y + __M(1,2)*z + __M(1,3),
 *          __M(2,0)*x + __M(2,1)*y + __M(2,2)*z + __M(3,3)
 *          )
 *
 * Z-Buffer and Projection difference between OpenGL And Direct3D
 * http://blog.csdn.net/Augusdi/article/details/20450691
 */
typedef union imat4 {
    ivec4 cols[4];
    ireal values[16];
}imat4;
   
/* the const identity */
extern const imat4 kimat4_identity;
    
/* imat4 copy */
#define __imat4_copy(dst, src) __iscaler_copy(imat4, dst, src)

/* imat4 indexing */
#define __imat4_v(m, i, j) ((m)->values[i+j*4])
    
/* iiyes, iino */
int imat4isidentity(const imat4 *mat);

/* iiyes, iino */
int imat4isequal(const imat4 *a, const imat4 *b);

/* matrix copy */
void imat4copy(__iout imat4 *dst, __iin const imat4 *src);

/* matrix operator: identify */
void imat4identity(__ioutin imat4 *mat);
/* matrix operator: inverse ; return iiyes or iino */
int imat4invert(__ioutin imat4 *mat);

/* matrix operator: transpose */
void imat4transpose(__ioutin imat4 *mat);

/* matrix operator: multiply */
void imat4multiply(__iout imat4 *mat, const imat4 *a, const imat4 *b);

/* a rotate matrix: rotate by x aixs */
void imat4rotationx(__iout imat4 *mat, ireal radians);

/* a rotate matrix: rotate by y aixs */
void imat4rotationy(__iout imat4 *mat, ireal radians);

/* a rotate matrix: rotate by z aixs */
void imat4rotationz(__iout imat4 *mat, ireal radians);

void imat4yawrollpitch(__iout imat4 *mat, ireal yaw, ireal roll, ireal pitch);

/* matrix operator: scale */
void imat4scale(__iout imat4 *mat, ireal scalex, ireal scaley, ireal scalez);

/* matrix operator: translation */
void imat4translation(__iout imat4 *mat, ireal transx, ireal transy, ireal transz);

/* extract the up vector */
void imat4upvec3(__iin imat4 *mat, __iout ivec3 *vec);

/* extract the right vector */
void imat4rightvec3(__iin imat4 *mat, __iout ivec3 *vec);

/* *************************************************************/
/* the forwrad vector: meanings point from the screen 
 * https://en.wikipedia.org/wiki/Right-hand_rule
 * * */
/* extract the forward vector in right-hand coordinate */
void imat4forwardvec3RH(__iin imat4 *mat, __iout ivec3 *vec);

/* extract the forward vector in left-hand coordinate */
void imat4forwardvec3LH(__iin imat4 *mat, __iout ivec3 *vec);

/* *************************************************************/
/* make a perspective projection */
void imat4perspectiveprojection(__iout imat4 *mat,
                                ireal fovy, ireal aspect, ireal znear, ireal zfar);

/* make a orthographic projection */
void imat4orthographicprojection(__iout imat4 *mat,
                                 ireal left, ireal right, ireal bottom, ireal top,
                                 ireal near, ireal far);

/* make a camera view matrix */
void imat4lookat(__iout imat4 *mat, const ivec3 *eye, const ivec3 *at, const ivec3 *up);
   
/* *************************************************************/
/* extract the rotate */
void imat4extractrotateimat3(__iin const imat4 *mat, __iout union imat3 * rotate);

/* extract the translation */
void imat4extracttranslationvec3(__iin const imat4 *mat, __iout ivec3 *translation);
    
/* *************************************************************/
/* transform vec3 */
void imat4transformvec3(const imat4 *mat, __ioutin ivec3 *v);
    
/* transform vec4 */
void imat4transformvec4(const imat4 *mat, __ioutin ivec4 *v);

    
/* matrix 3d
 * */
typedef union imat3 {
    ivec3 cols[3];
    ireal values[9];
}imat3;

/**/
int imat3isequal(__iin const imat3 *mat, __iin const imat3 *other);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IMAT_H_ */