#ifndef _IRECT_H_
#define _IRECT_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"

#include "foundation/math/ipos.h"
#include "foundation/math/isize.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/* forward declares */
struct icircle;
    
/*************************************************************/
/* irect                                                     */
/*************************************************************/

/* rectangle */
typedef struct irect {
    ipos pos;
    isize size;
}irect;

/* contains: iiok, iino */
int irectcontains(const irect *con, const irect *r);
/* contains: iiok, iino */
int irectcontainspoint(const irect *con, const ipos *p);
/* intersect: irect and icircle */
int irectintersect(const irect *con, const struct icircle *c);

/* down-left pos*/
ipos irectdownleft(const irect *con);
/* down-right pos*/
ipos irectdownright(const irect *con);
/* up-left pos*/
ipos irectupleft(const irect *con);
/* up-right pos*/
ipos irectupright(const irect *con);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IRECT_H_ */