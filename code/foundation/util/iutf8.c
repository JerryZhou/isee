#include "foundation/util/iutf8.h"

/*
 UTF-8: 8-bit Unicode Transformation Format
 */
typedef enum iutfconst{
    iRuneSelf = 0x0000007F,
    iRuneMax =  0x0010FFFF,
    iRuneErr =  0x0000FFFD,
    iUtf8Len = 4,
    
    iSurrogateMin = 0xD800,
    iSurrogateMax = 0xDFFF,
    
    iT1 = 0x00, /* 0000 0000 */
    iTx = 0x80, /* 1000 0000 */
    iT2 = 0xC0, /* 1100 0000 */
    iT3 = 0xE0, /* 1110 0000 */
    iT4 = 0xF0, /* 1111 0000 */
    iT5 = 0xF8, /* 1111 1000 */
    
    imaskx = 0x3F, /* 0011 1111 */
    imask2 = 0x1F, /* 0001 1111 */
    imask3 = 0x0F, /* 0000 1111 */
    imask4 = 0x07, /* 0000 0111 */
    
    iRune1Max = (1<<(7))-1,                 /* 1<<7-1     (128): 0x0000 - 0x007F */
    iRune2Max = (1<<(5+6))-1,               /* 1<<11-1   (1920): 0x0080 - 0x07FF */
    iRune3Max = (1<<(4+6+6))-1,             /* 1<<16-1  (61440): 0x0800 - 0xFFFF */
    /* 000800 - 00D7FF , 00E000 - 00FFFF 
     Unicode在范围D800-DFFF中不存在任何字符，基本多文种平面中约定了这个范围用于UTF-16扩展标识辅助平面
     （两个UTF-16表示一个辅助平面字符）*/
    iRune4Max = (1<<(3+6+6+6))-1,           /* 1<<21-1(1048576): 0x10000 - 0x1FFFFF */
    /* 2003年11月UTF-8被RFC 3629重新规范，只能使用原来Unicode定义的区域，U+0000到U+10FFFF */
    iRune5Max = (1<<(2+6+6+6+6))-1,         /* 1<<26-1         : 0x200000 - 0x3FFFFFF */
    iRune6Max = (1<<(1+6+6+6+6+6))-1,       /* 1<<31-1         : 0x4000000- 0x7FFFFFFF */
} iutfconst;

/*
 * the multiple bytes start as: 110xxxxx or 1110xxxx or 11110xxx
 * the subsequent byte is 10xxxxxx
 */
static ibool _irunestart(ibyte b) {
    return (b & 0xC0) != 0x80;
}

#define _ROut(_rune, _size, _need) do { rout->rune = _rune; rout->len = _size; rout->need = _need; return ; } while(0)

/* decoder */
void iutf8decode(const islice* bytes, iutf8decodeout* rout) {
    size_t len = islicelen(bytes);
    if (len < 1) {
        _ROut(iRuneErr, 0, iiok);
    }
    
    /* 0x0000 - 0x007F */
    ibyte c0 = isliceof(bytes, ibyte, 0);
    if (c0 < iTx) {
        _ROut(c0, 1, iino);
    }
    
    /* unexcepted bytes, multiple bytes: 
     should be 10xxxxxx or 110xxxxx or 1110xxxx or 11110xxx */
    if (c0 < iT2) {
        _ROut(iRuneErr, 1, iino);
    }
    
    /* need more bytes */
    if (len < 2) {
        _ROut(iRuneErr, 1, iiyes);
    }
    ibyte c1 = isliceof(bytes, ibyte, 1);
    /* the second byte should be: 10xxxxxx */
    if (c1 < iTx || c1 >= iT2) {
        _ROut(iRuneErr, 1, iino);
    }
    
    /* two bytes code : 110xxxxx, 10xxxxxx */
    if (c0 < iT3) {
        irune rune = ((irune)(c0&imask2))<<6 | ((irune)(c1&imaskx));
        if (rune <= iRune1Max) {
            _ROut(iRuneErr, 1, iino);
        }
        _ROut(iRuneErr, 2, iino);
    }
    /* least 3 bytes needed */
    if (len < 3) {
        _ROut(iRuneErr, 1, iiyes);
    }
    
    ibyte c2 = isliceof(bytes, ibyte, 2);
    /* the third byte should be: 10xxxxxx */
    if (c2 < iTx || c2 >= iT2) {
        _ROut(iRuneErr, 1, iino);
    }
    
    /* three bytes code : 1110xxxx, 10xxxxxx, 10xxxxxx */
    if (c0 < iT4) {
        irune rune = ((irune)(c0&imask3))<<12 | ((irune)(c1&imaskx))<<6 | ((irune)(c2&imaskx));
        if (rune <= iRune2Max) {
            _ROut(iRuneErr, 1, iino);
        }
        if (rune >= iSurrogateMin && rune <= iSurrogateMax) {
            _ROut(iRuneErr, 1, iino);
        }
        _ROut(rune, 3, iino);
    }
    
    /* least 4 bytes needed */
    if (len < 4) {
        _ROut(iRuneErr, 1, iiyes);
    }
    ibyte c3 = isliceof(bytes, ibyte, 3);
    /* the fourth byte should be: 10xxxxxx */
    if (c3 < iTx || c3 >= iT2) {
        _ROut(iRuneErr, 1, iino);
    }
    
    /* the 4 bytes code : 11110xxx, 10xxxxxx, 10xxxxxx, 10xxxxxx */
    if (c0 < iT5) {
        irune rune = ((irune)(c0&imask4))<<18 | ((irune)(c1&imaskx))<<12 |
            ((irune)(c2&imaskx))<<6 | ((irune)(c3&imaskx));
        if (rune <= iRune3Max || rune > iRuneMax) {
            _ROut(iRuneErr, 1, iino);
        }
        _ROut(rune, 4, iino);
    }
    
    /* the RFC 3629, utf8 only focus in 21 bit sequence unicode */
    _ROut(iRuneErr, 1, iino);
}
    
