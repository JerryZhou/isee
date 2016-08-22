#include "foundation/math/imath.h"

/* square of v */
ireal iSQR(ireal v) {
    return  v * v;
}

/* degrees to randians */
ireal idegreestoradians(ireal degrees) {
   return degrees * __iPIOver180;
}

/* randians to degrees */
ireal irandianstodegrees(ireal randians) {
    return randians * __iPIUnder180;
}

/* clamp the value to [min max] */
ireal iclamp(ireal v, ireal min, ireal max) {
    return v < min ? min : (v > max ? max : v);
}

/* lerp the x and y ==> (x * (1-t) + y * t) ==> (x + (y-x) * t )*/
ireal ilerp(ireal x, ireal y, ireal t) {
    return x + (y-x) * t;
}