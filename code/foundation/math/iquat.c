#include "foundation/math/iquat.h"
#include "foundation/math/imath.h"
#include "foundation/math/imat.h"

#define __iquat_fill(q, x, y, z, w) \
    (q)->values[0] = x; (q)->values[1] = y; (q)->values[2] = z; (q)->values[3] = w

/* quaternion: is equal */
int iquatisequal(__iin const iquat *a, __iin const iquat *b) {
    icheckret(a!=b, iiyes);
    if ( ireal_equal(a->values[0], b->values[0]) &&
        ireal_equal(a->values[1], b->values[1]) &&
        ireal_equal(a->values[2], b->values[2]) &&
        ireal_equal(a->values[3], b->values[3]) ) {
        return iiyes;
    }
    return iino;
}

/* quaternion: is identity */
int iquatisidentity(__iin const iquat *quat) {
    return quat->values[3] == 1.f &&
        quat->values[2] == 0.f &&
        quat->values[1] == 0.f &&
        quat->values[0] == 0.f;
}

/* quaternion: exp */
void iquatexp(__iout iquat *quat, __iin const iquat *q) {
    /*todos:*/
}
/* quaternion: ln */
void iquatln(__iout iquat *quat, __iin const iquat *q) {
    /*todos:*/
    /*
     A unit quaternion, is defined by:
     Q == (cos(theta), sin(theta) * v) where |v| = 1
     The natural logarithm of Q is, ln(Q) = (0, theta * v) */
}

/* quaternion: identity */
void iquatidentity(__ioutin iquat *quat) {
    quat->values[0] = quat->values[1] = quat->values[2] = 0.f;
    quat->values[3] = 1.f;
}
/* quaternion: inverse */
void iquatinverse(__ioutin iquat *quat) {
    ireal l = iquatlength(quat);
    
    if (ireal_less(l, iepsilon)) {
        quat->values[0]=quat->values[1]=quat->values[2]=quat->values[3] = 0.f;
        return;
    }
    quat->v.x = -quat->v.x;
    quat->v.y = -quat->v.y;
    quat->v.z = -quat->v.z;
    quat->v.w = -quat->v.w;
}
/* quaternion: dot */
ireal iquatdot(__iin const iquat *q1, __iin const iquat *q2) {
    /* A dot B = B dot A = AtBt + AxBx + AyBy + AzBz */
    
    return (q1->v.w * q2->v.w +
            q1->v.x * q2->v.x +
            q1->v.y * q2->v.y +
            q1->v.z * q2->v.z);
}

/* quaternion: length */
ireal iquatlength(__iin const iquat *quat) {
    return sqrtf(iquatlengthsqr(quat));
}

/* quaternion: length square */
ireal iquatlengthsqr(__iin const iquat *quat) {
    return iquatdot(quat, quat);
}

/* quaternion: multiply */
void iquatmultipy(__iout iquat *quat, __iin const iquat *qu1, __iin const iquat *qu2) {
    iquat* q1 = NULL;
    iquat* q2 = NULL;
    iquat tmp1, tmp2;
    iquatassign(&tmp1, qu1);
    iquatassign(&tmp2, qu2);
    
    /*Just aliasing*/
    q1 = &tmp1;
    q2 = &tmp2;
    
    quat->v.x = q1->v.w * q2->v.x + q1->v.x * q2->v.w + q1->v.y * q2->v.z - q1->v.z * q2->v.y;
    quat->v.y = q1->v.w * q2->v.y + q1->v.y * q2->v.w + q1->v.z * q2->v.x - q1->v.x * q2->v.z;
    quat->v.z = q1->v.w * q2->v.z + q1->v.z * q2->v.w + q1->v.x * q2->v.y - q1->v.y * q2->v.x;
    quat->v.w = q1->v.w * q2->v.w - q1->v.x * q2->v.x - q1->v.y * q2->v.y - q1->v.z * q2->v.z;
}

/* quaternion: normalize */
void iquatnormalize(__ioutin iquat *quat) {
    ireal length = iquatlength(quat);
    
    if (fabs(length) < iepsilon) {
        quat->v.x = 0.0;
        quat->v.y = 0.0;
        quat->v.z = 0.0;
        quat->v.w = 0.0;
        return;
    }
    
    quat->v.x = quat->v.x / length;
    quat->v.y = quat->v.y / length;
    quat->v.z = quat->v.z / length;
    quat->v.w = quat->v.w / length;
}

