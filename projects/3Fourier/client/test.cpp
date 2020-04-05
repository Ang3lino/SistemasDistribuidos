#include <iostream>
#include "Message.h"
#include "DatagramSocket.h"

using namespace std;


void size_of_types() {
    cout << "int " << sizeof(int) << endl;
    cout << "float " << sizeof(float) << endl;
    cout << "double " << sizeof(double) << endl;
    cout << "char " << sizeof(char) << endl;
    cout << "short " << sizeof(short) << endl;
    cout << "Message " << sizeof(Message) << endl;
}

void serialize(Message *msgPacket, char *data) {
    int *q = (int*) data;    
    *q = msgPacket->messageType;       q++;    
    *q = msgPacket->requestId;   q++;    
    *q = msgPacket->operationId;     q++;
    *q = msgPacket->argumentLength;     q++;
    char *p = (char*) q;
    for (int i = 0; i < msgPacket->argumentLength; ++i) {
        *p = msgPacket->arguments[i];
        p++;
    }
}

void print_bytes(char *bytes, unsigned len) {
    int j = 0, count = 0;
    printf("\n%04d: ", ++count);
    for (unsigned i = 0; i < len; ++i) {
        printf("%02x ", (unsigned char) bytes[i]);
        if (++j == 16) {
            printf("\n%04d: ", ++count);
            j = 0;
        }
        if (j % 4 == 0) {
            printf("\t");
        }
    }
}

int main(int argc, char const *argv[]) {
    float src[1024];
    for (int i = 0  ; i < 512 ; ++i) src[i] = (float) i;
    for (int i = 512; i < 1024; ++i) src[i] = (float) 2*i;
    Message m;
    DatagramSocket s;

    m.messageType = MessageType::REQUEST;
    m.requestId = 1023;
    m.operationId = OperationId::DUMMY;
    m.argumentLength = sizeof(src);
    memcpy((char *) m.arguments, (char *) src, m.argumentLength);
    unsigned len = sizeof(Message);
    char bytes[len];
    serialize(&m, bytes);


    const int port = 5400;
    DatagramPacket p(bytes, len, "127.0.0.1", port);
    s.send(p);

    print_bytes(bytes, len);

    cout << endl;
    size_of_types();
    for (int i = 0; i < 512; ++i) printf("%f ", src[i]);
    return 0;
}