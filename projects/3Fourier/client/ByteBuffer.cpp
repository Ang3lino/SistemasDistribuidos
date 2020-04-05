#include "ByteBuffer.h"


ByteBuffer::ByteBuffer(char *src, int src_len) {
    data = (unsigned char *) src;
    position = 0;
    limit = src_len;
    capacity = src_len;
    order = ByteBuffer::BIG_ENDIAN;
}

int ByteBuffer::readInt() {
    // unsigned mask = 0xff;
    unsigned a = (data[position]     ) << 24;
    unsigned b = (data[position + 1] ) << 16; 
    unsigned c = (data[position + 2] ) <<  8 ;
    unsigned d =  data[position + 3] ;
    int ans = (a | b | c | d);
    position += 4;
    return ans;
}

ByteBuffer ByteBuffer::wrap(char *src, int src_len) {
    return ByteBuffer(src, src_len);
}
