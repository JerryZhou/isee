#include "foundation/util/iringbuffer.h"
#include "foundation/util/istring.h"
#include "foundation/platform/iplatform.h"

/* the extern variable about size_t (-1) */
size_t ksize_invalid = -1;

/* destructor */
void iringbuffer_destructor(iptr x, iptr o) {
    iringbuffer *r = icast(iringbuffer, o);
    irefdelete(r->buf);
}

/* Make a ring buffer */
iringbuffer *iringbuffermake(size_t capacity, int flag) {
    iringbuffer *r = irefnew(iringbuffer);
    r->buf = iarraymakechar(capacity+1);
    r->buf->len = capacity;
    r->flag = flag;
    
    return r;
}

/* close the ring buffer: can not read and write */
void iringbufferclose(iringbuffer *r) {
    r->flag |= EnumRingBufferFlag_ReadChannelShut;
    r->flag |= EnumRingBufferFlag_WriteChannelShut;
}

/* shutdown the ringbuffer, to forbid the ringbuffer behavior */
void iringbuffershut(iringbuffer *r, int channel) {
    r->flag |= channel;
}

/* write s to ringbuffer, return count of write */
size_t iringbufferwrite(iringbuffer *rb, const char* s, size_t length) {
    size_t empty;
    size_t write;
    size_t finish = 0;
    size_t content;
    size_t capacity = iarraycapacity(rb->buf)-1;
    
    /* write to shut down rb */
    if (rb->flag & EnumRingBufferFlag_WriteChannelShut) {
        return ksize_invalid;
    }
    
    if (finish < length) do {
        /* should break when got shut down */
        if (rb->flag & EnumRingBufferFlag_WriteChannelShut) {
            break;
        }
        /* current content size */
        content = rb->wlen - rb->rlen;
        
        /* overide buffer */
        if (rb->flag & EnumRingBufferFlag_Override) {
            empty = length - finish;
        } else {
            empty = imin(capacity - content, length - finish);
        }
        
        /* no space continue */
        if (empty == 0) {
            /* the write channel have been shutdown */
            if (rb->flag & EnumRingBufferFlag_WriteChannelShut) {
                break;
            }
            /* not block mode, will return right now */
            if (!(rb->flag & EnumRingBufferFlag_BlockWrite)) {
                break;
            }
            /* need sleep */
            if (rb->flag & EnumRingBufferFlag_WriteSleep) {
                isleep(0);
            }
            /* can be dynamic resize the space */
            continue;
        }
        
        /* write data */
        if (empty > 0) do {
            write = capacity - rb->wcursor;
            write = imin(write, empty);
            
            memcpy(rb->buf->buffer + rb->wcursor, s + finish, write);
            rb->wcursor += write;
            rb->wlen += write;
            if (rb->wcursor >= capacity) {
                rb->wcursor = 0;
            }
            
            finish += write;
            empty -= write;
        } while(empty > 0);
        
    } while(finish < length && (rb->flag & EnumRingBufferFlag_BlockWrite));
    
    return finish;
}

/* read to dst, until read full of dst, return the realy readed count */
size_t iringbufferread(iringbuffer *rb, char * dst, size_t length) {
    size_t full;
    size_t read;
    size_t finish = 0;
    size_t capacity = iarraycapacity(rb->buf)-1;
    
    /* read to shut down rb */
    if (rb->flag & EnumRingBufferFlag_ReadChannelShut) {
        return ksize_invalid;
    }
    
    if (finish < length) do {
        /* read to shut down rb */
        if (rb->flag & EnumRingBufferFlag_ReadChannelShut) {
            break;
        }
        
        /* read override it */
        if (rb->flag & EnumRingBufferFlag_Override) {
            full = length - finish;
        } else {
            full = imin((rb->wlen - rb->rlen), length - finish);
        }
        
        /* no content continue */
        if (full == 0) {
            /* the read channel have been shutdown */
            if (rb->flag & EnumRingBufferFlag_ReadChannelShut) {
                break;
            }
            /* the read operating is not block, will return right now */
            if (!(rb->flag & EnumRingBufferFlag_BlockRead)) {
                break;
            }
            /* need sleep */
            if (rb->flag & EnumRingBufferFlag_ReadSleep) {
                isleep(0);
            }
            /* can be dynamic resize the space */
            continue;
        }
        
        /* read data */
        if (full > 0) do {
            read = capacity - rb->rcursor;
            read = imin(read, full);
            
            memcpy(dst + finish, rb->buf->buffer + rb->rcursor, read);
            rb->rcursor += read;
            rb->rlen += read;
            if (rb->rcursor >= capacity) {
                rb->rcursor = 0;
            }
            
            finish += read;
            full -= read;
        } while(full > 0);
        
    } while(finish < length && (rb->flag & EnumRingBufferFlag_BlockRead));
    
    return finish;
}

/* return the ready count of content */
size_t iringbufferready(iringbuffer *r) {
    return r->wlen - r->rlen;
}

/* giving the raw buffer address, unsafe behavior */
const char* iringbufferraw(iringbuffer *r) {
    return (const char*)iarraybuffer(r->buf);
}

/* Print to rb: support
 * %s(c null end string),
 * %i(signed int),
 * %I(signed 64 bit),
 * %u(unsigned int),
 * %U(unsigned 64bit) */
size_t iringbufferfmt(iringbuffer *rb, const char * fmt, ...) {
    const char *f = fmt;
    size_t i;
    va_list ap;
    
    char next, *str;
    size_t l;
    int64_t num;
    uint64_t unum;
    
    char buf[256];
    
    va_start(ap,fmt);
    f = fmt;    /* Next format specifier byte to process. */
    i = 0;
    while(*f) {
        
        /* Make sure there is always space for at least 1 char. */
        switch(*f) {
            case '%':
                next = *(f+1);
                f++;
                switch(next) {
                    case 's':
                    case 'S':
                        str = va_arg(ap,char*);
                        l = strlen(str);/*(next == 's') ?  : sdslen(str); */
                        iringbufferwrite(rb, str, l);
                        i += l;
                        break;
                    case 'i':
                    case 'I':
                        if (next == 'i')
                            num = va_arg(ap,int);
                        else
                            num = va_arg(ap,int64_t);
                    {
                        l = ill2string(buf,num);
                        iringbufferwrite(rb, buf, l);
                        i += l;
                    }
                        break;
                    case 'u':
                    case 'U':
                        if (next == 'u')
                            unum = va_arg(ap,unsigned int);
                        else
                            unum = va_arg(ap,uint64_t);
                    {
                        l = iull2string(buf,unum);
                        iringbufferwrite(rb, buf, l);
                        i += l;
                    }
                        break;
                    default: /* Handle %% and generally %<unknown>. */
                        iringbufferwrite(rb, f, 1);
                        break;
                }
                break;
            default:
                iringbufferwrite(rb, f, 1);
                break;
        }
        f++;
    }
    va_end(ap);
    
    return i;
}
