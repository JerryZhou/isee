#include "foundation/util/icmdarg.h"
#include "foundation/core/imetatypes.h"
#include "foundation/util/iarraytypes.h"

/* destructor */
void icmdarg_destructor(const struct imeta* meta, iptr o) {
    icmdarg *arg = icast(icmdarg, o);
    iassign(arg->args, NULL);
    iassign(arg->origin, NULL);
}

/* make a icmdarg from command lines */
icmdarg *icmdargmake(int argc, const char **argv) {
    icmdarg *arg = irefnew(icmdarg);
    istring *tmp = NULL;
    int i=0;
    
    /* make istring */
    arg->args = iarraymakeiref(argc);
    for (; i<argc; ++i) {
        tmp = istringmake(argv[i]);
        iarrayadd(arg->args, &tmp);
        irelease(tmp);
    }
    /* join it */
    arg->origin = istringjoin(arg->args, " ", 1);
    return arg;
}

/* make a icmdarg from the origin command input */
icmdarg *icmdargmakeby(const char* origin) {
    icmdarg *arg = irefnew(icmdarg);
    arg->origin = istringmake(origin);
    /* todos: take care of \" wrap */
    arg->args = istringsplit(arg->origin, " ", 1);
    return arg;
}

/* for win32 */
#ifdef WIN32
/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx
 * typedef CHAR *LPSTR;
 * #ifdef UNICODE
 *  typedef LPWSTR LPTSTR;
 * #else
 *  typedef LPSTR LPTSTR;
 * #endif
 */
icmdarg *icmdargmakewin32(LPSTR str) {
    const char* cstr = (const char*)str;
    return icmdargmakeby(cstr);
}
#endif
