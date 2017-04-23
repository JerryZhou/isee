#ifndef _IUTF8_H_
#define _IUTF8_H_
	
#include "foundation/itype.h"
#include "foundation/core/iref.h"
#include "foundation/container/islice.h"
	
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
    
   
/* the little endian in irune */
/* https://zh.wikipedia.org/wiki/UTF-8 */
typedef struct iutf8decodeout {
    ibyte len;      /* 1, 2, 3, 4*/
    irune rune;     /* the unicode */
    ibyte need;     /* the decode result*/
} iutf8decodeout;
     
typedef struct iutf8encodeout {
    ibyte len;      /* 1, 2, 3, 4*/
    ibyte utf8[4];  /* the utf8 encoded */
} iutf8encodeout;
  
/* decoder */
void iutf8decode(const islice* bytes, iutf8decodeout* rout);
    
/* decoding the last rune in bytes */
void iutf8decodelast(const islice* bytes, iutf8decodeout* rout);
   
/* encoding the rune to utf8 */
void iutf8encode(const irune rune, iutf8encodeout* rout);
   
/* is the right encoded in utf8 */
ibool iutf8valid(const islice* bytes);
    
/* the rune count in bytes */
size_t irunecount(const islice* bytes);
 
/* if the rune is valid */
ibool irunevalid(const irune rune);

/* the utf8-encoded lenght */
size_t irunelen(const irune rune);
 
/* convertint the fullwidth to halfwidth, only support ascii */
irune irunehalfwidth(const irune rune);

/* convertint the halfwidth to fullwidth, only support ascii */
irune irunefullwidth(const irune rune);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IUTF8_H_ */