/* make a quaternion by axis and degree */
void iquatrotateaxisangle(__iout iquat *quat, const ivec3 *axis, const ireal radians) {
    ireal rad = radians * 0.5f;
    ireal scale	= sinf(rad);
    
    quat->v.x = axis->v.x * scale;
    quat->v.y = axis->v.y * scale;
    quat->v.z = axis->v.z * scale;
    quat->v.w = cosf(rad);
    
    iquatnormalize(quat);
}

/* quaternion slerp with t; q1 + (q2-q1) * t */
void iquatslerp(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2, ireal t) {
    iquat tmp;
    iquat t1, t2;
    ireal theta_0;
    ireal theta;
    
    ireal dot = iquatdot(q1, q2);
    const double DOT_THRESHOLD = 0.9995;
    
    if (dot > DOT_THRESHOLD) {
        iquat diff;
        iquatsubtract(&diff, q2, q1);
        iquatscale(&diff, &diff, t);
        
        iquatadd(quat, q1, &diff);
        iquatnormalize(quat);
        return;
    }
    
    dot = iclamp(dot, -1, 1);
    
    theta_0 = acos(dot);
    theta = theta_0 * t;
    
    iquatscale(&tmp, q1, dot);
    iquatsubtract(&tmp, q2, &tmp);
    iquatnormalize(&tmp);
    
    iquatscale(&t1, q1, cos(theta));
    iquatscale(&t2, &tmp, sin(theta));
    
    iquatadd(quat, &t1, &t2);
}

/* extract the quaternion's axis and rotating angle */
void iquatextractaxisangle(__iin const iquat *quat, __iout ivec3 *axis, __iout ireal *radians) {
    ireal	scale;			/* temp vars*/
    iquat tmp;
    iquat norq;
    
    if(quat->v.w > 1.0) {
        iquatassign(&norq, quat);
        iquatnormalize(&norq);
    } else {
        iquatassign(&norq, quat);
    }
    
    *radians = 2.0 * acosf(tmp.v.w);
    scale = sqrtf(1.0 - iSQR(tmp.v.w));
    
    if (scale < iepsilon) {	/* angle is 0 or 360 so just simply set axis to 0,0,1 with angle 0*/
        axis->v.x = 0.0f;
        axis->v.y = 0.0f;
        axis->v.z = 1.0f;
    } else {
        axis->v.x = tmp.v.x / scale;
        axis->v.y = tmp.v.y / scale;
        axis->v.z = tmp.v.z / scale;
        ivec3normalize(axis);
    }
}

/* extract the quaternion's angle by rotating axis */
void iquatextractrotatearoundaxis(__iin const iquat *quat, __iin const ivec3 *axis, __iout iquat *q) {
    /**
     Given a quaternion, and an axis. This extracts the rotation around the axis into pOut as another quaternion.
     Uses the swing-twist decomposition.
     
     http://stackoverflow.com/questions/3684269/component-of-a-quaternion-rotation-around-an-axis/22401169?noredirect=1#comment34098058_22401169
     */
    
    ireal d;
    ivec3 ra = {{quat->v.x, quat->v.y, quat->v.z}};
    
    d = ivec3dot(&ra, axis);
    
    q->values[0] = axis->values[0] * d;
    q->values[1] = axis->values[1] * d;
    q->values[2] = axis->values[2] * d;
    iquatnormalize(q);
}

/* quaternion: scale */
void iquatscale(__iout iquat *quat, __iin const iquat *q, __iin ireal scale) {
    quat->values[0] = q->values[0] * scale;
    quat->values[1] = q->values[1] * scale;
    quat->values[2] = q->values[2] * scale;
    quat->values[3] = q->values[3] * scale;
}
/* quaternion: copy */
void iquatassign(__iout iquat *quat, __iin const iquat *q) {
    __iscaler_copy(iquat, quat, q);
}
/* quaternion: add */
void iquatadd(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2) {
    quat->values[0] = q1->values[0] + q2->values[0];
    quat->values[1] = q1->values[1] + q2->values[1];
    quat->values[2] = q1->values[2] + q2->values[2];
    quat->values[3] = q1->values[3] + q2->values[3];
}
/* quaternion: subtract */
void iquatsubtract(__iout iquat *quat, __iin const iquat *q1, __iin const iquat *q2) {
    quat->values[0] = q1->values[0] - q2->values[0];
    quat->values[1] = q1->values[1] - q2->values[1];
    quat->values[2] = q1->values[2] - q2->values[2];
    quat->values[3] = q1->values[3] - q2->values[3];
}

