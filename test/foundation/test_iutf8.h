//
//  test_iutf8.h
//  isee
//
//  Created by jerry on 2017/3/26.
//
//
#include "foundation/util/iutf8.h"
#include "foundation/util/iarraytypes.h"

#ifndef test_iutf8_h
#define test_iutf8_h

SP_SUIT(iutf8);

/* 好 <==> 22909 <==> 0x597d */
// utf8: '\xe5', '\xa5', '\xbd'
// utf8: 11100101, 10100101, 10111101
// utf8: 1110xxxx, 10xxxxxx, 10xxxxxx

SP_CASE(iutf8, iutf8decode) {
    irune TheRune = 0x597d;
    irune TheRuneErr = 0x0000FFFD;
    
    iutf8decodeout rout = {0};
    {
        istring *s = istringmake("");
        iutf8decode(s, &rout);
        SP_TRUE(rout.rune == TheRuneErr);
        SP_TRUE(rout.len == 0);
        SP_TRUE(rout.need == iiok);
        irefdelete(s);
    }
    {
        istring *s0 = istringmake("12345");
        iutf8decode(s0, &rout);
        SP_TRUE(rout.rune == '1');
        SP_TRUE(rout.len == 1);
        SP_TRUE(rout.need == iino);
        irefdelete(s0);
    }
    {
        istring *s0 = istringmake("好123"); /* utf8 encode */
        iutf8decode(s0, &rout);
        SP_TRUE(rout.rune == TheRune);
        SP_TRUE(rout.len == 3);
        SP_TRUE(rout.need == iino);
        irefdelete(s0);
    }
    
    {
        ibyte ss[] = {0xe5};
        iarray *ass = iarraymakeibyte(icountof(ss));
        iarrayappend(ass, ss, icountof(ss));
        islice *bytes = islicemakearg(ass, ":");
        
        iutf8decodeout rout = {0};
        iutf8decode(bytes, &rout);
        SP_TRUE(rout.len == 1);
        SP_TRUE(rout.rune == TheRuneErr);
        SP_TRUE(rout.need == iiyes);
        
        irefdelete(ass);
        irefdelete(bytes);
    }
    
    {
        ibyte ss[] = {0xe5, 0xa5};
        iarray *ass = iarraymakeibyte(icountof(ss));
        iarrayappend(ass, ss, icountof(ss));
        islice *bytes = islicemakearg(ass, ":");
        
        iutf8decodeout rout = {0};
        iutf8decode(bytes, &rout);
        SP_TRUE(rout.len == 1);
        SP_TRUE(rout.rune == TheRuneErr);
        SP_TRUE(rout.need == iiyes);
        
        irefdelete(ass);
        irefdelete(bytes);
    }
    
    {
        ibyte ss[] = {0xe5, 0xa5, 0xbd};
        iarray *ass = iarraymakeibyte(icountof(ss));
        iarrayappend(ass, ss, icountof(ss));
        islice *bytes = islicemakearg(ass, ":");
        
        iutf8decodeout rout = {0};
        iutf8decode(bytes, &rout);
        SP_TRUE(rout.len == 3);
        SP_TRUE(rout.rune == TheRune);
        SP_TRUE(rout.need == iino);
        
        irefdelete(ass);
        irefdelete(bytes);
    }
}

SP_CASE(iutf8, iutf8decodelast) {
    
}

SP_CASE(iutf8, iutf8encode) {
    
}

SP_CASE(iutf8, iutf8valid) {
    
}

SP_CASE(iutf8, irunecount) {
    
}

SP_CASE(iutf8, irunevalid) {
    
}

SP_CASE(iutf8, irunelen) {
    
}

SP_CASE(iutf8, end) {
    SP_TRUE(1);
}


#endif /* test_iutf8_h */
