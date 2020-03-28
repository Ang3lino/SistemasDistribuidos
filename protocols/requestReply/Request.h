
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
    char *doOperation(string &, int, OperationId, char *);
    // operationId, args
    char *doOperation(OperationId, char *);
private:
    DatagramSocket sock;
    string ip;
    int port;
};

#endif