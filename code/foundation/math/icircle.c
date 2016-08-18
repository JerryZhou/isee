#include "foundation/math/icircle.h"
#include "foundation/math/irect.h"


/* Caculating the offset that circle should moved to avoid collided with the line */
ivec2 icircleoffset(const icircle* circle, const iline2d* line) {
    /*@see http://doswa.com/2009/07/13/circle-segment-intersectioncollision.html */
    ipos closest = iline2dclosestpoint(line, &circle->pos, iepsilon);
    ivec2 dist = ivec2subtractpoint(&circle->pos, &closest);
    ireal distlen = ivec2length(&dist);
    ivec2 offset = {{0,0}};
    if (ireal_greater(distlen, circle->radius)) {
        return offset;
    }else if(ireal_equal_zero(distlen)) {
        /*the circle center is on line: move normal in line */
        offset = iline2dnormal(line);
        offset = ivec2multipy(&offset, circle->radius);
        return offset;
    }
    /* normalize(dist) * (radius - distlen) */
    return ivec2multipy(&dist, (circle->radius - distlen) / distlen);
}

/* intersect: iiok, iino */
int icircleintersect(const icircle *con, const icircle *c) {
    ireal ds = 0.0;
    icheckret(con, iino);
    icheckret(c, iiok);
    
    ds = (con->radius + c->radius);
    
    if (idistancepow2(&con->pos, &c->pos) <= ds * ds) {
        return iiok;
    }
    
    return iino;
}

/* contains: iiok, iino */
int icirclecontains(const icircle *con, const icircle *c) {
    ireal ds = 0.0;
    icheckret(con, iino);
    icheckret(c, iiok);
    ds = (con->radius - c->radius);
    icheckret(ds >= 0, iino);
    
    if (idistancepow2(&con->pos, &c->pos) <= ds * ds) {
        return iiok;
    }
    
    return iino;
}

/* contains: iiok, iino */
int icirclecontainspoint(const icircle *con, const ipos *p) {
    ireal ds = 0.0;
    icheckret(con, iino);
    icheckret(p, iiok);
    ds = (con->radius);
    icheckret(ds >= 0, iino);
    
    if (idistancepow2(&con->pos, p) <= ds * ds) {
        return iiok;
    }
    
    return iino;
}

/* circle relations: EnumCircleRelationBContainsA(c contains con), */
/*	  EnumCircleRelationAContainsB(con contains c), */
/*	  EnumCircleRelationIntersect(intersect), */
/*	  EnumCircleRelationNoIntersect(dismiss) */
int icirclerelation(const icircle *con, const icircle *c) {
    ireal minusds = 0.0;
    ireal addds = 0.0;
    ireal ds = 0.0;
    icheckret(con, EnumCircleRelationBContainsA);
    icheckret(c, EnumCircleRelationAContainsB);
    
    minusds = con->radius - c->radius;
    addds = con->radius + c->radius;
    ds = idistancepow2(&con->pos, &c->pos);
    
    if (ds <= minusds * minusds) {
        if (minusds >= 0) {
            return EnumCircleRelationAContainsB;
        }else {
            return EnumCircleRelationBContainsA;
        }
    } else if (ds <= addds *addds) {
        return EnumCircleRelationIntersect;
    } else {
        return EnumCircleRelationNoIntersect;
    }
}