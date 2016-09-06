#include "foundation/util/istring.h"
#include "simpletest.h"

SP_SUIT(istring);

SP_CASE(istring, kstring_zeroANDkstring_empty) {
    SP_TRUE(istringlen(kstring_zero) == 0);
    SP_TRUE(kstring_zero == NULL);
    
    SP_TRUE(istringlen(kstring_empty) == 0);
    SP_TRUE(kstring_empty != NULL);
}

SP_CASE(istring, istringmakeANDistringmakelen) {
    istring *s = istringmake(NULL);
    SP_TRUE(s == kstring_zero);
    
    istring *s0 = istringmake("");
    SP_TRUE(s0 == kstring_empty);
    
    istring *s1 = istringmake("123");
    SP_TRUE(istringlen(s1) == 3);
    SP_TRUE(istringbuf(s1)[0] == '1');
    SP_TRUE(istringbuf(s1)[1] == '2');
    SP_TRUE(istringbuf(s1)[2] == '3');
    SP_TRUE(istringbuf(s1)[3] == 0);
    
    irelease(s);
    irelease(s0);
    irelease(s1);
}

SP_CASE(istring, istringdup) {
    istring *s0 = istringmake("0123");
    istring *s1 = istringdup(s0);
    
    SP_TRUE(s0 != s1);
    SP_TRUE(istringcompare(s0, s1)==0);
    
    irelease(s0);
    irelease(s1);
}

SP_CASE(istring, istringlen) {
    istring *s0 = istringmake("0123");
    
    SP_TRUE(istringlen(s0) == 4);
    
    irelease(s0);
}

SP_CASE(istring, istringbuf) {
    istring *s0 = istringmake("0123");
    
    SP_TRUE(istringlen(s0) == 4);
    
    const char* sbuf = istringbuf(s0);
    SP_TRUE(sbuf[0] == '0');
    SP_TRUE(sbuf[1] == '1');
    SP_TRUE(sbuf[2] == '2');
    SP_TRUE(sbuf[3] == '3');
    SP_TRUE(sbuf[4] == 0);
    
    irelease(s0);
}

SP_CASE(istring, istringlaw) {
    istring *s0 = istringmake("0123");
    
    SP_TRUE(istringlen(s0) == 4);
    
    const char* sbuf = istringbuf(s0);
    SP_TRUE(sbuf[0] == '0');
    SP_TRUE(sbuf[1] == '1');
    SP_TRUE(sbuf[2] == '2');
    SP_TRUE(sbuf[3] == '3');
    SP_TRUE(sbuf[4] == 0);
    
    SP_TRUE(s0->array->entry == iarrayentryget(EnumArrayEntryType_Char));
    SP_TRUE(iflag_is(s0->flag, EnumSliceFlag_String));
    
    irelease(s0);
}

SP_CASE(istring, istringformat) {
    istring * s = istringmake("abc");
    istring * s0 = istringformat("i:%i,I:%I,v:%v,V:%V,u:%u,U:%U,s:%s,f:%f,F:%F", 1, int64_t(1), s, s, (unsigned int)(1), (uint64_t)(1), "abc", 1.0, 1.0);
    istring * s1 = istringmake("i:1,I:1,v:abc,V:abc,u:1,U:1,s:abc,f:1.0000,F:1.0000");
    
    SP_TRUE(istringcompare(s0, s1) == 0);
    
    irelease(s);
    irelease(s0);
    irelease(s1);
}

SP_CASE(istring, istringcompare) {
    istring * s0 = istringmake("aba");
    istring * s1 = istringmake("abb");
    istring * s2 = istringmake("abc");
    
    // s0 < s1 < s2
    SP_TRUE(istringcompare(s0, s1) < 0);
    SP_TRUE(istringcompare(s1, s2) < 0);
    SP_TRUE(istringcompare(s0, s2) < 0);
    
    SP_TRUE(istringcompare(kstring_empty, kstring_zero) > 0);
    SP_TRUE(istringcompare(kstring_zero, kstring_empty) < 0);
    SP_TRUE(istringcompare(kstring_zero, kstring_zero) == 0);
    SP_TRUE(istringcompare(kstring_empty, kstring_empty) == 0);
    
    irelease(s0);
    irelease(s1);
    irelease(s2);
}

SP_CASE(istring, istringfind) {
    /* 1-2-3-a-b-c- -1-2-3-  -a -b -c -d -  -1 -2 -3 -4 -  -a - */
    /* 0-1-2-3-4-5-6-7-8-9-10-11-12-13-14-15-16-17-18-19-20-21*/
    istring *s0 = istringmake("123abc 123 abcd 1234 a");
    int index = istringfind(s0, "123", 3, 0);
    SP_TRUE(index == 0);
    index = istringfind(s0, "1234", 4, 0);
    SP_TRUE(index == 16);
    index = istringfind(s0, "12345", 5, 0);
    SP_TRUE(index == kindex_invalid);
    
    irelease(s0);
}

