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

SP_CASE(ibase64, end) {
    SP_TRUE(1);
}


#endif /* test_ibase64_h */
