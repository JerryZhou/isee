#include "foundation/math/iline.h"

/*************************************************************/
/* iline2d                                                   */
/*************************************************************/

/* start ==> end */
ivec2 iline2ddirection(const iline2d *line) {
    ivec2 v = ivec2subtractpoint(&line->end, &line->start);
    return ivec2normalize(&v);
}

/* start ==> end , rorate -90 */
ivec2 iline2dnormal(const iline2d *line) {
    ireal y;
    ivec2 v = iline2ddirection(line);
    y = v.v.y;
    v.v.y = -v.v.x;
    v.v.x = y;
    return v;
}

/**/
ireal iline2dlength(const iline2d *line) {
    ivec2 v = ivec2subtractpoint(&line->end, &line->start);
    return ivec2length(&v);
}

/*
 * Determines the signed distance from a point to this line. Consider the line as
 * if you were standing on start of the line looking towards end. Posative distances
 * are to the right of the line, negative distances are to the left.
 * */
ireal iline2dsigneddistance(const iline2d *line, const ipos *point) {
    ivec2 v = ivec2subtractpoint(point, &line->start);
    ivec2 normal = iline2dnormal(line);
    return ivec2dot(&v, &normal);
}

/*
 * Determines the signed distance from a point to this line. Consider the line as
 * if you were standing on start of the line looking towards end. Posative distances
 * are to the right of the line, negative distances are to the left.
 * */
int iline2dclassifypoint(const iline2d *line, const ipos *point, ireal epsilon) {
    int      result = EnumPointClass_On;
    ireal      distance = iline2dsigneddistance(line, point);
    
    if (distance > epsilon) {
        result = EnumPointClass_Right;
    } else if (distance < -epsilon) {
        result = EnumPointClass_Left;
    }
    
    return result;
}

/*
 * Determines if two segments intersect, and if so the point of intersection. The current
 * member line is considered line AB and the incomming parameter is considered line CD for
 * the purpose of the utilized equations.
 *
 * A = PointA of the member line
 * B = PointB of the member line
 * C = PointA of the provided line
 * D = PointB of the provided line
 * */
int iline2dintersection(const iline2d *line, const iline2d *other,  ipos *intersect) {
    ireal Ay_minus_Cy = line->start.y - other->start.y;
    ireal Dx_minus_Cx = other->end.x - other->start.x;
    ireal Ax_minus_Cx = line->start.x - other->start.x;
    ireal Dy_minus_Cy = other->end.y - other->start.y;
    ireal Bx_minus_Ax = line->end.x - line->start.x;
    ireal By_minus_Ay = line->end.y - line->start.y;
    
    ireal Numerator = (Ay_minus_Cy * Dx_minus_Cx) - (Ax_minus_Cx * Dy_minus_Cy);
    ireal Denominator = (Bx_minus_Ax * Dy_minus_Cy) - (By_minus_Ay * Dx_minus_Cx);
    
    ireal FactorAB, FactorCD;
    
    /* if lines do not intersect, return now */
    if (!Denominator)
    {
        if (!Numerator)
        {
            return EnumLineClass_Collinear;
        }
        
        return EnumLineClass_Paralell;
    }
    
    FactorAB = Numerator / Denominator;
    FactorCD = ((Ay_minus_Cy * Bx_minus_Ax) - (Ax_minus_Cx * By_minus_Ay)) / Denominator;
    
    /* posting (hitting a vertex exactly) is not allowed, shift the results
     * if they are within a minute range of the end vertecies */
    /*
     if (fabs(FactorCD) < 1.0e-6f) {
     FactorCD = 1.0e-6f;
     } if (fabs(FactorCD - 1.0f) < 1.0e-6f) {
     FactorCD = 1.0f - 1.0e-6f;
     }
     */
    
    /* if an interection point was provided, fill it in now */
    if (intersect)
    {
        intersect->x = (line->start.x + (FactorAB * Bx_minus_Ax));
        intersect->y = (line->start.y + (FactorAB * By_minus_Ay));
    }
    
    /* now determine the type of intersection */
    if ((FactorAB >= 0.0f) && (FactorAB <= 1.0f) && (FactorCD >= 0.0f) && (FactorCD <= 1.0f)) {
        return EnumLineClass_Segments_Intersect;
    } else if ((FactorCD >= 0.0f) && (FactorCD <= 1.0f)) {
        return (EnumLineClass_A_Bisects_B);
    } else if ((FactorAB >= 0.0f) && (FactorAB <= 1.0f)) {
        return (EnumLineClass_B_Bisects_A);
    }
    
    return EnumLineClass_Lines_Intersect;
}

/* Caculating the closest point in the segment to center pos */
ipos iline2dclosestpoint(const iline2d *line, const ipos *center, ireal epsilon) {
    /*@see http://doswa.com/2009/07/13/circle-segment-intersectioncollision.html */
    ipos closest;
    
    ivec2 start_to_center = ivec2subtractpoint(center, &line->start);
    ivec2 line_direction = iline2ddirection(line);
    ireal line_len = iline2dlength(line);
    
    ireal projlen = ivec2dot(&start_to_center, &line_direction);
    if (projlen <= 0) {
        closest = line->start;
    } else if ( ireal_greater_than(projlen, line_len, epsilon)){
        closest = line->end;
    } else {
        closest.x = line->start.x + line_direction.v.x * projlen;
        closest.y = line->start.y + line_direction.v.y * projlen;
    }
    
    return closest;
}

/*************************************************************/
/* iline3d                                                   */
/*************************************************************/

/* start ==> end */
ivec3 iline3ddirection(const iline3d *line) {
    ivec3 v = ivec3subtractpoint(&line->end, &line->start);
    return ivec3normalize(&v);
}

/**/
ireal iline3dlength(const iline3d *line) {
    ivec3 v = ivec3subtractpoint(&line->end, &line->start);
    return ivec3length(&v);
}

/* find the closest point in line */
ipos3 iline3dclosestpoint(const iline3d *line, const ipos3 *center, ireal epsilon) {
    /*@see http://doswa.com/2009/07/13/circle-segment-intersectioncollision.html */
    ipos3 closest;
    
    ivec3 start_to_center = ivec3subtractpoint(center, &line->start);
    ivec3 line_direction = iline3ddirection(line);
    ireal line_len = iline3dlength(line);
    
    ireal projlen = ivec3dot(&start_to_center, &line_direction);
    if (projlen <= 0) {
        closest = line->start;
    } else if ( ireal_greater_than(projlen, line_len, epsilon)){
        closest = line->end;
    } else {
        closest.x = line->start.x + line_direction.v.x * projlen;
        closest.y = line->start.y + line_direction.v.y * projlen;
        closest.z = line->start.z + line_direction.v.z * projlen;
    }
    
    return closest;
}

