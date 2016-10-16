#include "foundation/util/iringbuffer.h"

SP_SUIT(iringbuffer);

SP_CASE(iringbuffer, iringbuffermake) {
    iringbuffer *rb = iringbuffermake(4, EnumRingBufferFlag_Override);
    
    SP_TRUE(iringbufferready(rb) == 0);
    
    SP_TRUE(iringbufferwrite(rb, "123", 3) == 3);
    SP_TRUE(iringbufferready(rb) == 3);
    
    irefdelete(rb);
}

SP_CASE(iringbuffer, iringbufferclose) {
    iringbuffer *rb = iringbuffermake(4, EnumRingBufferFlag_Override);
    SP_TRUE(iringbufferready(rb) == 0);
    
    iringbufferclose(rb);
    SP_TRUE(iringbufferwrite(rb, "123", 3) == ksize_invalid);
    SP_TRUE(iringbufferready(rb) == 0);
    
    irefdelete(rb);
}

SP_CASE(iringbuffer, iringbufferwrite) {
    iringbuffer *rb = iringbuffermake(4, EnumRingBufferFlag_Override);
    SP_TRUE(iringbufferready(rb) == 0);
    
    SP_TRUE(iringbufferwrite(rb, "1", 1) == 1);
    SP_TRUE(iringbufferready(rb) == 1);
    
    SP_TRUE(iringbufferwrite(rb, "23", 2) == 2);
    SP_TRUE(iringbufferready(rb) == 3);
    
    SP_TRUE(iringbufferwrite(rb, "45", 2) == 2);
    SP_TRUE(iringbufferready(rb) == 5);
    
    const char* raw = iringbufferraw(rb);
    SP_TRUE(raw[0] == '5');
    SP_TRUE(raw[1] == '2');
    SP_TRUE(raw[2] == '3');
    SP_TRUE(raw[3] == '4');
    
    irefdelete(rb);
}

SP_CASE(iringbuffer, iringbufferread) {
    iringbuffer *rb = iringbuffermake(4, EnumRingBufferFlag_Override);
    SP_TRUE(iringbufferready(rb) == 0);
    
    char buf[6] = {0};
    SP_TRUE(iringbufferwrite(rb, "12345", 5) == 5);
    
    SP_TRUE(iringbufferread(rb, buf, 6) == 6);
    SP_TRUE(buf[0] == '5');
    SP_TRUE(buf[1] == '2');
    SP_TRUE(buf[2] == '3');
    SP_TRUE(buf[3] == '4');
    SP_TRUE(buf[4] == '5');
    SP_TRUE(buf[5] == '2');
    
    irefdelete(rb);
}

SP_CASE(iringbuffer, iringbufferfmt) {
    iringbuffer *rb = iringbuffermake(512, 0);
    
    iringbufferfmt(rb, "%i-%I-%s-%S-%u-%U", (int)1, (int64_t)1, "1", "1", (unsigned int)1, (uint64_t)1);
    
    char bufvalue[] = "1-1-1-1-1-1";
    char buf[512] = {0};
    
    SP_TRUE(iringbufferread(rb, buf, 512) == 11);
    SP_TRUE(strncmp(bufvalue, buf, 11) == 0);
    
    irefdelete(rb);
}

SP_CASE(iringbuffer, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}