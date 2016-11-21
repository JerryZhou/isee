#ifndef _IPASS_H_
#define _IPASS_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* low pass filter 低通滤波器 
 * f(t) = (1-a).f(t-∆t) + a.u(t)
 * https://zh.wikipedia.org/zh-cn/%E4%BD%8E%E9%80%9A%E6%BB%A4%E6%B3%A2%E5%99%A8
 * */
ireal ilowpassfilter(ireal unfiltered, ireal lastfiltered, ireal rc, f32 dt);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IPASS_H_ */
