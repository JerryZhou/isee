#ifndef _IENTRY_H_
#define _IENTRY_H_

#include "foundation/util/icmdarg.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
/*
 * https://msdn.microsoft.com/en-us/library/k2b2ssfy(v=vs.80).aspx
 * windows: visual-studio,  __cdecl, __stdcall, __fastcall
 * linux: gcc,  __attribute__(__cdecl)
 */
    
/* platform application entry */
#ifdef WIN32
/* windows */
#define iimplementapplication() \
    int ISeeMain(const icmdarg * arg); \
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd) \
        icmdarg *arg = icmdargmakewin32(lpCmdLine);\
        return ISeeMain(arg);\
    }
#else
/* macosx, linux */
#define iimplementapplication() \
    int ISeeMain(const icmdarg * arg); \
    int main(int argc, const char** argv) { \
        icmdarg *arg = icmdargmake(argc, argv);\
        return ISeeMain(arg);\
    }
#endif
        
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif