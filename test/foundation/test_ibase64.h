//
//  test_ibase64.h
//  isee
//
//  Created by jerry on 2017/3/28.
//
//

#ifndef test_ibase64_h
#define test_ibase64_h

#include "foundation/util/ibase64.h"

SP_SUIT(ibase64);

SP_CASE(ibase64, ibase64encode) {
    
    {
        /*a ==> YQ== */
        istring *s = istringmake("a");
        istring *s0 = ibase64encode(ibase64Std(), s);
        
        SP_TRUE(islicelen(s0) == 4);
        SP_TRUE(isliceof(s0, ibyte, 0) == 'Y');
        SP_TRUE(isliceof(s0, ibyte, 1) == 'Q');
        SP_TRUE(isliceof(s0, ibyte, 2) == '=');
        SP_TRUE(isliceof(s0, ibyte, 3) == '=');
        
        irefdelete(s);
        irefdelete(s0);
    }
    
    {
        /*ab ==> YWI= */
        istring *s = istringmake("ab");
        istring *s0 = ibase64encode(ibase64Std(), s);
        
        SP_TRUE(islicelen(s0) == 4);
        SP_TRUE(isliceof(s0, ibyte, 0) == 'Y');
        SP_TRUE(isliceof(s0, ibyte, 1) == 'W');
        SP_TRUE(isliceof(s0, ibyte, 2) == 'I');
        SP_TRUE(isliceof(s0, ibyte, 3) == '=');
        
        irefdelete(s);
        irefdelete(s0);
    }
    
    {
        /* abc ==> YWJj */
        istring *s = istringmake("abc");
        istring *s0 = ibase64encode(ibase64Std(), s);
        
        SP_TRUE(islicelen(s0) == 4);
        SP_TRUE(isliceof(s0, ibyte, 0) == 'Y');
        SP_TRUE(isliceof(s0, ibyte, 1) == 'W');
        SP_TRUE(isliceof(s0, ibyte, 2) == 'J');
        SP_TRUE(isliceof(s0, ibyte, 3) == 'j');
        
        irefdelete(s);
        irefdelete(s0);
    }
}

SP_CASE(ibase64, ibase64decodedetail) {
    {
        /* YQ==  ==> a */
        ibase64decodeout rout = {};
        istring *s = istringmake("YQ==");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 0);
        SP_TRUE(rout.n == 1);
        SP_TRUE(islicelen(rout.dst) == 1);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWI=  ==> ab */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWI=");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 0);
        SP_TRUE(rout.n == 2);
        SP_TRUE(islicelen(rout.dst) == 2);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    {
        /* YWJj ==> abc */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJj");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 0);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJjx ==> abc[err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJjx");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 4);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJjxx ==> abc[err][err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJjxx");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 4);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJj= ==> abc[err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJj=");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 4);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJj== ==> abc[err][err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJj==");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 4);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJjx= ==> abc[err][err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJjx=");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 5);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJjxx= ==> abc[err][err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJjxx=");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 7);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJjxx=x ==> abc[err][err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJjxx=x");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 7);
        SP_TRUE(rout.n == 3);
        SP_TRUE(islicelen(rout.dst) == 3);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }
    
    {
        /* YWJjYQ==x ==> abca[err] */
        ibase64decodeout rout = {};
        istring *s = istringmake("YWJjYQ==x");
        ibase64decodedetails(ibase64Std(), s, &rout);
        SP_TRUE(rout.err == 8);
        SP_TRUE(rout.n == 4);
        SP_TRUE(islicelen(rout.dst) == 4);
        SP_TRUE(isliceof(rout.dst, ibyte, 0) == 'a');
        SP_TRUE(isliceof(rout.dst, ibyte, 1) == 'b');
        SP_TRUE(isliceof(rout.dst, ibyte, 2) == 'c');
        SP_TRUE(isliceof(rout.dst, ibyte, 3) == 'a');
        
        irefdelete(rout.dst);
        irefdelete(s);
    }

}

SP_CASE(ibase64, end) {
    SP_TRUE(1);
}


#endif /* test_ibase64_h */
