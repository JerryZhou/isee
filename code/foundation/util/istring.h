#ifndef _ISTRING_H_
#define _ISTRING_H_
#include "foundation/container/islice.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
typedef islice istring;

/* declare the string in stack, no need to free */
#define ideclarestring(name, value) \
iarray name##_array = {1, NULL, NULL, 0, NULL, strlen(value), strlen(value), (char*)value};\
islice name##_slice = {1, NULL, NULL, 0, NULL, &name##_array, 0, strlen(value)};\
islice * name = & name##_slice

/* NULL istring */
extern istring *kstring_zero;
/* empty istring */
extern istring *kstring_empty;

/*Make a string by c-style string */
istring* istringmake(const char* s);

/*Make a string by s and len*/
istring* istringmakelen(const char* s, size_t len);

/*Make a string by raw array, will release the reference of raw */
istring* istringfromraw(iarray *raw);

/*Make a copy of s with c-style string*/
istring* istringdup(const istring *s);

/*Return the string length */
size_t istringlen(const istring *s);

/*visit the real string buffer*/
const char* istringbuf(const istring *s);

/*set the entry for stack string */
istring* istringlaw(istring *s);

/*format the string and return the value*/
/* This function is similar to sdscatprintf, but much faster as it does
 * not rely on sprintf() family functions implemented by the libc that
 * are often very slow. Moreover directly handling the sds string as
 * new data is concatenated provides a performance improvement.
 *
 * However this function only handles an incompatible subset of printf-alike
 * format specifiers:
 *
 * %s - C String
 * %i - signed int
 * %I - 64 bit signed integer (long long, int64_t)
 * %u - unsigned int
 * %U - 64 bit unsigned integer (unsigned long long, uint64_t)
 * %v - istring
 * %V - istring
 * %f - double
 * %F - double
 * %% - Verbatim "%" character.
 */
    
istring* istringformat(const char* format, ...);

/* buf- raw format */
size_t istringrawformat(iarray *buf, const char *format, ...);

/* buf- raw va_list format */
size_t istringvrawformat(iarray *buf, const char *format, va_list ap);

/*compare the two istring*/
int istringcompare(const istring *lfs, const istring *rfs);

/*find the index in istring */
int istringfind(const istring *rfs, const char *sub, int len, int index);

/*sub string*/
istring* istringsub(const istring *s, int begin, int end);

/*return the array of istring*/
iarray* istringsplit(const istring *s, const char* split, size_t len);

/*return the array of string joined by dealer */
istring* istringjoin(const iarray* ss, const char* join, size_t len);

/*return the new istring with new component*/
istring* istringrepleace(const istring *s, const char* olds, size_t oldslen, const char* news, size_t newlen);

/*return the new istring append with value*/
istring* istringappend(const istring *s, const char* append, size_t len);

/*baisc wrap for ::atoi */
int istringatoi(const istring *s);

/*[cocos2dx](https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/base/ccUtils.h)*/
/** Same to ::atof, but strip the string, remain 7 numbers after '.' before call atof.
 * Why we need this? Because in android c++_static, atof ( and std::atof )
 * is unsupported for numbers have long decimal part and contain
 * several numbers can approximate to 1 ( like 90.099998474121094 ), it will return inf.
 * This function is used to fix this bug.
 * @param str The string be to converted to double.
 * @return Returns converted value of a string.
 */
double istringatof(const istring *s);

/* */
size_t ill2string(char *s, int64_t value);

/* */
size_t iull2string(char *s, uint64_t value);

/* */
size_t idouble2string(char *s, double value);

/* the hash-code in md5 */
uint64_t istringhashcode(const istring *s);

/* the meta funcs: hash with md5 code */
uint64_t istring_hash(const struct imeta*, iptr o);

/* the meta funcs: compare with literal order */
int istring_compare(const struct imeta*, iptr lfs, iptr rfs);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif
