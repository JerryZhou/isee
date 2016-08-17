#ifndef _ICMDARG_H_
#define _ICMDARG_H_

#include "foundation/core/iref.h"
#include "foundation/util/istring.h"

/* wrap the cmd arguments */
typedef struct icmdarg {
    irefdeclare;
    
    istring origin;
    iarray *args; /*iarray<istring> */
} icmdarg;

/* make a icmdarg from command lines */
icmdarg *icmdargmake(int argc, const char **argv);

/* make a icmdarg from the origin command input */
icmdarg *icmdargmakeby(const char* origin);

/* for win32 */
#ifdef WIN32
icmdarg *icmdargmakewin32(LPSTR str);
#endif

#endif