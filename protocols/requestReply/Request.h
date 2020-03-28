
#ifndef REQUEST_H
#define REQUEST_H

#include "DatagramSocket.h"
#include "Message.h"


class Request {
public:
    Request();
    // ip, port
    Request(string, int);

    // ip, port, operationId, args
    char *doOperation(string &, int, OperationId, char *, size_t);
    // operationId, args
    char *doOperation(OperationId, char *, size_t);
private:
    DatagramSocket *sock;
    string ip;
    int port;
};

#endif