/* quaternion: multiply with a vec3*/
void iquatmultipyvec3(__iout ivec3 *vout, __iin const iquat *q, __iin const ivec3 *v) {
    ivec3 uv, uuv, qvec;
    
    qvec.v.x = q->v.x;
    qvec.v.y = q->v.y;
    qvec.v.z = q->v.z;
    
    uv = ivec3cross(&qvec, v);
    uuv = ivec3cross(&qvec, &uv);
    
    uv = ivec3scale(&uv, 2.0f * q->v.w);
    uuv = ivec3scale(&uuv, 2.0f);
    
    *vout = ivec3add(v, &uv);
    *vout = ivec3add(vout, &uuv);
}

/* quaternion: rotating between */
void iquatrotatebetweenvec3(__iout iquat *quat,
                            __iin const ivec3 *vec1,
                            __iin const ivec3 *vec2,
                            __iin const ivec3 *fallback) {
    ireal a;
    ivec3 v1, v2;
    ivec3 axis;
    
    v1 = ivec3normalize(vec1);
    v2 = ivec3normalize(vec2);
    
    a = ivec3dot(&v1, &v2);
    
    if (a >= 1.0) {
        iquatidentity(quat);
        return ;
    }
    
    if (a < (1e-6f - 1.0f))	{
        if (fabs(ivec3lengthsqr(fallback)) < iepsilon) {
            iquatrotateaxisangle(quat, fallback, __iPI);
        } else {
            axis = ivec3cross(&kivec3_axis_x, vec1);
            
            /*If axis is zero*/
            if (fabs(ivec3lengthsqr(&axis)) < iepsilon) {
                axis = ivec3cross(&kivec3_axis_y, vec1);
            }
            
            axis = ivec3normalize(&axis);
            
            iquatrotateaxisangle(quat, &axis, __iPI);
        }
    } else {
        ireal s = sqrtf((1+a) * 2);
        ireal invs = 1 / s;
        
        ivec3 c;
        c = ivec3cross(&v1, &v2);
        
        quat->v.x = c.v.x * invs;
        quat->v.y = c.v.y * invs;
        quat->v.z = c.v.z * invs;
        quat->v.w = s * 0.5f;
        
        iquatnormalize(quat);
    }
}
/* quaternion: between */
void iquatbetweenvec3(__iout iquat *quat, __iin const ivec3 *u, __iin const ivec3 *v) {
    ivec3 w;
    ireal len;
    
    if(ivec3isequal(u, v)) {
        iquatidentity(quat);
        return;
    }
    
    len = sqrtf(ivec3lengthsqr(u) * ivec3lengthsqr(v));
    w = ivec3cross(u, v);
    __iquat_fill(quat, w.v.x, w.v.y, w.v.z, ivec3dot(u, v) + len);
    iquatnormalize(quat);
}

/* the rotating of behavior */
void iquatlookrotate(__iout iquat *quat, __iin const ivec3 *direction, __iin const ivec3 *up) {
    imat4 lookAt;
    imat3 rot;
    imat4lookat(&lookAt, &kivec3_zero, direction, up);
    
    imat4extractrotateimat3(&lookAt, &rot);
    
    iquatfromrotatemat3(quat, &rot);
    iquatnormalize(quat);
}

