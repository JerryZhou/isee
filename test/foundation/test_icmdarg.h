#include "foundation/util/icmdarg.h"
#include "simpletest.h"

SP_SUIT(icmdarg);

SP_CASE(icmdarg, icmdargmakeANDicmdargmakeby) {
    icmdarg * arg = icmdargmake(0, NULL);
    SP_TRUE(arg->origin);
    SP_TRUE(istringcompare(arg->origin, kstring_empty) == 0);
    SP_TRUE(iarraylen(arg->args)==0);
    
    irelease(arg);
    
    {
        istring *sarg = istringmake("x y z");
        const char* args[] = {"x", "y", "z"};
        icmdarg * arg0 = icmdargmake(3, args);
        SP_TRUE(istringcompare(arg0->origin, sarg) == 0);
        SP_TRUE(iarraylen(arg0->args)==3);
        
        icmdarg * arg1 = icmdargmakeby(istringbuf(sarg));
        SP_TRUE(istringcompare(arg0->origin, arg1->origin) == 0);
        SP_TRUE(iarraylen(arg0->args)==iarraylen(arg1->args));
        
        irelease(sarg);
        irelease(arg0);
        irelease(arg1);
    }
}

SP_CASE(icmdarg, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}