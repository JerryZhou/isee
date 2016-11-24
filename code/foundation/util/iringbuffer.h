#ifndef _IRINGBUFFER_H_
#define _IRINGBUFFER_H_

#include "foundation/itype.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iref.h"
#include "foundation/util/iarraytypes.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif
/* ringbuffer control flags */
typedef enum EnumRingBufferFlag {
    EnumRingBufferFlag_BlockRead = 1,  /* Block Read Will Got What We Needed */
    EnumRingBufferFlag_BlockWrite = 1<<1, /* Block Write Util We Got Empty Spaces */
    
    EnumRingBufferFlag_Override = 1<<2,   /* Override The Ring Buffer */
    
    EnumRingBufferFlag_ReadChannelShut = 1<<3,
    EnumRingBufferFlag_WriteChannelShut = 1<<4,
    
    EnumRingBufferFlag_ReadSleep = 1<<5,
    EnumRingBufferFlag_WriteSleep = 1<<6,
}EnumRingBufferFlag;
    
/* the extern variable about size_t (-1) */
extern size_t ksize_invalid;

/* ring buffer */
/*[the ring buffer](https://github.com/JerryZhou/ringbuffer)*/
typedef struct iringbuffer {
    irefdeclare;
    
    /* char array */
    iarray *buf;
    /* the control flags */
    int flag;
    /* write cursor */
    size_t wcursor;
    /* read cursor */
    size_t rcursor;
    /* total write length */
    int64_t wlen;
    /* total read length */
    int64_t rlen;
} iringbuffer;
    
/* destructor */
void iringbuffer_destructor(const imeta* meta, iptr o);
    
/* Make a ring buffer */
iringbuffer *iringbuffermake(size_t capacity, int flag);

/* close the ring buffer: can not read and write */
void iringbufferclose(iringbuffer *r);

/* shutdown the ringbuffer, to forbid the ringbuffer behavior */
void iringbuffershut(iringbuffer *r, int channel);

/* write s to ringbuffer, return count of write */
size_t iringbufferwrite(iringbuffer *r, const char* s, size_t len);

/* read to dst, until read full of dst, return the realy readed count */
size_t iringbufferread(iringbuffer *r, char * dst, size_t len);

/* return the ready count of content */
size_t iringbufferready(iringbuffer *r);

/* giving the raw buffer address, unsafe behavior */
const char* iringbufferraw(iringbuffer *r);

/* Print to rb: support
 * %s(c null end string),
 * %i(signed int),
 * %I(signed 64 bit),
 * %u(unsigned int),
 * %U(unsigned 64bit) */
size_t iringbufferfmt(iringbuffer *rb, const char * fmt, ...);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _IRINGBUFFER_H_ */
