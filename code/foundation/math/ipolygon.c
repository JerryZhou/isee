#include "foundation/math/ipolygon.h"


/*************************************************************/
/* ipolygon3d                                                */
/*************************************************************/

/* free resouces of polygon3d */
/* destructor */
void ipolygon3d_destructor(ithis x, iobj *o) {
    ipolygon3d *poly = icast(ipolygon3d, __irobj(o));
    irefdelete(poly->pos);
}

/* create a polygon 3d*/
ipolygon3d *ipolygon3dmake(size_t capacity){
    ipolygon3d *poly = irefnew(ipolygon3d);
    iarray* array = iarraymakeipos3(capacity);
    poly->pos = isliced(array, 0, 0);
    
    /* the min pos */
    poly->min.x = 0x1.fffffep+127f;
    poly->min.y = 0x1.fffffep+127f;
    poly->min.z = 0x1.fffffep+127f;
    
    irelease(array);
    iretain(poly);
    return poly;
}


/* the count of pos */
size_t ipolygon3dsize(const ipolygon3d *poly) {
    icheckret(poly, 0);
    return islicelen(poly->pos);
}

/* add ivec3 to polygon*/
void ipolygon3dadd(ipolygon3d *poly, const ipos3 *v, int nums) {
    int i;
    int j;
    ireal *values;
    ireal *max_values = (ireal*)&(poly->max);
    ireal *min_values = (ireal*)&(poly->min);
    ireal *accu_values = (ireal*)&(poly->accumulating);
    int slicelen = islicelen(poly->pos);
    icheck(v);
    icheck(poly);
    icheck(nums);
    
    /* update the min and max*/
    for (j=0; j<nums; ++j) {
        values = (ireal*)(&v[j]);
        for (i=0; i<3; ++i) {
            /* accumulating all pos */
            accu_values[i] += values[i];
            /* caculating the max and min */
            if (values[i] > max_values[i]) {
                /* for max */
                max_values[i] = values[i];
            } else if (values[i] < min_values[i]) {
                /* for min */
                min_values[i] = values[i];
            }
        }
    }
    
    /* add vec3 */
    poly->pos = isliceappendvalues(poly->pos, v, nums);
    
    /* set polygon plane */
    if (slicelen<3 && islicelen(poly->pos) >= 3) {
        /* set plane point */
        iplaneset(&poly->plane,
                  &isliceof(poly->pos, ipos3, 0),
                  &isliceof(poly->pos, ipos3, 1),
                  &isliceof(poly->pos, ipos3, 2));
    }
    
    /* auto polygon3d finish after add pos */
    ipolygon3dfinish(poly);
}

/* caculating the center of polygon3d  */
void ipolygon3dfinish(ipolygon3d *poly) {
    size_t n = islicelen(poly->pos);
    icheck(n > 1);
    poly->center.x = poly->accumulating.x / n;
    poly->center.y = poly->accumulating.y / n;
    poly->center.z = poly->accumulating.z / n;
}

/* take the polygon3d as a wrap buffer of pos */
const ipos3 *ipolygon3dpos3(ipolygon3d *polygon, int index) {
    size_t len = islicelen(polygon->pos);
    icheckret(len>0, &kipos3_zero);
    return (const ipos3 *) isliceat(polygon->pos, index%len);
}

/* take the polygon3d pos (x, z) as a wrap buffer of pos */
ipos ipolygon3dposxz(ipolygon3d *polygon, int index) {
    const ipos3* p3 = ipolygon3dpos3(polygon, index);
    ipos p = {p3->x, p3->z};
    return p;
}

/* the the edge (center-middle) point*/
ipos3 ipolygon3dedgecenter(ipolygon3d *polygon, int index) {
    const ipos3* p3_start = ipolygon3dpos3(polygon, index);
    const ipos3* p3_end = ipolygon3dpos3(polygon, index+1);
    ipos3 center = {
        (p3_start->x + p3_end->x)/2,
        (p3_start->y + p3_end->y)/2,
        (p3_start->z + p3_end->z)/2,
    };
    return center;
}

/* if the point in polygon, just like 2d contains*/
/* Left Hand System
 * y     z
 * ^     ^
 * |    /
 * |   /
 * |  /
 * | /
 * |---------> x
 * */
