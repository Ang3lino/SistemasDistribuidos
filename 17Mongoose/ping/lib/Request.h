
#ifndef REQUEST_H
#define REQUEST_H

#include "DatagramSocket.h"
#include "Message.h"
#include "MulticastSocket.h"

#include <limits.h>
#include <memory>
#include <vector>
#include <tuple>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

class Request {
public:
    Request();
    // ip, port
    Request(string ip, int port);

    void setSoTimeout(long, long);

    // multiast operation
    vector<pair<string, int64_t > > doOperationMulticast (OperationId operationId, char *args, size_t arglen, int receptors);

    // ip, port, operationId, args
    char *doOperation(string &, int, OperationId, char *, size_t);
    // operationId, args
    char *doOperation(OperationId, char *, size_t);
    // ip, port, operationId, args, arglen, secs, usecs
    char *doOperation(string &, int, OperationId, char *, size_t, time_t, long);
    // operationId, args, arglen, secs, usecs
    char *doOperation(OperationId, char *, size_t, time_t, long);
private:
    string ip = "127.0.0.1";
    int port = 0;
    long secs = 0, u_secs = 0;
    bool timeout_set = false;
    unsigned ack = 0;

    void send(Message &, DatagramSocket &);
    int receive_ack(DatagramSocket &);

};


#endif

// Author: Angel Manriquez
