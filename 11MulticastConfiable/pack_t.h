
#ifndef __pack_h__
#define __pack_h__

#include <cstdint>

typedef union {
    uint8_t frame[11];

    struct {
        unsigned id; // 4 bytes
        uint8_t ack; // 1 byte
        uint8_t msg_type;
        uint8_t data_len;
        uint8_t data[4]; // 4 bytes
    } ;
} pack_t;

#define new_pack_t { 0, 0, 0, 4, 0, 0, 0, 0 }

#endif 

