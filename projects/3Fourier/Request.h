
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

    // ip, port, operationId, args, arglen, secs, usecs
    char *doOperation(string &, int, OperationId, char *, size_t, time_t, long);
    // operationId, args, arglen, secs, usecs
    char *doOperation(OperationId, char *, size_t, time_t, long);
private:
    DatagramSocket *sock;  // this attribute could be removed since it is required in one member function and their args for its constructor can be infered.
    string ip;
    int port;
};


#endif
