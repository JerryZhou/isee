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
static irune TheRune = 0x597d;
static ibyte TheRuneBytes[] = {0xe5, 0xa5, 0xbd};
static irune TheRuneErr = 0x0000FFFD;

SP_CASE(iutf8, iutf8decode) {
    
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
    {
        ibyte ss[] = {'A', 0xe5, 0xa5, 0xbd};
        iarray *ass = iarraymakeibyte(icountof(ss));
        iarrayappend(ass, ss, icountof(ss));
        islice *bytes = islicemakearg(ass, ":");
        
        iutf8decodeout rout = {0};
        iutf8decodelast(bytes, &rout);
        SP_TRUE(rout.len == 3);
        SP_TRUE(rout.rune == TheRune);
        SP_TRUE(rout.need == iino);
        
        islice* snext = islicedby(bytes, 0, islicelen(bytes)-rout.len);
        iutf8decodelast(snext, &rout);
        SP_TRUE(rout.len == 1);
        SP_TRUE(rout.rune == 'A');
        SP_TRUE(rout.need == iino);
        irefdelete(snext);
        
        irefdelete(ass);
        irefdelete(bytes);
    }
}

SP_CASE(iutf8, iutf8encode) {
    iutf8encodeout rout;
    iutf8encode(TheRune, &rout);
    SP_TRUE(rout.len == 3);
    SP_TRUE(rout.utf8[0] == TheRuneBytes[0]);
    SP_TRUE(rout.utf8[1] == TheRuneBytes[1]);
    SP_TRUE(rout.utf8[2] == TheRuneBytes[2]);
    
    iutf8encode('A', &rout);
    SP_TRUE(rout.len == 1);
    SP_TRUE(rout.utf8[0] == 'A');
}

SP_CASE(iutf8, iutf8valid) {
    istring *s = istringmakelen((char*)TheRuneBytes, icountof(TheRuneBytes));
    SP_TRUE(iutf8valid(s) == iiok);
    irefdelete(s);
    
    {
        istring *s = istringmake("A");
        SP_TRUE(iutf8valid(s) == iiok);
        irefdelete(s);
    }
    
    {
        ibyte ss[] = {0xe5, 0xa5};
        iarray *ass = iarraymakeibyte(icountof(ss));
        iarrayappend(ass, ss, icountof(ss));
        islice *bytes = islicemakearg(ass, ":");
        
        SP_TRUE(iutf8valid(bytes) == iino);
        
        irefdelete(ass);
        irefdelete(bytes);
    }
}

SP_CASE(iutf8, irunecount) {
    istring *s = istringmake("A好12");
    SP_TRUE(iutf8valid(s) == iiok);
    SP_TRUE(irunecount(s) == 4);
    irefdelete(s);
}

SP_CASE(iutf8, irunevalid) {
    SP_TRUE(1);
}

SP_CASE(iutf8, irunelen) {
    SP_TRUE(1);
}

SP_CASE(iutf8, end) {
    SP_TRUE(1);
}


#endif /* test_iutf8_h */