SP_CASE(istring, istringsub) {
    istring *s0 = istringmake("0123");
    
    SP_TRUE(istringlen(s0) == 4);
    
    const char* sbuf = istringbuf(s0);
    SP_TRUE(sbuf[0] == '0');
    SP_TRUE(sbuf[1] == '1');
    SP_TRUE(sbuf[2] == '2');
    SP_TRUE(sbuf[3] == '3');
    SP_TRUE(sbuf[4] == 0);
    
    SP_TRUE(s0->array->entry == iarrayentryget(EnumArrayEntryType_Char));
    SP_TRUE(iflag_is(s0->flag, EnumSliceFlag_String));
    
    istring *s1 = istringsub(s0, 0, 0);
    SP_TRUE(istringlen(s1) == 0);
    SP_TRUE(s1 == kstring_empty);
    
    istring *s2 = istringsub(s0, 1, 0);
    SP_TRUE(istringlen(s2) == 0);
    SP_TRUE(s2 == kstring_empty);
    
    istring *s3 = istringsub(s0, 1, 2);
    SP_TRUE(istringlen(s3) == 1);
    SP_TRUE(istringbuf(s3)[0] == '1');
    SP_TRUE(istringbuf(s3)[1] == '2');
    
    irelease(s0);
    irelease(s1);
    irelease(s2);
    irelease(s3);
}

SP_CASE(istring, istringsplit) {
    istring *s0 = istringmake("0,11,222,3333");
    iarray *ss = istringsplit(s0, ",", 1);
    
    SP_TRUE(iarraylen(ss) == 4);
    
    istring *sx0d = istringmake("0");
    istring *sx0 = iarrayof(ss, istring*, 0);
    SP_TRUE(istringlen(sx0) == 1);
    SP_TRUE(istringcompare(sx0, sx0d)==0);
    
    istring *sx1d = istringmake("11");
    istring *sx1 = iarrayof(ss, istring*, 1);
    SP_TRUE(istringlen(sx1) == 2);
    SP_TRUE(istringcompare(sx1, sx1d)==0);
    
    istring *sx2d = istringmake("222");
    istring *sx2 = iarrayof(ss, istring*, 2);
    SP_TRUE(istringlen(sx2) == 3);
    SP_TRUE(istringcompare(sx2, sx2d)==0);
    
    istring *sx3d = istringmake("3333");
    istring *sx3 = iarrayof(ss, istring*, 3);
    SP_TRUE(istringlen(sx3) == 4);
    SP_TRUE(istringcompare(sx3, sx3d)==0);
    
    irelease(s0);
    irelease(ss);
    
    irelease(sx0d);
    irelease(sx1d);
    irelease(sx2d);
    irelease(sx3d);
}

SP_CASE(istring, istringjoin) {
    istring *s0 = istringmake("0,11,222,3333");
    iarray *ss = istringsplit(s0, ",", 1);
    
    SP_TRUE(iarraylen(ss) == 4);
    istring *sx = istringjoin(ss, ",", 1);
    SP_TRUE(istringcompare(s0, sx) == 0);
    SP_TRUE(istringbuf(sx)[istringlen(sx)] == 0);
 
    irelease(s0);
    irelease(sx);
    irelease(ss);
}

SP_CASE(istring, istringreplace) {
    istring *s0 = istringmake("0,11,222,3333");
    iarray *ss = istringsplit(s0, ",", 1);
    
    SP_TRUE(iarraylen(ss) == 4);
    istring *sx = istringjoin(ss, ":", 1);
    SP_TRUE(istringcompare(s0, sx) != 0);
    
    istring *snew = istringrepleace(s0, ",", 1, ":", 1);
    SP_TRUE(istringcompare(sx, snew) == 0);
    SP_TRUE(istringbuf(snew)[istringlen(snew)] == 0);
    
    irelease(s0);
    irelease(sx);
    irelease(ss);
    irelease(snew);
}

SP_CASE(istring, istringappend) {
    istring *s1 = istringmake("");
    istring *s2 = istringappend(s1, "--", 2);
    istring *s3 = istringappend(s2, "**", 2);
    SP_TRUE(istringbuf(s2)[0] == '-');
    SP_TRUE(istringbuf(s2)[1] == '-');
    SP_TRUE(istringbuf(s2)[2] == 0);
    
    SP_TRUE(istringbuf(s3)[0] == '-');
    SP_TRUE(istringbuf(s3)[1] == '-');
    SP_TRUE(istringbuf(s3)[2] == '*');
    SP_TRUE(istringbuf(s3)[3] == '*');
    SP_TRUE(istringbuf(s3)[4] == 0);
    
    irelease(s1);
    irelease(s2);
    irelease(s3);
}

SP_CASE(istring, istringatoi) {
    istring *s0 = istringmake("abc");
    istring *s1 = istringmake("-123");
    istring *s2 = istringmake("");
    
    SP_TRUE(istringatoi(s0) == 0);
    SP_TRUE(istringatoi(s1) == -123);
    SP_TRUE(istringatoi(s2) == 0);
    
    irelease(s0);
    irelease(s1);
    irelease(s2);
}

SP_CASE(istring, istringatof) {
    istring *s0 = istringmake("abc");
    istring *s1 = istringmake("-123");
    istring *s2 = istringmake("");
    istring *s3 = istringmake("-0.008f");
    
    SP_TRUE(istringatof(s0) == 0);
    SP_TRUE(istringatof(s1) == -123);
    SP_TRUE(istringatof(s2) == 0);
    double x = istringatof(s3);
    SP_TRUE(ireal_equal(x, -0.008f));
    
    irelease(s0);
    irelease(s1);
    irelease(s2);
    irelease(s3);
}

SP_CASE(istring, end) {
    SP_TRUE(1);
}