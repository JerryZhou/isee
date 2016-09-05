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

SP_CASE(istring, end) {
    SP_TRUE(1);
}