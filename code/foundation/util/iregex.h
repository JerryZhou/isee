#ifndef _IREGEX_H_
#define _IREGEX_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"

#include "foundation/util/istring.h"
#include "foundation/util/iarraytypes.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * [Implementing Regular Expressions](https://swtch.com/~rsc/regexp/ "By Russ Cox")
 * http://code.google.com/p/re2/wiki/Syntax
 * */
    
typedef struct iregex {
    irefdeclare;
} iregex;

/* destructor */
void iregex_destructor(const struct imeta* x, iptr o);

/**/
iregex* iregexcompile(const istring *reg);

/**/
ibool iregexmatch(iregex* reg, const istring *s);

/**/
iarray* iregexmatchall(iregex* reg, const istring *s);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IREGEX_H_ */
