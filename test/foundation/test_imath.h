#include "foundation/math/imath.h"

SP_SUIT(imath);

SP_CASE(imath, xx) {
    ireal i = iSQR(1);
    ireal izero = iSQR(0);
    SP_TRUE(i==1);
    SP_TRUE(izero==0);
    
    ireal ix = iSQR(1.414);
    SP_TRUE(ireal_equal_in(2, ix, 0.001));
}

SP_CASE(imath, idegreestoradians) {
    ireal pi = idegreestoradians(180);
    SP_TRUE(ireal_equal(pi, __iPI));
}

SP_CASE(imath, irandianstodegrees) {
    ireal degree = irandianstodegrees(__iPI);
    SP_TRUE(ireal_equal(degree, 180));
}

SP_CASE(imath, iclamp) {
    ireal x0 = iclamp(0, 0, 1);
    SP_TRUE(ireal_equal(x0, 0));
    ireal x1 = iclamp(1, 0, 1);
    SP_TRUE(ireal_equal(x1, 1));
    ireal xx = iclamp(0.5, 0, 1);
    SP_TRUE(ireal_equal(xx, 0.5));
    ireal xx0 = iclamp(-1, 0, 1);
    SP_TRUE(ireal_equal(xx0, 0));
    ireal xx1 = iclamp(2, 0, 1);
    SP_TRUE(ireal_equal(xx1, 1));
}

SP_CASE(imath, ilerp) {
    // v = x + (y-x) * t
    ireal v = ilerp(0, 1, 0);
    SP_TRUE(ireal_equal(v, 0));
    v = ilerp(0, 1, 1);
    SP_TRUE(ireal_equal(v, 1));
    v = ilerp(0, 1, 0.5);
    SP_TRUE(ireal_equal(v, 0.5));
    
    v = ilerp(0, 1, 2);
    SP_TRUE(ireal_equal(v, 2));
    
    v = ilerp(0, 1, -0.5);
    SP_TRUE(ireal_equal(v, -0.5));
}

SP_CASE(imath, end) {
    SP_TRUE(1);
}