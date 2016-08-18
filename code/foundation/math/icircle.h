#ifndef _ICIRCLE_H_
#define _ICIRCLE_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

#include "foundation/math/iline.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* fowrad declares */
struct irect;
    
/*************************************************************/
/* icircle                                                   */
/*************************************************************/

/* icircle */
typedef struct icircle {
    ipos pos;
    ireal radius;
}icircle;

/* relations */
typedef enum EnumCircleRelation {
    EnumCircleRelationBContainsA = -2,
    EnumCircleRelationAContainsB = -1,
    EnumCircleRelationNoIntersect = 0,
    EnumCircleRelationIntersect = 1,
} EnumCircleRelation;

/* intersect: iiok, iino */
int icircleintersect(const icircle *con, const icircle *c);
/* intersect: iiok, iino */
int icirclecontains(const icircle *con, const icircle *c);
/* intersect: iiok, iino */
int icirclecontainspoint(const icircle *con, const ipos *p);
/* intersect: EnumCircleRelationBContainsA(c contains con), */
/*    EnumCircleRelationAContainsB(con contains c), */
/*    EnumCircleRelationIntersect(intersect), */
/*    EnumCircleRelationNoIntersect(dismiss) */
int icirclerelation(const icircle *con, const icircle *c);

/* Caculating the offset that circle should moved to avoid collided with the line */
ivec2 icircleoffset(const icircle* circle, const iline2d* line);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _ICIRCLE_H_ */