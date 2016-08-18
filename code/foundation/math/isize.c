#include "foundation/math/isize.h"

/* isize change to isizei */
isizei isize2i(isize s) {
    isizei i = {(int)s.w, (int)s.h};
    return i;
}

/* isize change to isizei */
isize isizei2(isizei s) {
    isize r = {(ireal)s.w, (ireal)s.h};
    return r;
}

/* isize scale */
isize isizescale(isize s, ireal scale) {
    isize r = {s.w * scale, s.h * scale} ;
    return r;
}
