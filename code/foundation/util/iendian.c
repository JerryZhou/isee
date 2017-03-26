#include "foundation/util/iendian.h"

/* https://en.wikipedia.org/wiki/Endianness */

/* check big endian */
ibool iendianbig() {
    /* 大端序（英：big-endian）或称大尾序 */
    /* 最高位字节存储在最低的内存地址处 */
    union {
        int i;
        ibyte b[4];
    } a = {.i=1};
    return a.b[0] == 0;
}

/* check little endian */
ibool iendianlittle() {
    /* 小端序（英：little-endian）或称小尾序 */
    /* 最低位字节是存储在最低的内存地址处 */
    union {
        int i;
        ibyte b[4];
    } a = {.i=1};
    return a.b[0] == 1;
}

#define __iswapbyte(b0, b1) {ibyte b = b0; b0 = b1; b1 = b;}

/* the edndian swapping */
void iendianswapi16(int16_t *i16) {
    ibyte *bb = (ibyte*)i16;
    __iswapbyte(bb[0], bb[1]);
}

void iendianswapi32(int32_t *i) {
    ibyte *bb = (ibyte*)i;
    __iswapbyte(bb[0], bb[3]);
    __iswapbyte(bb[1], bb[2]);
}

void iendianswapi64(int64_t *i64) {
    ibyte *bb = (ibyte*)i64;
    __iswapbyte(bb[0], bb[7]);
    __iswapbyte(bb[1], bb[6]);
    __iswapbyte(bb[2], bb[5]);
    __iswapbyte(bb[3], bb[4]);
}