int ipolygon3dincollum(const ipolygon3d *poly, const ipos3 *v) {
    int inside = iino;
    int i, j, n;
    ipos3 *ui, *uj;
    
    icheckret(v, iiok);
    icheckret(poly, iino);
    
    /* beyond the bounding box*/
    if (v->x < poly->min.x ||
        v->x > poly->max.x ||
        v->z < poly->min.z ||
        v->z > poly->max.z) {
        return iino;
    }
    
    /* https://en.wikipedia.org/wiki/Point_in_polygon
     */
    n = islicelen(poly->pos);
    for (i = 0, j = n-1; i<n; j = i++) {
        ui = (ipos3*)isliceat(poly->pos, i);
        uj = (ipos3*)isliceat(poly->pos, j);
        if ((ui->z > v->z) != (uj->z > v->z) &&
            v->x < ((uj->x - ui->x)
                    * (v->z - ui->z)
                    / (uj->z - ui->z)
                    + ui->x) ) {
                inside = !inside;
            }
    }
    
    return inside;
}

/* give the projection rect in xz-plane */
void ipolygon3dtakerectxz(const ipolygon3d *poly, irect *r) {
    ipos min, max;
    ipos3takexz(&poly->min, &min);
    ipos3takexz(&poly->max, &max);
    r->pos = min;
    r->size.w = max.x - min.x;
    r->size.h = max.y - min.y;
}

/*************************************************************/
/* ipolygon2d                                                */
/*************************************************************/

/* free resouces of polygon3d */
/* destructor */
void ipolygon2d_destructor(ithis x, iobj *o) {
    ipolygon2d *poly = icast(ipolygon2d, __irobj(o));
    irefdelete(poly->pos);
}

/* create a polygon 2d*/
ipolygon2d *ipolygon2dmake(size_t capacity) {
    ipolygon2d *poly = irefnew(ipolygon2d);
    iarray* array = iarraymakeivec2(capacity);
    poly->pos = isliced(array, 0, 0);
    
    /* the min pos */
    poly->min.x = 0x1.fffffep+127f;
    poly->min.y = 0x1.fffffep+127f;
    
    irelease(array);
    return poly;
}

/* the count of pos */
size_t ipolygon2dsize(const ipolygon2d *poly) {
    icheckret(poly, 0);
    return islicelen(poly->pos);
}

/* add ivec2 to polygon*/
void ipolygon2dadd(ipolygon2d *poly, const ipos2 *v, int nums) {
    int i;
    int j;
    ireal *values;
    ireal *max_values = (ireal*)&(poly->max);
    ireal *min_values = (ireal*)&(poly->min);
    ireal *accu_values = (ireal*)&(poly->accumulating);
    
    icheck(v);
    icheck(poly);
    
    /* update the min and max*/
    for (j=0; j<nums; ++j) {
        values = (ireal*)(&v[j]);
        for (i=0; i<2; ++i) {
            /* accumulating all pos */
            accu_values[i] += values[i];
            /* caculating the max and min */
            if (values[i] > max_values[i]) {
                /* for max */
                max_values[i] = values[i];
            } else if (values[i] < min_values[i]) {
                /* for min */
                min_values[i] = values[i];
            }
        }
    }
    
    /* add vec2 */
    poly->pos = isliceappendvalues(poly->pos, v, nums);
    
    /* the center */
    ipolygon2dfinish(poly);
}

/* if the point in polygon
 * http://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
 * https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
 **/
int ipolygon2dcontains(const ipolygon2d *poly, const ipos2 *v) {
    int inside = iino;
    int i, j, n;
    ipos2 *ui, *uj;
    
    icheckret(v, iiok);
    icheckret(poly, iino);
    
    /* beyond the bounding box*/
    if (v->x < poly->min.x ||
        v->x > poly->max.x ||
        v->y < poly->min.y ||
        v->y > poly->max.y) {
        return iino;
    }
    
    /* https://en.wikipedia.org/wiki/Point_in_polygon
     */
    n = islicelen(poly->pos);
    for (i = 0, j = n-1; i<n; j = i++) {
        ui = (ipos2*)isliceat(poly->pos, i);
        uj = (ipos2*)isliceat(poly->pos, j);
        if ((ui->y>v->y) != (uj->y > v->y) &&
            v->x < ((uj->x - ui->x)
                      * (v->y - ui->y)
                      / (uj->y - ui->y)
                      + ui->x) ) {
                inside = !inside;
            }
    }
    
    return inside;
}

/* caculating the center of polygon3d  */
void ipolygon2dfinish(ipolygon2d *poly) {
    size_t n = islicelen(poly->pos);
    icheck(n > 1);
    poly->center.x = poly->accumulating.x / n;
    poly->center.y = poly->accumulating.y / n;
}