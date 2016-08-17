#ifndef _IENTRY_H_
#define _IENTRY_H_

#include "foundation/util/icmdarg.h"

/* platform application entry */
#ifdef WIN32
/* windows */
#define iimplementapplication() \
    int ISeeMain(const imdarg * arg); \
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        icmdarg *arg = icmdargmakewin32(lpCmdLine);\
        return ISeeMain(arg);\
    }
#else
/* macosx, linux */
#define iimplementapplication() \
    int ISeeMain(const imdarg * arg); \
    int __cdecl main(int argc, const char** argv) { \
        icmdarg *arg = icmdargmake(argc, argv);\
        return ISeeMain(arg);\
    }
#endif

#endif