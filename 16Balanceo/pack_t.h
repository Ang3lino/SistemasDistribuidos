
#ifndef __pack_h__
#define __pack_h__

#include <cstdint>

const int PACK_LEN = 4096;

typedef union {
    uint8_t frame[PACK_LEN];

    struct {
        unsigned id;                    // 4 bytes
        unsigned ack;                   // 4 byte
        uint8_t msg_type;               // 1 byte
        uint8_t data_len;               // 1 byte
        uint8_t data[PACK_LEN - 10];    // 4 bytes
    };
} pack_t;


#endif 

