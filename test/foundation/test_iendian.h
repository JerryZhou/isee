//
//  test_iendian.h
//  isee
//
//  Created by jerry on 2017/3/26.
//
//

#ifndef test_iendian_h
#define test_iendian_h

#include "foundation/util/iendian.h"

SP_SUIT(iendian);

SP_CASE(iendian, iendianbig) {
    /* the most intels, amds are little endian */
    SP_TRUE(iendianlittle());
}

SP_CASE(iendian, iendianlittle) {
    SP_TRUE(!iendianbig());
}

SP_CASE(iendian, iendianswap16) {
    int16_t a = 1 | 2 << 8;
    int64_t b = 2 | 1 << 8;
    iendianswapi16(&a);
    SP_TRUE(a == b);
}

SP_CASE(iendian, iendianswap32) {
    int32_t a = 1 | 2 << 8 | 3 << 16 | 4 <<24;
    int32_t b = 4 | 3 << 8 | 2 << 16 | 1 <<24;
    iendianswapi32(&a);
    SP_TRUE(a == b);
}

SP_CASE(iendian, iendianswap64) {
    int64_t i[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int64_t a = i[1] | i[2]<<8 | i[3]<<16 | i[4]<<24 | i[5]<<32 | i[6]<<40 | i[7]<<48 | i[8]<<56;
    int64_t b = i[8] | i[7]<<8 | i[6]<<16 | i[5]<<24 | i[4]<<32 | i[3]<<40 | i[2]<<48 | i[1]<<56;
    iendianswapi64(&a);
    SP_TRUE(a == b);
}

SP_CASE(iendian, end) {
    SP_TRUE(1);
}


#endif /* test_iendian_h */
