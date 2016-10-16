#include "foundation/util/iradix.h"

SP_SUIT(iradixunit);

const iradixunit _allsizes[] = {
    {"Bytes", 1024},
    {"Kb", 1024},
    {"Mb", 1024},
    {"Gb", 1024},
    {"Tb", 1024},
    {"Pb", 1024},
    {"Eb", 1024},
    {"Zb", 1024},
    {"Yb", 1024}};

const iradixunit _alltimes[] = {
    //{"nano", 1000},
    //{"micro", 1000},
    {"millis", 1000},
    {"secs", 60},
    {"minutes", 60},
    {"hour", 24},
    {"day", 30},
    {"month", 12},
    {"year", 365}};

const char* _alltimessuffixs[] = {"前", "现在", "后"};
const char* _alltimessuffixs_en[] = {" before", " now", " after"};

SP_CASE(iradixunit, iradixcalc) {
    iarray *arr = iarraymakecopyable(0, sizeof(iradixunit));
    iarrayappend(arr, _allsizes, icountof(_allsizes));
    {
        iarray *sizes = iradixcalc(arr, 1024, 5);
        istring *s = iradixcalccompose(arr, sizes);
        ideclarestring(kb, "1Kb");
        istringlaw(kb);
        SP_TRUE(istringcompare(kb, s) == 0);
        
        irelease(s);
        irelease(sizes);
    }
    {
        iarray *sizes = iradixcalc(arr, 2*1024 + 50, 5);
        istring *s = iradixcalccompose(arr, sizes);
        ideclarestring(kb, "2Kb50Bytes");
        istringlaw(kb);
        SP_TRUE(istringcompare(kb, s) == 0);
        
        irelease(s);
        irelease(sizes);
    }
    
    irelease(arr);
}

SP_CASE(iradixunit, iradixdiff) {
    iarray *arr = iarraymakecopyable(0, sizeof(iradixunit));
    iarrayappend(arr, _alltimes, icountof(_alltimes));
    iarray *suffixs = iarraymakeiref(5);
    for (int i=0; i<icountof(_alltimessuffixs); ++i) {
        istring *s = istringmake(_alltimessuffixs_en[i]);
        iarrayadd(suffixs, &s);
        irelease(s);
    }
    
    {
        iarray *sizes = iradixdiff(arr, 1000, 1016, 5);
        SP_TRUE(iarraylen(sizes)==2);
        SP_TRUE(iarrayof(sizes, uint64_t, 0)==16);
        SP_TRUE(iarrayof(sizes, uint64_t, 1)==uint64_t(0));
        
        istring *s = iradixdiffcompose(arr, sizes, suffixs);
        ideclarestring(tb, "16millis before");
        istringlaw(tb);
        SP_TRUE(istringcompare(tb, s) == 0);
        
        irelease(sizes);
        irelease(s);
    }
    
    {
        iarray *sizes = iradixdiff(arr, 1000 * 38 + 16 + 1000, 1000, 5);
        SP_TRUE(iarraylen(sizes)==3);
        SP_TRUE(iarrayof(sizes, uint64_t, 0)==16);
        SP_TRUE(iarrayof(sizes, uint64_t, 1)==uint64_t(38));
        SP_TRUE(iarrayof(sizes, uint64_t, 2)==uint64_t(2));
        
        istring *s = iradixdiffcompose(arr, sizes, suffixs);
        ideclarestring(tb, "38secs16millis after");
        istringlaw(tb);
        SP_TRUE(istringcompare(tb, s) == 0);
        
        irelease(sizes);
        irelease(s);
    }
    
    irelease(arr);
    irelease(suffixs);
}

SP_CASE(iradixunit, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}