/* make a quaternion from roate matrix */
void iquatfromrotatemat3(__iout iquat *quat, __iin const union imat3 *rot) {
#if 0
Note: The OpenGL matrices are transposed from the description below
    taken from the Matrix and Quaternion FAQ
    
    if ( mat[0] > mat[5] && mat[0] > mat[10] )  {	/* Column 0:*/
        S  = sqrt( 1.0 + mat[0] - mat[5] - mat[10] ) * 2;
        X = 0.25 * S;
        Y = (mat[4] + mat[1] ) / S;
        Z = (mat[2] + mat[8] ) / S;
        W = (mat[9] - mat[6] ) / S;
    } else if ( mat[5] > mat[10] ) {			/* Column 1:*/
        S  = sqrt( 1.0 + mat[5] - mat[0] - mat[10] ) * 2;
        X = (mat[4] + mat[1] ) / S;
        Y = 0.25 * S;
        Z = (mat[9] + mat[6] ) / S;
        W = (mat[2] - mat[8] ) / S;
    } else {						/* Column 2:*/
        S  = sqrt( 1.0 + mat[10] - mat[0] - mat[5] ) * 2;
        X = (mat[2] + mat[8] ) / S;
        Y = (mat[9] + mat[6] ) / S;
        Z = 0.25 * S;
        W = (mat[4] - mat[1] ) / S;
    }
#endif
    
    ireal x, y, z, w;
    ireal *pMatrix = NULL;
    ireal m4x4[16] = {0};
    ireal scale = 0.0f;
    ireal diagonal = 0.0f;
    
    icheck(rot);
    
    /*	0 3 6
     1 4 7
     2 5 8
     
     0 1 2 3
     4 5 6 7
     8 9 10 11
     12 13 14 15*/
    
    m4x4[0]  = rot->values[0];
    m4x4[1]  = rot->values[3];
    m4x4[2]  = rot->values[6];
    m4x4[4]  = rot->values[1];
    m4x4[5]  = rot->values[4];
    m4x4[6]  = rot->values[7];
    m4x4[8]  = rot->values[2];
    m4x4[9]  = rot->values[5];
    m4x4[10] = rot->values[8];
    m4x4[15] = 1;
    pMatrix = &m4x4[0];
    
    diagonal = pMatrix[0] + pMatrix[5] + pMatrix[10] + 1;
    
    if(diagonal > iepsilon) {
        /* Calculate the scale of the diagonal*/
        scale = (ireal)sqrt(diagonal ) * 2;
        
        /* Calculate the x, y, x and w of the quaternion through the respective equation*/
        x = ( pMatrix[9] - pMatrix[6] ) / scale;
        y = ( pMatrix[2] - pMatrix[8] ) / scale;
        z = ( pMatrix[4] - pMatrix[1] ) / scale;
        w = 0.25f * scale;
    }
    else
    {
        /* If the first element of the diagonal is the greatest value*/
        if ( pMatrix[0] > pMatrix[5] && pMatrix[0] > pMatrix[10] )
        {
            /* Find the scale according to the first element, and double that value*/
            scale = (ireal)sqrt( 1.0f + pMatrix[0] - pMatrix[5] - pMatrix[10] ) * 2.0f;
            
            /* Calculate the x, y, x and w of the quaternion through the respective equation*/
            x = 0.25f * scale;
            y = (pMatrix[4] + pMatrix[1] ) / scale;
            z = (pMatrix[2] + pMatrix[8] ) / scale;
            w = (pMatrix[9] - pMatrix[6] ) / scale;
        }
        /* Else if the second element of the diagonal is the greatest value*/
        else if (pMatrix[5] > pMatrix[10])
        {
            /* Find the scale according to the second element, and double that value*/
            scale = (ireal)sqrt( 1.0f + pMatrix[5] - pMatrix[0] - pMatrix[10] ) * 2.0f;
            
            /* Calculate the x, y, x and w of the quaternion through the respective equation*/
            x = (pMatrix[4] + pMatrix[1] ) / scale;
            y = 0.25f * scale;
            z = (pMatrix[9] + pMatrix[6] ) / scale;
            w = (pMatrix[2] - pMatrix[8] ) / scale;
        }
        /* Else the third element of the diagonal is the greatest value*/
        else
        {
            /* Find the scale according to the third element, and double that value*/
            scale  = (ireal)sqrt( 1.0f + pMatrix[10] - pMatrix[0] - pMatrix[5] ) * 2.0f;
            
            /* Calculate the x, y, x and w of the quaternion through the respective equation*/
            x = (pMatrix[2] + pMatrix[8] ) / scale;
            y = (pMatrix[9] + pMatrix[6] ) / scale;
            z = 0.25f * scale;
            w = (pMatrix[4] - pMatrix[1] ) / scale;
        }
    }
    
    __iquat_fill(quat, x, y, z, w);
}

