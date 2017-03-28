#ifndef _IBASE64_H_
#define _IBASE64_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
#include "foundation/util/istring.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* the base64 encoding-map */
typedef struct ibase64encoding {
    istring *source;
    ibyte encodeMap[256];
} ibase64encoding;
    
/* the decoding out */
typedef struct ibase64decodeout {
    size_t n;
    ibool end;
    int err;
    islice* dst;
} ibase64decodeout;

/* RFC 1421 */
const ibase64encoding *ibase64Std();
const ibase64encoding *ibase64URL();

/* encode the base64 */
islice* ibase64encode(const ibase64encoding *encoding, const islice* src);
    
/* decode the base64 with returning the details-result */
void ibase64decodedetails(const ibase64encoding *encoding, const islice*isrc, ibase64decodeout *rout);
    
/* decode the base64 */
islice* ibase64decode(const ibase64encoding *encoding, const islice* src);
    
/* encode len 3 byte ==> 4 byte: (len+2)/3 * 4 */
size_t ibase64encodelen(size_t len);

/* decode len 4 byte ==> 3 byte: len/4*3 */
size_t ibase64decodelen(size_t len);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IBASE64_H_ */
