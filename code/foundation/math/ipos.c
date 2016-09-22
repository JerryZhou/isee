#include "foundation/math/ipos.h"

/* zero point */
const ipos kipos_zero = {0,0};
const ipos kipos_x = {1,0};
const ipos kipos_y = {0,1};
const ipos kipos_xy = {1,1};

/* distance  */
ireal idistancepow2(const ipos *p, const ipos *t) {
    ireal dx = p->x - t->x;
    ireal dy = p->y - t->y;
    return dx*dx + dy*dy;
}

/* zero point */
const ipos3 kipos3_zero = {0, 0, 0};
const ipos3 kipos3_x = {1, 0, 0};
const ipos3 kipos3_y = {0, 1, 0};
const ipos3 kipos3_z = {0, 0, 1};
const ipos3 kipos3_xz = {1, 0, 1};

/* distance */
ireal idistancepow3(const ipos3 *p, const ipos3 *t) {
    ireal dx = p->x - t->x;
    ireal dy = p->y - t->y;
    ireal dz = p->z - t->z;
    return dx*dx + dy*dy + dz*dz;
}

/* get the xy from the p with xz */
void ipos3takexz(const ipos3 *p, ipos *to) {
    to->x = p->x;
    to->y = p->z;
}