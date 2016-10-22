#include "irand.h"

#define izeromemorylen(addr, size) memset(addr, 0 , size)
#define izeromemory(value)  izeromemorylen(value,  sizeof(value))

#define m16Long 65536L				/* 2^16 */
#define m16Mask 0xFFFF              /* mask for lower 16 bits */
#define m15Mask 0x7FFF              /* mask for lower 15 bits */
#define m31Mask 0x7FFFFFFF          /* mask for 31 bits */
#define m32Double  4294967295.0     /* 2^32-1 */

/* initialization rand struct */
void irandinit(irand *rand, unsigned long sSeed) {
    unsigned long  number;
    short n, *p;
    unsigned short sNumber;
    
    izeromemory(rand->mother1);
    izeromemory(rand->mother2);
    
    /* Initialize motheri with 9 random values the first time */
    sNumber= sSeed&m16Mask;   /* The low 16 bits */
    number= sSeed&m31Mask;   /* Only want 31 bits */
    
    p=rand->mother1;
    for (n=18;n--;) {
        number=30903*sNumber+(number>>16);   /* One line
                                              multiply-with-cary */
        *p++=sNumber=number&m16Mask;
        if (n==9) {
            p=rand->mother2;
        }
    }
    /* make cary 15 bits */
    rand->mother1[0]&=m15Mask;
    rand->mother2[0]&=m15Mask;
}

static unsigned long __irand_mother(irand *rand, double *f) {
    unsigned long  number1, number2;
    icheckretassert(rand && f, 0);
    
    /* Move elements 1 to 8 to 2 to 9 */
    memmove(rand->mother1+2,rand->mother1+1,8*sizeof(short));
    memmove(rand->mother2+2,rand->mother2+1,8*sizeof(short));
    
    /* Put the carry values in numberi */
    number1=rand->mother1[0];
    number2=rand->mother2[0];
    
    /* Form the linear combinations */
    
    number1+=1941*rand->mother1[2]+1860*rand->mother1[3]+1812*rand->mother1[4]+1776*rand->mother1[5]+
				
    1492*rand->mother1[6]+1215*rand->mother1[7]+1066*rand->mother1[8]+12013*rand->mother1[9];
    
    number2+=1111*rand->mother2[2]+2222*rand->mother2[3]+3333*rand->mother2[4]+4444*rand->mother2[5]+
				
    5555*rand->mother2[6]+6666*rand->mother2[7]+7777*rand->mother2[8]+9272*rand->mother2[9];
    
    /* Save the high bits of numberi as the new carry */
    rand->mother1[0]=number1/m16Long;
    rand->mother2[0]=number2/m16Long;
    /* Put the low bits of numberi into motheri[1] */
    rand->mother1[1]=m16Mask&number1;
    rand->mother2[1]=m16Mask&number2;
    
    /* Combine the two 16 bit random numbers into one 32 bit */
    number1=(((long)rand->mother1[1])<<16)+(long)rand->mother2[1];
    *f =  ((double)number1)/m32Double;
    
    /* Return a double value between 0 and 1 */
    return number1;
}

/* generated the rand value [0, 1] */
double irandf(irand *rand) {
    double f;
    __irand_mother(rand, &f);
    return f;
}

/* generated the rand value [0, 0xffffffff] */
unsigned long irandn(irand *rand) {
    double f;
    return __irand_mother(rand, &f);
}

/* generated the rand value [0, maxn] */
unsigned long irandN(irand *rand, unsigned long maxn) {
    return (unsigned long)(irandf(rand) * maxn);
}
