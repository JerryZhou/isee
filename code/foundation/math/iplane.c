#include "foundation/math/iplane.h"

/* Setup Plane object given a clockwise ordering of 3D points */
void iplaneset(iplane *plane, const ipos3 *a, const ipos3 *b, const ipos3 *c) {
    ivec3 ab = ivec3subtractpoint(a, b);
    ivec3 ac = ivec3subtractpoint(a, c);
    ivec3 normal = ivec3cross(&ab, &ac);
    ivec3 p = {{a->x, a->y, a->z}}; /*change to vec3*/
    
    plane->normal = ivec3normalize(&normal);
    plane->pos = *a;
    plane->distance = ivec3dot(&p, &plane->normal);
}

/* TODO: */
ireal iplanesigneddistance(const iplane *plane, const ipos3 *p) {
    return 0;
}

/* Given Z and Y, Solve for X on the plane */
ireal iplanesolveforx(iplane *plane, ireal y, ireal z) {
    /*
     * Ax + By + Cz + D = 0
     * Ax = -(By + Cz + D)
     * x = -(By + Cz + D)/A */
    
    if (plane->normal.values[0] ) {
        return ( -(plane->normal.values[1]*y
                   + plane->normal.values[2]*z
                   + plane->distance) / plane->normal.values[0] );
    }
    
    return (0.0f);
}

/* Given X and Z, Solve for Y on the plane */
ireal iplanesolvefory(iplane *plane, ireal x, ireal z) {
    /*
     * Ax + By + Cz + D = 0
     * By = -(Ax + Cz + D)
     * y = -(Ax + Cz + D)/B */
    
    if (plane->normal.values[1]) {
        return ( -(plane->normal.values[0]*x
                   + plane->normal.values[2]*z
                   + plane->distance) / plane->normal.values[1] );
    }
    
    return (0.0f);
    
}

/* Given X and Y, Solve for Z on the plane */
ireal iplanesolveforz(iplane *plane, ireal x, ireal y) {
    /*Ax + By + Cz + D = 0
     * Cz = -(Ax + By + D)
     * z = -(Ax + By + D)/C */
    
    if (plane->normal.values[2]) {
        return ( -(plane->normal.values[0]*x
                   + plane->normal.values[1]*y
                   + plane->distance) / plane->normal.values[2] );
    }
    
    return (0.0f);
}