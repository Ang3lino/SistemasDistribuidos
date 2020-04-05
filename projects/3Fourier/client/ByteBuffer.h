
#ifndef __bytebuffer__
#define __bytebuffer__ 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class ByteBuffer {
public:
    ByteBuffer(char *, int);

    int readInt();
    float readFloat();

    // void order();

    static ByteBuffer wrap(char *, int);
    static const int BIG_ENDIAN = 0, LITLE_ENDIAN = 1;

    // ~ByteBuffer();
private:
    unsigned char *data;
    int position;
    int limit;
    int capacity;
    bool order;
};

#endif
