
#ifndef __bytebuffer__
#define __bytebuffer__ 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class ByteBuffer {
public:
    ByteBuffer(char *, int);

    int readInt();
    float readFloat();
    char read();

    // void order();

    static ByteBuffer wrap(char *, int);

    // ~ByteBuffer();
private:
    unsigned char *data;
    int position;
    int limit;
    int capacity;
    bool order;
};

#endif
