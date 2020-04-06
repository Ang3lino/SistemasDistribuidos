
#ifndef REQUEST_H
#define REQUEST_H

#include "DatagramSocket.h"
#include "Message.h"
#include <limits.h>


class Request {
public:
    Request();
    // ip, port
    Request(string, int);

    // ip, port, operationId, args
    char *doOperation(string &, int, OperationId, char *, size_t);
    // operationId, args
    char *doOperation(OperationId, char *, size_t);

    // ip, port, operationId, args, arglen, secs, usecs
    char *doOperation(string &, int, OperationId, char *, size_t, time_t, long);
    // operationId, args, arglen, secs, usecs
    char *doOperation(OperationId, char *, size_t, time_t, long);
private:
    string ip;
    int port;
};


#endif
