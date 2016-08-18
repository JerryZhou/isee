#ifndef _ILINE_H_
#define _ILINE_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

#include "foundation/math/ipos.h"
#include "foundation/math/ivec.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*************************************************************/
/* iline2d                                                   */
/*************************************************************/
typedef struct iline2d {
    ipos start;
    ipos end;
}iline2d;

/* start ==> end */
ivec2 iline2ddirection(const iline2d *line);

/* start ==> end , rorate -90 */
ivec2 iline2dnormal(const iline2d *line);

/**/
ireal iline2dlength(const iline2d *line);

/*
 * Determines the signed distance from a point to this line. Consider the line as
 * if you were standing on start of the line looking towards end. Posative distances
 * are to the right of the line, negative distances are to the left.
 * */
ireal iline2dsigneddistance(const iline2d *line, const ipos *point);

/*
 * point classify
 * */
typedef enum EnumPointClass{
    EnumPointClass_On,      /* The point is on, or very near, the line  */
    EnumPointClass_Left,    /* looking from endpoint A to B, the test point is on the left */
    EnumPointClass_Right    /* looking from endpoint A to B, the test point is on the right */
}EnumPointClass;

/*
 * Determines the signed distance from a point to this line. Consider the line as
 * if you were standing on PointA of the line looking towards PointB. Posative distances
 * are to the right of the line, negative distances are to the left.
 * */
int iline2dclassifypoint(const iline2d *line, const ipos *point, ireal epsilon);

/*
 * line classify
 * */
typedef enum EnumLineClass {
    EnumLineClass_Collinear,			/* both lines are parallel and overlap each other */
    EnumLineClass_Lines_Intersect,      /* lines intersect, but their segments do not */
    EnumLineClass_Segments_Intersect,	/* both line segments bisect each other */
    EnumLineClass_A_Bisects_B,          /* line segment B is crossed by line A */
    EnumLineClass_B_Bisects_A,          /* line segment A is crossed by line B */
    EnumLineClass_Paralell              /* the lines are paralell */
}EnumLineClass;

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
int iline2dintersection(const iline2d *line, const iline2d *other,  ipos *intersect);

/* Caculating the closest point in the segment to center pos */
ipos iline2dclosestpoint(const iline2d *line, const ipos *center, ireal epsilon);

/*************************************************************/
/* iline3d                                                   */
/*************************************************************/
typedef struct iline3d {
    ipos3 start;
    ipos3 end;
}iline3d;

/* start ==> end */
ivec3 iline3ddirection(const iline3d *line);

/**/
ireal iline3dlength(const iline3d *line);

/* Caculating the closest point in the segment to center pos */
ipos3 iline3dclosestpoint(const iline3d *line, const ipos3 *center, ireal epsilon);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /*_ILINE_H_ */