/* decoding the last rune in bytes */
void iutf8decodelast(const islice* bytes, iutf8decodeout* rout) {
    size_t end = islicelen(bytes);
    if (end == 0) {
        _ROut(iRuneErr, 0, iino);
    }
    int start = (int)(end - 1);
    ibyte c = isliceof(bytes, ibyte, start);
    if (c < iRuneSelf) {
        _ROut(c, 1, iino);
    }
    /* guard the full-length of invalid utf8-bytes */
    int limit = 0;
    if (end > iUtf8Len) {
        limit = iUtf8Len;
    }
    
    /* find the last start byte */
    for (start--;start>=limit;start--) {
        c = isliceof(bytes, ibyte, start);
        if (_irunestart(c)) {
            break;
        }
    }
    if (start<0) {
        start = 0;
    }
    
    /* try decode */
    islice* temp = islicedby((islice*)bytes, start, end);
    iutf8decode(temp, rout);
    irefdelete(temp);
    if (rout->len + start != end) {
        /* may be the invalid start point */
        _ROut(iRuneErr, 1, iino);
    }
}

/* encoder */
void iutf8encode(const irune rune, iutf8encodeout* rout) {
    /* http://stackoverflow.com/questions/4607413/c-library-to-convert-unicode-code-points-to-utf8/4609989#4609989 
     * if (c<0x80) *b++=c;
     * else if (c<0x800) *b++=192+c/64, *b++=128+c%64;
     * else if (c-0xd800u<0x800) goto error;
     * else if (c<0x10000) *b++=224+c/4096, *b++=128+c/64%64, *b++=128+c%64;
     * else if (c<0x110000) *b++=240+c/262144, *b++=128+c/4096%64, *b++=128+c/64%64, *b++=128+c%64;
     * else goto error;
     * */

    if (rune < iRune1Max) {
        rout->utf8[0] = (ibyte)(rune);
        rout->len = 1;
        return;
    }
    if (rune < iRune2Max) {
        rout->utf8[0] = iT2 | ((ibyte)(rune>>6));
        rout->utf8[1] = iTx | ((ibyte)(rune&imaskx));
        rout->len = 2;
        return;
    }
    if (rune>iRuneMax || (rune>=iSurrogateMin && rune<=iSurrogateMax)) {
        rout->len = 0;
        return;
    }
    if (rune < iRune3Max) {
        rout->utf8[0] = iT3 | ((ibyte)(rune>>12));
        rout->utf8[1] = iTx | ((ibyte)((rune>>6)&imaskx));
        rout->utf8[2] = iTx | ((ibyte)(rune&imaskx));
        rout->len = 3;
        return;
    }
    rout->utf8[0] = iT4 | ((ibyte)(rune>>18));
    rout->utf8[1] = iTx | ((ibyte)((rune>>12)&imaskx));
    rout->utf8[2] = iTx | ((ibyte)((rune>>6)&imaskx));
    rout->utf8[3] = iTx | ((ibyte)(rune&imaskx));
    rout->len = 4;
    return;
}


/* the rune count in bytes */
size_t irunecount(const islice* bytes) {
    size_t count = 0;
    size_t i = 0;
    size_t len = islicelen(bytes);
    ibyte b = 0;
    for (; i<len; ++count) {
        b = isliceof(bytes, ibyte, i);
        if (b < iRuneSelf) {
            ++i;
        }  else {
            iutf8decodeout out = {0};
            islice *temp = islicedby((islice*)bytes, i, len);
            iutf8decode(temp, &out);
            irefdelete(temp);
            i += out.len;
        }
    }
    return count;
}
 
/* is the right encoded in utf8 */
ibool iutf8valid(const islice* bytes) {
    size_t count = 0;
    size_t i = 0;
    size_t len = islicelen(bytes);
    ibyte b = 0;
    for (; i<len; ++count) {
        b = isliceof(bytes, ibyte, i);
        if (b < iRuneSelf) {
            ++i;
        }  else {
            iutf8decodeout out = {0};
            islice *temp = islicedby((islice*)bytes, i, len);
            iutf8decode(temp, &out);
            irefdelete(temp);
            if (out.len == 1) {
                return false;
            }
            i += out.len;
        }
    }
    return true;
}

/* if the rune is valid */
ibool irunevalid(const irune rune) {
    if (rune > iRuneMax) {
        return iino;
    }
    if (rune>=iSurrogateMin && rune<=iSurrogateMax) {
        return iino;
    }
    return iiok;
}

/* the utf8-encoded lenght */
size_t irunelen(const irune rune) {
    if (rune<=iRune1Max) {
        return 1;
    }
    if (rune<=iRune2Max) {
        return 2;
    }
    if (irunevalid(rune) == iino) {
        return -1;
    }
    if (rune<=iRune3Max) {
        return 3;
    }
    return 4;
}
