#include "foundation/util/ibase64.h"
#include "foundation/util/iarraytypes.h"

/* https://en.wikipedia.org/wiki/Base64 */

static void _ibase64init(ibase64encoding* encoding, const ibyte* bytes) {
    encoding->source = istringmake((const char*)bytes);
    for (int i=0; i<icountof(encoding->encodeMap); ++i) {
        encoding->encodeMap[i] = 0xFF;
    }
    for (int i=0; i<islicelen(encoding->source); ++i) {
        encoding->encodeMap[isliceof(encoding->source, ibyte, i)] = (ibyte)(i);
    }
}

/* RFC 1421 */
const ibase64encoding *ibase64Std() {
    static ibase64encoding _Std = {0};
    if (_Std.source) {
        _ibase64init(&_Std, (ibyte*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    }
    return &_Std;
}

const ibase64encoding *ibase64URL() {
    static ibase64encoding _URL = {0};
    if (_URL.source) {
        _ibase64init(&_URL, (ibyte*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
    }
    return &_URL;
}

/* encode the base64 */
islice* ibase64encode(const ibase64encoding *encoding, const islice* isrc) {
    /* make the room space for encode */
    size_t olen = islicelen(isrc);
    size_t encodelen = ibase64encodelen(olen);
    iarray *bytes = iarraymakeibyte(encodelen);
    bytes->len = encodelen;
    
    /* the padding byte */
    ibyte pad = '=';
    
    /* prepare the encode dst and read src*/
    islice* idst = isliceunique(bytes);
    islice* dst = islicemakeargby(idst, ":");
    islice* src = islicemakeargby((islice*)isrc, ":");
    
    for (; islicelen(src); ) {
        ibyte b[4] = {0};
        
        /* the encode */
        switch (islicelen(src)) {
            default:
                b[3] = (isliceof(src, ibyte, 2) & 0x3F);
                b[2] = (isliceof(src, ibyte, 2) >> 6);
            case 2:
                b[2] |= (isliceof(src, ibyte, 1) << 2) & 0x3F;
                b[1] = isliceof(src, ibyte, 1) >> 4;
            case 1:
                b[1] |= (isliceof(src, ibyte, 0) << 4) & 0x3F;
                b[0] = isliceof(src, ibyte, 0) >> 2;
                break;
        }
        
        /* the encode-result */
        isliceset(dst, 0, isliceat(encoding->source, b[0]));
        isliceset(dst, 1, isliceat(encoding->source, b[1]));
        isliceset(dst, 2, isliceat(encoding->source, b[2]));
        isliceset(dst, 3, isliceat(encoding->source, b[3]));
        
        /* the pading */
        if (islicelen(src) < 3) {
            isliceset(dst, 3, &pad);
            if (islicelen(src) < 2) {
                isliceset(dst, 2, &pad);
            }
            break;
        }
        
        /* next src and dst */
        src = isliceuniqueby(src, "3:");
        dst = isliceuniqueby(dst, "4:");
    }
    
    irefdelete(src);
    irefdelete(dst);
    
    return idst;
}

#define _ROut(_n, _end, _err) { rout->n = _n; rout->end = _end; rout->err = _err; }

// 内部解码
void ibase64decodedetails(const ibase64encoding *encoding, const islice*isrc, ibase64decodeout *rout) {
    /* the dest-buffer */
    size_t olen = islicelen(isrc);
    size_t decodeLen = ibase64decodelen(olen);
    iarray* arr = iarraymakeibyte(decodeLen);
    arr->len = decodeLen;
    
    /* the source */
    islice* idst = isliceunique(arr);
    islice* dst = islicedby((islice*)idst, 0, islicelen(idst));
    islice* src = islicedby((islice*)isrc, 0, islicelen(isrc));
    _ROut(0, false, 0); rout->dst = idst;
    
    for (; islicelen(src) && !rout->end; ) {
        ibyte dbuf[4];
        size_t dlen = 4;
        for (size_t j=0; j<icountof(dbuf); ++j) {
            if (islicelen(src) == 0) {
                _ROut(rout->n, false, -1);
                goto ret;
            }
            ibyte in = isliceof(src, ibyte, 0);
            src = isliceuniqueby(src, "1:");
            if (in == '=') {
                switch (j) {
                    case 0:
                    case 1:
                        _ROut(rout->n, false, olen - islicelen(src)-1); /*  */
                        goto ret;
                        break;
                    case 2:
                        /*except == */
                        if (islicelen(src) == 0) {
                            _ROut(rout->n, false, olen - islicelen(src) -1); /*  */
                            goto ret;
                        }
                        src = isliceuniqueby(src, "1:");
                    break;
                }
                if (islicelen(src) > 0) {
                    rout->err = olen - islicelen(src); /*  */
                }
                dlen = j;
                rout->end = iiok;
                break;
            }
            dbuf[j] = encoding->encodeMap[in];
            if (dbuf[j] == 0xFF) {
                _ROut(rout->n, false, olen - islicelen(src) -1); /*  */
                goto ret;
            }
        }
        
        ibyte* rdst = (ibyte*) isliceat(dst, 0);
        switch (dlen) {
            case 4:
                rdst[2] = dbuf[2] << 6 | dbuf[3];
            case 3:
                rdst[1] = dbuf[1] <<4 | dbuf[2] >> 2;
            case 2:
                rdst[0] = dbuf[0] <<2 | dbuf[1] >> 4;
                break;
        }
        dst = isliceuniqueby(dst, "3:");
        rout->n += dlen-1;
    }
    
ret:
    irefdelete(dst);
    irefdelete(src);
    rout->dst = idst;
}

/* decode the base64 */
islice* ibase64decode(const ibase64encoding *encoding, const islice* src) {
    ibase64decodeout out = {0};
    ibase64decodedetails(encoding, src, &out);
    if (out.err != 0) {
        irefdelete(out.dst);
    }
    return out.dst;
}

/* encode len 3 byte ==> 4 byte: (len+2)/3 * 4 */
size_t ibase64encodelen(size_t len) {
    return (len + 2)/3*4;
}

/* decode len 4 byte ==> 3 byte: len/4*3 */
size_t ibase64decodelen(size_t len) {
    return len/4*3;
}

