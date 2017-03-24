#include "foundation/algorithm/ilamport.h"
#include "foundation/util/iarraytypes.h"
#include "foundation/core/imetatypes.h"

/* the lamport algorithm for hardcode-capacity */
ilamport* ilamportmake(size_t capacity) {
    ilamport *p = irefnew(ilamport);
    p->number = iarraymakeuint64(capacity);
    p->entering = iarraymakeint(capacity);
    return p;
}

/* the max value of arr */
static uint64_t _imax_arr(iarray *arr) {
    uint64_t imax = 0;
    irangearray(arr, uint64_t,
                if (__value > imax) {
                    imax = __value;
                }
                );
    return imax;
}

/* the lamport algorithm for lock */
void ilamportlock(ilamport *l, int i) {
#define __n(key) (iarrayof(l->number, uint64_t, key))
#define __m(key) (iarrayof(l->entering, int, key))
#define __mn(i, j) ((__n(i)<__n(j)) || (__n(i)==__n(j)&&i<j))
    
    __m(i) = iiok;
    __n(i) = 1 + _imax_arr(l->number);
    __m(i) = iino;
    
    irangearray(l->entering, int,
                // Wait until thread j receives its number:
                while (iarrayof(l->entering, int, __key)) {/* nothing */}
                // Wait until all threads with smaller numbers or with the same
                // number, but with higher priority, finish their work:
                while (__n(__key) == 0 && __mn(__key, i)) {/* nothing */};
                );
}

/* the lamport algorithm for unlock */
void ilamportunlock(ilamport *l, int i) {
    icheck(l && i>=0 && i<iarraylen(l->number));
    iarrayof(l->number, int, i) = 0;
}

/* the meta destructor func */
void ilamport_destructor(const struct imeta* meta, iptr o) {
    ilamport *p = icast(ilamport, o);
    irefdelete(p->entering);
    irefdelete(p->number);
}
