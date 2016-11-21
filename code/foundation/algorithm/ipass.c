#include "foundation/algorithm/ipass.h"

/* low pass filter 低通滤波器 
 * f(t) = (1-a).f(t-∆t) + a.u(t)
 * https://zh.wikipedia.org/zh-cn/%E4%BD%8E%E9%80%9A%E6%BB%A4%E6%B3%A2%E5%99%A8
 * */
ireal ilowpassfilter(ireal unfiltered, ireal lastfiltered, ireal rc, f32 dt) {
    ireal a = dt / (rc + dt);
    return (1.-a) * lastfiltered + a * unfiltered;
}

