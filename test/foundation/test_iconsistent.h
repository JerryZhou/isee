#include "foundation/algorithm/iconsistent.h"

SP_SUIT(iconsistent);

SP_CASE(iconsistent, make) {
    iconsistent *c = iconsistentmake(20, 2);
    SP_TRUE(iconsistentsize(c) == 0);
    irefdelete(c);
}

static void _i_test_log_consistent(const iconsistent *c) {
    size_t count = iconsistentcount(c);
    ilog("\n");
    for (int i=0; i<count; ++i) {
        uint64_t code = iconsistentcodeat(c, i);
        istring *svalue = iconsistentvalueat(c, i);
        ilog("%llu(%s)%s", code, istringbuf(svalue), i!=count-1?"==>\n":"");
    }
    
    ilog("\n");
}

SP_CASE(iconsistent, iconsistentaddANDremoveANDsize) {
    iconsistent *c = iconsistentmake(20, 2);
    SP_TRUE(iconsistentsize(c) == 0);
    
    istring *key0 = istringmake("0");
    
    iconsistentadd(c, key0);
    SP_TRUE(iconsistentsize(c) == 1);
    SP_TRUE(iconsistentcount(c) == 2);
    
    iconsistentremove(c, key0);
    SP_TRUE(iconsistentsize(c) == 0);
    
    istring *key1 = istringmake("1");
    iarray *keys = iarraymakeiref(5);
    iarrayadd(keys, &key0);
    iarrayadd(keys, &key1);
    iconsistentset(c, keys);
    SP_TRUE(iconsistentsize(c) == 2);
    SP_TRUE(iconsistentcount(c) == 4);
    
    istring* key2 = istringmake("2");
    iconsistentadd(c, key2);
    SP_TRUE(iconsistentsize(c) == 3);
    SP_TRUE(iconsistentcount(c) == 6);
    
    istring *key3 = istringmake("3");
    iarrayadd(keys, &key3);
    iconsistentset(c, keys);
    SP_TRUE(iconsistentsize(c) == 3);
    SP_TRUE(iconsistentcount(c) == 6);
    
    _i_test_log_consistent(c);
    /*
     5251092334357796901(1|@@[0])==>
     10883064650890462037(0|@@[1])==>
     1583063878606045400(1|@@[1])==>
     8695347472642594371(3|@@[0])==>
     9877205026647883141(3|@@[1])==>
     1651995473600541432(0|@@[0])
     */
    
    irefdelete(key0);
    irefdelete(key1);
    irefdelete(key2);
    irefdelete(key3);
    irefdelete(keys);
    irefdelete(c);
}

SP_CASE(iconsistent, iconsistentindexingof) {
    iconsistent *c = iconsistentmake(20, 2);
    SP_TRUE(iconsistentsize(c) == 0);
    
    istring *key0 = istringmake("0");
    iconsistentadd(c, key0);
    _i_test_log_consistent(c);
    
    istring *key1 = istringmake("1");
    iconsistentadd(c, key1);
    _i_test_log_consistent(c);
    
    istring *key2 = istringmake("2");
    iconsistentadd(c, key2);
    _i_test_log_consistent(c);
    
    SP_TRUE(iconsistentsize(c) == 3);
    SP_TRUE(iconsistentcount(c) == 6);
    _i_test_log_consistent(c);
    
    /*
     1067005182627833177(2|@@[0])==>
     5251092334357796901(1|@@[0])==>
     10883064650890462037(0|@@[1])==>
     1583063878606045400(1|@@[1])==>
     18185625803458238043(2|@@[1])==>
     1651995473600541432(0|@@[0])
     
     md5sum("123") = 6559309979213966368
     md5sum("xyz") = 8716735811002003409
     md5sum("000@@[1]") = 13830845673527567555
     md5sum("000@@11") = 105462549998873386
     */
    
    /*
     168753921(2|@@[1])==>
     296086648(2|@@[0])==>
     475895099(0|@@[0])==>
     703306102(1|@@[0])==>
     1174443678(0|@@[1])==>
     2030115139(1|@@[1])
     
     md5sum("123") =415752058
     md5sum("xyz") =1638109669
     md5sum("000@@[1]") =1908274814
     md5sum("000@@11") =1756857964
     */
    {
        istring *skey = istringmake("2|@@[1]");
        int index = iconsistentindexing(c, skey);
        SP_TRUE(index == 1);
        irefdelete(skey);
    }
    {
        istring *skey = istringmake("0|@@[0]");
        int index = iconsistentindexing(c, skey);
        SP_TRUE(index == 3);
        irefdelete(skey);
    }
    {
        istring *skey = istringmake("1|@@[1]");
        int index = iconsistentindexing(c, skey);
        SP_TRUE(index == 0);
        irefdelete(skey);
    }
    {
        istring *skey = istringmake("123");
        int index = iconsistentindexing(c, skey);
        SP_TRUE(index == 2);
        irefdelete(skey);
    }
    {
        istring *skey = istringmake("000@@[1]");
        int index = iconsistentindexing(c, skey);
        SP_TRUE(index == 5);
        irefdelete(skey);
    }
    
    {
        istring *skey = istringmake("000@@[1]");
        iarray * srange = iconsistentsearch(c, skey, 2);
        SP_TRUE(iarraylen(srange) == 2);
        
        istring *srkey0 = iarrayof(srange, istring*, 0);
        istring *srkey1 = iarrayof(srange, istring*, 1);
        
        istring *sxkey0 = istringmake("1");
        istring *sxkey1 = istringmake("2");
        
        SP_TRUE(istringcompare(srkey0, sxkey0) == 0);
        SP_TRUE(istringcompare(srkey1, sxkey1) == 0);
        
        irefdelete(sxkey0);
        irefdelete(sxkey1);
        
        irefdelete(srange);
        irefdelete(skey);
    }
    
    irefdelete(key0);
    irefdelete(key1);
    irefdelete(key2);
    irefdelete(c);
}

SP_CASE(iconsistent, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
