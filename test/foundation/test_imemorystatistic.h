#include "simpletest.h"
#include "foundation/imemorystatistics.h"

// **********************************************************************************
// imemorystatistics
SP_SUIT(imemorystatistics);

SP_CASE(imemorystatistics, imemorystatisbehavior_alloc) {
    imemorystatistics statis = {};
    SP_TRUE(statis.alloced == 0);
    SP_TRUE(statis.current == 0);
    SP_TRUE(statis.freed == 0);
    
    imemorystatisbehavior_alloc(&statis, 1);
    SP_TRUE(statis.alloced == 1);
    SP_TRUE(statis.current == 1);
    SP_TRUE(statis.freed == 0);
}

SP_CASE(imemorystatistics, imemorystatisbehavior_free) {
    imemorystatistics statis = {};
    SP_TRUE(statis.alloced == 0);
    SP_TRUE(statis.current == 0);
    SP_TRUE(statis.freed == 0);
    
    imemorystatisbehavior_alloc(&statis, 1);
    SP_TRUE(statis.alloced == 1);
    SP_TRUE(statis.current == 1);
    SP_TRUE(statis.freed == 0);
    
    imemorystatisbehavior_free(&statis, 1);
    SP_TRUE(statis.alloced == 1);
    SP_TRUE(statis.current == 0);
    SP_TRUE(statis.freed == 1);
}